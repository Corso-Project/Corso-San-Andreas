// Credits to YSI
//#define va_args<%0> %0
#if defined _INC_y_globaltags
	#endinput
#endif
#define _INC_y_globaltags

// "File,Float," must remain last always.
#if defined CUSTOM_TAG_TYPES
	#define File,Float, Float,File,Text3D,CUSTOM_TAG_TYPES
#else
	#define File,Float, Float,File,Text3D
#endif
// Add new tags to the START of this list.
//#define GLOBAL_TAG_TYPES {_,Language,Bit,PlayerText3D,Text,Text3D,Menu,DB,DBResult,Style,XML,Bintree,Group,Timer,File,Float} //,CUSTOM_TAG_TYPES}
#define GLOBAL_TAG_TYPES {_,Language,Bit,Text,Menu,Style,XML,Bintree,Group,Timer,File,Float,} //,CUSTOM_TAG_TYPES}

#define va_args<%0> GLOBAL_TAG_TYPES:...
#define va_start<%0> (va_:(%0))
#define YSI_MAX_STRING (130)

static stock
	YSI_g_sHeap,
	YSI_g_sStack,
	YSI_g_sArgCount,
	YSI_g_sArgs[5];

stock PlayerText:va_CreatePlayerTextDraw(playerid, Float:x, Float:y, fmat[], va_args<>)
{
    return CreatePlayerTextDraw(playerid, x, y, va_return(fmat, va_start<4>));
}
stock Text:va_TextDrawCreate(Float:x, Float:y, fmat[], va_args<>)
{
    return TextDrawCreate(x, y, va_return(fmat, va_start<3>));
}
stock va_SendClientMessage(playerid, colour, const fmat[], va_args<>)
{
    return SendClientMessage(playerid, colour, va_return(fmat, va_start<3>));
}
stock va_SendClientMessageToAll(colour, const fmat[], va_args<>)
{
    return SendClientMessageToAll(colour, va_return(fmat, va_start<2>));
}
stock va_SendPlayerMessageToPlayer(playerid, senderid, const fmat[], va_args<>)
{
    return SendPlayerMessageToPlayer(playerid, senderid, va_return(fmat, va_start<3>));
}
stock va_SendPlayerMessageToAll(senderid, const fmat[], va_args<>)
{
    return SendPlayerMessageToAll(senderid, va_return(fmat, va_start<2>));
}
stock va_GameTextForPlayer(playerid, const fmat[], time, style, va_args<>)
{
    return GameTextForPlayer(playerid, va_return(fmat, va_start<4>), time, style);
}
stock va_GameTextForAll(const fmat[], time, style, va_args<>)
{
    return GameTextForAll(va_return(fmat, va_start<3>), time, style);
}
stock va_print(const fmat[], va_args<>)
{
	return print(va_return(fmat, va_start<1>));
}
stock va_fprintf(File:fhnd, const fmat[], va_args<>)
{
    return fwrite(fhnd, va_return(fmat, va_start<2>));
}
stock va_return(const fmat[], va_:STATIC_ARGS)
{
	static
		out[YSI_MAX_STRING * 8],
		size = sizeof (out);

	// Get the number of parameters.
	#emit LOAD.S.alt   STATIC_ARGS
	#emit DEC.alt      // 2 - n
	#emit SHL.C.alt    2
	// "alt" now contains the number of static arguments in bytes - 4.

	// Get the previous parameter count.
	#emit LOAD.S.pri   0
	#emit ADD.C        8
	#emit LOAD.I
	#emit SUB
	#emit ADD.C        8
	#emit STOR.pri     YSI_g_sArgCount // "format"s parameter count.

	// Get the address of the arguments we are replacing.
	#emit LOAD.S.pri   0
	#emit ADD

	// Copy them to our temporary buffer.
	#emit CONST.alt    YSI_g_sArgs
	#emit MOVS         16 // (n + 1) * 4

	// Go to the new "top" of the stack.
	#emit STACK        0
	#emit STOR.alt     YSI_g_sStack    // Store it.
	#emit ADD.C        16 // (n + 1) * 4
	#emit SCTRL        4

	// "frm" is still valid.
	#emit PUSH.S       fmat
	#emit PUSH         size
	#emit PUSH.C       out
	#emit PUSH         YSI_g_sArgCount // Push the parameter count.

	// Modify the heap to hold "locals".
	#emit HEAP         0
	#emit STOR.alt     YSI_g_sHeap
	#emit LCTRL        4
	#emit SCTRL        2

	// Call the function.
	#emit SYSREQ.C     format

	// Copy the data back.
	#emit LOAD.pri     YSI_g_sHeap
	#emit SCTRL        2
	#emit STACK        0
	#emit CONST.pri    YSI_g_sArgs
	#emit MOVS         16
	#emit LOAD.pri     YSI_g_sStack
	#emit SCTRL        4

	// Now do the real return.
	return out;
}
