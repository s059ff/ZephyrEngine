using System;
using System.Collections.Generic;
using System.Threading;
using System.Windows.Forms;
using ZephyrSharp.GameSystem;
using ComponentID = System.Type;
using EntityID = System.UInt64;
using Timer = System.Windows.Forms.Timer;

namespace ZephyrTools.GameSystemMonitor
{
    /// <summary>
    /// ゲームシステムの状態を監視するツールです。
    /// </summary>
    public partial class GameSystemMonitor : Form
    {
        class EntityTreeNode : TreeNode
        {
            public Entity MonitorEntity;
        }

        class ComponentTreeNode : TreeNode
        {
            public EntityComponent MonitorComponent;
        }

        class NothingComponent : EntityComponent { }

        ComponentTreeNode NothingComponentTreeNode
        {
            get
            {
                return new ComponentTreeNode()
                {
                    ImageIndex = 1,
                    SelectedImageIndex = 1,
                    MonitorComponent = new NothingComponent(),
                    Text = "（なし）"
                };
            }
        }

        Dictionary<EntityID, PropertyView> EntityPropertyViews
            = new Dictionary<EntityID, PropertyView>();

        Dictionary<Tuple<EntityID, ComponentID>, PropertyView> ComponentPropertyViews
            = new Dictionary<Tuple<EntityID, ComponentID>, PropertyView>();

        public static GameSystemMonitor Execute()
        {
            GameSystemMonitor form = null;

            var thread = new Thread(() =>
            {
                form = new GameSystemMonitor();
                Application.Run(form);
            });
            thread.Start();

            while (form == null)
                Thread.Sleep(1);

            return form;
        }

        public static void Shutdown(GameSystemMonitor monitor)
        {
            monitor.Invoke((MethodInvoker)(() => monitor.Close()));
        }

        private Timer timer = new Timer();

        private GameSystemMonitor()
        {
            InitializeComponent();

            timer.Tick += Timer_Tick;
            timer.Interval = 20;
            timer.Start();
        }

        private void Timer_Tick(object sender, EventArgs e)
        {
            this.Synchronize();
        }

        private void Synchronize()
        {
            var nodes = treeView1.Nodes;

            LinkedList<Entity> entities = new LinkedList<Entity>();
            Entity.ForEach(e => { entities.AddLast(e); });

            SyncEntityView(nodes, entities);
            foreach (TreeNode node in nodes)
            {
                if (node.IsExpanded)
                {
                    SyncComponentView(node.Nodes, (node as EntityTreeNode).MonitorEntity.Components);
                }
            }

            foreach (var view in EntityPropertyViews.Values)
            {
                view.SyncView();
            }
            foreach (var view in ComponentPropertyViews.Values)
            {
                view.SyncView();
            }
        }

        private void SyncEntityView(TreeNodeCollection nodes, IEnumerable<Entity> entities)
        {
            List<TreeNode> removeList = new List<TreeNode>();
            foreach (TreeNode node in nodes)
            {
                var e = ((EntityTreeNode)node).MonitorEntity;
                if (!e.IsAlive)
                {
                    removeList.Add(node);
                }
            }
            foreach (var node in removeList)
            {
                nodes.Remove(node);
            }

            foreach (var e in entities)
            {
                if (!nodes.ContainsKey(e.ID.ToString()))
                {
                    var node = new EntityTreeNode()
                    {
                        ImageIndex = 0,
                        SelectedImageIndex = 0,
                        Name = e.ID.ToString(),
                        MonitorEntity = e,
                        Text = string.Format("[{0}] {1}", e.ID, e.Name),
                    };
                    node.Nodes.Add(NothingComponentTreeNode);
                    nodes.Add(node);
                }
            }
        }

        private void SyncComponentView(TreeNodeCollection nodes, IEnumerable<EntityComponent> components)
        {
            List<TreeNode> removeList = new List<TreeNode>();
            foreach (TreeNode node in nodes)
            {
                var c = ((ComponentTreeNode)node).MonitorComponent;
                bool notFound = true;
                foreach (var component in components)
                {
                    if (c.GetType() == component.GetType())
                    {
                        notFound = false;
                        break;
                    }
                }
                if (notFound)
                {
                    removeList.Add(node);
                }
            }
            foreach (var node in removeList)
            {
                nodes.Remove(node);
            }

            foreach (var c in components)
            {
                if (!nodes.ContainsKey(c.GetType().Name))
                {
                    nodes.Add(new ComponentTreeNode()
                    {
                        ImageIndex = 1,
                        SelectedImageIndex = 1,
                        Name = c.GetType().Name,
                        MonitorComponent = c,
                        Text = c.GetType().Name,
                    });
                }
            }

            if (nodes.Count == 0)
            {
                nodes.Add(NothingComponentTreeNode);
            }
        }

        private void treeView1_NodeMouseDoubleClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            if (e.Node is EntityTreeNode)
            {
                var node = (EntityTreeNode)e.Node;
                var key = node.MonitorEntity.ID;
                if (this.EntityPropertyViews.ContainsKey(key))
                {
                    var view = EntityPropertyViews[key];
                    view.SyncView();
                    EntityPropertyViews[key].Activate();
                }
                else
                {
                    var view = new PropertyView(node.MonitorEntity);
                    view.Text = node.Text;
                    view.SyncView();
                    view.Show();
                    view.Activate();
                    view.FormClosed += (_, __) => EntityPropertyViews.Remove(key);
                    EntityPropertyViews.Add(key, view);
                }
            }
            else
            {
                var node = (ComponentTreeNode)e.Node;
                if (!(node.MonitorComponent is NothingComponent))
                {
                    var key = new Tuple<EntityID, ComponentID>(node.MonitorComponent.Owner.ID, node.MonitorComponent.GetType());
                    if (ComponentPropertyViews.ContainsKey(key))
                    {
                        var view = ComponentPropertyViews[key];
                        view.SyncView();
                        ComponentPropertyViews[key].Activate();
                    }
                    else
                    {
                        var view = new PropertyView(node.MonitorComponent);
                        view.Text = string.Format("{0}.{1}", node.Parent.Text, node.Text);
                        view.SyncView();
                        view.Show();
                        view.Activate();
                        view.FormClosed += (_, __) => ComponentPropertyViews.Remove(key);
                        ComponentPropertyViews.Add(key, view);
                    }
                }
            }
        }

        private void treeView1_BeforeExpand(object sender, TreeViewCancelEventArgs e)
        {
            if (e.Node is EntityTreeNode)
            {
                var node = (EntityTreeNode)e.Node;
                SyncComponentView(node.Nodes, node.MonitorEntity.Components);
            }
        }

        private void treeView1_AfterCollapse(object sender, TreeViewEventArgs e)
        {
            if (e.Node is EntityTreeNode)
            {
                var node = (EntityTreeNode)e.Node;
                foreach (var componentNode in node.Nodes)
                {
                    (componentNode as ComponentTreeNode).MonitorComponent = null;
                }
                node.Nodes.Clear();
                node.Nodes.Add(NothingComponentTreeNode);
            }
        }
    }
}
