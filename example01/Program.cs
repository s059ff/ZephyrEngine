using System;
using System.Text;
using System.Net;
using System.Net.Sockets;

class Program
{
    const int Port = 12345;

    static void Main(string[] args)
    {
        IPAddress host = IPAddress.Parse("127.0.0.1");
        IPEndPoint ipe = new IPEndPoint(host, Port);
        TcpListener server = new TcpListener(ipe);
        try
        {
            server.Start();

            using (var client = server.AcceptTcpClient())
            using (var stream = client.GetStream())
            {
                {
                    byte[] buffer = new byte[1024];
                    int length = stream.Read(buffer, 0, buffer.Length);
                    Array.Resize(ref buffer, length);
                    string message = Encoding.UTF8.GetString(buffer);
                    Console.WriteLine($"Received message: '{message}'");
                }
                {
                    string message = DateTime.Now.ToString("MM/dd/yyyy hh:mm:ss.fff tt");
                    byte[] buffer = Encoding.UTF8.GetBytes(message);
                    stream.Write(buffer, 0, buffer.Length);
                    Console.WriteLine($"Sent message: '{message}'");
                }
            }
        }
        finally
        {
            server.Stop();
        }
    }
}
