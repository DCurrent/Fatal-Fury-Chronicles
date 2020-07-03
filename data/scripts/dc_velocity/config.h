#ifndef DC_VELOCITY_CONFIG
#define DC_VELOCITY_CONFIG

// Configuration
#define DC_VELOCITY_INVERT_X_AUTO			0	// Reverse X velocity if entity faces left. 
#define DC_VELOCITY_INVERT_X_MANUAL			1	// No X reversal.

// Default values.
#define DC_VELOCITY_DEFAULT_INSTANCE		0
#define DC_VELOCITY_DEFAULT_ENT				getlocalvar("self")
#define DC_VELOCITY_DEFAULT_INVERT_X		DC_VELOCITY_INVERT_X_AUTO
#define DC_VELOCITY_DEFAULT_VELOCITY_X		0.0 
#define DC_VELOCITY_DEFAULT_VELOCITY_Y		0.0 
#define DC_VELOCITY_DEFAULT_VELOCITY_Z		0.0  

// Variable keys.
#define DC_VELOCITY_MEMBER_INSTANCE		"dcvel_0"
#define DC_VELOCITY_MEMBER_ENT				"dcvel_1"
#define DC_VELOCITY_MEMBER_INVERT_X		"dcvel_2"
#define DC_VELOCITY_MEMBER_VELOCITY_X		"dcvel_3"
#define DC_VELOCITY_MEMBER_VELOCITY_Y		"dcvel_4"
#define DC_VELOCITY_MEMBER_VELOCITY_Z		"dcvel_5"

#endif // !DC_VELOCITY_CONFIG

