public OnPlayerRequestClass(playerid, classid) {
	if (P[playerid][_p_in_game] == true) {
		if (P[playerid][p_saveLastPos] == 1) {
			new Float: x,
				Float: y,
				Float: z,
				Float: Angle;
			sscanf(P[playerid][p_last_pos], "p<,>ffff", x, y, z, Angle);
			if (x != 0 && y != 0 && z != 0) {
				SetSpawnInfo(playerid, 0, P[playerid][p_skin], x, y, z, Angle, 0,0,0,0,0,0);
			} else {
				SetSpawnInfo(playerid, 0, P[playerid][p_skin], 1642.4329,-2239.0205,13.4967, 180.0, 0,0,0,0,0,0);
			}
		} else {
			SetSpawnInfo(playerid, 0, P[playerid][p_skin], 1642.4329,-2239.0205,13.4967, 180.0, 0,0,0,0,0,0);
		}
        SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
        SpawnPlayer(playerid);
		PlayerPlaySound(playerid, 1069, 0.0, 0.0, 0.0);

		SetPlayerHealth(playerid, P[playerid][p_health]);
		SetPlayerArmour(playerid, P[playerid][p_armour]);
		P[playerid][_p_spawned] = true;
	} else {
		SetPlayerInterior(playerid, 0);
		SetPlayerPos(playerid,1984.4445,157.9501,55.9384);
		SetPlayerFacingAngle(playerid,0.0);
		InterpolateCameraPos(playerid, 1984.4445,160.9501,55.9384, 1984.4445,160.9501,55.9384, 1000);
		InterpolateCameraLookAt(playerid, 1984.4445,157.9501,55.9384, 1984.4445,157.9501,55.9384, 1000);

		if (GetPVarInt(playerid, "Gender") == 1) {
			switch(classid) {
				case 0: SetPlayerSkin(playerid, 230);
				case 1: SetPlayerSkin(playerid, 212);
				case 2: SetPlayerSkin(playerid, 200);
				case 3: SetPlayerSkin(playerid, 78);
				case 4: SetPlayerSkin(playerid, 79);

				case 5: SetPlayerSkin(playerid, 230);
				case 6: SetPlayerSkin(playerid, 212);
				case 7: SetPlayerSkin(playerid, 200);
				case 8: SetPlayerSkin(playerid, 78);
				case 9: SetPlayerSkin(playerid, 78);
			}
		} else if (GetPVarInt(playerid, "Gender") == 2) {
			switch(classid) {
				case 0: SetPlayerSkin(playerid, 39);
				case 1: SetPlayerSkin(playerid, 54);
				case 2: SetPlayerSkin(playerid, 77);

				case 3: SetPlayerSkin(playerid, 39);
				case 4: SetPlayerSkin(playerid, 54);
				case 5: SetPlayerSkin(playerid, 77);
			}
		}
		P[playerid][_p_spawned] = true;
	}
	SendClientMessage(playerid, -1, "OnPlayerRequestClass");
	return true;
}
public OnPlayerRequestSpawn(playerid) {
	PlayerPlaySound(playerid, 1069, 0.0, 0.0, 0.0);
    P[playerid][p_skin] = GetPlayerSkin(playerid);

	SetSpawnInfo(playerid, 0, P[playerid][p_skin], 1642.4329,-2239.0205,13.4967, 180.0, 0,0,0,0,0,0);
	SetPlayerInterior(playerid, 0);
	SetPlayerVirtualWorld(playerid, 0);
	SpawnPlayer(playerid);

	new string_date[32];
	format(string_date,sizeof(string_date), "%s", date("%yyyy-%mm-%dd %hh:%ii:%ss", gettime()));

	if (GetPVarInt(playerid, "Gender") == 1)
		P[playerid][p_sex] = 0;
	else P[playerid][p_sex] = 1;
	P[playerid][p_reg_date] = string_date;

	orm_insert(P[playerid][_p_ormid], "OnMySQL_InsertAccount", "d", playerid);
    return true;
}
public OnPlayerConnect(playerid) {
	TogglePlayerSpectating(playerid, 1);
	SetPlayerTime(playerid, Hour, Minute);
	Dialog_Message(playerid, "Загрузка...","{FFFFFF}Мы рады вас видеть на нашем сервере {b3f9b0}", "Ok");
    connect_player_wait[playerid] = SetTimerEx("AutoTimer", 3000, true, "i", playerid);
    return true;
}
public OnPlayerDisconnect(playerid, reason) {
	if (P[playerid][_p_ormid]) {
	    if (P[playerid][_p_in_game] == true) {
			if (P[playerid][p_saveLastPos] == 1) {
				new Float:x, Float:y, Float:z, Float: Angle;
				GetPlayerPos(playerid, x, y, z);
				GetPlayerFacingAngle(playerid, Angle);
				format(P[playerid][p_last_pos], 45, "%f, %f, %f, %0.2f", x, y, z, Angle);
			}

    		GetPlayerHealth(playerid, P[playerid][p_health]);
			GetPlayerArmour(playerid, P[playerid][p_armour]);
			P[playerid][p_cash] = GetPlayerMoney(playerid);
			orm_update(P[playerid][_p_ormid]);
	    }
	    orm_destroy(P[playerid][_p_ormid]);
	}
	for(new i; i < sizeof(P[]); i++) P[playerid][E_PLAYER_DATA: i] = 0;
    return true;
}
public OnPlayerSpawn(playerid) {
	if(P[playerid][_p_in_game] == true) {
		for(new i; i < sizeof GangZonesIDs; i++) {
			ShowZoneForPlayer(playerid, GangZonesIDs[i], GangZonesColors[random(sizeof GangZonesColors)]);
			CreateZoneBorders(GangZonesIDs[i]);
		}
		SendClientMessage(playerid, -1, "OnPlayerSpawn");
		if (!P[playerid][_p_spawned]) {
			SendClientMessage(playerid, -1, "Bad Guy");
			respawnAtHospital(playerid);
			P[playerid][_p_spawned] = true;
		}
	}
    return true;
}
public OnPlayerDeath(playerid, killerid, reason) {
	SendClientMessage(playerid, -1, "OnPlayerDeath");
	P[playerid][_p_spawned] = false;

	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	SetSpawnInfo(playerid, 0, P[playerid][p_skin], x, y, z, 0, 0,0,0,0,0,0);
    return true;
}
public OnPlayerText(playerid, text[]) {
    return false;
}
public OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	if(P[playerid][_p_in_game] == false) return 0;
	if(newkeys & KEY_YES) {
		Dialog_Show(playerid, Dialog:d_user_menu);
	}
	return true;
}
public OnPlayerClickMap(playerid, Float: fX, Float: fY, Float: fZ) {
	switch(GetPlayerState(playerid)) {
	    case 0,7..9: return 1;
	    case 1,3..6: {
	        if(GetPlayerInterior(playerid) != 0) SetPlayerInterior(playerid, 0);
	        if(GetPlayerVirtualWorld(playerid) != 0) SetPlayerVirtualWorld(playerid, 0);
	        SetPlayerPosFindZ(playerid, fX,fY,fZ+0.1);
	    }
	    case 2: SetVehiclePos(GetPlayerVehicleID(playerid), fX,fY,fZ+0.1);
	}
	return true;
}
public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger) {
	if (V[vehicleid][v_door] == false) {
		ClearAnimations(playerid);
		SendClientMessage(playerid, -1, "Автомобиль закрыт.");
		return true;
	}
    return true;
}
