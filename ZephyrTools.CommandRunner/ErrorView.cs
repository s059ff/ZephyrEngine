using System.CodeDom.Compiler;
using System.Windows.Forms;

namespace ZephyrTools.CommandRunner
{
    public partial class ErrorView : UserControl
    {
        public ErrorView()
        {
            InitializeComponent();
        }

        public void Clear()
        {
            this.listView1.Items.Clear();
        }

        public void Add(CompilerError error)
        {
            string number = error.ErrorNumber;
            string line = error.Line.ToString();
            string column = error.Column.ToString();
            string desc = error.ErrorText;
            this.Add(number, line, column, desc);
        }

        private void Add(string number, string line, string column, string desc)
        {
            this.listView1.Items.Add(new ErrorListViewItem(number, line, column, desc));
        }

        private void listView1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            var senderList = (ListView)sender;
            var mousePos = senderList.PointToClient(Control.MousePosition);
            var hitTest = senderList.HitTest(mousePos);
            var item = hitTest.Item as ErrorListViewItem;
            if (item != null)
            {
                item.Selected = true;
                //this.ParentForm.OpenFile(item.FileName);
            }
        }

        new CommandRunner ParentForm { get { return base.ParentForm as CommandRunner; } }
    }
}
