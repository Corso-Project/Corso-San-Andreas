forward OnMySQL_SelectAccount(playerid);
public OnMySQL_SelectAccount(playerid) {
	PlayerPlaySound(playerid, 1097, 0.0, 0.0, 10.0);
	new rand = random(sizeof(CamerasRand));
	SetPlayerCameraPos(playerid, CamerasRand[rand][0], CamerasRand[rand][1], CamerasRand[rand][2]);
	SetPlayerCameraLookAt(playerid,CamerasRand[rand][3], CamerasRand[rand][4], CamerasRand[rand][5]);

	switch(orm_errno(P[playerid][_p_ormid])) {
	    case ERROR_OK: Dialog_Show(playerid, Dialog:d_user_login);
	    case ERROR_NO_DATA: Dialog_Show(playerid, Dialog:d_user_register);
	}
	orm_setkey(P[playerid][_p_ormid], "UID");
}
forward OnMySQL_InsertAccount(playerid);
public OnMySQL_InsertAccount(playerid) {
	orm_load(P[playerid][_p_ormid]);
	P[playerid][_p_in_game] = true;
}
