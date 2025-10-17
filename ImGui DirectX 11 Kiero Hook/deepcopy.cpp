#include "deepcopy.h"

/*
bool pickupadded = false;

void OnPickupAdded(Il2CppObject* obj)
{
	if (!obj || !obj->klass)
	{
		std::cout << "invalid object\n";
		return;
	}

	std::cout << obj->klass->_1.name << "\n";

	InventorySystem_Items_Pickups_ItemPickupBase_o* pickup = reinterpret_cast<InventorySystem_Items_Pickups_ItemPickupBase_o*>(obj);
	std::cout << pickup->klass->_1.name << "\n";
	std::cout << "added new pickup\n";
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

void OnBeforePickupDestroyed(Il2CppObject* obj)
{

	if (!obj || !obj->klass)
	{
		std::cout << "invalid object\n";
		return;
	}


	std::cout << obj->klass->_1.name << "\n";
	InventorySystem_Items_Pickups_ItemPickupBase_o* pickup = reinterpret_cast<InventorySystem_Items_Pickups_ItemPickupBase_o*>(obj);

	std::cout << "removed " << pickup->fields.Info.fields.ItemId << "\n";

	if (!pickup || !pickup->klass)
	{
		std::cout << "invalid object\n";
	}

	pauseitem = true;
	auto s = std::find(ItemList.begin(), ItemList.end(), pickup);
	if (s != ItemList.end()) ItemList.erase(s);
	pauseitem = false;
}

void AddPickup(System_Action_ItemPickupBase__o* action)
{
	pickupadded = true;

	Unity::il2cppType pickupType = {};
	pickupType.m_pDummy = InventoryPickupClass;
	pickupType.m_uType = 12;
	pickupType.m_uAttributes = 0;
	pickupType.m_uMods = 0;
	pickupType.m_uByref = 0;
	pickupType.m_uPinned = 0;

	Unity::il2cppType voidType = {};
	voidType.m_uType = 1;         // 1 = IL2CPP_TYPE_VOID
	voidType.m_uAttributes = 0;
	voidType.m_uMods = 0;
	voidType.m_uByref = 0;
	voidType.m_uPinned = 0;

	static Unity::il2cppParameterInfo paramInfo = {
		"obj",         // Name
		0,             // Position
		0,             // Token (optional)
		&pickupType  // Typ (z. B. ItemPickupBase)
	};

	struct Unity::il2cppMethodInfo onBeforePickupDestroyedMethodInfo =
	{
		.m_pMethodPointer = (void*)&Functions::OnBeforePickupDestroyed,
		.m_pInvokerMethod = nullptr,                  // optional
		.m_pName = "OnPickupDestroyed",
		.m_pClass = (Unity::il2cppClass*)action->fields.method_info->klass,                            // z. B. klass vom originalen MethodInfo
		.m_pReturnType = &voidType,                  // z. B. void
		.m_pParameters = &paramInfo,
		.m_pRGCTX = nullptr,
		.m_pGenericMethod = nullptr,
		.m_uToken = 0,
		.m_uFlags = 0x0006,                           // public | static
		.m_uFlags2 = 0,
		.m_uSlot = 0xFFFF,                            // kein vtable slot
		.m_uArgsCount = 1,
		.m_uGeneric = 0,
		.m_uInflated = 0,
		.m_uWrapperType = 0,
		.m_uMarshaledFromNative = 0
	};

	System_Action_ItemPickupBase__o* onBeforePickupDestroyed = (System_Action_ItemPickupBase__o*)calloc(1, sizeof(System_Action_ItemPickupBase__o));
	System_Action_ItemPickupBase__o* onPickupAdded = (System_Action_ItemPickupBase__o*)calloc(1, sizeof(System_Action_ItemPickupBase__o));

	memcpy(onBeforePickupDestroyed, action, sizeof(System_Action_ItemPickupBase__o));
	memcpy(onPickupAdded, action, sizeof(System_Action_ItemPickupBase__o));

	onBeforePickupDestroyed->fields.method_ptr = (intptr_t)&Functions::OnBeforePickupDestroyed;
	onBeforePickupDestroyed->fields.invoke_impl = (intptr_t)&Functions::OnBeforePickupDestroyed;
	onBeforePickupDestroyed->fields.method_info = (System_Reflection_MethodInfo_o*)&onBeforePickupDestroyedMethodInfo;

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
*/