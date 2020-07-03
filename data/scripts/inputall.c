void main()
{
	int player_index = getlocalvar("player");

	// Macro test.
	int key_press = getplayerproperty(player_index, "newkeys");
	
	if (key_press & openborconstant("FLAG_ATTACK2"))
	{
		key_press = openborconstant("FLAG_ATTACK") + openborconstant("FLAG_JUMP");
		changeplayerproperty(player_index, "newkeys", key_press);		
	}
}