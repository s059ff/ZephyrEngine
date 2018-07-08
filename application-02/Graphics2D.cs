using System.Collections.Generic;
using ZephyrSharp.Graphics;
using ZephyrSharp.Linalg;

public class Graphics2D
{
    public void Create()
    {
        // Create shaders.
        passes[0].vs.CreateFromFile("res/shader/2DVertexShader.hlsl", "pass0");
        passes[0].ps.CreateFromFile("res/shader/2DPixelShader.hlsl", "pass0");
        passes[1].vs.CreateFromFile("res/shader/2DVertexShader.hlsl", "pass1");
        passes[1].ps.CreateFromFile("res/shader/2DPixelShader.hlsl", "pass1");
        passes[2].vs.CreateFromFile("res/shader/2DVertexShader.hlsl", "pass2");
        passes[2].ps.CreateFromFile("res/shader/2DPixelShader.hlsl", "pass2");

        // Create vertex layout.
        {
            VertexElement e1 = new VertexElement("POSITION", 0, Format.Float3, 0, 0, VertexElement.Classification.VertexData, 0);
            VertexElement e2 = new VertexElement("TEXCOORD", 0, Format.Float2, 1, 0, VertexElement.Classification.VertexData, 0);
            passes[0].layout.Create(new VertexElement[] { e1 }, passes[0].vs);
            passes[1].layout.Create(new VertexElement[] { e1, e2 }, passes[1].vs);
            passes[2].layout = passes[1].layout;
        }

        // Create vertex buffers.
        {
            Vector3[] vb0_src = {
                new Vector3(-0.5f, +0.5f, 0),
                new Vector3(+0.5f, +0.5f, 0),
                new Vector3(-0.5f, -0.5f, 0),
                new Vector3(+0.5f, -0.5f, 0)
            };
            vb0.Create(vb0_src, Accessibility.None);
            vb0_dynamic.Create(vb0_src, Accessibility.DynamicWriteOnly);

            Vector2[] vb1_src = {
                new Vector2(0, 0),
                new Vector2(1, 0),
                new Vector2(0, 1),
                new Vector2(1, 1)
            };
            vb1.Create(vb1_src, Accessibility.None);
            vb1_dynamic.Create(vb1_src, Accessibility.DynamicWriteOnly);
        }
    }

    public void SetMatrix(Matrix4x4 value)
    {
        passes[0].vs.SetConstantBuffer(value, 0);
    }

    public void SetColor(Color value)
    {
        passes[0].ps.SetConstantBuffer(value, 0);
    }

    public void SetColor(ColorCode value)
    {
        passes[0].ps.SetConstantBuffer(new Color(value), 0);
    }

    public void SetTexture(Texture2D value)
    {
        passes[0].ps.SetTexture(value, 0);
    }

    public void SetFont(Font value)
    {
        if (!this.fontTexes.ContainsKey(value))
        {
            var obj = new FontTexture();
            obj.Create(value);
            this.fontTexes.Add(value, obj);
        }
        this.fontTex = this.fontTexes[value];
    }

    public void SetAddreessMode(SamplerState value)
    {
        passes[0].ps.SetSamplerState(value, 0);
        passes[1].ps.SetSamplerState(value, 0);
    }

    public void SetColorThreshold(float r0, float g0, float b0, float a0, float r1, float g1, float b1, float a1)
    {
        var value = new float8();
        value.v1 = r0;
        value.v2 = g0;
        value.v3 = b0;
        value.v4 = a0;
        value.v5 = r1;
        value.v6 = g1;
        value.v7 = b1;
        value.v8 = a1;
        this.passes[0].ps.SetConstantBuffer(value, 1);
    }

    public void SetTextureThreshold(float u0, float v0, float u1, float v1)
    {
        var value = new float4();
        value.v1 = u0;
        value.v2 = v0;
        value.v3 = u1;
        value.v4 = v1;
        this.passes[0].ps.SetConstantBuffer(value, 2);
    }

    public void SetVertexPositions(float x0, float y0, float x1, float y1)
    {
        vb0_dynamic.Lock(Accessibility.DynamicWriteOnly);
        {
            vb0_dynamic.Write(0, new Vector3(x0, y0, 0));
            vb0_dynamic.Write(1, new Vector3(x1, y0, 0));
            vb0_dynamic.Write(2, new Vector3(x0, y1, 0));
            vb0_dynamic.Write(3, new Vector3(x1, y1, 0));
        }
        vb0_dynamic.Unlock();
    }

    public void SetTextureCoords(float u0, float v0, float u1, float v1)
    {
        vb1_dynamic.Lock(Accessibility.DynamicWriteOnly);
        {
            vb1_dynamic.Write(0, new Vector2(u0, v0));
            vb1_dynamic.Write(1, new Vector2(u1, v0));
            vb1_dynamic.Write(2, new Vector2(u0, v1));
            vb1_dynamic.Write(3, new Vector2(u1, v1));
        }
        vb1_dynamic.Unlock();
    }

    public void DrawRectangle()
    {
        DrawPass(0);
    }

    public void DrawRectangleWithDynamical()
    {
        DrawPass(0, true);
    }

    public void DrawTexture()
    {
        DrawPass(1);
    }

    public void DrawTextureWithDynamical()
    {
        DrawPass(1, true);
    }

    public void DrawTextureWithThreshold()
    {
        DrawPass(2, false);
    }

    public void DrawText(string text, TextAlignment horizontal, TextAlignment vertical)
    {
        SetTextureCoords(0, 0, 1, 1);

        string[] textByLine = text.Split('\n');

        float y = 0;

        switch (vertical)
        {
            case TextAlignment.Center:
                y += getParagraphHeight(text) / 2;
                break;
            case TextAlignment.Bottom:
                y += getParagraphHeight(text);
                break;
            default:
                break;
        }
        foreach (var line in textByLine)
        {
            float x = 0;

            switch (horizontal)
            {
                case TextAlignment.Center:
                    x -= getLineWidth(line) / 2;
                    break;
                case TextAlignment.Right:
                    x -= getLineWidth(line);
                    break;
                default:
                    break;
            }

            foreach (var c in line)
            {
                switch (c)
                {
                    case ' ':
                        x += 0.5f;
                        break;

                    case '\t':
                        x += 2.0f;
                        break;

                    default:
                        var tex = this.fontTex.GetTexture(c);
                        if (tex.Stride > 0)
                        {
                            float w = (float)tex.Width / this.fontTex.Size;
                            float h = (float)tex.Height / this.fontTex.Size;
                            this.SetTexture(tex);

                            SetVertexPositions(x, y, x + w, y - h);

                            DrawPass(1, true);

                            x += w;
                        }
                        break;
                }
            }

            y += -1.0f;
        }
    }

    private float getLineWidth(string text)
    {
        float width = 0;

        foreach (var c in text)
        {
            switch (c)
            {
                case ' ':
                    width += 0.5f;
                    break;
                case '\t':
                    width += 2.0f;
                    break;
                default:
                    var tex = this.fontTex.GetTexture(c);
                    width += (tex.Stride > 0) ? (float)tex.Width / this.fontTex.Size : 0;
                    break;
            }
        }

        return width;
    }

    private float getParagraphHeight(string text)
    {
        float height = 1.0f;

        foreach (var c in text)
        {
            if (c == '\n')
                height += 1.0f;
        }

        return height;
    }

    private void DrawPass(int pass, bool dynamic = false)
    {
        var dev = GraphicsDevice.Instance;
        dev.SetVertexBuffer(dynamic ? vb0_dynamic : vb0, 0);
        dev.SetVertexBuffer(dynamic ? vb1_dynamic : vb1, 1);
        dev.SetVertexShader(passes[pass].vs);
        dev.SetPixelShader(passes[pass].ps);
        dev.SetVertexLayout(passes[pass].layout);
        dev.SetPrimitiveTopology(PrimitiveTopology.TriangleStrip);
        dev.Draw(4);
    }

    public static Graphics2D Instance = new Graphics2D();

    private Graphics2D() { }

    class Pass
    {
        public VertexShader vs = new VertexShader();
        public PixelShader ps = new PixelShader();
        public VertexLayout layout = new VertexLayout();
    }

    struct float4
    {
        public float v1, v2, v3, v4;
    }

    struct float8
    {
        public float v1, v2, v3, v4, v5, v6, v7, v8;
    }

    VertexBuffer<Vector3> vb0 = new VertexBuffer<Vector3>();
    VertexBuffer<Vector2> vb1 = new VertexBuffer<Vector2>();

    VertexBuffer<Vector3> vb0_dynamic = new VertexBuffer<Vector3>();
    VertexBuffer<Vector2> vb1_dynamic = new VertexBuffer<Vector2>();

    Pass[] passes = new Pass[3] { new Pass(), new Pass(), new Pass() };

    Dictionary<Font, FontTexture> fontTexes = new Dictionary<Font, FontTexture>();

    FontTexture fontTex;
}
