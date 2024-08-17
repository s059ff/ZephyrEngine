using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;
using ZephyrSharp.Scripting;

class Program
{
    static void Main(string[] args)
    {
        var inputFileNames = new List<string>();
        var option = new ScriptCompilerOption() { FormatCode = true };
        string outputFileName = string.Empty;

        foreach (var argv in args)
        {
            var pattern = new Regex(@"^/(?<identifier>\w+)(:(?<value>.*))?");
            var match = pattern.Match(argv);
            if (match.Success)
            {
                var identifier = match.Groups["identifier"].Value;
                var value = match.Groups["value"].Value;

                switch (identifier)
                {
                    case "include":
                        if (!Directory.Exists(value))
                        {
                            throw new Exception($"Not found directory: '{value}'");
                        }
                        option.IncludeDirectories = option.IncludeDirectories.Append(value).ToArray();
                        break;

                    case "scriptclass":
                        option.ScriptClassName = value;
                        break;

                    case "entrypoint":
                        option.DefineProgramEntryPoint = true;
                        break;

                    case "format":
                        option.FormatCode = true;
                        break;

                    case "output":
                        outputFileName = value;
                        break;

                    default:
                        throw new Exception($"Invalid identifier: '{identifier}'");
                }
            }
            else
            {
                string path = argv;
                string dirname = Path.GetDirectoryName(path);
                string filename = Path.GetFileName(path);
                string[] filenames = Directory.GetFiles(dirname, filename); // To be able to handle wildcard(*).
                inputFileNames.AddRange(filenames);
                option.IncludeDirectories = option.IncludeDirectories.Append(dirname).ToArray();
            }
        }

        string[] sources = inputFileNames.Select(path => File.ReadAllText(path)).ToArray();

        try
        {
            string code = ScriptCompiler.Compile(option, sources);
            if (outputFileName != string.Empty)
            {
                File.WriteAllText(outputFileName, code);
                Console.WriteLine($"Compiled code was written to '{Path.GetFullPath(outputFileName)}'.");
            }
            else
            {
                Console.WriteLine(code);
            }
        }
        catch (ScriptCompileException e)
        {
            foreach (var error in e.Errors)
            {
                Console.WriteLine($"{error.Code}, {e.Source}");
            }

            throw;
        }
    }
}
