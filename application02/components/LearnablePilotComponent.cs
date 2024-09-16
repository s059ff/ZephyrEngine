using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.Diagnostics;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;
using ZephyrSharp;
using ZephyrSharp.GameSystem;
using static EngineScript;
using static GameScript;

class LearnablePilotComponent : AbstractPilotComponent
{
    static LearnablePilotComponent()
    {
        var process = Process.GetCurrentProcess();
        var address = "127.0.0.1";
        var port = 12345 + process.Id;
        var host = IPAddress.Parse(address);

        listener = new TcpListener(host, port);
        listener.Start();
        client = listener.AcceptTcpClient();
        stream = client.GetStream();
    }

    protected override void ReceiveMessage(object message, object argument)
    {
        base.ReceiveMessage(message, argument);

        switch (message as string)
        {
            case UpdateMessage:
                this.Update();
                break;

            case PostUpdateMessage:
                this.PostUpdate();
                break;

            default:
                break;
        }
    }

    private void Update()
    {
        if (this.initialState)
        {
            this.SendObservationData();
            this.initialState = false;
        }
        this.ReceiveActionData();
    }

    private void PostUpdate()
    {
        this.SendObservationData();
    }

    private void SendMessage(object obj)
    {
        string message = JObject.FromObject(obj).ToString(Formatting.None);
        byte[] payload = Encoding.UTF8.GetBytes(message);
        stream.Write(payload, 0, payload.Length);
        stream.WriteByte(0);
    }

    private JObject ReceiveMessage()
    {
        using (var buffer = new MemoryStream())
        {
            while (true)
            {
                byte[] chunk = new byte[4096];
                int count = stream.Read(chunk, 0, chunk.Length);
                if (count == 0)
                    throw new RuntimeException("socket connection broken");
                buffer.Write(chunk, 0, count);
                if (chunk[count - 1] == 0)
                    break;
            }
            byte[] payload = buffer.ToArray();
            assert(0 < payload.Length);
            assert(payload[payload.Length - 1] == 0);

            string message = Encoding.UTF8.GetString(payload, 0, payload.Length - 1);
            return JObject.Parse(message);
        }
    }

    private void SendObservationData()
    {
        var observer = this.Owner.Get<EnvironmentObserverComponent>();
        var observation = observer.Observe();
        this.SendMessage(observation);

        Program.ResetSceneSignal = (bool)observation["episode_done"];
    }

    private void ReceiveActionData()
    {
        JObject response = this.ReceiveMessage();

        var aircraft = this.Owner.Get<AircraftComponent>();
        aircraft.RollInput = (float)response["roll_input"];
        aircraft.PitchInput = (float)response["pitch_input"];
        aircraft.YawInput = (float)response["yaw_input"];
        aircraft.ThrottleInput = (float)response["throttle_input"];

        var display = Entity.Find("debugger").Get<DebugInformationDisplayComponent>();
        display.DebugMessages["action"] = response.ToString(Formatting.Indented);
    }

    private bool initialState = true;
    private static TcpListener listener;
    private static TcpClient client;
    private static NetworkStream stream;
}
