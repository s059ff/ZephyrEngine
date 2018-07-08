using System;
using System.Collections.Generic;
using System.Drawing;
using System.Reflection;
using System.Windows.Forms;

namespace ZephyrTools.GameSystemMonitor
{
    partial class PropertyView : Form
    {
        object Object;

        List<FieldInfo> FieldsInfo = new List<FieldInfo>();

        List<PropertyInfo> PropertiesInfo = new List<PropertyInfo>();

        bool IsSynchronizing = false;

        public PropertyView(object obj)
        {
            InitializeComponent();
            this.dataGridView1.Font = new Font("Yu Gothic UI", 10);

            Object = obj;

            foreach (var info in Object.GetType().GetFields())
            {
                if (!info.IsStatic)
                {
                    dataGridView1.Rows.Add(info.Name, string.Empty);
                    FieldsInfo.Add(info);
                }
            }
            foreach (var info in Object.GetType().GetProperties())
            {
                if (!info.GetMethod.IsStatic)
                {
                    dataGridView1.Rows.Add(info.Name, string.Empty);
                    PropertiesInfo.Add(info);
                }
            }
        }

        public void SyncView()
        {
            int index = 0;
            IsSynchronizing = true;
            foreach (var info in FieldsInfo)
            {
                dataGridView1.Rows[index++].Cells[1].Value = info.GetValue(Object);
            }
            foreach (var info in PropertiesInfo)
            {
                dataGridView1.Rows[index++].Cells[1].Value = info.GetValue(Object);
            }
            IsSynchronizing = false;
        }

        private void dataGridView1_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            if (!IsSynchronizing)
            {
                int index = e.RowIndex;
                if (0 <= index)
                {
                    bool isField = index < FieldsInfo.Count;
                    if (isField)
                    {
                        int fieldIndex = index;

                        string text = dataGridView1.Rows[index].Cells[1].Value.ToString();
                        var info = FieldsInfo[fieldIndex];
                        var type = info.FieldType;
                        if (type != typeof(string))
                        {
                            var method = type.GetMethod("Parse", new Type[] { typeof(string) });
                            object data = method.Invoke(null, new object[] { text });
                            info.SetValue(Object, data);
                        }
                        else
                        {
                            info.SetValue(Object, text);
                        }
                    }
                    else
                    {
                        int propertyIndex = index - FieldsInfo.Count;

                        string text = dataGridView1.Rows[index].Cells[1].Value.ToString();
                        var info = this.PropertiesInfo[propertyIndex];
                        var type = info.PropertyType;
                        if (type != typeof(string))
                        {
                            var method = type.GetMethod("Parse", new Type[] { typeof(string) });
                            object data = method.Invoke(null, new object[] { text });
                            info.SetValue(Object, data);
                        }
                        else
                        {
                            info.SetValue(Object, text);
                        }
                    }
                }
            }
        }

        private void dataGridView1_CellBeginEdit(object sender, DataGridViewCellCancelEventArgs e)
        {
            int index = e.RowIndex;
            if (0 <= index)
            {
                bool isField = index < FieldsInfo.Count;
                if (isField)
                {
                    int fieldIndex = index;
                    var info = FieldsInfo[fieldIndex];
                    var type = info.FieldType;
                    var isString = (type == typeof(string));
                    var hasParseMethod = (type.GetMethod("Parse", new Type[] { typeof(string) }) != null);
                    if (!isString && !hasParseMethod)
                    {
                        e.Cancel = true;
                        return;
                    }
                }
                else
                {
                    int propertyIndex = index - FieldsInfo.Count;
                    var info = PropertiesInfo[propertyIndex];
                    var type = info.PropertyType;
                    var hasSetMethod = (info.SetMethod != null);
                    var isString = (type == typeof(string));
                    var hasParseMethod = (type.GetMethod("Parse", new Type[] { typeof(string) }) != null);
                    if (!hasSetMethod)
                    {
                        e.Cancel = true;
                        return;
                    }
                    else if (!isString && !hasParseMethod)
                    {
                        e.Cancel = true;
                        return;
                    }
                }
            }
        }

        private void PropertyView_FormClosed(object sender, FormClosedEventArgs e)
        {
            Object = null;
        }
    }
}
