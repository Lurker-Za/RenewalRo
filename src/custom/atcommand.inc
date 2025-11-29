// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

/**
 * Custom Atcommands
 * Place the body of custom atcommands in this file.
 * Format:
 *	ACMD_FUNC(command_name)
 *	{
 *		<code>;
 *	}
 **/

//ACMD_FUNC(newcommand)
//{
//	clif_displaymessage(fd, "It works!");
//	clif_specialeffect(&sd->bl, EF_HEARTCASTING, AREA);
//	return 0;
//}

ACMD_FUNC(pcmileage)
{
	int pcm=0, ret=-1;
	nullpo_retr(-1, sd);
	int64 points = pc_readparam( sd, SP_GOLDPC_POINTS );

	if (!message || !*message || (pcm = atoi(message)) == 0) {
		clif_displaymessage(fd, msg_txt(sd,1012)); // Please enter an amount (usage: @pcmileage <amount>).
		return -1;
	}

	if(pcm != 0){
		points = cap_value((points + pcm), 0, 300);
		pc_setparam(sd, SP_GOLDPC_POINTS, points);
		clif_goldpc_info(*sd);
	}
	return 0;
}
