DialogCreate:d_user_login(playerid) {
    Dialog_Open(playerid, Dialog:d_user_login, DIALOG_STYLE_INPUT, "Войти","\\c{FFFFFF}Добро пожаловать на {B3F9B0}"SERVER_NAME"{FFFFFF}\n\\cДанный аккаунт уже зарегистрирован, введите пароль:\n\\c{b3f9b0}Если Вы утратили доступ к аккаунту, нажмите кнопку E-Mail","Войти","E-Mail");
}
DialogResponse:d_user_login(playerid, response, listitem, inputtext[]) {
    if (!response) {
		SendClientMessage(playerid, -1, "E-Mail.");
		return 1;
	}
    if(!strlen(inputtext)) return Dialog_Show(playerid, Dialog:d_user_login);
    if(strlen(inputtext) != strlen(P[playerid][p_password])) {
		if(strcmp(P[playerid][p_password], inputtext, false) != 0) return SendClientMessage(playerid, -1, "Неправильынй пароль.");
	}
    P[playerid][_p_in_game] = true;
    GetPlayerIp(playerid, P[playerid][p_last_ip], 46);
	TogglePlayerSpectating(playerid, 0);

    sscanf(P[playerid][p_settings], "p<,>i", P[playerid][p_saveLastPos]);

    if (P[playerid][p_access] > 1) {
        new string[37+1+1];
        format(string, sizeof(string), "Вы вошли как администратор %i уровня. ->", P[playerid][p_access]);
        SendClientMessage(playerid, -1, string);
    }
    orm_update(P[playerid][_p_ormid]);
    return true;
}

DialogCreate:d_user_register(playerid) {
    Dialog_Open(playerid, Dialog:d_user_register, DIALOG_STYLE_INPUT,"Регистрация","\\c{FFFFFF}Добро пожаловать на сервер {B3F9B0}"SERVER_NAME"\n\\c{FFFFFF}Вы не зарегистрированы на сервере.\n\\c{b3f9b0}Для регистрации придумайте себе пароль:","Готово", "Выход");
}
DialogResponse:d_user_register(playerid, response, listitem, inputtext[]) {
    if (!response) Kick(playerid);
	if (strlen(inputtext) < 5 || strlen(inputtext) > 18) return Dialog_Show(playerid, Dialog:d_user_register);
	for (new i; i < strlen(inputtext); i++) switch(inputtext[i]) {
		case '0'..'9': continue;
		case 'a'..'z': continue;
		case 'A'..'Z': continue;
		default: return Dialog_Show(playerid, Dialog:d_user_register);
	}
	format(P[playerid][p_password], 18, inputtext);
	GetPlayerIp(playerid, P[playerid][p_reg_ip], 46);
    GetPlayerIp(playerid, P[playerid][p_last_ip], 46);

    sscanf(P[playerid][p_settings], "p<,>i", P[playerid][p_saveLastPos]);
    P[playerid][p_saveLastPos] = 1;
    format(P[playerid][p_settings], 10, "%i", P[playerid][p_saveLastPos]);

    Dialog_Show(playerid, Dialog:d_user_select_gender);
	return true;
}

DialogCreate:d_user_select_gender(playerid) {
    Dialog_Open(playerid, Dialog:d_user_select_gender, DIALOG_STYLE_MSGBOX, "Выберите пол персонажа"," ","Мужской","Женский");
}
DialogResponse:d_user_select_gender(playerid, response, listitem, inputtext[]) {
    if(!response) return SetPVarInt(playerid, "Gender", 2), TogglePlayerSpectating(playerid, 0); //female
    SetPVarInt(playerid, "Gender", 1); // male
    TogglePlayerSpectating(playerid, 0);
    return true;
}

DialogCreate:d_user_menu(playerid) {
    Dialog_Open(playerid, Dialog:d_user_menu, DIALOG_STYLE_LIST, "Меню", "1. Статистика\n2. Настройки", "Выбрать", "");
}
DialogResponse:d_user_menu(playerid, response, listitem, inputtext[]) {
    if (!response) return true;
    switch(listitem) {
        case 0: Dialog_Show(playerid, Dialog:d_user_stats);
        case 1: Dialog_Show(playerid, Dialog:d_user_settings);
    }
    return true;
}

DialogCreate:d_user_stats(playerid){
	Show_Stats(playerid, playerid);
}
DialogResponse:d_player_stats(playerid, response, listitem, inputtext[]){
	if(!response)
		return Dialog_Show(playerid, Dialog: d_user_menu);
    else if(response) return Dialog_Show(playerid, Dialog: d_user_menu);
	return true;
}

DialogCreate:d_user_settings(playerid) {
    new dialogFormat[255];
    format(dialogFormat, sizeof(dialogFormat), "{FFFFFF}Настройка\t \t{FFFFFF}Статус\n\
    Сохранения позиции при выходе\t \t%s\n", P[playerid][p_saveLastPos] == 1 ? ("{1CF50D}Вкл.") : ("{FF0000}Выкл."));
    Dialog_Open(playerid, Dialog:d_user_settings, DIALOG_STYLE_TABLIST_HEADERS, "Настройки", dialogFormat, "Выбрать", "Назад");
}
DialogResponse:d_user_settings(playerid, response, listitem, inputtext[]) {
    if (!response) return Dialog_Show(playerid, Dialog:d_user_menu);
    switch(listitem) {
        case 0: {
            if(P[playerid][p_saveLastPos] == 0)
    			P[playerid][p_saveLastPos] = 1;
    		else if(P[playerid][p_saveLastPos] == 1)
    			P[playerid][p_saveLastPos] = 0;
        }
    }
    Update_PlayerSettings(playerid);
    return true;
}
