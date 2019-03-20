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
    if (P[playerid][p_access] > 1) {
        new string[37+1+1];
        format(string, sizeof(string), "Вы вошли как администратор %i уровня.", P[playerid][p_access]);
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
