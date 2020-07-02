#include "data/scripts/dc_fidelity/config.h"

// Enables auto balance. As a location moves horizontaly
// in relation to screen position, volume balance is 
// adjusted to create a true location based stereo
// effect.
void dc_fidelity_set_sound_location_balance(int value)
{
	char id;

	id = dc_fidelity_get_instance() + DC_FIDELITY_MEMBER_SOUND_LOCATION_BALANCE;

	// If requested value is the same as default, 
	// don't waste memory for a variable since we 
	// fall back to default on NULL() anyway.
	if (DC_FIDELITY_DEFAULT_SOUND_LOCATION_BALANCE == value)
	{
		value = NULL();
	}

	setlocalvar(id, value);
}

int dc_fidelity_get_sound_location_balance()
{
	char id;

	id = dc_fidelity_get_instance() + DC_FIDELITY_MEMBER_SOUND_LOCATION_BALANCE;

	int result = getlocalvar(id);

	if (typeof(result) != openborconstant("VT_INTEGER"))
	{
		result = DC_FIDELITY_DEFAULT_SOUND_LOCATION_BALANCE;
	}

	return result;
}

// Caskey, Damon V. 
// 2018-10-13
//
// Return an adjusted volume based on position in screen. 
int dc_fidelity_auto_balance_volume(float position, int volume)
{
	float	center;
	float	result;
	float	factor;

	// Positions are absolute, so we need to subtract
	// the level scroll position to get where we 
	// are on the screen.
	position -= openborvariant("xpos");

	// Get median of the screen resolution.
	center = openborvariant("hResolution") * 0.5;

	// Divide position by center. This gives us a mutiplication
	// factor based on X posiition on screen:
	//
	// Far left, approaching 0.
	// Center, 1. 
	// Far right, approaching 2.
	factor = position / center;

	// Divide the orginal volume in half. We then mutiply by
	// our factor to produce an adjusted volume from left to
	// right:
	//
	// Far left, approaching 0.
	// Center, half volume.
	// Far right, approaching original volume.
	result = (volume / 2) * factor;

	// Return the result. 
	// -- Right channel: Use as is.
	// -- Left channel: Subtract from orginal channel volume.
	return result;
}