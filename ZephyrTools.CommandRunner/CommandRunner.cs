using System.CodeDom.Compiler;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Threading;
using System.Windows.Forms;
using ZephyrSharp.Scripting;
using Timer = System.Windows.Forms.Timer;

namespace ZephyrTools.CommandRunner
{
    public partial class CommandRunner : Form
    {
        public static CommandRunner Execute()
        {
            CommandRunner form = null;
            var thread = new Thread(() =>
            {
                form = new CommandRunner();
                Application.Run(form);
            });
            thread.SetApartmentState(ApartmentState.STA);
            thread.Start();

            while (form == null)
                Thread.Sleep(1);

            return form;
        }

        public static void Shutdown(CommandRunner monitor)
        {
            monitor.Invoke((MethodInvoker)(() => monitor.Close()));
        }

        private CommandRunner()
        {
            InitializeComponent();

            this.splitContainer1.Panel1.Controls.Add(Scintilla);
            Scintilla.BringToFront();

            this.splitContainer1.Panel2.Controls.Add(ErrorView);
            ErrorView.BringToFront();

            Scintilla.TextChanged += Scintilla_TextChanged;
            Scintilla.SaveCommand += Scintilla_SaveCommand;
            Scintilla.CloseCommand += Scintilla_CloseCommand;
            Scintilla.OpenCommand += Scintilla_OpenCommand;

            this.Text = this.Text.Replace("*", "");
        }

        private void Scintilla_OpenCommand()
        {
            OpenNew();
        }

        private void Scintilla_SaveCommand()
        {
            Save();
        }

        private void Scintilla_CloseCommand()
        {
            Close();
        }

        private void Scintilla_TextChanged(object sender, System.EventArgs e)
        {
            if (!this.Text.EndsWith("*"))
                this.Text += "*";
        }

        private CustomScintilla Scintilla = new CustomScintilla();

        private ErrorView ErrorView = new ErrorView();

        private int CommandNumber = 0;

        private string OpenFilePath;

        private void openToolStripMenuItem_Click(object sender, System.EventArgs e)
        {
            OpenNew();
        }

        private void saveToolStripMenuItem_Click(object sender, System.EventArgs e)
        {
            Save();
        }

        private void Open(string path)
        {
            if (File.Exists(path))
            {
                using (var stream = new StreamReader(path))
                    Scintilla.Text = stream.ReadToEnd();
                OpenFilePath = path;
            }
            this.Text = this.Text.Replace("*", "");
        }

        private void OpenNew()
        {
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.Filter = "C# ファイル|*.cs|すべてのファイル|*.*";
            dialog.InitialDirectory = Directory.GetCurrentDirectory();

            if (dialog.ShowDialog() == DialogResult.OK)
            {
                var path = dialog.FileName;
                this.Open(path);
            }
        }

        private void Save()
        {
            if (OpenFilePath == null)
            {
                SaveFileDialog dialog = new SaveFileDialog();
                dialog.Filter = "C# ファイル|*.cs|すべてのファイル|*.*";
                dialog.InitialDirectory = Directory.GetCurrentDirectory();

                if (dialog.ShowDialog() == DialogResult.OK)
                {
                    OpenFilePath = dialog.FileName;
                }
            }

            if (OpenFilePath != null)
            {
                using (var stream = new StreamWriter(OpenFilePath))
                    stream.Write(Scintilla.Text);
                this.Text = this.Text.Replace("*", "");
            }
        }

        private void runToolStripMenuItem_Click(object sender, System.EventArgs e)
        {
            Run();
        }

        private void NotifyMessage(string message)
        {
            this.toolStripStatusLabel1.Text = message;

            Timer tickTimer = new Timer() { Interval = 3000 };
            tickTimer.Tick += (s, _e) =>
            {
                this.toolStripStatusLabel1.Text = string.Empty;
                tickTimer.Dispose();
            };
            tickTimer.Start();
        }

        private void NotifyProgress(int progress)
        {
            this.toolStripProgressBar1.Value = progress;
        }

        private void Run()
        {
            var source = this.Scintilla.Text;

            this.ErrorView.Clear();

            this.NotifyProgress(0);

            this.CommandNumber++;

            ScriptPreprocessorResults results1 = null;

            #region Not preprocessed C#/Script -> C#/Script
            {
                var params1 = new ScriptPreprocessorParameters(Path.GetDirectoryName(OpenFilePath));
                try
                {
                    results1 = new ScriptPreprocessor().Preprocess(params1, source);
                }
                catch (CompilerErrorException e)
                {
                    if (e.Errors.Count > 0)
                    {
                        foreach (CompilerError error in e.Errors)
                        {
                            this.ErrorView.Add(error);
                        }
                        this.NotifyMessage("プリプロセスエラーが発生しました。");
                        this.NotifyProgress(0);
                        return;
                    }
                }
                this.NotifyProgress(25);
            }
            #endregion

            ScriptConverterResults results2;

            #region C#/Script -> C#
            {
                string baseclass = Assembly.GetEntryAssembly().GetType("GameScript") != null ? "GameScript" : "object";
                var params2 = new ScriptConverterParameters("_Command" + this.CommandNumber, baseclass, false) { BatchScriptStyle = true };
                results2 = new ScriptConverter().Convert(params2, results1.OutputSources);

                this.NotifyProgress(50);
            }
            #endregion

            var source2 = results2.OutputSources[0];

            CompilerResults results3;

            #region C# -> Assembly
            {
                var compiler = CodeDomProvider.CreateProvider("C#");
                var params3 = new CompilerParameters()
                {
                    GenerateExecutable = false,
                    GenerateInMemory = true,
                    IncludeDebugInformation = false,
                };
                params3.ReferencedAssemblies.AddRange(results1.ReferencedAssemblies.ToArray());
                params3.ReferencedAssemblies.AddRange(Directory.GetFiles(Application.StartupPath, "*.dll"));
                params3.ReferencedAssemblies.AddRange(Directory.GetFiles(Application.StartupPath, "*.exe"));
                params3.CompilerOptions += " /unsafe";
                params3.CompilerOptions += " /optimize+";

                results3 = compiler.CompileAssemblyFromSource(params3, source2);
                compiler.Dispose();
                if (results3.Errors.HasErrors)
                {
                    string[] splitedSource2 = source2.Split('\n');

                    foreach (CompilerError error in results3.Errors)
                    {
                        int lineOfSource2 = error.Line - 1;

                        if (0 <= lineOfSource2 && lineOfSource2 < splitedSource2.Length)
                        {
                            string errorText = splitedSource2[lineOfSource2];
                            error.Line = getline(source, errorText);
                        }

                        this.ErrorView.Add(error);
                    }
                    this.NotifyMessage("コンパイルエラーが発生しました。");
                    this.NotifyProgress(0);
                    return;
                }
                this.NotifyProgress(100);
            }
            #endregion

            #region Run script
            {
                var asm = results3.CompiledAssembly;
                var type = asm.GetType("_Command" + this.CommandNumber);
                type.GetMethod("run").Invoke(null, null);
                this.NotifyMessage("スクリプトの実行が完了しました。");
            }
            #endregion
        }

        private static int getline(string body, string search)
        {
            const int NotFound = -1;

            int index = body.IndexOf(search);
            int line = NotFound;

            if (index != NotFound)
            {
                line = body.Substring(0, index).Split('\n').Length;
            }
            else
            {
                line = NotFound;
            }

            return line;
        }
    }
}
