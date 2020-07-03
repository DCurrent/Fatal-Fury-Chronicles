#define ANI_BLOCK_NORMAL  openborconstant("ANI_BLOCKPAIN")     // Default guard.
#define ANI_BLOCK_MIDDLE  openborconstant("ANI_BLOCKPAIN2")    // Middle guard.
#define ANI_BLOCK_LOW     openborconstant("ANI_BLOCKPAIN3")    // Low guard.
#define ANI_BLOCK_HIGH    openborconstant("ANI_BLOCKPAIN4")    // High guard. 

// Caskey, Damon V.
// 2012-11-13
//
// Retool of bloc0001 (2007). Return animation for blocking based
// on hit height (head, body, feet, etc.).
int dc_find_block_height_animation()
{    
	void ent;				// Calling entity.        
    void attacker;			// Attacking entity.
    int  height;			// Caller height.            
    int  lasthit_y;			// Last hit Y.    
    int  animation_current;	// Caller animation.
    float  pos_y;			// Attacker Y location.
    int  pos_base;			// Attacker base Y.
    int  animation_block;	// Final block animation.
    
	// Get entities.
	ent = getlocalvar("self");
	attacker = getlocalvar("attacker");

	// Current animation.
	animation_current	= getentityproperty(ent, "animationid");

    //Fatal Fury style proximity blocking. If entity is blocking (not an attack with autoblock), 
    //switch to the appropriate block animation based on height of incomming attack.
    if (animation_current == openborconstant("ANI_BLOCK")                                                //In block animation? 
        || animation_current == ANI_BLOCK_NORMAL
        || animation_current == ANI_BLOCK_LOW
        || animation_current == ANI_BLOCK_MIDDLE
        || animation_current == ANI_BLOCK_HIGH)
    {
		// Get total height of ent and height of last hit.
        height = getentityproperty(ent, "height") + getentityproperty(ent, "base");    
        lasthit_y   = openborvariant("lasthita");
    
		// Now calculate block based on hit height vs. total height.
		// 30%-: Low block.
		// 31-75%: Middle block.
		// 75%+ from grounded attack: Default block.
		// 75%+ from off ground attack: High block.
        if (lasthit_y < height * 0.3)                                                          
        {
            animation_block = ANI_BLOCK_LOW;                                                           
        }
        else if (lasthit_y < height * 0.75)                                                    
        {
            animation_block = ANI_BLOCK_MIDDLE; 
        }
        else                                                                               
        {
			// Let's find out if attacker is off the ground. If so, we'll
			// use an extra high block. Otherwise, use the default.
            pos_y          = getentityproperty(attacker, "a");                               
            pos_base       = getentityproperty(attacker, "base");                             
			
            if ((pos_y - pos_base) > 1)                                                           
            {
                animation_block = ANI_BLOCK_HIGH;                                                      
            }
            else
            {
                animation_block = ANI_BLOCK_NORMAL;                                                                      
            }
        }
        
		// If we have the selected block animation, apply it here.
		if (getentityproperty(ent, "animvalid", animation_block))
		{
			return animation_block;
		}
    }

	return ANI_BLOCK_NORMAL;
}

#undef ANI_BLOCK_NORMAL
#undef ANI_BLOCK_MIDDLE
#undef ANI_BLOCK_LOW
#undef ANI_BLOCK_HIGH