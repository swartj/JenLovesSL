#include "includes.h"
#include "resources.h"
#include "Rendering.hpp"
#include "Font.h"
#include "sdk.h"
#include "damageindicator.h"
#include "Functions.h"
#include "kiero/minhook/include/MinHook.h"
#include "il2cpp_resolver.hpp"
#include "Lists.hpp"
#include "Callback.hpp"
#include <Utils/VFunc.hpp>
#include <iostream>
#include <PaternScan.hpp>
#include <intrin.h>
#include "Debug.h"
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


#define MAX_PLAYER_DISTANCE 200
#define MAX_ITEM_DISTANCE 100
#define MAX_ITEM_COUNT 50


Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;

Unity::il2cppClass* MaterialClass = 0x0;
Unity::il2cppClass* FpcMouseLookClass = 0x0;
Unity::il2cppClass* TeslaGateClass = 0x0;
Unity::il2cppClass* ReferenceHubClass = 0x0;
Unity::il2cppClass* PocketDimensionTeleportClass = 0x0;
Unity::il2cppClass* RoomIdentifierClass = 0x0;
Unity::il2cppObject* CharacterModelSystemType;
Unity::il2cppObject* SubcontrollerBehaviourSystemType;
Unity::il2cppObject* MeshRendererType;
Unity::il2cppObject* MaterialType;



void CreateConsole() {

	console = Console();

	return;
	AllocConsole();
	//AttachConsole(GetCurrentProcessId());
	SetConsoleTitle("JenExMachina");
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
}

void initvars() {
	if (IL2CPP::Initialize(true)) {
		printf("[ DEBUG ] Il2Cpp initialized\n");
	}
	else {
		printf("[ DEBUG ] Il2Cpp initialize failed, quitting...");
		Sleep(300);
		exit(0);
	}
	sdk::Base = (uintptr_t)GetModuleHandleA(NULL);
	printf("[ DEBUG ] Base Address: 0x%llX\n", sdk::Base);
	sdk::GameAssembly = (uintptr_t)GetModuleHandleA("GameAssembly.dll");
	printf("[ DEBUG ] GameAssembly Base Address: 0x%llX\n", sdk::GameAssembly);
	sdk::UnityPlayer = (uintptr_t)GetModuleHandleA("UnityPlayer.dll");
	printf("[ DEBUG ] UnityPlayer Base Address: 0x%llX\n", sdk::UnityPlayer);
	printf("----------------------------------------------------------\n");
	printf("\n");
}

void Log(uintptr_t address, const char* name) {
	printf("[ LOG ] %s: 0x%llX\n", name, address);
}
#define DEBUG // undefine in release

bool find_sigs() {
	Unity::il2cppClass* UECameraClass = IL2CPP::Class::Find("UnityEngine.Camera");
	ReferenceHubClass = IL2CPP::Class::Find("ReferenceHub");



	Unity::il2cppClass* ComponentClass = IL2CPP::Class::Find("UnityEngine.Component");
	Unity::il2cppClass* GameObjectClass = IL2CPP::Class::Find("UnityEngine.GameObject");
	Unity::il2cppClass* TransformClass = IL2CPP::Class::Find("UnityEngine.Transform");
	Unity::il2cppClass* CharacterControllerClass = IL2CPP::Class::Find("UnityEngine.CharacterController");
	Unity::il2cppClass* PlayerRoleBaseClass = IL2CPP::Class::Find("PlayerRoles.PlayerRoleBase");
	Unity::il2cppClass* NicknameSyncClass = IL2CPP::Class::Find("NicknameSync");
	Unity::il2cppClass* InventoryItemLoaderClass = IL2CPP::Class::Find("InventorySystem.InventoryItemLoader");
	Unity::il2cppClass* InventoryPickupClass = IL2CPP::Class::Find("InventorySystem.Items.Pickups.ItemPickupBase");
	Unity::il2cppClass* RestartClass = IL2CPP::Class::Find("RoundRestarting.RoundRestart");
	Unity::il2cppClass* RoundStartClass = IL2CPP::Class::Find("GameCore.RoundStart");
	Unity::il2cppClass* PhysicsModuleClass = IL2CPP::Class::Find("InventorySystem.Items.Pickups.PickupPhysicsModule");
	Unity::il2cppClass* RoomUtilsClass = IL2CPP::Class::Find("MapGeneration.RoomUtils");
	RoomIdentifierClass = IL2CPP::Class::Find("MapGeneration.RoomIdentifier");
	Unity::il2cppClass* StandardDamageHandlerClass = IL2CPP::Class::Find("PlayerStatsSystem.StandardDamageHandler");
	PocketDimensionTeleportClass = IL2CPP::Class::Find("PocketDimensionTeleport");
	Unity::il2cppClass* FirstPersonMovementModuleClass = IL2CPP::Class::Find("PlayerRoles.FirstPersonControl.FirstPersonMovementModule");
	Unity::il2cppClass* FpcMotorClass = IL2CPP::Class::Find("PlayerRoles.FirstPersonControl.FpcMotor");
	Unity::il2cppClass* PlayerRolesUtilsClass = IL2CPP::Class::Find("PlayerRoles.PlayerRolesUtils");
	Unity::il2cppClass* StringClass = IL2CPP::Class::Find("System.String");
	Unity::il2cppClass* AnimatorClass = IL2CPP::Class::Find("UnityEngine.Animator");
	Unity::il2cppClass* AnimatedCharacterModelClass = IL2CPP::Class::Find("PlayerRoles.FirstPersonControl.Thirdperson.AnimatedCharacterModel");
	Unity::il2cppClass* AvatarClass = IL2CPP::Class::Find("UnityEngine.Avatar");
	Unity::il2cppClass* ObjectClass = IL2CPP::Class::Find("UnityEngine.Object");
	Unity::il2cppClass* SubcontrollerBehaviourClass = IL2CPP::Class::Find("PlayerRoles.FirstPersonControl.Thirdperson.Subcontrollers.SubcontrollerBehaviour");
	Unity::il2cppClass* UnityEnginePhysicsClass = IL2CPP::Class::Find("UnityEngine.Physics");
	Unity::il2cppClass* HitboxIdentityClass = IL2CPP::Class::Find("HitboxIdentity");
	FpcMouseLookClass = IL2CPP::Class::Find("PlayerRoles.FirstPersonControl.FpcMouseLook");
	Unity::il2cppClass* QuaternionClass = IL2CPP::Class::Find("UnityEngine.Quaternion");
	Unity::il2cppClass* BacktrackClass = IL2CPP::Class::Find("InventorySystem.Items.Firearms.Modules.Misc.ShotBacktrackData");
	Unity::il2cppClass* RelativePositionClass = IL2CPP::Class::Find("RelativePositioning.RelativePosition");
	Unity::il2cppClass* SystemTypeClass = IL2CPP::Class::Find("System.Type");
	Unity::il2cppClass* AutomaticActionModuleClass = IL2CPP::Class::Find("InventorySystem.Items.Firearms.Modules.AutomaticActionModule");
	Unity::il2cppClass* SubcomponentBaseClass = IL2CPP::Class::Find("InventorySystem.Items.Autosync.SubcomponentBase");
	Unity::il2cppClass* NetworkWriterClass = IL2CPP::Class::Find("Mirror.NetworkWriter");
	Unity::il2cppClass* NetworkWriterPoolClass = IL2CPP::Class::Find("Mirror.NetworkWriterPool");
	Unity::il2cppClass* NetworkConnectionClass = IL2CPP::Class::Find("Mirror.NetworkConnection");
	Unity::il2cppClass* NetworkDiagnosticsClass = IL2CPP::Class::Find("Mirror.NetworkDiagnostics");
	Unity::il2cppClass* NetworkConnectionToServerClass = IL2CPP::Class::Find("Mirror.NetworkConnectionToServer");
	Unity::il2cppClass* BatcherClass = IL2CPP::Class::Find("Mirror.Batcher");
	TeslaGateClass = IL2CPP::Class::Find("TeslaGate");
	Unity::il2cppClass* Scp079CameraClass = IL2CPP::Class::Find("PlayerRoles.PlayableScps.Scp079.Cameras.Scp079Camera");
	Unity::il2cppClass* Scp079CurrentCameraSyncClass = IL2CPP::Class::Find("PlayerRoles.PlayableScps.Scp079.Cameras.Scp079CurrentCameraSync");
	Unity::il2cppClass* Scp079TeslaAbilityClass = IL2CPP::Class::Find("PlayerRoles.PlayableScps.Scp079.Scp079TeslaAbility");
	Unity::il2cppClass* Scp079AbilityBase = IL2CPP::Class::Find("PlayerRoles.PlayableScps.Scp079.Scp079AbilityBase");
	Unity::il2cppClass* DebugClass = IL2CPP::Class::Find("UnityEngine.Debug");
	Unity::il2cppClass* HitscanHitregModuleBaseClass = IL2CPP::Class::Find("InventorySystem.Items.Firearms.Modules.HitscanHitregModuleBase");
	Unity::il2cppClass* ColorClass = IL2CPP::Class::Find("UnityEngine.Color");
	Unity::il2cppClass* DrawableLinesManagerClass = IL2CPP::Class::Find("DrawableLine.DrawableLinesManager");
	Unity::il2cppClass* MeshRendererClass = IL2CPP::Class::Find("UnityEngine.MeshRenderer");
	Unity::il2cppClass* RendererClass = IL2CPP::Class::Find("UnityEngine.Renderer");
	MaterialClass = IL2CPP::Class::Find("UnityEngine.Material");
	Unity::il2cppClass* ShaderClass = IL2CPP::Class::Find("UnityEngine.Shader");
	Unity::il2cppClass* TracerBaseClass = IL2CPP::Class::Find("InventorySystem.Items.Firearms.Modules.Misc.TracerBase");
	Unity::il2cppClass* BulletTracerClass = IL2CPP::Class::Find("InventorySystem.Items.Firearms.Modules.Misc.HitscanBulletTracer");
	Unity::il2cppClass* ImpactEffectsModuleClass = IL2CPP::Class::Find("InventorySystem.Items.Firearms.Modules.ImpactEffectsModule");
	Unity::il2cppClass* NetworkReaderClass = IL2CPP::Class::Find("Mirror.NetworkReader");
	Unity::il2cppClass* UnbatcherClass = IL2CPP::Class::Find("Mirror.Unbatcher");
	Unity::il2cppClass* Scp173TeleportAbilityClass = IL2CPP::Class::Find("PlayerRoles.PlayableScps.Scp173.Scp173TeleportAbility");
	Unity::il2cppClass* ReferenceHubReaderWriterClass = IL2CPP::Class::Find("Utils.Networking.ReferenceHubReaderWriter");
	Unity::il2cppClass* NetworkWriterExtensionClass = IL2CPP::Class::Find("Mirror.NetworkWriterExtensions");
	Unity::il2cppClass* SystemArrayClass = IL2CPP::Class::Find("System.Array");

	
	
	//Unity::il2cppClass* ShotRequestClass = IL2CPP::Class::Find("InventorySystem.Items.Firearms.Modules.ShotRequest");
	
	Offsets::GetMethods = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(SystemTypeClass, "GetMethods");
	Offsets::CreateString = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(StringClass, "CreateString");
	Offsets::GetComponentByName = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(GameObjectClass, "GetComponentByName");
	Offsets::GetComponent = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(GameObjectClass, "GetComponent");
	Offsets::GetDisplayName = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(NicknameSyncClass, "get_DisplayName");
	Offsets::LocalHub = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(ReferenceHubClass, "get_LocalHub");
	Offsets::WolrdToScreen = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(UECameraClass, "WorldToScreenPoint");
	Offsets::GetPosition = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(TransformClass, "get_position");
	Offsets::GetTransform = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(ComponentClass, "get_transform");
	Offsets::GetGameObject = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(ComponentClass, "get_gameObject");
	Offsets::GetMainCamera = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(UECameraClass, "get_main");
	Offsets::GetReferenceHub = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(ReferenceHubClass, "get_AllHubs");
	Offsets::GetCenter = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(CharacterControllerClass, "get_center");
	Offsets::GetTeam = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(PlayerRolesUtilsClass, "GetTeam");
	Offsets::IsHost = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(ReferenceHubClass, "get_IsHost");
	Offsets::IsDummy = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(ReferenceHubClass, "get_IsDummy");
	Offsets::IsPOV = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(ReferenceHubClass, "get_IsPOV");
	Offsets::GetAvailableItems = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(InventoryItemLoaderClass, "get_AvailableItems");
	Offsets::PickupGetPosition = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(InventoryPickupClass, "get_Position");
	Offsets::OnPickupDestroy = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(InventoryPickupClass, "OnDestroy");
	Offsets::IsRoundRestarting = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(RestartClass, "get_IsRoundRestarting");
	Offsets::GetHostHub = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(ReferenceHubClass, "get_HostHub");
	Offsets::AddOnBeforePickupDestroyed = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(InventoryPickupClass, "add_OnPickupDestroyed");
	Offsets::AddOnPickupAdded = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(InventoryPickupClass, "add_OnPickupAdded");
	Offsets::AddOnBeforePlayerDestroyed = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(ReferenceHubClass, "add_OnPlayerDestroyed");
	Offsets::GetRoundStarted = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(RoundStartClass, "get_RoundStarted");
	Offsets::GetDefaultPhysicsModule = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(InventoryPickupClass, "get_DefaultPhysicsModule");
	Offsets::GetIsSpawned = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(PhysicsModuleClass, "get_IsSpawned");
	Offsets::TryFindRoom = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(RoomUtilsClass, "TryFindRoom");
	Offsets::GetMainCoords = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(RoomIdentifierClass, "get_MainCoords");
	Offsets::ApplyDamage = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(StandardDamageHandlerClass, "ApplyDamage");
	Offsets::GetTotalDamageDealt = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(StandardDamageHandlerClass, "get_TotalDamageDealt");
	Offsets::GetAbsorbedAhpDamage = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(StandardDamageHandlerClass, "get_AbsorbedAhpDamage");
	Offsets::GetAbsorbedHumeDamage = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(StandardDamageHandlerClass, "get_AbsorbedHumeDamage");
	Offsets::GetDealtHealthDamage = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(StandardDamageHandlerClass, "get_DealtHealthDamage");
	Offsets::GetIsGrounded = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(FirstPersonMovementModuleClass, "get_IsGrounded");
	Offsets::GetVelocity = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(FpcMotorClass , "get_Velocity");
	Offsets::SetVelocity = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(FpcMotorClass, "set_Velocity");
	Offsets::GetMotor = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(FirstPersonMovementModuleClass, "get_Motor");
	Offsets::SetWantsToJump = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(FpcMotorClass, "set_WantsToJump");
	Offsets::GetRoleColor = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(PlayerRoleBaseClass, "get_RoleColor");
	Offsets::IsAlive = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(PlayerRolesUtilsClass, "IsAlive");
	//Offsets::GetBoneTransform = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(AnimatorClass, "GetBoneTransformInternal");
	Offsets::GetBoneTransform = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(AnimatorClass, "GetBoneTransform");
	Offsets::GetAvatar = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(AnimatorClass, "get_avatar");
	Offsets::TryGetOwner = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(PlayerRoleBaseClass, "TryGetOwner");
	Offsets::GetAnimator = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(AnimatedCharacterModelClass, "get_Animator");
	Offsets::GetRole = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(AnimatedCharacterModelClass, "get_Role");
	Offsets::GetIsHuman = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(AvatarClass, "get_isHuman");
	Offsets::GetIsValid = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(AvatarClass, "get_isValid");
	Offsets::FindObjectsByType = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(AvatarClass, "FindObjectsByType");
	Offsets::SetupAnimator = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(AnimatedCharacterModelClass, "SetupAnimator");
	Offsets::HasOwner = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(SubcontrollerBehaviourClass, "get_HasOwner");
	Offsets::GetOwnerHub = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(SubcontrollerBehaviourClass, "get_OwnerHub");
	Offsets::ControllerGetAnimator = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(SubcontrollerBehaviourClass, "get_Animator");
	Offsets::GetModel = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(PlayerRolesUtilsClass, "GetModel");
	Offsets::Linecast = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(UnityEnginePhysicsClass, "Linecast");
	Offsets::IsEnemy = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(HitboxIdentityClass, "IsEnemy");
	Offsets::GetCenterOfMass = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(HitboxIdentityClass, "get_CenterOfMass");
	Offsets::GetHitboxType = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(HitboxIdentityClass, "get_HitboxType");
	Offsets::GetMouseInput = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(FpcMouseLookClass, "GetMouseInput");
	Offsets::SetCurrentHorizontal = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(FpcMouseLookClass, "set_CurrentHorizontal");
	Offsets::SetCurrentVertical = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(FpcMouseLookClass, "set_CurrentVertical");
	Offsets::GetCurrentHorizontal = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(FpcMouseLookClass, "get_CurrentHorizontal");
	Offsets::GetCurrentVertical = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(FpcMouseLookClass, "get_CurrentVertical");
	Offsets::LookRotation = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(QuaternionClass, "LookRotation", 1);
	Offsets::GetEulerAngles = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(QuaternionClass, "get_eulerAngles");
	Offsets::OnPlayerMove = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(AnimatedCharacterModelClass, "OnPlayerMove");
	Offsets::WriteSelf = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(BacktrackClass, "WriteSelf");
	Offsets::RelativePositionConstructor = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer("RelativePositioning.RelativePosition", ".ctor");
	Offsets::RelativePositionConstructorNetworkReader = Offsets::RelativePositionConstructor + 0x4B0;
	Offsets::RelativePositionGetPosition = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(RelativePositionClass, "get_Position");
	Offsets::GetBaseFireRate = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(AutomaticActionModuleClass, "get_BaseFireRate");
	Offsets::WriteShotRequest = Offsets::GetBaseFireRate + 0x229B30; //(uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(AutomaticActionModuleClass, "Write");
	Offsets::ShotRequestConstructor = Offsets::GetBaseFireRate + 0x2298B0;
	Offsets::ServerSendRejection = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(AutomaticActionModuleClass, "ServerSendRejection");
	Offsets::ServerSendResponse = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(AutomaticActionModuleClass, "ServerSendResponse");
	Offsets::ServerOnRequestTimedOut = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(AutomaticActionModuleClass, "ServerOnRequestTimedOut");
	Offsets::GetActionDown = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(SubcomponentBaseClass, "GetActionDown");
	Offsets::SendCmd = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(SubcomponentBaseClass, "SendCmd");
	Offsets::WriteInt = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(NetworkWriterClass, "WriteBlittable<int>");
	Offsets::NetworkWriterConstructor = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(NetworkWriterClass, ".ctor");
	Offsets::NetworkWriterToArraySegment = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(NetworkWriterClass, "ToArraySegment");
	Offsets::NetworkWriterPoolGet = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(NetworkWriterPoolClass, "Get");
	Offsets::NetworkWriterPoolReturn = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(NetworkWriterPoolClass, "Return");
	Offsets::NetworkConnectionSend = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(NetworkConnectionClass, "Send");
	Offsets::AddOutMessageEvent = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(NetworkDiagnosticsClass, "add_OutMessageEvent");
	Offsets::SendToTransport = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(NetworkConnectionToServerClass, "SendToTransport");
	Offsets::BatcherAddMessage = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(BatcherClass, "AddMessage");
	Offsets::NetworkWriterWriteByte = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(NetworkWriterClass, "WriteByte");
	Offsets::PlayerInRange = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(TeslaGateClass, "PlayerInRange");
	Offsets::PlayerInHurtRange = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(TeslaGateClass, "PlayerInHurtRange");
	Offsets::TryGetMainCamera = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(Scp079CameraClass, "TryGetMainCamera");
	Offsets::ClientSwitchTo = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(Scp079CurrentCameraSyncClass, "ClientSwitchTo");
	Offsets::GetSwitchCost = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(Scp079CurrentCameraSyncClass, "GetSwitchCost");
	Offsets::TeslaAbilityConstructor = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(Scp079TeslaAbilityClass, ".ctor");
	Offsets::TeslaAbilityTrigger = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(Scp079TeslaAbilityClass, "Trigger");
	Offsets::TeslaAbilityStart = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(Scp079TeslaAbilityClass, "Start");
	Offsets::TeslaAbilityGetIsReady = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(Scp079TeslaAbilityClass, "get_IsReady");
	Offsets::AbilityBaseGetCurrentCamSync = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(Scp079AbilityBase, "get_CurrentCamSync");
	Offsets::GetFailMessage = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(Scp079AbilityBase, "get_FailMessage");
	Offsets::GetRoleId = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(PlayerRolesUtilsClass, "GetRoleId");
	Offsets::GetCurrentCamera = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(Scp079CurrentCameraSyncClass, "get_CurrentCamera");
	Offsets::DrawRay = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(DebugClass, "DrawRay");
	Offsets::GetForwardRay = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(HitscanHitregModuleBaseClass, "get_ForwardRay");
	Offsets::ColorConstructor = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(ColorClass, ".ctor");
	Offsets::DrawLine = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(DrawableLinesManagerClass, "DrawLine");
	Offsets::CreatePrimitive = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(GameObjectClass, "CreatePrimitive");
	Offsets::GameObjectGetTransform = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(GameObjectClass, "get_transform");
	Offsets::TransformSetPositionAndRotation = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(TransformClass, "SetPositionAndRotation");
	Offsets::RendererGetEnabled = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(RendererClass, "get_enabled");
	Offsets::RendererSetEnabled = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(RendererClass, "set_enabled");
	Offsets::RendererSetMaterial = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(RendererClass, "set_material");
	Offsets::RendererGetMaterial = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(RendererClass, "get_material");
	Offsets::GetDefaultMaterial = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(MaterialClass, "GetDefaultMaterial");
	Offsets::MaterialSetFloat = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(MaterialClass, "SetFloat");
	Offsets::MaterialSetInt = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(MaterialClass, "SetInt");
	Offsets::MaterialSetColor = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(MaterialClass, "set_color");
	Offsets::MaterialConstructor = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(MaterialClass, ".ctor");
	Offsets::ShaderFind = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(ShaderClass, "Find");
	Offsets::ObjectGetName = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(ObjectClass, "GetName");
	Offsets::MaterialSetTexture = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(MaterialClass, "SetTexture");
	Offsets::MaterialGetShader = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(MaterialClass, "get_shader");
	Offsets::MaterialSetRenderQueue = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(MaterialClass, "set_renderQueue");
	Offsets::ShaderGetPropertyCount = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(ShaderClass, "GetPropertyCount");
	Offsets::ShaderGetPropertyName = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(ShaderClass, "GetPropertyName");
	Offsets::QuaternionByEuler = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(QuaternionClass, "Euler");
	Offsets::TransformSetLocalScale = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(TransformClass, "set_localScale");
	Offsets::MaterialGetShaderKeywords = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(MaterialClass, "get_shaderKeywords");
	Offsets::MaterialIsKeywordEnabled = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(MaterialClass, "IsKeywordEnabled");
	Offsets::ObjectDestroy = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(ObjectClass, "Destroy");
	Offsets::TracerBaseFire = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(TracerBaseClass, "Fire");
	Offsets::BulletTracerOnCreated = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(BulletTracerClass, "OnCreated");
	Offsets::HitscanHitregModuleBaseRandomizeRay = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(HitscanHitregModuleBaseClass, "RandomizeRay");
	Offsets::ClientReadImpactDecal = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(ImpactEffectsModuleClass, "ClientReadImpactDecal");
	Offsets::ClientReadPlayerHit = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(ImpactEffectsModuleClass, "ClientReadPlayerHit");
	Offsets::ClientReadTracer = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(ImpactEffectsModuleClass, "ClientReadTracer");
	Offsets::ClientProcessRpcTemplate = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(ImpactEffectsModuleClass, "ClientProcessRpcTemplate");
	Offsets::GetNextMessage = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(UnbatcherClass, "GetNextMessage");
	Offsets::GameObjectGetComponentInChildren = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(GameObjectClass, "GetComponentInChildren");
	Offsets::GameObjectGetComponentInParent = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(GameObjectClass, "GetComponentInParent");
	Offsets::Scp0173TeleportAbilityClientWriteCmd = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(Scp173TeleportAbilityClass, "ClientWriteCmd");
	Offsets::GetEffectiveBlinkDistance = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(Scp173TeleportAbilityClass, "get_EffectiveBlinkDistance");
	Offsets::NetworkWriterWriteReferenceHub = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(ReferenceHubReaderWriterClass, "WriteReferenceHub");
	Offsets::NetworkWriterReset = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(NetworkWriterClass, "Reset");
	Offsets::NetworkWriterWriteQuaternion = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(NetworkWriterExtensionClass, "WriteQuaternion");
	Offsets::NetworkWriterWriteFloat = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(NetworkWriterExtensionClass, "WriteFloat");
	Offsets::RendererGetMaterialArray = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(RendererClass, "GetMaterialArray");
	Offsets::RendererGetSharedMaterialArray = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(RendererClass, "GetSharedMaterialArray");
	Offsets::RendererSetMaterialArray = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(RendererClass, "SetMaterialArray");
	Offsets::ArrayCreateInstance = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(SystemArrayClass, "CreateInstance") + 0x42B0;
	Offsets::ArraySetValue = (uintptr_t)IL2CPP::Class::Utils::GetMethodPointer(SystemArrayClass, "SetValue");
	Offsets::Il2cppObjectNew = (uintptr_t)IL2CPP::UnityAPI::ResolveExport("il2cpp_object_new");
	

	//Functions::TestShit((jaaaSystem_Type_o*)IL2CPP::Class::GetSystemType(NetworkWriterClass));

	SubcontrollerBehaviourSystemType = IL2CPP::Class::GetSystemType(SubcontrollerBehaviourClass);
	CharacterModelSystemType = IL2CPP::Class::GetSystemType(AnimatedCharacterModelClass);
	MeshRendererType = IL2CPP::Class::GetSystemType(MeshRendererClass);
	MaterialType = IL2CPP::Class::GetSystemType(MaterialClass);

	Unity::GameObjectFunctions.m_pGetComponent = (void*)Offsets::GetComponentByName;


#ifdef DEBUG

	console.Log("objectnew", Offsets::Il2cppObjectNew - sdk::GameAssembly);


#endif 

	return true;
}

void EnableHooks() {

	//if (MH_CreateHook(reinterpret_cast<LPVOID*>(Offsets::OnPickupDestroy), &Functions::OnPickupDestroy_hk, (LPVOID*)&Functions::OnPickupDestroy) == MH_OK)
	//{
	//	MH_EnableHook(reinterpret_cast<LPVOID*>(Offsets::OnPickupDestroy));
	//	std::cout << "enabled hook\n";
	//}

	if (MH_CreateHook(reinterpret_cast<LPVOID*>(Offsets::AddOnBeforePickupDestroyed), &Functions::add_OnBeforePickupDestroyed_hk, (LPVOID*)&Functions::add_OnBeforePickupDestroyed) == MH_OK)
	{
		MH_EnableHook(reinterpret_cast<LPVOID*>(Offsets::AddOnBeforePickupDestroyed));
		std::cout << "enabled pickup hook\n";
	}

	if (MH_CreateHook(reinterpret_cast<LPVOID*>(Offsets::ApplyDamage), &Functions::ApplyDamage_hk, (LPVOID*)&Functions::ApplyDamage) == MH_OK)
	{
		MH_EnableHook(reinterpret_cast<LPVOID*>(Offsets::ApplyDamage));
		std::cout << "enabled damage hook\n";
	}

	if (MH_CreateHook(reinterpret_cast<LPVOID*>(Offsets::OnPlayerMove), &Functions::OnPlayerMove_hk, (LPVOID*)&Functions::OnPlayerMove) == MH_OK)
	{
		MH_EnableHook(reinterpret_cast<LPVOID*>(Offsets::OnPlayerMove));
		std::cout << "enabled player move hook\n";
	}

	if (MH_CreateHook(reinterpret_cast<LPVOID*>(Offsets::WriteSelf), &Functions::WriteSelf_hk, (LPVOID*)&Functions::WriteSelf) == MH_OK)
	{
		MH_EnableHook(reinterpret_cast<LPVOID*>(Offsets::WriteSelf));
		std::cout << "enabled write self hook\n";
	}

	if (MH_CreateHook(reinterpret_cast<LPVOID*>(Offsets::WriteShotRequest), &Functions::WriteShotRequest_hk, (LPVOID*)&Functions::WriteShotRequest) == MH_OK)
	{
		MH_EnableHook(reinterpret_cast<LPVOID*>(Offsets::WriteShotRequest));
		console.WriteLine("enabled ShotRequest self hook");
	}

	//if (MH_CreateHook(reinterpret_cast<LPVOID*>(Offsets::Scp0173TeleportAbilityClientWriteCmd), &Functions::Scp173TeleportAbilityClientWriteCmd_hk, (LPVOID*)&Functions::Scp173TeleportAbilityClientWriteCmd) == MH_OK)
	//{
	//	MH_EnableHook(reinterpret_cast<LPVOID*>(Offsets::Scp0173TeleportAbilityClientWriteCmd));
	//	console.WriteLine("enabled teleport hook");
	//}


	//if (MH_CreateHook(reinterpret_cast<LPVOID*>(Offsets::GetNextMessage), &Functions::GetNextMessage_hk, (LPVOID*)&Functions::GetNextMessage) == MH_OK)
	//{
	//	MH_EnableHook(reinterpret_cast<LPVOID*>(Offsets::GetNextMessage));
	//	console.WriteLine("enabled GetNextMessage hook");
	//}

	//if (MH_CreateHook(reinterpret_cast<LPVOID*>(Offsets::RelativePositionConstructorNetworkReader), &Functions::RelativePositionConstructorNetworkReader_hk, (LPVOID*)&Functions::RelativePositionConstructorNetworkReader) == MH_OK)
	//{
	//	MH_EnableHook(reinterpret_cast<LPVOID*>(Offsets::RelativePositionConstructorNetworkReader));
	//	console.WriteLine("enabled Relpos hook");
	//}

	/*
	if (MH_CreateHook(reinterpret_cast<LPVOID*>(Offsets::ClientReadTracer), &Functions::ClientReadTracer_hk, (LPVOID*)&Functions::ClientReadTracer) == MH_OK)
	{
		MH_EnableHook(reinterpret_cast<LPVOID*>(Offsets::ClientReadTracer));
		console.WriteLine("enabled Tracer hook");
	}

	if (MH_CreateHook(reinterpret_cast<LPVOID*>(Offsets::ClientReadPlayerHit), &Functions::ClientReadPlayerHit_hk, (LPVOID*)&Functions::ClientReadPlayerHit) == MH_OK)
	{
		MH_EnableHook(reinterpret_cast<LPVOID*>(Offsets::ClientReadPlayerHit));
		console.WriteLine("enabled Player hook");
	}

	if (MH_CreateHook(reinterpret_cast<LPVOID*>(Offsets::ClientReadImpactDecal), &Functions::ClientReadImpactDecal_hk, (LPVOID*)&Functions::ClientReadImpactDecal) == MH_OK)
	{
		MH_EnableHook(reinterpret_cast<LPVOID*>(Offsets::ClientReadImpactDecal));
		console.WriteLine("enabled decal hook");
	}

	if (MH_CreateHook(reinterpret_cast<LPVOID*>(Offsets::ClientProcessRpcTemplate), &Functions::ClientProcessRpcTemplate_hk, (LPVOID*)&Functions::ClientProcessRpcTemplate) == MH_OK)
	{
		MH_EnableHook(reinterpret_cast<LPVOID*>(Offsets::ClientProcessRpcTemplate));
		console.WriteLine("enabled ClientProcessRpcTemplate hook");
	}
	*/

	//if (MH_CreateHook(reinterpret_cast<LPVOID*>(Offsets::BatcherAddMessage), &Functions::AddMessage_hk, (LPVOID*)&Functions::AddMessage) == MH_OK)
	//{
	//	MH_EnableHook(reinterpret_cast<LPVOID*>(Offsets::BatcherAddMessage));
	//	console.WriteLine("enabled BatcherAddMessage hook");
	//}
	
	//if (MH_CreateHook(reinterpret_cast<LPVOID*>(Offsets::SendToTransport), &Functions::SendToTransport_hk, (LPVOID*)&Functions::SendToTransport) == MH_OK)
	//{
	//	MH_EnableHook(reinterpret_cast<LPVOID*>(Offsets::SendToTransport));
	//	console.WriteLine("enabled SendToTransport hook");
	//}

	//if (MH_CreateHook(reinterpret_cast<LPVOID*>(Offsets::NetworkConnectionSend), &Functions::NetworkConnectionSend_hk, (LPVOID*)&Functions::NetworkConnectionSend) == MH_OK)
	//{
	//	MH_EnableHook(reinterpret_cast<LPVOID*>(Offsets::NetworkConnectionSend));
	//	console.WriteLine("enabled NetworkSend hook");
	//}

	//if (MH_CreateHook(reinterpret_cast<LPVOID*>(Offsets::SetupAnimator), &Functions::SetupAnimator_hk, (LPVOID*)&Functions::SetupAnimator) == MH_OK)
	//{
	//	MH_EnableHook(reinterpret_cast<LPVOID*>(Offsets::SetupAnimator));
	//	std::cout << "enabled animator hook\n";
	//}
}

void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);

	ImGuiStyle* style = &ImGui::GetStyle();
	style->Colors[ImGuiCol_WindowBg] = ImColor(0, 0, 0, 255);
	style->Colors[ImGuiCol_ChildBg] = ImColor(25, 25, 25, 255);
	style->Colors[ImGuiCol_FrameBg] = ImColor(50, 50, 50, 255);
	style->Colors[ImGuiCol_Text] = ImColor(0, 255, 255, 255);
	style->Colors[ImGuiCol_Button] = ImColor(25, 25, 25, 255);
	style->Colors[ImGuiCol_ButtonActive] = ImColor(100, 100, 100, 255);
	style->Colors[ImGuiCol_ButtonHovered] = ImColor(150, 150, 150, 255);
	style->Colors[ImGuiCol_TitleBg] = ImColor(10, 10, 10, 255);
	style->FrameRounding = 50;
	style->WindowBorderSize = 5;
	style->WindowRounding = 5;
	style->WindowPadding = { 20, 20 };
	style->ChildRounding = 5;
}

void RenderBacktrack()
{
	ImGui::SetCursorPos({ 200.f, 40.f });
	ImGui::BeginChild("Backtrack", ImGui::GetContentRegionAvail());
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0);

	ImGui::Checkbox("Enable Backtrack", &vars::backtracking);
	ImGui::SameLine(200.f);
	ImGui::SliderFloat("Backtrack Delay", &backtrack::backtracktime, 0.f, 0.4f);
	ImGui::Checkbox("Render Records", &backtrack::renderRecords);

	ImGui::PopStyleVar();
	ImGui::EndChild();
}

void RenderAimAssist()
{
	ImGui::SetCursorPos({ 200.f, 40.f });
	ImGui::BeginChild("Aim Assist", ImGui::GetContentRegionAvail());
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0);

	ImGui::Checkbox("Enable Aim Assist", &vars::aimbot);
	ImGui::SameLine(200.f);
	ImGui::SetNextItemWidth(200.f);
	ImGui::SliderFloat("Move Time", &aimbot::moveTime, 0.f, 0.5);
	ImGui::Checkbox("Display Target", &aimbot::displayTarget);
	ImGui::SameLine(200.f);
	ImGui::SetNextItemWidth(200.f);
	ImGui::SliderFloat("Drag Force", &aimbot::maxDrag, 0.f, 1.f);
	ImGui::Checkbox("Draw FOV", &aimbot::drawFov);
	ImGui::SameLine(200.f);
	ImGui::SetNextItemWidth(200.f);
	ImGui::InputInt("FOV", &aimbot::fov);

	ImGui::PopStyleVar();
	ImGui::EndChild();
};

void RenderVisuals()
{
	ImGui::SetCursorPos({ 200.f, 40.f });
	ImGui::BeginChild("Visuals", ImGui::GetContentRegionAvail());
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0);

	ImGui::Checkbox("Player ESP", &vars::playerESP);
	ImGui::SameLine(200.f);
	ImGui::Checkbox("Room ESP", &vars::roomESP);
	ImGui::Checkbox("Skeleton ESP", &vars::skeletonESP);
	ImGui::SameLine(200.f);
	ImGui::Checkbox("Render Console", &vars::renderConsole);
	ImGui::Checkbox("Item ESP", &vars::itemESP);

	ImGui::PopStyleVar();
	ImGui::EndChild();
}

void RenderGui()
{
	if (!vars::drawMenu)
		return;

	ImGui::PushFont(resources::indicatorFont);

	float fontHeight = ImGui::CalcTextSize("A").y;
	gui::pop = false;

	ImGui::SetNextWindowPos({ (float)(0.5 * (vars::screen_size.x - gui::menuSize.x)), (float)(0.5 * (vars::screen_size.y - gui::menuSize.y)) });
	ImGui::SetNextWindowSize(gui::menuSize);

	ImGui::Begin("Menu");

	if (ImGui::Button("Aim Assist", { 150.f, fontHeight + 10.f }))
	{
		gui::renderBacktrack = false;
		gui::renderVisuals = false;
		gui::renderAimAssist = !gui::renderAimAssist;
	}


	if (ImGui::Button("Visuals", { 150.f, fontHeight + 10.f }))
	{
		gui::renderBacktrack = false;
		gui::renderAimAssist = false;
		gui::renderVisuals = !gui::renderVisuals;
	}	

	if (ImGui::Button("Backtrack", { 150.f, fontHeight + 10.f }))
	{
		gui::renderVisuals = false;
		gui::renderAimAssist = false;
		gui::renderBacktrack = !gui::renderBacktrack;
	}

	if (gui::renderAimAssist)
		RenderAimAssist();

	if (gui::renderBacktrack)
		RenderBacktrack();

	if (gui::renderVisuals)
		RenderVisuals();

	ImGui::PopFont();
	ImGui::End();

}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProcA(oWndProc, hWnd, uMsg, wParam, lParam);
}

bool init = false;
bool playercaching = false;
bool movmodulecaching = false;
bool itemcaching = false;
bool roundStarted = false;
bool localSpawned = false;

volatile bool crashed = false;
volatile bool getCharacterModelsPoll = false;
volatile bool gotCharacterModels = false;

Unity::il2cppArray<Unity::CComponent*>* characterModelList;

void UpdateTracers()
{
	if (TracerList.size() == 0)
		return;

	for (int i = 0; i < TracerList.size(); i++)
	{
		Tracer* tracer = TracerList[i];

		tracer->livingTime = max(tracer->livingTime - 1, 0);

		if (!tracer->livingTime)
		{
			Functions::ObjectDestroy((UnityEngine_Object_o*)tracer->gameObject, 0.f);
		}
	}
}

void SCP079Electrocute(TeslaGate_o* teslaGate)
{
	PlayerRoles_PlayableScps_Scp079_Cameras_Scp079Camera_o* cam;
	if (!Functions::TryGetMainCamera(teslaGate->fields.Room, &cam))
		return;

	int totalCost = 0;

	auto list = Unity::Object::FindObjectsOfType<PlayerRoles_PlayableScps_Scp079_Scp079TeslaAbility_o>("PlayerRoles.PlayableScps.Scp079.Scp079TeslaAbility");

	PlayerRoles_PlayableScps_Scp079_Scp079TeslaAbility_o* ability = list->At(0);

	if (!Functions::TeslaAbilityGetIsReady(ability))
		return;
	
	auto currentCamSync = Functions::GetCurrentCameraSync((PlayerRoles_PlayableScps_Scp079_Scp079AbilityBase_o*)ability);

	if (currentCamSync == nullptr)
		return;

	totalCost = totalCost + ability->fields._cost;
	totalCost = totalCost + Functions::GetSwitchCost(currentCamSync, cam);

	Functions::ClientSwitchTo(currentCamSync, cam);

}

void SCP079GateTrigger()
{
	TeslaGate_c* teslaGateClass = (TeslaGate_c*)TeslaGateClass;
	auto gates = teslaGateClass->static_fields->AllGates;
	auto slots = gates->fields._slots;

	for (int i = 0; i < slots->max_length; i++)
	{
		auto slot = gates->fields._slots->m_Items[i];
		TeslaGate_o* gate = (TeslaGate_o*)slot.fields.value;

		if (gate == nullptr)
			continue;

		PlayerRoles_PlayableScps_Scp079_Cameras_Scp079Camera_o* cam;
		if (!Functions::TryGetMainCamera(gate->fields.Room, &cam))
			continue;

		if (!cam->fields._isActive)
			continue;

		ReferenceHub_c* referenceHubClass = (ReferenceHub_c*)ReferenceHubClass;
		System_Collections_Generic_Dictionary_GameObject__ReferenceHub__o* hashset = referenceHubClass->static_fields->HubsByGameObjects;

		if (hashset == nullptr)
			return;

		for (int j = 0; j < hashset->fields._count; j++)
		{
			auto entry = hashset->fields._entries->m_Items[j];
			UnityEngine_GameObject_o* gameObject = (UnityEngine_GameObject_o*)entry.fields.key;
			ReferenceHub_o* hub = (ReferenceHub_o*)entry.fields.value;

			if (gameObject == nullptr || hub == nullptr)
				continue;

			if (!Functions::IsEnemy(vars::LocalPlayer, hub))
				continue;

			if (Functions::PlayerInHurtRange(gate, gameObject))
			{
				auto list = Unity::Object::FindObjectsOfType<PlayerRoles_PlayableScps_Scp079_Scp079TeslaAbility_o>("PlayerRoles.PlayableScps.Scp079.Scp079TeslaAbility");

				PlayerRoles_PlayableScps_Scp079_Scp079TeslaAbility_o* ability = list->At(0);

				if (!Functions::TeslaAbilityGetIsReady(ability))
					return;

				Functions::TeslaAbilityTrigger(ability);
			}
		}
	}
}

void SCP079GateFinder()
{
	scp::targetGate = nullptr;
	TeslaGate_c* teslaGateClass = (TeslaGate_c*)TeslaGateClass;
	auto gates = teslaGateClass->static_fields->AllGates;
	auto slots = gates->fields._slots;

	for (int i = 0; i < PlayerList.size(); i++)
	{
		ReferenceHub_o* hub = PlayerList[i];

		if (hub == nullptr)
			continue;

		if (!Functions::IsEnemy(vars::LocalPlayer, hub))
			continue;

		for (int j = 0; j < slots->max_length; j++)
		{
			auto slot = gates->fields._slots->m_Items[j];
			TeslaGate_o* gate = (TeslaGate_o*)slot.fields.value;

			if (gate == nullptr)
				continue;

			if (Functions::PlayerInRange(gate, hub))
				scp::targetGate = gate;
		}
	}

	if (scp::targetGate == nullptr)
		return;

	ImGui::GetBackgroundDrawList()->AddText({ 1600, 800 }, ImColor(255, 0, 255), "Jump To Gate");
}

void UpdateTeslaGate()
{
	if (Functions::GetRoleId(vars::LocalPlayer) != 7)
		return;

	SCP079GateFinder();
	SCP079GateTrigger();

	if (GetAsyncKeyState(VK_NUMPAD0))
	{
		if (scp::targetGate == nullptr)
			return;

		PlayerRoles_PlayableScps_Scp079_Cameras_Scp079Camera_o* cam;
		if (!Functions::TryGetMainCamera(scp::targetGate->fields.Room, &cam))
			return;

		auto list = Unity::Object::FindObjectsOfType<PlayerRoles_PlayableScps_Scp079_Scp079TeslaAbility_o>("PlayerRoles.PlayableScps.Scp079.Scp079TeslaAbility");

		PlayerRoles_PlayableScps_Scp079_Scp079TeslaAbility_o* ability = list->At(0);

		if (!Functions::TeslaAbilityGetIsReady(ability))
			return;

		auto currentCamSync = Functions::GetCurrentCameraSync((PlayerRoles_PlayableScps_Scp079_Scp079AbilityBase_o*)ability);

		if (currentCamSync == nullptr)
			return;

		Functions::ClientSwitchTo(currentCamSync, cam);
	}

	return;


	TeslaGate_c* teslaGateClass = (TeslaGate_c*)TeslaGateClass;
	auto gates = teslaGateClass->static_fields->AllGates;
	auto slots = gates->fields._slots;
	TeslaGate_o* targetGate = nullptr;
	ReferenceHub_c* referenceHubClass = (ReferenceHub_c*)ReferenceHubClass;

	System_Collections_Generic_Dictionary_GameObject__ReferenceHub__o* hashset = referenceHubClass->static_fields->HubsByGameObjects;

	if (hashset == nullptr)
		return;

	for (int i = 0; i < hashset->fields._count; i++)
	{
		auto entry = hashset->fields._entries->m_Items[i];
		UnityEngine_GameObject_o* gameObject = (UnityEngine_GameObject_o*)entry.fields.key;
		ReferenceHub_o* hub = (ReferenceHub_o*)entry.fields.value;

		if (gameObject == nullptr || hub == nullptr)
			continue;

		if (!Functions::IsEnemy(vars::LocalPlayer, hub))
			continue;

		for (int j = 0; j < slots->max_length; j++)
		{
			auto slot = gates->fields._slots->m_Items[j];
			TeslaGate_o* gate = (TeslaGate_o*)slot.fields.value;

			if (gate == nullptr)
				continue;

			if (Functions::PlayerInHurtRange(gate, gameObject))
				targetGate = gate;
		}		
	}

	if (targetGate == nullptr)
		return;

	console.WriteLine("Electrocuting");

	SCP079Electrocute(targetGate);
}

void UpdateUltraRapidFire()
{
	if (!vars::ultraRapidFire)
		return;

	InventorySystem_Items_Firearms_Firearm_o* firearm;

	if (!Functions::HasFirearmEquipped(&firearm))
	{
		ultraRapidFire::equippedFirearm = nullptr;
		return;
	}
	
	// on new chargeup
	if (firearm != ultraRapidFire::equippedFirearm)
	{
		ultraRapidFire::equippedFirearm = firearm;
		ultraRapidFire::lastWeaponEquipped = std::chrono::system_clock::now();
		ultraRapidFire::chargedShots = 0;
		ultraRapidFire::weaponCooldown = Functions::GetWeaponCooldown(firearm);
	}
		
	// chargeup

}

void UpdateBacktrackRecords()
{
	for (int i = 0; i < BacktrackRecordList.size(); i++)
	{
		BacktrackRecord* record = BacktrackRecordList[i];

		std::chrono::duration<double> elapsed = std::chrono::system_clock::now() - record->creationStamp;
		record->age = elapsed.count();

		if (record->age > backtrack::backtracktime || record->deprecated)
		{
			auto s = std::find(BacktrackRecordList.begin(), BacktrackRecordList.end(), record);
			if (s != BacktrackRecordList.end()) BacktrackRecordList.erase(s);
			delete record->relativePosition;
			delete record;
			i--;
			continue;
		}
	}
}

void ScpGetBestTarget()
{
	auto localPosition = Functions::GetPosition(vars::LocalPlayer->fields.PlayerCameraReference);

	scp::bestTarget = nullptr;
	scp::bestTargetDistance = 10000;

	for (int i = 0; i < PlayerList.size(); i++)
	{
		ReferenceHub_o* hub = PlayerList[i];

		if (!Functions::IsEnemy(vars::LocalPlayer, hub))
			continue;

		auto hubPosition = Functions::GetPosition(hub->fields.PlayerCameraReference);

		if (!Functions::InLineOfSight(vars::LocalPlayer, hubPosition))
			continue;

		float distance = Functions::GetDistance(localPosition, hubPosition);

		if (distance < scp::bestTargetDistance)
		{
			scp::bestTarget = hub;
			scp::bestTargetDistance = distance;
		}
	}
}

void UpdateScp()
{
	if (Functions::GetTeam(vars::LocalPlayer) != 0)
		return;

	ScpGetBestTarget();
	UpdateTeslaGate();

}

void RenderBacktrackRecords()
{
	if (!vars::backtracking)
		return;

	if (!backtrack::renderRecords)
		return;

	for (int i = 0; i < BacktrackRecordList.size(); i++)
	{
		BacktrackRecord* record = BacktrackRecordList[i];

		Vector2 pos1;
		Vector2 pos2;

		if (!Functions::worldtoscreen(record->headPosition, pos1))
			continue;

		if (!Functions::worldtoscreen(record->footPosition, pos2))
			continue;

		ImGui::GetBackgroundDrawList()->AddLine({ pos1.x, pos1.y }, { pos2.x, pos2.y }, colors::backtrackRecord, 2);
	}
}

void GetRooms()
{
	MapGeneration_RoomIdentifier_c* roomIdentifierClass = (MapGeneration_RoomIdentifier_c*)RoomIdentifierClass;
	UnityEngine_Vector3_o scale = roomIdentifierClass->static_fields->GridScale;

	for (int i = 0; i < sizeof(settings::roomIDs) / sizeof(int); i++)
	{

		System_Nullable_RoomName__o name;
		System_Nullable_FacilityZone__o zone;
		System_Nullable_RoomShape__o shape;
		MapGeneration_RoomIdentifier_o* foundRoom;

		name.fields.hasValue = true;
		name.fields.value = settings::roomIDs[i];
		zone.fields.hasValue = false;
		zone.fields.value = 0;
		shape.fields.hasValue = false;
		shape.fields.value = 0;

		if (!Functions::TryFindRoom(name, zone, shape, &foundRoom))
		{
			continue;
		}

		UnityEngine_Vector3_o buffer;
		auto position = Functions::GetMainCoords(foundRoom);



		buffer.fields.x = position.fields.m_X * scale.fields.x;
		buffer.fields.y = position.fields.m_Y * scale.fields.y;
		buffer.fields.z = position.fields.m_Z * scale.fields.z;

		Room* room = new Room;
		room->name = settings::roomNames[i];
		room->position = buffer;

		RoomList.push_back(room);
	}
}

void RenderBoneESP()
{
	if (!vars::skeletonESP)
		return;

	for (int i = 0; i < PlayerList.size(); i++)
	{
		__try
		{
			ReferenceHub_o* hub = PlayerList[i];

			if (hub == nullptr)
				continue;

			if (Functions::IsPOV(hub))
				continue;

			PlayerRoles_FirstPersonControl_Thirdperson_AnimatedCharacterModel_o* characterModel = (PlayerRoles_FirstPersonControl_Thirdperson_AnimatedCharacterModel_o*)Functions::GetModel(hub);

			if (characterModel == nullptr)
				continue;

			UnityEngine_Animator_o* animator = Functions::GetAnimator(characterModel);

			if (animator == nullptr)
				continue;

			UnityEngine_Avatar_o* avatar = Functions::GetAvatar(animator);

			if (avatar == nullptr) continue;
			if (!Functions::GetIsValid(avatar)) continue;
			if (!Functions::GetIsHuman(avatar)) continue;

			for (int j = 0; j < sizeof(vars::skeleton) / sizeof(vars::skeleton[0]); j++)
			{
				int boneID1 = vars::skeleton[j][0];
				int boneID2 = vars::skeleton[j][1];
				auto trans1 = Functions::GetBoneTransform(animator, boneID1);
				auto trans2 = Functions::GetBoneTransform(animator, boneID2);

				if (trans1 == nullptr) continue;
				if (trans2 == nullptr) continue;

				auto position1 = Functions::GetPosition(trans1);
				auto position2 = Functions::GetPosition(trans2);

				Vector2 pos1;
				Vector2 pos2;
				if (!Functions::worldtoscreen(position1, pos1)) continue;
				if (!Functions::worldtoscreen(position2, pos2)) continue;

				ImColor color = colors::skeleton;

				if (Functions::InLineOfSight(vars::LocalPlayer, position1) && Functions::InLineOfSight(vars::LocalPlayer, position2))
					color = colors::skeletonCanSee;

				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos1.x, pos1.y), ImVec2(pos2.x, pos2.y), color, 1);
			}
		}

		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			continue;
		}
	}
}

void OnRoundStart()
{
	GetRooms();
}

void CleanUp()
{
	vars::movementModule = NULL;

	if (RoomList.size() > 0)
	{
		for (int i = 0; i < RoomList.size(); i++)
		{
			delete RoomList[i];
		}

		RoomList.clear();
	}
}

void PocketExits()
{
	PocketDimensionTeleport_c* teleportClass = (PocketDimensionTeleport_c*)PocketDimensionTeleportClass;
	System_Collections_Generic_HashSet_PocketDimensionTeleport__o* allInstances = teleportClass->static_fields->AllInstances;

	if (allInstances == nullptr)
	{
		std::cout << "nullptr\n";
		return;
	}

	auto slots = allInstances->fields._slots;

	for (int i = 0; i < allInstances->fields._lastIndex; i++)
	{
		auto slot = slots->m_Items[i];
		if (slot.fields.hashCode >= 0 && slot.fields.value != nullptr)
		{
			PocketDimensionTeleport_o* teleport = reinterpret_cast<PocketDimensionTeleport_o*>(slot.fields.value);

			if (teleport == nullptr)
			{
				std::cout << i << " nullptr\n";
				continue;
			}
			
			std::cout << i << "i: " << teleport->fields._type << "\n";

			if (teleport->fields._type)
			{
				UnityEngine_Vector3_o position = Functions::GetPosition(Functions::GetTransform((UnityEngine_Component_o*)teleport));

				Vector2 pos;
				if (!Functions::worldtoscreen(position, pos)) continue;

				ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x, pos.y - 20), colors::room, "Exit");
			}
		}
	}
}

void ApplyChams()
{
	return;

	if (!vars::chams)
		return;

	if (PlayerList.size() <= 0)
		return;

	UnityEngine_Shader_o* shader = Functions::ShaderFind((System_String_o*)IL2CPP::String::New("Hidden/Internal-Colored"));
	
	for (int i = 0; i < PlayerList.size(); i++)
	{
		ReferenceHub_o* hub = PlayerList[i];

		if (hub == nullptr)
			continue;

		if (!Functions::IsAlive(hub))
			continue;


		//UnityEngine_Color_o* visColor = new UnityEngine_Color_o;
		//Functions::ColorConstructor(visColor, 1.f, 1.f, 1.f, 1.f);

		auto color = Functions::GetTeamColor(hub);
		UnityEngine_Color_o* visColor = new UnityEngine_Color_o;
		Functions::ColorConstructor(visColor, color.Value.x, color.Value.y, color.Value.z, 0.2f);

		UnityEngine_Material_o* visibleMaterial = (UnityEngine_Material_o*)Functions::Il2cppObjectNew(MaterialClass);
		Functions::MaterialConstructor(visibleMaterial, shader);
		Functions::MaterialSetRenderQueue(visibleMaterial, 3000);
		Functions::MaterialSetColor(visibleMaterial, *visColor);


		UnityEngine_Color_o* testColor = new UnityEngine_Color_o;
		Functions::ColorConstructor(testColor, color.Value.x, color.Value.y, color.Value.z, 0.2f);
		UnityEngine_Material_o* testMaterial = (UnityEngine_Material_o*)Functions::Il2cppObjectNew(MaterialClass);
		Functions::MaterialConstructor(testMaterial, shader);
		Functions::MaterialSetRenderQueue(testMaterial, 3000);
		Functions::MaterialSetColor(testMaterial, *testColor);

		/*
		UnityEngine_Color_o* wallColor = new UnityEngine_Color_o;
		Functions::ColorConstructor(wallColor, color.Value.x, color.Value.y, color.Value.z, 0.2f);
		UnityEngine_Material_o* wallMaterial = (UnityEngine_Material_o*)Functions::Il2cppObjectNew(MaterialClass);
		Functions::MaterialConstructor(wallMaterial, shader);
		Functions::MaterialSetInt(wallMaterial, (System_String_o*)IL2CPP::String::New("_ZWrite"), 0);
		Functions::MaterialSetInt(wallMaterial, (System_String_o*)IL2CPP::String::New("_ZTest"), 8);
		Functions::MaterialSetRenderQueue(wallMaterial, 3000);
		Functions::MaterialSetColor(wallMaterial, *wallColor);
		*/

		auto model = Functions::GetModel(hub);

		if (model == nullptr)
			continue;


		auto renderers = model->fields._renderers;

		if (renderers == nullptr)
			continue;

		for (int j = 0; j < renderers->max_length; j++)
		{
			auto renderer = renderers->m_Items[j];
			if (renderer == nullptr)
				continue;

			auto mats = (UnityEngine_Material_array*)Functions::ArrayCreateInstance((System_Type_o*)MaterialType, 2);
			/*
			Il2CppObject** items = (Il2CppObject**)((uintptr_t)mats + sizeof(Il2CppObject) + sizeof(Il2CppArrayBounds*) + sizeof(il2cpp_array_size_t));
			items[0] = (Il2CppObject*)visibleMaterial;
			items[1] = (Il2CppObject*)wallMaterial;
			*/

			//mats->m_Items[1] = visibleMaterial;
			mats->m_Items[0] = testMaterial;

			Functions::RendererSetMaterialArray(renderer, (UnityEngine_Material_array*)mats, 1);

			console.WriteLine("got it");
		}
	}
}

void Player_Cache()
{
	while (true)
	{
		Sleep(1000);

		if (!vars::initil2cpp) continue;

		if (!Functions::GetRoundStarted())
		{
			roundStarted = false;
			CleanUp();
			continue;
		}
		if (!roundStarted)
		{
			roundStarted = true;
			OnRoundStart();
		}

		vars::HostHub = Functions::GetHostHub();
		if (vars::HostHub == nullptr) continue;
		vars::LocalPlayer = Functions::GetLocalHub();
		if (vars::LocalPlayer == nullptr) continue;
	

		void* m_pThisThread = IL2CPP::Thread::Attach(IL2CPP::Domain::Get());
		PlayerList.clear();
		System_Collections_Generic_HashSet_ReferenceHub__o* hashset = Functions::GetAllHubs();

		if (hashset == nullptr) continue;

		auto slots = hashset->fields._slots;

		for (int i = 0; i < hashset->fields._lastIndex; i++)
		{
			auto slot = slots->m_Items[i];
			if (slot.fields.hashCode >= 0 && slot.fields.value != nullptr)
			{
				ReferenceHub_o* hub = reinterpret_cast<ReferenceHub_o*>(slot.fields.value);

				if (hub == vars::LocalPlayer)
				{
					continue;
				}

				PlayerList.push_back(hub);
			}
		}
		

		IL2CPP::Thread::Detach(m_pThisThread);
	}
}

void RenderPlayerESP()
{

	if (!vars::playerESP)
		return;

	if (PlayerList.size() <= 0)
		return;

	UnityEngine_Vector3_o localPosition = Functions::GetPosition(vars::LocalPlayer->fields.PlayerCameraReference);

	for (int i = 0; i < PlayerList.size(); i++)
	{
		ReferenceHub_o* currentHub = PlayerList[i];

		if (currentHub == nullptr) continue;
		if (Functions::IsHost(currentHub)) continue;

		UnityEngine_Vector3_o playerPosition = Functions::GetPosition(currentHub->fields.PlayerCameraReference);
		PlayerRoles_PlayerRoleBase_o* roleBase = currentHub->fields.roleManager->fields._curRole;

		char team = *((char*)roleBase + 0xD1); // teamObject.fields.value__;
		//UnityEngine_Color_o UEColor = *((UnityEngine_Color_o*)roleBase + 0xD4);
		
		float distance = Functions::GetDistance(localPosition, playerPosition);		
		ImColor color = ImColor(255, 255, 255, 255);
		Vector2 pos;
		if (!Functions::worldtoscreen(playerPosition, pos)) continue;

		if (distance > 20000) continue;
		
		switch (team)
		{
		case 0:
			color = colors::scp;
			break;
		case 1:
			color = colors::mtf;
			break;
		case 2:
			color = colors::chaos;
			break;
		case 3:
			color = colors::scientist;
			break;
		case 4:
			color = colors::classd;
			break;
		}
		
		std::string name = Functions::SystemStringOToString(Functions::GetDisplayName(currentHub->fields.nicknameSync));

		//ImGui::GetBackgroundDrawList()->AddLine(ImVec2(vars::screen_center.x, vars::screen_size.y + 5), ImVec2(pos.x, pos.y), color, 1.5f);
		ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x, pos.y - 20), color, name.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x, pos.y - 10), color, std::to_string(float(std::ceil(distance * 100) / 100)).c_str());
	}
}

void RenderItemESP()
{
	if (!vars::itemESP)
		return;

	if (ItemList.size() <= 0)
		return;
	
	UnityEngine_Vector3_o localPosition = Functions::GetPosition(vars::LocalPlayer->fields.PlayerCameraReference);
	for (int i = 0; i < ItemList.size(); i++)
	{
		InventorySystem_Items_Pickups_ItemPickupBase_o* item = ItemList[i];

		if (vars::pauseitem) break;
		if (item == nullptr) continue;

		UnityEngine_Vector3_o itemPosition = Functions::PickupGetPosition(item);
		Vector2 pos;
		ImColor color = ImColor(255, 255, 255, 255);
		float distance = Functions::GetDistance(itemPosition, localPosition);

		if (!Functions::worldtoscreen(itemPosition, pos)) continue;
		if (distance > 100) continue;

		auto texture = resources::ItemTypeToTexture(item->fields.Info.fields.ItemId);
		if (texture == nullptr) continue;
		ImVec2 size = { 50, 50 };
		ImGui::GetBackgroundDrawList()->AddImage(texture, { pos.x, pos.y }, { pos.x + size.x, pos.y + size.y });
	}
}

void RenderRoomESP()
{
	if (!vars::roomESP)
		return;

	if (RoomList.size() <= 0)
		return;
	
	UnityEngine_Vector3_o localPosition = Functions::GetPosition(vars::LocalPlayer->fields.PlayerCameraReference);
	for (int i = 0; i < RoomList.size(); i++)
	{
		Room* room = RoomList[i];
		float distance = Functions::GetDistance(room->position, localPosition);
		Vector2 pos;

		if (!Functions::worldtoscreen(room->position, pos)) continue;
		if (distance > 200) continue;

		ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x, pos.y), colors::room, room->name);
	}
}

void RenderIndicators()
{
	if (IndicatorList.size() <= 0)
	
	for (int i = 0; i < IndicatorList.size(); i++)
	{
		Indicator* indicator = IndicatorList.at(i);
		ImColor color = ImColor(255, 0, 0, 255);

		switch (indicator->type)
		{
		case hume:
			color = colors::hume;
			break;
		case ahp:
			color = colors::ahp;
			break;
		case health:
			color = colors::health;
			break;
		}

		indicator->livingTime--;
		if (indicator->livingTime <= 0)
		{
			auto s = std::find(IndicatorList.begin(), IndicatorList.end(), indicator);
			if (s != IndicatorList.end()) IndicatorList.erase(s);
			delete indicator;
			continue;
		}

		Vector2 pos;
		if (!Functions::worldtoscreen(indicator->position, pos)) continue;
		ImGui::PushFont(resources::indicatorFont);
		ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x, pos.y), color, std::to_string(indicator->amount).c_str());
		ImGui::PopFont();
	}
}

void AutoBunnyHop()
{
	if (vars::movementModule == nullptr)
		return;

	if (movmodulecaching)
		return;

	if (GetAsyncKeyState(VK_SPACE))
	{
		Functions::SetWantsToJump(Functions::GetMotor(vars::movementModule), true);
	}
	else
	{
		Functions::SetWantsToJump(Functions::GetMotor(vars::movementModule), false);
	}
}

void Aimbot()
{
	if (!vars::aimbot)
		return;

	if (aimbot::drawFov)
		ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(vars::screen_center.x, vars::screen_center.y), aimbot::fov, ImColor(255, 255, 255, 255), 120);

	if (PlayerList.size() <= 0)
		return;

	UnityEngine_Vector3_o localPlayerPosition = Functions::GetPosition(vars::LocalPlayer->fields.PlayerCameraReference);
	ReferenceHub_o* targetHub = nullptr;
	int targetHubDistance = 9999;

	for (int i = 0; i < PlayerList.size(); i++)
	{
		ReferenceHub_o* hub = PlayerList[i];

		if (hub == nullptr)
			continue;

		if (!aimbot::friendlyFireActive && !Functions::IsEnemy(vars::LocalPlayer, hub))
			continue;

		UnityEngine_Vector3_o targetPosition = Functions::GetPosition(hub->fields.PlayerCameraReference);
		Vector2 pos;

		if (Functions::GetDistance(localPlayerPosition, targetPosition) > aimbot::range)
			continue;

		if (!Functions::worldtoscreen(targetPosition, pos))
			continue;

		int currentHubDistance = Functions::GetScreenDistance(vars::screen_center, pos);

		if (targetHubDistance < currentHubDistance)
			continue;

		targetHub = hub;
		targetHubDistance = currentHubDistance;
	}

	if (targetHub == nullptr)
		return;

	auto characterModel = Functions::GetModel(targetHub);
	auto hitboxes = characterModel->fields.Hitboxes;

	HitboxIdentity_o* targetHitbox = nullptr;
	UnityEngine_Vector3_o targetHitboxPosition;
	Vector2 targetHitboxScreenPosition;
	int targetHitboxPriority = 999;
	int targetHitboxDistance = 0;

	for (int j = 0; j < hitboxes->max_length; j++)
	{
		HitboxIdentity_o* currentHitbox = hitboxes->m_Items[j];

		UnityEngine_Vector3_o currentHitboxPosition = Functions::GetCenterOfMass(currentHitbox);
		Vector2 screenPositon;

		if (!Functions::worldtoscreen(currentHitboxPosition, screenPositon))
			continue;

		float currentHitboxDistance = Functions::GetScreenDistance(vars::screen_center, screenPositon);

		if (currentHitboxDistance > aimbot::fov)
			continue;

		int currentHitboxPriority = aimbot::hitboxPriority[Functions::GetHitboxType(currentHitbox)];

		if (currentHitboxPriority > targetHitboxPriority)
			continue;

		if (currentHitboxPriority < targetHitboxPriority)
		{
			targetHitbox = currentHitbox;
			targetHitboxPosition = currentHitboxPosition;
			targetHitboxScreenPosition = screenPositon;
			targetHitboxPriority = currentHitboxPriority;
			targetHitboxDistance = currentHitboxDistance;
			continue;
		}

		if (targetHitboxDistance < currentHitboxDistance)
			continue;

		targetHitbox = currentHitbox;
		targetHitboxScreenPosition = screenPositon;
		targetHitboxPosition = currentHitboxPosition;
		targetHitboxDistance = currentHitboxDistance;
	}

	if (targetHitbox == nullptr)
		return;

	if (aimbot::displayTarget)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(vars::screen_center.x, vars::screen_center.y), ImVec2(targetHitboxScreenPosition.x, targetHitboxScreenPosition.y),
			aimbot::targetColor, aimbot::targetThickness);

	auto mouseLook = ((PlayerRoles_FirstPersonControl_FpcMouseLook_c*)(FpcMouseLookClass))->static_fields->_localInstance;

	if (mouseLook == nullptr)
		return;

	float hrot;
	float vrot;

	Functions::GetMouseInput(mouseLook, &hrot, &vrot);

	if (!hrot && !vrot)
		return;

	int directionx = targetHitboxScreenPosition.x - vars::screen_center.x;
	int directiony = vars::screen_center.x - targetHitboxScreenPosition.y;

	if (signbit(directionx) != signbit(hrot) && abs(hrot) > aimbot::maxDrag)
		return;

	if (signbit(directiony) != signbit(vrot) && abs(vrot) > aimbot::maxDrag)
		return;

	UnityEngine_Vector3_o direction;
	direction.fields.x = targetHitboxPosition.fields.x - localPlayerPosition.fields.x;
	direction.fields.y = targetHitboxPosition.fields.y - localPlayerPosition.fields.y;
	direction.fields.z = targetHitboxPosition.fields.z - localPlayerPosition.fields.z;

	if (direction.fields.x == 0 && direction.fields.z == 0)
		return;

	UnityEngine_Vector3_o normDirection = Functions::Normalize(direction);
	UnityEngine_Quaternion_o quaternion = Functions::LookRotation(normDirection);
	UnityEngine_Vector3_o eulerAngles = Functions::GetEulerAngles(quaternion);

	float currentYaw = Functions::GetCurrentHorizontal(mouseLook);
	float currentPitch = Functions::GetCurrentVertical(mouseLook);

	float yawDifference = eulerAngles.fields.y - currentYaw;
	float pitchDifference = -eulerAngles.fields.x - currentPitch;

	float yawStep = min(abs(yawDifference), aimbot::moveTime) * (signbit(yawDifference) * -2 + 1);
	float pitchStep = min(abs(pitchDifference), aimbot::moveTime) * (signbit(pitchDifference) * -2 + 1);

	float yaw = currentYaw + yawStep;
	float pitch = currentPitch + pitchStep;

	Functions::SetCurrentHorizontal(mouseLook, yaw);
	Functions::SetCurrentVertical(mouseLook, pitch);
}

void renderloop()
{

	if (!vars::initil2cpp)
		return;

	if (vars::renderConsole)
		console.RenderConsole();

	gui::inputCooldown = max(0, gui::inputCooldown - 1);

	if (GetAsyncKeyState(VK_RSHIFT))
	{
		if (gui::inputCooldown)
			return;

		vars::drawMenu = !vars::drawMenu;
		gui::inputCooldown = 20;
	}

	RenderGui();

	if (!Functions::GetRoundStarted()) return;
	if (vars::HostHub == nullptr) return;
	if (vars::LocalPlayer == nullptr) return;

	if (GetAsyncKeyState(VK_NUMPAD1))
	{
		auto mouseLook = ((PlayerRoles_FirstPersonControl_FpcMouseLook_c*)(FpcMouseLookClass))->static_fields->_localInstance;

		auto pos = Functions::GetPosition(vars::LocalPlayer->fields.PlayerCameraReference);

		std::cout << "pitch: " << Functions::GetCurrentVertical(mouseLook) << "\n";
	}

	if (GetAsyncKeyState(VK_NUMPAD3))
	{
		console.WriteLine("closed");
		console.file.close();
	}

	if (GetAsyncKeyState(VK_NUMPAD4))
	{
	}

	if (GetAsyncKeyState(VK_NUMPAD5))
		console.Clear();

	UpdateScp();
	UpdateBacktrackRecords();
	UpdateTracers();

	Aimbot();
	RenderBacktrackRecords();
	RenderBoneESP();
	RenderPlayerESP();
	RenderItemESP();
	RenderRoomESP();
	//RenderIndicators();
	//AutoBunnyHop();
}

bool LoadImagek(unsigned char* image, size_t image_size, ID3D11ShaderResourceView** result)
{
	D3DX11_IMAGE_LOAD_INFO information;
	ID3DX11ThreadPump* thread = nullptr;

	auto hres = D3DX11CreateShaderResourceViewFromMemory(pDevice, (LPCWSTR)image, image_size, &information, thread, result, 0);

	if (hres != S_OK)
	{
		std::cout << "texture fucked up" << hres << "\n";
	}

	return (hres == S_OK);
}

void LoadResources()
{
	ImGuiIO& io = ImGui::GetIO();
	resources::indicatorFont = io.Fonts->AddFontFromFileTTF("C:\\Users\\\\AppData\\Local\\Microsoft\\Windows\\Fonts\\ARLRDBD.TTF", 20);
	console.Init(io);

	if (resources::indicatorFont == NULL)
	{
		std::cout << "font failed\n";
	}

	LoadImagek(KeycardJanitor, sizeof(KeycardJanitor), &resources::KeycardJanitor);
	LoadImagek(KeycardScientist, sizeof(KeycardScientist), &resources::KeycardScientist);
	LoadImagek(KeycardResearchCoordinator, sizeof(KeycardResearchCoordinator), &resources::KeycardResearchCoordinator);
	LoadImagek(KeycardZoneManager, sizeof(KeycardZoneManager), &resources::KeycardZoneManager);
	LoadImagek(KeycardGuard, sizeof(KeycardGuard), &resources::KeycardGuard);
	LoadImagek(KeycardMTFPrivate, sizeof(KeycardMTFPrivate), &resources::KeycardMTFPrivate);
	LoadImagek(KeycardContainmentEngineer, sizeof(KeycardContainmentEngineer), &resources::KeycardContainmentEngineer);
	LoadImagek(KeycardMTFOperative, sizeof(KeycardMTFOperative), &resources::KeycardMTFOperative);
	LoadImagek(KeycardMTFCaptian, sizeof(KeycardMTFCaptian), &resources::KeycardMTFCaptian);
	LoadImagek(KeycardFacilityManager, sizeof(KeycardFacilityManager), &resources::KeycardFacilityManager);
	LoadImagek(KeycardChaosInsurgency, sizeof(KeycardChaosInsurgency), &resources::KeycardChaosInsurgency);
	LoadImagek(KeycardO5, sizeof(KeycardO5), &resources::KeycardO5);
	LoadImagek(Radio, sizeof(Radio), &resources::Radio);
	LoadImagek(GunCOM15, sizeof(GunCOM15), &resources::GunCOM15);
	LoadImagek(Medkit, sizeof(Medkit), &resources::Medkit);
	LoadImagek(Flashlight, sizeof(Flashlight), &resources::Flashlight);
	LoadImagek(MicroHID, sizeof(MicroHID), &resources::MicroHID);
	LoadImagek(SCP500, sizeof(SCP500), &resources::SCP500);
	LoadImagek(SCP207, sizeof(SCP207), &resources::SCP207);
	LoadImagek(Ammo12gauge, sizeof(Ammo12gauge), &resources::Ammo12gauge);
	LoadImagek(GunE11SR, sizeof(GunE11SR), &resources::GunE11SR);
	LoadImagek(GunCrossvec, sizeof(GunCrossvec), &resources::GunCrossvec);
	LoadImagek(Ammo556x45, sizeof(Ammo556x45), &resources::Ammo556x45);
	LoadImagek(GunFSP9, sizeof(GunFSP9), &resources::GunFSP9);
	LoadImagek(GunLogicer, sizeof(GunLogicer), &resources::GunLogicer);
	LoadImagek(GrenadeHE, sizeof(GrenadeHE), &resources::GrenadeHE);
	LoadImagek(GrenadeFlash, sizeof(GrenadeFlash), &resources::GrenadeFlash);
	LoadImagek(Ammo44cal, sizeof(Ammo44cal), &resources::Ammo44cal);
	LoadImagek(Ammo762x39, sizeof(Ammo762x39), &resources::Ammo762x39);
	LoadImagek(Ammo9x19, sizeof(Ammo9x19), &resources::Ammo9x19);
	LoadImagek(GunCOM18, sizeof(GunCOM18), &resources::GunCOM18);
	LoadImagek(SCP018, sizeof(SCP018), &resources::SCP018);
	LoadImagek(SCP268, sizeof(SCP268), &resources::SCP268);
	LoadImagek(Adrenaline, sizeof(Adrenaline), &resources::Adrenaline);
	LoadImagek(Painkillers, sizeof(Painkillers), &resources::Painkillers);
	LoadImagek(Coin, sizeof(Coin), &resources::Coin);
	LoadImagek(ArmorLight, sizeof(ArmorLight), &resources::ArmorLight);
	LoadImagek(ArmorCombat, sizeof(ArmorCombat), &resources::ArmorCombat);
	LoadImagek(ArmorHeavy, sizeof(ArmorHeavy), &resources::ArmorHeavy);
	LoadImagek(GunRevolver, sizeof(GunRevolver), &resources::GunRevolver);
	LoadImagek(GunAK, sizeof(GunAK), &resources::GunAK);
	LoadImagek(GunShotgun, sizeof(GunShotgun), &resources::GunShotgun);
	LoadImagek(SCP330, sizeof(SCP330), &resources::SCP330);
	LoadImagek(SCP2176, sizeof(SCP2176), &resources::SCP2176);
	LoadImagek(SCP244a, sizeof(SCP244a), &resources::SCP244a);
	LoadImagek(SCP244b, sizeof(SCP244b), &resources::SCP244b);
	LoadImagek(SCP1853, sizeof(SCP1853), &resources::SCP1853);
	LoadImagek(ParticleDisruptor, sizeof(ParticleDisruptor), &resources::ParticleDisruptor);
	LoadImagek(GunCOM45, sizeof(GunCOM45), &resources::GunCOM45);
	LoadImagek(SCP1576, sizeof(SCP1576), &resources::SCP1576);
	LoadImagek(Jailbird, sizeof(Jailbird), &resources::Jailbird);
	LoadImagek(AntiSCP207, sizeof(AntiSCP207), &resources::AntiSCP207);
	LoadImagek(GunFRMG0, sizeof(GunFRMG0), &resources::GunFRMG0);
	LoadImagek(GunA7, sizeof(GunA7), &resources::GunA7);
	LoadImagek(Lantern, sizeof(Lantern), &resources::Lantern);
	LoadImagek(SCP1344, sizeof(SCP1344), &resources::SCP1344);
	LoadImagek(SurfaceAccessPass, sizeof(SurfaceAccessPass), &resources::SurfaceAccessPass);
	LoadImagek(GunSCP127, sizeof(GunSCP127), &resources::GunSCP127);

}


HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	void* m_pThisThread = IL2CPP::Thread::Attach(IL2CPP::Domain::Get());

	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			ImGui::GetIO().Fonts->AddFontDefault();
			ImFontConfig font_cfg;
			font_cfg.GlyphExtraSpacing.x = 1.2;
			gameFont = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(TTSquaresCondensedBold, 14, 14, &font_cfg);
			ImGui::GetIO().Fonts->AddFontDefault();
			LoadResources();
			// Grab A shader Here If You want
			init = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}

	pContext->RSGetViewports(&vars::vps, &vars::viewport);
	vars::screen_size = { vars::viewport.Width, vars::viewport.Height };
	vars::screen_center = { vars::viewport.Width / 2.0f, vars::viewport.Height / 2.0f };

	auto begin_scene = [&]() {
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	};

	auto end_scene = [&]() {
		ImGui::Render();
	};

	begin_scene();

	auto isFrames = ImGui::GetFrameCount();

	POINT mousePos;
	GetCursorPos(&mousePos);
	ScreenToClient(window, &mousePos);


	// Render
	try
	{
		renderloop();
	}
	catch (...) {}

	end_scene();

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	IL2CPP::Thread::Detach(m_pThisThread);

	return oPresent(pSwapChain, SyncInterval, Flags);
}



void initchair()
{
#ifdef DEBUG
	// if using melonloader console is already created
	//system("cls");
#endif // DEBUG
	CreateConsole();
	initvars();
	find_sigs();
	EnableHooks();
	//IL2CPP::Callback::Initialize();
	kiero::bind(8, (void**)&oPresent, hkPresent);
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Player_Cache, NULL, NULL, NULL);
	//CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)UnsafeBullShit, NULL, NULL, NULL);
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{
	bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			initchair();
			init_hook = true;
			vars::initil2cpp = true;
		}
	} while (!init_hook);
	return TRUE;
}



BOOL WINAPI DllMain(HMODULE mod, DWORD reason, LPVOID lpReserved)
{
	if (reason == 1)
	{
		DisableThreadLibraryCalls(mod);
		CreateThread(nullptr, 0, MainThread, mod, 0, nullptr);
	}
	return TRUE;
}



/*
UnityEngine_MeshRenderer_o * inmeshRenderer = (UnityEngine_MeshRenderer_o*)cgo->GetComponent("MeshRenderer");
UnityEngine_MeshRenderer_o* inrenderer = (UnityEngine_MeshRenderer_o*)cgo->GetComponent("MeshRenderer");
UnityEngine_MeshRenderer_o* skinnedMeshRenderer = (UnityEngine_MeshRenderer_o*)cgo->GetComponent("SkinnedMeshRenderer");


auto meshcomp = Functions::GameObjectGetComponentInChildren(gameObject, (System_Type_o*)mesh, true);
auto renderercomp = Functions::GameObjectGetComponentInParent(gameObject, (System_Type_o*)renderer, true);
auto skinnedcomp = Functions::GameObjectGetComponentInParent(gameObject, (System_Type_o*)skinned, true);

if (inmeshRenderer == nullptr)
console.WriteLine("mesh1");

if (inrenderer == nullptr)
console.WriteLine("renderer1");


if (skinnedMeshRenderer == nullptr)
console.WriteLine("skinned1");


if (meshcomp == nullptr)
console.WriteLine("mesh");

if (renderercomp == nullptr)
console.WriteLine("renderer");


if (skinnedcomp == nullptr)
console.WriteLine("skinned");
*/
