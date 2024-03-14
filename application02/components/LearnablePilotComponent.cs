using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;
using ZephyrSharp.GameSystem;
using static GameScript;

class LearnablePilotComponent : AbstractPilotComponent
{
    public LearnablePilotComponent()
    {
        const string address = "127.0.0.1";
        const int port = 12345;
        IPAddress host = IPAddress.Parse(address);
        this.server = new TcpListener(host, port);
    }

    protected override void OnAttach()
    {
        base.OnAttach();

        this.server.Start();
    }

    protected override void OnDetach()
    {
        base.OnDetach();

        this.server.Stop();
        this.client?.Dispose();
        this.client = null;
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

        if (this.client == null || !this.client.Connected)
        {
            this.client = this.server.AcceptTcpClient();
            this.stream = this.client.GetStream();
            try
            {
                this.SendObservationData();
                this.ReceiveResponseOkData();
            }
            catch (IOException) { }
            catch (JsonReaderException) { }
        }

        {
            TimeSpan timeout = new TimeSpan(hours: 0, minutes: 0, seconds: 30);
            const int FPS = 60;

            bool flag = false;
            flag |= (Entity.Find("system").Get<SystemComponent>().FrameCount > timeout.TotalSeconds * FPS);
            flag |= (this.Owner.Get<AircraftComponent>().Armor == 0.0f);
            //flag |= Entity.Find(e => (e.Name != null) && (e.Name.StartsWith("enemy")) && (e.Has<AircraftComponent>()) && (0 < e.Get<AircraftComponent>().Armor)) == null;

            var obs = this.Owner.Get<EnvironmentObservationComponent>();
            obs.EpisodeDone = flag;
            Program.ResetSceneSignal = flag;
        }

        try
        {
            this.SendObservationData();
            this.ReceiveActionData();
        }
        catch (IOException) { }
        catch (JsonReaderException) { }
    }

    private void SendObservationData()
    {
        var obs = this.Owner.Get<EnvironmentObservationComponent>();
        {
            string text = obs.ToJsonString();
            byte[] buffer = Encoding.UTF8.GetBytes(text);
            this.stream.Write(buffer, 0, buffer.Length);
        }
    }

    private void ReceiveResponseOkData()
    {
        byte[] buffer = new byte[8192];
        int length = this.stream.Read(buffer, 0, buffer.Length);
        Array.Resize(ref buffer, length);

        string text = Encoding.UTF8.GetString(buffer);
        JObject input = JObject.Parse(text);
        if ((string)input["response"] != "ok")
            throw new IOException();
    }

    private void ReceiveActionData()
    {
        byte[] buffer = new byte[8192];
        int length = this.stream.Read(buffer, 0, buffer.Length);
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

    private TcpListener server;
    private TcpClient client;
    private NetworkStream stream;
}
