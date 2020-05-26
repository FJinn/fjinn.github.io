import unreal

def GetCoreBasedRotation(CoreLocation, SelfActor) :
  SelfLocation = SelfActor.get_actor_location()
  PullingVector = unreal.Vector(CoreLocation.x - SelfLocation.x, CoreLocation.y - SelfLocation.y, CoreLocation.z - SelfLocation.z)
  PullingVector *= -1
  ResultRotation = unreal.MathLibrary().make_rot_from_zx(PullingVector, SelfActor.get_actor_forward_vector())
  return ResultRotation

def SpawnSurroundingActor(ActorToSpawn, Core, CenterObject, Distance=10, NumberOfWalls=0) :
  if NumberOfWalls <= 0 : NumberOfWalls = Distance

  spawningActorAsset = unreal.EditorAssetLibrary().find_asset_data(ActorToSpawn)
  spawningActorObject = spawningActorAsset.get_asset()

  level_actor_list = unreal.EditorLevelLibrary().get_all_level_actors()

  for a in level_actor_list:
    if a.get_name() == Core : core_object = a
    if a.get_name() == CenterObject : center_object = a
  
  ForwardVector = center_object.get_actor_forward_vector()
  PerpendicularVector = unreal.Vector(1, 1, ((ForwardVector.x + ForwardVector.y) * -1) / ForwardVector.z )
  PerpendicularVector = PerpendicularVector * Distance
  NewPosition = PerpendicularVector + center_object.get_actor_location()
  RotationAxis = center_object.get_actor_location() - core_object.get_actor_location()

  with unreal.ScopedEditorTransaction("Spawn Surrounding Actors") as trans:
    for i in range(0, NumberOfWalls, 2) :
      ResultPosition = unreal.MathLibrary().rotate_angle_axis(NewPosition, i * 360 / Distance, RotationAxis)

      unit_direction = unreal.MathLibrary().get_direction_unit_vector(core_object.get_actor_location(), ResultPosition)
      ResultLocation = (unit_direction * 590) + core_object.get_actor_location()

      spawned_actor = unreal.EditorLevelLibrary().spawn_actor_from_object(spawningActorObject, ResultLocation)
      spawned_actor.set_actor_relative_scale3d(unreal.Vector(0.1, 0.1, 2.0))
      spawned_actor.set_actor_rotation(GetCoreBasedRotation(core_object.get_actor_location(), spawned_actor), True)
