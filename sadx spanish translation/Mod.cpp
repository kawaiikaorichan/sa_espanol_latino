#include "SADXModLoader.h"
#include <stdio.h>
const char MyString[] = "Ass";

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
		char pathbuf[MAX_PATH];
		HMODULE HDGUI = GetModuleHandle(L"HD_GUI");
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