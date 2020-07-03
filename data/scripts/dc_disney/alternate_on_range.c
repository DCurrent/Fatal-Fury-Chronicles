#include "data/scripts/dc_disney/config.h"

#import "data/scripts/dc_disney/entity.c"

// Caskey, Damon V.
// 2018-11-03 (orginal 2009-10-26)
//
// Switch to alternate animation if nearest hostile target is
// in the alternate animation's range.
void dc_disney_alternate_on_range(int animation) 
{
	void ent;
	void target;

	// Get base entity.
	ent = dc_disney_get_entity();

	// Find target in range of animation.
	target = findtarget(ent, animation);

	// If we found a target, then switch animations.
	if (target)
	{
		changeentityproperty(ent, "animation", animation);
	}
}
