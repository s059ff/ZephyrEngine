var e = Entity.Find("camera");
var c = e.Get<CameraComponent>();
c.TrackingTarget = Entity.Find("enemy");