using System.CodeDom.Compiler;
using System.IO;
using System.Linq;
using System.Reflection;

namespace ZephyrSharp.Scripting
{
    public class ScriptCompiler
    {
        public static Assembly CompileAssemblyFromFile(ScriptCompilerParameters parameters, params string[] filenames)
        {
            string[] sources = filenames.Select(filename =>
            {
                using (StreamReader sr = new StreamReader(filename))
                {
                    return sr.ReadToEnd();
                }
            }).ToArray();

            return CompileAssemblyFromSource(parameters, sources);
        }

        public static Assembly CompileAssemblyFromSource(ScriptCompilerParameters parameters, params string[] sources)
        {
            // Not preprocessed C#/Script -> C#/Script
            ScriptPreprocessorResults results1 = new ScriptPreprocessor().Preprocess(new ScriptPreprocessorParameters()
            {
                IncludeDirectories = parameters.IncludeDirectories
            }, sources);

            // C#/Script -> C#
            ScriptConverterResults results2 = new ScriptConverter().Convert(new ScriptConverterParameters()
            {
                ClassName = parameters.ClassName,
                BaseClassName = parameters.BaseClassName,
                GenerateExecutable = parameters.GenerateExecutable,
                PythonScopeStyle = parameters.PythonScopeStyle,
                BatchScriptStyle = parameters.BatchScriptStyle,
                SourceFormat = parameters.SourceFormat
            }, results1.OutputSources);

            // C# -> Assembly
            var params3 = new CompilerParameters()
            {
                OutputAssembly = parameters.AssemblyName,
                GenerateExecutable = parameters.GenerateExecutable,
                GenerateInMemory = parameters.GenerateInMemory,
                IncludeDebugInformation = false,
                CompilerOptions = "/optimize+ ",
            };
            params3.ReferencedAssemblies.AddRange(results1.ReferencedAssemblies.ToArray());
            params3.ReferencedAssemblies.AddRange(parameters.ReferencedAssemblies);
            params3.ReferencedAssemblies.AddRange(Directory.GetFiles(Path.GetDirectoryName(Assembly.GetEntryAssembly().Location), "*.dll"));
            params3.ReferencedAssemblies.AddRange(Directory.GetFiles(Path.GetDirectoryName(Assembly.GetEntryAssembly().Location), "*.exe"));

            CompilerResults results3 = CodeDomProvider.CreateProvider("C#").CompileAssemblyFromSource(params3, results2.OutputSources);
            if (0 < results3.Errors.Count)
                throw new CompilerErrorException("C# コンパイル", results3.Errors);

            return results3.CompiledAssembly;
        }
    }
}
