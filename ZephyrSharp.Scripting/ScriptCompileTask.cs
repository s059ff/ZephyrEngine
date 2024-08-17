using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.Remoting.Messaging;
using System.Text.RegularExpressions;

namespace ZephyrSharp.Scripting
{
    internal class ScriptCompileTask
    {
        public ScriptCompileTask(ScriptCompilerOption option)
        {
            this.option = option;
        }

        public void Compile(string[] codes)
        {
            Func<string, string> preprocess = (code) =>
            {
                code = this.PreprocessReservedMacro(code);  // To keep line numbers as original code
                code = this.PreprocessInclude(code);
                code = this.PreprocessComment(code);
                code = this.PreprocessFunctionMacro(code);
                code = this.PreprocessObjectMacro(code);
                return code;
            };

            Func<string, string> compile = (code) =>
            {
                code = this.ParsePartialFunction(code);
                code = this.option.DefineProgramEntryPoint ? this.AppendProgramEntryPoint(code) : code;
                code = this.ChangeClassMemberAttributes(code);
                code = this.InsertClassDefinition(code);
                code = this.MoveUsingStatements(code);
                code = this.option.FormatCode ? this.FormatCode(code) : code;
                return code;
            };

            this.OutputCode = compile(string.Join(EOL, codes.Select(preprocess)));
        }

        private string PreprocessComment(string code)
        {
            // Delete comments.
            code = Regex.Replace(code, @"/\*.*?\*/", string.Empty, RegexOptions.Singleline);
            code = Regex.Replace(code, @"//.+", string.Empty);

            // Delete compile-off sections.
            code = Regex.Replace(code, @"#if\s+true(?<code>.*?)#else.*?#endif", "${code}", RegexOptions.Singleline);
            code = Regex.Replace(code, @"#if\s+false.*?#else(?<code>.*?)#endif", "${code}", RegexOptions.Singleline);
            code = Regex.Replace(code, @"#if\s+true(?<code>.*?)#endif", "${code}", RegexOptions.Singleline);
            code = Regex.Replace(code, @"#if\s+false.*?#endif", string.Empty, RegexOptions.Singleline);

            return code;
        }

        private string PreprocessInclude(string code)
        {
            MatchEvaluator evaluator = (Match match) =>
            {
                string filename = match.Groups["path"].Value;
                foreach (var dir in this.option.IncludeDirectories)
                {
                    string path = Path.Combine(dir, filename);
                    if (File.Exists(path))
                    {
                        using (var stream = new StreamReader(path))
                        {
                            return this.PreprocessInclude(stream.ReadToEnd());
                        }
                    }
                }

                this.Errors.Add(new ScriptCompileError()
                {
                    Code = ScriptCompileError.ErrorCode.IncludeError,
                    Source = match.Value
                });
                return string.Empty;
            };

            Regex pattern = new Regex(@"#include\s+""(?<path>[\w\-. ]+)""");
            code = pattern.Replace(code, evaluator);

            return code;
        }

        private string PreprocessFunctionMacro(string code)
        {
            // Map of "FunctionName" -> "Statement of %1, %2, ..."
            Dictionary<string, string> macros = new Dictionary<string, string>();
            {
                MatchEvaluator evaluator = (Match match) =>
                {
                    string identifier = match.Groups["identifier"].Value;
                    string[] args = match.Groups["args"].Value.Split(',').Select(s => s.Trim()).ToArray();
                    string statement = match.Groups["statement"].Value.Trim();

                    // Replace arguments to "%i".
                    for (int i = 0; i < args.Length; i++)
                    {
                        Regex pattern = new Regex(new Regex(@"\b") + args[i] + new Regex(@"\b"));
                        statement = pattern.Replace(statement, $"%{i}");
                    }

                    macros.Add(identifier, statement);

                    return string.Empty;
                };

                {
                    Regex pattern = new Regex(@"#define\s+(?<identifier>\w+)\s*\((?<args>[^()]*)\)\s+(?<statement>.*)");
                    code = pattern.Replace(code, evaluator);
                }
            }

            // Replace macro.
            foreach (var macro in macros)
            {
                string identifier = macro.Key;
                string replace = macro.Value;

                MatchEvaluator evaluator1 = (Match match1) =>
                {
                    // Replace "%i" in statement to real arg.
                    string[] args = match1.Groups["args"].Value.Split(',').Select(s => s.Trim()).ToArray();
                    MatchEvaluator evaluator2 = (Match match2) =>
                    {
                        int n = int.Parse(match2.Groups["n"].Value);
                        try
                        {
                            return args[n];
                        }
                        catch (IndexOutOfRangeException)
                        {
                            this.Errors.Add(new ScriptCompileError()
                            {
                                Code = ScriptCompileError.ErrorCode.FunctionMacroError,
                                Source = match1.Value
                            });
                            return string.Empty;
                        }
                    };

                    Regex pattern = new Regex(@"%(?<n>\d+)");
                    return pattern.Replace(replace, evaluator2);
                };

                {
                    string pattern = identifier + new Regex(@"\s*\((?<args>[^()]*)\)");
                    code = Regex.Replace(code, pattern, evaluator1);
                }
            }

            return code;
        }

        private string PreprocessObjectMacro(string code)
        {
            Dictionary<string, string> macros = new Dictionary<string, string>();
            {
                Regex pattern = new Regex(@"#define\s+(?<identifier>\w+)\s+(?<statement>.*)");
                code = pattern.Replace(code, (match) =>
                {
                    string identifier = match.Groups["identifier"].Value;
                    string statement = match.Groups["statement"].Value.Trim();
                    macros.Add(identifier, statement);
                    return string.Empty;
                });
            }

            foreach (var macro in macros)
            {
                string pattern = new Regex(@"\b") + macro.Key + new Regex(@"\b");
                code = Regex.Replace(code, pattern, macro.Value);
            }

            return code;
        }

        private string PreprocessReservedMacro(string code)
        {
            string[] lines = code.Split('\n');
            for (int i = 0; i < lines.Length; i++)
            {
                string line = lines[i];
                string pattern = new Regex(@"\b") + "__LINE__" + new Regex(@"\b");
                lines[i] = Regex.Replace(line, pattern, (match) => (i + 1).ToString());
            }
            return string.Join(EOL, lines);
        }

        private string ParsePartialFunction(string code)
        {
            var functionMappings = new Dictionary<string, List<string>>();
            {
                string pattern = "^"
                    + "partial"
                    + new Regex(@"\s+")
                    + new Regex(@"(?<rettype>[\w\.<>\[\]]+)\s+(?<funcname>[\w]+)")
                    + new Regex(@"\s*\(\s*")
                    + new Regex(@"(?<arguments>[\w\.<>\[\]]+\s+[\w]+(\s*,\s*[\w\.<>\[\]]+\s+[\w]+)*)?")
                    + new Regex(@"\s*\)");
                MatchEvaluator evaluator = (Match match) =>
                {
                    string rettype = match.Groups["rettype"].Value;
                    if (rettype != "void")
                    {
                        this.Errors.Add(new ScriptCompileError()
                        {
                            Code = ScriptCompileError.ErrorCode.SyntaxError,
                            Source = match.Value
                        });
                        return match.Value;
                    }

                    string funcname1 = match.Groups["funcname"].Value;
                    string funcname2 = $"__{match.Groups["funcname"].Value}_{match.Index}";
                    string arguments = match.Groups["arguments"].Value;
                    if (arguments != string.Empty)
                    {
                        this.Errors.Add(new ScriptCompileError()
                        {
                            Code = ScriptCompileError.ErrorCode.SyntaxError,
                            Source = match.Value
                        });
                        return match.Value;
                    }

                    if (!functionMappings.ContainsKey(funcname1))
                        functionMappings[funcname1] = new List<string>();
                    functionMappings[funcname1].Add(funcname2);

                    return $"{rettype} {funcname2}({arguments})";
                };
                code = Regex.Replace(code, pattern, evaluator, RegexOptions.Multiline);
            }

#if true
            // Implementation using auto-generated function
            // NOTE: This implementation does NOT allow function arguments
            SortedSet<string> footers = new SortedSet<string>();
            foreach (var it in functionMappings)
            {
                string funcname = it.Key;
                List<string> funcnames = it.Value;
                string impl = $"void {funcname}() {{ {string.Join(" ", funcnames.Select(s => $"{s}();"))} }}";
                footers.Add(impl);
            }
            return string.Join(EOL, new[] { code }.Concat(footers));
#else
            // Implementation using inline code
            // NOTE: This implementation allows function arguments
            foreach (var it in functionMappings)
            {
                string funcname = it.Key;
                List<string> funcnames = it.Value;

                string pattern = new Regex(@"\b") + funcname + new Regex(@"\s*\((?<arguments>.*)\)");
                code = Regex.Replace(code, pattern, (match) =>
                {
                    string arguments = match.Groups["arguments"].Value;
                    string replace = string.Join(";", funcnames.Select(s => $"{s}({arguments})"));
                    return replace;
                });
            }
            return code;
#endif
        }

        private string InsertClassDefinition(string code)
        {
            return string.Join(EOL, $"public class {this.option.ScriptClassName}", "{", code, "}");
        }

        private string MoveUsingStatements(string code)
        {
            SortedSet<string> headers = new SortedSet<string>();
            MatchEvaluator evaluator = (Match match) =>
            {
                headers.Add(match.Value);
                return string.Empty;
            };

            code = Regex.Replace(code, @"^using\s+[\w\.<>\[\]]+;", evaluator, RegexOptions.Multiline);
            code = Regex.Replace(code, @"^using\s+[\w]+\s*=\s*[\w\.<>\[\]]+;", evaluator, RegexOptions.Multiline);

            return string.Join(EOL, headers.Concat(new[] { code }));
        }

        private string ChangeClassMemberAttributes(string code)
        {
            string pattern = "^"
                + new Regex(@"(?<attributes>([\w]+\s+)*)")
                + new Regex(@"(?<type>[\w\.<>\[\]]+)\s+(?<varname>[\w]+)");
            MatchEvaluator evaluator = (Match match) =>
            {
                string substring = match.Groups["attributes"].Value;
                SortedSet<string> attributes = new SortedSet<string>(
                    substring.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries)
                );
                string type = match.Groups["type"].Value;
                string varname = match.Groups["varname"].Value;
                string[] modifiers = new[] { "public", "protected", "private", "internal", "new" };
                if (type == "using")
                {
                    return match.Value;
                }
                else if (attributes.Intersect(modifiers).Count() > 0)
                {
                    this.Errors.Add(new ScriptCompileError()
                    {
                        Code = ScriptCompileError.ErrorCode.SyntaxError,
                        Source = match.Value
                    });
                    return match.Value;
                }
                else
                {
                    attributes.Add("public");
                    if (!attributes.Contains("const"))
                    {
                        attributes.Add("static");
                    }
                    string[] priority = new string[]
                    {
                        "public",
                        "static",
                        "const"
                    };
                    return $"{string.Join(" ", priority.Intersect(attributes))} {type} {varname}";
                }
            };
            code = Regex.Replace(code, pattern, evaluator, RegexOptions.Multiline);
            return code;
        }

        private string AppendProgramEntryPoint(string code)
        {
            string entrypoint = $"void Main(string[] args) {{ main(args); }}";
            return string.Join(EOL, new string[] { code, entrypoint });
        }

        private string FormatCode(string code)
        {
            return Regex.Replace(code, @"^\s*$\n|\r", string.Empty, RegexOptions.Multiline).TrimEnd();
        }

        private static readonly string EOL = Environment.NewLine;

        private readonly ScriptCompilerOption option;

        public List<ScriptCompileError> Errors { get; } = new List<ScriptCompileError>();

        public string OutputCode { get; private set; }
    }
}
