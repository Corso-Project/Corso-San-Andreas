CMD:ban(playerid, params[]){
	if (P[playerid][p_access] < 1) return true;
	new
		target,
		time_string[10],
		time,
		reason[64];

	if (sscanf(params, "us[10]s[32]", target, time_string, reason)){
		SendClientMessage(playerid, 0xB22222FF, "[Справка]: {FFFFFF}Используйте /ban [ID] [время (число[h/d/m])] [причина]");
		SendClientMessage(playerid, 0xB22222FF, "[Пример]: {FFFFFF}/ban 0 5d Тест - выдаёт бан игроку с ID 0 на 5 дней.");
		return 1;
	}

	if (strfind(time_string, "h", true) != -1) {
		time = gettime() + (strval(time_string)*3600);

		foreach(new i:Player) {
			new banString[47+24+24+30+64+1];
			// format(string, sizeof(string), "%i %s",strval(time_string), Lang_ReturnOnlyText(i, "HOURS"));
			// Lang_SendText(i, "MESSAGE_ALL_BAN", P[playerid][p_name], P[target][p_name], string, reason);
            format(banString, sizeof(banString), "Администратор %s забанил %s на %i Час{FFCC66}(ов){FFFFFF}. Причина: %s", P[playerid][p_name], P[target][p_name], strval(time_string), reason);
            SendClientMessageToAll(-1, banString);
		}
	} else if(strfind(time_string, "d", true) != -1) {
		time = gettime() + (strval(time_string)*86400);

		foreach(new i:Player) {
			new banString[47+24+24+30+64+1];
			// format(string, sizeof(string), "%i %s",strval(time_string), Lang_ReturnOnlyText(i, "DAYS"));
			// Lang_SendText(i, "MESSAGE_ALL_BAN", P[playerid][p_name], P[target][p_name], string, reason);
            format(banString, sizeof(banString), "Администратор %s забанил %s на %i Д{FFCC66}(ней){FFFFFF}ень. Причина: %s", P[playerid][p_name], P[target][p_name], strval(time_string), reason);
            SendClientMessageToAll(-1, banString);
		}
	} else if(strfind(time_string, "m", true) != -1) {
		time = gettime() + (strval(time_string)*2629743);

		foreach(new i:Player) {
            new banString[47+24+24+30+64+1];
			// format(string, sizeof(string), "%i %s",strval(time_string), Lang_ReturnOnlyText(i, "MONTHS"));
			// Lang_SendText(i, "MESSAGE_ALL_BAN", P[playerid][p_name], P[target][p_name], string, reason);
            format(banString, sizeof(banString), "Администратор %s забанил %s на %i Месяц{FFCC66}(а){FFFFFF}. Причина: %s", P[playerid][p_name], P[target][p_name], strval(time_string), reason);
            SendClientMessageToAll(-1, banString);
		}
	}
	new query[256];

	mysql_format(g_MySQL_DB, query, sizeof(query), "INSERT INTO `bans` (Name, Admin_Name, Reg_IP, Last_IP, Unix_Time_Start, Unix_Time_End, Reason) VALUES ('%e', '%e', '%s', '%s', '%i', '%i', '%e')", P[target][p_name], P[playerid][p_name], P[target][p_reg_ip], P[target][p_last_ip], gettime(), time, reason);
	mysql_tquery(g_MySQL_DB, query);

	Kick(target);
	return true;
}
CMD:unban(playerid, params[])
{
	if (P[playerid][p_access] < 1) return true;

	new target[MAX_PLAYER_NAME];
	if(sscanf(params,"s[24]", target)) return SendClientMessage(playerid, 0xB22222FF, "[Справка]: {FFFFFF}Используйте /unban [Имя пользователя]");// Lang_SendText(playerid, "ADMIN_CMDS_UNBAN_HELP");

    new query[64+1];
	mysql_format(g_MySQL_DB, query, sizeof(query), "SELECT * FROM `bans` WHERE `Name` = '%e'", target);
	mysql_tquery(g_MySQL_DB, query, "OnMySQL_DeleteBanName", "is", playerid, target);
	return 1;
}
CMD:unbanip(playerid, params[])
{
	if (P[playerid][p_access] < 1) return true;

	new IP[46];
	if(sscanf(params,"s[24]", IP)) return SendClientMessage(playerid, 0xB22222FF, "[Справка]: {FFFFFF}Используйте /unban [IP]");// Lang_SendText(playerid, "ADMIN_CMDS_UNBAN_HELP");

    new query[86+1];
	mysql_format(g_MySQL_DB, query, sizeof(query), "SELECT * FROM `bans` WHERE `Name` = '%s'", IP);
	mysql_tquery(g_MySQL_DB, query, "OnMySQL_DeleteBanIP", "is", playerid, IP);
	return 1;
}
CMD:offban(playerid, params[]){
	if (P[playerid][p_access] < 1) return true;
	new target[MAX_PLAYER_NAME],
		time_string[10],
		reason[64],
		time;

	if(sscanf(params, "s[24]s[10]s[32]", target, time_string, reason)){
		// Lang_SendText(playerid, "ADMIN_CMDS_OFFBAN_HELP");
        SendClientMessage(playerid, 0xB22222FF, "[Справка]: {FFFFFF}Используйте /offban [Имя пользователя] [Время (число[h/d/m])] [Причина]");
		return 1;
	}
	if (IsNumeric(target))
		return SendClientMessage(playerid, 0xB22222FF, "[Справка]: {FFFFFF}Неправильный формат."); // Lang_SendText(playerid, "ADMIN_CMDS_OFFBAN_ERROR");

	if(strfind(time_string, "h", true) != -1) {
		time = gettime() + (strval(time_string)*3600);
	} else if(strfind(time_string, "d", true) != -1) {
		time = gettime() + (strval(time_string)*86400);
	} else if(strfind(time_string, "m", true) != -1) {
		time = gettime() + (strval(time_string)*2629743);
	} else return SendClientMessage(playerid, 0xB22222FF, "[Справка]: {FFFFFF}Неправильный формат.");  // Lang_SendText(playerid, "ADMIN_CMDS_OFFBAN_ERROR");

	new Name_[MAX_PLAYER_NAME];
	foreach (new i:Player) {
		if(!IsPlayerConnected(i)) continue;
    	GetPlayerName(playerid, Name_, sizeof(Name_));
        if(!strcmp(Name_, target, false)) return SendClientMessage(playerid, 0xB22222FF, "[Справка]: {FFFFFF}Этот игрок находится в игре. Вы не можете забанить его сейчас.");// Lang_SendText(playerid, "ADMIN_CMDS_OFFBAN_P_IN_GAME");

		new query[156];
		mysql_format(g_MySQL_DB, query, sizeof(query), "SELECT *, (SELECT `ID` FROM `bans` WHERE `Name` = '%e') as banid FROM `accounts` WHERE `Name` = '%e'", target, target);
		mysql_tquery(g_MySQL_DB, query, "OnMySQL_OffBan", "isiss", playerid, target, time, reason, time_string);
		return 1;
	}
	return true;
}
CMD:baninfo(playerid, params[]){
	if(P[playerid][p_access] < 1) return true;
	new target[MAX_PLAYER_NAME];
	if(sscanf(params, "s[24]", target)) return SendClientMessage(playerid, 0xB22222FF, "[Справка]: {FFFFFF}Используйте /baninfo [ID бана или Имя пользователя]");

	if (IsNumeric(target)) {
		strval(target);
	}

	new query[86+1];
	mysql_format(g_MySQL_DB, query, sizeof(query), "SELECT * FROM `bans` WHERE `Name` = '%e' OR `ID` = '%i'", target, strval(target));
	mysql_tquery(g_MySQL_DB, query, "OnMySQL_GetBanInfo", "isi", playerid, target, strval(target));
	return true;
}
