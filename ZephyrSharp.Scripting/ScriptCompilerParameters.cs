namespace ZephyrSharp.Scripting
{
    /// <summary>
    /// コンパイラの設定を表します。
    /// </summary>
    public class ScriptCompilerParameters
    {
        /// <summary>
        /// #include ディレクティブによってインクルードされるヘッダファイルを検索するディレクトリを表します。
        /// </summary>
        public string[] IncludeDirectories { get; set; }

        /// <summary>
        /// ラッピングするクラスの基底クラスの名前。
        /// </summary>
        public string BaseClassName { get; set; } = "System.Object";

        /// <summary>
        /// ラッピングするクラスの名前。
        /// </summary>
        public string ClassName { get; set; } = "Script";

        /// <summary>
        /// 出力ソースコードのフォーマットを行うかどうか。
        /// </summary>
        public bool SourceFormat { get; set; } = true;

        /// <summary>
        /// 実行可能ファイルを出力するかどうか。
        /// </summary>
        public bool GenerateExecutable { get; set; } = true;

        /// <summary>
        /// インデントでスコープを定義するかどうか。
        /// </summary>
        public bool PythonScopeStyle { get; set; } = false;

        /// <summary>
        /// バッチファイル形式かどうか。
        /// </summary>
        public bool BatchScriptStyle { get; set; } = false;

        /// <summary>
        /// メモリ内に出力する場合は true にします。
        /// </summary>
        public bool GenerateInMemory { get; set; } = true;

        /// <summary>
        /// 出力ファイルの名前。
        /// </summary>
        public string AssemblyName { get; set; }

        /// <summary>
        /// 参照アセンブリ。
        /// </summary>
        public string[] ReferencedAssemblies { get; set; } = new string[] { };
    }
}
