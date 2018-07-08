using System;
using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;
using ZephyrSharp.Scripting;

namespace scc
{
    class Program
    {
        static void Main(string[] args)
        {
            List<string> paths = new List<string>();
            List<string> inc = new List<string>();
            List<string> @ref = new List<string>();
            string bin = "a.exe";
            string @class = "Script";
            string @base = "System.Object";
            string option = "";
            bool nocsc = false;
            bool classLib = false;
            bool pythonStyle = false;

            char prefix = '#';

            foreach (var item in args)
            {
                if (item == "/?")
                {
                    Console.WriteLine("cssc [/class:<classname>] [/ref:<file>] [/bin:<file>] [/base:<basename>] [/optimize] [/unsafe] [/win32icon:<file>] [/include:<dir>] [/nocsc] [/target:library] [/?] <src>");
                    Console.WriteLine();
                    Console.WriteLine("{0, -20}依存ファイルを指定します。", "/ref:<file>");
                    Console.WriteLine("{0, -20}出力ファイルを指定します。", "/bin:<file>");
                    Console.WriteLine("{0, -20}基底クラスを指定します。", "/base:<basename>");
                    Console.WriteLine("{0, -20}クラス名を指定します。", "/class:<classname>");
                    Console.WriteLine("{0, -20}インクルードファイルのディレクトリを指定します。", "/include:<dir>");
                    Console.WriteLine("{0, -20}入力ファイルを指定します。", "<src>");
                    Console.WriteLine("{0, -20}最適化を行います。", "/optimize");
                    Console.WriteLine("{0, -20}アンセーフコードを許可します。", "/unsafe");
                    Console.WriteLine("{0, -20}アイコンファイルを指定します。", "/win32icon:<file>");
                    Console.WriteLine("{0, -20}アセンブリの生成を行いません。", "/nocsc");
                    Console.WriteLine("{0, -20}クラスライブラリを出力します。", "/target:library");
                    Console.WriteLine("{0, -20}インデントでスコープを定義します。", "/scope:python");
                    Console.WriteLine();
                    Console.WriteLine("＊ソースファイルが一つも指定されていない場合、自動でソースファイルを検索します。");
                    Console.WriteLine();
                }

                var match = Regex.Match(item, @"/(?<name>\w+)(:(?<value>.*))?");
                if (match.Success)
                {
                    var name = match.Groups["name"].Value;
                    bool hasValue = (match.Groups.Count > 1);
                    var value = hasValue ? match.Groups["value"].Value : null;

                    switch (name)
                    {
                        case "ref":
                            @ref.Add(value);
                            break;
                        case "bin":
                            bin = value;
                            break;
                        case "base":
                            @base = value;
                            break;
                        case "class":
                            @class = value;
                            break;
                        case "include":
                            inc.Add(value);
                            break;
                        case "optimize":
                            option += " /optimize+";
                            break;
                        case "unsafe":
                            option += " /unsafe";
                            break;
                        case "win32icon":
                            option += " /win32icon:" + value;
                            break;
                        case "nocsc":
                            nocsc = true;
                            break;
                        case "target":
                            if (value == "library")
                                classLib = true;
                            break;
                        case "scope":
                            if (value == "python")
                                pythonStyle = true;
                            break;
                        default:
                            break;
                    }
                }
                else
                {
                    paths.Add(item);
                }
            }

            if (paths.Count == 0)
            {
                Console.WriteLine("入力ファイルを自動で検索します。");
                foreach (var path in Directory.GetFiles(Environment.CurrentDirectory, "*.cs", SearchOption.AllDirectories))
                {
                    var file = Path.GetFileName(path);
                    if (!file.StartsWith(prefix.ToString()) && (char.IsLower(file.First())))
                        paths.Add(path);
                }
                foreach (var path in paths)
                {
                    Console.WriteLine("+ " + path);
                }
            }

            // Auto add include directory.
            foreach (var path in paths)
            {
                inc.Add(Path.GetDirectoryName(path));
            }

            try
            {
                // Not preprocessed C#/Script -> C#/Script
                var processor1 = new ScriptPreprocessor();
                var params1 = new ScriptPreprocessorParameters(inc.ToArray());
                var results1 = processor1.PreprocessFromFile(params1, paths.ToArray());

                // C#/Script -> C#
                var processor2 = new ScriptConverter();
                var params2 = new ScriptConverterParameters(@class, @base, !classLib) { PythonScopeStyle = pythonStyle };
                var results2 = processor2.Convert(params2, results1.OutputSources);

                // (Save intermediate code.)
                List<string> csSourceFiles = new List<string>();
                for (int i = 0; i < results2.OutputSources.Length; i++)
                {
                    var dir = Path.GetDirectoryName(paths[i]);
                    var file = prefix + Path.GetFileName(paths[i]);
                    var path = Path.Combine(dir, file);
                    using (var stream = new StreamWriter(path))
                    {
                        stream.Write(results2.OutputSources[i]);
                    }
                    csSourceFiles.Add(path);
                }

                if (nocsc)
                    goto Finish;

                // C# -> Assembly
                var processor3 = CodeDomProvider.CreateProvider("C#");
                var params3 = new CompilerParameters()
                {
                    GenerateExecutable = (Path.GetExtension(bin) == ".exe"),
                    GenerateInMemory = false,
                    IncludeDebugInformation = false,
                    OutputAssembly = bin,
                    CompilerOptions = option
                };
                params3.ReferencedAssemblies.AddRange(results1.ReferencedAssemblies.ToArray());
                params3.ReferencedAssemblies.AddRange(@ref.ToArray());
                var results3 = processor3.CompileAssemblyFromFile(params3, csSourceFiles.ToArray());
                processor3.Dispose();
                if (results3.Errors.HasErrors)
                {
                    var results = results3;

                    // Modify line number and columns.
                    foreach (CompilerError error in results.Errors)
                    {
                        if (File.Exists(error.FileName))
                        {
                            string errorSource;
                            using (var reader = new StreamReader(error.FileName))
                            {
                                errorSource = reader.ReadToEnd().Split('\n')[error.Line - 1];
                            }

                            var original = error.FileName.Replace("#", "");
                            if (File.Exists(original))
                            {
                                using (var reader = new StreamReader(original))
                                {
                                    error.Line = getline(reader.ReadToEnd(), errorSource);
                                }
                            }
                        }
                    }

                    foreach (CompilerError error in results.Errors)
                    {
                        error.FileName = error.FileName.Replace("#", "");
                    }

                    Console.ForegroundColor = ConsoleColor.White;
                    Console.WriteLine("<!-- コンパイル エラー -->");
                    foreach (CompilerError error in results.Errors)
                    {
                        if (error.IsWarning)
                            Console.ForegroundColor = ConsoleColor.DarkYellow;
                        else
                            Console.ForegroundColor = ConsoleColor.DarkRed;
                        Console.WriteLine(error.ToString());
                    }
                    return;
                }

                Finish:
                Console.ForegroundColor = ConsoleColor.White;
                Console.WriteLine("コンパイルが成功しました。");
            }
            catch (Exception e)
            {
                Console.ForegroundColor = ConsoleColor.White;
                Console.WriteLine("コンパイル中に例外が発生しました。");
                Console.WriteLine(e);
            }
            finally
            {
                Console.ForegroundColor = ConsoleColor.White;
            }
        }

        static int getline(string body, string search)
        {
            const int NotFound = -1;

            int index = body.IndexOf(search);
            int line = NotFound;

            if (index != NotFound)
            {
                line = body.Substring(0, index).Split('\n').Length;
            }
            else
            {
                line = NotFound;
            }

            return line;
        }
    }
}
