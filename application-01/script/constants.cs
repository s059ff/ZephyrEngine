#include "common.csh"

BlendState NoBlend = new BlendState();
BlendState Addition = new BlendState();
BlendState HalfAddition = new BlendState();
BlendState Subtraction = new BlendState();
BlendState Multiplication = new BlendState();
BlendState Reverse = new BlendState();
BlendState AlphaBlend = new BlendState();

SamplerState Wrap = new SamplerState();
SamplerState Mirror = new SamplerState();

RasterizerState CullingOn = new RasterizerState();
RasterizerState CullingOff = new RasterizerState();

DepthStencilState ZTestOn = new DepthStencilState();
DepthStencilState ZTestOnWriteOff = new DepthStencilState();
DepthStencilState ZTestOff = new DepthStencilState();

const string UpdateMessage = "update";
const string RenderDepthMapMessage = "render depth map";
const string RenderMessage = "render";
const string TranslucentRenderMessage = "translucent render";
const string DrawMessage = "draw";

partial void initialize()
{
    NoBlend.Create(BlendOperation.None);
    Addition.Create(BlendOperation.Add, BlendFactor.One, BlendFactor.One);
    HalfAddition.Create(BlendOperation.Add, BlendFactor.One, BlendFactor.InvSrcAlpha);
    Subtraction.Create(BlendOperation.RevSubtract, BlendFactor.One, BlendFactor.One);
    Multiplication.Create(BlendOperation.Add, BlendFactor.Zero, BlendFactor.SrcColor);
    Reverse.Create(BlendOperation.Add, BlendFactor.InvDestColor, BlendFactor.InvSrcColor);
    AlphaBlend.Create(BlendOperation.Add, BlendFactor.SrcAlpha, BlendFactor.InvSrcAlpha);

    Wrap.Create(TextureAddressMode.Wrap, TextureAddressMode.Wrap, TextureAddressMode.Wrap);
    Mirror.Create(TextureAddressMode.Mirror, TextureAddressMode.Mirror, TextureAddressMode.Mirror);

    CullingOn.Create(CullMode.Back, FillMode.Solid);
    CullingOff.Create(CullMode.None, FillMode.Solid);

    ZTestOn.Create(true, false, true);
    ZTestOnWriteOff.Create(true, false, false);
    ZTestOff.Create(false, false, false);
}

partial void finalize()
{
    NoBlend.Dispose();
    Addition.Dispose();
    HalfAddition.Dispose();
    Subtraction.Dispose();
    Multiplication.Dispose();
    Reverse.Dispose();
    AlphaBlend.Dispose();

    Wrap.Dispose();
    Mirror.Dispose();

    CullingOn.Dispose();
    CullingOff.Dispose();

    ZTestOn.Dispose();
    ZTestOnWriteOff.Dispose();
    ZTestOff.Dispose();
}