#include "damageindicator.h"


struct Indicator* CreateIndicator(UnityEngine_Vector3_o position, DamageType type, float amount)
{
	Indicator* indicator = new Indicator;

	indicator->position.fields.x = position.fields.x + (rand() - 0.5 * RAND_MAX) / (0.5 * RAND_MAX) * MAX_INDICATOR_SPREAD;
	indicator->position.fields.y = position.fields.y + (rand() - 0.5 * RAND_MAX) / (0.5 * RAND_MAX) * MAX_INDICATOR_SPREAD;
	indicator->position.fields.z = position.fields.z + (rand() - 0.5 * RAND_MAX) / (0.5 * RAND_MAX) * MAX_INDICATOR_SPREAD;

	indicator->type = type;
	indicator->amount = (int)amount;
	indicator->livingTime = MAX_INDICATOR_LIVINGTIME;

	return indicator;
}
