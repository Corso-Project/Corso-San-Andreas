stock Vehicle_LoadFromFile(const filename[]) {
	if(!fexist(filename)) return 0;
	new File: txt;
	new line[128];
	new vehicletype,
		Float:x,Float:y,Float:z,Float:rotation,
		color1,color2;

	txt = fopen(filename, io_read);

	if(!txt) return 0;

	while(fread(txt, line, 128) > 0) {
	    sscanf(line, "p<,>iffffii", vehicletype,x,y,z,rotation,color1,color2);
	    new vehicleid = CreateVehicle(vehicletype, x,y,z,rotation, color1,color2, -1);
		new number_plate[7+1];
		format(number_plate, sizeof(number_plate), "%c%c%c%i%c%c", 65+random(25), 65+random(25), 65+random(25), randomEx(0, 99), 65+random(25), 65+random(25));
	    SetVehicleNumberPlate(vehicleid, number_plate);
		V[vehicleid][v_door] = false;
	}
	fclose(txt);
	return 1;
}
