namespace ZephyrSharp.Scripting
{
    public static class ScriptCompiler
    {
        public static string Compile(ScriptCompilerOption option, string[] codes)
        {
            ScriptCompileTask task = new ScriptCompileTask(option);
            task.Compile(codes);

            if (task.Errors.Count > 0)
            {
                throw new ScriptCompileException() { Errors = task.Errors };
            }

            return task.OutputCode;
        }
    }
}
