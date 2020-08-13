
#define DC_DISNEY_CANCEL_KEY_PREFIX "dc_cancel_"


#define MASK_FRAME 511
#define MASK_HITS 16383
#define HITS_REQUIRE_NONE 16383

#define SHIFT_FRAME_START 0
#define SHIFT_FRAME_END 9
#define SHIFT_HITS_MAX 18

// Caskey, Damon V.
// 2020-08-06
//
// Set up a cancel point and its limitations. Mutiple cancels
// into and/or out of a given animation are allowed. Just repeat
// the function with the new cancel arguments.
//
// -- animation_cancel_to: Animation that can be cancled into. 
// -- animation_cancel_from: Animation that can be canceled out of.
//
// -- frame_start/end: Frame range animation from must be within to 
// allow cancel. Maximum range is 0 to 510. Set both to 0 for no 
// required frame range.
//
// -- hits_min: Minium number of previous hits to allow a cancel. 
// maximum range is 0 to 1023. Use HITS_REQUIRE_NONE to only allow 
// cancel when no previous hits occured.
void dc_disney_cancel_setup(int animation_cancel_to, int animation_cancel_from, int frame_start, int frame_end, int hits_min)
{
    int index = 0;
    char key = "";

    log("\n");
    log("\n dc_disney_cancel_setup()");

    // Create an artificial 2D array. This array is keyed
    // by a combination of the cancel into animation, the
    // cancel from animation and a sequential index.
    //
    // Each element of the array contains an encoded value
    // of cancel data (frame start, frame end, etc.) using
    // bitwise operations. We can decode the data back into
    // its seperate parts when we need to use it again. 
    //
    // cancel_list[animation_cancel_to + animation_cancel_from + index] = {frame_range_start, frame_range_end, required hits}
    //
    // We are using an artificial array instead of OpenBOR
    // Script's native array support because native arrays
    // must be actively removed from memory once established.
    // By using local vars, our artificial array here is
    // fire and forget. Encoding the data rather than using 
    // variables for each saves a lot of memory and time as 
    // otherwise we'd need another artficial array for each 
    // portion of the data. 

    // Find the first available index by checking
    // for previous cancel sets until we get an
    // uninitialized variable.

    do
    {
        key = DC_DISNEY_CANCEL_KEY_PREFIX + animation_cancel_to + "_" + animation_cancel_from + "_" + index;
        index++;

        log("\n key: " + key);

    } while (getlocalvar(key));

    index--;

    // Masks and bit shift values. 
    // 
    // Masks must be the top range of a value, keeping 
    // in mind 0 indexing. For example, an 8bit sized 
    // value gives us 256 possible combinations, meaning
    // a number range of 0-255. Therefore the mask should
    // be 255, or a hexadecimal of 0xFF.
    //
    // Bit shifts are the starting set of bits for our 
    // values. Bits are 0 indexed left to right. As an 
    // example, assume we are encoding four 8bit values. 
    // The first value always starts at bit 0, so it does
    // not need a shift. Since it's 8bit in size, it occupies
    // bits 0-7. That means the second value must start at 
    // bit 8, so we shift to 8. Continuing the same pattern,
    // our second value occupies bits 8-15, so we shift to 
    // 16 for the third value's start bit. Finally, the third 
    // value occupies bits 16-23, so we shift to bit 24 for 
    // the fourth, which then occupies remaining bits 24-32.


    int encoded = 0;

    // Compress values into single integer and use it
    // to populate local var.
    encoded = (frame_start << SHIFT_FRAME_START) | (frame_end << SHIFT_FRAME_END) | (hits_min << SHIFT_HITS_MAX);

    setlocalvar(key, encoded);    

    
    // Debug. Remove when finished.

    // First blank and output encoded so
    // we know anything below is taken
    // from localvar call.
    encoded = NULL();
    log("\n encoded: " + encoded);
    
    // Get encoded data, decompress and output to log.
    encoded = getlocalvar(key);

    log("\n encoded: " + encoded);

    log("\n frame start: " + ((encoded >> SHIFT_FRAME_START) & MASK_FRAME));
    log("\n frame end: " + ((encoded >> SHIFT_FRAME_END) & MASK_FRAME));
    log("\n Required hits: " + ((encoded >> SHIFT_HITS_MAX) & MASK_HITS));
    
    // End debug.
}

// 1. Command triggered?
// -- 2. Look up list of cancel "to" animations vs. 

int dc_disney_check_cancel(void ent, int animation_cancel_to)
{
    int index = 0;
    char key = "";

    int animation_id = get_entity_property(ent, "animation_id");
    int animation_frame = get_entity_property(ent, "animation_frame");

    int cancel_data;

    int frame_start = 0;
    int frame_end = 0;
    int hits_min = 0;
    int hits_count = 0;

    // Loop over artificial array (dc_disney_cancel_setup)
    // and attempt to locate cancel from entries for our
    // current animation. If we find an animation entry,
    // check current frame vs. frame range of cancel.

    log("\n");
    log("\n dc_disney_check_cancel()");

    do
    {
        // Get cancel data using a key made up of the animation 
        // we want to cancel into, (supplied by argument), the
        // animation we can cancel from (current animation), and
        // an index. 

        key = DC_DISNEY_CANCEL_KEY_PREFIX + animation_cancel_to + "_" + animation_id + "_" + index;

        log("\n key: " + key);

        cancel_data = getlocalvar(key);

        log("\n cancel_data: " + cancel_data);

        // If we got any cancel data, we need to decode it back
        // into indivdiual parts (see cancel setup function). 
        // Then we can determine if we are elgible to cancel.

        if (typeof(cancel_data) == openborconstant("VT_INTEGER"))
        {
            frame_start = (cancel_data >> SHIFT_FRAME_START) & MASK_FRAME;
            frame_end = (cancel_data >> SHIFT_FRAME_END) & MASK_FRAME;

            log("\n animation_frame: " + animation_frame);
            log("\n frame_start: " + frame_start);
            log("\n frame_end: " + frame_end);

            // Current frame is within frame range or 
            // there is no frame range at all?
            if ((animation_frame >= frame_start && animation_frame <= frame_end) || (!frame_start && !frame_end))
            {
                // Now run same check as frame, but for
                // minimum and maximum hits.
                                
                hits_min = (cancel_data >> SHIFT_HITS_MAX) & MASK_HITS;
                hits_count = getentityproperty(ent, "rush_count");

                log("\n hits_count: " + hits_count);
                log("\n hits_min: " + hits_min);
                
                // Check required hits. If HITS_REQUIRE_NONE is
                // set then no hits are allowed. Otherwise compare
                // current hits to min hits.

                if (hits_min == HITS_REQUIRE_NONE && hits_count > 0)
                {
                    return 0;
                }
                else if (hits_count >= hits_min)
                {                    
                    return 1;
                }
            }
        }

        // Increment index for next loop.
        index++;
    }
    while (cancel_data);

    // If we get here, there were no valid
    // cancels found. Return false.
    return 0;
}

#undef MASK_FRAME
#undef MASK_HITS

#undef SHIFT_FRAME_START
#undef SHIFT_FRAME_END
#undef SHIFT_HITS_MAX


void oncreate()
{    
    dc_disney_cancel_setup(openborconstant("ANI_FREESPECIAL6"), openborconstant("ANI_ATTACK1"), 0, 0, 0);
    dc_disney_cancel_setup(openborconstant("ANI_FREESPECIAL6"), openborconstant("ANI_ATTACK2"), 0, 0, 0);
    dc_disney_cancel_setup(openborconstant("ANI_FREESPECIAL6"), openborconstant("ANI_ATTACK3"), 0, 0, 0);
    dc_disney_cancel_setup(openborconstant("ANI_FREESPECIAL6"), openborconstant("ANI_ATTACK4"), 0, 0, 0);
    dc_disney_cancel_setup(openborconstant("ANI_FREESPECIAL6"), openborconstant("ANI_ATTACK5"), 0, 0, 0);
    dc_disney_cancel_setup(openborconstant("ANI_FREESPECIAL6"), openborconstant("ANI_ATTACK6"), 0, 0, 0);
    dc_disney_cancel_setup(openborconstant("ANI_FREESPECIAL6"), openborconstant("ANI_CHARGEATTACK"), 0, 0, 0);
    dc_disney_cancel_setup(openborconstant("ANI_FREESPECIAL6"), openborconstant("ANI_FOLLOW82"), 0, 0, 0);
}

// Terry Bogard key key capture.
int dc_try_terry_rising_tackle()
{
#define DC_TERRY_RISING_TACKLE_DELAY 450

    void ent;
    int player_index;
    int key_hold;
    int key_play;
    int key_press;
    int key_release;
    int attacking;
    int elapsed_time;   
    int key_jump_press_time;

    // Let's set up foundation variables.

    ent = getplayerproperty(player_index, "entity");
    player_index = getlocalvar("player");
    elapsed_time = openborvariant("elapsed_time");

    // Jump key press? If so, let's set the timer
    // variable up and then exit.

    key_press = getplayerproperty(player_index, "newkeys");

    if (key_press & openborconstant("FLAG_JUMP"))
    {
        setlocalvar("dc_terry_rising_tackle_key_jump_press_time" + player_index, elapsed_time + DC_TERRY_RISING_TACKLE_DELAY);
        return 0;
    }    

    // Let's start checking for conditions. If any condition is 
    // not met, we exit.

    // -- Jump key release.

    key_release = getplayerproperty(player_index, "releasekeys");

    if (!(key_release & openborconstant("FLAG_JUMP")))
    {

        // This mess is to prevent jumping when another key is released
        // while the Jump key is held. Normally, OpenBOR always attempts
        // a jump action when Jump key is pressed unless specfically 
        // overriden by another action. For example, if the player 
        // presses and holds Jump when they are already holding the 
        // Special key (blocking), then releases Special while still 
        // holding Jump, a jump occurs. We want to disable this behavior 
        // so player will have ability to begin charging Terry's Rising 
        // Tackle during another action without jumping when the other
        // action is finished. But we also need to be careful not to mess 
        // up native jumping, jump control scripts, or any in air moves 
        // that use a hold key command.
        //
        // We will first check for the release of the other in game action 
        // keys. Then we get the final player key input. If the character 
        // is not jumping and the player key input includes a Jump, we know 
        // they are releasing a non Jump key while on the ground and holding 
        // Jump key to charge the Rising Tackle. We can then remove Jump key
        // from player key input before the engine detects it and triggers a
        // native jump action.
        if (key_release & openborconstant("FLAG_SPECIAL") || key_release & openborconstant("FLAG_ATTACK") || key_release & openborconstant("FLAG_ATTACK2") || key_release & openborconstant("FLAG_ATTACK3"))
        {
            key_play = getplayerproperty(player_index, "playkeys");

            if (key_play & openborconstant("FLAG_JUMP") && !get_entity_property(ent, "jump_state"))
            {                
                key_play -= openborconstant("FLAG_JUMP");                

                changeplayerproperty(player_index, "playkeys", key_play);
            }
        }

        return 0;
    }

    // -- Not enough time passed since user first pressed the
    // key, or there is no time set at all.

    elapsed_time = openborvariant("elapsed_time");

    key_jump_press_time = getlocalvar("dc_terry_rising_tackle_key_jump_press_time" + player_index);

    if (!key_jump_press_time || key_jump_press_time > elapsed_time)
    {
        return 0;
    }

    // -- Not jumping.

    if (get_entity_property(ent, "jump_state"))
    {
    	return 0;
    }

    // -- Idle, or can be canceled.

    if (!get_entity_property(ent, "idle_state") && !dc_disney_check_cancel(ent, openborconstant("ANI_FREESPECIAL6")))
    {
        return 0;
    }

    // not losing.

    //if (get_entity_property(ent, "in_pain") || get_entity_property(ent, "in_pain_back") || get_entity_property(ent, "fall_state"))
    //{
    //    return 0;
    //}

    // -- Not holding Special key.

    key_hold = getplayerproperty(player_index, "keys");
    
    if (key_hold & openborconstant("FLAG_SPECIAL"))
    {
        return 0;
    }

    // -- Can pay the energy cost.

    void animation = getentityproperty(ent, "animation.handle", openborconstant("ANI_FREESPECIAL6"));

    int energy_cost = get_animation_property(animation, "energy_cost_amount");
    int mp = get_entity_property(ent, "mp"); 
    int seal = get_entity_property(ent, "seal_energy");   

    if (energy_cost > mp || seal > energy_cost)
    {
        return 0;
    }

    // All conditions passed. Deduct energy and set the animation.
    mp = mp - energy_cost;

    set_entity_property(ent, "mp", mp);

    performattack(ent, openborconstant("ANI_FREESPECIAL6"), 0);

    // Clear key flag.
    key_release -= openborconstant("FLAG_JUMP");
    changeplayerproperty(player_index, "releasekeys", key_release);

    // Return true.
    return 1;

#undef DC_TERRY_RISING_TACKLE_DELAY
}

// Terry Bogard key key capture.
int dc_try_terry_empty_series()
{
    void ent;
    int player_index;    
    int key_press;
    int rush_count;
    int animation;
    int idle;

    int empty_series_2;

    // Let's set up foundation variables.

    ent = getplayerproperty(player_index, "entity");
    player_index = getlocalvar("player");

    key_press = getplayerproperty(player_index, "newkeys");

    if (!(key_press & openborconstant("FLAG_ATTACK")))
    {
        return;
    }

    rush_count = getentityproperty(ent, "rush_count");

    if (rush_count > 0)
    {
        return;
    }
    
    idle = get_entity_property(ent, "idle_state");

    if (idle)
    {
        return;
    }

    animation = get_entity_property(ent, "animation_id");

    log("\n animation: " + animation + ", openborconstant(ANI_ATTACK1): " + openborconstant("ANI_ATTACK1"));


    if (animation == openborconstant("ANI_ATTACK1"))
    {
        performattack(ent, openborconstant("ANI_ATTACK5"));

        setlocalvar("dc_combo_empty_series_2" + player_index, openborconstant("ANI_ATTACK5"));
    }
    else if(animation == openborconstant("ANI_ATTACK5"))
    {
        empty_series_2 = getlocalvar("dc_combo_empty_series_2" + player_index);

        if (empty_series_2 == openborconstant("ANI_ATTACK5"))
        {
            performattack(ent, openborconstant("ANI_ATTACK1"));
        }

        setlocalvar("dc_combo_empty_series_2" + player_index, NULL());
    }
}


void main(){

    dc_try_terry_rising_tackle();
    //dc_try_terry_empty_series();
}