using System;
using System.Collections.Generic;
using ZephyrSharp.GameSystem;

public class SquadronComponent : CustomEntityComponent
{
    class SquadronInfo
    {
        public Entity[] entities = new Entity[8];
        public int count = 0;
    }

    static Dictionary<string, SquadronInfo> Squadrons = new Dictionary<string, SquadronInfo>();

    public Entity SquadronLeader { get { return Squadrons[SquadronName].entities[0]; } }

    public readonly string SquadronName;
    public int Number;

    public SquadronComponent(string squadronName)
    {
        SquadronName = squadronName;
    }

    protected override void OnAttach()
    {
        base.OnAttach();

        if (!Squadrons.ContainsKey(SquadronName))
        {
            Squadrons.Add(SquadronName, new SquadronInfo());
        }
        Number = Squadrons[SquadronName].count++;

        var squadronsEntities = Squadrons[SquadronName].entities;
        if (squadronsEntities.Length <= Number)
            Array.Resize(ref squadronsEntities, squadronsEntities.Length * 2);
        squadronsEntities[Number] = Owner;
    }

    protected override void OnDetach()
    {
        base.OnDetach();

        Squadrons[SquadronName].entities[Number] = null;
        Number = -1;
    }
}
