#include "common.csh"

void assert(bool b)
{
    assert(b, "エラーが発生しました。");
}

void assert(bool b, string comment)
{
    if (!b) 
    { 
        MessageBox.Show(
            comment + Environment.NewLine 
            + "スタックトレース:" + Environment.NewLine 
            + Environment.StackTrace, "エラーが発生しました。", MessageBoxIcon.Error); 
        throw new RuntimeException(comment); 
    }
}

void stacktrace()
{
    MessageBox.Show(
        "スタックトレース:" + Environment.NewLine + Environment.StackTrace, 
        "スタックトレース", MessageBoxIcon.Information); 
}

void pause()
{
    MessageBox.Show("一時停止", "一時停止", MessageBoxIcon.Information);
}

void mesbox()
{
    MessageBox.Show("", "");
}

void mesbox(string contents)
{
    MessageBox.Show(contents, "");
}

void mesbox(string contents, string title)
{
    MessageBox.Show(contents, title);
}

void dump(object obj)
{
    string text = string.Empty;
    {
        var infos = obj.GetType().GetFields();
        foreach (var info in infos)
        {
            text += string.Format("{0} = {1}\n", info.Name, info.GetValue(obj).ToString());
        }
    }
    {
        var infos = obj.GetType().GetProperties();
        foreach (var info in infos)
        {
            text += string.Format("{0} = {1}\n", info.Name, info.GetValue(obj).ToString());
        }
    }
    print(text);
}
