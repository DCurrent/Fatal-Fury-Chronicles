#include "data/scripts/dc_instance/config.h"

// Which instance is in use?
char dc_instance_get(char instance_key)
{
	char result;

	// If there's no key, getlocalvar fails. Catch that here 
	// and use a default.
	if (typeof(instance_key) == openborconstant("VT_EMPTY"))
	{
		return DC_INSTANCE_DEFAULT_INSTANCE;
	}

	// Get the result. If it's blank, return default instance.
	result = getlocalvar(instance_key);

	if (!result)
	{
		result = DC_INSTANCE_DEFAULT_INSTANCE;
	}

	return result;
}

void dc_instance_set(char instance_key, char value)
{
	if (value == DC_INSTANCE_DEFAULT_INSTANCE)
	{
		value = NULL();
	}

	setlocalvar(instance_key, value);
}

// Use whe sending instance id to dependency, so that the dependency's 
// instance is unique to the library that calls it.
char dc_instance_dependency_get(char base_id, char instance_key)
{
	int result;

	result = base_id + dc_instance_get(instance_key);
}

// Caskey, Damon V.
// 2018-11-22
//
// Clears the current instance, effectively resetting
// all values to their defaults.
void dc_instance_reset(char base_id, char instance_key, int the_end)
{
	int instance;

	// Get instance.
	instance = dc_instance_get(instance_key);

	// Destroy all instance variables.
	dc_instance_free(base_id, instance_key, the_end);

	// If the instance ID isn't default, then restore 
	// it to memory. Either way we now have a clean
	// copy of the current instance.
	if (instance != DC_INSTANCE_DEFAULT_INSTANCE)
	{
		dc_instance_set(instance_key, instance);
	}
}

// Caskey, Damon V.
// 2018-11-22
//
// Destroy the current instance by deleting all
// library variables.
void dc_instance_free(char base_id, char instance_key, int the_end)
{
	int instance;
	int i;
	char id;

	// Get instance.
	instance = dc_instance_get(instance_key);

	// Loop from 0 to end count of library variables.
	for (i = 0; i < the_end; i++)
	{
		// Concatenate the variable ID.
		id = instance + base_id + i;

		// Delete variable.
		setlocalvar(id, NULL());
	}
}

// Caskey, Damon V.
// 2018-11-22
//
// Send all library variables to log for debugging.
void dc_instance_dump(char base_id, char instance_key, int the_end)
{
	log("\n dc_instance_dump: " + base_id + ", " + instance_key + ", " + the_end);

	int instance;
	int i;
	char id;

	// Get instance.
	instance = dc_instance_get(instance_key);

	// Log base name and instance.
	log("\n\n " + base_id + " dump:");
	log("\n\t " + "Instance: " + instance);

	// Loop from 0 to end count of instance variables.
	for (i = 0; i < the_end; i++)
	{
		// Concatenate the variable ID.
		id = instance + base_id + i;

		// Log ID.
		log("\n\t " + id + ": \t");

		// Log value.
		log(getlocalvar(id));
	}

	// Log end point.
	log("\n End Dump.\n");
}

