using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace ZephyrSharp.Scripting
{
    public class ScriptPreprocessor
    {
        /// <summary>
        /// C#/Script のプリプロセスを行います。
        /// </summary>
        /// <param name="parameters">プリプロセッサの設定。</param>
        /// <param name="sources">ソースプログラム。</param>
        /// <returns></returns>
        public ScriptPreprocessorResults Preprocess(ScriptPreprocessorParameters parameters, params string[] sources)
        {
            this.parameters = parameters;

            this.results = new ScriptPreprocessorResults();
            this.results.ReferencedAssemblies = new string[] { };
            this.results.OutputSources = new string[sources.Length];
            this.errors = new CompilerErrorCollection();

            for (int i = 0; i < sources.Length; i++)
            {
                this.currentSourceNumber = i;

                string code = sources[i];

                // Delete comments.
                code = PreprocessComment(code);

                // Expand #include directives.
                code = PreprocessInclude(code);

                // Expand macro.
                code = PreprocessFunctionMacro(code);
                code = PreprocessObjectMacro(code);

                // Preprocess reserved macros.
                code = PreprocessReservedMacro(code);

                // Process #using directives.
                code = PreprocessUsing(code);

                this.results.OutputSources[i] = code;
            }

            foreach (PreprocessorError error in this.errors)
            {
                // Modify error information.
                string source = sources[error.SourceNumber];
                int index = source.IndexOf(error.ErrorText);
                int line = source.Substring(0, index).Split('\n').Length;
                int column = source.Split('\n')[line].IndexOf(error.ErrorText);
                error.Line = line + 1;
                error.Column = column;
            }

            if (this.errors.HasErrors)
                throw new CompilerErrorException("C#/Script プリプロセス", this.errors);

            return this.results;
        }

        /// <summary>
        /// C#/Script のプリプロセスを行います。
        /// </summary>
        /// <param name="parameters">プリプロセッサの設定。</param>
        /// <param name="sources">ソースファイル。</param>
        /// <returns></returns>
        public ScriptPreprocessorResults PreprocessFromFile(ScriptPreprocessorParameters parameters, params string[] filenames)
        {
            string[] sources = filenames.Select(filename =>
            {
                using (StreamReader sr = new StreamReader(filename))
                {
                    return sr.ReadToEnd();
                }
            }).ToArray();

            var result = Preprocess(parameters, sources);

            foreach (PreprocessorError error in this.errors)
            {
                error.FileName = filenames[error.SourceNumber];
            }

            return result;
        }

        ScriptPreprocessorParameters parameters;

        ScriptPreprocessorResults results;

        CompilerErrorCollection errors;

        int currentSourceNumber;

        string PreprocessComment(string source)
        {
            // Delete comments.
            source = Regex.Replace(source, @"/\*.*?\*/", "", RegexOptions.Singleline);
            source = Regex.Replace(source, @"//[^/]$.*", "");

            // Delete compile-off sections.
            MatchEvaluator evaluator = (Match match) => { return match.Groups["code"].Value; };
            source = Regex.Replace(source, @"#if\s+true(?<code>.*?)#else.*?#endif", evaluator, RegexOptions.Singleline);
            source = Regex.Replace(source, @"#if\s+false.*?#else(?<code>.*?)#endif", evaluator, RegexOptions.Singleline);
            source = Regex.Replace(source, @"#if\s+true(?<code>.*?)#endif", evaluator, RegexOptions.Singleline);
            source = Regex.Replace(source, @"#if\s+false.*?#endif", string.Empty, RegexOptions.Singleline);

            return source;
        }

        string PreprocessInclude(string source)
        {
            MatchEvaluator evaluator = (Match match) =>
            {
                string filename = match.Groups["path"].Value;
                foreach (var dir in this.parameters.IncludeDirectories)
                {
                    string path = Path.Combine(dir, filename);
                    if (File.Exists(path))
                    {
                        using (var stream = new StreamReader(path))
                        {
                            var temp = stream.ReadToEnd();
                            temp = PreprocessComment(temp);
                            temp = PreprocessInclude(temp);
                            return temp;
                        }
                    }
                }

                this.errors.Add(new PreprocessorError()
                {
                    ErrorText = match.Value,
                    ErrorNumber = ParseErrorMessage(ErrorNumbers.IncludeFileIsNotFound),
                    SourceNumber = this.currentSourceNumber
                });

                return string.Empty;
            };

            source = Regex.Replace(source, @"#include\s+""(?<path>.*)""", evaluator);

            return source;
        }

        string PreprocessFunctionMacro(string source)
        {
            // Map of "FunctionName" -> "Statement of %1, %2, ..."
            Dictionary<string, string> macros = new Dictionary<string, string>();

            // Build the macro database.
            {
                MatchEvaluator evaluator = (Match match) =>
                {
                    var name = match.Groups["name"].Value;
                    var args = Regex.Split(match.Groups["args"].Value, @"\s*,\s*");
                    var after = match.Groups["after"].Value.TrimEnd('\r', '\n');

                    // Replace arguments to "%i".
                    for (int i = 0; i < args.Length; i++)
                    {
                        after = Regex.Replace(after, @"\b" + args[i] + @"\b", "%" + i);
                    }

                    // Add to database.
                    macros.Add(name, after);

                    return string.Empty;
                };

                source = Regex.Replace(source, @"#define\s+(?<name>\w+)\s*\((?<args>[^()]*)\)\s+(?<after>.*)", evaluator);
            }

            // Replace macro.
            foreach (var macro in macros)
            {
                var name = macro.Key;
                var after = macro.Value;

                MatchEvaluator evaluator = (Match match) =>
                {
                    var arg = match.Groups["args"].Value;
                    var args = Regex.Split(arg, ",");

                    // Replace "%i" in statement to real arg.
                    MatchEvaluator _evaluator = (Match _match) =>
                    {
                        int n = int.Parse(_match.Groups["number"].Value);
                        if (args.Length <= n)
                        {
                            this.errors.Add(new PreprocessorError()
                            {
                                ErrorText = match.Value,
                                ErrorNumber = ParseErrorMessage(ErrorNumbers.FunctionMacroArgumentIsNotEnough),
                                SourceNumber = this.currentSourceNumber
                            });
                            return "";
                        }
                        return args[n];
                    };

                    return Regex.Replace(after, @"%(?<number>\d+)", _evaluator);
                };

                source = Regex.Replace(source, name + @"\s*\((?<args>[^()]*)\)", evaluator);
            }

            return source;
        }

        string PreprocessObjectMacro(string source)
        {
            Dictionary<string, string> macros = new Dictionary<string, string>();

            MatchEvaluator evaluator = (Match match) =>
            {
                string name = match.Groups["name"].Value;
                string after = match.Groups["statement"].Value.TrimEnd('\r', '\n');
                macros.Add(name, after);
                return string.Empty;
            };

            source = Regex.Replace(source, @"#define\s+(?<name>\w+)\s+(?<statement>.*)", evaluator);

            foreach (var macro in macros)
            {
                source = Regex.Replace(source, @"\b" + macro.Key + @"\b", macro.Value);
            }

            return source;
        }

        string PreprocessReservedMacro(string source)
        {
            string[] lines = source.Split('\n');
            for (int i = 0; i < lines.Length; i++)
            {
                lines[i] = lines[i].Replace("__LINE__", (i + 1).ToString());
            }
            return string.Join("\n", lines);
        }

        string PreprocessUsing(string source)
        {
            SortedSet<string> refs = new SortedSet<string>();

            MatchEvaluator evaluator = (Match match) =>
            {
                string filename = match.Groups["filename"].Value;
                refs.Add(Path.GetFullPath(filename));
                return string.Empty;
            };

            this.results.ReferencedAssemblies = refs.ToArray();

            source = Regex.Replace(source, @"#using\s+""(?<filename>.*)""", evaluator);

            return source;
        }

        static string ParseErrorMessage(ErrorNumbers errorNumber)
        {
            switch (errorNumber)
            {
                case ErrorNumbers.IncludeFileIsNotFound:
                    return "インクルードファイルが見つかりません。インクルードファイルの検索ディレクトリを確かめてください。";

                case ErrorNumbers.FunctionMacroArgumentIsNotEnough:
                    return "関数マクロの引数の数が足りません。";

                default:
                    return "不明なエラー。";
            }
        }

        enum ErrorNumbers
        {
            UnknownError,
            IncludeFileIsNotFound,
            FunctionMacroArgumentIsNotEnough
        }

        class PreprocessorError : CompilerError
        {
            public int SourceNumber;
        }
    }
}
