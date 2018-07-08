#include "common.csh"

Matrix4x3 _viewing { get { return Entity.Find("camera2d").Get<CameraComponent>().ViewingMatrix; } }
Matrix4x4 _projection { get { return Entity.Find("projector2d").Get<ProjectorComponent>().ProjectionMatrix; } }

RasterizerState _rasterizerState = new RasterizerState();
DepthStencilState _depthStencilState = new DepthStencilState();

partial void initialize()
{
    Graphics2D.Instance.Create();
    color(WHITE);

    _rasterizerState.Create(CullMode.None, FillMode.Solid);
    _depthStencilState.Create(false, false, false);
}

void draw(Texture tex)
{
    GraphicsDevice.Instance.SetRasterizerState(_rasterizerState);
    GraphicsDevice.Instance.SetDepthStencilState(_depthStencilState);
    Graphics2D.Instance.SetTexture(tex);
    Graphics2D.Instance.SetMatrix(_world * _viewing * _projection);
    Graphics2D.Instance.DrawTexture();
}

void draw(Texture tex, float u0, float v0, float u1, float v1)
{
    GraphicsDevice.Instance.SetRasterizerState(_rasterizerState);
    GraphicsDevice.Instance.SetDepthStencilState(_depthStencilState);
    Graphics2D.Instance.SetTexture(tex);
    Graphics2D.Instance.SetMatrix(_world * _viewing * _projection);
    Graphics2D.Instance.SetVertexPositions(-0.5f, 0.5f, 0.5f, -0.5f);
    Graphics2D.Instance.SetTextureCoords(u0, v0, u1, v1);
    Graphics2D.Instance.DrawTextureWithDynamical();
}

void drawThreshold(Texture tex, float u0, float v0, float u1, float v1)
{
    GraphicsDevice.Instance.SetRasterizerState(_rasterizerState);
    GraphicsDevice.Instance.SetDepthStencilState(_depthStencilState);
    Graphics2D.Instance.SetTexture(tex);
    Graphics2D.Instance.SetMatrix(_world * _viewing * _projection);
    Graphics2D.Instance.SetColorThreshold(0, 0, 0, 0, 1, 1, 1, 1);
    Graphics2D.Instance.SetTextureThreshold(u0, v0, u1, v1);
    Graphics2D.Instance.DrawTextureWithThreshold();
}

void rectangle()
{
    GraphicsDevice.Instance.SetRasterizerState(_rasterizerState);
    GraphicsDevice.Instance.SetDepthStencilState(_depthStencilState);
    Graphics2D.Instance.SetMatrix(_world * _viewing * _projection);
    Graphics2D.Instance.DrawRectangle();
}

void font(Font _font)
{
    Graphics2D.Instance.SetFont(_font);
}

void color(float rgb)
{
    Graphics2D.Instance.SetColor(new Color(rgb, rgb, rgb));
}

void color(float r, float g, float b)
{
    Graphics2D.Instance.SetColor(new Color(r, g, b));
}

void color(float r, float g, float b, float a)
{
    Graphics2D.Instance.SetColor(new Color(r, g, b, a));
}

void color(Color color)
{
    Graphics2D.Instance.SetColor(color);
}

void color(ColorCode code)
{
    Graphics2D.Instance.SetColor(new Color(code));
}

void write(string text, TextAlignment horizontal = LEFT, TextAlignment vertical = TOP)
{
    GraphicsDevice.Instance.SetRasterizerState(_rasterizerState);
    GraphicsDevice.Instance.SetDepthStencilState(_depthStencilState);
    Graphics2D.Instance.SetMatrix(_world * _viewing * _projection);
    Graphics2D.Instance.DrawText(text, horizontal, vertical);
}

void blend(BlendState state)
{
    GraphicsDevice.Instance.SetBlendState(state);
}

void addressing(SamplerState state)
{
    Graphics2D.Instance.SetAddreessMode(state);
}