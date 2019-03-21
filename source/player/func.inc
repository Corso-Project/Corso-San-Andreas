stock Update_PlayerSettings(playerid) {
	format(P[playerid][p_settings], 10, "%i", P[playerid][p_saveLastPos]);
	orm_update(P[playerid][_p_ormid]);
}
