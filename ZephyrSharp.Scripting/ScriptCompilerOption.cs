namespace ZephyrSharp.Scripting
{
    public class ScriptCompilerOption
    {
        public string[] IncludeDirectories { get; set; } = { };

        public string ScriptClassName { get; set; } = "Script";

        public bool DefineProgramEntryPoint { get; set; } = false;

        public bool FormatCode { get; set; } = false;
    }
}
