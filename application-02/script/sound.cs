#include "common.csh"

const double AffectionSoundRange = 500;
const double SonicSpeed = 340.0 / 60.0;

SoundBuffer ExplosionSound = new SoundBuffer();
SoundBuffer LargeExplosionSound = new SoundBuffer();
SoundBuffer JetSound = new SoundBuffer();
SoundBuffer LockonSound = new SoundBuffer();
SoundBuffer AlertSound = new SoundBuffer();
SoundBuffer BulletSound = new SoundBuffer();
SoundBuffer BulletHitSound = new SoundBuffer();

partial void initialize()
{
    ExplosionSound.Create("res/sound/explosion1.wav");
    LargeExplosionSound.Create("res/sound/explosion2.wav");
    JetSound.Create("res/sound/burner_f15.wav");
    LockonSound.Create("res/sound/lockon4.wav");
    LockonSound.Volume = 0.25;
    AlertSound.Create("res/sound/alert2.wav");
    AlertSound.Volume = 0.25;
    BulletSound.Create("res/sound/bullet.wav");
    BulletHitSound.Create("res/sound/bulletHit.wav");
    BulletHitSound.Volume = 0.1;
}

partial void finalize()
{
    ExplosionSound.Dispose();
    LargeExplosionSound.Dispose();
    JetSound.Dispose();
    LockonSound.Dispose();
    AlertSound.Dispose();
    BulletSound.Dispose();
    BulletHitSound.Dispose();
}

double volume(double distance)
{
    return (distance > 0) ? clamp(AffectionSoundRange / distance, 0, 1) : 1;
}

double frequency(double vo, double vs, uint f0)
{
    double k = (SonicSpeed - vo) / (SonicSpeed - vs);
    return (uint)(k * f0);
}
