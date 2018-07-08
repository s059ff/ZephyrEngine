namespace ZephyrTools.CommandRunner
{
    partial class ErrorView
    {
        /// <summary> 
        /// 必要なデザイナー変数です。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// 使用中のリソースをすべてクリーンアップします。
        /// </summary>
        /// <param name="disposing">マネージ リソースを破棄する場合は true を指定し、その他の場合は false を指定します。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region コンポーネント デザイナーで生成されたコード

        /// <summary> 
        /// デザイナー サポートに必要なメソッドです。このメソッドの内容を 
        /// コード エディターで変更しないでください。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ErrorView));
            this.listView1 = new System.Windows.Forms.ListView();
            this.ColumnHeader_Icon = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.ColumnHeader_ErrorCode = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.ColumnHeader_Line = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.ColumnHeader_Column = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.ColumnHeader_Description = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.imageList1 = new System.Windows.Forms.ImageList(this.components);
            this.SuspendLayout();
            // 
            // listView1
            // 
            this.listView1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.listView1.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.ColumnHeader_Icon,
            this.ColumnHeader_ErrorCode,
            this.ColumnHeader_Line,
            this.ColumnHeader_Column,
            this.ColumnHeader_Description});
            this.listView1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.listView1.Font = new System.Drawing.Font("Yu Gothic UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.listView1.Location = new System.Drawing.Point(0, 0);
            this.listView1.Name = "listView1";
            this.listView1.Size = new System.Drawing.Size(1002, 218);
            this.listView1.SmallImageList = this.imageList1;
            this.listView1.TabIndex = 1;
            this.listView1.UseCompatibleStateImageBehavior = false;
            this.listView1.View = System.Windows.Forms.View.Details;
            this.listView1.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.listView1_MouseDoubleClick);
            // 
            // ColumnHeader_Icon
            // 
            this.ColumnHeader_Icon.Text = "";
            this.ColumnHeader_Icon.Width = 24;
            // 
            // ColumnHeader_ErrorCode
            // 
            this.ColumnHeader_ErrorCode.Text = "エラーコード";
            this.ColumnHeader_ErrorCode.Width = 71;
            // 
            // ColumnHeader_Line
            // 
            this.ColumnHeader_Line.Text = "行";
            // 
            // ColumnHeader_Column
            // 
            this.ColumnHeader_Column.Text = "列";
            // 
            // ColumnHeader_Description
            // 
            this.ColumnHeader_Description.Text = "説明";
            this.ColumnHeader_Description.Width = 770;
            // 
            // imageList1
            // 
            this.imageList1.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList1.ImageStream")));
            this.imageList1.TransparentColor = System.Drawing.Color.Transparent;
            this.imageList1.Images.SetKeyName(0, "StatusCriticalError_32x.png");
            this.imageList1.Images.SetKeyName(1, "StatusWarning_32x.png");
            // 
            // ErrorView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.Controls.Add(this.listView1);
            this.Name = "ErrorView";
            this.Size = new System.Drawing.Size(1002, 218);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ListView listView1;
        private System.Windows.Forms.ColumnHeader ColumnHeader_ErrorCode;
        private System.Windows.Forms.ColumnHeader ColumnHeader_Line;
        private System.Windows.Forms.ColumnHeader ColumnHeader_Description;
        private System.Windows.Forms.ImageList imageList1;
        private System.Windows.Forms.ColumnHeader ColumnHeader_Icon;
        private System.Windows.Forms.ColumnHeader ColumnHeader_Column;
    }
}
