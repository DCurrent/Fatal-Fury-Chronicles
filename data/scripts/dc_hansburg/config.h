#ifndef DC_HANSBURG_CONFIG
#define DC_HANSBURG_CONFIG 1

// Dependencies
//#include "data/scripts/dc_disney/main.c"
#include "data/scripts/dc_target/main.c"
#include "data/scripts/dc_instance/main.c"

// Name of library. Used mainly as a base for variable IDs. Must
// be unique vs all other libraries. Try to keep it short.
#define DC_HANSBURG_BASE_ID		"dchansb"

// Animations
//
// These are the extra jumping animations. If a model does not
// have one of these animations, then it simply does not have the associated
// jumping capability. You can mix and match how you like. In other words, a model
// might not have a wall jump, but could still have double jumping. Another model
// might only have double jumping, and yet another might have everything.

// Note that if you like you may also re-use animation definitions. For example, you
// could define the same animation here for the start-up of obstacle jumping, wall
// jumping, and edge jumping. Then adding that single animation to a model would
// give it all those types of auxiliary jumping.
#define DC_HANSBURG_ANI_JUMP_DOUBLE_NEUTRAL     openborconstant("ANI_FOLLOW42")     // Double jump, no direction command.
#define DC_HANSBURG_ANI_JUMP_DOUBLE_NEUTRAL_RUN	openborconstant("ANI_FOLLOW42")     // Double jump, no direction command, from run jump.
#define DC_HANSBURG_ANI_JUMP_DOUBLE_BACK        openborconstant("ANI_FOLLOW44")     // Double jump, direction command opposite current facing.
#define DC_HANSBURG_ANI_JUMP_DOUBLE_BACK_RUN    openborconstant("ANI_FOLLOW44")     // Double jump, direction command opposite current facing, from run rump.
#define DC_HANSBURG_ANI_JUMP_DOUBLE_FORWARD     openborconstant("ANI_FOLLOW43")     // Double jumping forward animation, direction command toward current facing.
#define DC_HANSBURG_ANI_JUMP_DOUBLE_FORWARD_RUN openborconstant("ANI_FOLLOW43")     // Double jumping forward animation, direction command toward current facing, from run.
#define DC_HANSBURG_ANI_JUMP_EDGE               openborconstant("ANI_FOLLOW41")     // Screen edge jumping animation.
#define DC_HANSBURG_ANI_JUMP_EDGE_RUN           openborconstant("ANI_FOLLOW41")     // Screen edge jumping animation, from run.
#define DC_HANSBURG_ANI_JUMP_EDGE_START         openborconstant("ANI_FOLLOW40")     // Screen edge prepping to jump animation. The range of this animation is used to detect screen edges.
#define DC_HANSBURG_ANI_JUMP_EDGE_START_RUN     openborconstant("ANI_FOLLOW40")     // Screen edge prepping to jump animation, from run. The range of this animation is used to detect screen edges.
#define DC_HANSBURG_ANI_JUMP_OBJECT             openborconstant("ANI_FOLLOW41")     // Obstacle jumping animation.
#define DC_HANSBURG_ANI_JUMP_OBJECT_RUN         openborconstant("ANI_FOLLOW41")     // Obstacle jumping animation, from run.
#define DC_HANSBURG_ANI_JUMP_OBJECT_START       openborconstant("ANI_FOLLOW40")     // Obstacle prepping to jump animation. The range of this animation is used to detect objects.
#define DC_HANSBURG_ANI_JUMP_OBJECT_START_RUN   openborconstant("ANI_FOLLOW40")     // Obstacle prepping to jump animation, from run. The range of this animation is used to detect objects.
#define DC_HANSBURG_ANI_JUMP_WALL               openborconstant("ANI_FOLLOW41")     // Wall jump animation.
#define DC_HANSBURG_ANI_JUMP_WALL_RUN           openborconstant("ANI_FOLLOW41")     // Wall jump animation, from run.
#define DC_HANSBURG_ANI_JUMP_WALL_START         openborconstant("ANI_FOLLOW40")     // Wall prepping to jump animation. The range of this animation is used to detect walls.
#define DC_HANSBURG_ANI_JUMP_WALL_START_RUN     openborconstant("ANI_FOLLOW40")     // Wall prepping to jump animation, from run. The range of this animation is used to detect walls.

// Control flags
#define DC_HANSBURG_TIME_INFINITE						-1		// True.
#define DC_HANSBURG_NO_EXTRA_JUMP						-1		// No extra jump animation set. Used as a "fail" result when verifying a given extra jump is possible.

// General limits
#define DC_HANSBURG_IN_AIR								0.1		// Air threshold. If an entity’s Y position is this value or more above its base, we consider it airborne. For reference, OpenBOR's native air threshold is 0.1 above base.

// Key press types.
#define DC_HANSBURG_PLAYER_KEY_HOLD						0		
#define DC_HANSBURG_PLAYER_KEY_PRESS					1
#define DC_HANSBURG_PLAYER_KEY_RELEASE					2

// Forward/Backward command "entity_status" in relation to facing.
#define DC_HANSBURG_KEY_MOVE_HORIZONTAL_BACK			1
#define DC_HANSBURG_KEY_MOVE_HORIZONTAL_FORWARD			2 
#define DC_HANSBURG_KEY_MOVE_HORIZONTAL_NEUTRAL			3

// Double jump counter reset options.
#define DC_HANSBURG_DOUBLE_JUMP_COUNT_RESET_NONE		0		// The double jump counter never resets itself unless you do it manually. Overridden if combined with any other option.
#define DC_HANSBURG_DOUBLE_JUMP_COUNT_RESET_BASE		1		// Reset at the start of a normal jump.
#define DC_HANSBURG_DOUBLE_JUMP_COUNT_RESET_EDGE		2		// Reset when rebound jumping from a screen edge.
#define DC_HANSBURG_DOUBLE_JUMP_COUNT_RESET_OBSTACLE	4		// Reset when rebound jumping from an obstacle.
#define DC_HANSBURG_DOUBLE_JUMP_COUNT_RESET_WALL		8		// Reset when rebound jumping from a wall.

// Axis control options. Note OpenBOR's native axis control 
// still applies, so depending on which of these you want
// to use you might want to disable the native options.
#define DC_HANSBURG_AXIS_CONTROL_NONE					0		// No axis control enabled. 
#define DC_HANSBURG_AXIS_CONTROL_DIRECTION				1		// Left/right changes entity facing.		
#define DC_HANSBURG_AXIS_CONTROL_VELOCITY_X				2		// Left/Right moves entity in air (not implemented as of 2019-11-02).
#define DC_HANSBURG_AXIS_CONTROL_VELOCITY_Y_FLY			4		// Flight control (not implemented as of 2019-11-02).
#define DC_HANSBURG_AXIS_CONTROL_VELOCITY_Y_MARIO		8		// Control jump height by length of Jump button press (i.e. Mario Brothers series and many other platform games).
#define DC_HANSBURG_AXIS_CONTROL_VELOCITY_Z				16		// Up/Down moves entity along Z axis in air (not implemented as of 2019-11-02).

// Default values.
#define DC_HANSBURG_DEFAULT_AXIS_CONTROL					DC_HANSBURG_AXIS_CONTROL_VELOCITY_Y_MARIO	// Axis control options.
#define DC_HANSBURG_DEFAULT_BOUNDARY_JUMP_START_HOVER		500											// Extra toss time (no falling) applied when entity is in starting animation for wall/obstacle/edge jump. Should be longer than any start animation.
#define DC_HANSBURG_DEFAULT_DISABLE							0											// If true, all extra jump functions are disabled.
#define DC_HANSBURG_DEFAULT_DOUBLE_JUMP_COUNT				0											// Starting number of double jumps in counter.
#define DC_HANSBURG_DEFAULT_DOUBLE_JUMP_COUNT_RESET			DC_HANSBURG_DOUBLE_JUMP_COUNT_RESET_BASE + DC_HANSBURG_DOUBLE_JUMP_COUNT_RESET_EDGE + DC_HANSBURG_DOUBLE_JUMP_COUNT_RESET_OBSTACLE + DC_HANSBURG_DOUBLE_JUMP_COUNT_RESET_WALL
#define DC_HANSBURG_DEFAULT_DOUBLE_JUMP_MAX					1											// Maximum number of double jumps allowed before counter resets.
#define DC_HANSBURG_DEFAULT_ENT								getlocalvar("self")
#define DC_HANSBURG_DEFAULT_MARIO_MIN_Y						40											// Minimum height before Mario vertical jump control will apply. 										
#define DC_HANSBURG_DEFAULT_MARIO_Y_STOP					0.9											// Mutiplier applied to current Y velocity when player releases jump key (mario jumping control enabled). This gives a smooth stop.
#define DC_HANSBURG_DEFAULT_MAX_Y							openborvariant("vResolution") * 1.25		// All extra jumping functions automatically fail unless entity is below this height. Meant to avoid entities getting over stage boundaries or stuck off screen.

// Member keys.
#define DC_HANSBURG_MEMBER_INSTANCE							DC_HANSBURG_BASE_ID + 0		// Script instance. See https://github.com/DCurrent/openbor-script-instance for details.
#define DC_HANSBURG_MEMBER_AXIS_CONTROL						DC_HANSBURG_BASE_ID + 1		// Axis control options.
#define DC_HANSBURG_MEMBER_BOUNDARY_JUMP_START_HOVER		DC_HANSBURG_BASE_ID + 2		// Hover time during boundary jump start animations.
#define DC_HANSBURG_MEMBER_DOUBLE_JUMP_COUNT				DC_HANSBURG_BASE_ID + 3		// Number of double jumps executed since last counter reset.
#define DC_HANSBURG_MEMBER_DOUBLE_JUMP_COUNT_RESET			DC_HANSBURG_BASE_ID + 4		// Conditions to reset double jump counter.
#define DC_HANSBURG_MEMBER_DOUBLE_JUMP_MAX					DC_HANSBURG_BASE_ID + 5		// Maximum allowed double jumps (until next reset).
#define DC_HANSBURG_MEMBER_DISABLE							DC_HANSBURG_BASE_ID + 6		// Disable auxiliary jumping.
#define DC_HANSBURG_MEMBER_ENT								DC_HANSBURG_BASE_ID + 7		// Entity.
#define DC_HANSBURG_MEMBER_MARIO_MIN_Y						DC_HANSBURG_BASE_ID + 8		// Minimum height before mario style control will stop jump.
#define DC_HANSBURG_MEMBER_MAX_Y							DC_HANSBURG_BASE_ID + 9		// Maximum height to allow wall jumps, double jumps, etc.
#define DC_HANSBURG_MEMBER_MARIO_Y_STOP						DC_HANSBURG_BASE_ID + 10	// Percentage of current Y to apply when stopping a mario style jump.
#define DC_HANSBURG_MEMBER_THE_END							11							// Should always be last, with a value one higher than previous key ID.

// Instance control. See https://github.com/DCurrent/openbor-script-instance for details.
#define dc_hansburg_get_instance()				dc_instance_get(DC_HANSBURG_MEMBER_INSTANCE)
#define dc_hansburg_set_instance(value)			dc_instance_set(DC_HANSBURG_MEMBER_INSTANCE, value)
#define dc_hansburg_get_instance_dependency()	dc_instance_dependency_get(DC_HANSBURG_BASE_ID, DC_HANSBURG_MEMBER_INSTANCE)
#define dc_hansburg_reset_instance()			dc_instance_reset(DC_HANSBURG_BASE_ID, DC_HANSBURG_MEMBER_INSTANCE, DC_HANSBURG_MEMBER_THE_END)
#define dc_hansburg_free_instance()				dc_instance_free(DC_HANSBURG_BASE_ID, DC_HANSBURG_MEMBER_INSTANCE, DC_HANSBURG_MEMBER_THE_END)
#define dc_hansburg_dump_instance()				dc_instance_dump(DC_HANSBURG_BASE_ID, DC_HANSBURG_MEMBER_INSTANCE, DC_HANSBURG_MEMBER_THE_END)
#define dc_hansburg_export_instance()			dc_instance_export(DC_HANSBURG_BASE_ID, DC_HANSBURG_MEMBER_INSTANCE, DC_HANSBURG_MEMBER_THE_END)
#define dc_hansburg_import_instance()			dc_instance_import(DC_HANSBURG_BASE_ID, DC_HANSBURG_MEMBER_INSTANCE, DC_HANSBURG_MEMBER_THE_END)
#define dc_hansburg_free_export()				dc_instance_free_export(DC_HANSBURG_BASE_ID, DC_HANSBURG_MEMBER_INSTANCE, DC_HANSBURG_MEMBER_THE_END)

#endif


