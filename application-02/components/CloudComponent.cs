﻿using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Graphics;
using ZephyrSharp.Linalg;
using static Script;

public class CloudComponent : CustomEntityComponent
{
    static VertexBuffer<Vector3> VertexPositions = new VertexBuffer<Vector3>();
    static VertexBuffer<Vector2> VertexTextureCoords = new VertexBuffer<Vector2>();
    static VertexLayout VertexLayout = new VertexLayout();
    static VertexShader VertexShader = new VertexShader();
    static PixelShader PixelShader = new PixelShader();
    static Texture2D Texture = new Texture2D();

    class Instance
    {
        public Vector3 Position;
        public float Scale;
    }

    InstanceBuffer<Matrix4x4> InstanceWVPs = new InstanceBuffer<Matrix4x4>();
    Instance[] Instances;

    static CloudComponent()
    {
        VertexPositions.Create(new Vector3[]
        {
            new Vector3(-0.5f, +0.5f, 0),
            new Vector3(+0.5f, +0.5f, 0),
            new Vector3(-0.5f, -0.5f, 0),
            new Vector3(+0.5f, -0.5f, 0),
        }, Accessibility.None);

        VertexTextureCoords.Create(new Vector2[]
        {
            new Vector2(0, 0),
            new Vector2(1, 0),
            new Vector2(0, 1),
            new Vector2(1, 1),
        }, Accessibility.None);

        VertexShader.CreateFromFile("res/shader/CloudVertexShader.hlsl");
        PixelShader.CreateFromFile("res/shader/CloudPixelShader.hlsl");

        VertexLayout.Create(new VertexElement[]
        {
            new VertexElement("POSITION", 0, Format.Float3, 0, 0, VertexElement.Classification.VertexData, 0),
            new VertexElement("TEXCOORD", 0, Format.Float2, 1, 0, VertexElement.Classification.VertexData, 0),
            new VertexElement("WVP", 0, Format.Float4, 2, sizeof(float) * 0, VertexElement.Classification.InstanceData, 1),
            new VertexElement("WVP", 1, Format.Float4, 2, sizeof(float) * 4, VertexElement.Classification.InstanceData, 1),
            new VertexElement("WVP", 2, Format.Float4, 2, sizeof(float) * 8, VertexElement.Classification.InstanceData, 1),
            new VertexElement("WVP", 3, Format.Float4, 2, sizeof(float) * 12, VertexElement.Classification.InstanceData, 1),
        }, VertexShader);

        Texture.Create("res/texture/cloud.dds", Accessibility.None);
    }

    public CloudComponent(Vector3[] positions)
    {
        Instances = new Instance[positions.Length];
        for (int i = 0; i < Instances.Length; i++)
        {
            Instances[i] = new Instance()
            {
                Position = positions[i],
                Scale = 250.0f,
            };
        }
        InstanceWVPs.Create(Instances.Length, Accessibility.DynamicWriteOnly);
    }

    protected override void OnDestroy()
    {
        base.OnDestroy();

        InstanceWVPs.Dispose();
    }

    protected override void ReceiveMessage(object message, object argument)
    {
        base.ReceiveMessage(message, argument);

        switch (message as string)
        {
            case TranslucentRenderMessage:
                this.TransparentRender();
                break;

            default:
                break;
        }
    }

    void TransparentRender()
    {
        GraphicsDevice device = GraphicsDevice.Instance;
        device.SetBlendState(AlphaBlend);
        device.SetRasterizerState(CullingOff);
        device.SetDepthStencilState(ZTestOnWriteOff);
        device.SetVertexLayout(VertexLayout);
        device.SetPrimitiveTopology(PrimitiveTopology.TriangleStrip);
        device.SetVertexShader(VertexShader);
        device.SetPixelShader(PixelShader);

        device.SetVertexBuffer(VertexPositions, 0);
        device.SetVertexBuffer(VertexTextureCoords, 1);

        PixelShader.SetSamplerState(Wrap, 0);
        PixelShader.SetTexture(Texture, 0);

        InstanceWVPs.Lock(Accessibility.DynamicWriteOnly);

        var eye = Entity.Find("camera").Get<TransformComponent>().Position;

        for (int i = 0; i < Instances.Length; i++)
        {
            var instance = Instances[i];
            Vector3 position = instance.Position;
            float scale = instance.Scale;

            var world = new Matrix4x3().Identity();
            world.Translate(position * ViewingMatrix);
            world.Scale(scale);

            InstanceWVPs.Write(i, world * ProjectionMatrix);
        }

        InstanceWVPs.Unlock();

        device.SetInstanceBuffer(InstanceWVPs, 2);

        device.DrawInstanced(4, Instances.Length);
    }
}
