using ICSharpCode.NRefactory.CSharp;
using System;
using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text.RegularExpressions;

namespace ZephyrSharp.Scripting
{
    public class ScriptConverter
    {
        public ScriptConverterResults Convert(ScriptConverterParameters parameters, params string[] sources)
        {
            this.parameters = parameters;

            this.results = new ScriptConverterResults();
            this.results.OutputSources = new string[sources.Length];
            this.errors = new CompilerErrorCollection();
            this.PartialFunctionSuffix = new Dictionary<string, PartialFunctionInfo>();

            for (int i = 0; i < sources.Length; i++)
            {
                var source = sources[i];

                if (parameters.PythonScopeStyle)
                    source = ParseIndentToBlockScope(source);

                if (parameters.BatchScriptStyle)
                    source = ParseBatchScript(source);

                source = AutoUsings(source);

                source = ParsePartialFunction(source);

                if (i == sources.Length - 1)
                {
                    if (this.parameters.GenerateExecutable)
                        source = CreateMainMethod(source);

                    source = CreateCallerPartialFuntion(source);
                }

                source = InsertClass(source);

                source = ArrangeUsings(source);

                source = Format(source);

                this.results.OutputSources[i] = source;
            }

            return this.results;
        }

        ScriptConverterParameters parameters;

        ScriptConverterResults results;

        CompilerErrorCollection errors;

        class PartialFunctionInfo
        {
            public int FunctionNumber;
        }

        Dictionary<string, PartialFunctionInfo> PartialFunctionSuffix;

        string ParseIndentToBlockScope(string source)
        {
            Func<string, int> CountIndent = (string line) =>
            {
                return line.Length - line.TrimStart(' ').Length;
            };
            string[] sourceByLines = source.Split(new string[] { Environment.NewLine }, StringSplitOptions.None);

            int prevIndent = 0;
            for (int i = 0; i < sourceByLines.Length; i++)
            {
                int indent = CountIndent(sourceByLines[i]);
                if (prevIndent < indent)
                {
                    sourceByLines[i] = "{" + sourceByLines[i];
                }
                else if (prevIndent > indent)
                {
                    sourceByLines[i] = "}" + sourceByLines[i];
                }
                prevIndent = indent;
            }

            return string.Join(string.Empty, sourceByLines);
        }

        string ParseBatchScript(string source)
        {
            return "void new run() {" + source + "}";
        }

        string AutoUsings(string source)
        {
            string usings = string.Empty;

            Action<Type> addNamespace = null;
            addNamespace = (type) =>
            {
                var @namespace = type.Namespace;
                if (@namespace != null && @namespace.StartsWith("ZephyrSharp"))
                {
                    usings += "using " + @namespace + ";" + Environment.NewLine;
                }

                foreach (Type _type in type.GetNestedTypes())
                {
                    addNamespace(_type);
                }
            };

            foreach (var name in Assembly.GetEntryAssembly().GetReferencedAssemblies())
            {
                Assembly assembly = Assembly.Load(name.ToString());
                foreach (var type in assembly.GetTypes())
                {
                    addNamespace(type);
                }
            }

            return usings + source;
        }

        string ParsePartialFunction(string source)
        {
            MatchEvaluator evaluator = (Match match) =>
            {
                var name = match.Groups["name"].Value;
                if (!this.PartialFunctionSuffix.ContainsKey(name))
                {
                    this.PartialFunctionSuffix.Add(name, new PartialFunctionInfo() { FunctionNumber = 0 });
                }
                int suffix = this.PartialFunctionSuffix[name].FunctionNumber;
                this.PartialFunctionSuffix[name].FunctionNumber++;
                return string.Format("void {0}{1}", name, suffix);
            };

            source = Regex.Replace(source, @"partial\s+void\s+(?<name>\w+)", evaluator);

            return source;
        }

        string InsertClass(string source)
        {
            return
                "public partial class " + this.parameters.ClassName + " : " + this.parameters.BaseClassName
                + Environment.NewLine
                + "{"
                + Environment.NewLine
                + source
                + Environment.NewLine
                + "}"
                + Environment.NewLine;
        }

        string ArrangeUsings(string source)
        {
            SortedSet<string> namespaces = new SortedSet<string>();

            MatchEvaluator evaluator = (Match match) =>
            {
                string @namespace = match.Groups["namespace"].Value;
                namespaces.Add(@namespace);
                return string.Empty;
            };

            source = Regex.Replace(source, @"using\s+(?<namespace>.*);", evaluator);

            string header = string.Empty;

            foreach (var @namespace in namespaces)
            {
                header = header + "using " + @namespace + ";" + Environment.NewLine;
            }

            source = header + source;

            return source;
        }

        string CreateCallerPartialFuntion(string source)
        {
            foreach (var item in this.PartialFunctionSuffix)
            {
                var functionName = item.Key;
                var functionCount = item.Value.FunctionNumber;

                string partialFunctionContents = "public void " + functionName + "()" + Environment.NewLine;
                partialFunctionContents += "{" + Environment.NewLine;
                for (int i = 0; i < functionCount; i++)
                {
                    int suffix = i;
                    partialFunctionContents += string.Format("{0}{1}();", functionName, suffix);
                    partialFunctionContents += Environment.NewLine;
                }

                partialFunctionContents += "}" + Environment.NewLine;

                source += partialFunctionContents;
            }

            return source;
        }

        string CreateMainMethod(string source)
        {
            source += "[System.STAThreadAttribute]";
            source += "static void Main(string[] args)";
            source += "{";
            source += parameters.ClassName + ".main();";
            source += "}";

            return source;
        }

        string Format(string source)
        {
            var parser = new CSharpParser();

            var root = parser.Parse(source, "");

            foreach (var target in root.Descendants.OfType<MethodDeclaration>())
            {
                if (target.Modifiers.HasFlag(Modifiers.Private))
                {
                    target.Modifiers ^= Modifiers.Private;
                }
                if (target.Modifiers.HasFlag(Modifiers.Protected))
                {
                    target.Modifiers ^= Modifiers.Protected;
                }
                target.Modifiers |= Modifiers.Public;
                target.Modifiers |= Modifiers.Static;
            }
            foreach (var target in root.Descendants.OfType<FieldDeclaration>())
            {
                if (target.Modifiers.HasFlag(Modifiers.Private))
                {
                    target.Modifiers ^= Modifiers.Private;
                }
                if (target.Modifiers.HasFlag(Modifiers.Protected))
                {
                    target.Modifiers ^= Modifiers.Protected;
                }
                target.Modifiers |= Modifiers.Public;
                if (!target.Modifiers.HasFlag(Modifiers.Const))
                    target.Modifiers |= Modifiers.Static;
            }
            foreach (var target in root.Descendants.OfType<PropertyDeclaration>())
            {
                if (target.Modifiers.HasFlag(Modifiers.Private))
                {
                    target.Modifiers ^= Modifiers.Private;
                }
                if (target.Modifiers.HasFlag(Modifiers.Protected))
                {
                    target.Modifiers ^= Modifiers.Protected;
                }
                target.Modifiers |= Modifiers.Public;
                target.Modifiers |= Modifiers.Static;
            }
            foreach (var target in root.Descendants.OfType<TypeDeclaration>())
            {
                if (target.Modifiers.HasFlag(Modifiers.Private))
                {
                    target.Modifiers ^= Modifiers.Private;
                }
                if (target.Modifiers.HasFlag(Modifiers.Protected))
                {
                    target.Modifiers ^= Modifiers.Protected;
                }
                target.Modifiers |= Modifiers.Public;
            }

            return root.ToString();
        }
    }
}
