#include "data/scripts/dc_instance/config.h"

#import "data/scripts/dc_instance/operation.c"

// Caskey, Damon V.
// 2018-11-28
//
// Export instance to global vars for other event
// to import.
void dc_instance_export(char base_id, char instance_key, int the_end)
{
	int instance;
	int i;
	char id;

	void value;

	// Get instance.
	instance = dc_instance_get(instance_key);

	// Loop from 0 to end count of instance variables.
	for (i = 0; i < the_end; i++)
	{
		// Concatenate the variable ID.
		id = instance + base_id + i;

		// Get local (library) value.
		value = getlocalvar(id);

		// Export value to global var.
		setglobalvar(id, value);
	}
}

// Caskey, Damon V.
// 2018-11-28
//
// Import an exported instance.
void dc_instance_import(char base_id, char instance_key, int the_end)
{
	int instance;
	int i;
	char id;

	void value;

	// Get instance.
	instance = dc_instance_get(instance_key);

	// Loop from 0 to end count of instance variables.
	for (i = 0; i < the_end; i++)
	{
		// Concatenate the variable ID.
		id = instance + base_id + i;

		// Get value
		value = getglobalvar(id);

		// Import value to local (library) var.
		setlocalvar(id, value);
	}
}

// Caskey, Damon V.
// 2018-11-22
//
// Destroy the current instance export.
void dc_instance_free_export(char base_id, char instance_key, int the_end)
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

		// Delete the global variable.
		setglobalvar(id, NULL());
	}
}