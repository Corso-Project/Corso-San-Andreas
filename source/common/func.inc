stock isdigit(symbol)
{
	return '0' <= symbol <= '9';
}
stock IsNumeric(const string[])
{
	for (new i = 0; string[i] != '\0'; i++) {
		if (!isdigit(string[i])) {
			return 0;
		}
	}
	return 1;
}
stock randomEx(min, max)
{
    //Credits to y_less
    new rand = random(max-min)+min;
    return rand;
}
