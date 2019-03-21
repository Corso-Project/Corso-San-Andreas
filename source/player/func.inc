stock Update_PlayerSettings(playerid) {
	format(P[playerid][p_settings], 10, "%i", P[playerid][p_saveLastPos]);
	orm_update(P[playerid][_p_ormid]);
}
stock Show_Stats(playerid, targetid) {
	new Float:KD;
	KD = Float:P[targetid][p_kills]/Float:P[targetid][p_deaths];
	new string[10];
	format(string,sizeof(string), "+ %f",KD);
	new stringStats[84+24+2+2+9+9];
	format(stringStats, sizeof(stringStats),
	"{FFFFFF}Никнейм: %s\n\
	Убийств: %i\n\
	Смертей: %i\n\
	Денег: %i\n\
	K/D: %0.2f",
	P[targetid][p_name],
	P[targetid][p_kills],
	P[targetid][p_deaths],
	P[targetid][p_cash],
	string);

	Dialog_Open(playerid, Dialog:d_player_stats, DIALOG_STYLE_MSGBOX, "Статистика", stringStats, "Закрыть", "");
}
