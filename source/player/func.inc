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
	"{FFFFFF}ID ��������: %i\n\
	�������: %s\n\
	�������: %i\n\
	�������: %i\n\
	�����: %i\n\
	K/D: %0.2f",
	P[targetid][p_uid],
	P[targetid][p_name],
	P[targetid][p_kills],
	P[targetid][p_deaths],
	P[targetid][p_cash],
	string);

	Dialog_Open(playerid, Dialog:d_player_stats, DIALOG_STYLE_MSGBOX, "����������", stringStats, "�������", "");
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
	va_SendClientMessage(playerid, -1, "[IRC] ��������� %i IRC ������:", GetPVarInt(playerid, "IRC"));
	foreach(new i : Player)
		if (GetPVarInt(i, "IRC") == GetPVarInt(playerid, "IRC"))
			va_SendClientMessage(playerid, -1, "%s[%i]", Name(i), i);
}
stock Get_TeamName(playerid) {
	new dests[32];
	switch(P[playerid][p_job_team]) {
		case ORG_UNKNOWN: dests = "���������";

		case ORG_GOVERNMENT: dests = "������������� �����";
		case ORG_FBI: dests = "����������� ���� �������������";
		case ORG_LSPD: dests = "������� ��� ������";
		case ORG_SFPD: dests = "������� ��� ������";
		case ORG_LVPD: dests = "������� ��� ��������";
		case ORG_MILITARY: dests = "������������ �������";
		case ORG_EMERGENCY: dests = "������ ���������� ������";
		case ORG_SANNEWS: dests = "������� ��� �������";
		case ORG_AUTOSCHOOL: dests = "����� ����������";

		case ORG_GROVE: dests = "����� 'Grove Street Families'";
		case ORG_BALLAS: dests = "����� 'Ballas'";
		case ORG_AZTECAS: dests = "����� 'Varrios Los Aztecas'";
		case ORG_VAGOS: dests = "����� 'Los Santos Vagos'";
		case ORG_RIFA: dests = "����� 'San Fierro Rifa'";

		case ORG_CHINESE: dests = "����� '������'";
		case ORG_DANANG: dests = "����� 'Da Nang Boys'";
		case ORG_RUSSIAN: dests = "����� '���� � ������'";
		case ORG_ITALIAN: dests = "����� '�� ���� ������'";

		case ORG_BIKERS: dests = "������� ���-�������";
		case ORG_CA: dests = "����������� ���������";
	}
	return dests;
}
stock Show_PlayerLic(playerid, targetid){
	new output[482+1],lic_car[26],lic_aircraft[26],lic_boat[26],lic_moto[26],lic_weapon[26],lic_freight[26],lic_helicopter[26];
	lic_car = (P[playerid][p_lic_car] == 1) ? "{33AA33}� �������{FFFFFF}" : "{AA3333}���{FFFFFF}";
	lic_aircraft = (P[playerid][p_lic_aircraft] == 1) ? "{33AA33}� �������{FFFFFF}" : "{AA3333}���{FFFFFF}";
	lic_boat = (P[playerid][p_lic_boat] == 1) ? "{33AA33}� �������{FFFFFF}" : "{AA3333}���{FFFFFF}";
	lic_moto = (P[playerid][p_lic_moto] == 1) ? "{33AA33}� �������{FFFFFF}" : "{AA3333}���{FFFFFF}";
	lic_weapon = (P[playerid][p_lic_weapon] == 1) ? "{33AA33}� �������{FFFFFF}" : "{AA3333}���{FFFFFF}";
	lic_freight = (P[playerid][p_lic_freight] == 1) ? "{33AA33}� �������{FFFFFF}" : "{AA3333}���{FFFFFF}";
	lic_helicopter = (P[playerid][p_lic_helicopter] == 1) ? "{33AA33}� �������{FFFFFF}" : "{AA3333}���{FFFFFF}";
	format(output, sizeof(output),
		"{FFFFFF}������������ �����:\t\t\t\t\t%s\n\
		�������� ������������� ��������:\t\t\t%s\n\
		�������� �� ������ ���������:\t\t\t%s\n\
		�������� �� �������� ����� �����:\t\t\t%s\n\
		�������� �� ������:\t\t\t\t\t%s\n\
		�������� �� �����-���������:\t\t\t\t%s\n\
		�������� �� ������������� ���������:\t\t%s",
		lic_car,lic_aircraft,lic_boat,lic_moto,lic_weapon,lic_freight,lic_helicopter);
	Dialog_Message(targetid, "��������", output, "��");
	// P[playerid][_p_dialog] = true;
}
