namespace ZephyrSharp.Scripting
{
    public class ScriptPreprocessorParameters
    {
        public ScriptPreprocessorParameters() { }

        public ScriptPreprocessorParameters(params string[] includeDirectories)
        {
            this.IncludeDirectories = includeDirectories;
        }

        public string[] IncludeDirectories { get; set; }
    }
}
