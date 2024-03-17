using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Diagnostics;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;
using ZephyrSharp.GameSystem;
using static GameScript;

class LearnablePilotComponent : AbstractPilotComponent
{
    static LearnablePilotComponent()
    {
        var process = Process.GetCurrentProcess();
        var address = "127.0.0.1";
        var port = 12345 + process.Id;
        var host = IPAddress.Parse(address);

        server = new TcpListener(host, port);
        server.Start();
        client = server.AcceptTcpClient();
        stream = client.GetStream();
    }

    protected override void OnAttach()
    {
        base.OnAttach();

        this.SendObservationData();
        this.ReceiveResponseOkData();
    }

    protected override void ReceiveMessage(object message, object argument)
    {
        base.ReceiveMessage(message, argument);

        switch (message as string)
        {
            case KillMessage:
                this.Update();
                break;
        }
    }

    protected override void Update()
    {
        base.Update();

        {
            TimeSpan timeout = new TimeSpan(hours: 0, minutes: 0, seconds: 30);
            const int frameRate = 60;

            bool flag = false;
            flag |= (Entity.Find("system").Get<SystemComponent>().FrameCount > timeout.TotalSeconds * frameRate);
            flag |= (this.Owner.Get<AircraftComponent>().Armor == 0.0f);
            //flag |= Entity.Find(e => (e.Name != null) && (e.Name.StartsWith("enemy")) && (e.Has<AircraftComponent>()) && (0 < e.Get<AircraftComponent>().Armor)) == null;

            var obs = this.Owner.Get<EnvironmentObservationComponent>();
            obs.EpisodeDone = flag;
            Program.ResetSceneSignal = flag;

            this.SendObservationData();
            this.ReceiveActionData();
        }
    }

    private void SendObservationData()
    {
        var obs = this.Owner.Get<EnvironmentObservationComponent>();
        {
            string text = obs.ToJsonString();
            byte[] buffer = Encoding.UTF8.GetBytes(text);
            stream.Write(buffer, 0, buffer.Length);
        }
    }

    private void ReceiveResponseOkData()
    {
        byte[] buffer = new byte[8192];
        int length = stream.Read(buffer, 0, buffer.Length);
        Array.Resize(ref buffer, length);

        string text = Encoding.UTF8.GetString(buffer);
        JObject input = JObject.Parse(text);
        if ((string)input["response"] != "ok")
            throw new IOException();
    }

    private void ReceiveActionData()
    {
        byte[] buffer = new byte[8192];
        int length = stream.Read(buffer, 0, buffer.Length);
        Array.Resize(ref buffer, length);

        string text = Encoding.UTF8.GetString(buffer);
        JObject input = JObject.Parse(text);

        var aircraft = this.Owner.Get<AircraftComponent>();
        aircraft.RollInput = (float)input["roll_input"];
        aircraft.PitchInput = (float)input["pitch_input"];
        aircraft.YawInput = (float)input["yaw_input"];
        aircraft.ThrottleInput = (float)input["throttle_input"];

        var display = Entity.Find("debugger").Get<DebugInformationDisplayComponent>();
        display.DebugMessages["action"] = input.ToString(Formatting.Indented);
    }

    private static TcpListener server;
    private static TcpClient client;
    private static NetworkStream stream;
}
