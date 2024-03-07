using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Graphics;
using ZephyrSharp.Linalg;
using static GameScript;

public class DebugMarkerComponent : CustomEntityComponent
{
    static VertexShader VertexShader = new VertexShader();
    static PixelShader PixelShader = new PixelShader();
    static VertexLayout VertexLayout = new VertexLayout();
    static GraphicsModel GraphicsModel = new GraphicsModel();

    static DebugMarkerComponent()
    {
        VertexShader.CreateFromFile("res/shader/DebugMarkerVertexShader.hlsl");
        PixelShader.CreateFromFile("res/shader/DebugMarkerPixelShader.hlsl");

        VertexLayout.Create(new VertexElement[]
        {
            new VertexElement("POSITION", 0, Format.Float3, 0, 0, VertexElement.Classification.VertexData, 0),
        }, VertexShader);

        GraphicsModel.CreateSphere(16, 16);
    }

    protected override void ReceiveMessage(object message, object argument)
    {
        base.ReceiveMessage(message, argument);

        switch (message as string)
        {
            case RenderMessage:
                {
                    Matrix4x4 world = new Matrix4x4(this.Owner.Get<TransformComponent>().Matrix);
                    Matrix4x4 viewing = new Matrix4x4(Entity.Find("camera").Get<CameraComponent>().ViewingMatrix);
                    Matrix4x4 projection = Entity.Find("projector").Get<ProjectorComponent>().ProjectionMatrix;

                    GraphicsDeviceContext device = GraphicsDeviceContext.Instance;
                    device.SetBlendState(NoBlend);
                    device.SetRasterizerState(CullingOn);
                    device.SetDepthStencilState(ZTestOn);
                    device.SetVertexLayout(VertexLayout);
                    device.SetPrimitiveTopology(GraphicsModel.Topology);
                    device.SetVertexShader(VertexShader);
                    device.SetPixelShader(PixelShader);

                    device.SetVertexBuffer(GraphicsModel.VertexPositions, 0);
                    device.SetIndexBuffer(GraphicsModel.VertexIndices);

                    PixelShader.SetSamplerState(Wrap, 0);
                    VertexShader.SetConstantBuffer(world * viewing * projection, 0);

                    device.DrawIndexed(GraphicsModel.VertexIndices.Count);
                }
                break;

            default:
                break;
        }
    }
}
