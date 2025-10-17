#pragma once
#include <chrono>


struct Room
{
	const char* name;
	UnityEngine_Vector3_o position;
};

struct BacktrackRecord
{
	ReferenceHub_o* hub;
	UnityEngine_Vector3_o headPosition;
	UnityEngine_Vector3_o footPosition;

	RelativePositioning_RelativePosition_o* relativePosition;

	std::chrono::system_clock::time_point creationStamp;
	double age;

	bool deprecated = false;
};

struct Tracer
{
	UnityEngine_GameObject_o* gameObject;

	int livingTime;
};

std::vector<UnityEngine_Animator_o*> AnimatorList(NULL);
std::vector<ReferenceHub_o*> PlayerList(NULL);
std::vector<InventorySystem_Items_Pickups_ItemPickupBase_o*> ItemList(NULL);
std::vector<Room*>RoomList(NULL);
std::vector<Indicator*>IndicatorList(NULL);
std::vector<BacktrackRecord*>BacktrackRecordList;
std::vector<Tracer*>TracerList(NULL);
std::vector<UnityEngine_Material_o*>MaterialList(NULL);
std::vector<UnityEngine_Material_o*>OldMaterialList(NULL);
