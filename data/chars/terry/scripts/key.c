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

    // -- Not in pain.

    if (get_entity_property(ent, "in_pain") || get_entity_property(ent, "in_pain_back"))
    {
        return 0;
    }

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