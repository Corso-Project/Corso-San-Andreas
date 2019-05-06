stock isdigit(symbol) {
	return '0' <= symbol <= '9';
}
stock IsNumeric(const string[]) {
	for (new i = 0; string[i] != '\0'; i++) {
		if (!isdigit(string[i])) {
			return 0;
		}
	}
	return true;
}
stock randomEx(min, max) {
    // Credits to y_less
    new rand = random(max-min)+min;
    return rand;
}
stock Log(const fmat[], va_args<>) {
	if (g_Log_Level == 0) return true;
	print(va_return(fmat, va_start<1>));
	return true;
}
