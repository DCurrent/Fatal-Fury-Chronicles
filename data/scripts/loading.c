#include "data/scripts/dc_d20/main.c"
#include "data/scripts/dc_fidelity/main.c"

void oncreate()
{
	log("\n");
	log("loaded.c");
	log("\t");
	log("- oncreate().");
	log("\n");

	// Global sounds.
	dc_fidelity_setup(DC_FIDELITY_CATEGORY_GLOBAL, DC_FIDELITY_TYPE_SOUND_ATTACK_LIGHT, "data/sounds/custom/golden_axe_whiff_light_0.wav");
	dc_fidelity_setup(DC_FIDELITY_CATEGORY_GLOBAL, DC_FIDELITY_TYPE_SOUND_ATTACK_LIGHT, "data/sounds/custom/rb-whiff-light-0.wav");
	dc_fidelity_setup(DC_FIDELITY_CATEGORY_GLOBAL, DC_FIDELITY_TYPE_SOUND_ATTACK_MEDIUM, "data/sounds/custom/rb-whiff-med-0.wav");
	dc_fidelity_setup(DC_FIDELITY_CATEGORY_GLOBAL, DC_FIDELITY_TYPE_SOUND_ATTACK_MEDIUM_BLADE, "data/sounds/custom/samurai_shodown_whiff_light_0.wav");
	dc_fidelity_setup(DC_FIDELITY_CATEGORY_GLOBAL, DC_FIDELITY_TYPE_SOUND_ATTACK_MEDIUM_BLADE, "data/sounds/custom/samurai_shodown_whiff_light_1.wav");
	dc_fidelity_setup(DC_FIDELITY_CATEGORY_GLOBAL, DC_FIDELITY_TYPE_SOUND_ATTACK_HEAVY, "data/sounds/custom/rb-whiff-heavy-0.wav");
	dc_fidelity_setup(DC_FIDELITY_CATEGORY_GLOBAL, DC_FIDELITY_TYPE_SOUND_ATTACK_HEAVY, "data/sounds/custom/rb-whiff-heavy-1.wav");
	dc_fidelity_setup(DC_FIDELITY_CATEGORY_GLOBAL, DC_FIDELITY_TYPE_SOUND_ATTACK_HEAVY_BLADE, "data/sounds/custom/samurai_shodown_whiff_heavy_0.wav");	

	// Global voices.
	dc_fidelity_setup(DC_FIDELITY_CATEGORY_GLOBAL, DC_FIDELITY_TYPE_VOICE_KO, "data/sounds/custom/avp_soldier_ko_0.wav");
	dc_fidelity_setup(DC_FIDELITY_CATEGORY_GLOBAL, DC_FIDELITY_TYPE_VOICE_KO, "data/sounds/custom/avp_soldier_ko_1.wav");
	dc_fidelity_setup(DC_FIDELITY_CATEGORY_GLOBAL, DC_FIDELITY_TYPE_VOICE_KO, "data/sounds/custom/fatal_fury_rebout_ko.wav");
	dc_fidelity_setup(DC_FIDELITY_CATEGORY_GLOBAL, DC_FIDELITY_TYPE_VOICE_KO, "data/sounds/custom/fighters_history_2_ray_ko.wav");
	dc_fidelity_setup(DC_FIDELITY_CATEGORY_GLOBAL, DC_FIDELITY_TYPE_VOICE_KO, "data/sounds/custom/mortal_kombat_pain_0.wav");
	dc_fidelity_setup(DC_FIDELITY_CATEGORY_GLOBAL, DC_FIDELITY_TYPE_VOICE_KO, "data/sounds/custom/ninja_spirit_ko.wav");
	dc_fidelity_setup(DC_FIDELITY_CATEGORY_GLOBAL, DC_FIDELITY_TYPE_VOICE_KO, "data/sounds/custom/punisher_ko_0.wav");
	dc_fidelity_setup(DC_FIDELITY_CATEGORY_GLOBAL, DC_FIDELITY_TYPE_VOICE_KO, "data/sounds/custom/punisher_ko_1.wav");
	dc_fidelity_setup(DC_FIDELITY_CATEGORY_GLOBAL, DC_FIDELITY_TYPE_VOICE_KO, "data/sounds/custom/punisher_ko_2.wav");
	dc_fidelity_setup(DC_FIDELITY_CATEGORY_GLOBAL, DC_FIDELITY_TYPE_VOICE_KO, "data/sounds/custom/sor2_ko_0.wav");
	dc_fidelity_setup(DC_FIDELITY_CATEGORY_GLOBAL, DC_FIDELITY_TYPE_VOICE_KO, "data/sounds/custom/sor2_ko_1.wav");
	dc_fidelity_setup(DC_FIDELITY_CATEGORY_GLOBAL, DC_FIDELITY_TYPE_VOICE_KO, "data/sounds/custom/sor3_ko_0.wav");
	dc_fidelity_setup(DC_FIDELITY_CATEGORY_GLOBAL, DC_FIDELITY_TYPE_VOICE_KO, "data/sounds/custom/unknown_ko.wav");

	// Jump and hop liftoff.
	dc_fidelity_setup("hop_liftoff", DC_FIDELITY_TYPE_SOUND_SPAWN, "data/sounds/custom/fatal_fury_1_jump.wav");
	dc_fidelity_setup("jump_liftoff", DC_FIDELITY_TYPE_SOUND_SPAWN, "data/sounds/custom/fatal_fury_1_jump.wav");

	// Jump land.
	dc_fidelity_setup("jump_land", DC_FIDELITY_TYPE_SOUND_SPAWN, "data/sounds/custom/fatal_fury_1_land.wav");

	// Fall Land.
	dc_fidelity_setup("fall_land", DC_FIDELITY_TYPE_SOUND_SPAWN, "data/sounds/custom/unknown_fall_land.wav");

	// Heavy slam Land.
	dc_fidelity_setup("flash_slam_heavy", DC_FIDELITY_TYPE_SOUND_SPAWN, "data/sounds/custom/unknown_slam.wav");

	// Block flash.
	dc_fidelity_setup("block", DC_FIDELITY_TYPE_SOUND_SPAWN, "data/sounds/custom/cvs_block.wav");

	//  Hit flash
	dc_fidelity_setup("Flash", DC_FIDELITY_TYPE_SOUND_SPAWN, "data/sounds/custom/double_dragon_2_hit_0.wav");
	dc_fidelity_setup("flash_fatal_fury", DC_FIDELITY_TYPE_SOUND_SPAWN, "data/sounds/custom/fatal_fury_1_hit.wav");
	dc_fidelity_setup("flash_indirect", DC_FIDELITY_TYPE_SOUND_SPAWN, "data/sounds/custom/sor1_hit_0.wav");
	dc_fidelity_setup("flash_cvs_cut_heavy", DC_FIDELITY_TYPE_SOUND_SPAWN, "data/sounds/custom/mvc_slash_0.wav");
	dc_fidelity_setup("flash_cvs_cut_blunt", DC_FIDELITY_TYPE_SOUND_SPAWN, "data/sounds/custom/fatal_fury_1_hit.wav");

	

	// Galford
	dc_fidelity_setup("Galford_Weller", DC_FIDELITY_TYPE_VOICE_SPAWN_NEW, "data/chars/galford/sounds/voice-lets-go-poppy.wav");

	dc_fidelity_setup("Galford_Weller", DC_FIDELITY_TYPE_VOICE_KO, "data/chars/galford/sounds/voice-no.wav");

	dc_fidelity_setup("Galford_Weller", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_HEAVY, "data/chars/galford/sounds/voice-atk-3.wav");
	dc_fidelity_setup("Galford_Weller", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_HEAVY, "data/chars/galford/sounds/voice-atk-4.wav");
	dc_fidelity_setup("Galford_Weller", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_HEAVY, "data/chars/galford/sounds/voice-atk-5.wav");
	dc_fidelity_setup("Galford_Weller", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_HEAVY, "data/chars/galford/sounds/voice-atk-6.wav");
	dc_fidelity_setup("Galford_Weller", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_HEAVY, "data/chars/galford/sounds/voice-atk-7.wav");
	
	dc_fidelity_setup("Galford_Weller", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_LIGHT, "data/chars/galford/sounds/voice-atk-0.wav");
	dc_fidelity_setup("Galford_Weller", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_LIGHT, "data/chars/galford/sounds/voice-atk-1.wav");
	dc_fidelity_setup("Galford_Weller", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_LIGHT, "data/chars/galford/sounds/voice-atk-8.wav");

	dc_fidelity_setup("Galford_Weller", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_MEDIUM, "data/chars/galford/sounds/voice-atk-0.wav");
	dc_fidelity_setup("Galford_Weller", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_MEDIUM, "data/chars/galford/sounds/voice-atk-1.wav");
	dc_fidelity_setup("Galford_Weller", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_MEDIUM, "data/chars/galford/sounds/voice-atk-2.wav");

	dc_fidelity_setup("Galford_Weller", DC_FIDELITY_TYPE_VOICE_PAIN, "data/chars/galford/sounds/voice-pain-0.wav");
	dc_fidelity_setup("Galford_Weller", DC_FIDELITY_TYPE_VOICE_PAIN, "data/chars/galford/sounds/voice-pain-1.wav");
	dc_fidelity_setup("Galford_Weller", DC_FIDELITY_TYPE_VOICE_PAIN, "data/chars/galford/sounds/voice-pain-2.wav");
	dc_fidelity_setup("Galford_Weller", DC_FIDELITY_TYPE_VOICE_PAIN, "data/chars/galford/sounds/voice-pain-3.wav");

	dc_fidelity_setup("Galford_Weller", DC_FIDELITY_TYPE_VOICE_PAIN_FALL, "data/chars/galford/sounds/voice-pain-0.wav");
	dc_fidelity_setup("Galford_Weller", DC_FIDELITY_TYPE_VOICE_PAIN_FALL, "data/chars/galford/sounds/voice-pain-1.wav");
	dc_fidelity_setup("Galford_Weller", DC_FIDELITY_TYPE_VOICE_PAIN_FALL, "data/chars/galford/sounds/voice-pain-2.wav");
	dc_fidelity_setup("Galford_Weller", DC_FIDELITY_TYPE_VOICE_PAIN_FALL, "data/chars/galford/sounds/voice-pain-3.wav");
	

	dc_fidelity_setup("Galford_Weller", "sheath_sword", "data/chars/galford/sounds/sound_sheath_sword.wav");

	//  Ray
	dc_fidelity_setup("Ray", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_LIGHT, "data/chars/ray/sounds/spi_001e_01.wav");
	dc_fidelity_setup("Ray", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_LIGHT, "data/chars/ray/sounds/spi_002e_01.wav");
	dc_fidelity_setup("Ray", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_LIGHT, "data/chars/ray/sounds/spi_003e_01.wav");
	dc_fidelity_setup("Ray", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_LIGHT, "data/chars/ray/sounds/spi_004e_01.wav");

	dc_fidelity_setup("Ray", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_HEAVY, "data/chars/ray/sounds/spi_005e_01.wav");
	dc_fidelity_setup("Ray", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_HEAVY, "data/chars/ray/sounds/spi_006e_01.wav");
	dc_fidelity_setup("Ray", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_HEAVY, "data/chars/ray/sounds/spi_007e_01.wav");
	dc_fidelity_setup("Ray", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_HEAVY, "data/chars/ray/sounds/spi_008e_01.wav");
	dc_fidelity_setup("Ray", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_HEAVY, "data/chars/ray/sounds/spi_009e_01.wav");

	dc_fidelity_setup("Ray", DC_FIDELITY_TYPE_VOICE_BATTLE_TAUNT, "data/chars/ray/sounds/spi_023e_01.wav");
	dc_fidelity_setup("Ray", DC_FIDELITY_TYPE_VOICE_BATTLE_TAUNT, "data/chars/ray/sounds/spi_024e.wav");
	dc_fidelity_setup("Ray", DC_FIDELITY_TYPE_VOICE_BATTLE_TAUNT, "data/chars/ray/sounds/spi_025e.wav");
	dc_fidelity_setup("Ray", DC_FIDELITY_TYPE_VOICE_BATTLE_TAUNT, "data/chars/ray/sounds/spi_028e_pu.wav");
	dc_fidelity_setup("Ray", DC_FIDELITY_TYPE_VOICE_BATTLE_TAUNT, "data/chars/ray/sounds/spi_029e_pu.wav");
	dc_fidelity_setup("Ray", DC_FIDELITY_TYPE_VOICE_BATTLE_TAUNT, "data/chars/ray/sounds/spi_033be_pu.wav");
	dc_fidelity_setup("Ray", DC_FIDELITY_TYPE_VOICE_BATTLE_TAUNT, "data/chars/ray/sounds/spi_033e_pu.wav");
	dc_fidelity_setup("Ray", DC_FIDELITY_TYPE_VOICE_BATTLE_TAUNT, "data/chars/ray/sounds/spi_037e.wav");
	dc_fidelity_setup("Ray", DC_FIDELITY_TYPE_VOICE_BATTLE_TAUNT, "data/chars/ray/sounds/spi_038e.wav");
	dc_fidelity_setup("Ray", DC_FIDELITY_TYPE_VOICE_BATTLE_TAUNT, "data/chars/ray/sounds/spi_074e.wav");
	dc_fidelity_setup("Ray", DC_FIDELITY_TYPE_VOICE_BATTLE_TAUNT, "data/chars/ray/sounds/spi_074e_pu.wav");	

	dc_fidelity_setup("Ray", DC_FIDELITY_TYPE_VOICE_PAIN, "data/chars/ray/sounds/spi_013e_01.wav");
	dc_fidelity_setup("Ray", DC_FIDELITY_TYPE_VOICE_PAIN, "data/chars/ray/sounds/spi_014e_01.wav");
	dc_fidelity_setup("Ray", DC_FIDELITY_TYPE_VOICE_PAIN, "data/chars/ray/sounds/spi_015e_01.wav");
	dc_fidelity_setup("Ray", DC_FIDELITY_TYPE_VOICE_PAIN, "data/chars/ray/sounds/spi_016e_01.wav");
	dc_fidelity_setup("Ray", DC_FIDELITY_TYPE_VOICE_PAIN, "data/chars/ray/sounds/spi_017e_01.wav");

	dc_fidelity_setup("Ray", DC_FIDELITY_TYPE_VOICE_PAIN_FALL, "data/chars/ray/sounds/spi_018e_01.wav");
	dc_fidelity_setup("Ray", DC_FIDELITY_TYPE_VOICE_PAIN_FALL, "data/chars/ray/sounds/spi_019e_01.wav");
	dc_fidelity_setup("Ray", DC_FIDELITY_TYPE_VOICE_PAIN_FALL, "data/chars/ray/sounds/spi_020e_01.wav");

	//  Ryu  
	dc_fidelity_setup("Ryu", DC_FIDELITY_TYPE_VOICE_SPAWN_NEW, "data/chars/ryu/sounds/ABD_CV_E_00000000_01.wav");
	dc_fidelity_setup("Ryu", DC_FIDELITY_TYPE_VOICE_SPAWN_NEW, "data/chars/ryu/sounds/ryu_038e_01.wav");

	dc_fidelity_setup("Ryu", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_LIGHT, "data/chars/ryu/sounds/ryu_001e_01.wav");
	dc_fidelity_setup("Ryu", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_LIGHT, "data/chars/ryu/sounds/ryu_002e_01.wav");
	dc_fidelity_setup("Ryu", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_LIGHT, "data/chars/ryu/sounds/ryu_003e_01.wav");
	dc_fidelity_setup("Ryu", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_MEDIUM, "data/chars/ryu/sounds/ryu_004e_01.wav");
	dc_fidelity_setup("Ryu", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_MEDIUM, "data/chars/ryu/sounds/ryu_005e_01.wav");
	dc_fidelity_setup("Ryu", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_MEDIUM, "data/chars/ryu/sounds/ryu_006e_01.wav");
	dc_fidelity_setup("Ryu", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_HEAVY, "data/chars/ryu/sounds/ryu_007e_01.wav");
	dc_fidelity_setup("Ryu", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_HEAVY, "data/chars/ryu/sounds/ryu_008e_01.wav");
	dc_fidelity_setup("Ryu", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_HEAVY, "data/chars/ryu/sounds/ryu_009e_01.wav");

	dc_fidelity_setup("Ryu", DC_FIDELITY_TYPE_VOICE_BATTLE_TAUNT, "data/chars/ryu/sounds/ryu_044e_01.wav");
	dc_fidelity_setup("Ryu", DC_FIDELITY_TYPE_VOICE_BATTLE_TAUNT, "data/chars/ryu/sounds/ryu_045e_01.wav");
	dc_fidelity_setup("Ryu", DC_FIDELITY_TYPE_VOICE_BATTLE_TAUNT, "data/chars/ryu/sounds/ryu_049e_01.wav");
	dc_fidelity_setup("Ryu", DC_FIDELITY_TYPE_VOICE_BATTLE_TAUNT, "data/chars/ryu/sounds/ryu_116e_01.wav");
	dc_fidelity_setup("Ryu", DC_FIDELITY_TYPE_VOICE_BATTLE_TAUNT, "data/chars/ryu/sounds/ryu_117e_01.wav");

	dc_fidelity_setup("Ryu", DC_FIDELITY_TYPE_VOICE_PAIN, "data/chars/ryu/sounds/ABD_CV_E_00000030_01.wav");
	dc_fidelity_setup("Ryu", DC_FIDELITY_TYPE_VOICE_PAIN, "data/chars/ryu/sounds/ABD_CV_E_00000031_01.wav");
	dc_fidelity_setup("Ryu", DC_FIDELITY_TYPE_VOICE_PAIN, "data/chars/ryu/sounds/ABD_CV_E_00000032_01.wav");
	dc_fidelity_setup("Ryu", DC_FIDELITY_TYPE_VOICE_PAIN, "data/chars/ryu/sounds/ABD_CV_E_00000033_01.wav");
	dc_fidelity_setup("Ryu", DC_FIDELITY_TYPE_VOICE_PAIN, "data/chars/ryu/sounds/ABD_CV_E_00000034_01.wav");

	dc_fidelity_setup("Ryu", DC_FIDELITY_TYPE_VOICE_PAIN_FALL, "data/chars/ryu/sounds/ABD_CV_E_00000035_01.wav");
	dc_fidelity_setup("Ryu", DC_FIDELITY_TYPE_VOICE_PAIN_FALL, "data/chars/ryu/sounds/ABD_CV_E_00000036_01.wav");
	dc_fidelity_setup("Ryu", DC_FIDELITY_TYPE_VOICE_PAIN_FALL, "data/chars/ryu/sounds/ABD_CV_E_00000037_01.wav");
	dc_fidelity_setup("Ryu", DC_FIDELITY_TYPE_VOICE_PAIN_FALL, "data/chars/ryu/sounds/ABD_CV_E_00000038_01.wav");
	dc_fidelity_setup("Ryu", DC_FIDELITY_TYPE_VOICE_PAIN_FALL, "data/chars/ryu/sounds/ABD_CV_E_00000039_01.wav");

	dc_fidelity_setup("Ryu", "Hadouken", "data/chars/ryu/sounds/ABD_CV_E_0000000B_01.wav");
	dc_fidelity_setup("Ryu", "Hadouken", "data/chars/ryu/sounds/voice-hadouken-0c.wav");

	dc_fidelity_setup("Ryu", "Shoryuken", "data/chars/ryu/sounds/ABD_CV_E_0000000E_01.wav"); 
	dc_fidelity_setup("Ryu", "Shoryuken", "data/chars/ryu/sounds/ryu_051e_01.wav");

	dc_fidelity_setup("Ryu", "Tatus", "data/chars/ryu/sounds/ABD_CV_E_00000010_01.wav");
	dc_fidelity_setup("Ryu", "Tatsu", "data/chars/ryu/sounds/ryu_052e_01.wav");

	dc_fidelity_setup("Ryu", "Thrust", "data/chars/ryu/sounds/ryu_053e_01.wav");
	dc_fidelity_setup("Ryu", "Thrust", "data/chars/ryu/sounds/ryu_054e_01.wav");

	dc_fidelity_setup("ryu_hadouken", DC_FIDELITY_TYPE_SOUND_SPAWN, "data/chars/ryu/hadouken/ryu_se_hadou_01.wav");
	   
	// Terry
	dc_fidelity_setup("Terry_Bogard", "power_wave", "data/chars/terry/sounds/rb-terry-power-wave-0.wav");
	
	dc_fidelity_setup("Terry_Bogard", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_LIGHT, "data/chars/terry/sounds/rb_terry_voice_attack_light_0.wav");
	dc_fidelity_setup("Terry_Bogard", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_LIGHT, "data/chars/terry/sounds/rb_terry_voice_attack_light_1.wav");
	dc_fidelity_setup("Terry_Bogard", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_LIGHT, "data/chars/terry/sounds/rb_terry_voice_attack_light_2.wav");
	dc_fidelity_setup("Terry_Bogard", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_MEDIUM, "data/chars/terry/sounds/rb_terry_voice_attack_light_0.wav");
	dc_fidelity_setup("Terry_Bogard", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_MEDIUM, "data/chars/terry/sounds/rb_terry_voice_attack_light_1.wav");
	dc_fidelity_setup("Terry_Bogard", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_MEDIUM, "data/chars/terry/sounds/rb_terry_voice_attack_light_2.wav");
	dc_fidelity_setup("Terry_Bogard", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_MEDIUM, "data/chars/terry/sounds/rb_terry_voice_attack_heavy_0.wav");
	dc_fidelity_setup("Terry_Bogard", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_MEDIUM, "data/chars/terry/sounds/rb_terry_voice_attack_light_1.wav");
	dc_fidelity_setup("Terry_Bogard", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_HEAVY, "data/chars/terry/sounds/rb_terry_voice_attack_heavy_0.wav");
	dc_fidelity_setup("Terry_Bogard", DC_FIDELITY_TYPE_VOICE_ATTACK_SHOUT_HEAVY, "data/chars/terry/sounds/rb_terry_voice_attack_heavy_1.wav");

	dc_fidelity_setup("Terry_Bogard", DC_FIDELITY_TYPE_VOICE_BATTLE_TAUNT, "data/chars/terry/sounds/terry_clip_buy_you_a_drink.wav");
	dc_fidelity_setup("Terry_Bogard", DC_FIDELITY_TYPE_VOICE_BATTLE_TAUNT, "data/chars/terry/sounds/terry_clip_goodnight.wav");
}

void ondestroy()
{
	log("\n");
	log("loaded.c");
	log("\t");
	log("- ondestroy().");
	log("\n");
}

void main()
{
	void	s;
	void	value	=	getlocalvar("value");
	void	max		=	getlocalvar("max");
	if(max==1){
		return;
	}else{}

	void percent=value*100/max;
	percent%=++percent;

	void dot=percent%3;
	if(dot==0)
		s=".";
	else if(dot==1)
		s="..";
	else
		s="...";

	drawstring(194,60,2,"WARNING");
	drawstring(36,100,2,"THIS GAME IS NOT PRODUCED UNDER LICENCE OF");
	drawstring(162,140,2,"CAPCOM AND SNK");
	drawstring(143,242,0,"Loading Models..."+percent);
	drawstring(259,242,0,"% Complete"+s);
	drawbox(0,260,480,2,11,rgbcolor(0,122,133),0);
	drawbox(0,260,percent*480*0.01,2,15,rgbcolor(0,233,233),0);

	if (value == max)
	{
	}

}




