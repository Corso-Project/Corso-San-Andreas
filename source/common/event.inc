public OnGameModeInit() {
    Load_MySQL();
	//Подключения к MySQL
	mysql_log(ALL);
	g_MySQL_DB = mysql_connect(g_MySQL_Host,g_MySQL_User,g_MySQL_Password,g_MySQL_Database);
	if(mysql_errno() != 0) {
	    print("\n[Ошибка]: Внимание! Подключение к базе данных MySQL не установлено.\n");
		SendRconCommand("exit");
	    return 0;
	}
	SetGameModeText(GAMEMODE_VERSION);
	SendRconCommand("hostname "SERVER_NAME);
	DisableInteriorEnterExits();
	EnableStuntBonusForAll(0);
	ShowPlayerMarkers(2);
	ShowNameTags(1);
    // DisableNameTagLOS();
	UsePlayerPedAnims();
	// Selection
		//male
	AddPlayerClass(230, 0,0,0,0, 0,0,0,0,0,0);
	AddPlayerClass(212, 0,0,0,0, 0,0,0,0,0,0);
	AddPlayerClass(200, 0,0,0,0, 0,0,0,0,0,0);
	AddPlayerClass(78, 0,0,0,0, 0,0,0,0,0,0);
	AddPlayerClass(79, 0,0,0,0, 0,0,0,0,0,0);
		//female
	AddPlayerClass(39, 0,0,0,0, 0,0,0,0,0,0);
	AddPlayerClass(54, 0,0,0,0, 0,0,0,0,0,0);
	AddPlayerClass(77, 0,0,0,0, 0,0,0,0,0,0);

    Vehicle_LoadFromFile("vehicles/bone.txt");
    Vehicle_LoadFromFile("vehicles/flint.txt");
    Vehicle_LoadFromFile("vehicles/ls_airport.txt");
    Vehicle_LoadFromFile("vehicles/ls_gen_inner.txt");
    Vehicle_LoadFromFile("vehicles/ls_gen_outer.txt");
    Vehicle_LoadFromFile("vehicles/ls_law.txt");
    Vehicle_LoadFromFile("vehicles/lv_airport.txt");
    Vehicle_LoadFromFile("vehicles/lv_gen.txt");
    Vehicle_LoadFromFile("vehicles/lv_law.txt");
    Vehicle_LoadFromFile("vehicles/pilots.txt");
    Vehicle_LoadFromFile("vehicles/red_county.txt");
    Vehicle_LoadFromFile("vehicles/sf_airport.txt");
    Vehicle_LoadFromFile("vehicles/sf_gen.txt");
    Vehicle_LoadFromFile("vehicles/sf_law.txt");
    Vehicle_LoadFromFile("vehicles/tierra.txt");
    Vehicle_LoadFromFile("vehicles/whetstone.txt");

    SetTimer("UpdateTime", 1000, false);
    return true;
}
public OnGameModeExit() {
    mysql_close();
	return 1;
}
public OnRconLoginAttempt(ip[], password[], success) {
    if(!success) //If the password was incorrect
    {
        printf("FAILED RCON LOGIN BY IP %s USING PASSWORD %s",ip, password);
        new pip[16];
		foreach(new i : Player){
			GetPlayerIp(i, pip, sizeof(pip));
			if(!strcmp(ip, pip, true)) //If a player's IP is the IP that failed the login
            {
                SendClientMessage(i, -1, "Wrong Password. Bye!"); //Send a message
                Kick(i); //They are now kicked.
            }
		}
    }
    return 1;
}
