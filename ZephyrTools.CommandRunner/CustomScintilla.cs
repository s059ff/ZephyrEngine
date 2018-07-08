using ScintillaNET;
using System;
using System.Drawing;
using System.Windows.Forms;

namespace ZephyrTools.CommandRunner
{
    class CustomScintilla : Scintilla
    {
        public CustomScintilla()
        {
            this.Dock = DockStyle.Fill;
            this.StyleResetDefault();
            this.Styles[Style.Default].Font = "Consolas";
            this.Styles[Style.Default].Size = 12;
            this.StyleClearAll();
            this.Styles[Style.Cpp.Default].ForeColor = Color.Silver;
            this.Styles[Style.Cpp.Comment].ForeColor = Color.FromArgb(0, 128, 0);
            this.Styles[Style.Cpp.CommentLine].ForeColor = Color.FromArgb(0, 128, 0);
            this.Styles[Style.Cpp.CommentLineDoc].ForeColor = Color.FromArgb(128, 128, 128);
            this.Styles[Style.Cpp.Number].ForeColor = Color.Olive;
            this.Styles[Style.Cpp.Word].ForeColor = Color.Blue;
            this.Styles[Style.Cpp.Word2].ForeColor = Color.Blue;
            this.Styles[Style.Cpp.String].ForeColor = Color.FromArgb(163, 21, 21);
            this.Styles[Style.Cpp.Character].ForeColor = Color.FromArgb(163, 21, 21);
            this.Styles[Style.Cpp.Verbatim].ForeColor = Color.FromArgb(163, 21, 21);
            this.Styles[Style.Cpp.StringEol].BackColor = Color.Pink;
            this.Styles[Style.Cpp.Operator].ForeColor = Color.Purple;
            this.Styles[Style.Cpp.Preprocessor].ForeColor = Color.Maroon;
            this.Margins[0].Width = 40;
            this.Margins[0].Type = MarginType.Number;
            this.Lexer = Lexer.Cpp;
            this.CaretLineVisible = true;
            this.CaretLineBackColor = Color.AliceBlue;
            this.SetKeywords(0, "abstract as base break case catch checked continue default delegate do else event explicit extern false finally fixed for foreach goto if implicit in interface internal is lock namespace new null object operator out override params private protected public readonly ref return sealed sizeof stackalloc switch this throw true try typeof unchecked unsafe using virtual while var where");
            this.SetKeywords(1, "bool byte char class const decimal double enum float int long sbyte short static string struct uint ulong ushort void");
            this.SaveCommand += () => { };
            this.CloseCommand += () => { };
            this.RunCommand += () => { };
        }

        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            if (keyData.HasFlag(Keys.Control) && keyData.HasFlag(Keys.S))
            {
                this.SaveCommand();
                return true;
            }
            else if (keyData.HasFlag(Keys.Control) && keyData.HasFlag(Keys.W))
            {
                this.CloseCommand();
                return true;
            }
            else if (keyData.HasFlag(Keys.Control) && keyData.HasFlag(Keys.O))
            {
                this.OpenCommand();
                return true;
            }
            else if (keyData.HasFlag(Keys.Control) && keyData.HasFlag(Keys.F5))
            {
                this.RunCommand();
                return true;
            }
            else
            {
                return base.ProcessCmdKey(ref msg, keyData);
            }
        }

        public event Action SaveCommand;

        public event Action CloseCommand;

        public event Action OpenCommand;

        public event Action RunCommand;

        private void InitializeComponent()
        {
            this.SuspendLayout();
            // 
            // CustomScintilla
            // 
            this.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.ResumeLayout(false);

        }
    }
}
