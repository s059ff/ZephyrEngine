using System;
using System.Collections.Generic;
using ZephyrSharp.GameSystem;

public class SquadronComponent : CustomEntityComponent
{
    const int MaxUnits = 8;

    class SquadronInfo
    {
        public Entity[] entities = new Entity[MaxUnits];
        public int count = 0;
    }

    static Dictionary<string, SquadronInfo> SquadronTable = new Dictionary<string, SquadronInfo>();

    public Entity SquadronLeader { get { return SquadronTable[this.SquadronName].entities[0]; } }

    public readonly string SquadronName;
    public int UnitNumber;

    const int InvalidUnitNumber = -1;

    public SquadronComponent(string squadronName)
    {
        this.SquadronName = squadronName;
        this.UnitNumber = InvalidUnitNumber;
    }

    protected override void OnAttach()
    {
        base.OnAttach();

        if (!SquadronTable.ContainsKey(this.SquadronName))
        {
            SquadronTable.Add(this.SquadronName, new SquadronInfo());
        }
        var squadronInfo = SquadronTable[this.SquadronName];

        this.UnitNumber = squadronInfo.count++;
        squadronInfo.entities[this.UnitNumber] = this.Owner;
    }

    protected override void OnDetach()
    {
        base.OnDetach();

        var squadronInfo = SquadronTable[this.SquadronName];
        squadronInfo.entities[this.UnitNumber] = null;
        squadronInfo.count--;

        this.UnitNumber = InvalidUnitNumber;
    }
}
