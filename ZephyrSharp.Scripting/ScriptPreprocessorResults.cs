using System.CodeDom.Compiler;

namespace ZephyrSharp.Scripting
{
    public class ScriptPreprocessorResults
    {
        public string[] OutputSources { get; set; }

        public string[] ReferencedAssemblies { get; set; }
    }
}
