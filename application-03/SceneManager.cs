using System.Threading;
using ZephyrSharp;
using ZephyrSharp.GameSystem;

public class SceneManager
{
    public void SetNextScene(AbstractScene scene, object argument = null)
    {
        if (this.Running)
            throw new RuntimeException();

        this.Scene = scene;
        this.thread = new Thread(new ParameterizedThreadStart(run));
        this.argument = argument;
    }

    public void NextScene()
    {
        Entity.Clear();
        this.Running = true;
        this.thread.Start(this.argument);
    }

    private void run(object argument)
    {
        Scene.LoadScene(argument);
        this.Running = false;
        this.Scene = null;
        this.thread = null;
        this.argument = null;
    }

    public AbstractScene Scene { get; private set; }

    public bool Running { get; private set; }

    private Thread thread;

    private object argument;
}
