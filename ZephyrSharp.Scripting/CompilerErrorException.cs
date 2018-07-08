using System;
using System.CodeDom.Compiler;
using System.IO;

namespace ZephyrSharp.Scripting
{
    public class CompilerErrorException : Exception
    {
        public CompilerErrorException(string processName, CompilerErrorCollection errors)
        {
            this.ProcessName = processName;
            this.Errors = errors;
        }

        public override string ToString()
        {
            StringWriter stream = new StringWriter();

            if (0 < Errors.Count)
            {
                stream.WriteLine("{0} が失敗しました。", ProcessName);

                stream.WriteLine("<!-- {0} エラー -->", ProcessName);

                foreach (CompilerError error in Errors)
                {
                    stream.WriteLine("{0}({1}, {2}) {3}", error.FileName, error.Line, error.Column, error.ErrorText);
                }
            }

            return stream.ToString();
        }

        public string ProcessName { get; set; }

        public CompilerErrorCollection Errors { get; set; }
    }
}
