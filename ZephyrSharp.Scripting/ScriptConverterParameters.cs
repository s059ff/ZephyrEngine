namespace ZephyrSharp.Scripting
{
    public class ScriptConverterParameters
    {
        public ScriptConverterParameters() { }

        public ScriptConverterParameters(string className) {
            this.ClassName = className;
        }

        public ScriptConverterParameters(string className, string baseClassName)
        {
            this.ClassName = className;
            this.BaseClassName = baseClassName;
        }

        public ScriptConverterParameters(string className, string baseClassName, bool generateExecutable)
        {
            this.ClassName = className;
            this.BaseClassName = baseClassName;
            this.GenerateExecutable = generateExecutable;
        }

        public string BaseClassName { get; set; } = "System.Object";

        public string ClassName { get; set; } = "Script";

        public bool SourceFormat { get; set; } = true;

        public bool GenerateExecutable { get; set; } = true;

        public bool PythonScopeStyle { get; set; } = false;

        public bool BatchScriptStyle { get; set; } = false;
    }
}
