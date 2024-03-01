MODULE := engines/hpl1

MODULE_OBJS := \
	string.o \
	opengl.o \
	graphics.o \
	serialize.o \
	engine/ai/AI.o \
	engine/ai/AINodeContainer.o \
	engine/ai/AINodeGenerator.o \
	engine/ai/AStar.o \
	engine/ai/StateMachine.o \
	engine/game/Game.o \
	engine/game/GameTypes.o \
	engine/game/SaveGame.o \
	engine/game/ScriptFuncs.o \
	engine/game/Updater.o \
	engine/game/low_level_game_setup.o \
	engine/graphics/Animation.o \
	engine/graphics/AnimationTrack.o \
	engine/graphics/BackgroundImage.o \
	engine/graphics/Beam.o \
	engine/graphics/BillBoard.o \
	engine/graphics/Bone.o \
	engine/graphics/BoneState.o \
	engine/graphics/Color.o \
	engine/graphics/font_data.o \
	engine/graphics/GPUProgram.o \
	engine/graphics/GfxObject.o \
	engine/graphics/Graphics.o \
	engine/graphics/GraphicsDrawer.o \
	engine/graphics/ImageEntityData.o \
	engine/graphics/Material.o \
	engine/graphics/MaterialHandler.o \
	engine/graphics/Material_Additive.o \
	engine/graphics/Material_Alpha.o \
	engine/graphics/Material_BaseLight.o \
	engine/graphics/Material_Bump.o \
	engine/graphics/Material_BumpColorSpec.o \
	engine/graphics/Material_BumpSpec.o \
	engine/graphics/Material_BumpSpec2D.o \
	engine/graphics/Material_Diffuse.o \
	engine/graphics/Material_Diffuse2D.o \
	engine/graphics/Material_DiffuseAdditive2D.o \
	engine/graphics/Material_DiffuseAlpha2D.o \
	engine/graphics/Material_DiffuseSpec.o \
	engine/graphics/Material_EnvMap_Reflect.o \
	engine/graphics/Material_Fallback01_BaseLight.o \
	engine/graphics/Material_Fallback02_BaseLight.o \
	engine/graphics/Material_Flat.o \
	engine/graphics/Material_FontNormal.o \
	engine/graphics/Material_Modulative.o \
	engine/graphics/Material_ModulativeX2.o \
	engine/graphics/Material_Smoke2D.o \
	engine/graphics/Material_Water.o \
	engine/graphics/Mesh.o \
	engine/graphics/Mesh2d.o \
	engine/graphics/MeshCreator.o \
	engine/graphics/ParticleEmitter.o \
	engine/graphics/ParticleEmitter2D.o \
	engine/graphics/ParticleEmitter3D.o \
	engine/graphics/ParticleEmitter3D_UserData.o \
	engine/graphics/ParticleSystem3D.o \
	engine/graphics/RenderList.o \
	engine/graphics/RenderObject2D.o \
	engine/graphics/RenderState.o \
	engine/graphics/Renderable.o \
	engine/graphics/Renderer2D.o \
	engine/graphics/Renderer3D.o \
	engine/graphics/RendererPostEffects.o \
	engine/graphics/Skeleton.o \
	engine/graphics/SubMesh.o \
	engine/graphics/bitmap2D.o \
	engine/gui/Gui.o \
	engine/gui/GuiGfxElement.o \
	engine/gui/GuiMaterialBasicTypes.o \
	engine/gui/GuiPopUp.o \
	engine/gui/GuiPopUpMessageBox.o \
	engine/gui/GuiSet.o \
	engine/gui/GuiSkin.o \
	engine/gui/Widget.o \
	engine/gui/WidgetBaseClasses.o \
	engine/gui/WidgetButton.o \
	engine/gui/WidgetCheckBox.o \
	engine/gui/WidgetComboBox.o \
	engine/gui/WidgetFrame.o \
	engine/gui/WidgetImage.o \
	engine/gui/WidgetLabel.o \
	engine/gui/WidgetListBox.o \
	engine/gui/WidgetSlider.o \
	engine/gui/WidgetTextBox.o \
	engine/gui/WidgetWindow.o \
	engine/impl/CGProgram.o \
	engine/impl/CharacterBodyNewton.o \
	engine/impl/CollideShapeNewton.o \
	engine/impl/LowLevelGraphicsSDL.o \
	engine/impl/LowLevelPhysicsNewton.o \
	engine/impl/LowLevelSoundOpenAL.o \
	engine/impl/MeshLoaderCollada.o \
	engine/impl/MeshLoaderColladaHelpers.o \
	engine/impl/MeshLoaderColladaLoader.o \
	engine/impl/MeshLoaderMSH.o \
	engine/impl/OcclusionQueryOGL.o \
	engine/impl/OpenALSoundChannel.o \
	engine/impl/OpenALSoundData.o \
	engine/impl/OpenALSoundEnvironment.o \
	engine/impl/PhysicsBodyNewton.o \
	engine/impl/PhysicsControllerNewton.o \
	engine/impl/PhysicsJointBallNewton.o \
	engine/impl/PhysicsJointHingeNewton.o \
	engine/impl/PhysicsJointScrewNewton.o \
	engine/impl/PhysicsJointSliderNewton.o \
	engine/impl/PhysicsMaterialNewton.o \
	engine/impl/PhysicsWorldNewton.o \
	engine/impl/SDLTexture.o \
	engine/impl/SqScript.o \
	engine/impl/VertexBufferOGL.o \
	engine/impl/VertexBufferVBO.o \
	engine/libraries/angelscript/add-ons/scriptstdstring.o \
	engine/libraries/angelscript/add-ons/scripthelper.o \
	engine/libraries/angelscript/add-ons/scriptarray.o \
	engine/impl/tinyXML/tinyxml.o \
	engine/impl/tinyXML/tinyxmlerror.o \
	engine/impl/tinyXML/tinyxmlparser.o \
	engine/input/Action.o \
	engine/input/ActionKeyboard.o \
	engine/input/ActionMouseButton.o \
	engine/input/Input.o \
	engine/input/InputDevice.o \
	engine/input/Keyboard.o \
	engine/input/LowLevelInput.o \
	engine/input/Mouse.o \
	engine/math/BoundingVolume.o \
	engine/math/Frustum.o \
	engine/math/Math.o \
	engine/math/MathTypes.o \
	engine/math/MeshTypes.o \
	engine/math/Quaternion.o \
	engine/math/Spring.o \
	engine/physics/Body2D.o \
	engine/physics/CharacterBody.o \
	engine/physics/Collider2D.o \
	engine/physics/Physics.o \
	engine/physics/PhysicsBody.o \
	engine/physics/PhysicsController.o \
	engine/physics/PhysicsJoint.o \
	engine/physics/PhysicsJointBall.o \
	engine/physics/PhysicsJointHinge.o \
	engine/physics/PhysicsJointScrew.o \
	engine/physics/PhysicsJointSlider.o \
	engine/physics/PhysicsWorld.o \
	engine/physics/SurfaceData.o \
	engine/resources/AnimationManager.o \
	engine/resources/ConfigFile.o \
	engine/resources/EntityLoader_Object.o \
	engine/resources/FileSearcher.o \
	engine/resources/FontManager.o \
	engine/resources/FrameBitmap.o \
	engine/resources/FrameTexture.o \
	engine/resources/GpuProgramManager.o \
	engine/resources/ImageEntityManager.o \
	engine/resources/ImageManager.o \
	engine/resources/LanguageFile.o \
	engine/resources/MaterialManager.o \
	engine/resources/MeshLoaderHandler.o \
	engine/resources/MeshManager.o \
	engine/resources/ParticleManager.o \
	engine/resources/ResourceBase.o \
	engine/resources/ResourceImage.o \
	engine/resources/ResourceManager.o \
	engine/resources/Resources.o \
	engine/resources/ScriptManager.o \
	engine/resources/SoundEntityManager.o \
	engine/resources/SoundManager.o \
	engine/resources/TextureManager.o \
	engine/resources/TileSetManager.o \
	engine/resources/VideoManager.o \
	engine/resources/low_level_resources.o \
	engine/scene/AnimationState.o \
	engine/scene/Area2D.o \
	engine/scene/Camera2D.o \
	engine/scene/Camera3D.o \
	engine/scene/ColliderEntity.o \
	engine/scene/Entity.o \
	engine/scene/Entity2D.o \
	engine/scene/Entity3D.o \
	engine/scene/GridMap2D.o \
	engine/scene/ImageEntity.o \
	engine/scene/Light.o \
	engine/scene/Light2D.o \
	engine/scene/Light2DPoint.o \
	engine/scene/Light3D.o \
	engine/scene/Light3DPoint.o \
	engine/scene/Light3DSpot.o \
	engine/scene/MeshEntity.o \
	engine/scene/MultiImageEntity.o \
	engine/scene/Node.o \
	engine/scene/Node2D.o \
	engine/scene/Node3D.o \
	engine/scene/NodeState.o \
	engine/scene/PortalContainer.o \
	engine/scene/Scene.o \
	engine/scene/SectorVisibility.o \
	engine/scene/SoundEntity.o \
	engine/scene/SoundSource.o \
	engine/scene/SubMeshEntity.o \
	engine/scene/Tile.o \
	engine/scene/TileData.o \
	engine/scene/TileLayer.o \
	engine/scene/TileMap.o \
	engine/scene/TileMapLineIt.o \
	engine/scene/TileMapRectIt.o \
	engine/scene/TileSet.o \
	engine/scene/World2D.o \
	engine/scene/World3D.o \
	engine/sound/LowLevelSound.o \
	engine/sound/MusicHandler.o \
	engine/sound/Sound.o \
	engine/sound/SoundEntityData.o \
	engine/sound/SoundHandler.o \
	engine/system/Container.o \
	engine/system/LogicTimer.o \
	engine/system/low_level_system.o \
	engine/system/SerializeClass.o \
	engine/system/String.o \
	engine/system/System.o \
	hpl1.o \
	metaengine.o \
	penumbra-overture/AttackHandler.o \
	penumbra-overture/ButtonHandler.o \
	penumbra-overture/CharacterMove.o \
	penumbra-overture/Credits.o \
	penumbra-overture/DeathMenu.o \
	penumbra-overture/DemoEndText.o \
	penumbra-overture/EffectHandler.o \
	penumbra-overture/FadeHandler.o \
	penumbra-overture/GameArea.o \
	penumbra-overture/GameDamageArea.o \
	penumbra-overture/GameEnemy.o \
	penumbra-overture/GameEnemy_Dog.o \
	penumbra-overture/GameEnemy_Spider.o \
	penumbra-overture/GameEnemy_Worm.o \
	penumbra-overture/GameEntity.o \
	penumbra-overture/GameForceArea.o \
	penumbra-overture/GameItem.o \
	penumbra-overture/GameItemType.o \
	penumbra-overture/GameLadder.o \
	penumbra-overture/GameLamp.o \
	penumbra-overture/GameLink.o \
	penumbra-overture/GameLiquidArea.o \
	penumbra-overture/GameMessageHandler.o \
	penumbra-overture/GameMusicHandler.o \
	penumbra-overture/GameObject.o \
	penumbra-overture/GameSaveArea.o \
	penumbra-overture/GameScripts.o \
	penumbra-overture/GameStickArea.o \
	penumbra-overture/GameSwingDoor.o \
	penumbra-overture/GameTypes.o \
	penumbra-overture/GraphicsHelper.o \
	penumbra-overture/HudModel_Throw.o \
	penumbra-overture/HudModel_Weapon.o \
	penumbra-overture/Init.o \
	penumbra-overture/IntroStory.o \
	penumbra-overture/Inventory.o \
	penumbra-overture/MainMenu.o \
	penumbra-overture/MapHandler.o \
	penumbra-overture/MapLoadText.o \
	penumbra-overture/Notebook.o \
	penumbra-overture/NumericalPanel.o \
	penumbra-overture/Player.o \
	penumbra-overture/PlayerHands.o \
	penumbra-overture/PlayerHelper.o \
	penumbra-overture/PlayerState_Interact.o \
	penumbra-overture/PlayerState_Misc.o \
	penumbra-overture/PlayerState_Weapon.o \
	penumbra-overture/PreMenu.o \
	penumbra-overture/RadioHandler.o \
	penumbra-overture/SaveHandler.o \
	penumbra-overture/SaveTypes.o \
	penumbra-overture/TriggerHandler.o \
	penumbra-overture/Triggers.o \
	engine/libraries/newton/core/dg.o \
	engine/libraries/newton/core/dgAABBPolygonSoup.o \
	engine/libraries/newton/core/dgCRC.o \
	engine/libraries/newton/core/dgConvexHull3d.o \
	engine/libraries/newton/core/dgConvexHull4d.o \
	engine/libraries/newton/core/dgDebug.o \
	engine/libraries/newton/core/dgDelaunayTetrahedralization.o \
	engine/libraries/newton/core/dgGeneralMatrix.o \
	engine/libraries/newton/core/dgGeneralVector.o \
	engine/libraries/newton/core/dgGoogol.o \
	engine/libraries/newton/core/dgIntersections.o \
	engine/libraries/newton/core/dgMatrix.o \
	engine/libraries/newton/core/dgMemory.o \
	engine/libraries/newton/core/dgNode.o \
	engine/libraries/newton/core/dgPolygonSoupBuilder.o \
	engine/libraries/newton/core/dgPolyhedra.o \
	engine/libraries/newton/core/dgPolyhedraMassProperties.o \
	engine/libraries/newton/core/dgQuaternion.o \
	engine/libraries/newton/core/dgRandom.o \
	engine/libraries/newton/core/dgRef.o \
	engine/libraries/newton/core/dgRefCounter.o \
	engine/libraries/newton/core/dgSPDMatrix.o \
	engine/libraries/newton/core/dgSmallDeterminant.o \
	engine/libraries/newton/core/dgSphere.o \
	engine/libraries/newton/core/dgThreads.o \
	engine/libraries/newton/core/dgTree.o \
	engine/libraries/newton/core/dgTypes.o \
	engine/libraries/newton/Newton.o \
	engine/libraries/newton/NewtonClass.o \
	engine/libraries/newton/physics/dgBallConstraint.o \
	engine/libraries/newton/physics/dgBilateralConstraint.o \
	engine/libraries/newton/physics/dgBody.o \
	engine/libraries/newton/physics/dgBodyMasterList.o \
	engine/libraries/newton/physics/dgBroadPhaseCollision.o \
	engine/libraries/newton/physics/dgCollision.o \
	engine/libraries/newton/physics/dgCollisionBVH.o \
	engine/libraries/newton/physics/dgCollisionBox.o \
	engine/libraries/newton/physics/dgCollisionCapsule.o \
	engine/libraries/newton/physics/dgCollisionChamferCylinder.o \
	engine/libraries/newton/physics/dgCollisionCompound.o \
	engine/libraries/newton/physics/dgCollisionCompoundBreakable.o \
	engine/libraries/newton/physics/dgCollisionCone.o \
	engine/libraries/newton/physics/dgCollisionConvex.o \
	engine/libraries/newton/physics/dgCollisionConvexHull.o \
	engine/libraries/newton/physics/dgCollisionConvexModifier.o \
	engine/libraries/newton/physics/dgCollisionCylinder.o \
	engine/libraries/newton/physics/dgCollisionEllipse.o \
	engine/libraries/newton/physics/dgCollisionHeightField.o \
	engine/libraries/newton/physics/dgCollisionMesh.o \
	engine/libraries/newton/physics/dgCollisionNull.o \
	engine/libraries/newton/physics/dgCollisionScene.o \
	engine/libraries/newton/physics/dgCollisionSphere.o \
	engine/libraries/newton/physics/dgCollisionUserMesh.o \
	engine/libraries/newton/physics/dgConnectorConstraint.o \
	engine/libraries/newton/physics/dgConstraint.o \
	engine/libraries/newton/physics/dgContact.o \
	engine/libraries/newton/physics/dgCorkscrewConstraint.o \
	engine/libraries/newton/physics/dgHingeConstraint.o \
	engine/libraries/newton/physics/dgMeshEffect.o \
	engine/libraries/newton/physics/dgMeshEffect2.o \
	engine/libraries/newton/physics/dgMeshEffect3.o \
	engine/libraries/newton/physics/dgMeshEffectSolidTree.o \
	engine/libraries/newton/physics/dgMinkowskiConv.o \
	engine/libraries/newton/physics/dgNarrowPhaseCollision.o \
	engine/libraries/newton/physics/dgPointToCurveConstraint.o \
	engine/libraries/newton/physics/dgSlidingConstraint.o \
	engine/libraries/newton/physics/dgUniversalConstraint.o \
	engine/libraries/newton/physics/dgUpVectorConstraint.o \
	engine/libraries/newton/physics/dgUserConstraint.o \
	engine/libraries/newton/physics/dgWorld.o \
	engine/libraries/newton/physics/dgWorldDynamicUpdate.o \
	engine/libraries/angelscript/sources/as_atomic.o \
	engine/libraries/angelscript/sources/as_builder.o \
	engine/libraries/angelscript/sources/as_bytecode.o \
	engine/libraries/angelscript/sources/as_callfunc.o \
	engine/libraries/angelscript/sources/as_compiler.o \
	engine/libraries/angelscript/sources/as_configgroup.o \
	engine/libraries/angelscript/sources/as_context.o \
	engine/libraries/angelscript/sources/as_datatype.o \
	engine/libraries/angelscript/sources/as_gc.o \
	engine/libraries/angelscript/sources/as_generic.o \
	engine/libraries/angelscript/sources/as_globalproperty.o \
	engine/libraries/angelscript/sources/as_memory.o \
	engine/libraries/angelscript/sources/as_module.o \
	engine/libraries/angelscript/sources/as_objecttype.o \
	engine/libraries/angelscript/sources/as_outputbuffer.o \
	engine/libraries/angelscript/sources/as_parser.o \
	engine/libraries/angelscript/sources/as_restore.o \
	engine/libraries/angelscript/sources/as_scriptcode.o \
	engine/libraries/angelscript/sources/as_scriptengine.o \
	engine/libraries/angelscript/sources/as_scriptfunction.o \
	engine/libraries/angelscript/sources/as_scriptnode.o \
	engine/libraries/angelscript/sources/as_scriptobject.o \
	engine/libraries/angelscript/sources/as_string.o \
	engine/libraries/angelscript/sources/as_string_util.o \
	engine/libraries/angelscript/sources/as_thread.o \
	engine/libraries/angelscript/sources/as_tokenizer.o \
	engine/libraries/angelscript/sources/as_typeinfo.o \
	engine/libraries/angelscript/sources/as_variablescope.o

ifdef USE_TINYGL
MODULE_OBJS += \
	engine/impl/low_level_graphics_tgl.o \
	engine/impl/texture_tgl.o \
	engine/impl/vertex_buffer_tgl.o
endif

# This module can be built as a plugin
ifeq ($(ENABLE_HPL1), DYNAMIC_PLUGIN)
PLUGIN := 1
endif

# Include common rules
include $(srcdir)/rules.mk

# Detection objects
DETECT_OBJS += $(MODULE)/detection.o