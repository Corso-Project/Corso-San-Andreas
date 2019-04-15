forward AutoTimer(playerid);
public AutoTimer(playerid) {
    KillTimer(connect_player_wait[playerid]);
    GetPlayerName(playerid, P[playerid][p_name], MAX_PLAYER_NAME);

    new ORM: ormid = P[playerid][_p_ormid] = orm_create("accounts");

    orm_addvar_int(ormid, P[playerid][p_uid], "UID");
    orm_addvar_string(ormid, P[playerid][p_name], MAX_PLAYER_NAME, "Name");
    orm_addvar_string(ormid, P[playerid][p_password], 18, "Password");

    orm_addvar_int(ormid, P[playerid][p_access], "Access");

    orm_addvar_int(ormid, P[playerid][p_kills], "Kills");
    orm_addvar_int(ormid, P[playerid][p_deaths], "Deaths");
    orm_addvar_int(ormid, P[playerid][p_cash], "Cash");
    orm_addvar_int(ormid, P[playerid][p_skin], "Skin");
    orm_addvar_int(ormid, P[playerid][p_sex], "Sex");

    orm_addvar_float(ormid, P[playerid][p_health], "Health");
    orm_addvar_float(ormid, P[playerid][p_armour], "Armour");

    orm_addvar_string(ormid, P[playerid][p_reg_date], 32, "Reg_Date");
    orm_addvar_string(ormid, P[playerid][p_reg_ip], 46, "Reg_IP");
    orm_addvar_string(ormid, P[playerid][p_last_ip], 46, "Last_IP");

    orm_addvar_string(ormid, P[playerid][p_settings], 10, "Settings");

    orm_addvar_string(ormid, P[playerid][p_last_pos], 45, "Last_Pos");

    orm_setkey(ormid, "Name");
    orm_select(ormid, "OnMySQL_SelectAccount", "i", playerid);
}

forward WeatherChanger();
public WeatherChanger() {
    SetWeather(randomEx(0, 20));
    // SendClientMessageToAll(-1, "Погода изменилась!");
    printf("Погода изменилась!");
    return 1;
}
forward CustomTimeTimer();
public CustomTimeTimer(){
    if (Minute >= 60) {
        Hour += 1;
        if (Hour >= 24) {
            Hour = 0;
        }
        Minute = 0;
    } else {
        Minute += 1;
    }

    // new string[30];
    // format(string, sizeof(string), "Время сменилось: %i:%i", Hour, Minute);
    foreach (new playerid : Player) {
        SetPlayerTime(playerid, Hour, Minute);
        // SendClientMessage(playerid, -1, string);
    }
}
