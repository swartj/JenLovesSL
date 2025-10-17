#pragma once
#include "vec.h"
#include "vec2.h"
#include <string>
#include "il2cpp_resolver.hpp"
#include "Lists.hpp"
#include <intrin.h>
#include <Windows.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <TlHelp32.h>
#include <string>
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")


namespace Functions
{
#pragma region Hooks



	bool pickupadded = false;

	void OnPickupAdded(Il2CppObject* obj, Il2CppObject* obj2)
	{
		if (!obj || !obj->klass)
		{
			std::cout << "invalid object\n";
			return;
		}

		InventorySystem_Items_Pickups_ItemPickupBase_o* pickup = reinterpret_cast<InventorySystem_Items_Pickups_ItemPickupBase_o*>(obj2);
		ItemList.push_back(pickup);
	}

	void AddOnPickupAdded(System_Action_ItemPickupBase__o* action)
	{
		void(UNITY_CALLING_CONVENTION t)(System_Action_ItemPickupBase__o*);
		return reinterpret_cast<decltype(t)>(Offsets::AddOnPickupAdded)(action);
	}

	void AddOnBeforePickupDestroyed(System_Action_ItemPickupBase__o* action)
	{
		void(UNITY_CALLING_CONVENTION t)(System_Action_ItemPickupBase__o*);
		return reinterpret_cast<decltype(t)>(Offsets::AddOnBeforePickupDestroyed)(action);
	}

	void OnBeforePickupDestroyed(Il2CppObject* obj, Il2CppObject* obj2)
	{

		if (!obj || !obj->klass)
		{
			std::cout << "invalid object\n";
			return;
		}

		if (!obj2 || !obj2->klass)
		{
			std::cout << "invalid object2\n";
			return;
		}

		auto pickup = reinterpret_cast<InventorySystem_Items_Pickups_ItemPickupBase_o*>(obj2);

		vars::pauseitem = true;
		auto s = std::find(ItemList.begin(), ItemList.end(), pickup);
		if (s != ItemList.end()) ItemList.erase(s);
		vars::pauseitem = false;
	}

	void AddPickup(System_Action_ItemPickupBase__o* action)
	{
		pickupadded = true;

		System_Action_ItemPickupBase__o* onBeforePickupDestroyed = (System_Action_ItemPickupBase__o*)calloc(1, sizeof(System_Action_ItemPickupBase__o));
		System_Action_ItemPickupBase__o* onPickupAdded = (System_Action_ItemPickupBase__o*)calloc(1, sizeof(System_Action_ItemPickupBase__o));

		memcpy(onBeforePickupDestroyed, action, sizeof(System_Action_ItemPickupBase__o));
		memcpy(onPickupAdded, action, sizeof(System_Action_ItemPickupBase__o));

		onBeforePickupDestroyed->fields.method_ptr = (intptr_t)&Functions::OnBeforePickupDestroyed;
		onBeforePickupDestroyed->fields.invoke_impl = (intptr_t)&Functions::OnBeforePickupDestroyed;

		onPickupAdded->fields.method_ptr = (intptr_t)&Functions::OnPickupAdded;
		onPickupAdded->fields.invoke_impl = (intptr_t)&Functions::OnPickupAdded;

		Functions::AddOnBeforePickupDestroyed(onBeforePickupDestroyed);
		Functions::AddOnPickupAdded(onPickupAdded);
	}

	void (UNITY_CALLING_CONVENTION add_OnBeforePickupDestroyed)(System_Action_ItemPickupBase__o* action);

	void add_OnBeforePickupDestroyed_hk(System_Action_ItemPickupBase__o* action)
	{
		std::cout << "hook called\n";
		if (!Functions::pickupadded) Functions::AddPickup(action);
		return add_OnBeforePickupDestroyed(action);
	}

	void (UNITY_CALLING_CONVENTION OnPickupDestroy)(InventorySystem_Items_Pickups_ItemPickupBase_o* pickup);

	void OnPickupDestroy_hk(InventorySystem_Items_Pickups_ItemPickupBase_o* pickup)
	{
		vars::pauseitem = true;
		auto s = std::find(ItemList.begin(), ItemList.end(), pickup);
		if (s != ItemList.end()) ItemList.erase(s);
		vars::pauseitem = false;

		return OnPickupDestroy(pickup);
	}

	UnityEngine_Animator_o* (UNITY_CALLING_CONVENTION SetupAnimator)(PlayerRoles_FirstPersonControl_Thirdperson_AnimatedCharacterModel_o* characterModel);

	UnityEngine_Animator_o* SetupAnimator_hk(PlayerRoles_FirstPersonControl_Thirdperson_AnimatedCharacterModel_o* characterModel)
	{
		std::cout << "setup animator\n";

		UnityEngine_Animator_o* animator = Functions::SetupAnimator(characterModel);

		AnimatorList.push_back(animator);

		return animator;
	}

	
#pragma endregion

#pragma region Game Functions
	// UnityEngine_Camera$$Get_Main
	UnityEngine_GameObject_o* GetGameObject(UnityEngine_Component_o* component)
	{
		UnityEngine_GameObject_o* (UNITY_CALLING_CONVENTION t)(UnityEngine_Component_o*);
		return reinterpret_cast<decltype(t)>(Offsets::GetGameObject)(component);
	}

	UnityEngine_Camera_o* GetMainCamera()
	{
		UnityEngine_Camera_o* (UNITY_CALLING_CONVENTION get_main)();
		return reinterpret_cast<decltype(get_main)>(Offsets::GetMainCamera)();
	}

	UnityEngine_Component_o* GetComponent(UnityEngine_GameObject_o* gameObject, System_String_o* type)
	{
		UnityEngine_Component_o* (UNITY_CALLING_CONVENTION t)(UnityEngine_GameObject_o*, System_String_o*);
		return reinterpret_cast<decltype(t)>(Offsets::GetComponentByName)(gameObject, type);
	}
	
	template<typename T>
	static Unity::il2cppArray<T*>* FindObjectsByType(Unity::il2cppObject* systemType, int32_t sortMode)
	{
		return reinterpret_cast<Unity::il2cppArray<T*>*(UNITY_CALLING_CONVENTION)(Unity::il2cppObject*, int32_t)>(Offsets::FindObjectsByType)(systemType, sortMode);

	}

	System_String_o* CreateString(System_String_o* idfk, uint16_t* value)
	{
		System_String_o* (UNITY_CALLING_CONVENTION t)(System_String_o*, uint16_t*);
		return reinterpret_cast<decltype(t)>(Offsets::CreateString)(idfk, value);
	}

	UnityEngine_Avatar_o* GetAvatar(UnityEngine_Animator_o* animator)
	{
		UnityEngine_Avatar_o* (UNITY_CALLING_CONVENTION t)(UnityEngine_Animator_o*);
		return reinterpret_cast<decltype(t)>(Offsets::GetAvatar)(animator);
	}

	bool GetIsHuman(UnityEngine_Avatar_o* avatar)
	{
		bool (UNITY_CALLING_CONVENTION t)(UnityEngine_Avatar_o*);
		return reinterpret_cast<decltype(t)>(Offsets::GetIsHuman)(avatar);
	}

	bool GetIsValid(UnityEngine_Avatar_o* avatar)
	{
		bool (UNITY_CALLING_CONVENTION t)(UnityEngine_Avatar_o*);
		return reinterpret_cast<decltype(t)>(Offsets::GetIsValid)(avatar);
	}

	UnityEngine_Shader_o* MaterialGetShader(UnityEngine_Material_o* __this)
	{
		UnityEngine_Shader_o* (UNITY_CALLING_CONVENTION t)(UnityEngine_Material_o*);
		return reinterpret_cast<decltype(t)>(Offsets::MaterialGetShader)(__this);
	}

	void MaterialSetTexture(UnityEngine_Material_o* __this, System_String_o* name, UnityEngine_Texture_o* value)
	{
		void (UNITY_CALLING_CONVENTION t)(UnityEngine_Material_o*, System_String_o*, UnityEngine_Texture_o*);
		return reinterpret_cast<decltype(t)>(Offsets::MaterialSetTexture)(__this, name, value);
	}

	ReferenceHub_o* GetOwnerHub(PlayerRoles_FirstPersonControl_Thirdperson_Subcontrollers_SubcontrollerBehaviour_o* controller)
	{
		ReferenceHub_o* (UNITY_CALLING_CONVENTION t)(PlayerRoles_FirstPersonControl_Thirdperson_Subcontrollers_SubcontrollerBehaviour_o*);
		return reinterpret_cast<decltype(t)>(Offsets::GetOwnerHub)(controller);
	}

	bool GetHasOwner(PlayerRoles_FirstPersonControl_Thirdperson_Subcontrollers_SubcontrollerBehaviour_o* controller)
	{
		bool (UNITY_CALLING_CONVENTION t)(PlayerRoles_FirstPersonControl_Thirdperson_Subcontrollers_SubcontrollerBehaviour_o*);
		return reinterpret_cast<decltype(t)>(Offsets::HasOwner)(controller);
	}

	UnityEngine_Vector3_o RelativePositionGetPosition(RelativePositioning_RelativePosition_o* __this)
	{
		UnityEngine_Vector3_o(UNITY_CALLING_CONVENTION t)(RelativePositioning_RelativePosition_o*);
		return reinterpret_cast<decltype(t)>(Offsets::RelativePositionGetPosition)(__this);
	}

	void RelativePositionConstructor(RelativePositioning_RelativePosition_o* __this, UnityEngine_Vector3_o targetPosition)
	{
		void (UNITY_CALLING_CONVENTION t)(RelativePositioning_RelativePosition_o*, UnityEngine_Vector3_o);
		return reinterpret_cast<decltype(t)>(Offsets::RelativePositionConstructor)(__this, targetPosition);
	}

	PlayerRoles_PlayerRoleBase_o* GetRole(PlayerRoles_FirstPersonControl_Thirdperson_AnimatedCharacterModel_o* characterModel)
	{
		PlayerRoles_PlayerRoleBase_o* (UNITY_CALLING_CONVENTION t)(PlayerRoles_FirstPersonControl_Thirdperson_AnimatedCharacterModel_o*);
		return reinterpret_cast<decltype(t)>(Offsets::GetRole)(characterModel);
	}

	UnityEngine_Animator_o* GetAnimator(PlayerRoles_FirstPersonControl_Thirdperson_AnimatedCharacterModel_o* characterModel)
	{
		UnityEngine_Animator_o* (UNITY_CALLING_CONVENTION t)(PlayerRoles_FirstPersonControl_Thirdperson_AnimatedCharacterModel_o*);
		return reinterpret_cast<decltype(t)>(Offsets::GetAnimator)(characterModel);
	}

	bool Linecast(UnityEngine_Vector3_o start, UnityEngine_Vector3_o end, int32_t layerMask, int32_t queryTriggerInteraction)
	{
		bool (UNITY_CALLING_CONVENTION t)(UnityEngine_Vector3_o, UnityEngine_Vector3_o, int32_t, int32_t);
		return reinterpret_cast<decltype(t)>(Offsets::Linecast)(start, end, layerMask, queryTriggerInteraction);
	}

	PlayerRoles_FirstPersonControl_Thirdperson_CharacterModel_o* GetModel(ReferenceHub_o* hub)
	{
		PlayerRoles_FirstPersonControl_Thirdperson_CharacterModel_o* (UNITY_CALLING_CONVENTION t)(ReferenceHub_o*);
		return reinterpret_cast<decltype(t)>(Offsets::GetModel)(hub);
	}

	UnityEngine_Animator_o* ControllerGetAnimator(PlayerRoles_FirstPersonControl_Thirdperson_Subcontrollers_SubcontrollerBehaviour_o* controller)
	{
		UnityEngine_Animator_o* (UNITY_CALLING_CONVENTION t)(PlayerRoles_FirstPersonControl_Thirdperson_Subcontrollers_SubcontrollerBehaviour_o * controller);
		return reinterpret_cast<decltype(t)>(Offsets::ControllerGetAnimator)(controller);
	}


	bool TryGetOwner(PlayerRoles_PlayerRoleBase_o* roleBase, ReferenceHub_o** hub)
	{
		bool (UNITY_CALLING_CONVENTION t)(PlayerRoles_PlayerRoleBase_o*, ReferenceHub_o**);
		return reinterpret_cast<decltype(t)>(Offsets::TryGetOwner)(roleBase, hub);
	}

	UnityEngine_Transform_o* GetBoneTransform(UnityEngine_Animator_o* animator,int id)
	{
		UnityEngine_Transform_o* (UNITY_CALLING_CONVENTION t)(UnityEngine_Animator_o*, int);
		return reinterpret_cast<decltype(t)>(Offsets::GetBoneTransform)(animator, id);
	}

	InventorySystem_Items_Pickups_PickupPhysicsModule_o* GetDefaultPhysicsModule(InventorySystem_Items_Pickups_ItemPickupBase_o* pickup)
	{
		InventorySystem_Items_Pickups_PickupPhysicsModule_o* (UNITY_CALLING_CONVENTION t)(InventorySystem_Items_Pickups_ItemPickupBase_o*);
		return reinterpret_cast<decltype(t)>(Offsets::GetDefaultPhysicsModule)(pickup);
	}

	bool GetIsSpawned(InventorySystem_Items_Pickups_PickupPhysicsModule_o* physicsModule)
	{
		bool (UNITY_CALLING_CONVENTION t)(InventorySystem_Items_Pickups_PickupPhysicsModule_o*);
		return reinterpret_cast<decltype(t)>(Offsets::GetIsSpawned)(physicsModule);
	}

	UnityEngine_Vector3_o WorldToScreenPoint(UnityEngine_Camera_o* camera, UnityEngine_Vector3_o position, int32_t eye)
	{
		UnityEngine_Vector3_o (UNITY_CALLING_CONVENTION t)(UnityEngine_Camera_o*, UnityEngine_Vector3_o, int32_t);
		return reinterpret_cast<decltype(t)>(Offsets::WolrdToScreen)(camera, position, eye);
	}

	UnityEngine_Vector3Int_o GetMainCoords(MapGeneration_RoomIdentifier_o* room)
	{
		UnityEngine_Vector3Int_o(UNITY_CALLING_CONVENTION t)(MapGeneration_RoomIdentifier_o*);
		return reinterpret_cast<decltype(t)>(Offsets::GetMainCoords)(room);
	}

	bool TryFindRoom(System_Nullable_RoomName__o name, System_Nullable_FacilityZone__o zone, System_Nullable_RoomShape__o shape, MapGeneration_RoomIdentifier_o** foundRoom)
	{
		bool (UNITY_CALLING_CONVENTION t)(System_Nullable_RoomName__o, System_Nullable_FacilityZone__o, System_Nullable_RoomShape__o, MapGeneration_RoomIdentifier_o**);
		return reinterpret_cast<decltype(t)>(Offsets::TryFindRoom)(name, zone, shape, foundRoom);
	}

	bool IsAlive(ReferenceHub_o* hub)
	{
		bool (UNITY_CALLING_CONVENTION t)(ReferenceHub_o*);
		return reinterpret_cast<decltype(t)>(Offsets::IsAlive)(hub);
	}

	struct System_Collections_Generic_HashSet_ReferenceHub__o* GetAllHubs()
	{
		struct System_Collections_Generic_HashSet_ReferenceHub__o* (UNITY_CALLING_CONVENTION t)();
		return reinterpret_cast<decltype(t)>(Offsets::GetReferenceHub)();
	}

	UnityEngine_Transform_o* GetTransform(UnityEngine_Component_o* component)
	{
		UnityEngine_Transform_o* (UNITY_CALLING_CONVENTION ttt)(UnityEngine_Component_o*);
		return reinterpret_cast<decltype(ttt)>(Offsets::GetTransform)(component);
	}

	uint8_t GetTeam(ReferenceHub_o* hub)
	{
		uint8_t(UNITY_CALLING_CONVENTION ttt)(ReferenceHub_o*);
		return reinterpret_cast<decltype(ttt)>(Offsets::GetTeam)(hub);
	}

	UnityEngine_Color_o GetRoleColor(PlayerRoles_PlayerRoleBase_o* roleBase)
	{
		UnityEngine_Color_o(UNITY_CALLING_CONVENTION t)(PlayerRoles_PlayerRoleBase_o*);
		return reinterpret_cast<decltype(t)>(Offsets::GetRoleColor)(roleBase);
	}

	ReferenceHub_o* GetLocalHub()
	{
		ReferenceHub_o* (UNITY_CALLING_CONVENTION tttt)();
		return reinterpret_cast<decltype(tttt)>(Offsets::LocalHub)();
	}
	
	System_String_o* GetDisplayName(NicknameSync_o* nicknameSync)
	{
		System_String_o* (UNITY_CALLING_CONVENTION tttt)(NicknameSync_o*);
		return reinterpret_cast<decltype(tttt)>(Offsets::GetDisplayName)(nicknameSync);
	}

	System_Collections_Generic_Dictionary_ItemType__ItemBase__o* GetAvailableItems()
	{
		System_Collections_Generic_Dictionary_ItemType__ItemBase__o* (UNITY_CALLING_CONVENTION tttt)();
		return reinterpret_cast<decltype(tttt)>(Offsets::GetAvailableItems)();
	}


	UnityEngine_Vector3_o PickupGetPosition(InventorySystem_Items_Pickups_ItemPickupBase_o* itemPickupBase)
	{
		UnityEngine_Vector3_o (UNITY_CALLING_CONVENTION tttt)(InventorySystem_Items_Pickups_ItemPickupBase_o*);
		return reinterpret_cast<decltype(tttt)>(Offsets::PickupGetPosition)(itemPickupBase);
	}

	bool IsPOV(ReferenceHub_o* hub)
	{
		bool (UNITY_CALLING_CONVENTION tttt)(ReferenceHub_o*);
		return reinterpret_cast<decltype(tttt)>(Offsets::IsPOV)(hub);
	}

	bool IsDummy(ReferenceHub_o* hub)
	{
		bool (UNITY_CALLING_CONVENTION tttt)(ReferenceHub_o*);
		return reinterpret_cast<decltype(tttt)>(Offsets::IsDummy)(hub);
	}

	ReferenceHub_o* GetHostHub()
	{
		ReferenceHub_o* (UNITY_CALLING_CONVENTION tttt)();
		return reinterpret_cast<decltype(tttt)>(Offsets::GetHostHub)();
	}

	bool IsHost(ReferenceHub_o* hub)
	{
		bool (UNITY_CALLING_CONVENTION tttt)(ReferenceHub_o*);
		return reinterpret_cast<decltype(tttt)>(Offsets::IsHost)(hub);
	}

	UnityEngine_Vector3_o GetPosition(UnityEngine_Transform_o* transform)
	{
		UnityEngine_Vector3_o(UNITY_CALLING_CONVENTION tttt)(UnityEngine_Transform_o*, const MethodInfo*);
		return reinterpret_cast<decltype(tttt)>(Offsets::GetPosition)(transform, nullptr);
	}

	bool IsRoundRestarting()
	{
		bool(UNITY_CALLING_CONVENTION t)();
		return reinterpret_cast<decltype(t)>(Offsets::IsRoundRestarting)();

	}

	bool GetRoundStarted()
	{
		bool (UNITY_CALLING_CONVENTION tttt)();
		return reinterpret_cast<decltype(tttt)>(Offsets::GetRoundStarted)();
	}

	bool GetIsGrounded(PlayerRoles_FirstPersonControl_FirstPersonMovementModule_o* movementModule)
	{
		bool(UNITY_CALLING_CONVENTION t)(PlayerRoles_FirstPersonControl_FirstPersonMovementModule_o*);
		return reinterpret_cast<decltype(t)>(Offsets::GetIsGrounded)(movementModule);
	}

	UnityEngine_Vector3_o GetCenterOfMass(HitboxIdentity_o* hitbox)
	{
		UnityEngine_Vector3_o(UNITY_CALLING_CONVENTION t)(HitboxIdentity_o*);
		return reinterpret_cast<decltype(t)>(Offsets::GetCenterOfMass)(hitbox);
	}

	bool GetActionDown(InventorySystem_Items_Autosync_SubcomponentBase_o* __this, int32_t action)
	{
		bool (UNITY_CALLING_CONVENTION t)(InventorySystem_Items_Autosync_SubcomponentBase_o*, int32_t);
		return reinterpret_cast<decltype(t)>(Offsets::GetActionDown)(__this, action);
	}

	System_ArraySegment_byte__o NetworkWriterToArraySegment(Mirror_NetworkWriter_o* writer)
	{
		System_ArraySegment_byte__o(UNITY_CALLING_CONVENTION t)(Mirror_NetworkWriter_o*);
		return reinterpret_cast<decltype(t)>(Offsets::NetworkWriterToArraySegment)(writer);
	}

	Mirror_NetworkWriterPooled_o* NetworkWriterPoolGet()
	{
		Mirror_NetworkWriterPooled_o* (UNITY_CALLING_CONVENTION t)();
		return reinterpret_cast<decltype(t)>(Offsets::NetworkWriterPoolGet)();
	}

	void NetworkConnectionSendDepr(Mirror_NetworkConnection_o* __this, System_ArraySegment_byte__o segment, int32_t channelId)
	{
		void (UNITY_CALLING_CONVENTION t)(Mirror_NetworkConnection_o*, System_ArraySegment_byte__o, int32_t);
		return reinterpret_cast<decltype(t)>(Offsets::NetworkConnectionSend)(__this, segment, channelId);
	}

	void NetworkWriterPoolReturn(Mirror_NetworkWriterPooled_o* networkWriterPooled)
	{
		void (UNITY_CALLING_CONVENTION t)(Mirror_NetworkWriterPooled_o*);
		return reinterpret_cast<decltype(t)>(Offsets::NetworkWriterPoolReturn)(networkWriterPooled);
	}

	bool IsEnemy(ReferenceHub_o* attacker, ReferenceHub_o* victim)
	{
		bool (UNITY_CALLING_CONVENTION t)(ReferenceHub_o*, ReferenceHub_o*);
		return reinterpret_cast<decltype(t)>(Offsets::IsEnemy)(attacker, victim);
	}

	bool PlayerInRange(TeslaGate_o* __this, ReferenceHub_o* player)
	{
		bool (UNITY_CALLING_CONVENTION t)(TeslaGate_o*, ReferenceHub_o*);
		return reinterpret_cast<decltype(t)>(Offsets::PlayerInRange)(__this, player);
	}

	bool PlayerInHurtRange(TeslaGate_o* __this, UnityEngine_GameObject_o* player)
	{
		bool (UNITY_CALLING_CONVENTION t)(TeslaGate_o*, UnityEngine_GameObject_o*);
		return reinterpret_cast<decltype(t)>(Offsets::PlayerInHurtRange)(__this, player);
	}

	bool TryGetMainCamera(MapGeneration_RoomIdentifier_o* room, PlayerRoles_PlayableScps_Scp079_Cameras_Scp079Camera_o** main)
	{
		bool (UNITY_CALLING_CONVENTION t)(MapGeneration_RoomIdentifier_o*, PlayerRoles_PlayableScps_Scp079_Cameras_Scp079Camera_o**);
		return reinterpret_cast<decltype(t)>(Offsets::TryGetMainCamera)(room, main);
	}

	void ClientSwitchTo(PlayerRoles_PlayableScps_Scp079_Cameras_Scp079CurrentCameraSync_o* __this, PlayerRoles_PlayableScps_Scp079_Cameras_Scp079Camera_o* target)
	{
		void (UNITY_CALLING_CONVENTION t)(PlayerRoles_PlayableScps_Scp079_Cameras_Scp079CurrentCameraSync_o*, PlayerRoles_PlayableScps_Scp079_Cameras_Scp079Camera_o*);
		return reinterpret_cast<decltype(t)>(Offsets::ClientSwitchTo)(__this, target);
	}

	void TeslaAbilityConstructor(PlayerRoles_PlayableScps_Scp079_Scp079TeslaAbility_o* ability)
	{
		void (UNITY_CALLING_CONVENTION t)(PlayerRoles_PlayableScps_Scp079_Scp079TeslaAbility_o*);
		return reinterpret_cast<decltype(t)>(Offsets::TeslaAbilityConstructor)(ability);
	}

	void NetworkWriterReset(Mirror_NetworkWriter_o* __this)
	{
		void(UNITY_CALLING_CONVENTION t)(Mirror_NetworkWriter_o*);
		return reinterpret_cast<decltype(t)>(Offsets::NetworkWriterReset)(__this);
	}

	bool TeslaAbilityGetIsReady(PlayerRoles_PlayableScps_Scp079_Scp079TeslaAbility_o* __this)
	{
		bool (UNITY_CALLING_CONVENTION t)(PlayerRoles_PlayableScps_Scp079_Scp079TeslaAbility_o*);
		return reinterpret_cast<decltype(t)>(Offsets::TeslaAbilityGetIsReady)(__this);
	}

	PlayerRoles_PlayableScps_Scp079_Cameras_Scp079CurrentCameraSync_o* GetCurrentCameraSync(PlayerRoles_PlayableScps_Scp079_Scp079AbilityBase_o* __this)
	{
		PlayerRoles_PlayableScps_Scp079_Cameras_Scp079CurrentCameraSync_o* (UNITY_CALLING_CONVENTION t)(PlayerRoles_PlayableScps_Scp079_Scp079AbilityBase_o*);
		return reinterpret_cast<decltype(t)>(Offsets::AbilityBaseGetCurrentCamSync)(__this);
	}

	void RendererSetEnabled(UnityEngine_Renderer_o* __this, bool value)
	{
		void (UNITY_CALLING_CONVENTION t)(UnityEngine_Renderer_o*, bool);
		return reinterpret_cast<decltype(t)>(Offsets::RendererSetEnabled)(__this, value);
	}

	bool RendererGetEnabled(UnityEngine_Renderer_o* __this)
	{
		bool (UNITY_CALLING_CONVENTION t)(UnityEngine_Renderer_o*);
		return reinterpret_cast<decltype(t)>(Offsets::RendererGetEnabled)(__this);
	}

	void MaterialSetColor(UnityEngine_Material_o* __this, UnityEngine_Color_o value)
	{
		void (UNITY_CALLING_CONVENTION t)(UnityEngine_Material_o*, UnityEngine_Color_o);
		return reinterpret_cast<decltype(t)>(Offsets::MaterialSetColor)(__this, value);
	}

	int32_t GetSwitchCost(PlayerRoles_PlayableScps_Scp079_Cameras_Scp079CurrentCameraSync_o* __this, PlayerRoles_PlayableScps_Scp079_Cameras_Scp079Camera_o* target)
	{
		int32_t(UNITY_CALLING_CONVENTION t)(PlayerRoles_PlayableScps_Scp079_Cameras_Scp079CurrentCameraSync_o*, PlayerRoles_PlayableScps_Scp079_Cameras_Scp079Camera_o*);
		return reinterpret_cast<decltype(t)>(Offsets::GetSwitchCost)(__this, target);
	}

	UnityEngine_Material_o* GetDefaultMaterial()
	{
		UnityEngine_Material_o* (UNITY_CALLING_CONVENTION t)();
		return reinterpret_cast<decltype(t)>(Offsets::GetDefaultMaterial)();
	}

	void RendererSetMaterial(UnityEngine_Renderer_o* __this, UnityEngine_Material_o* value)
	{
		void (UNITY_CALLING_CONVENTION t)(UnityEngine_Renderer_o*, UnityEngine_Material_o*);
		return reinterpret_cast<decltype(t)>(Offsets::RendererSetMaterial)(__this, value);
	}

	UnityEngine_Material_o* RendererGetMaterial(UnityEngine_Renderer_o* __this)
	{
		UnityEngine_Material_o* (UNITY_CALLING_CONVENTION t)(UnityEngine_Renderer_o*);
		return reinterpret_cast<decltype(t)>(Offsets::RendererGetMaterial)(__this);
	}

	UnityEngine_Shader_o* ShaderFind(System_String_o* name)
	{
		UnityEngine_Shader_o* (UNITY_CALLING_CONVENTION t)(System_String_o*);
		return reinterpret_cast<decltype(t)>(Offsets::ShaderFind)(name);
	}

	void MaterialConstructor(UnityEngine_Material_o* __this, UnityEngine_Shader_o* shader)
	{
		void (UNITY_CALLING_CONVENTION t)(UnityEngine_Material_o*, UnityEngine_Shader_o*);
		return reinterpret_cast<decltype(t)>(Offsets::MaterialConstructor)(__this, shader);
	}

	void MaterialSetFloat(UnityEngine_Material_o* __this, System_String_o* name, float value)
	{
		void (UNITY_CALLING_CONVENTION t)(UnityEngine_Material_o*, System_String_o*, float);
		return reinterpret_cast<decltype(t)>(Offsets::MaterialSetFloat)(__this, name, value);
	}

	UnityEngine_Quaternion_o QuaternionByEuler(float x, float y, float z)
	{
		UnityEngine_Quaternion_o (UNITY_CALLING_CONVENTION t)(float, float, float);
		return reinterpret_cast<decltype(t)>(Offsets::QuaternionByEuler)(x, y, z);
	}

	void TransformSetLocalScale(UnityEngine_Transform_o* __this, UnityEngine_Vector3_o value)
	{
		void (UNITY_CALLING_CONVENTION t)(UnityEngine_Transform_o* , UnityEngine_Vector3_o);
		return reinterpret_cast<decltype(t)>(Offsets::TransformSetLocalScale)(__this, value);
	}

	System_Array_o* ArrayCreateInstance(System_Type_o* elementType, int32_t length)
	{
		System_Array_o* (UNITY_CALLING_CONVENTION t)(System_Type_o*, int32_t);
		return reinterpret_cast<decltype(t)>(Offsets::ArrayCreateInstance)(elementType, length);
	}

	Il2CppObject* Il2cppObjectNew(Unity::il2cppClass* klass)
	{
		Il2CppObject* (UNITY_CALLING_CONVENTION t)(Unity::il2cppClass*);
		return reinterpret_cast<decltype(t)>(Offsets::Il2cppObjectNew)(klass);
	}

	void ArraySetValue(System_Array_o* __this, Il2CppObject* value, int32_t index)
	{
		void (UNITY_CALLING_CONVENTION t)(System_Array_o*, Il2CppObject*, int32_t);
		return reinterpret_cast<decltype(t)>(Offsets::ArraySetValue)(__this, value, index);
	}

	void RendererSetMaterialArray(UnityEngine_Renderer_o* __this, UnityEngine_Material_array* m, int64_t length)
	{
		void (UNITY_CALLING_CONVENTION t)(UnityEngine_Renderer_o*, UnityEngine_Material_array*, int64_t);
		return reinterpret_cast<decltype(t)>(Offsets::RendererSetMaterialArray)(__this, m, length);
	}

	void MaterialSetInt(UnityEngine_Material_o* __this, System_String_o* name, int32_t value)
	{
		void (UNITY_CALLING_CONVENTION t)(UnityEngine_Material_o*, System_String_o*, int32_t);
		return reinterpret_cast<decltype(t)>(Offsets::MaterialSetInt)(__this, name, value);
	}

	void MaterialSetRenderQueue(UnityEngine_Material_o* __this, int32_t value)
	{
		void (UNITY_CALLING_CONVENTION t)(UnityEngine_Material_o*, int32_t);
		return reinterpret_cast<decltype(t)>(Offsets::MaterialSetRenderQueue)(__this, value);
	}

	bool MaterialIsKeywordEnabled(UnityEngine_Material_o* __this, System_String_o* keyword)
	{
		bool (UNITY_CALLING_CONVENTION t)(UnityEngine_Material_o*, System_String_o*);
		return reinterpret_cast<decltype(t)>(Offsets::MaterialIsKeywordEnabled)(__this, keyword);
	}

	System_String_array* GetShaderKeywords(UnityEngine_Material_o* __this)
	{
		System_String_array* (UNITY_CALLING_CONVENTION t)(UnityEngine_Material_o*);
		return reinterpret_cast<decltype(t)>(Offsets::MaterialGetShaderKeywords)(__this);
	}

	int32_t ShaderGetPropertyCount(UnityEngine_Shader_o* __this)
	{
		int32_t(UNITY_CALLING_CONVENTION t)(UnityEngine_Shader_o*);
		return reinterpret_cast<decltype(t)>(Offsets::ShaderGetPropertyCount)(__this);
	}

	System_String_o* ShaderGetPropertyName(UnityEngine_Shader_o* __this, int32_t index)
	{
		System_String_o* (UNITY_CALLING_CONVENTION t)(UnityEngine_Shader_o*, int32_t);
		return reinterpret_cast<decltype(t)>(Offsets::ShaderGetPropertyName)(__this, index);
	}

	PlayerRoles_FirstPersonControl_FpcMotor_o* GetMotor(PlayerRoles_FirstPersonControl_FirstPersonMovementModule_o* movementModule)
	{
		PlayerRoles_FirstPersonControl_FpcMotor_o* (UNITY_CALLING_CONVENTION t)(PlayerRoles_FirstPersonControl_FirstPersonMovementModule_o*);
		return reinterpret_cast<decltype(t)>(Offsets::GetMotor)(movementModule);
	}

	UnityEngine_Vector3_o GetVelocity(PlayerRoles_FirstPersonControl_FpcMotor_o* motor)
	{
		UnityEngine_Vector3_o(UNITY_CALLING_CONVENTION t)(PlayerRoles_FirstPersonControl_FpcMotor_o*);
		return reinterpret_cast<decltype(t)>(Offsets::GetVelocity)(motor);

	}

	void ColorConstructor(UnityEngine_Color_o* __this, float r, float g, float b, float a)
	{
		void (UNITY_CALLING_CONVENTION t)(UnityEngine_Color_o*, float, float, float, float);
		return reinterpret_cast<decltype(t)>(Offsets::ColorConstructor)(__this, r, g, b, a);
	}

	UnityEngine_Component_o* GetComponent(UnityEngine_GameObject_o* __this, System_Type_o* type)
	{
		UnityEngine_Component_o* (UNITY_CALLING_CONVENTION t)(UnityEngine_GameObject_o*, System_Type_o*);
		return reinterpret_cast<decltype(t)>(Offsets::GetComponent)(__this, type);
	}

	void DrawRay(UnityEngine_Vector3_o start, UnityEngine_Vector3_o dir, UnityEngine_Color_o color, float duration)
	{
		void (UNITY_CALLING_CONVENTION t)(UnityEngine_Vector3_o, UnityEngine_Vector3_o, UnityEngine_Color_o, float);
		return reinterpret_cast<decltype(t)>(Offsets::DrawRay)(start, dir, color, duration);
	}

	UnityEngine_GameObject_o* CreatePrimitive(int32_t primitiveType)
	{
		UnityEngine_GameObject_o* (UNITY_CALLING_CONVENTION t)(int32_t);
		return reinterpret_cast<decltype(t)>(Offsets::CreatePrimitive)(primitiveType);
	}

	UnityEngine_Transform_o* GameObjectGetTransform(UnityEngine_GameObject_o* __this)
	{
		UnityEngine_Transform_o* (UNITY_CALLING_CONVENTION t)(UnityEngine_GameObject_o*);
		return reinterpret_cast<decltype(t)>(Offsets::GameObjectGetTransform)(__this);
	}

	System_String_o* ObjectGetName(UnityEngine_Object_o* __this)
	{
		System_String_o* (UNITY_CALLING_CONVENTION t)(UnityEngine_Object_o*);
		return reinterpret_cast<decltype(t)>(Offsets::ObjectGetName)(__this);
	}

	void TransformSetPositionAndRotation(UnityEngine_Transform_o* __this, UnityEngine_Vector3_o position, UnityEngine_Quaternion_o rotation)
	{
		void (UNITY_CALLING_CONVENTION t)(UnityEngine_Transform_o*, UnityEngine_Vector3_o, UnityEngine_Quaternion_o);
		return reinterpret_cast<decltype(t)>(Offsets::TransformSetPositionAndRotation)(__this, position, rotation);
	}

	UnityEngine_Material_array* RendererGetMaterialArray(UnityEngine_Renderer_o* __this)
	{
		UnityEngine_Material_array* (UNITY_CALLING_CONVENTION t)(UnityEngine_Renderer_o*);
		return reinterpret_cast<decltype(t)>(Offsets::RendererGetMaterialArray)(__this);
	}

	UnityEngine_Material_array* RendererGetSharedMaterialArray(UnityEngine_Renderer_o* __this)
	{
		UnityEngine_Material_array* (UNITY_CALLING_CONVENTION t)(UnityEngine_Renderer_o*);
		return reinterpret_cast<decltype(t)>(Offsets::RendererGetSharedMaterialArray)(__this);
	}

	void DrawLine(UnityEngine_Vector3_o start, UnityEngine_Vector3_o end, UnityEngine_Color_o color, float duration, float width)
	{
		void (UNITY_CALLING_CONVENTION t)(UnityEngine_Vector3_o, UnityEngine_Vector3_o, UnityEngine_Color_o, float, float);
		return reinterpret_cast<decltype(t)>(Offsets::DrawLine)(start, end, color, duration, width);
	}

	UnityEngine_Ray_o GetForwardRay(InventorySystem_Items_Firearms_Modules_HitscanHitregModuleBase_o* __this)
	{
		UnityEngine_Ray_o(UNITY_CALLING_CONVENTION t)(InventorySystem_Items_Firearms_Modules_HitscanHitregModuleBase_o*);
		return reinterpret_cast<decltype(t)>(Offsets::GetForwardRay)(__this);
	}

	PlayerRoles_PlayableScps_Scp079_Cameras_Scp079Camera_o* GetCurrentCamera(PlayerRoles_PlayableScps_Scp079_Cameras_Scp079CurrentCameraSync_o* __this)
	{
		PlayerRoles_PlayableScps_Scp079_Cameras_Scp079Camera_o* (UNITY_CALLING_CONVENTION t)(PlayerRoles_PlayableScps_Scp079_Cameras_Scp079CurrentCameraSync_o*);
		return reinterpret_cast<decltype(t)>(Offsets::GetCurrentCamera)(__this);
	}

	void SetWantsToJump(PlayerRoles_FirstPersonControl_FpcMotor_o* motor, bool value)
	{
		void(UNITY_CALLING_CONVENTION t)(PlayerRoles_FirstPersonControl_FpcMotor_o*, bool);
		return reinterpret_cast<decltype(t)>(Offsets::SetWantsToJump)(motor, value);

	}

	int8_t GetRoleId(ReferenceHub_o* hub)
	{
		int8_t(UNITY_CALLING_CONVENTION t)(ReferenceHub_o*);
		return reinterpret_cast<decltype(t)>(Offsets::GetRoleId)(hub);
	}

	int32_t GetHitboxType(HitboxIdentity_o* hitbox)
	{
		int(UNITY_CALLING_CONVENTION t)(HitboxIdentity_o*);
		return reinterpret_cast<decltype(t)>(Offsets::GetHitboxType)(hitbox);
	}

	void SetVelocity(PlayerRoles_FirstPersonControl_FpcMotor_o* motor, UnityEngine_Vector3_o velocity)
	{
		void(UNITY_CALLING_CONVENTION t)(PlayerRoles_FirstPersonControl_FpcMotor_o*, UnityEngine_Vector3_o);
		return reinterpret_cast<decltype(t)>(Offsets::GetVelocity)(motor, velocity);

	}

	float GetCurrentVertical(PlayerRoles_FirstPersonControl_FpcMouseLook_o* fpcMouseLook)
	{
		float(UNITY_CALLING_CONVENTION t)(PlayerRoles_FirstPersonControl_FpcMouseLook_o*);
		return reinterpret_cast<decltype(t)>(Offsets::GetCurrentVertical)(fpcMouseLook);
	}

	float GetCurrentHorizontal(PlayerRoles_FirstPersonControl_FpcMouseLook_o* fpcMouseLook)
	{
		float(UNITY_CALLING_CONVENTION t)(PlayerRoles_FirstPersonControl_FpcMouseLook_o*);
		return reinterpret_cast<decltype(t)>(Offsets::GetCurrentHorizontal)(fpcMouseLook);
	}

	UnityEngine_Quaternion_o LookRotation(UnityEngine_Vector3_o forward)
	{
		UnityEngine_Quaternion_o(UNITY_CALLING_CONVENTION t)(UnityEngine_Vector3_o);
		return reinterpret_cast<decltype(t)>(Offsets::LookRotation)(forward);
	}

	UnityEngine_Vector3_o GetEulerAngles(UnityEngine_Quaternion_o quaternion)
	{
		UnityEngine_Vector3_o(UNITY_CALLING_CONVENTION t)(UnityEngine_Quaternion_o);
		return reinterpret_cast<decltype(t)>(Offsets::GetEulerAngles)(quaternion);
	}

	void NetworkWriterWriteByte(Mirror_NetworkWriter_o* __this, uint8_t value)
	{
		void(UNITY_CALLING_CONVENTION t)(Mirror_NetworkWriter_o*, uint8_t);
		return reinterpret_cast<decltype(t)>(Offsets::NetworkWriterWriteByte)(__this, value);
	}

	void NetworkWriterWriteFloat(Mirror_NetworkWriter_o* writer, float value)
	{
		void(UNITY_CALLING_CONVENTION t)(Mirror_NetworkWriter_o*, float);
		return reinterpret_cast<decltype(t)>(Offsets::NetworkWriterWriteFloat)(writer, value);
	}

	void NetworkWriterWriteQuaternion(Mirror_NetworkWriter_o* writer, UnityEngine_Quaternion_o value)
	{
		void(UNITY_CALLING_CONVENTION t)(Mirror_NetworkWriter_o*, UnityEngine_Quaternion_o);
		return reinterpret_cast<decltype(t)>(Offsets::NetworkWriterWriteFloat)(writer, value);
	}

	void WriteReferenceHub(Mirror_NetworkWriter_o* writer, ReferenceHub_o* hub)
	{
		void (UNITY_CALLING_CONVENTION t)(Mirror_NetworkWriter_o*, ReferenceHub_o*);
		return reinterpret_cast<decltype(t)>(Offsets::NetworkWriterWriteReferenceHub)(writer, hub);
	}

	void NetworkWriterConstructor(Mirror_NetworkWriter_o* writer)
	{
		void(UNITY_CALLING_CONVENTION t)(Mirror_NetworkWriter_o*);
		return reinterpret_cast<decltype(t)>(Offsets::NetworkWriterConstructor)(writer);
	}

	void SetCurrentVertical(PlayerRoles_FirstPersonControl_FpcMouseLook_o* fpcMouseLook, float pitch)
	{
		void(UNITY_CALLING_CONVENTION t)(PlayerRoles_FirstPersonControl_FpcMouseLook_o*, float);
		return reinterpret_cast<decltype(t)>(Offsets::SetCurrentVertical)(fpcMouseLook, pitch);
	}

	void SetCurrentHorizontal(PlayerRoles_FirstPersonControl_FpcMouseLook_o* fpcMouseLook, float yaw)
	{
		void(UNITY_CALLING_CONVENTION t)(PlayerRoles_FirstPersonControl_FpcMouseLook_o*, float);
		return reinterpret_cast<decltype(t)>(Offsets::SetCurrentHorizontal)(fpcMouseLook, yaw);
	}

	void GetMouseInput(PlayerRoles_FirstPersonControl_FpcMouseLook_o* fpcMouseLook, float* hrot, float* vrot)
	{
		void(UNITY_CALLING_CONVENTION t)(PlayerRoles_FirstPersonControl_FpcMouseLook_o*, float*, float*);
		return reinterpret_cast<decltype(t)>(Offsets::GetMouseInput)(fpcMouseLook, hrot, vrot);
	}

	System_Reflection_MethodInfo_array* GetMethods(System_Type_o* type)
	{
		System_Reflection_MethodInfo_array* (UNITY_CALLING_CONVENTION t)(System_Type_o*);
		return reinterpret_cast<decltype(t)>(Offsets::GetMethods)(type);
	}

	struct Vector3 GetCenter(Unity::CComponent* component)
	{
		struct Vector3(UNITY_CALLING_CONVENTION t)(Unity::CComponent*);
		return reinterpret_cast<decltype(t)>(Offsets::GetCenter)(component);
	}

	void ShotRequestConstructor(InventorySystem_Items_Firearms_Modules_AutomaticActionModule_ShotRequest_o* __this, InventorySystem_Items_Firearms_Modules_AutomaticActionModule_o* mod)
	{
		void(UNITY_CALLING_CONVENTION t)(InventorySystem_Items_Firearms_Modules_AutomaticActionModule_ShotRequest_o*, InventorySystem_Items_Firearms_Modules_AutomaticActionModule_o*);
		return reinterpret_cast<decltype(t)>(Offsets::ShotRequestConstructor)(__this, mod);
	}

	void TeslaAbilityTrigger(PlayerRoles_PlayableScps_Scp079_Scp079TeslaAbility_o* __this)
	{
		void (UNITY_CALLING_CONVENTION t)(PlayerRoles_PlayableScps_Scp079_Scp079TeslaAbility_o*);
		return reinterpret_cast<decltype(t)>(Offsets::TeslaAbilityTrigger)(__this);
	}

	void ObjectDestroy(UnityEngine_Object_o* obj, float delay)
	{
		void (UNITY_CALLING_CONVENTION t)(UnityEngine_Object_o*, float);
		return reinterpret_cast<decltype(t)>(Offsets::ObjectDestroy)(obj, delay);
	}

	UnityEngine_Component_o* GameObjectGetComponentInChildren(UnityEngine_GameObject_o* __this, System_Type_o* type, bool includeInactive)
	{
		UnityEngine_Component_o* (UNITY_CALLING_CONVENTION t)(UnityEngine_GameObject_o*, System_Type_o*, bool);
		return reinterpret_cast<decltype(t)>(Offsets::GameObjectGetComponentInChildren)(__this, type, includeInactive);
	}
	
	UnityEngine_Component_o* GameObjectGetComponentInParent(UnityEngine_GameObject_o* __this, System_Type_o* type, bool includeInactive)
	{
		UnityEngine_Component_o* (UNITY_CALLING_CONVENTION t)(UnityEngine_GameObject_o*, System_Type_o*, bool);
		return reinterpret_cast<decltype(t)>(Offsets::GameObjectGetComponentInParent)(__this, type, includeInactive);
	}

	void AddOnBeforePlayerDestroyed(System_Action_ReferenceHub__o* action)
	{
		void(UNITY_CALLING_CONVENTION t)(System_Action_ReferenceHub__o*);
		return reinterpret_cast<decltype(t)>(Offsets::AddOnBeforePlayerDestroyed)(action);
	}

	void OnBeforePlayerDestroyed(ReferenceHub_o* player)
	{
		std::cout << "player destroyed\n";
		auto s = std::find(PlayerList.begin(), PlayerList.end(), player);
		if (s != PlayerList.end()) PlayerList.erase(s);
	}

	float GetAbsorbedAhpDamage(PlayerStatsSystem_StandardDamageHandler_o* __this)
	{
		float(UNITY_CALLING_CONVENTION t)(PlayerStatsSystem_StandardDamageHandler_o*);
		return reinterpret_cast<decltype(t)>(Offsets::GetAbsorbedAhpDamage)(__this);
	}
	
	float GetAbsorbedHumeDamage(PlayerStatsSystem_StandardDamageHandler_o* __this)
	{
		float(UNITY_CALLING_CONVENTION t)(PlayerStatsSystem_StandardDamageHandler_o*);
		return reinterpret_cast<decltype(t)>(Offsets::GetAbsorbedHumeDamage)(__this);
	}

	float GetDealtHealthDamage(PlayerStatsSystem_StandardDamageHandler_o* __this)
	{
		float(UNITY_CALLING_CONVENTION t)(PlayerStatsSystem_StandardDamageHandler_o*);
		return reinterpret_cast<decltype(t)>(Offsets::GetDealtHealthDamage)(__this);
	}

	float GetTotalDamageDealt(PlayerStatsSystem_StandardDamageHandler_o* __this)
	{
		float(UNITY_CALLING_CONVENTION t)(PlayerStatsSystem_StandardDamageHandler_o*);
		return reinterpret_cast<decltype(t)>(Offsets::GetTotalDamageDealt)(__this);
	}

	float GetBaseFireRate(InventorySystem_Items_Firearms_Modules_AutomaticActionModule_o* __this)
	{
		float (UNITY_CALLING_CONVENTION t)(InventorySystem_Items_Firearms_Modules_AutomaticActionModule_o*);
		return reinterpret_cast<decltype(t)>(Offsets::GetBaseFireRate)(__this);
	}

	float GetEffectiveBlinkDistance(PlayerRoles_PlayableScps_Scp173_Scp173TeleportAbility_o* __this)
	{
		float (UNITY_CALLING_CONVENTION t)(PlayerRoles_PlayableScps_Scp173_Scp173TeleportAbility_o*);
		return reinterpret_cast<decltype(t)>(Offsets::GetEffectiveBlinkDistance)(__this);
	}

#pragma endregion

#pragma region Custom Functions

	ImColor GetTeamColor(ReferenceHub_o* hub)
	{
	
		ImColor color = ImColor(255, 255, 255, 255);

		char team = GetTeam(hub);

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

		return color;
	}

	void LogNetworkWriter(Mirror_NetworkWriter_o* writer, const char* name)
	{
		console.file << name;

		for (int i = 0; i < writer->fields.buffer->max_length; i++)
		{
			console.file << writer->fields.buffer->m_Items[i] << " ";
		}

		console.file << "EoF";
	}

	bool HasFirearmEquipped(InventorySystem_Items_Firearms_Firearm_o** firearm)
	{
		if (vars::LocalPlayer == nullptr)
			return false;

		InventorySystem_Items_ItemBase_o* base = vars::LocalPlayer->fields.inventory->fields._curInstance;

		if (base == nullptr)
			return false;

		if (base->fields.Category != 4)	
			return false;

		*firearm = (InventorySystem_Items_Firearms_Firearm_o*)base;
		return true;
	}

	bool worldtoscreen(UnityEngine_Vector3_o world, Vector2& screen)
	{
		UnityEngine_Camera_o* CameraMain = Functions::GetMainCamera(); // Get The Main Camera
		if (!CameraMain) {
			std::cout << "Cam failed" << "\n";
			return false;
		}

		UnityEngine_Vector3_o buffer = Functions::WorldToScreenPoint(CameraMain, world, 2);
		
		if (buffer.fields.x > vars::screen_size.x || buffer.fields.y > vars::screen_size.y || buffer.fields.x < 0 || buffer.fields.y < 0 || buffer.fields.z < 0) // check if point is on screen
		{
			return false;
		}

		if (buffer.fields.z > 0.0f) // Check if point is in view
		{
			screen = Vector2(buffer.fields.x, vars::screen_size.y - buffer.fields.y);
		}

		if (screen.x > 0 || screen.y > 0) // Check if point is in view
		{
			return true;
		}
		
		return false;
	}

	UnityEngine_Vector3_o Normalize(UnityEngine_Vector3_o vector3)
	{
		UnityEngine_Vector3_o out;

		out.fields.x = 0;
		out.fields.y = 0;
		out.fields.z = 0;

		float len = sqrt(vector3.fields.x * vector3.fields.x + vector3.fields.y * vector3.fields.y + vector3.fields.z * vector3.fields.z);

		if (len == 0)
			return out;

		out.fields.x = vector3.fields.x / len;
		out.fields.y = vector3.fields.y / len;
		out.fields.z = vector3.fields.z / len;

		return out;
	}

	std::string SystemStringOToString(System_String_o* str)
	{
		if (str == nullptr) return "xxx";

		// Pointer auf den ersten Char
		const uint16_t* utf16_str = reinterpret_cast<const uint16_t*>(&(str->fields._firstChar));
		int length = str->fields._stringLength;

		// Konvertiere UTF-16 zu UTF-8 (std::string)
		std::u16string u16str(utf16_str, utf16_str + length);
		std::string result;
		result.reserve(length); // Reserve optional

		// Einfache Konvertierung (nur ASCII-safe)
		for (char16_t ch : u16str) {
			if (ch < 0x80) {
				result.push_back(static_cast<char>(ch));
			}
			else {
				// Hier solltest du eigentlich eine echte UTF-16 → UTF-8 Konvertierung machen
				result.push_back('?'); // Platzhalter
			}
		}

		return result;
	}

	bool InLineOfSight(ReferenceHub_o* hub, UnityEngine_Vector3_o position)
	{
		bool hit = Functions::Linecast(Functions::GetPosition(hub->fields.PlayerCameraReference), position, 1208238081, 0);
		return !hit;
	}

	float GetDistance(UnityEngine_Vector3_o position1, UnityEngine_Vector3_o position2)
	{
		return sqrt(pow(position1.fields.x - position2.fields.x, 2) + pow(position1.fields.y - position2.fields.y, 2) + pow(position1.fields.z - position2.fields.z, 2));
	}

	float GetScreenDistance(Vector2 position1, Vector2 position2)
	{
		return sqrt(pow(position1.x - position2.x, 2) + pow(position1.y - position2.y, 2));
	}

	unsigned char (UNITY_CALLING_CONVENTION ApplyDamage)(PlayerStatsSystem_StandardDamageHandler_o* target, ReferenceHub_o* hub);

	unsigned char ApplyDamage_hk(PlayerStatsSystem_StandardDamageHandler_o* target, ReferenceHub_o* hub)
	{
		if (hub != vars::LocalPlayer)
		{
			PlaySound((LPCSTR)skeetSound, NULL, SND_MEMORY | SND_ASYNC | SND_NOSTOP);
		}
	
		UnityEngine_Vector3_o playerPosition = Functions::GetPosition(hub->fields.PlayerCameraReference);

		unsigned char handlerOutput = Functions::ApplyDamage(target, hub);
		float total = GetTotalDamageDealt(target);
		float ahp = GetAbsorbedAhpDamage(target);
		float hume = GetAbsorbedHumeDamage(target);
		float health = GetDealtHealthDamage(target);

		if (ahp)
		{
			IndicatorList.push_back(CreateIndicator(playerPosition, DamageType::ahp, ahp));
		}

		if (hume)
		{
			IndicatorList.push_back(CreateIndicator(playerPosition, DamageType::hume, hume));
		}

		if (health)
		{
			IndicatorList.push_back(CreateIndicator(playerPosition, DamageType::health, health));
		}


		//if (ahp) DamageIndicator::indicatorList.push_back(&DamageIndicator::DamageIndicator(playerPosition, DamageType::ahp, ahp));
		//if (hume) DamageIndicator::indicatorList.push_back(&DamageIndicator::DamageIndicator(playerPosition, DamageType::hume, hume));
		//if (health) DamageIndicator::indicatorList.push_back(&DamageIndicator::DamageIndicator(playerPosition, DamageType::health, health));

		return handlerOutput;
	}

	double GetWeaponCooldown(InventorySystem_Items_Firearms_Firearm_o* firearm)
	{
		auto mods = firearm->fields._modules;

		InventorySystem_Items_ItemBase_o* base = (InventorySystem_Items_ItemBase_o*)firearm;

		if (base->fields.ItemTypeId == 39)
			return 0.5;

		InventorySystem_Items_Firearms_Modules_AutomaticActionModule_o* autoModule = (InventorySystem_Items_Firearms_Modules_AutomaticActionModule_o*)mods->m_Items[0];

		float fireRate = Functions::GetBaseFireRate(autoModule) * 0.9;
		double cooldown = 1 / fireRate;

		return cooldown;
	}

	double GetLocalWeaponCooldown()
	{
		InventorySystem_Items_Firearms_Firearm_o* firearm;
		if (Functions::HasFirearmEquipped(&firearm))
		{
			return Functions::GetWeaponCooldown(firearm);
		}

		return 0;
	}

	UnityEngine_GameObject_o* CreateRay(UnityEngine_Vector3_o start, UnityEngine_Vector3_o end, float width, UnityEngine_Color_o color)
	{

		UnityEngine_Vector3_o direction;
		direction.fields.x = end.fields.x - start.fields.x;
		direction.fields.y = end.fields.y - start.fields.y;
		direction.fields.z = end.fields.z - start.fields.z;

		UnityEngine_Vector3_o fixedPosition;
		fixedPosition.fields.x = start.fields.x + 0.5 * direction.fields.x;
		fixedPosition.fields.y = start.fields.y + 0.5 * direction.fields.y;
		fixedPosition.fields.z = start.fields.z + 0.5 * direction.fields.z;

		UnityEngine_Quaternion_o rotation = Functions::LookRotation(direction);
		auto eulerAngles = Functions::GetEulerAngles(rotation);
		eulerAngles.fields.x = eulerAngles.fields.x - 90;
		UnityEngine_Quaternion_o fixedRotation = Functions::QuaternionByEuler(eulerAngles.fields.x, eulerAngles.fields.y, eulerAngles.fields.z);

		UnityEngine_Material_o* material = new UnityEngine_Material_o;
		UnityEngine_Shader_o* shader = Functions::ShaderFind((System_String_o*)IL2CPP::String::New("Hidden/Internal-Colored"));
		Functions::MaterialConstructor(material, shader);

		UnityEngine_GameObject_o* tempGameObject = Functions::CreatePrimitive(2);
		UnityEngine_Transform_o* tempTransform = Functions::GameObjectGetTransform(tempGameObject);

		UnityEngine_Vector3_o scale;
		scale.fields.x = width;
		scale.fields.y = 0.5 * Functions::GetDistance(start, end);
		scale.fields.z = width;

		Functions::TransformSetLocalScale(tempTransform, scale);
		Functions::TransformSetPositionAndRotation(tempTransform, fixedPosition, fixedRotation);

		Unity::CGameObject* cgo = (Unity::CGameObject*)tempGameObject;
		UnityEngine_MeshRenderer_o* meshRenderer = (UnityEngine_MeshRenderer_o*)cgo->GetComponent("MeshRenderer");
		UnityEngine_Object_o* collider = (UnityEngine_Object_o*)cgo->GetComponent("Collider");

		Functions::ObjectDestroy(collider, 0.f);

		Functions::MaterialSetInt(material, (System_String_o*)IL2CPP::String::New("_ZWrite"), 0);
		Functions::MaterialSetInt(material, (System_String_o*)IL2CPP::String::New("_ZTest"), 8);
		Functions::MaterialSetRenderQueue(material, 3500);

		Functions::MaterialSetColor(material, color);
		Functions::RendererSetMaterial((UnityEngine_Renderer_o*)meshRenderer, material);

		return tempGameObject;
	}

	BacktrackRecord* GetBacktrackRecord(ReferenceHub_o* target)
	{
		BacktrackRecord* bestRecord = nullptr;
		float screenDistance = 9999;
		double age = 0;

		for (int i = 0; i < BacktrackRecordList.size(); i++)
		{
			BacktrackRecord* record = BacktrackRecordList[i];

			if (record->deprecated)
				continue;

			if (record->hub != target)
				continue;

			Vector2 screenPosition;

			if (!Functions::worldtoscreen(record->headPosition, screenPosition))
				continue;

			float distance = Functions::GetScreenDistance(vars::screen_center, screenPosition);

			if (distance > screenDistance)
				continue;

			bestRecord = record;
			screenDistance = distance;
			age = bestRecord->age;
		}

		if (bestRecord == nullptr)
			return bestRecord;

		double cooldown = min(Functions::GetLocalWeaponCooldown(), backtrack::backtracktime);

		backtrack::nextShotStamp = std::chrono::system_clock::now() + std::chrono::milliseconds(int(cooldown * 1000) - int(bestRecord->age * 1000));

		for (int i = 0; i < BacktrackRecordList.size(); i++)
		{
			BacktrackRecord* record = BacktrackRecordList[i];

			if (record->age < bestRecord->age + cooldown)
				continue;

			record->deprecated = true;
		}

		return bestRecord;
	}

	void (UNITY_CALLING_CONVENTION OnPlayerMove)(PlayerRoles_FirstPersonControl_Thirdperson_AnimatedCharacterModel_o* animatedCharacterModel);

	void OnPlayerMove_hk(PlayerRoles_FirstPersonControl_Thirdperson_AnimatedCharacterModel_o* animatedCharacterModel)
	{
		OnPlayerMove(animatedCharacterModel);

		if (std::chrono::system_clock::now() < backtrack::nextShotStamp)
			return;

		PlayerRoles_FirstPersonControl_Thirdperson_CharacterModel_o* characterModel = (PlayerRoles_FirstPersonControl_Thirdperson_CharacterModel_o*)animatedCharacterModel;

		if (characterModel == nullptr)
			return;

		ReferenceHub_o* owner = characterModel->fields._OwnerHub_k__BackingField;

		if (owner == nullptr)
			return;

		if (owner == vars::LocalPlayer)
			return;

		BacktrackRecord* record = new BacktrackRecord;
		record->hub = owner;
		
		UnityEngine_Vector3_o position = Functions::GetPosition(owner->fields.PlayerCameraReference);

		record->headPosition = position;
		record->footPosition = position;
		record->footPosition.fields.y = record->footPosition.fields.y - 1.4;

		position.fields.y = position.fields.y - 0.629;

		RelativePositioning_RelativePosition_o* relativePosition = new RelativePositioning_RelativePosition_o;

		Functions::RelativePositionConstructor(relativePosition, position);

		record->relativePosition = relativePosition;
		record->creationStamp = std::chrono::system_clock::now();
		BacktrackRecordList.push_back(record);
	}

	void Backtracking(InventorySystem_Items_Firearms_Modules_Misc_ShotBacktrackData_o* backtrackData)
	{
		if (!vars::backtracking)
			return;

		if (backtrackData->fields.HasPrimaryTarget)
		{

			ReferenceHub_o* target = backtrackData->fields.PrimaryTargetHub;
			BacktrackRecord* targetRecord;

			if (target == nullptr)
				return;

			targetRecord = Functions::GetBacktrackRecord(target);

			if (targetRecord == nullptr)
				return;

			backtrackData->fields.CreationTimestamp = backtrackData->fields.CreationTimestamp - targetRecord->age;
			backtrackData->fields.PrimaryTargetRelativePosition = *targetRecord->relativePosition;
		}
	}

	void (UNITY_CALLING_CONVENTION WriteSelf)(InventorySystem_Items_Firearms_Modules_Misc_ShotBacktrackData_o backtrackData, Mirror_NetworkWriter_o* writer);

	bool UltraRapidFire(InventorySystem_Items_Firearms_Modules_Misc_ShotBacktrackData_o backtrackData, Mirror_NetworkWriter_o* writer)
	{


		double cooldown = GetLocalWeaponCooldown();
		double originalTime = backtrackData.fields.CreationTimestamp;

		backtrackData.fields.CreationTimestamp = originalTime - cooldown;
		WriteSelf(backtrackData, writer);

		backtrackData.fields.CreationTimestamp = originalTime;
		WriteSelf(backtrackData, writer);

		return true;
	}

	void WriteSelf_hk(InventorySystem_Items_Firearms_Modules_Misc_ShotBacktrackData_o backtrackData, Mirror_NetworkWriter_o* writer)
	{
		Functions::Backtracking(&backtrackData);
		Functions::WriteSelf(backtrackData, writer);
	}

	void (UNITY_CALLING_CONVENTION WriteShotRequest)(InventorySystem_Items_Firearms_Modules_AutomaticActionModule_ShotRequest_o __this, Mirror_NetworkWriter_o* writer);

	void WriteShotRequest_hk(InventorySystem_Items_Firearms_Modules_AutomaticActionModule_ShotRequest_o __this, Mirror_NetworkWriter_o* writer)
	{

		//console.Log("Correction", __this.fields.CorrectionVersion);
		//console.Log("Reserve", __this.fields.PredictedReserve);

		
		WriteShotRequest(__this, writer);


		//urfRequest->fields.PredictedReserve--;
		//console.Log("URF Correction", urfRequest->fields.CorrectionVersion);
		//console.Log("URF Reserve", urfRequest->fields.PredictedReserve);

		//urfRequest->fields.BacktrackData.fields.CreationTimestamp = originalTime;
		//WriteShotRequest(*urfRequest, writer);

	}

	void (UNITY_CALLING_CONVENTION ServerSendResponse)(InventorySystem_Items_Firearms_Modules_AutomaticActionModule_o* __this, InventorySystem_Items_Firearms_Modules_AutomaticActionModule_ShotRequest_o request);

	void ServerSendResponse_hk(InventorySystem_Items_Firearms_Modules_AutomaticActionModule_o* __this, InventorySystem_Items_Firearms_Modules_AutomaticActionModule_ShotRequest_o request)
	{
		console.WriteLine("responded");
		ServerSendResponse(__this, request);
	}

	void (UNITY_CALLING_CONVENTION ServerSendRejection)(InventorySystem_Items_Firearms_Modules_AutomaticActionModule_o* __this, int32_t reason, uint8_t errorCode);

	void ServerSendRejection_hk(InventorySystem_Items_Firearms_Modules_AutomaticActionModule_o* __this, int32_t reason, uint8_t errorCode)
	{
		console.Log("Reason", reason);
		console.Log("Code", errorCode);

		ServerSendRejection(__this, reason, errorCode);
	}

	void (UNITY_CALLING_CONVENTION ServerOnRequestTimedOut)(InventorySystem_Items_Firearms_Modules_AutomaticActionModule_o* __this, InventorySystem_Items_Firearms_Modules_AutomaticActionModule_ShotRequest_o request);

	void ServerOnRequestTimedOut_hk(InventorySystem_Items_Firearms_Modules_AutomaticActionModule_o* __this, InventorySystem_Items_Firearms_Modules_AutomaticActionModule_ShotRequest_o request)
	{
		console.WriteLine("request timed out");
		ServerOnRequestTimedOut(__this, request);
	}

	void (UNITY_CALLING_CONVENTION SendToTransport)(Mirror_NetworkConnectionToServer_o* __this, System_ArraySegment_byte__o segment, int32_t channelId);

	void SendToTransport_hk(Mirror_NetworkConnectionToServer_o* __this, System_ArraySegment_byte__o segment, int32_t channelId)
	{
		if (!ultraRapidFire::setconn)
		{
			ultraRapidFire::conn = __this;
			ultraRapidFire::setconn = true;
		}

		SendToTransport(__this, segment, channelId);
	}

	void PrintShit(Mirror_Batcher_o* __this, System_ArraySegment_byte__o message, double timeStamp)
	{
		if (message.fields._count == 2 || message.fields._count == 13 || message.fields._count == 8)
			return;

		console.WriteLine(message.fields._count);

	}

	void (UNITY_CALLING_CONVENTION AddMessage)(Mirror_Batcher_o* __this, System_ArraySegment_byte__o message, double timeStamp);

	void AddMessage_hk(Mirror_Batcher_o* __this, System_ArraySegment_byte__o message, double timeStamp)
	{
		if (!ultraRapidFire::gotBatcher)
		{
			ultraRapidFire::batcher = __this;
			ultraRapidFire::gotBatcher = true;
		}

		//PrintShit(__this, message, timeStamp);

		AddMessage(__this, message, timeStamp);
	}

	bool (UNITY_CALLING_CONVENTION GetNextMessage)(Mirror_Unbatcher_o* __this, System_ArraySegment_byte__o* message, double* remoteTimeStamp);

	bool GetNextMessage_hk(Mirror_Unbatcher_o* __this, System_ArraySegment_byte__o* message, double* remoteTimeStamp)
	{
		bool value = GetNextMessage(__this, message, remoteTimeStamp);

		if (message->fields._count == 0 || message->fields._count == 2 || message->fields._count == 4 || message->fields._count == 10 || message->fields._count == 6)
			return value;

		if (message->fields._count == 23)
		{
			console.file << "req";

			for (int i = 0; i < message->fields._count; i++)
			{
				console.file << message->fields._array->m_Items[message->fields._offset + i] << "  ";
			}

			console.file << "EOF";
			//console.WriteLine("wrote stuff");
		}

		//console.WriteLine(message->fields._count);

		return value;
	}

	void SendFire()
	{
		InventorySystem_Items_Firearms_Firearm_o* firearm;
		if (Functions::HasFirearmEquipped(&firearm))
		{
			InventorySystem_Items_Firearms_Modules_AutomaticActionModule_o* mod = (InventorySystem_Items_Firearms_Modules_AutomaticActionModule_o*)firearm->fields._modules->m_Items[0];
			InventorySystem_Items_Firearms_Modules_AutomaticActionModule_ShotRequest_o* urfRequest = new InventorySystem_Items_Firearms_Modules_AutomaticActionModule_ShotRequest_o;
			Functions::ShotRequestConstructor(urfRequest, mod);

			unsigned char header[7] = { 0xE1, 0xB8, 0xFF, 0xFF, 0xFF, 0x1D, 0x00 };
			header[2] = (unsigned char)(InventorySystem_Items_ItemBase_o*)(firearm)->fields._ItemSerial_k__BackingField & 0xFF;
			header[3] = (unsigned char)(InventorySystem_Items_ItemBase_o*)((firearm)->fields._ItemSerial_k__BackingField >> 8) & 0xFF;
			header[4] = (unsigned char)(InventorySystem_Items_ItemBase_o*)(firearm)->fields.ItemTypeId & 0xFF;

			Mirror_NetworkWriter_o* writer1 = (Mirror_NetworkWriter_o*)Functions::NetworkWriterPoolGet();

			for (int i = 0; i < 7; i++)
			{
				Functions::NetworkWriterWriteByte(writer1, header[i]);
			}

			Functions::WriteShotRequest(*urfRequest, writer1);

			auto segment = Functions::NetworkWriterToArraySegment(writer1);
			Functions::AddMessage(ultraRapidFire::batcher, segment, urfRequest->fields.BacktrackData.fields.CreationTimestamp);
		}
	}

	void InspectShader(UnityEngine_Shader_o* shader, UnityEngine_Material_o* material)
	{
		int propertyCount = Functions::ShaderGetPropertyCount(shader);

		for (int i = 0; i < propertyCount; i++)
		{
			console.Log(Functions::SystemStringOToString(Functions::ShaderGetPropertyName(shader, i)), i);
		}


		auto shaderKeywords = Functions::GetShaderKeywords(material);

		for (int i = 0; i < shaderKeywords->max_length; i++)
		{
			auto keyword = shaderKeywords->m_Items[i];

			if (Functions::MaterialIsKeywordEnabled(material, keyword))
			{
				console.WriteLine(Functions::SystemStringOToString(keyword) + ": true");
			}
			else
			{
				console.WriteLine(Functions::SystemStringOToString(keyword) + ": false");
			}
		}
	}

	void CreateTracer(RelativePositioning_RelativePosition_o* relPosition)
	{
		return;

		console.WriteLine("tracers");

		InventorySystem_Items_Firearms_Firearm_o* firearm;
		if (HasFirearmEquipped(&firearm))
		{
			Tracer* tracer = new Tracer;
			auto position = RelativePositionGetPosition(relPosition);

			UnityEngine_Color_o* color = new UnityEngine_Color_o;
			ColorConstructor(color, 0, 1, 1, 0.10);

			tracer->gameObject = CreateRay(GetPosition(vars::LocalPlayer->fields.PlayerCameraReference), position, 0.05, *color);
			tracer->livingTime = tracers::standardLivingTime;

			TracerList.push_back(tracer);

			delete color;
			console.WriteVector(position);
		}
	}

	void (UNITY_CALLING_CONVENTION RelativePositionConstructorNetworkReader)(RelativePositioning_RelativePosition_o* __this, Mirror_NetworkReader_o* reader);

	void RelativePositionConstructorNetworkReader_hk(RelativePositioning_RelativePosition_o* __this, Mirror_NetworkReader_o* reader)
	{
	
		RelativePositionConstructorNetworkReader(__this, reader);

		__try
		{

			if (reader->fields.buffer.fields._array->m_Items[0] == 8)
				CreateTracer(__this);
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			return;
		}
	}

	void(UNITY_CALLING_CONVENTION Scp173TeleportAbilityClientWriteCmd)(PlayerRoles_PlayableScps_Scp173_Scp173TeleportAbility_o* __this, Mirror_NetworkWriter_o* writer);

	void Scp173TeleportAbilityClientWriteCmd_hk(PlayerRoles_PlayableScps_Scp173_Scp173TeleportAbility_o* __this, Mirror_NetworkWriter_o* writer)
	{
		
		if (!vars::autoTeleport)
		{
			Scp173TeleportAbilityClientWriteCmd(__this, writer);
			return;
		}
		
		if (scp::bestTarget == nullptr)
		{
			Scp173TeleportAbilityClientWriteCmd(__this, writer);
			return;
		}
		
		if (scp::bestTargetDistance > GetEffectiveBlinkDistance(__this))
		{
			Scp173TeleportAbilityClientWriteCmd(__this, writer);
			return;
		}
		

		char data = __this->fields._cmdData & 0xFF;

		if ((data & 2) != 2)
		{
			Scp173TeleportAbilityClientWriteCmd(__this, writer);
			return;
		}

		console.WriteLine("real");
		console.WriteVector(__this->fields._tpPosition);
		console.WriteLine(__this->fields._targetDis);

		auto start = GetPosition(vars::LocalPlayer->fields.PlayerCameraReference);
		auto end = GetPosition(scp::bestTarget->fields.PlayerCameraReference);
		float distance = GetDistance(start, end);


		UnityEngine_Vector3_o direction;
		direction.fields.x = end.fields.x - start.fields.x;
		direction.fields.y = end.fields.y - start.fields.y;
		direction.fields.z = end.fields.z - start.fields.z;


		UnityEngine_Vector3_o normDirection = Functions::Normalize(direction);
		UnityEngine_Quaternion_o quaternion = Functions::LookRotation(normDirection);

		NetworkWriterWriteByte(writer, data);
		NetworkWriterWriteQuaternion(writer, quaternion);
		NetworkWriterWriteFloat(writer, distance);
		WriteReferenceHub(writer, scp::bestTarget);


		console.WriteLine("done");
	}

#pragma endregion
}