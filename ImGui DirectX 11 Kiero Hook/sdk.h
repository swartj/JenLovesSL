#pragma once
#include "il2cpp.h"
#include "vec.h"
#include "vec2.h"
#include <vector>
#include <utility> // for std::pair
#include <chrono>
#include "Debug.h"

bool show_menu = true;

Console console;

namespace mem
{
	template<typename T> T read(uintptr_t address) {
		try { return *(T*)address; }
		catch (...) { return T(); }
	}

	template<typename T> void write(uintptr_t address, T value) {
		try { *(T*)address = value; }
		catch (...) { return; }
	}
}

namespace sdk
{
	uintptr_t Base;
	uintptr_t GameAssembly;
	uintptr_t UnityPlayer;

	void mousemove(float tarx, float tary, float X, float Y, int smooth)
	{
		float ScreenCenterX = (X / 2);
		float ScreenCenterY = (Y / 2);
		float TargetX = 0;
		float TargetY = 0;

		smooth = smooth + 3;

		if (tarx != 0)
		{
			if (tarx > ScreenCenterX)
			{
				TargetX = -(ScreenCenterX - tarx);
				TargetX /= smooth;
				if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = 0;
			}

			if (tarx < ScreenCenterX)
			{
				TargetX = tarx - ScreenCenterX;
				TargetX /= smooth;
				if (TargetX + ScreenCenterX < 0) TargetX = 0;
			}
		}

		if (tary != 0)
		{
			if (tary > ScreenCenterY)
			{
				TargetY = -(ScreenCenterY - tary);
				TargetY /= smooth;
				if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = 0;
			}

			if (tary < ScreenCenterY)
			{
				TargetY = tary - ScreenCenterY;
				TargetY /= smooth;
				if (TargetY + ScreenCenterY < 0) TargetY = 0;
			}
		}
		mouse_event(MOUSEEVENTF_MOVE, static_cast<DWORD>(TargetX), static_cast<DWORD>(TargetY), NULL, NULL);
	}
}


namespace Offsets
{
	uintptr_t Il2cppObjectNew = 0x0;
	uintptr_t ArraySetValue = 0x0;
	uintptr_t ArrayCreateInstance = 0x0;
	uintptr_t RendererSetMaterialArray = 0x0;
	uintptr_t RendererGetSharedMaterialArray = 0x0;
	uintptr_t RendererGetMaterialArray = 0x0;
	uintptr_t NetworkWriterWriteQuaternion = 0x0;
	uintptr_t NetworkWriterWriteFloat = 0x0;
	uintptr_t NetworkWriterWriteReferenceHub = 0x0;
	uintptr_t GetEffectiveBlinkDistance = 0x0;
	uintptr_t NetworkWriterReset = 0x0;
	uintptr_t Scp0173TeleportAbilityClientWriteCmd = 0x0;
	uintptr_t GameObjectGetComponentInParent = 0x0;
	uintptr_t GameObjectGetComponentInChildren = 0x0;
	uintptr_t RelativePositionConstructorNetworkReader = 0x0;
	uintptr_t GetNextMessage = 0x0;
	uintptr_t ClientProcessRpcTemplate = 0x0;
	uintptr_t ClientReadPlayerHit = 0x0;
	uintptr_t ClientReadImpactDecal = 0x0;
	uintptr_t ClientReadTracer = 0x0;
	uintptr_t HitscanHitregModuleBaseRandomizeRay = 0x0;
	uintptr_t BulletTracerOnCreated = 0x0;
	uintptr_t TracerBaseFire = 0x0;
	uintptr_t ObjectDestroy = 0x0;
	uintptr_t MaterialIsKeywordEnabled = 0x0;
	uintptr_t MaterialGetShaderKeywords = 0x0;
	uintptr_t MaterialSetRenderQueue = 0x0;
	uintptr_t MaterialSetInt = 0x0;
	uintptr_t TransformSetLocalScale = 0x0;
	uintptr_t QuaternionByEuler = 0x0;
	uintptr_t MaterialSetFloat = 0x0;
	uintptr_t ShaderGetPropertyName = 0x0;
	uintptr_t ShaderGetPropertyCount = 0x0;
	uintptr_t MaterialGetShader = 0x0;
	uintptr_t MaterialSetTexture = 0x0;
	uintptr_t ObjectGetName = 0x0;
	uintptr_t MaterialConstructor = 0x0;
	uintptr_t ShaderFind = 0x0;
	uintptr_t RendererGetMaterial = 0x0;
	uintptr_t RendererSetMaterial = 0x0;
	uintptr_t MaterialSetColor = 0x0;
	uintptr_t GetDefaultMaterial = 0x0;
	uintptr_t RendererSetEnabled = 0x0;
	uintptr_t RendererGetEnabled = 0x0;
	uintptr_t GetComponent = 0x0;
	uintptr_t TransformSetPositionAndRotation = 0x0;
	uintptr_t GameObjectGetTransform = 0x0;
	uintptr_t CreatePrimitive = 0x0;
	uintptr_t DrawLine = 0x0;
	uintptr_t ColorConstructor = 0x0;
	uintptr_t GetForwardRay = 0x0;
	uintptr_t DrawRay = 0x0;
	uintptr_t GetCurrentCamera = 0x0;
	uintptr_t GetRoleId = 0x0;
	uintptr_t TeslaAbilityStart = 0x0;
	uintptr_t GetFailMessage = 0x0;
	uintptr_t AbilityBaseGetCurrentCamSync = 0x0;
	uintptr_t TeslaAbilityGetIsReady = 0x0;
	uintptr_t TeslaAbilityConstructor = 0x0;
	uintptr_t TeslaAbilityTrigger = 0x0;
	uintptr_t ClientSwitchTo = 0x0;
	uintptr_t GetSwitchCost = 0x0;
	uintptr_t TryGetMainCamera = 0x0;
	uintptr_t PlayerInHurtRange = 0x0;
	uintptr_t PlayerInRange = 0x0;
	uintptr_t BatcherAddMessage = 0x0;
	uintptr_t SendToTransport = 0x0;
	uintptr_t AddOutMessageEvent = 0x0;
	uintptr_t NetworkConnectionSend = 0x0;
	uintptr_t NetworkWriterWriteByte = 0x0;
	uintptr_t NetworkWriterToArraySegment = 0x0;
	uintptr_t NetworkWriterPoolGet = 0x0;
	uintptr_t NetworkWriterPoolReturn = 0x0;
	uintptr_t NetworkWriterConstructor = 0x0;
	uintptr_t ServerOnRequestTimedOut = 0x0;
	uintptr_t ShotRequestConstructor = 0x0;
	uintptr_t GetMethods = 0x0;
	uintptr_t WriteInt = 0x0;
	uintptr_t SendCmd = 0x0;
	uintptr_t GetActionDown = 0x0;
	uintptr_t ServerSendResponse = 0x0;
	uintptr_t ServerSendRejection = 0x0;
	uintptr_t WriteShotRequest = 0x0;
	uintptr_t GetBaseFireRate = 0x0;
	uintptr_t RelativePositionConstructor = 0x0;
	uintptr_t RelativePositionGetPosition = 0x0;
	uintptr_t WriteSelf = 0x0;
	uintptr_t OnPlayerMove = 0x0;
	uintptr_t LookRotation = 0x0;
	uintptr_t GetEulerAngles = 0x0;
	uintptr_t GetCurrentHorizontal = 0x0;
	uintptr_t GetCurrentVertical = 0x0;
	uintptr_t SetCurrentHorizontal = 0x0;
	uintptr_t SetCurrentVertical = 0x0;
	uintptr_t GetMouseInput = 0x0;
	uintptr_t GetHitboxType = 0x0;
	uintptr_t GetCenterOfMass = 0x0;
	uintptr_t IsEnemy = 0x0;
	uintptr_t Linecast = 0x0;
	uintptr_t GetModel = 0x0;
	uintptr_t ControllerGetAnimator = 0x0;
	uintptr_t GetOwnerHub = 0x0;
	uintptr_t HasOwner = 0x0;
	uintptr_t SetupAnimator = 0x0;
	uintptr_t FindObjectsByType = 0x0;
	uintptr_t GetIsValid = 0x0;
	uintptr_t GetAvatar = 0x0;
	uintptr_t GetIsHuman = 0x0;
	uintptr_t GetAnimator = 0x0;
	uintptr_t GetRole = 0x0;
	uintptr_t TryGetOwner = 0x0;
	uintptr_t GetBoneTransform = 0x0;
	uintptr_t CreateString = 0x0;
	uintptr_t GetComponentByName = 0x0;
	uintptr_t IsAlive = 0x0;
	uintptr_t GetRoleColor = 0x0;
	uintptr_t SetWantsToJump = 0x0;
	uintptr_t GetMotor = 0x0;
	uintptr_t GetVelocity = 0x0;
	uintptr_t SetVelocity = 0x0;
	uintptr_t GetIsGrounded = 0x0;
	uintptr_t GetTotalDamageDealt = 0x0;
	uintptr_t GetAbsorbedAhpDamage = 0x0;
	uintptr_t GetAbsorbedHumeDamage = 0x0;
	uintptr_t GetDealtHealthDamage = 0x0;
	uintptr_t ApplyDamage = 0x0;
	uintptr_t GetMainCoords = 0x0;
	uintptr_t TryFindRoom = 0x0;
	uintptr_t GetIsSpawned = 0x0;
	uintptr_t GetDefaultPhysicsModule = 0x0;
	uintptr_t GetRoundStarted = 0x0;
	uintptr_t AddOnPickupAdded = 0x0;
	uintptr_t AddOnBeforePlayerDestroyed = 0x0;
	uintptr_t AddOnBeforePickupDestroyed = 0x0;
	uintptr_t GetHostHub = 0x0;
	uintptr_t IsRoundRestarting = 0x0;
	uintptr_t OnPickupDestroy = 0x0;
	uintptr_t PickupGetPosition = 0x0;
	uintptr_t GetAvailableItems = 0x0;
	uintptr_t IsPOV = 0x0;
	uintptr_t IsHost = 0x0;
	uintptr_t IsDummy = 0x0;
	uintptr_t GetDisplayName = 0x0;
	uintptr_t LocalHub = 0x0;
	uintptr_t WolrdToScreen = 0x0;
	uintptr_t GetTeam = 0x0;
	uintptr_t GetCenter = 0x0;
	uintptr_t GetPosition = 0x0;
	uintptr_t GetTransform = 0x0;
	uintptr_t GetGameObject = 0x0;
	uintptr_t GetEnumerator = 0x0;
	uintptr_t GetMainCamera = 0x0;
	uintptr_t GetReferenceHub = 0x0;
}

namespace settings
{
	//rooms of interest
	const char* roomNames[] = { "914", "Checkpoint A", "Checkpoint B", "Testroom", "Nuke", "Gate A", "Gate B"};
	int roomIDs[] = { 10, 3, 4, 37, 16, 27, 28 };

}

namespace vars
{
	inline static UINT vps = 1;
	Vector2 screen_size = { 0, 0 };
	Vector2 screen_center = { 0, 0 };
	D3D11_VIEWPORT viewport;
	bool initil2cpp = false;

	int skeleton[][2] = { {6, 4}, {4, 2}, {2, 0}, {0, 1}, {1, 3}, {3, 5}, {0, 7}, {7, 8}, {8, 9}, {13, 12}, {12, 14}, {14, 16}, {16, 18}, {13, 15}, {15, 17}};

	int boneIDS[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 10, 11, 12, 13, 14, 15, 16, 17, 18, 54 };
	bool pauseitem = false;
	bool drawing = false;
	bool animatorCaching = false;
	bool skeletonDrawing = false;

	ReferenceHub_o* HostHub = NULL;
	ReferenceHub_o* LocalPlayer = NULL;
	PlayerRoles_FirstPersonControl_FirstPersonMovementModule_o* movementModule;
	Il2CppObject materialArrayBullShit = (Il2CppObject)0;

	bool chams = true;
	bool autoTeleport = true;
	bool drawMenu = false;
	bool skeletonESP = true;
	bool autoBunnyHop = true;
	bool playerESP = true;
	bool itemESP = true;
	bool roomESP = true;
	bool aimbot = true;
	bool backtracking = false;
	bool ultraRapidFire = true;
	bool renderConsole = true;
}

namespace tracers
{
	int standardLivingTime = 240;
	float standardColor[4] = { 0.f, 1.f, 1.f, 0.25f };

}

namespace chams
{

}

namespace scp
{
	ReferenceHub_o* bestTarget = nullptr;
	float bestTargetDistance = 10000;

	// 073
	TeslaGate_o* targetGate = nullptr;
}

namespace gui
{
	int inputCooldown = 0;

	ImVec2 menuSize = { 800, 600 };

	bool pop = false;

	bool renderBacktrack = false;
	bool renderVisuals = false;
	bool renderAimAssist = false;
}

namespace ultraRapidFire
{
	//E1 B8 ID ID Type 1D 00

	float chargeTime = 0.4f;
	double weaponCooldown = 0;
	int chargedShots = 0;

	std::chrono::system_clock::time_point lastShot;
	std::chrono::system_clock::time_point lastWeaponEquipped;

	Mirror_NetworkConnectionToServer_o* conn;
	Mirror_Batcher_o* batcher;
	InventorySystem_Items_Firearms_Firearm_o* equippedFirearm;
	System_Action_NetworkWriter__o* writerFunction = (System_Action_NetworkWriter__o*)(calloc(1, sizeof(System_Action_NetworkWriter__o)));
	int32_t channelId = 0;
	bool writerSet = false;
	bool gotAction = false;
	bool gotAction2 = false;
	bool sentshit = true;
	bool gotBatcher = false;
	bool debug = false;
	bool setconn = false;


	bool hasWeaponEquipped = false;
	bool renderChargeUp = true;

}

namespace backtrack
{
	float backtracktime = 0.4;
	
	std::chrono::system_clock::time_point nextShotStamp;

	bool renderRecords = true;
}

namespace aimbot
{
	int range = 100;
	int fov = 30;
	float maxDrag = 0.125;
	float moveTime = 0.1;

	// head: 2, body: 0, limb: 1
	int hitboxPriority[] = { 1, 2, 0 };
	bool friendlyFireActive = false;
	bool drawFov = true;
	bool displayTarget = true;
	ImColor targetColor = ImColor(255, 255, 255, 255);
	int targetThickness = 4;

}

namespace colors
{

	ImColor backtrackRecord = ImColor(0, 255, 255, 127);
	ImColor skeletonCanSee = ImColor(0, 255, 0, 255);
	ImColor skeleton = ImColor(255, 255, 255, 255);
	ImColor room = ImColor(255, 255, 0, 255);
	ImColor scp = ImColor(233, 16, 16, 255);
	ImColor mtf = ImColor(5, 147, 250, 255);
	ImColor classd = ImColor(251, 126, 4, 255);
	ImColor chaos = ImColor(3, 141, 29, 255);
	ImColor scientist = ImColor(247, 247, 121, 255);
	ImColor ahp = ImColor(102, 227, 72, 255);
	ImColor hume = ImColor(114, 111, 219, 255);
	ImColor health = ImColor(255, 255, 255, 255);
}

namespace resources
{

	UnityEngine_Material_o* standardMaterial;

	ImFont* indicatorFont;

	ID3D11ShaderResourceView* KeycardJanitor;
	ID3D11ShaderResourceView* KeycardScientist;
	ID3D11ShaderResourceView* KeycardResearchCoordinator;
	ID3D11ShaderResourceView* KeycardZoneManager;
	ID3D11ShaderResourceView* KeycardGuard;
	ID3D11ShaderResourceView* KeycardMTFPrivate;
	ID3D11ShaderResourceView* KeycardContainmentEngineer;
	ID3D11ShaderResourceView* KeycardMTFOperative;
	ID3D11ShaderResourceView* KeycardMTFCaptian;
	ID3D11ShaderResourceView* KeycardFacilityManager;
	ID3D11ShaderResourceView* KeycardChaosInsurgency;
	ID3D11ShaderResourceView* KeycardO5;
	ID3D11ShaderResourceView* Radio;
	ID3D11ShaderResourceView* GunCOM15;
	ID3D11ShaderResourceView* Medkit;
	ID3D11ShaderResourceView* Flashlight;
	ID3D11ShaderResourceView* MicroHID;
	ID3D11ShaderResourceView* SCP500;
	ID3D11ShaderResourceView* SCP207;
	ID3D11ShaderResourceView* Ammo12gauge;
	ID3D11ShaderResourceView* GunE11SR;
	ID3D11ShaderResourceView* GunCrossvec;
	ID3D11ShaderResourceView* Ammo556x45;
	ID3D11ShaderResourceView* GunFSP9;
	ID3D11ShaderResourceView* GunLogicer;
	ID3D11ShaderResourceView* GrenadeHE;
	ID3D11ShaderResourceView* GrenadeFlash;
	ID3D11ShaderResourceView* Ammo44cal;
	ID3D11ShaderResourceView* Ammo762x39;
	ID3D11ShaderResourceView* Ammo9x19;
	ID3D11ShaderResourceView* GunCOM18;
	ID3D11ShaderResourceView* SCP018;
	ID3D11ShaderResourceView* SCP268;
	ID3D11ShaderResourceView* Adrenaline;
	ID3D11ShaderResourceView* Painkillers;
	ID3D11ShaderResourceView* Coin;
	ID3D11ShaderResourceView* ArmorLight;
	ID3D11ShaderResourceView* ArmorCombat;
	ID3D11ShaderResourceView* ArmorHeavy;
	ID3D11ShaderResourceView* GunRevolver;
	ID3D11ShaderResourceView* GunAK;
	ID3D11ShaderResourceView* GunShotgun;
	ID3D11ShaderResourceView* SCP330;
	ID3D11ShaderResourceView* SCP2176;
	ID3D11ShaderResourceView* SCP244a;
	ID3D11ShaderResourceView* SCP244b;
	ID3D11ShaderResourceView* SCP1853;
	ID3D11ShaderResourceView* ParticleDisruptor;
	ID3D11ShaderResourceView* GunCOM45;
	ID3D11ShaderResourceView* SCP1576;
	ID3D11ShaderResourceView* Jailbird;
	ID3D11ShaderResourceView* AntiSCP207;
	ID3D11ShaderResourceView* GunFRMG0;
	ID3D11ShaderResourceView* GunA7;
	ID3D11ShaderResourceView* Lantern;
	ID3D11ShaderResourceView* SCP1344;
	ID3D11ShaderResourceView* SurfaceAccessPass;
	ID3D11ShaderResourceView* GunSCP127;

	ID3D11ShaderResourceView* ItemTypeToTexture(int type)
	{
		switch (type)
		{
		case 0:
			return resources::KeycardJanitor;
		case 1:
			return resources::KeycardScientist;
		case 2:
			return resources::KeycardResearchCoordinator;
		case 3:
			return resources::KeycardZoneManager;
		case 4:
			return resources::KeycardGuard;
		case 5:
			return resources::KeycardMTFPrivate;
		case 6:
			return resources::KeycardContainmentEngineer;
		case 7:
			return resources::KeycardMTFOperative;
		case 8:
			return resources::KeycardMTFCaptian;
		case 9:
			return resources::KeycardFacilityManager;
		case 10:
			return resources::KeycardChaosInsurgency;
		case 11:
			return resources::KeycardO5;
		case 12:
			return resources::Radio;
		case 13:
			return resources::GunCOM15;
		case 14:
			return resources::Medkit;
		case 15:
			return resources::Flashlight;
		case 16:
			return resources::MicroHID;
		case 17:
			return resources::SCP500;
		case 18:
			return resources::SCP207;
		case 19:
			return resources::Ammo12gauge;
		case 20:
			return resources::GunE11SR;
		case 21:
			return resources::GunCrossvec;
		case 22:
			return resources::Ammo556x45;
		case 23:
			return resources::GunFSP9;
		case 24:
			return resources::GunLogicer;
		case 25:
			return resources::GrenadeHE;
		case 26:
			return resources::GrenadeFlash;
		case 27:
			return resources::Ammo44cal;
		case 28:
			return resources::Ammo762x39;
		case 29:
			return resources::Ammo9x19;
		case 30:
			return resources::GunCOM18;
		case 31:
			return resources::SCP018;
		case 32:
			return resources::SCP268;
		case 33:
			return resources::Adrenaline;
		case 34:
			return resources::Painkillers;
		case 35:
			return resources::Coin;
		case 36:
			return resources::ArmorLight;
		case 37:
			return resources::ArmorCombat;
		case 38:
			return resources::ArmorHeavy;
		case 39:
			return resources::GunRevolver;
		case 40:
			return resources::GunAK;
		case 41:
			return resources::GunShotgun;
		case 42:
			return resources::SCP330;
		case 43:
			return resources::SCP2176;
		case 44:
			return resources::SCP244a;
		case 45:
			return resources::SCP244b;
		case 46:
			return resources::SCP1853;
		case 47:
			return resources::ParticleDisruptor;
		case 48:
			return resources::GunCOM45;
		case 49:
			return resources::SCP1576;
		case 50:
			return resources::Jailbird;
		case 51:
			return resources::AntiSCP207;
		case 52:
			return resources::GunFRMG0;
		case 53:
			return resources::GunA7;
		case 54:
			return resources::Lantern;
		case 55:
			return resources::SCP1344;
		case 61:
			return resources::SurfaceAccessPass;
		case 62:
			return resources::GunSCP127;

		default:
			return nullptr;
		}
	}
}
