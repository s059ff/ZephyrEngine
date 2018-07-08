/**
 * コマンドランナーテスト
 */

using System;
using ZephyrTools.CommandRunner;

class Program
{
    static CommandRunner runner;

    [STAThread]
    static void Main(string[] args)
    {
        runner = CommandRunner.Execute();
    }
}
