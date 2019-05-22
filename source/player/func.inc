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
stock Name(playerid) {
    new dest[MAX_PLAYER_NAME+1];
	GetPlayerName(playerid, dest, MAX_PLAYER_NAME);
	return dest;
}
stock TeleportPlayerToPos(playerid, Float:x, Float:y, Float:z, interiorid, worldid) {
	SetPlayerPos(playerid, x, y, z);
	SetPlayerInterior(playerid, interiorid);
	SetPlayerVirtualWorld(playerid, worldid);
}
stock Message_ToIRC(playerid, const fmat[], va_args<>) {
	foreach(new i : Player)
		if (GetPVarInt(i, "IRC") == GetPVarInt(playerid, "IRC"))
			SendClientMessage(i, -1, va_return(fmat, va_start<2>));
}
stock IRCMembers(playerid) {
	va_SendClientMessage(playerid, -1, "[IRC] Участники %i IRC канала:", GetPVarInt(playerid, "IRC"));
	foreach(new i : Player)
		if (GetPVarInt(i, "IRC") == GetPVarInt(playerid, "IRC"))
			va_SendClientMessage(playerid, -1, "%s[%i]", Name(i), i);
}
stock Get_TeamName(playerid) {
	new dests[32];
	switch(P[playerid][p_job_team]) {
		case ORG_UNKNOWN: dests = "Гражданин";
		
		case ORG_GOVERNMENT: dests = "Правительство Штата";
		case ORG_FBI: dests = "Федеральное Бюро Расследований";
		case ORG_LSPD: dests = "Полиция Лос Сантос";
		case ORG_SFPD: dests = "Полиция Сан Фиерро";
		case ORG_LVPD: dests = "Полиция Лас Вентурас";
		case ORG_MILITARY: dests = "Национальная Гвардия";
		case ORG_EMERGENCY: dests = "Служба Экстренной Помощи";
		case ORG_SANNEWS: dests = "Новости Сан Андреас";
		case ORG_AUTOSCHOOL: dests = "Центр Аттестации";

		case ORG_GROVE: dests = "Банда 'Grove Street Families'";
		case ORG_BALLAS: dests = "Банда 'Ballas'";
		case ORG_AZTECAS: dests = "Банда 'Varrios Los Aztecas'";
		case ORG_VAGOS: dests = "Банда 'Los Santos Vagos'";
		case ORG_RIFA: dests = "Банда 'San Fierro Rifa'";

		case ORG_CHINESE: dests = "Семья 'Триада'";
		case ORG_DANANG: dests = "Семья 'Da Nang Boys'";
		case ORG_RUSSIAN: dests = "Семья 'Воры в законе'";
		case ORG_ITALIAN: dests = "Семья 'Ла Коза Ностра'";

		case ORG_BIKERS: dests = "Байкеры Сан-Андреас";
		case ORG_ICA: dests = "Контрактное Агентство";
	}
	return dests;
}
