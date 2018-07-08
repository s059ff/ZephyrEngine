#include "common.csh"


Dictionary<string, string> loadSettings(string path)
{
    Dictionary<string, string> settings = new Dictionary<string, string>();

    using (var stream = new StreamReader(path))
    {
        string s = string.Empty;
        while ((s = stream.ReadLine()) != null)
        {
            Regex regex = new Regex(@"(?<name>\w+)\s*=\s*(?<value>.+)");
            Match match = regex.Match(s);
            string name = match.Groups["name"].Value.Trim();
            string value = match.Groups["value"].Value.Trim();
            settings.Add(name, value);
        }
    }
    return settings;
}
