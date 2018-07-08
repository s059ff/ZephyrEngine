using System;
using System.Linq;
using System.Collections.Generic;
using XepherSharp.Graphics;
using XepherSharp.Input;
using static Script;

class TitleSceneComponent : CustomEntityComponent
{
    Texture2D EffectTexture = new Texture2D();
    Texture2D SparkTexture = new Texture2D();
    bool PressedAnyKey = false;
    int FrameFromPressedAnykey = 0;

    Node MenuNodes = new Node("root", null, null, 0);
    Node CurrentNode;

    float DisplayNodeOffsetX = 0;

    class Node : Dictionary<string, Node>
    {
        public readonly string Text;
        public readonly Node Parent;
        public Node Before;
        public Node Next;
        public readonly int Depth;

        public Node(string text, Node parent, Node before, int depth)
        {
            this.Text = text;
            this.Parent = parent;
            this.Before = before;
            if (this.Before != null)
                this.Before.Next = this;
            this.Depth = depth;
        }

        public new Node this[string text]
        {
            get
            {
                if (!ContainsKey(text))
                {
                    Add(text, new Node(text, this, Values.Count > 0 ? Values.Last() : null, Depth + 1));
                }
                return base[text];
            }
        }
    }

    public TitleSceneComponent()
    {
        //tex_meconopsis.Create("res/picture/meconopsis.png", Accessibility.None);
        //tex_marupeke.Create("res/picture/marupeke.png", Accessibility.None);
        //tex_maoudamashii.Create("./picture/maoudamashii.png", Accessibility.None);
        EffectTexture.Create("res/picture/bg08.jpg", Accessibility.None);
        SparkTexture.Create("res/picture/spark.png", Accessibility.None);
        //snd_electron.Create("res/sound/denki002.wav");
        //snd_electron.Play();
        //snd_decide.Create("res/sound/SE_attack.wav");
        object dummy;
        dummy = MenuNodes["Start"];
        dummy = MenuNodes["Option"];
        dummy = MenuNodes["Quit"];
        dummy = MenuNodes["Option"]["Screen size"];
        dummy = MenuNodes["Option"]["Difficulty"];
        dummy = MenuNodes["Option"]["Difficulty"]["Easy"];
        dummy = MenuNodes["Option"]["Difficulty"]["Normal"];
        dummy = MenuNodes["Option"]["Difficulty"]["Hard"];
        CurrentNode = MenuNodes["Option"];
    }

    protected override void ReceiveMessage(object message, object argument)
    {
        base.ReceiveMessage(message, argument);

        switch (message as string)
        {
            case UpdateMessage:
                this.Update();
                break;

            case DrawMessage:
                this.Draw();
                break;

            default:
                break;
        }
    }

    private void Update()
    {
        if (PressedAnyKey)
            FrameFromPressedAnykey++;

        foreach (KeyCode key in Enum.GetValues(typeof(KeyCode)))
        {
            if (pressed(key))
            {
                PressedAnyKey = true;
            }
        }

        if (nowpressed(KeyCode.Right))
        {
            if (CurrentNode.Count > 0)
                CurrentNode = CurrentNode.First().Value;
        }
        if (nowpressed(KeyCode.Left))
        {
            if (CurrentNode.Parent != null)
                CurrentNode = CurrentNode.Parent;
        }
        if (nowpressed(KeyCode.Up))
        {
            if (CurrentNode.Before != null)
                CurrentNode = CurrentNode.Before;
        }
        if (nowpressed(KeyCode.Down))
        {
            if (CurrentNode.Next != null)
                CurrentNode = CurrentNode.Next;
        }
    }

    private void Draw()
    {
        Color White = new Color(ColorCode.White);

        Action<Node> drawMenu = null;
        drawMenu = (Node node) =>
        {
            translate(1, 0);
            foreach (var _node in node)
            {
                color(1, 1, 1, CurrentNode == _node.Value ? 1.0f : 0.5f);
                if (CurrentNode == _node.Value)
                {
                    color(1, 1, 1, 1);

                    pushMatrix();
                    {
                        translate(-1, -0.5f);
                        rotate(deg2rad(-45));
                        translate(cos(frame / 10.0f) * 0.25f, sin(frame / 10.0f) * 0.5f);
                        scale(3);
                        draw(SparkTexture);
                    }
                    popMatrix();

                    pushMatrix();
                    {
                        translate(-1, -0.5f);
                        rotate(deg2rad(-45));
                        translate(-cos(frame / 10.0f) * 0.25f, -sin(frame / 10.0f) * 0.5f);
                        scale(3);
                        draw(SparkTexture);
                    }
                    popMatrix();
                }
                write(_node.Value.Text);
                translate(0, -1);

                drawMenu(_node.Value);
            }
            translate(-1, 0);
        };

        color(White);
        font(Ricty);

        pushMatrix();
        {
            float alpha = 0;
            alpha = frame < 120 ? cos(frame / 120.0f * PI) : 0;
            if (alpha > 0)
            {
                blend(AlphaBlend);
                color(0, 0, 0, alpha);
                identity();
                scale(2 * DisplayAspect, 2);
                rectangle();
            }

            blend(AlphaBlend);
            color(1, 1, 1, 1);
            identity();
            scale(0.15f);
            translate(0, 1, 0);
            write("AirSurvival 3", TextAlignment.Center, TextAlignment.Center);

            if (frame > 120)
            {
                alpha = frame < 180 ? sin((frame - 120) / 60.0f * PIOver2) : 1;
                if (alpha > 0)
                {
                }
            }

            //alpha = FrameFromPressedAnykey / 30.0f;
            //if (alpha > 0)
            //{
            //    blend(Subtraction);
            //    color(alpha, alpha, alpha);
            //    identity();
            //    scale(2 * DisplayAspect, 2);
            //    draw(EffectTexture);
            //}

            //if (FrameFromPressedAnykey == 120)
            //    pause();
        }
        popMatrix();

        pushMatrix();
        {
            blend(AlphaBlend);
            color(White);
            identity();
            translate(-0.5f, 0, 0);
            scale(0.08f);
            DisplayNodeOffsetX = close(DisplayNodeOffsetX, -(CurrentNode.Depth - 1), 0.1f);
            translate(DisplayNodeOffsetX, 0);
            drawMenu(MenuNodes);
        }
        popMatrix();
    }
}
