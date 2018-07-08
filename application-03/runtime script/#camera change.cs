public partial class Script : System.Object
{
	public static var e = Entity.Find ("camera");

	public static var c = e.Get<CameraComponent> ();
}
