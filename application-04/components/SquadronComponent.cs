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

    static Dictionary<string, SquadronInfo> Squadrons = new Dictionary<string, SquadronInfo>();

    public Entity SquadronLeader { get { return Squadrons[this.SquadronName].entities[0]; } }

    public readonly string SquadronName;
    public int Number;

    public SquadronComponent(string squadronName)
    {
        this.SquadronName = squadronName;
    }

    protected override void OnAttach()
    {
        base.OnAttach();

        if (!Squadrons.ContainsKey(this.SquadronName))
        {
            Squadrons.Add(this.SquadronName, new SquadronInfo());
        }
        this.Number = Squadrons[this.SquadronName].count++;

        var squadronsEntities = Squadrons[this.SquadronName].entities;
        if (squadronsEntities.Length <= this.Number)
            Array.Resize(ref squadronsEntities, squadronsEntities.Length * 2);
        squadronsEntities[this.Number] = Owner;
    }

    protected override void OnDetach()
    {
        base.OnDetach();

        Squadrons[this.SquadronName].entities[this.Number] = null;
        this.Number = -1;
    }
}
