
#define DC_DISNEY_CANCEL_KEY_PREFIX "dc_cancel_"

void dc_disney_cancel_setup(int animation_cancel_to, int animation_cancel_from, int frame_start, int frame_end, int hits_min, int hits_max)
{
    int index = 0;
    char key = "";

    log("\n");
    log("\n dc_disney_cancel_setup()");

    // Find the first available index by checking
    // for previous cancel sets until we get an
    // uninitialized variable.

    do
    {
        key = DC_DISNEY_CANCEL_KEY_PREFIX + animation_cancel_to + "_" + index;
        index++;

        log("\n key: " + key);

    } while (getlocalvar(key + "_ani"));

    index--;

    // Create an artificial 2D array. This array is keyed
    // by a combination of the cancel into animation and
    // sequential index (see above).
    //
    // Each array element is an array containing the ID 
    // of an animation that can be canceled from, and the 
    // start/end frame range.
    //
    // cancel_list[animation_cancel_to + index] = {animation_cancel_from, frame_range_start, frame_range_end}
    //
    // We are using an artificial array instead of OpenBOR
    // Script's native array support because native arrays
    // must be actively removed from memory once established.
    // By using local vars, our artificial array here is
    // fire and forget.

    setlocalvar(key + "_ani", animation_cancel_from);
    setlocalvar(key + "_frame_start", frame_start);
    setlocalvar(key + "_frame_end", frame_end);
    setlocalvar(key + "_hits_min", hits_min);
    setlocalvar(key + "_hits_max", hits_max);

    log("\n\t" + key + " _ani: " + getlocalvar(key + "_ani"));
    log("\n\t" + key + " _frame_start: " + getlocalvar(key + "_frame_start"));
    log("\n\t" + key + " _frame_end: " + getlocalvar(key + "_frame_end"));
}

int dc_disney_check_cancel(void ent, int animation_cancel_to)
{
    int index = 0;
    char key = "";

    int animation_id = get_entity_property(ent, "animation_id");
    int animation_frame = get_entity_property(ent, "animation_frame");

    int cancel_from;

    int frame_start = 0;
    int frame_end = 0;
    int hits_max = 0;
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
        key = DC_DISNEY_CANCEL_KEY_PREFIX + animation_cancel_to + "_" + index;

        log("\n key: " + key);

        cancel_from = getlocalvar(key + "_ani");

        log("\n cancel_from: " + cancel_from);
        log("\n animation_id: " + animation_id);

        if (cancel_from == animation_id)
        {
            frame_start = getlocalvar(key + "_frame_start");
            frame_end = getlocalvar(key + "_frame_start");

            // Make sure empty values are integers.
            if (!frame_start) frame_start = 0;
            if (!frame_end) frame_end = 0;

            log("\n animation_frame: " + animation_frame);
            log("\n frame_start: " + frame_start);
            log("\n frame_end: " + frame_end);

            // Current frame is within frame range or 
            // there is no frame range at all?
            if ((animation_frame >= frame_start || frame_start == -1) && (animation_frame <= frame_end || frame_end == -1))
            {
                // Now run same check as frame, but for
                // minimum and maximum hits.

                hits_min = getlocalvar(key + "_hits_min");
                hits_max = getlocalvar(key + "_hits_max");

                if (!hits_min) hits_min = 0;
                if (!hits_max) hits_max = 0;

                hits_count = getentityproperty(ent, "rush_count");

                log("\n hits_count: " + hits_count);
                log("\n hits_min: " + hits_min);
                log("\n hits_max: " + hits_max);

                if ((hits_count >= hits_min || hits_min == -1) && (hits_count <= hits_max || hits_max == -1))
                {                    
                    return 1;
                }
            }
        }

        // Increment index for next loop.
        index++;

    }
    while (cancel_from);

    // If we get here, there were no valid
    // cancels found. Return false.
    return 0;
}

void oncreate()
{    
    dc_disney_cancel_setup(openborconstant("ANI_FREESPECIAL6"), openborconstant("ANI_ATTACK1"), -1, -1, -1, -1);
    dc_disney_cancel_setup(openborconstant("ANI_FREESPECIAL6"), openborconstant("ANI_ATTACK2"), -1, -1 - 1, -1);
    dc_disney_cancel_setup(openborconstant("ANI_FREESPECIAL6"), openborconstant("ANI_ATTACK3"), -1, -1 - 1, -1);
    dc_disney_cancel_setup(openborconstant("ANI_FREESPECIAL6"), openborconstant("ANI_ATTACK4"), -1, -1 - 1, -1);
    dc_disney_cancel_setup(openborconstant("ANI_FREESPECIAL6"), openborconstant("ANI_ATTACK5"), -1, -1 - 1, -1);
    dc_disney_cancel_setup(openborconstant("ANI_FREESPECIAL6"), openborconstant("ANI_ATTACK6"), -1, -1 - 1, -1);
    dc_disney_cancel_setup(openborconstant("ANI_FREESPECIAL6"), openborconstant("ANI_CHARGEATTACK"), -1, -1 - 1, -1);
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