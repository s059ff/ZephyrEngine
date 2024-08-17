using System;
using System.Collections.Generic;
using System.Linq;

namespace ZephyrSharp.Scripting
{
    public class ScriptCompileException : Exception
    {
        public List<ScriptCompileError> Errors { get; set; }
    }
}
