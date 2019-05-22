forward AutoTimer(playerid);
public AutoTimer(playerid) {
    KillTimer(connect_player_wait[playerid]);
    GetPlayerName(playerid, P[playerid][p_name], MAX_PLAYER_NAME);

    new ORM: ormid = P[playerid][_p_ormid] = orm_create("accounts");

    orm_addvar_int(ormid, P[playerid][p_uid], "UID");
    orm_addvar_string(ormid, P[playerid][p_name], MAX_PLAYER_NAME, "Name");
    orm_addvar_string(ormid, P[playerid][p_password], WHIRLPOOL_LEN, "Password");

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
    new weather = randomEx(0, 20),
        dests[34];
    SetWeather(weather);
    switch(weather) {
        case 0: dests = "Очень солнечно ЛС";
        case 1: dests = "Солнечно ЛС";
        case 2: dests = "Очень солнечно с смогом ЛС";
        case 3: dests = "Солнечно с смогом ЛС";
        case 4: dests = "Облачно ЛС";
        case 5: dests = "Солнечно СФ";
        case 6: dests = "Очень солнечно СФ";
        case 7: dests = "Облачно СФ";
        case 8: dests = "Дождь СФ";
        case 9: dests = "Смог СФ";
        case 10: dests = "Солнечно ЛВ";
        case 11: dests = "Очень солнечно ЛВ";
        case 12: dests = "Облачно ЛВ";
        case 13: dests = "Очень солнечно Деревня";
        case 14: dests = "Солнечно Деревня";
        case 15: dests = "Облачно Деревня";
        case 16: dests = "Дождливо Деревня";
        case 17: dests = "Очень солнечно Пустыня";
        case 18: dests = "Солнечно Пустыня";
        case 19: dests = "Песчаная буря";
        case 20: dests = "Подводное (зеленоватый, туманный)";
    }
    Log("[DEBUG] Погода изменилась на ID: %i(%s)", weather, dests);
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

    foreach (new playerid : Player) {
        SetPlayerTime(playerid, Hour, Minute);
    }
}
