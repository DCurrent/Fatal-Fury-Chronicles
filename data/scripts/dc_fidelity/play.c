#include "data/scripts/dc_fidelity/config.h"

#import "data/scripts/dc_fidelity/adjustments.c"
#import "data/scripts/dc_fidelity/category.c"
#import "data/scripts/dc_fidelity/entity.c"
#import "data/scripts/dc_fidelity/global.c"
#import "data/scripts/dc_fidelity/sound_config.c"
#import "data/scripts/dc_fidelity/timed.c"

// Caskey, Damon V.
// 2018-10-23
//
// Get a sample ID from sound type and the current 
// target entity's model.
int dc_fidelity_get_entity_sound(int type)
{
	void ent;
	char model;
	int sample_id;

	// Get target entity.
	ent = dc_fidelity_get_entity();

	model = getentityproperty(ent, "defaultmodel");
	

	// Now that we have a model, run model sound function 
	// to get a sample ID.
	sample_id = dc_fidelity_find_category_sound(model, type);

	// If we failed to find a sample, try again using the
	// global category instead of our model name.
	if (sample_id == DC_FIDELITY_SAMPLE_NONE)
	{
		// Global fallback enabled? Then give the global
		// category a try.
		if (dc_fidelity_get_global_fallback())
		{
			sample_id = dc_fidelity_find_category_sound(DC_FIDELITY_CATEGORY_GLOBAL, type);
		}		
	}

	return sample_id;
}

// Caskey, Damon V.
// 2018-10-23
//
// Calculate chance to perform action against current
// chance setting and return result. 
//
// 0 Fail (no).
// 1 Pass (yes).
int dc_fidelity_sound_chance()
{
	float chance;
	int percentage;
	int random;

	chance = dc_fidelity_get_sound_chance();

	// Convert chance to whole number percentage.
	percentage = chance * 100;

	// Get random 0-100.
	//dc_d20_set_instance(DC_FIDELITY_BASE_ID);
	
	dc_d20_set_range_max(100);
	random = dc_d20_random_int();

	if (percentage >= random)
	{
		return 1;
	}

	return 0;
}

// Caskey, Damon V.
// 2018-10-23
//
// Get a sample ID from sound type and a known category.
int dc_fidelity_find_category_sound(char category, int type)
{
	void ent;			// Target entity.
	int result;			// Sound index.
	void category_list;	// Array of categories (usually models) array.
	void type_list;		// Sound types array.
	void index_list;	// Sound indexes array.
	int size;			// Size of array.

	// Get the cateogry list array.
	category_list = dc_fidelity_get_category_list();

	// No list of categories. We can't go any further.
	if (!category_list)
	{
		return DC_FIDELITY_SAMPLE_NONE;
	}

	// If category is blank, get() fails and shuts down. Let's 
	// handle it here.
	if (typeof(category) == openborconstant("VT_EMPTY"))
	{
		// Log error.
		if (DC_FIDELITY_LOG & DC_FIDELITY_LOG_CATEGORY_MISSING)
		{
			log("\n\n");
			log("Error: " + DC_FIDELITY_BASE_ID);
			log("\n\t Missing category.");
			log("\n\t dc_fidelity_find_category_sound(category: " + category + ", type: " + type + ")");
			log("\n");
		}

		// Fall back to global.
		if (DC_FIDELITY_DEFAULT_GLOBAL_FALLBACK)
		{
			category = DC_FIDELITY_CATEGORY_GLOBAL;
		}
	}	

	// Each category entry is an array of types. Here we get the
	// type array pointer.
	type_list = get(category_list, category);

	// If there's no entry in the categroy list for this
	// requested category, we don't have a list of types.
	if (!type_list)
	{
		if (DC_FIDELITY_LOG & DC_FIDELITY_LOG_CATEGORY_TYPE_NOT_FOUND)
		{
			log("\n\n");
			log("Error: " + DC_FIDELITY_BASE_ID);
			log("\n\t Entry not found in category list.");
			log("\n\t dc_fidelity_find_category_sound(category: " + category + ", type: " + type + ")");
			log("\n");
		}

		return DC_FIDELITY_SAMPLE_NONE;
	}

	// Each type is an array of sample IDs. Here we get
	// the sound array pointer.
	index_list = get(type_list, type);

	// Send the sound array pointer to sound selection function.
	// It will choose an element from the array either manually 
	// or randomly, and return the sample id.
	result = dc_fidelity_select_sample_id(index_list);

	// We now have a sample id to return.
	return result;
}


// Caskey, Damon V.
// 2018-10-23
// 
// Get a sound index (sample ID) from a sound indexes array. 
int dc_fidelity_select_sample_id(void index_list)
{
	int result;
	int size;
	int element;

	// We don't have a valid array of sound sample IDs.
	if (!index_list)
	{
		return DC_FIDELITY_SAMPLE_NONE;
	}

	// Get element setting.
	element = dc_fidelity_get_sound_element();

	// If element is set to random, then get a 
	// random item from the available range of 
	// array elements.
	if (element == DC_FIDELITY_INDEX_RANDOM)
	{
		// Set instance for dc d20 function to this
		// library and current instance.
		dc_d20_set_instance(DC_FIDELITY_BASE_ID + dc_fidelity_get_instance());

		// Get size, decrement by 1 to compensate
		// for 0 indexing and use as upper bound
		// for a random int.
		size = size(index_list);
		size--;

		dc_d20_set_range_max(size);		

		element = dc_d20_random_int();
	}

	// Get sound index value from indexes array.
	result = get(index_list, element);

	//log("\n\t result: " + result);

	// Return result.
	return result;
}

// Caskey, Damon V.
// 2018-10-14
//
// Play requested sample with X axis based stereo.
int dc_fidelity_quick_play(int type)
{
	int		sample_id;		// Sample ID to play.

	// If random chance doesn't pass, exit now.
	if (!dc_fidelity_sound_chance())
	{
		return;
	}

	// Get a sample ID.
	sample_id = dc_fidelity_get_entity_sound(type);

	// Send to play balanced and return result.
	return dc_fidelity_play_balanced(sample_id);
}

// Caskey, Damon V.
// 2019-04-20
//
// Similar to quick play, but play the selected sound
// with a dley by sending it to a timed list.
void dc_fidelity_timed_play(int type, int delay)
{
	int		sample_id;		// Sample ID to play.

	// If random chance doesn't pass, exit now.
	if (!dc_fidelity_sound_chance())
	{
		return;
	}

	// Get a sample ID.
	sample_id = dc_fidelity_get_entity_sound(type);

	// Send sample to timed list for timed playback.
	dc_fidelity_timed_setup(sample_id, delay);
}

// Caskey, Damon V.
// 2019-04-20 (offloading from quick_play)
//
// Play sample with auto balance.
int dc_fidelity_play_balanced(int sample_id)
{
	void ent;
	float pos_x;

	int volume_left;
	int volume_right;

	// Get set volumes.
	volume_left = dc_fidelity_get_sound_volume_main_left();
	volume_right = dc_fidelity_get_sound_volume_main_right();

	// Get entity X position. It's possible for an entity to become
	// invalid after calling a for a sound, so verify first and
	// apply a default value if we have to.
	ent = dc_fidelity_get_entity();

	if (typeof(ent) == openborconstant("VT_PTR"))
	{
		pos_x = get_entity_property(ent, "position_x");
	}
	else
	{
		// Log error.
		if (DC_FIDELITY_LOG & DC_FIDELITY_LOG_BALANCE_INVALID_ENTITY)
		{
			log("\n\n");
			log("Error: " + DC_FIDELITY_BASE_ID);
			log("\n\t Entry not found in category list.");
			log("\n\t dc_fidelity_play_balanced(sample_id: " + sample_id + ")");
			log("\n");
		}

		// Apply default position.
		pos_x = DC_FIDELITY_DEFAULT_SOUND_LOCATION_POS_X;
	}
		

	// Get adjusted volumes.
	if (dc_fidelity_get_sound_location_balance())
	{
		volume_left -= dc_fidelity_auto_balance_volume(pos_x, volume_left);
		volume_right = dc_fidelity_auto_balance_volume(pos_x, volume_right);

		if (volume_left < 0)
		{
			volume_left = 0;
		}

		if (volume_right < 0)
		{
			volume_right = 0;
		}
	}

	// Send to play sample function.
	return dc_fidelity_playsample(sample_id, volume_left, volume_right);
}

// Caskey, Damon V.
// 2018-10-23
// 
// Wrapper for the OpenBOR playsample() function. Gets any leftover
// config values before playing sound and verifies the sample ID.
// There's no way to know id a sample ID is actually valid, but
// it must be a positive integer, so we can at least check that.
//
// Returns 1 if sample plays, 0 otherwise.
int dc_fidelity_playsample(int sample_id, int volume_left, int volume_right)
{

	int priority;
	int speed;
	int loop;

	// Sample ID must be a valid integer.
	if (typeof(sample_id) != openborconstant("VT_INTEGER"))
	{
		return 0;
	}

	// Sample ID must be 0+.
	if (sample_id < 0)
	{
		return 0;
	}

	loop = dc_fidelity_get_sound_loop();
	priority = dc_fidelity_get_sound_priority();
	speed = dc_fidelity_get_sound_speed();

	// Play the sample.
	playsample(sample_id, priority, volume_left, volume_right, speed, loop);

	return 1;
}

// Caskey, Damon V.
// 2018-10-23
//
// Check and play timed samples.
void dc_fidelity_play_timed()
{
	void timed_list;
	void timed_sample;
	void ent;
	int time;
	int time_current;
	int sample_id;
	int size;
	int i;
	   
	timed_list = dc_fidelity_get_timed_list();

	// No list? Exit.
	if (timed_list == NULL())
	{
		return;
	}

	size = size(timed_list);

	// If the list is empty, remove it and get out.
	if (size == 0)
	{
		free(timed_list);
		dc_fidelity_set_timed_list(NULL());

		return;
	}

	// Check each element for a sample.
	for (i = 0; i < size; i++)
	{

		// Get pointer to timed sample.
		timed_sample = get(timed_list, i);

		if (timed_sample == NULL())
		{
			continue;
		}

		time = get(timed_sample, DC_FIDELITY_TIMED_SAMPLE_TIME);

		// Time expired? Let's play the sound and delete its
		// array and list entry.
		time_current = openborvariant("elapsed_time");
		
		if (time < time_current)
		{
			sample_id = get(timed_sample, DC_FIDELITY_TIMED_SAMPLE_SAMPLE_ID);
			ent = get(timed_sample, DC_FIDELITY_TIMED_SAMPLE_ENTITY);

			if (!get_entity_property(ent, "exists"))
			{
				continue;
			}

			if (get_entity_property(ent, "dead"))
			{
				continue;
			}

			dc_fidelity_set_entity(ent);
			dc_fidelity_play_balanced(sample_id);

			// Destroy timed sample array and remove 
			// element from list.
			free(timed_sample);

			delete(timed_list, i);
		}
	}
}

