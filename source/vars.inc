#define GAMEMODE_VERSION	"San Andreas v 0.0.1"
#define SERVER_NAME			"Corso San Andreas"

enum {
	SEX_FEMALE,
	SEX_MALE
}

enum E_PLAYER_DATA
{
	bool: _p_in_game,
	ORM: _p_ormid,
	//mysql synced
	p_uid,
	p_name[MAX_PLAYER_NAME],
	p_password[18],

	p_access,

	p_kills,
	p_deaths,
	p_cash,
	p_skin,
	p_sex,

	p_reg_date[32],
	p_reg_ip[46]
};
new P[MAX_PLAYERS][E_PLAYER_DATA];

// mysql.ini
new g_MySQL_Host[46],
	g_MySQL_User[46],
	g_MySQL_Database[46],
	g_MySQL_Password[46],
	MySQL: g_MySQL_DB;
// Timers
new connect_player_wait[MAX_PLAYERS];

// All
new Float: CamerasRand[5][6] = {
	{2080.2300,916.1449,73.9590,2066.1353,937.4230,63.1651},
	{1213.2228,1270.5652,88.5621,1181.8884,1218.2719,70.1035},
	{-449.4783,1678.8866,169.5441,-397.7283,1638.3353,145.5633},
	{-1479.5405,985.2203,148.1212,-1503.0316,961.5603,138.4412},
	{421.2505,-1650.1685,112.1631,389.8018,-1612.4978,93.7020}
};
