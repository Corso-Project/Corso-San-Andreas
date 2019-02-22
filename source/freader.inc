stock Load_MySQL() {
	new mysql_ini = ini_openFile("mysql.ini");
	ini_getString(mysql_ini, "Host", g_MySQL_Host);
	ini_getString(mysql_ini, "User", g_MySQL_User);
	ini_getString(mysql_ini, "Database", g_MySQL_Database);
	ini_getString(mysql_ini, "Password", g_MySQL_Password);
	ini_closeFile(mysql_ini);
}
