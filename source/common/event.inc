public OnGameModeInit() {
    Load_MySQL();
	//Подключения к MySQL
	mysql_log(ALL);
	g_MySQL_DB = mysql_connect(g_MySQL_Host,g_MySQL_User,g_MySQL_Password,g_MySQL_Database);
    mysql_set_charset("cp1251");
	if(mysql_errno() != 0) {
	    print("\n[Ошибка]: Внимание! Подключение к базе данных MySQL не установлено.\n");
		SendRconCommand("exit");
	    return 0;
	}
	SetGameModeText(GAMEMODE_VERSION);
	SendRconCommand("hostname "SERVER_NAME);
	// DisableInteriorEnterExits();
	EnableStuntBonusForAll(0);
	ShowPlayerMarkers(PLAYER_MARKERS_MODE_STREAMED);
	ShowNameTags(1);
    // DisableNameTagLOS();
	UsePlayerPedAnims();
    /* new start_year, start_month, start_day, start_hour, start_minute, start_second;
    new time = gettime();
    gmtime(time, start_year, start_month, start_day, start_hour, start_minute, start_second);
    SetWorldTime(start_hour+2); */

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

    // Аммунация
    CreateDynamicMapIcon(1372.9, -1278.8, 12.5, 6, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(2400.5, -1978.4, 13.5, 6, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(-2626.6, 209.4, 4.9, 6, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(2535.9, 2083.5, 10.8, 6, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(2156.5, 943.2, 10.8, 6, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(779.7, 1874.3, 4.9, 6, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(-2092.7, -2463.8, 30.6, 6, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(240.0, -178.2, 2.0, 6, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(-1509.4, 2611.8, 58.5, 6, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(-315.67, 829.87, 13.43, 6, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(2332.9, 63.6, 31.0, 6, 0xFFFFFFFF, -1,-1,-1, 1000);

    // Бургершот
    CreateDynamicMapIcon(812.9, -1616.1, 13.6, 10, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(1199.1, -924.0, 43.3, 10, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(2362.2, 2069.9, 10.8, 10, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(2469.5, 2033.8, 10.8, 10, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(2172.9, 2795.7, 10.8, 10, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(1875.3, 2072.0, 10.8, 10, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(1161.5, 2072.0, 10.8, 10, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(-2356.0, 1009.0, 49.0, 10, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(-1913.3, 826.2, 36.9, 10, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(2335.6, -165.6, 39.5, 10, 0xFFFFFFFF, -1,-1,-1, 1000);
    // Cluckin Bell
    CreateDynamicMapIcon(2397.8, -1895.6, 13.7, 14, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(2421.6, -1509.6, 24.1, 14, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(-2671.6, 257.4, 4.6, 14, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(2392.4, 2046.5, 10.8, 14, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(2844.5, 2401.1, 11.0, 14, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(2635.5, 1674.3, 11.0, 14, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(2105.7, 2228.7, 11.0, 14, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(-2154.0, -2461.2, 30.8, 14, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(-1816.2, 620.8, 37.5, 14, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(-1216.0, 1831.4, 45.3, 14, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(172.73, 1176.76, 13.7, 14, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(932.0, -1353.0, 14.0, 14, 0xFFFFFFFF, -1,-1,-1, 1000);
    // Diner
    CreateDynamicMapIcon(2862.0, -1439.0, 10.0, 17, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(384.6615, -1819.529, 6.8414, 17, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(-1699.0, 1380.0, 6.0, 17, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(-2524.0, 1216.0, 37.0, 17, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(1376.892, 2327.792, 9.822, 17, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(2368.058, 1983.185, 10.003, 17, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(681.544, -473.494, 15.592, 17, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(-1941.516, 2379.672, 48.4922, 17, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(-53.867, 1189.297, 18.414, 17, 0xFFFFFFFF, -1,-1,-1, 1000);
    // Marker_Emmets_Gun
    CreateDynamicMapIcon(2447.364, -1974.496, 12.5469, 18, 0xFFFFFFFF, -1,-1,-1, 1000);
    // Hospital
    CreateDynamicMapIcon(1178.62330, -1323.8820, 14.1292, 22, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(2034.24260, -1414.6997, 16.9922, 22, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(-2200.5435, -2310.4019, 30.6250, 22, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(-316.22600, 1055.19190, 19.7422, 22, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(1243.31880, 329.896100, 19.7578, 22, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(1876.10530, 2238.56520, 11.1250, 22, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(1606.86690, 1822.86160, 10.8203, 22, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(-2658.1619, 631.018000, 14.4531, 22, 0xFFFFFFFF, -1,-1,-1, 1000);
    // Trans Fender
    CreateDynamicMapIcon(-2728.5, 212.2, 3.4, 27, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(2644.252, -2028.246, 12.5547, 27, 0xFFFFFFFF, -1,-1,-1, 1000);
    // Well Stacked Pizza
    CreateDynamicMapIcon(-1805.7, 943.2, 24.8, 29, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(2750.9, 2470.9, 11.0, 29, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(2351.8, 2529.0, 10.8, 29, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(2635.5, 1847.4, 11.0, 29, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(2083.4, 2221.0, 11.0, 29, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(-1719.1, 1359.4, 8.6, 29, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(2330.2, 75.2, 31.0, 29, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(203.2, -200.4, 6.5, 29, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(2107.624, -1807.516, 21.2114, 29, 0xFFFFFFFF, -1,-1,-1, 1000); // Marker_Idlewood_Pizzeria
    // Clothes
    CreateDynamicMapIcon(-2376.4, 909.2, 45.4, 45, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(1654.0, 1733.4, 11.0, 45, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(2105.7, 2257.4, 11.0, 45, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(-2371.1, 910.2, 47.2, 45, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(501.7, -1358.5, 16, 45, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(2818.6, 2401.5, 11.0, 45, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(2112.8, -1214.7, 23.9, 45, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(2772.0, 2447.6, 11.0, 45, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(-2489.0, -26.9, 32.6, 45, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(2243.807, -1668.567, 20.0313, 45, 0xFFFFFFFF, -1,-1,-1, 1000); // Marker_Ganton_Clothes_Shop
    // Gym
    CreateDynamicMapIcon(2228.0, -1722.811, 12.5543, 54, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(-2269.4, -155.6, 35.3, 54, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(1968.6, 2292.1, 16.4, 54, 0xFFFFFFFF, -1,-1,-1, 1000);
    // Pay N Spray
    CreateDynamicMapIcon(2067.4, -1831.2, 13.5, 63, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(488.0, -1734.0, 34.4, 63, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(720.016, -454.625, 15.328, 63, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(-1420.547, 2583.945, 58.031, 63, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(1966.532, 2162.65, 10.995, 63, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(-2425.46, 1020.83, 49.39, 63, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(1021.8, -1018.7, 30.9, 63, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(-1908.9, 292.3, 40.0, 63, 0xFFFFFFFF, -1,-1,-1, 1000);
    CreateDynamicMapIcon(-103.6, 1112.4, 18.7, 63, 0xFFFFFFFF, -1,-1,-1, 1000);
    // Zero RC Shop
    CreateDynamicMapIcon(-2245.663, 128.8889, 34.3203, 47, 0xFFFFFFFF, -1,-1,-1, 1000);
    // Triadas_Casino
    CreateDynamicMapIcon( 1962.432, 974.675, 993.4688, 44, 0xFFFFFFFF, -1,-1,-1, 1000);
    // Caligula
    CreateDynamicMapIcon(2270.634, 1635.599, 1007.367, 25, 0xFFFFFFFF, -1,-1,-1, 1000);

    SendRconCommand("loadfs dillimore_gas");
    SendRconCommand("loadfs ferriswheel");
    SendRconCommand("loadfs flymode");
    SendRconCommand("loadfs kylies_barn");
    SendRconCommand("loadfs ls_apartments1");
    SendRconCommand("loadfs ls_beachside");
    SendRconCommand("loadfs maxips");
    SendRconCommand("loadfs netstats");
    SendRconCommand("loadfs pnetstats");
    SendRconCommand("loadfs pnetstats2");
    SendRconCommand("loadfs vspawner");
    SendRconCommand("loadfs cameditor");

    GangZonesIDs[0] = CreateZone(2632.8, -1852.8, 2959.3, -1668.1);
    GangZonesIDs[1] = CreateZone(2632.8, -1668.1, 2747.7, -1393.4);
    GangZonesIDs[2] = CreateZone(2747.7, -1668.1, 2959.3, -1498.6);
    GangZonesIDs[3] = CreateZone(2747.7, -1498.6, 2959.3, -1120.0);
    GangZonesIDs[4] = CreateZone(2421.0, -1628.5, 2632.8, -1454.3);
    GangZonesIDs[5] = CreateZone(2222.5, -1628.5, 2421.0, -1494.0);
    GangZonesIDs[6] = CreateZone(2266.2, -1494.0, 2381.6, -1372.0);
    GangZonesIDs[7] = CreateZone(2281.4, -1372.0, 2381.6, -1135.0);
    GangZonesIDs[8] = CreateZone(2381.6, -1454.3, 2462.1, -1135.0);
    GangZonesIDs[9] = CreateZone(2462.1, -1454.3, 2581.7, -1135.0);
    GangZonesIDs[10] = CreateZone(1812.6, -2179.2, 1970.6, -1852.8);
    GangZonesIDs[11] = CreateZone(1692.6, -2179.2, 1812.6, -1842.2);
    GangZonesIDs[12] = CreateZone(2222.5, -1852.8, 2632.8, -1722.3);
    GangZonesIDs[13] = CreateZone(2222.5, -1722.3, 2632.8, -1628.5);
    GangZonesIDs[14] = CreateZone(1812.6, -1449.6, 1996.9, -1350.7);
    GangZonesIDs[15] = CreateZone(1812.6, -1350.7, 2056.8, -1100.8);
    GangZonesIDs[16] = CreateZone(1812.6, -1852.8, 1971.6, -1742.3);
    GangZonesIDs[17] = CreateZone(1812.6, -1742.3, 1951.6, -1602.3);
    GangZonesIDs[18] = CreateZone(1951.6, -1742.3, 2124.6, -1602.3);
    GangZonesIDs[19] = CreateZone(1812.6, -1602.3, 2124.6, -1449.6);
    GangZonesIDs[20] = CreateZone(2124.6, -1742.3, 2222.5, -1494.0);
    GangZonesIDs[21] = CreateZone(1971.6, -1852.8, 2222.5, -1742.3);
    GangZonesIDs[22] = CreateZone(2124.6, -1494.0, 2266.2, -1449.6);
    GangZonesIDs[23] = CreateZone(2056.8, -1372.0, 2281.4, -1210.7);
    GangZonesIDs[24] = CreateZone(2056.8, -1210.7, 2185.3, -1126.3);
    GangZonesIDs[25] = CreateZone(2185.3, -1210.7, 2281.4, -1154.5);
    GangZonesIDs[26] = CreateZone(2056.8, -1449.6, 2266.2, -1372.0);
    GangZonesIDs[27] = CreateZone(1994.3, -1100.8, 2056.8, -920.8);
    GangZonesIDs[28] = CreateZone(2056.8, -1126.3, 2126.8, -920.8);
    GangZonesIDs[29] = CreateZone(2185.3, -1154.5, 2281.4, -934.4);
    GangZonesIDs[30] = CreateZone(2126.8, -1126.3, 2185.3, -934.4);
    GangZonesIDs[31] = CreateZone(2747.7, -1120.0, 2959.3, -945.0);
    GangZonesIDs[32] = CreateZone(2632.7, -1135.0, 2747.7, -945.0);
    GangZonesIDs[33] = CreateZone(2281.4, -1135.0, 2632.7, -945.0);
    GangZonesIDs[34] = CreateZone(1701.9, -1842.2, 1812.6, -1722.2);
    GangZonesIDs[35] = CreateZone(1758.9, -1722.2, 1812.6, -1577.5);
    GangZonesIDs[36] = CreateZone(2581.7, -1454.3, 2632.8, -1393.4);
    GangZonesIDs[37] = CreateZone(2581.7, -1393.4, 2747.7, -1135.0);
    GangZonesIDs[38] = CreateZone(2703.5, -2126.9, 2959.3, -1852.8);
    GangZonesIDs[39] = CreateZone(342.6, -2173.2, 647.7, -1684.6);
    GangZonesIDs[40] = CreateZone(72.6, -2173.2, 342.6, -1684.6);
    GangZonesIDs[41] = CreateZone(1252.3, -1130.8, 1378.3, -1026.3);
    GangZonesIDs[42] = CreateZone(1252.3, -1026.3, 1391.0, -926.9);
    GangZonesIDs[43] = CreateZone(1252.3, -926.9, 1357.0, -910.1);
    GangZonesIDs[44] = CreateZone(952.6, -1130.8, 1096.4, -937.1);
    GangZonesIDs[45] = CreateZone(1096.4, -1130.8, 1252.3, -1026.3);
    GangZonesIDs[46] = CreateZone(1692.6, -1971.8, 1812.6, -1932.8);
    GangZonesIDs[47] = CreateZone(647.7, -2173.2, 930.2, -1804.2);
    GangZonesIDs[48] = CreateZone(930.2, -2006.7, 1073.2, -1804.2);
    GangZonesIDs[49] = CreateZone(851.4, -1804.2, 1046.1, -1577.5);
    GangZonesIDs[50] = CreateZone(1161.5, -1722.2, 1323.9, -1577.5);
    GangZonesIDs[51] = CreateZone(1046.1, -1722.2, 1161.5, -1577.5);
    GangZonesIDs[52] = CreateZone(787.4, -1130.8, 952.6, -954.6);
    GangZonesIDs[53] = CreateZone(1970.6, -2179.2, 2089.0, -1852.8);
    GangZonesIDs[54] = CreateZone(2089.0, -2235.8, 2201.8, -1989.9);
    GangZonesIDs[55] = CreateZone(2089.0, -1989.9, 2324.0, -1852.8);
    GangZonesIDs[56] = CreateZone(2201.8, -2095.0, 2324.0, -1989.9);
    GangZonesIDs[57] = CreateZone(2324.0, -2059.2, 2541.7, -1852.8);
    for(new i; i < sizeof GangZonesIDs; i++) {
		CreateZoneBorders(GangZonesIDs[i]);
	}

    WeatherChanger();
    weatherTimer = SetTimer("WeatherChanger", randomEx(1500000, 3600000), true);
    customtimeTimer = SetTimer("CustomTimeTimer", 1000, true);
    return true;
}
public OnGameModeExit() {
    KillTimer(weatherTimer);
    KillTimer(customtimeTimer);
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
