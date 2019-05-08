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
stock respawnAtHospital(playerid) {
	new min_id;
	new Float:min_distance = 99999.0;
	new Float:hospitalCoords[][] = {
	    {1178.62330, -1323.8820, 14.1292, 270.0},
	    {2034.24260, -1414.6997, 16.9922, 135.0},
	    {-2200.5435, -2310.4019, 30.6250, 318.0},
	    {-316.22600, 1055.19190, 19.7422, 3.000},
	    {1243.31880, 329.896100, 19.7578, 335.0},
		{1876.10530, 2238.56520, 11.1250, 1.000},
		{1606.86690, 1822.86160, 10.8203, 355.0},
		{-2658.1619, 631.018000, 14.4531, 18.00}
	};
	for (new x; x < sizeof(hospitalCoords); x++) {
	    new Float: distance = GetPlayerDistanceFromPoint(playerid, hospitalCoords[x][0], hospitalCoords[x][1], hospitalCoords[x][2]);
	    if (distance < min_distance) {
	        min_distance = distance;
	        min_id = x;
	    }
	}
	SetPlayerPos(playerid, hospitalCoords[min_id][0], hospitalCoords[min_id][1], hospitalCoords[min_id][2]);
	SetPlayerFacingAngle(playerid, hospitalCoords[min_id][3]);
	SetCameraBehindPlayer(playerid);
}
stock Cash_Give(playerid, money) {
    P[playerid][p_cash] += money;
    ResetPlayerMoney(playerid);
    GivePlayerMoney(playerid, P[playerid][p_cash]);
}
