﻿using static EngineScript;

class LearnablePilotComponent : AbstractPilotComponent
{
    protected override void Update()
    {
        base.Update();

        var aircraft = this.Owner.Get<AircraftComponent>();
        aircraft.RollInput = uniform(-1.0f, +1.0f);
        aircraft.PitchInput = uniform(-1.0f, +1.0f);
        aircraft.YawInput = uniform(-1.0f, +1.0f);
        aircraft.ThrottleInput = uniform(+0.5f, 1.0f);
        aircraft.MissileLaunchInput = false;
        aircraft.GunFireInput = false;
    }
}