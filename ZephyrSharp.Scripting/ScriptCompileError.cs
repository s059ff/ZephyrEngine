namespace ZephyrSharp.Scripting
{
    public class ScriptCompileError
    {
        public ErrorCode Code { get; set; }

        public string Source { get; set; }

        public enum ErrorCode
        {
            IncludeError,
            FunctionMacroError,
            SyntaxError,
        }
    }
}
