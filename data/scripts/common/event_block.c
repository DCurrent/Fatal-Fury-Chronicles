#import "data/scripts/common/dc_find_block_height_animation.c"

void main()
{
	int animation;
	void ent;

	ent = getlocalvar("self");
	animation = dc_find_block_height_animation();

	changeentityproperty(ent, "animation", animation);
}
