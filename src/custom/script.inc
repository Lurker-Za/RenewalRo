// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

/**
 * Custom Script Commands
 * Place the body of custom script commands in this file.
 * Format:
 *	BUILDIN_FUNC(command_name)
 *	{
 *		<code>;
 *	}
 **/

//BUILDIN_FUNC(example)
//{
//	ShowInfo("buildin_example: It works!\n");
//	script_pushint(st,1);
//	return 0;
//}

//-----------------------------------------------------
//Custom bonuses start
//-----------------------------------------------------
BUILDIN_FUNC(exbonus)
{
	uint16 dur, pos;
	int16 rate;
	TBL_PC* sd;
	const char *bonus_script = NULL;

	if( !script_rid2sd(sd) )
		return SCRIPT_CMD_SUCCESS; // no player attached

	if (current_equip_combo_pos)
		pos = current_equip_combo_pos;
	else
		pos = sd->inventory.u.items_inventory[current_equip_item_index].equip;

	rate = script_getnum(st,3);
	dur = script_getnum(st,4);
	bonus_script = script_getstr(st,2);
	if( !rate || !dur || !pos || !bonus_script )
		return SCRIPT_CMD_SUCCESS;

	if( pc_addexbonus(sd->exbonus, bonus_script, rate, dur, pos) )
	{
		script_add_exbonus(bonus_script);
	}

	return SCRIPT_CMD_SUCCESS;
}

BUILDIN_FUNC(getequipcombocnt) {
	map_session_data *sd;

	if (!script_rid2sd(sd))
		return SCRIPT_CMD_SUCCESS;
    
    if (sd) {
        script_pushint(st, sd->current_combo_count);
    } else {
        script_pushint(st, -1);
    }
    return SCRIPT_CMD_SUCCESS;
}

BUILDIN_FUNC(clonemob)
{
	TBL_PC *sd, *msd=NULL;
	uint32 char_id, id, master_id, damage = 0, x, y, flag = 0;
	int16 m;
	enum e_mode mode = MD_NONE;

	uint32 duration = 0;
	const char *mapname,*event;

	mapname=script_getstr(st,2);
	x=script_getnum(st,3);
	y=script_getnum(st,4);
	event=script_getstr(st,5);
	char_id=script_getnum(st,6);

	if( script_hasdata(st,7) )
		id=script_getnum(st,7);

	if( script_hasdata(st,8) )
		master_id=script_getnum(st,8);

	if( script_hasdata(st,9) )
		mode=static_cast<e_mode>(script_getnum(st,9));

	if( script_hasdata(st,10) )
		flag=script_getnum(st,10);

	if( script_hasdata(st,11) )
		duration=script_getnum(st,11);

	if( script_hasdata(st,12) )
		damage=script_getnum(st,12);

	check_event(st, event);

	m = map_mapname2mapid(mapname);
	if (m < 0)
		return SCRIPT_CMD_SUCCESS;

	sd = map_charid2sd(char_id);

	if (master_id) {
		msd = map_charid2sd(master_id);
		if (msd)
			master_id = msd->id;
		else
			master_id = 0;
	}
	if (sd && id) //Return ID of newly crafted clone.
		script_pushint(st,pc_summon_slave(sd, m, x, y, event, id, master_id, mode, flag, 1000*duration, damage));
	else //Failed to create clone.
		script_pushint(st,0);

	return SCRIPT_CMD_SUCCESS;
}
//-----------------------------------------------------
//Custom bonuses end
//-----------------------------------------------------
