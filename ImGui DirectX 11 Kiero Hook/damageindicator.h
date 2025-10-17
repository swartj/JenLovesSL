#pragma once
#include "il2cpp.h"
#include <vector>
#include <iostream>


#define MAX_INDICATOR_LIVINGTIME 60
#define MAX_INDICATOR_SPREAD 0.25


enum DamageType
{
	health,
	ahp,
	hume
};

struct Indicator
{
	int livingTime;
	int amount;
	DamageType type;
	UnityEngine_Vector3_o position;
};


struct Indicator* CreateIndicator(UnityEngine_Vector3_o position, DamageType type, float amount);
