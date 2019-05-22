#define GAMEMODE_VERSION	"San Andreas v 0.0.4"
#define SERVER_NAME			"Corso San Andreas"

new Hour = 0,
	Minute = 0;

enum {
	ORG_UNKNOWN,

	ORG_GOVERNMENT,
	ORG_FBI,
	ORG_LSPD,
	ORG_SFPD,
	ORG_LVPD,
	ORG_MILITARY,
	ORG_EMERGENCY,
	ORG_SANNEWS,
	ORG_AUTOSCHOOL,

	ORG_GROVE,
	ORG_BALLAS,
	ORG_AZTECAS,
	ORG_VAGOS,
	ORG_RIFA,

	ORG_CHINESE,
	ORG_DANANG,
	ORG_RUSSIAN,
	ORG_ITALIAN,

	ORG_BIKERS,
	ORG_CA
}

enum {
	SEX_FEMALE,
	SEX_MALE
}

enum E_PLAYER_DATA
{
	bool: _p_in_game,
	ORM: _p_ormid,
	bool: _p_spawned,
	//mysql synced
	p_uid,
	p_name[MAX_PLAYER_NAME],
	p_password[WHIRLPOOL_LEN],

	p_access,

	p_kills,
	p_deaths,
	p_cash,
	p_skin,
	p_sex,
	Float: p_health,
	Float: p_armour,

	p_job_team,

	p_reg_date[32],
	p_reg_ip[46],
	p_last_ip[46],

	// settings
	p_settings[10],
	p_saveLastPos,

	p_last_pos[45]
};
new P[MAX_PLAYERS][E_PLAYER_DATA];

// mysql.ini
new g_MySQL_Host[46],
	g_MySQL_User[46],
	g_MySQL_Database[46],
	g_MySQL_Password[46],
	MySQL: g_MySQL_DB;
// settings.ini
new g_Log_Level;
// Timers
new connect_player_wait[MAX_PLAYERS],
	weatherTimer,
	customtimeTimer;

// All
new Float: CamerasRand[][] = {
	// SetPlayerCameraPos                 // SetPlayerCameraLookAt
	{1587.295410, -1343.91918, 353.02212, 1583.398071, -1345.2114, 350.16882},
	{2236.614990, -1730.95153, 17.908832, 2238.796630, -1726.5458, 18.820371},
	{2089.854492, 1537.968750, 24.085695, 2091.074951, 1542.81030, 23.820104},
	{2089.751464, -1806.37304, 15.563168, 2094.751464, -1806.4022, 15.555676},
	{2735.750976, -1773.51708, 155.95469, 2735.747070, -1773.0812, 150.97372},
	{1412.731689, -870.593505, 86.736419, 1412.781372, -865.59527, 86.860107},
	{-2749.57666, -247.971099, 86.004989, -2749.58496, -248.40679, 81.024017},
	{-2781.11914, 1309.175659, 38.314773, -2778.68798, 1313.53906, 38.538646},
	{-2018.13037, 210.6668850, 51.885322, -2014.63171, 214.074523, 50.814262},
	{1422.325439, -2216.03295, 43.626846, 1425.134033, -2219.8837, 42.115695},
	{915.5786740, -1067.80981, 103.26267, 915.4323730, -1062.8205, 102.96977}
};
// Gang Zone
new GangZonesColors[] = {
	0xFFFFFF50, 0xFFFFFF50, 0xFFFFFF50
};
new GangZonesIDs[58];
