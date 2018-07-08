#include "common.csh"

// 数学定数
const float PI = 3.14159265359f;
const float PI2 = 3.14159265359f * 2.0f;
const float PIOver2 = 3.14159265359f / 2.0f;
const float PIOver4 = 3.14159265359f / 4.0f;
const float Napier = 2.7182818284590452353602874713526624977572470936999595749669F;

// 重力加速度[m / frame^2]
const float Gravity = 9.80665f / 60 / 60;

// 数学関数 (float)
float sin(float x) { return (float)Math.Sin(x); }
float cos(float x) { return (float)Math.Cos(x); }
float tan(float x) { return (float)Math.Tan(x); }
float asin(float x) { return (float)Math.Asin(x); }
float acos(float x) { return (float)Math.Acos(x); }
float atan(float x) { return (float)Math.Atan(x); }
float atan2(float y, float x) { return (float)Math.Atan2(y, x); }
float abs(float x) { return (float)Math.Abs(x); }
float ceil(float x) { return (float)Math.Ceiling(x); }
float floor(float x) { return (float)Math.Floor(x); }
float round(float x) { return (float)Math.Round(x); }
int sign(float x) { return Math.Sign(x); }
float sqrt(float x) { return (float)Math.Sqrt(x); }
float log(float x) { return (float)Math.Log(x); }
float exp(float x) { return (float)Math.Exp(x); }
float pow(float x, float y) { return (float)Math.Pow(x, y); }
float square(float x) { return x * x; }

// 比較
int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

float max(float a, float b) { return a > b ? a : b; }
float min(float a, float b) { return a < b ? a : b; }

// 角度変換
float deg2rad(float deg) { return deg / 180.0f * (float)PI; }
float rad2deg(float rad) { return rad / (float)PI * 180.0f; }

// 乱数
int uniform(int min, int max) { return new Random().Next(min, max + 1); }
float uniform(float min = 0, float max = 1) { return _engine.Random(new UniformDistribution(min, max)); }
float normal(float mean = 0, float variance = 1) { return _engine.Random(new NormalDistribution(mean, variance)); }
float random(float[] probs)
{
    var dist = new DiscreteDistribution(probs);
    int x = _engine.Random(dist);
    return (float)x;
}
float[] randoms(float[] probs, int count)
{
    int W = probs.Length;
    var dist = new DiscreteDistribution(probs);
    float[] values = new float[count];
    for (int i = 0; i < count; i++)
    {
        int x = _engine.Random(dist);
        values[i] = x / (float)W;
    }
    return values;
}
Tuple<float, float>[] randoms(float[,] probs, int count)
{
    var _probs = probs.Cast<float>().ToArray();
    var dist = new DiscreteDistribution(_probs);
    int H = probs.GetLength(0);
    int W = probs.GetLength(1);
    Tuple<float, float>[] values = new Tuple<float, float>[count];
    for (int i = 0; i < count; i++)
    {
        int n = _engine.Random(dist);
        int y = n / H;
        int x = n % H;
        values[i] = new Tuple<float, float>(y / (float)H, x / (float)W);
    }
    return values;
}

// 制限
int clamp(int x, int min, int max) { return x < min ? min : x > max ? max : x; }
float clamp(float x, float min, float max) { return x < min ? min : x > max ? max : x; }
Vector3 clamp(Vector3 x, float min, float max)
{
    float k = x.Magnitude;
    x.Normalize();
    return clamp(k, min, max) * x;
}
double clamp(double x, double min, double max) { return x < min ? min : x > max ? max : x; }

// 制限
void clamp(ref int x, int min, int max) { x = clamp(x, min, max); }
void clamp(ref float x, float min, float max) { x = clamp(x, min, max); }

// 正数に制限
int positive(int x) { return x > 0 ? x : 0; }
float positive(float x) { return x > 0 ? x : 0; }

// 負数に制限
int negative(int x) { return x < 0 ? x : 0; }
float negative(float x) { return x < 0 ? x : 0; }

// 範囲内か調べる
bool is_inner(int value, int min, int max) { return value >= min && value <= max; }
bool is_inner(float value, float min, float max) { return value >= min && value <= max; }

// 範囲外か調べる
bool is_outer(int value, int min, int max) { return value < min || value > max; }
bool is_outer(float value, float min, float max) { return value < min || value > max; }

// 線形写像
float map(float x, float minx, float maxx, float miny, float maxy)
{
    float a = (maxy - miny) / (maxx - minx);
    float y = a * (x - minx) + miny;
    return y;
}

// 値をある値に近づける
float close(float value, float desiredValue, float delta)
{
    if (abs(value - desiredValue) < delta)
        return desiredValue;
    else
        return value + ((desiredValue > value) ? delta : -delta);
}

// ラジアンから度数に変換する
float RadianToDegree(float radian)
{
    return radian * 180.0f / PI;
}

// 度数からラジアンに変換する
float DegreeToRadian(float degree)
{
    return degree * PI / 180.0f;
}

// 度数からラジアンに変換する
float DegreeToRadian(int degree)
{
    return degree * PI / 180.0f;
}

// 速度[m/frame]を秒速[m/s]に変換する
float ToMeterPerSecond(float velocity)
{
    return velocity * 60;
}

// 速度[m/frame]を時速[m/h]に変換する
float ToMeterPerHour(float velority)
{
    return ToMeterPerSecond(velority) * 60 * 60;
}

// 速度[m/frame]を時速[km/h]に変換する
float ToKmPerHour(float velority)
{
    return ToMeterPerHour(velority) / 1000;
}

// 速度[m/frame]をノット[kt]に変換する
float ToKnot(float velocity)
{
    return ToMeterPerSecond(velocity) * 1.94384f;
}

// メートルを海里に変換する
float ToNauticalMile(float meter)
{
    return 1.852f * meter;
}

// メートルをフィートに変換する
float ToFeet(float meter)
{
    return 3.281f * meter;
}

// 海里をメートルに変換する
float NauticalMileToMeter(float nm)
{
    return nm / 1.852f;
}

readonly RandomEngine _engine = new RandomEngine();
