cbuffer C0 : register(b0) { row_major matrix g_world; };
cbuffer C1 : register(b1) { row_major matrix g_local; };
cbuffer C2 : register(b2) { float4 g_camera_pos; };
cbuffer C3 : register(b3) { float4 _g_light_dir; };

SamplerState g_sampler : register(s0);

Texture2D g_texture : register(t0);
texture2D g_normalmap : register(t1);
TextureCube g_environment_texture : register(t2);

#if 0
struct PSInput
{
    float4 pos : SV_POSITION;
    float3 normal : NORMAL;
    float2 tex : TEXCOORD;
    float distance : DISTANCE;
};

float4 main(PSInput input) : SV_TARGET
{
    float3 ld = -light_direction.xyz;
    float3 n = normalize(mul(float4(input.normal, 0), w).xyz);
    float k = clamp(dot(ld, n), 0.0f, 1.0f);

    float3 color = g_texture.Sample(g_sampler, input.tex).rgb;

    float d = min(input.distance / 3072.0f, 1.0f);
    color = k * (1 - d) * color + d * (float3(0.5f, 0.7f, 0.8f) - 0.2f);

    return float4(color, 1);
}
#endif

inline float square(float x) { return x * x; }

void main(
    float4 _position : SV_POSITION,
    float3 normal : NORMAL,
    float2 texcoord : TEXCOORD,
    float3 tangent : TANGENT,
    float distance : DISTANCE,
    out float4 out_color : SV_TARGET)
{
    static const float g_light_color = 1.0f;
    static const float g_ambient = 0.25f;
    static const float g_diffuse = 0.5f;
    static const float g_specular = 0.25f;

    float3 g_light_dir = _g_light_dir.xyz;

    row_major float3x3 local2vertex;
    {
        float3 N = normal;
        float3 T = normalize(tangent);
        float3 B = normalize(cross(N, T));
        local2vertex = float3x3(N, T, B);
    }

    float3 position = _position.xyz;
    position /= _position.w;
    //float3 L = normalize(mul(mul(float4(g_light_dir, 0.0f), g_local).xyz, local2vertex));
    //float3 N = normalize(2.0f * g_normalmap.Sample(g_sampler, texcoord).xyz - 1.0f);
    //float3 V = normalize(mul(mul(g_camera_pos, g_local).xyz - position, local2vertex)).xyz;
    //float3 H = normalize(L + V);

    float3 L = mul(-float4(g_light_dir, 0), g_local).xyz;
    float3 N = normal;
    float3 V = normalize(mul(g_camera_pos, g_local).xyz - position);
    float3 H = normalize(L + V);

    float diffuse;
    {
        float id = g_light_color;
        float kd = g_diffuse;
        diffuse = id * kd * dot(normal, -g_light_dir);
    }

    float ambient;
    {
        float ia = g_light_color;
        float ka = g_ambient;
        ambient = ia * ka;
    }

    float specular;
    {
        float NH = dot(N, H);
        float NV = dot(N, V);
        float D;
        {
            const float m = 0.35f;
            const float m2 = m * m;
            float NH2 = NH * NH;
            float NH4 = NH2 * NH2;
            D = 1.0f / (4 * m2 * NH4) * exp(-1.0f / m2 * (1 - NH2) / NH2);
        }
        float G;
        {
            float VH = dot(V, H);
            float NL = dot(N, L);
            float Ga = 2.0f * NH * NV / VH;
            float Gb = 2.0f * NH * NL / VH;
            G = min(min(Ga, Gb), 1);
        }
        float F;
        {
            float n = 20.0f;
            float c = dot(L, H);
            float g = sqrt(n * n + c * c - 1);
            float f1 = 0.5f;
            float f2 = square(g - c) / square(g + c);
            float f3 = 1.0f + square(c * (g + c) - 1) / square(c * (g - c) + 1);
            F = f1 * f2 * f3;
        }
        float is = g_light_color;
        float ks = g_specular;
        specular = max(D * G * F / NV, 0) * is * ks;
    }

    float color = min(ambient + diffuse + specular, 1.0f);
    out_color.rgb = color * g_texture.Sample(g_sampler, texcoord).rgb;
    out_color.a = 1.0f;

    {
        float3 N = normalize(mul(float4(normal, 0.0f), g_world).xyz);
        float3 V = normalize(g_camera_pos.xyz - mul(float4(position, 1.0f), g_world).xyz);
        float3 H = normalize(V + N);
        float3 color = g_environment_texture.Sample(g_sampler, H).rgb;
        color.r = pow(color.r, 8);
        color.g = pow(color.g, 8);
        color.b = pow(color.b, 8);
        out_color.rgb = out_color.rgb + 0.1f * color;
    }

    float d = min(distance / 3072.0f, 1.0f);
    out_color.rgb = (1 - d) * out_color.rgb + d * (float3(0.5f, 0.7f, 0.8f) - 0.2f);
    out_color.a = 1;
}
