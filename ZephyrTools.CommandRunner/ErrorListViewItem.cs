using System.Windows.Forms;

namespace ZephyrTools.CommandRunner
{
    class ErrorListViewItem : ListViewItem
    {
        public ErrorListViewItem(string number, string line, string column, string desc)
            : base(new string[] { "", number, line, column, desc })
        {
            this.ImageIndex = 0;
            this.Line = int.Parse(line);
            this.Column = int.Parse(column);
        }

        public int Line { get; private set; }

        public int Column { get; private set; }
    }
}
