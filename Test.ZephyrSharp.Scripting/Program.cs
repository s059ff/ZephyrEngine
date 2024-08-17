using Microsoft.CodeDom.Providers.DotNetCompilerPlatform;
using System;
using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using ZephyrSharp.Scripting;

class CompileException : Exception
{
    public CompilerErrorCollection Errors;
}

class Program
{
    static void assert(bool condition)
    {
        if (!condition)
        {
            throw new Exception("Assertion error!");
        }
    }

    static void equals<T1, T2>(T1 a, T2 b)
    {
        assert(a.Equals(b));
    }

    public static void Main(string[] args)
    {
        string[] codes = Directory.GetFiles("./scripts", "*.cs").Select(p => File.ReadAllText(p)).ToArray();

        ScriptCompilerOption option = new ScriptCompilerOption()
        {
            IncludeDirectories = new string[] { "./scripts" },
            DefineProgramEntryPoint = true,
            FormatCode = true,
        };

        string code = ScriptCompiler.Compile(option, codes);
        Console.WriteLine(new string('-', 64));
        Console.WriteLine(code);
        Console.WriteLine(new string('-', 64));

        var provider = new CSharpCodeProvider(new Dictionary<string, string> { { "CompilerVersion", "v7.3" } });
        var results = provider.CompileAssemblyFromSource(
            new CompilerParameters() { GenerateExecutable = true }, new string[] { code }
        );
        if (results.Errors.Count > 0)
        {
            throw new CompileException() { Errors = results.Errors };
        }

        var assembly = results.PathToAssembly;

        ProcessStartInfo startinfo = new ProcessStartInfo(assembly)
        {
            UseShellExecute = false,
            RedirectStandardOutput = true,
            RedirectStandardInput = false
        };
        using (var process = Process.Start(startinfo))
        {
            string output = process.StandardOutput.ReadToEnd();
            string[] lines = output.Split(
                new string[] { Environment.NewLine },
                StringSplitOptions.None
            );
            string[] expects = new[]
            {
                "3",
                "japanjapan",
                "process1",
                "process2",
                "23",
                "0.1.2",
            };
            for (int i = 0; i < expects.Length; i++)
            {
                equals(lines[i], expects[i]);
            }

            Console.WriteLine("The test finished without any errors.");

            process.WaitForExit();
        }
    }
}
