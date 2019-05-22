CMD:ban(playerid, params[]){
	if(P[playerid][_p_in_game] == false) return 1;
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

		va_SendClientMessageToAll(-1, "Администратор %s забанил %s на %i Час{FFCC66}(ов){FFFFFF}. Причина: %s", P[playerid][p_name], P[target][p_name], strval(time_string), reason);
	} else if(strfind(time_string, "d", true) != -1) {
		time = gettime() + (strval(time_string)*86400);

		va_SendClientMessageToAll(-1, "Администратор %s забанил %s на %i Д{FFCC66}(ней){FFFFFF}ень. Причина: %s", P[playerid][p_name], P[target][p_name], strval(time_string), reason);
	} else if(strfind(time_string, "m", true) != -1) {
		time = gettime() + (strval(time_string)*2629743);

		va_SendClientMessageToAll(-1, "Администратор %s забанил %s на %i Месяц{FFCC66}(а){FFFFFF}. Причина: %s", P[playerid][p_name], P[target][p_name], strval(time_string), reason);
	}
	new query[256];

	mysql_format(g_MySQL_DB, query, sizeof(query), "INSERT INTO `bans` (Name, Admin_Name, Reg_IP, Last_IP, Unix_Time_Start, Unix_Time_End, Reason) VALUES ('%e', '%e', '%s', '%s', '%i', '%i', '%e')", P[target][p_name], P[playerid][p_name], P[target][p_reg_ip], P[target][p_last_ip], gettime(), time, reason);
	mysql_pquery(g_MySQL_DB, query);

	Kick(target);
	return true;
}
CMD:unban(playerid, params[]) {
	if(P[playerid][_p_in_game] == false) return 1;
	if (P[playerid][p_access] < 1) return true;

	new target[MAX_PLAYER_NAME];
	if(sscanf(params,"s[24]", target)) return SendClientMessage(playerid, 0xB22222FF, "[Справка]: {FFFFFF}Используйте /unban [Имя пользователя]");

    new query[64+1];
	mysql_format(g_MySQL_DB, query, sizeof(query), "SELECT * FROM `bans` WHERE `Name` = '%e'", target);
	mysql_pquery(g_MySQL_DB, query, "OnMySQL_DeleteBanName", "is", playerid, target);
	return 1;
}
CMD:unbanip(playerid, params[]) {
	if(P[playerid][_p_in_game] == false) return 1;
	if (P[playerid][p_access] < 1) return true;

	new IP[46];
	if(sscanf(params,"s[24]", IP)) return SendClientMessage(playerid, 0xB22222FF, "[Справка]: {FFFFFF}Используйте /unban [IP]");

    new query[86+1];
	mysql_format(g_MySQL_DB, query, sizeof(query), "SELECT * FROM `bans` WHERE `Name` = '%s'", IP);
	mysql_pquery(g_MySQL_DB, query, "OnMySQL_DeleteBanIP", "is", playerid, IP);
	return 1;
}
CMD:offban(playerid, params[]) {
	if(P[playerid][_p_in_game] == false) return 1;
	if (P[playerid][p_access] < 1) return true;
	new target[MAX_PLAYER_NAME],
		time_string[10],
		reason[64],
		time;

	if(sscanf(params, "s[24]s[10]s[32]", target, time_string, reason)){
        SendClientMessage(playerid, 0xB22222FF, "[Справка]: {FFFFFF}Используйте /offban [Имя пользователя] [Время (число[h/d/m])] [Причина]");
		return 1;
	}
	if (IsNumeric(target))
		return SendClientMessage(playerid, 0xB22222FF, "[Справка]: {FFFFFF}Неправильный формат.");

	if(strfind(time_string, "h", true) != -1) {
		time = gettime() + (strval(time_string)*3600);
	} else if(strfind(time_string, "d", true) != -1) {
		time = gettime() + (strval(time_string)*86400);
	} else if(strfind(time_string, "m", true) != -1) {
		time = gettime() + (strval(time_string)*2629743);
	} else return SendClientMessage(playerid, 0xB22222FF, "[Справка]: {FFFFFF}Неправильный формат.");

	new Name_[MAX_PLAYER_NAME];
	foreach (new i:Player) {
		if(!IsPlayerConnected(i)) continue;
    	GetPlayerName(playerid, Name_, sizeof(Name_));
        if(!strcmp(Name_, target, false)) return SendClientMessage(playerid, 0xB22222FF, "[Справка]: {FFFFFF}Этот игрок находится в игре. Вы не можете забанить его сейчас.");

		new query[156];
		mysql_format(g_MySQL_DB, query, sizeof(query), "SELECT *, (SELECT `ID` FROM `bans` WHERE `Name` = '%e') as banid FROM `accounts` WHERE `Name` = '%e'", target, target);
		mysql_pquery(g_MySQL_DB, query, "OnMySQL_OffBan", "isiss", playerid, target, time, reason, time_string);
		return 1;
	}
	return true;
}
CMD:baninfo(playerid, params[]) {
	if(P[playerid][_p_in_game] == false) return 1;
	if(P[playerid][p_access] < 1) return true;
	new target[MAX_PLAYER_NAME];
	if(sscanf(params, "s[24]", target)) return SendClientMessage(playerid, 0xB22222FF, "[Справка]: {FFFFFF}Используйте /baninfo [ID бана или Имя пользователя]");

	if (IsNumeric(target)) {
		strval(target);
	}

	new query[86+1];
	mysql_format(g_MySQL_DB, query, sizeof(query), "SELECT * FROM `bans` WHERE `Name` = '%e' OR `ID` = '%i'", target, strval(target));
	mysql_pquery(g_MySQL_DB, query, "OnMySQL_GetBanInfo", "isi", playerid, target, strval(target));
	return true;
}
CMD:id(playerid, params[]){
	if(P[playerid][_p_in_game] == false) return 1; //Concept from GTO
    new ids[5];
	if(sscanf(params, "?<MATCH_NAME_PARTIAL=1>u[5]", ids)) return SendClientMessage(playerid, 0xB22222FF,"[Справка]: {FFFFFF}Используйте /id [ID игрока/Часть Ника]");
	new i, insert_pos, string[265];
	SendClientMessage(playerid, 0xB22222FF,"[Результаты]:");
	while (ids[i] != INVALID_PLAYER_ID)
	{
        if (ids[i] == cellmin)
		{
            SendClientMessage(playerid,0xFFCC66FF,"* {FFFFFF}и другие...");
            break;
        }
		GetPlayerName(ids[i], string, sizeof(string));
		insert_pos = strfind(string, params, true);
		if (insert_pos != -1) {
			strins(string, "{FFFFFF}", strlen(params) + insert_pos);
			strins(string, "{FF8888}", insert_pos);
		}
		va_SendClientMessage(playerid, -1,"%s [%d] [№%i]",string, ids[i],P[i][p_uid]);
		i++;
	}
	if (i == 0) {
		SendClientMessage(playerid, 0xB22222FF,"[Справка]: {FFFFFF}Никто не найден");
	}
	return true;
}
CMD:teleport(playerid, params[]){
	if(P[playerid][_p_in_game] == false) return 1; //concept from GTO
	if(P[playerid][p_access] < 1) return true;
	new subcmd[7], subparams[64];
	if (sscanf(params, "s[7]s[64]", subcmd, subparams)){
		SendClientMessage(playerid, 0xB22222FF,"[Справка]: {FFFFFF}Используйте /t{FFCC66}[ele]{FFFFFF}p{FFCC66}[ort]{FFFFFF} to [ID игрока/Часть Ника]");
		SendClientMessage(playerid, 0xB22222FF,"[Справка]: {FFFFFF}Используйте /t{FFCC66}[ele]{FFFFFF}p{FFCC66}[ort]{FFFFFF} here [ID игрока/Часть Ника]");
		SendClientMessage(playerid, 0xB22222FF,"[Справка]: {FFFFFF}Используйте /t{FFCC66}[ele]{FFFFFF}p{FFCC66}[ort]{FFFFFF} coord <x> <y> <z> <интерьер> <мир>");
		return 1;
	}
	new targetid = INVALID_PLAYER_ID;

	if(sscanf(subparams, "u", targetid)) return SendClientMessage(playerid, 0xB22222FF,"[Справка]: {FFFFFF}Игрок не найден");
	new Float:p_pos_x,            Float:t_pos_x,
		Float:p_pos_y,            Float:t_pos_y,
		Float:p_pos_z,            Float:t_pos_z,
		Float:p_pos_a,            Float:t_pos_a,
		p_interior,               t_interior,
		p_world,                  t_world;

	GetPlayerPos(playerid, p_pos_x, p_pos_y, p_pos_z);
	GetPlayerFacingAngle(playerid, p_pos_a);
	p_interior = GetPlayerInterior(playerid);
	p_world = GetPlayerVirtualWorld(playerid);

	if (targetid != -1) {
		GetPlayerPos(targetid, t_pos_x, t_pos_y, t_pos_z);
		GetPlayerFacingAngle(targetid, t_pos_a);
		t_interior = GetPlayerInterior(targetid);
		t_world = GetPlayerVirtualWorld(targetid);
	}
	if(strcmp(subcmd, "to", true) == 0) {
		if (targetid == INVALID_PLAYER_ID || targetid == -1) return SendClientMessage(playerid, 0xB22222FF,"[Справка]: {FFFFFF}Игрок не найден");
		TeleportPlayerToPos(playerid,t_pos_x + random(2) - random(4), t_pos_y + random(2) - random(4), t_pos_z,t_interior, t_world);
		Message_ToAdmins(0xAFAFAFFF, "Администратор %s[%d] телепортировался к %s[%d].", Name(playerid), playerid, Name(targetid), targetid);
	}
	else if(strcmp(subcmd, "here", true) == 0) {
		if (targetid == INVALID_PLAYER_ID) return SendClientMessage(playerid, 0xB22222FF,"[Справка]: {FFFFFF}Игрок не найден");
		TeleportPlayerToPos(targetid, p_pos_x + random(2) - random(4), p_pos_y + random(2) - random(4), p_pos_z, p_interior, p_world);
		Message_ToAdmins(0xAFAFAFFF, "Администратор %s[%d] телепортировал к себе %s[%d].",Name(playerid),playerid,Name(targetid),targetid);
	}
	else if(strcmp(subcmd, "coord", true) == 0) {
		if(sscanf(subparams, "p<,>fffI(0)I(0)", t_pos_x, t_pos_y, t_pos_z, t_interior, t_world)) return SendClientMessage(playerid, 0xB22222FF, "[Справка]: {FFFFFF}/t{FFCC66}[ele]{FFFFFF}p{FFCC66}[ort]{FFFFFF} coord <x> <y> <z> <интерьер> <мир>");
		TeleportPlayerToPos(playerid, t_pos_x, t_pos_y, t_pos_z, t_interior, t_world);
	}
	return true;
}
alias:teleport("tp");
CMD:irc(playerid, params[]) {
	if(P[playerid][_p_in_game] == false) return 1;
	new subcmd[7], subparams[64];
	if (sscanf(params, "s[8]S(-1)[64]", subcmd, subparams)){
		SendClientMessage(playerid, 0xB22222FF,"[Справка]: {FFFFFF}Используйте {FFCC66}/irc join [Номер комнаты]{FFFFFF} чтобы войти в IRC комнату.");
		SendClientMessage(playerid, 0xB22222FF,"[Справка]: {FFFFFF}Используйте {FFCC66}/irc chat [Текст]{FFFFFF} чтобы войти в IRC комнату.");
		SendClientMessage(playerid, 0xB22222FF,"[Справка]: {FFFFFF}Используйте {FFCC66}/irc members{FFFFFF} чтобы посмотреть список участников в комнате.");
		SendClientMessage(playerid, 0xB22222FF,"[Справка]: {FFFFFF}Используйте {FFCC66}/irc leave{FFFFFF} чтобы выйти из IRC комнаты.");
		return 1;
	}
	new targetid,
		stringChat[64];

	if(strcmp(subcmd, "join", true) == 0) {
		if(sscanf(subparams, "i", targetid)) return SendClientMessage(playerid, 0xB22222FF,"[Справка]: {FFFFFF}Неправильный номер.");
		if (targetid == INVALID_PLAYER_ID || targetid < 1 || targetid > 999999) return SendClientMessage(playerid, 0xB22222FF,"[Справка]: {FFFFFF}Вы можете подключаться только к комнатам с 1 до 999999 ID.");
		va_SendClientMessage(playerid, 0xB22222FF,"[Справка]: {FFFFFF}Вы подключились к %i IRC каналу.", targetid);
		SetPVarInt(playerid, "IRC", targetid);
		Message_ToIRC(playerid, "[IRC] %s подключился к IRC каналу.", Name(playerid));
	}
	else if(strcmp(subcmd, "chat", true) == 0) {
		if(!GetPVarInt(playerid, "IRC") || GetPVarInt(playerid, "IRC") == -1) return SendClientMessage(playerid, 0xB22222FF,"[Справка]: {FFFFFF}Вы не можете отправлять сообщения в IRC канал, так как ещё не подключены к одному из них.");
		if(strcmp(subparams, "-1") == 0) return SendClientMessage(playerid, 0xB22222FF, "[Справка]: {FFFFFF}/irc chat [текст]");
		if(sscanf(subparams, "s[64]", stringChat)) return SendClientMessage(playerid, 0xB22222FF, "[Справка]: {FFFFFF}/irc chat [текст]");
		Message_ToIRC(playerid, "[IRC] %s: %s", Name(playerid), stringChat);
	}
	else if(strcmp(subcmd, "members", true) == 0) {
		if(!GetPVarInt(playerid, "IRC") || GetPVarInt(playerid, "IRC") == -1) return SendClientMessage(playerid, 0xB22222FF,"[Справка]: {FFFFFF}Вы не можете посмотреть участников IRC канала, так как ещё не подключены к одному из них.");
		IRCMembers(playerid);
	}
	else if(strcmp(subcmd, "leave", true) == 0) {
		if(!GetPVarInt(playerid, "IRC") || GetPVarInt(playerid, "IRC") == -1) return SendClientMessage(playerid, 0xB22222FF,"[Справка]: {FFFFFF}Вы не можете выйти из IRC канала, так как ещё не подключены к одному из них.");
		va_SendClientMessage(playerid, 0xB22222FF,"[Справка]: {FFFFFF}Вы вышли из %i IRC канала.", GetPVarInt(playerid, "IRC"));
		Message_ToIRC(playerid, "[IRC] %s вышел из IRC канала.", Name(playerid));
		SetPVarInt(playerid, "IRC", -1);
	}
	return true;
}
