#include "data/scripts/dc_disney/config.h"

#import "data/scripts/dc_disney/entity.c"

// Caskey, Damon V.
// 2018-11-03
// 
// Switch animation based on health thresholds. For now,
// defaults to switching on 20% or below. We can add
// more switches using localvars later when we need them.
void dc_disney_alternate_on_health(int animation)
{ 
	
	void  ent;
	int   hp_current = 0.0;
	int   hp_max = 0.0;
	float ratio_current = 0.0;

	float ratio_threshold = 0.2;

	// Get base entity.
	ent = dc_disney_get_entity();

	hp_current += getentityproperty(ent, "health");
	hp_max += getentityproperty(ent, "maxhealth");
	
	ratio_current = (hp_current / hp_max);

	// At or below ratio_threshold?
	if (ratio_current <= ratio_threshold)
	{
		if (getentityproperty(ent, "animvalid", animation))
		{
			changeentityproperty(ent, "animation", animation);
		}
	}
}