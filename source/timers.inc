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

    orm_addvar_int(ormid, P[playerid][p_job_team], "Job_Team");

    orm_addvar_string(ormid, P[playerid][p_reg_date], 32, "Reg_Date");
    orm_addvar_string(ormid, P[playerid][p_reg_ip], 46, "Reg_IP");
    orm_addvar_string(ormid, P[playerid][p_last_ip], 46, "Last_IP");

    orm_addvar_int(ormid, P[playerid][p_lic_moto], "Lic_Moto");
	orm_addvar_int(ormid, P[playerid][p_lic_car], "Lic_Car");
	orm_addvar_int(ormid, P[playerid][p_lic_freight], "Lic_Freight");
	orm_addvar_int(ormid, P[playerid][p_lic_boat], "Lic_Boat");
	orm_addvar_int(ormid, P[playerid][p_lic_helicopter], "Lic_Helicopter");
	orm_addvar_int(ormid, P[playerid][p_lic_aircraft], "Lic_Aircraft");
	orm_addvar_int(ormid, P[playerid][p_lic_weapon], "Lic_Weapon");

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
        case 0: dests = "����� �������� ��";
        case 1: dests = "�������� ��";
        case 2: dests = "����� �������� � ������ ��";
        case 3: dests = "�������� � ������ ��";
        case 4: dests = "������� ��";
        case 5: dests = "�������� ��";
        case 6: dests = "����� �������� ��";
        case 7: dests = "������� ��";
        case 8: dests = "����� ��";
        case 9: dests = "���� ��";
        case 10: dests = "�������� ��";
        case 11: dests = "����� �������� ��";
        case 12: dests = "������� ��";
        case 13: dests = "����� �������� �������";
        case 14: dests = "�������� �������";
        case 15: dests = "������� �������";
        case 16: dests = "�������� �������";
        case 17: dests = "����� �������� �������";
        case 18: dests = "�������� �������";
        case 19: dests = "�������� ����";
        case 20: dests = "��������� (�����������, ��������)";
    }
    Log("[DEBUG] ������ ���������� �� ID: %i(%s)", weather, dests);
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
