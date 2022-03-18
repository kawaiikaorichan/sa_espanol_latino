#include "pch.h"
const char MyString[] = "Ass";

Trampoline* LoadRegObjTextures_b = nullptr;
Trampoline* FreeRegObjTexlists_b = nullptr;

HMODULE DCconversion = GetModuleHandle(L"DCMods_Main");

static NJS_TEXNAME EspGUI_TEXNAME[2] = {};
static NJS_TEXLIST EspGUI_TEXLIST = { arrayptrandlengthT(EspGUI_TEXNAME, int) };

static void __cdecl LoadRegObjTextures_r(int a1)
{
	if (DCconversion)
	{
		LoadPVM("Tex_espanol", &EspGUI_TEXLIST);
		((decltype(LoadRegObjTextures_r)*)LoadRegObjTextures_b->Target())(a1);
	}
}

static void __cdecl FreeRegObjTexlists_r()
{
	njReleaseTexture(&EspGUI_TEXLIST);
	((decltype(FreeRegObjTexlists_r)*)FreeRegObjTexlists_b->Target())();
}

void EspGUI_Init()
{
	LoadRegObjTextures_b = new Trampoline(0x4212E0, 0x4212E5, LoadRegObjTextures_r, false);
	FreeRegObjTexlists_b = new Trampoline(0x420F40, 0x420F45, FreeRegObjTexlists_r, false);
}

//Arrays
DataArray(TitleCardTexture, SonicTitleCards, 0x91C358, 10);
DataArray(TitleCardTexture, TailsTitleCards, 0x91C3A8, 5);
DataArray(TitleCardTexture, KnucklesTitleCards, 0x91C3D0, 5);
DataArray(TitleCardTexture, AmyTitleCards, 0x91C3F8, 3);
DataArray(TitleCardTexture, BigTitleCards, 0x91C410, 4);
DataArray(TitleCardTexture, GammaTitleCards, 0x91C430, 4);
DataArray(TitleCardTexture, AdventureTitleCards, 0x91C458, 9);
DataArray(TitleCardTexture, SubgameTitleCards, 0x91C4A0, 5);

//Macros
#define ReplacePNG_Common(a) do { \
	_snprintf_s(pathbuf, LengthOfArray(pathbuf), "%s\\textures\\pvrs\\index.txt", path); \
	helperFunctions.ReplaceFile("system\\" a ".PVR", pathbuf); \
} while (0)

#define ReplacePNG_StageS(a) do { \
	_snprintf_s(pathbuf, LengthOfArray(pathbuf), "%s\\textures\\pvr_stage_sp\\index.txt", path); \
	helperFunctions.ReplaceFile("system\\" a ".PVR", pathbuf); \
} while (0)

extern "C"
{
	__declspec(dllexport) __declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		//Init stuff
		WriteData((const char**)0x504B5B, " Crear Archivo");
		WriteData((const char**)0x5482A8, "Caos 0");
		WriteData((const char**)0x54CCFE, "Caos 2");
		WriteData((const char**)0x5509DC, "Caos 4");
		WriteData((const char**)0x559872, "Caos 6");
		WriteData((const char**)0x56037F, "Caos Perfecto");
		WriteData((const char**)0x587DA4, "CERO");
		WriteData((const char**)0x62616D, "PUNTAJE MAS ALTO");
		WriteData((const char**)0x626215, "DOCTOR ROBOTNIK");
		WriteData((const char**)0x626279, "INICIA");
		WriteData((const char**)0x6262C9, "TIEMPO");
		WriteData((const char**)0x6262D8, "CONTEO");
		WriteData((const char**)0x626401, "FIN DEL JUEGO");
		WriteData((const char**)0x626458, "FELICIDADES");
		WriteData((const char**)0x6264C0, "GANAS LA PLUMA DEL GUERRERO");
		WriteData((const char**)0x6264D3, "GANAS EL MARTILLO LARGO");
		WriteData((const char**)0x62652A, "TIENES LA PUNTUACION MAS ALTA");
		WriteData((const char**)0x6283F5, "FIN DEL JUEGO");
		WriteData((const char**)0x7595DF, "PRESIONA A PARA MATAR AL CHAO");
		WriteData((const char**)0x4B544C, "\tAhora puedes jugar con Metal Sonic\nen el modo de prueba.");
		WriteData((const char**)0x917DFC, "¿Registrar en este botón?"); // sp
		WriteData((const char**)0x917E10, "Presiona el botón a registrar"); // sp
		WriteData((const char**)0x90C4AC, "Se terminará la partida y volverá a la\npantalla de selección de personaje. ¿Ok?"); // sp
		WriteData((const char**)0x90C4C0, "Se terminará el nivel y volverá al \ncampo de aventura. ¿Ok?"); // sp
		WriteData((const char**)0x90C4D4, "Se terminará la partida y volverá \nal menú principal. ¿Ok?"); // sp
		WriteData((const char**)0x7D3B5B, "\aLa Piedra del Viento... Parece una llave.\nEl grabado debe significar algo."); // sp
		WriteData((const char**)0x7D3B10, "\aLa Piedra de Hielo... Parece una llave.\nQuizá pueda usarla en Ruinas Místicas."); // sp
		WriteData((const char**)0x2BBF540, "\aLa Piedra de Hielo... Parece una llave.\nQuizá pueda usarla en Ruinas Místicas."); // sp
		WriteData((const char**)0x10D7958, "\t\tBorrado."); // sp
		WriteData((const char**)0x111CB5C, "\aDice 'Botón destruye-monos'\n"); // sp
		WriteData((const char**)0x111CB60, "\a'Presiona para destruir.'"); // sp
		WriteData((const char**)0x111CB30, "\a¡Botón... presionado!"); // sp
		WriteData((const char**)0x111CB08, "\aEl botón fue accionado,\npero no pasó nada."); // sp
		WriteData((const char**)0x111CAE0, "\aEl botón fue accionado,\npero no pasó nada."); // sp
		WriteData((const char**)0x2BC07C0, "\a¡Una tarjeta de empleado!\nAhora puedo entrar en este edificio."); // sp
		WriteData((const char**)0x2BC07E8, "\aIdentidad comprobada"); // sp
		WriteData((const char**)0x2BBF480, "\a¡Un pase! Ahora puedo entrar\nen el Circuito Destello."); // sp 
		WriteData((const char**)0x2BBF468, "\a¡Bienvenido al Circuito Destello!"); // sp
		WriteData((const char**)0x8033D4, "\a¡Cuidado! ¡Trama algo!"); // sp
		WriteData((const char**)0x7FD52C, "\a¡Salta y vuelve a presionar el botón de \nsalto para realizar el ataque teledirigido!");
		WriteData((const char**)0x7FD57C, "\aApunta al punto débil en su cabeza.");
		WriteData((const char**)0x7FD970, "\a¡Apunta a la cabeza de Caos \ncuando baje la guardia!");
		WriteData((const char**)0x7FD9C0, "\a¡Planea o usa tu ataque giratorio en lugar \nde los puños para golpear su núcleo!");
		WriteData((const char**)0x7FDA10, "\a¡Puedes golpear las burbujitas de agua.!");
		WriteData((const char**)0x7FE460, "\a¡Cuando Caos asome su cabeza, \nes la hora de atacar!");
		WriteData((const char**)0x7FEBB0, "\aSi pudieras congelar a Caos... \nPiensa en un forma de hacerlo.");
		WriteData((const char**)0x7FEC08, "Avienta las Eggbombas de Robotnik \na la boca de Caos.");
		WriteData((const char**)0x7FEC58, "\a¡Apunta a la rana \ny arroja tu anzuelo!"); // sp
		WriteData((const char**)0x7FECC0, "\a¡Arroja tu anzuelo");
		WriteData((const char**)0x7FECC8, "\aen cuanto Caos se aproxime a ti!");
		WriteData((const char**)0x801D64, "\aEl Egg Hornet es su propio punto débil. \nAtácalo cuando se acerque. ");
		WriteData((const char**)0x802D20, "\aApunta a las piernas \npara que pierda el equilibrio. ");
		WriteData((const char**)0x802D30, "\a¡No sólo le des a las piernas, \napunta a la cabina!");
		WriteData((const char**)0x803494, "\aRobotnik está del otro lado \ndel concentrador de energía.");
		WriteData((const char**)0x8034A4, "\aUsa ataques teledirigidos");
		WriteData((const char**)0x8034B4, "\apara llegar a la cabina.");
		WriteData((const char**)0x8034C4, "\aSube a la rueda de púas \ny alcanzarás la cabina.");
		WriteData((const char**)0x8046FC, "\aDebe tener algún punto débil.");
		WriteData((const char**)0x804704, "\a¡Sigue atacando hasta que lo encuentres!");
		WriteData((const char**)0x80055C, "\aCuando alcances la máxima velocidad \nte volverás una bola ardiente.");
		WriteData((const char**)0x800564, "\a¡Es el momento de atacar a Caos!");
		WriteData((const char**)0x2BC5808, "El objetivo es encontrar el");
		WriteData((const char**)0x2BC580C, "\"objeto de la misión\" en el");
		WriteData((const char**)0x2BC5810, "campo de aventura. Usa la pista");
		WriteData((const char**)0x2BC5814, "que se muestra a continuación");
		WriteData((const char**)0x2BC5818, "para completar la misión.");
		WriteData((const char**)0x2BC581C, "Al tocar el \"objeto de la");
		WriteData((const char**)0x2BC5820, "misión\" se mostrará una");
		WriteData((const char**)0x2BC5824, "pista. Usa esta pista para");
		WriteData((const char**)0x2BC5828, "averiguar qué debes hacer para");
		WriteData((const char**)0x2BC582C, "poder completar la misión.");
		WriteData((const char**)0x2BC5830, "Son 60 misiones para 6");
		WriteData((const char**)0x2BC5834, "personajes (Sonic, Tails,");
		WriteData((const char**)0x2BC5838, "Knuckles, Amy, E-102, Big).");

		char pathbuf[MAX_PATH];
		HMODULE HDGUI = GetModuleHandle(L"HD_GUI");
		EspGUI_Init();
		//PVRs
		ReplacePNG_Common("ST_064S_SCORE");
		ReplacePNG_Common("HYOJI_BALLS_E");
		//Replace stage titlecard filenames
		//Sonic
		SonicTitleCards[0].TextureName = "s_stage01_s";
		SonicTitleCards[1].TextureName = "s_stage02_s";
		SonicTitleCards[2].TextureName = "s_stage03_s";
		SonicTitleCards[3].TextureName = "s_stage04_s";
		SonicTitleCards[4].TextureName = "s_stage05_s";
		SonicTitleCards[5].TextureName = "s_stage06_s";
		SonicTitleCards[6].TextureName = "s_stage07_s";
		SonicTitleCards[7].TextureName = "s_stage08_s";
		SonicTitleCards[8].TextureName = "s_stage09_s";
		SonicTitleCards[9].TextureName = "s_stage10_s";
		//Tails
		TailsTitleCards[0].TextureName = "m_stage01_s";
		TailsTitleCards[1].TextureName = "m_stage02_s";
		TailsTitleCards[2].TextureName = "m_stage03_s";
		TailsTitleCards[3].TextureName = "m_stage04_s";
		TailsTitleCards[4].TextureName = "m_stage05_s";
		//Knackels
		KnucklesTitleCards[0].TextureName = "k_stage01_s";
		KnucklesTitleCards[1].TextureName = "k_stage02_s";
		KnucklesTitleCards[2].TextureName = "k_stage03_s";
		KnucklesTitleCards[3].TextureName = "k_stage04_s";
		KnucklesTitleCards[4].TextureName = "k_stage05_s";
		//Amy
		AmyTitleCards[0].TextureName = "a_stage01_s";
		AmyTitleCards[1].TextureName = "a_stage02_s";
		AmyTitleCards[2].TextureName = "a_stage03_s";
		//Big
		BigTitleCards[0].TextureName = "b_stage01_s";
		BigTitleCards[1].TextureName = "b_stage02_s";
		BigTitleCards[2].TextureName = "b_stage03_s";
		BigTitleCards[3].TextureName = "b_stage04_s";
		//Gamma
		GammaTitleCards[0].TextureName = "e_stage01_s";
		GammaTitleCards[1].TextureName = "e_stage02_s";
		GammaTitleCards[2].TextureName = "e_stage03_s";
		GammaTitleCards[3].TextureName = "e_stage04_s";
		//Adventure Fields
		AdventureTitleCards[0].TextureName = "t_stationsquare_s";
		AdventureTitleCards[1].TextureName = "t_stationsquare_s";
		AdventureTitleCards[2].TextureName = "t_stationsquare_s";
		AdventureTitleCards[3].TextureName = "t_eggcarrier_s";
		AdventureTitleCards[4].TextureName = "t_eggcarrier_s";
		AdventureTitleCards[5].TextureName = "t_eggcarrier_s";
		AdventureTitleCards[6].TextureName = "t_eggcarrier_s";
		AdventureTitleCards[7].TextureName = "t_misticruin_s";
		AdventureTitleCards[8].TextureName = "t_misticruin_s";
		//Subgames
		SubgameTitleCards[0].TextureName = "St_stage03_s";
		SubgameTitleCards[1].TextureName = "St_stage01_s";
		SubgameTitleCards[2].TextureName = "St_stage02_s";
		SubgameTitleCards[3].TextureName = "St_stage04_s";
		SubgameTitleCards[4].TextureName = "St_stage05_s";
		//Replace PVRs with HD PNGs if HD GUI is detected
		//Spanish stage PVRs
		if (HDGUI)
		{
			ReplacePNG_Common("ST_064S_SCORE");
			ReplacePNG_Common("HYOJI_BALLS_E");
			ReplacePNG_StageS("A_STAGE01_S");
			ReplacePNG_StageS("A_STAGE02_S");
			ReplacePNG_StageS("A_STAGE03_S");
			ReplacePNG_StageS("B_STAGE01_S");
			ReplacePNG_StageS("B_STAGE02_S");
			ReplacePNG_StageS("B_STAGE03_S");
			ReplacePNG_StageS("B_STAGE04_S");
			ReplacePNG_StageS("E_STAGE01_S");
			ReplacePNG_StageS("E_STAGE02_S");
			ReplacePNG_StageS("E_STAGE03_S");
			ReplacePNG_StageS("E_STAGE04_S");
			ReplacePNG_StageS("E_STAGE05_S");
			ReplacePNG_StageS("K_STAGE01_S");
			ReplacePNG_StageS("K_STAGE02_S");
			ReplacePNG_StageS("K_STAGE03_S");
			ReplacePNG_StageS("K_STAGE04_S");
			ReplacePNG_StageS("K_STAGE05_S");
			ReplacePNG_StageS("M_STAGE01_S");
			ReplacePNG_StageS("M_STAGE02_S");
			ReplacePNG_StageS("M_STAGE03_S");
			ReplacePNG_StageS("M_STAGE04_S");
			ReplacePNG_StageS("M_STAGE05_S");
			ReplacePNG_StageS("ST_STAGE01_S");
			ReplacePNG_StageS("ST_STAGE02_S");
			ReplacePNG_StageS("ST_STAGE03_S");
			ReplacePNG_StageS("ST_STAGE04_S");
			ReplacePNG_StageS("ST_STAGE05_S");
			ReplacePNG_StageS("S_STAGE01_S");
			ReplacePNG_StageS("S_STAGE02_S");
			ReplacePNG_StageS("S_STAGE03_S");
			ReplacePNG_StageS("S_STAGE04_S");
			ReplacePNG_StageS("S_STAGE05_S");
			ReplacePNG_StageS("S_STAGE06_S");
			ReplacePNG_StageS("S_STAGE07_S");
			ReplacePNG_StageS("S_STAGE08_S");
			ReplacePNG_StageS("S_STAGE09_S");
			ReplacePNG_StageS("S_STAGE10_S");
			ReplacePNG_StageS("T_SGGCARRIER_S");
			ReplacePNG_StageS("T_MISTICRUIN_S");
			ReplacePNG_StageS("T_STATIONSQUARE_S");
		}
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}