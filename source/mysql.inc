forward OnMySQL_SelectAccount(playerid);
public OnMySQL_SelectAccount(playerid) {
	PlayerPlaySound(playerid, 1097, 0.0, 0.0, 10.0);
	new rand = random(sizeof(CamerasRand));
	SetPlayerCameraPos(playerid, CamerasRand[rand][0], CamerasRand[rand][1], CamerasRand[rand][2]);
	SetPlayerCameraLookAt(playerid,CamerasRand[rand][3], CamerasRand[rand][4], CamerasRand[rand][5]);

	switch(orm_errno(P[playerid][_p_ormid])) {
	    case ERROR_OK: {
			new query[250];
			mysql_format(g_MySQL_DB, query, sizeof(query), "SELECT * FROM `bans` WHERE `Name` = '%e' OR `Reg_IP`='%s' OR `Last_IP`='%s'", P[playerid][p_name], P[playerid][p_reg_ip], P[playerid][p_last_ip]);
			mysql_tquery(g_MySQL_DB, query, "OnMySQL_CheckBans", "iss", playerid, P[playerid][p_reg_ip], P[playerid][p_last_ip]);
		}
	    case ERROR_NO_DATA: Dialog_Show(playerid, Dialog:d_user_register);
	}
	orm_setkey(P[playerid][_p_ormid], "UID");
}
forward OnMySQL_InsertAccount(playerid);
public OnMySQL_InsertAccount(playerid) {
	orm_load(P[playerid][_p_ormid]);
	P[playerid][_p_in_game] = true;
}

forward OnMySQL_CheckBans(playerid, reg_ip[46], last_ip[46]);
public OnMySQL_CheckBans(playerid, reg_ip[46], last_ip[46]) {
	if(cache_num_rows() == 0) {
		Dialog_Show(playerid, Dialog:d_user_login);
	} else {
		new b_ID,
			b_Name[MAX_PLAYER_NAME],
			b_Admin_Name[MAX_PLAYER_NAME],
			b_Reg_IP[46],
			b_Last_IP[46],
			b_Unix_Time_Start,
			b_Unix_Time_End,
			b_Reason[64];

		cache_get_value_name_int(0, "ID", b_ID);
		cache_get_value_name(0, "Name", b_Name);
		cache_get_value_name(0, "Admin_Name", b_Admin_Name);
		cache_get_value_name(0, "Reg_IP", b_Reg_IP);
		cache_get_value_name(0, "Last_IP", b_Last_IP);
		cache_get_value_name_int(0, "Unix_Time_Start", b_Unix_Time_Start);
		cache_get_value_name_int(0, "Unix_Time_End", b_Unix_Time_End);
		cache_get_value_name(0, "Reason", b_Reason);

		new start_year, start_month, start_day, start_hour, start_minute, start_second;
		gmtime(b_Unix_Time_Start, start_year, start_month, start_day, start_hour, start_minute, start_second);

		new end_year, end_month, end_day, end_hour, end_minute, end_second;
		gmtime(b_Unix_Time_End, end_year, end_month, end_day, end_hour, end_minute, end_second);

		if (b_Unix_Time_End < gettime()) {
			new query[200];
			mysql_format(g_MySQL_DB, query, sizeof(query), "DELETE FROM `bans` WHERE `Name` = '%e' OR `Reg_IP`='%s' OR `Last_IP`='%s'", b_Name, b_Reg_IP, b_Last_IP);
			mysql_tquery(g_MySQL_DB, query);

			Dialog_Show(playerid, Dialog:d_user_login);
		} else {
			new string[666];
			format(string, sizeof(string),
				"{FFFFFF}\t\t�� �������� �� ����� �������.\n\n��� �������: \t\t\t\t{FFCC66}%s (ID ����: %i){FFFFFF}\n��� ��������������: \t\t\t{FFCC66}%s{FFFFFF}\n\
				����� ����: \t\t\t\t{FFCC66}%02d:%02d:%02d %02d.%02d.%04d{FFFFFF}\n���� ��������� ����� ����: \t\t{FFCC66}%02d:%02d:%02d %02d.%02d.%04d{FFFFFF}\n\n�������: \t\t\t\t{FFCC66}%s{FFFFFF}",
				b_Name, b_ID, b_Admin_Name,
				start_hour, start_minute, start_second, start_day, start_month, start_year,
				end_hour, end_minute, end_second, end_day, end_month, end_year,
				b_Reason);
			Dialog_Message(playerid, "�� ��������.", string, "OK");
			Kick(playerid);
		}
	}
}
forward OnMySQL_DeleteBanName(playerid, Name_[24]);
public OnMySQL_DeleteBanName(playerid, Name_[24]) {
	if(cache_num_rows() == 0)
		return SendClientMessage(playerid, 0xB22222FF, "[�������]: {FFFFFF}���� ������������/IP �� �������.");

	new query[64+1];
	mysql_format(g_MySQL_DB, query, sizeof(query), "DELETE FROM `bans` WHERE `Name` = '%e'", Name_);
	mysql_tquery(g_MySQL_DB, query);

	Message_ToAdmins(0xAA3333AA, "MESSAGE_ADMIN_UNBAN",P[playerid][p_name], Name_);
	return true;
}
forward OnMySQL_DeleteBanIP(playerid, IP[46]);
public OnMySQL_DeleteBanIP(playerid, IP[46]) {
	if(cache_num_rows() == 0)
		return SendClientMessage(playerid, 0xB22222FF, "[�������]: {FFFFFF}���� ������������/IP �� �������.");

	new query[64+1];
	mysql_format(g_MySQL_DB, query, sizeof(query), "DELETE FROM `bans` WHERE `Reg_IP` = '%s' OR `Last_IP` = `%s`", IP, IP);
	mysql_tquery(g_MySQL_DB, query);

	Message_ToAdmins(0xAA3333AA, "MESSAGE_ADMIN_UNBAN_IP",P[playerid][p_name], IP);
	return true;
}
forward OnMySQL_OffBan(playerid, account[MAX_PLAYER_NAME], time, reason[64], time_string[10]);
public OnMySQL_OffBan(playerid, account[MAX_PLAYER_NAME], time, reason[64], time_string[10]) {
	new b_Name[MAX_PLAYER_NAME],
		b_Reg_IP[46],
		b_Last_IP[46],
		b_access;

	if(cache_num_rows() == 0) {
		new string[73+24+1];
		format(string, sizeof(string), "[�������]: {FFFFFF}�� ���� ����� ������� {FFCC66}%s{FFFFFF} � ��.", account);
		SendClientMessage(playerid, 0xB22222FF, string);
		return true;
	} else {
		cache_get_value_name(0, "Name", b_Name);
		cache_get_value_name(0, "Reg_IP", b_Reg_IP);
		cache_get_value_name(0, "Last_IP", b_Last_IP);
		cache_get_value_name_int(0, "Access", b_access);

		if(P[playerid][p_access] < b_access) return Kick(playerid);
	}
	new b_id;

	if(cache_get_value_name_int(0, "banid", b_id) != 0) {
		new string[200];
		format(string, sizeof(string), "[�������]: {FFCC66}%s{FFFFFF} ��� �������.", account);
		SendClientMessage(playerid, 0xB22222FF, string);
	}

	new query[256];
	mysql_format(g_MySQL_DB, query, sizeof(query), "INSERT INTO `bans` (Name, Admin_Name, Reg_IP, Last_IP, Unix_Time_Start, Unix_Time_End, Reason) VALUES ('%e', '%e', '%s', '%s', '%i', '%i', '%s')",
		account, P[playerid][p_name], b_Reg_IP, b_Last_IP, gettime(), time, reason);
	mysql_tquery(g_MySQL_DB, query);
	new string[30];
	if(strfind(time_string, "h", true) != -1) {
		format(string, sizeof(string), "%i ���{FFCC66}(��){FFFFFF}", strval(time_string));
	} else if(strfind(time_string, "d", true) != -1) {
		format(string, sizeof(string), "%i �{FFCC66}(���){FFFFFF}���", strval(time_string));
	} else if(strfind(time_string, "m", true) != -1) {
		format(string, sizeof(string), "%i �����{FFCC66}(�){FFFFFF}", strval(time_string));
	}
	Message_ToAdmins(0xAA3333AA, "MESSAGE_ADMIN_OFFBAN", P[playerid][p_name], account, string, reason);
	return true;
}
forward OnMySQL_GetBanInfo(playerid, name[MAX_PLAYER_NAME], id);
public OnMySQL_GetBanInfo(playerid, name[MAX_PLAYER_NAME], id) {
	if(cache_num_rows() == 0)
		return SendClientMessage(playerid, 0xB22222FF, "[�������]: {FFFFFF}�� ���� ����� ������ ������� � ��.");
	else {
		new b_ID,
			b_Name[MAX_PLAYER_NAME],
			b_Admin_Name[MAX_PLAYER_NAME],
			b_Reg_IP[46],
			b_Last_IP[46],
			b_Unix_Time_Start,
			b_Unix_Time_End,
			b_Reason[64];

		cache_get_value_name_int(0, "ID", b_ID);
		cache_get_value_name(0, "Name", b_Name);
		cache_get_value_name(0, "Admin_Name", b_Admin_Name);
		cache_get_value_name(0, "Reg_IP", b_Reg_IP);
		cache_get_value_name(0, "Last_IP", b_Last_IP);
		cache_get_value_name_int(0, "Unix_Time_Start", b_Unix_Time_Start);
		cache_get_value_name_int(0, "Unix_Time_End", b_Unix_Time_End);
		cache_get_value_name(0, "Reason", b_Reason);

		new start_year, start_month, start_day, start_hour, start_minute, start_second;
		gmtime(b_Unix_Time_Start, start_year, start_month, start_day, start_hour, start_minute, start_second);

		new end_year, end_month, end_day, end_hour, end_minute, end_second;
		gmtime(b_Unix_Time_End, end_year, end_month, end_day, end_hour, end_minute, end_second);

		new string[300];
		format(string, sizeof(string), "{FFFFFF}\t\t���������� � ���� ������.\n\n�������: \t\t\t\t{FFCC66}%s (ID ����: %i){FFFFFF}\n��� ��������������: \t\t\t{FFCC66}%s{FFFFFF}\n\
		����� ����: \t\t\t\t{FFCC66}%02d:%02d:%02d %02d.%02d.%04d{FFFFFF}\n���� ��������� ����� ����: \t\t{FFCC66}%02d:%02d:%02d %02d.%02d.%04d{FFFFFF}\n\n�������: \t\t\t\t{FFCC66}%s{FFFFFF}",
		b_Name, b_ID, b_Admin_Name,
		start_hour, start_minute, start_second, start_day, start_month, start_year,
		end_hour, end_minute, end_second, end_day, end_month, end_year,
		b_Reason);

		Dialog_Message(playerid, " ", string, "OK");
	}
	return true;
}
forward OnMySQL_GangZones();
public OnMySQL_GangZones() {
	if(cache_num_rows() == 0)
		return print("[OnMySQL_GangZones] � ���� ������ ��� GangZones!");
	if (cache_num_rows() != sizeof(GZ))
		return printf("[OnMySQL_GangZones] � ���� ������ ������ ��� [%d], ��� � ������� GZ [%d]", cache_num_rows(), sizeof(GZ));

	new TotalGangZones;
	for(new x; x < sizeof(GZ); x++) {
		GZ[x][_gz_ormid] = orm_create("gangzones");

		orm_addvar_int(GZ[x][_gz_ormid], GZ[x][gz_id], "ID");
	    orm_setkey(GZ[x][_gz_ormid], "ID");
	    orm_addvar_float(GZ[x][_gz_ormid], GZ[x][gz_min_pos_x], "MinX");
		orm_addvar_float(GZ[x][_gz_ormid], GZ[x][gz_min_pos_y], "MinY");
		orm_addvar_float(GZ[x][_gz_ormid], GZ[x][gz_max_pos_x], "MaxX");
		orm_addvar_float(GZ[x][_gz_ormid], GZ[x][gz_max_pos_y], "MaxY");
	    orm_addvar_int(GZ[x][_gz_ormid], GZ[x][gz_team],"Team");

	    orm_apply_cache(GZ[x][_gz_ormid], x);

		GZ[x][_gz_local] = CreateZone(GZ[x][gz_min_pos_x], GZ[x][gz_min_pos_y], GZ[x][gz_max_pos_x], GZ[x][gz_max_pos_y]);
		CreateZoneBorders(GZ[x][_gz_local]);
		TotalGangZones++;
	}
	printf("���������� ���� ���:%i      [������������ ��������: %d ms]",TotalGangZones,cache_get_query_exec_time(MILLISECONDS));
	return true;
}
