#include "pch.h"
#include "Creditos.h"
#include "SADXStructsNew.h"
const char MyString[] = "Ass";

#define ReplacePVM(a, b) helperFunctions.ReplaceFile("system\\" a ".PVM", "system\\" b ".PVM");
#define ReplaceTex(pvm, pvr, folder, pngname, gbix, x, y) helperFunctions.ReplaceTexture(pvm, pvr, (std::string(path) + "\\textures\\" folder "\\" pngname ".png").c_str(), gbix, x, y);

HMODULE DCconversion = GetModuleHandle(L"DCMods_Main");

int VoiceVolumeBoost = 5100;
int VoiceVolumeConv = 0;

int CalculateVolume_SADXStyle(int percent, int mode)
{
	// 0 for music, 1 for voices
	if (mode == 1)
		return 100 * (97 * percent / 100 - 100);
	else
		return 100 * (89 * percent / 100 - 100);
}

DataPointer(int, VoiceVolumeBK, 0x3ABDF90);

enum Doblaje { Neutro, Mexicano, Chileno };

static bool MusicaDub = true;
static int Dub = Neutro;
bool CreditsLoaded = false;

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
		const IniFile* config = new IniFile(std::string(path) + "\\config.ini");

		VoiceVolumeBoost = config->getInt("Volumen", "VoiceVolumeBoost", 5100);
		VoiceVolumeConv = CalculateVolume_SADXStyle(GetPrivateProfileIntA("sonicDX", "voicev", 100, ".\\sonicDX.ini"), 1) + VoiceVolumeBoost;

		std::string Dub_String = "Neutro";
		Dub_String = config->getString("Opciones", "Localizacion", "Neutro");
		MusicaDub = config->getBool("Opciones", "MusicaDub", true);

		if (Dub_String == "Neutro") Dub = Neutro;
		if (Dub_String == "Mexicano") Dub = Mexicano;
		if (Dub_String == "Chileno") Dub = Chileno;

		//Init stuff
		WriteData((const char**)0x504B5B, "  Crear Archivo");
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

		ReplaceTex("AVA_CHSEL_E", "CS_CE_TX", "traducidos", "CS_CE_TX", 365105, 256, 32);
		ReplaceTex("AVA_CHSEL_E", "cs_sinkou_e", "traducidos", "cs_sinkou_e", 10000035, 64, 32);
		ReplaceTex("AVA_CHSEL_E", "CS_TX_e", "traducidos", "CS_TX_e", 10000448, 512, 32);
		ReplaceTex("AVA_DLG_E", "B_CANSEL_e", "traducidos", "B_CANSEL_e", 10000180, 128, 16);
		ReplaceTex("AVA_DLG_E", "B_ENDING_e", "traducidos", "B_ENDING_e", 10000176, 128, 16);
		ReplaceTex("AVA_DLG_E", "B_KAISHI_e", "traducidos", "B_KAISHI_e", 10000489, 128, 16);
		ReplaceTex("AVA_DLG_E", "B_KETTEI_e", "traducidos", "B_KETTEI_e", 10000177, 64, 16);
		ReplaceTex("AVA_DLG_E", "B_no_e", "traducidos", "B_no_e", 10000499, 64, 16);
		ReplaceTex("AVA_DLG_E", "b_setumei_e", "traducidos", "b_setumei_e", 10000181, 256, 16);
		ReplaceTex("AVA_DLG_E", "b_ss_player_e", "traducidos", "b_ss_player_e", 10000182, 128, 32);
		ReplaceTex("AVA_DLG_E", "b_ss_stage_e", "traducidos", "b_ss_stage_e", 10000183, 128, 32);
		ReplaceTex("AVA_DLG_E", "b_syoukyo_e", "traducidos", "b_syoukyo_e", 10000185, 64, 16);
		ReplaceTex("AVA_DLG_E", "B_yes_e", "traducidos", "B_yes_e", 10000497, 32, 16);
		ReplaceTex("AVA_DLG_E", "syokika_e", "traducidos", "syokika_e", 710223, 64, 16);
		ReplaceTex("AVA_DLG_E", "retry_en", "traducidos", "retry_en", 710254, 64, 16);
		ReplaceTex("AVA_DLG_E", "dont", "traducidos", "dont", 710271, 128, 16);
		ReplaceTex("AVA_DLG_E", "manage", "traducidos", "manage", 710269, 128, 16);
		ReplaceTex("AVA_EMBLEMVIEW_E", "emb_result_ttl", "traducidos", "emb_result_ttl", 10000623, 256, 32);
		ReplaceTex("AVA_EMBLEMVIEW_E", "head_advf", "traducidos", "head_advf", 10000614, 256, 32);
		ReplaceTex("AVA_EMBLEMVIEW_E", "head_chaorace", "traducidos", "head_chaorace", 10000630, 256, 32);
		ReplaceTex("AVA_EMBLEMVIEW_E", "head_ending", "traducidos", "head_ending", 10000618, 128, 32);
		ReplaceTex("AVA_EMBLEMVIEW_E", "head_minigame", "traducidos", "head_minigame", 10000629, 256, 32);
		ReplaceTex("AVA_EMBLEMVIEW_E", "select_advf", "traducidos", "select_advf", 10000611, 256, 16);
		ReplaceTex("AVA_EMBLEMVIEW_E", "select_chaorace", "traducidos", "select_chaorace", 10000627, 128, 16);
		ReplaceTex("AVA_EMBLEMVIEW_E", "select_ending", "traducidos", "select_ending", 10000628, 128, 16);
		ReplaceTex("AVA_EMBLEMVIEW_E", "select_minigame", "traducidos", "select_minigame", 10000626, 128, 16);
		ReplaceTex("AVA_FILESEL_E", "fs_m_clear_e", "traducidos", "fs_m_clear_e", 10000038, 256, 16);
		ReplaceTex("AVA_FILESEL_E", "fs_m_embrem_e", "traducidos", "fs_m_embrem_e", 10000036, 256, 16);
		ReplaceTex("AVA_FILESEL_E", "fs_m_play_e", "traducidos", "fs_m_play_e", 10000040, 256, 16);
		ReplaceTex("AVA_FILESEL_E", "fs_m_start_e", "traducidos", "fs_m_start_e", 10000041, 256, 16);
		ReplaceTex("AVA_FILESEL_E", "FS_TX_e", "traducidos", "FS_TX_e", 10000445, 512, 32);
		ReplaceTex("AVA_GTITLE0_E", "p_enter_us_00", "traducidos", "p_enter_us_00", 3489661283, 256, 256);
		ReplaceTex("AVA_GTITLE0_E", "p_enter_us_01", "traducidos", "p_enter_us_01", 3489661284, 256, 256);
		ReplaceTex("AVA_GTITLE0_E", "p_enter_us_02", "traducidos", "p_enter_us_01", 3489661258, 256, 256);
		ReplaceTex("AVA_OPTION_E", "b_oto_nomi_e", "traducidos", "b_oto_nomi_e", 10000179, 128, 16);
		ReplaceTex("AVA_OPTION_E", "b_oto_txt_e", "traducidos", "b_oto_txt_e", 10000175, 128, 16);
		ReplaceTex("AVA_OPTION_E", "B_STEREO_e", "traducidos", "B_STEREO_e", 10000184, 64, 16);
		ReplaceTex("AVA_OPTION_E", "op_modoru_tx", "traducidos", "op_modoru_tx", 10000187, 128, 16);
		ReplaceTex("AVA_OPTION_E", "OP_MS_TX", "traducidos", "OP_MS_TX", 10000188, 128, 16);
		ReplaceTex("AVA_OPTION_E", "op_out_tx", "traducidos", "op_out_tx", 10000189, 128, 16);
		ReplaceTex("AVA_OPTION_E", "op_test_tx", "traducidos", "op_test_tx", 10000190, 128, 16);
		ReplaceTex("AVA_OPTION_E", "OP_TX_e", "traducidos", "OP_TX_e", 10000447, 128, 32);
		ReplaceTex("AVA_OPTION_E", "ta_notext", "traducidos", "ta_notext", 10000709, 128, 16);
		ReplaceTex("AVA_OPTION_E", "ta_text", "traducidos", "ta_text", 10000713, 128, 16);
		ReplaceTex("AVA_OPTION_E", "ta_voice", "traducidos", "ta_voice", 10000710, 128, 16);
		ReplaceTex("AVA_OPTION_E", "Op_tv_tx_e", "traducidos", "Op_tv_tx_e", 10001312, 128, 16);
		ReplaceTex("AVA_OPTION_E", "op_lang_tx_e", "traducidos", "op_lang_tx_e", 10001320, 128, 16);
		ReplaceTex("AVA_OPTION_E", "op_vib_tx_e", "traducidos", "op_vib_tx_e", 100000220, 128, 16);
		ReplaceTex("AVA_OPTION_E", "op_file_tx", "traducidos", "op_file_tx", 10000186, 128, 16);
		ReplaceTex("AVA_OPTION_E", "op_vib_on", "traducidos", "op_vib_on", 100000208, 32, 16);
		ReplaceTex("AVA_OPTION_E", "op_vib_off", "traducidos", "op_vib_off", 100000209, 32, 16);
		ReplaceTex("AVA_SNDTEST_E", "st_action", "traducidos", "st_action", 10000193, 256, 16);
		ReplaceTex("AVA_SNDTEST_E", "st_adventure", "traducidos", "st_adventure", 10000194, 256, 16);
		ReplaceTex("AVA_SNDTEST_E", "st_charactor", "traducidos", "st_charactor", 10000195, 128, 16);
		ReplaceTex("AVA_SNDTEST_E", "St_event_e", "traducidos", "St_event_e", 10000494, 64, 16);
		ReplaceTex("AVA_SNDTEST_E", "ST_KOUKA", "traducidos", "ST_KOUKA", 10000196, 64, 16);
		ReplaceTex("AVA_SNDTEST_E", "st_modoru_e", "traducidos", "st_modoru_e", 10000498, 256, 16);
		ReplaceTex("AVA_SNDTEST_E", "st_sonota_e", "traducidos", "st_sonota_e", 10000492, 64, 16);
		ReplaceTex("AVA_SNDTEST_E", "ST_TX_e", "traducidos", "ST_TX_e", 10000450, 256, 32);
		ReplaceTex("AVA_STNAM_E", "TX_ST01_e", "traducidos", "TX_ST01_e", 10000413, 256, 16);
		ReplaceTex("AVA_STNAM_E", "TX_ST02_e", "traducidos", "TX_ST02_e", 10000410, 256, 16);
		ReplaceTex("AVA_STNAM_E", "TX_ST04_e", "traducidos", "TX_ST04_e", 10000412, 256, 16);
		ReplaceTex("AVA_STNAM_E", "TX_ST05_e", "traducidos", "TX_ST05_e", 10000409, 128, 16);
		ReplaceTex("AVA_STNAM_E", "TX_ST07_e", "traducidos", "TX_ST07_e", 10000415, 128, 16);
		ReplaceTex("AVA_STNAM_E", "TX_ST08_e", "traducidos", "TX_ST08_e", 10000416, 256, 16);
		ReplaceTex("AVA_STNAM_E", "TX_ST09_e", "traducidos", "TX_ST09_e", 10000417, 256, 16);
		ReplaceTex("AVA_STNAM_E", "TX_ST10_e", "traducidos", "TX_ST10_e", 10000418, 128, 16);
		ReplaceTex("AVA_STNAM_E", "TX_ST11_e", "traducidos", "TX_ST11_e", 10000419, 128, 16);
		ReplaceTex("AVA_STNAM_E", "TX_ST12_e", "traducidos", "TX_ST12_e", 10000420, 128, 16);
		ReplaceTex("AVA_STNAM_E", "TX_ST13_e", "traducidos", "TX_ST13_e", 10000421, 128, 16);
		ReplaceTex("AVA_STNAM_E", "TX_ST15_e", "traducidos", "TX_ST15_e", 10000423, 256, 16);
		ReplaceTex("AVA_STNAM_E", "TX_ST16_e", "traducidos", "TX_ST16_e", 10000424, 256, 16);
		ReplaceTex("AVA_STNAM_E", "TX_ST17_e", "traducidos", "TX_ST17_e", 10000425, 128, 16);
		ReplaceTex("AVA_STNAM_E", "TX_ST18_e", "traducidos", "TX_ST18_e", 10000426, 256, 16);
		ReplaceTex("AVA_STNAM_E", "TX_ST19_e", "traducidos", "TX_ST19_e", 10000427, 256, 16);
		ReplaceTex("AVA_STNAM_E", "TX_ST20_e", "traducidos", "TX_ST20_e", 10000428, 64, 16);
		ReplaceTex("AVA_STNAM_E", "TX_ST21_e", "traducidos", "TX_ST21_e", 10000429, 128, 16);
		ReplaceTex("AVA_STNAM_E", "TX_ST22_e", "traducidos", "TX_ST22_e", 10000430, 128, 16);
		ReplaceTex("AVA_STNAM_E", "TX_ST23_e", "traducidos", "TX_ST23_e", 10000431, 128, 16);
		ReplaceTex("AVA_STNAM_E", "TX_ST31_e", "traducidos", "TX_ST31_e", 10000439, 32, 16);
		ReplaceTex("AVA_STNAM_E", "TX_ST33_e", "traducidos", "TX_ST33_e", 10000441, 64, 16);
		ReplaceTex("AVA_STNAM_E", "tx_st34_e", "traducidos", "tx_st34_e", 10000442, 256, 16);
		ReplaceTex("AVA_TITLE_E", "main_tx_action_e", "traducidos", "main_tx_action_e", 10000117, 256, 16);
		ReplaceTex("AVA_TITLE_E", "main_tx_ad_e", "traducidos", "main_tx_ad_e", 10000114, 128, 16);
		ReplaceTex("AVA_TITLE_E", "main_tx_in_e", "traducidos", "main_tx_in_e", 10000115, 128, 16);
		ReplaceTex("AVA_TITLE_E", "main_tx_ms_e", "traducidos", "main_tx_in_e", 10000115, 128, 16);
		ReplaceTex("AVA_TITLE_E", "main_tx_mini_e", "traducidos", "main_tx_mini_e", 10000116, 128, 16);
		ReplaceTex("AVA_TITLE_E", "main_tx_op_e", "traducidos", "main_tx_op_e", 10000113, 128, 16);
		ReplaceTex("AVA_TITLE_E", "main_tx_try_e", "traducidos", "main_tx_try_e", 10000118, 128, 16);
		ReplaceTex("AVA_TITLE_E", "main_tx_emblem_v", "traducidos", "main_tx_emblem_v", 10001357, 256, 16);
		ReplaceTex("AVA_TITLE_E", "main_tx_puti_e", "traducidos", "main_tx_puti_e", 100000141, 256, 16);
		ReplaceTex("AVA_TITLE_E", "end_game_e", "traducidos", "end_game_e", 3489661192, 128, 16);
		ReplaceTex("AVA_TRIALACTSEL_E", "SS_1ST", "traducidos", "SS_1ST", 365093, 64, 32);
		ReplaceTex("AVA_TRIALACTSEL_E", "SS_2ND", "traducidos", "SS_2ND", 365094, 64, 32);
		ReplaceTex("AVA_TRIALACTSEL_E", "SS_3RD", "traducidos", "SS_3RD", 365095, 64, 32);
		ReplaceTex("AVA_TRIALACTSEL_E", "SS_TX_e", "traducidos", "SS_TX_e", 10000444, 512, 32);
		ReplaceTex("AVA_TRIALACTSEL_E", "ss_tx_bestclear", "traducidos", "ss_tx_bestclear", 10000464, 128, 16);
		ReplaceTex("AVA_TRIALACTSEL_E", "ss_tx_bestweight_e", "traducidos", "ss_tx_bestweight_e", 10000496, 128, 16);
		ReplaceTex("AVA_TRIALACTSEL_E", "ss_tx_embrem", "traducidos", "ss_tx_embrem", 10000454, 128, 16);
		ReplaceTex("AVA_TRIALACTSEL_E", "ss_tx_hiscore", "traducidos", "ss_tx_hiscore", 10000455, 128, 16);
		ReplaceTex("AVA_TRIALACTSEL_E", "ss_tx_minigame_e", "traducidos", "ss_tx_minigame_e", 10000449, 256, 32);
		ReplaceTex("AVA_TRIALACTSEL_E", "ss_tx_ring", "traducidos", "ss_tx_ring", 10000456, 256, 16);
		ReplaceTex("AVA_TRIALACTSEL_E", "ss_tx_score", "traducidos", "ss_tx_score", 10000457, 64, 16);
		ReplaceTex("AVA_TRIALACTSEL_E", "ss_tx_time", "traducidos", "ss_tx_time", 10000458, 64, 16);
		ReplaceTex("AVA_VMSSEL_E", "ms_port_a", "traducidos", "ms_port_a", 10000468, 128, 16);
		ReplaceTex("AVA_VMSSEL_E", "ms_port_b", "traducidos", "ms_port_b", 10000467, 128, 16);
		ReplaceTex("AVA_VMSSEL_E", "MS_TX_e", "traducidos", "MS_TX_e", 10000446, 512, 32);
		ReplaceTex("B_CHNAM_E", "B_SONIC_e", "traducidos", "B_SONIC_e", 10000032, 512, 64);
		ReplaceTex("B_CHNAM_E", "b_knuckles_e", "traducidos", "b_knuckles_e", 10000031, 512, 64);
		ReplaceTex("B_CHNAM_E", "B_BIG_e", "traducidos", "B_BIG_e", 10000029, 512, 64);
		ReplaceTex("B_CHNAM_E", "b_supersonic_e", "traducidos", "b_supersonic_e", 10000028, 512, 64);
		ReplaceTex("BOARD_SCORE", "st_064s_score", "traducidos", "st_064s_score", 310000, 64, 32);
		ReplaceTex("CHAOS_LIFEGAUGE", "target_hpbar", "traducidos", "target_hpbar", 400997, 64, 64);
		ReplaceTex("CHAOS0_OBJECT", "sspd", "traducidos", "sspd", 205200, 64, 64);
		ReplaceTex("CON_REGULAR_E", "hyoji_head", "traducidos", "hyoji_head", 931, 64, 64);
		ReplaceTex("CON_REGULAR_E", "npa_m_adventure", "traducidos", "pausa", 100000054, 256, 64);
		ReplaceTex("CON_REGULAR_E", "npa_restart", "traducidos", "npa_restart", 365749, 256, 64);
		ReplaceTex("CON_REGULAR_E", "npa_saikai", "traducidos", "npa_saikai", 365748, 256, 64);
		ReplaceTex("CON_REGULAR_E", "npa_stop", "traducidos", "npa_stop", 365747, 256, 64);
		ReplaceTex("CON_REGULAR_E", "npa_autocam", "traducidos", "npa_autocam", 100000050, 256, 64);
		ReplaceTex("CON_REGULAR_E", "npa_freecam", "traducidos", "npa_freecam", 100000051, 256, 64);
		ReplaceTex("CON_REGULAR_E", "npa_map", "traducidos", "npa_map", 100000052, 256, 64);
		ReplaceTex("CON_REGULAR_E", "npa_mission", "traducidos", "npa_mission", 100000053, 256, 64);
		ReplaceTex("CON_REGULAR_E", "npa_m_trial", "traducidos", "pausa", 100000055, 256, 64);
		ReplaceTex("CON_REGULAR_E", "npa_m_mission", "traducidos", "pausa", 100000056, 256, 64);
		ReplaceTex("CON_REGULAR_E", "p_set_00", "traducidos", "p_set_00", 3489661184, 256, 64);
		ReplaceTex("CON_REGULAR_E", "p_set_01", "traducidos", "p_set_01", 3489661185, 256, 64);
		ReplaceTex("CON_REGULAR_E", "p_set_02", "traducidos", "p_set_02", 3489661186, 256, 64);
		ReplaceTex("CON_REGULAR_E", "p_set_03", "traducidos", "p_set_03", 3489661187, 256, 64);
		ReplaceTex("CON_REGULAR_E", "p_set_04", "traducidos", "p_set_04", 3489661188, 256, 64);
		ReplaceTex("CON_REGULAR_E", "p_set_05", "traducidos", "p_set_05", 3489661189, 256, 64);
		ReplaceTex("CON_REGULAR_E", "p_set_06", "traducidos", "p_set_06", 3489661190, 256, 64);
		ReplaceTex("CON_REGULAR_E", "s_menu_pset", "traducidos", "s_menu_pset", 3489661191, 256, 64);
		ReplaceTex("CON_REGULAR_E", "p_set_07", "traducidos", "p_set_07", 3489661193, 256, 64);
		ReplaceTex("E102TIME", "e102_getsecbg", "traducidos", "e102_getsecbg", 1697, 64, 64);
		ReplaceTex("E102TIME", "e102lastsec", "traducidos", "e102lastsec", 1699, 128, 128);
		ReplaceTex("EFF_REGULAR", "hit", "traducidos", "hit", 360060, 64, 64);
		ReplaceTex("EV_HELI", "sspd", "traducidos", "sspd", 206012, 64, 64);
		ReplaceTex("FISHING", "castgauge0", "traducidos", "castgauge0", 361002, 128, 256);
		ReplaceTex("FISHING", "bighyouji", "traducidos", "bighyouji", 361006, 64, 64);
		ReplaceTex("FISHING", "hit0", "traducidos", "hit0", 361008, 128, 128);
		ReplaceTex("FISHING", "hit1", "traducidos", "hit1", 361009, 128, 128);
		ReplaceTex("GAMEOVER_E", "gameover", "traducidos", "gameover", 365759, 256, 32);
		ReplaceTex("GAMEOVER_E", "npa_saikai", "traducidos", "npa_saikai", 10000200, 128, 32);
		ReplaceTex("GAMEOVER_E", "npa_stop", "traducidos", "npa_stop", 10000202, 128, 32);
		ReplaceTex("M_CHNAM", "m_supersonic", "traducidos", "m_supersonic", 365255, 256, 64);
		ReplaceTex("MAP_EC_A", "map_eca_e0", "traducidos", "map_eca_e0", 100000810, 256, 256);
		ReplaceTex("MAP_EC_A", "map_eca_e1", "traducidos", "map_eca_e1", 100000811, 256, 256);
		ReplaceTex("MAP_EC_A", "map_eca_e2", "traducidos", "map_eca_e2", 100000812, 256, 256);
		ReplaceTex("MAP_EC_A", "map_eca_e3", "traducidos", "map_eca_e3", 100000813, 256, 256);
		ReplaceTex("MAP_EC_A", "map_eca_e4", "traducidos", "map_eca_e4", 100000814, 256, 256);
		ReplaceTex("MAP_EC_A", "map_eca_e5", "traducidos", "map_eca_e5", 100000815, 256, 256);
		ReplaceTex("MAP_EC_B", "map_ecb_e0", "traducidos", "map_ecb_e0", 100000830, 256, 256);
		ReplaceTex("MAP_EC_B", "map_ecb_e1", "traducidos", "map_ecb_e1", 100000831, 256, 256);
		ReplaceTex("MAP_EC_B", "map_ecb_e2", "traducidos", "map_ecb_e2", 100000832, 256, 256);
		ReplaceTex("MAP_EC_B", "map_ecb_e3", "traducidos", "map_ecb_e3", 100000833, 256, 256);
		ReplaceTex("MAP_EC_B", "map_ecb_e4", "traducidos", "map_ecb_e4", 100000834, 256, 256);
		ReplaceTex("MAP_EC_B", "map_ecb_e5", "traducidos", "map_ecb_e5", 100000835, 256, 256);
		ReplaceTex("MAP_EC_H", "map_ech_e0", "traducidos", "map_ech_e0", 100000850, 256, 256);
		ReplaceTex("MAP_EC_H", "map_ech_e1", "traducidos", "map_ech_e1", 100000851, 256, 256);
		ReplaceTex("MAP_EC_H", "map_ech_e2", "traducidos", "map_ech_e2", 100000852, 256, 256);
		ReplaceTex("MAP_EC_H", "map_ech_e3", "traducidos", "map_ech_e3", 100000853, 256, 256);
		ReplaceTex("MAP_EC_H", "map_ech_e4", "traducidos", "map_ech_e4", 100000854, 256, 256);
		ReplaceTex("MAP_EC_H", "map_ech_e5", "traducidos", "map_ech_e5", 100000855, 256, 256);
		ReplaceTex("MAP_MR_A", "map_mra_e0", "traducidos", "map_mra_e0", 100000530, 256, 256);
		ReplaceTex("MAP_MR_A", "map_mra_e1", "traducidos", "map_mra_e1", 100000531, 256, 256);
		ReplaceTex("MAP_MR_A", "map_mra_e2", "traducidos", "map_mra_e2", 100000532, 256, 256);
		ReplaceTex("MAP_MR_A", "map_mra_e3", "traducidos", "map_mra_e3", 100000533, 256, 256);
		ReplaceTex("MAP_MR_A", "map_mra_e4", "traducidos", "map_mra_e4", 100000534, 256, 256);
		ReplaceTex("MAP_MR_A", "map_mra_e5", "traducidos", "map_mra_e5", 100000535, 256, 256);
		ReplaceTex("MAP_MR_J", "map_mrj_e0", "traducidos", "map_mrj_e0", 100000550, 256, 256);
		ReplaceTex("MAP_MR_J", "map_mrj_e1", "traducidos", "map_mrj_e1", 100000551, 256, 256);
		ReplaceTex("MAP_MR_J", "map_mrj_e2", "traducidos", "map_mrj_e2", 100000552, 256, 256);
		ReplaceTex("MAP_MR_J", "map_mrj_e4", "traducidos", "map_mrj_e4", 100000554, 256, 256);
		ReplaceTex("MAP_MR_J", "map_mrj_e5", "traducidos", "map_mrj_e5", 100000555, 256, 256);
		ReplaceTex("MAP_MR_S", "map_mrs_e0", "traducidos", "map_mrs_e0", 100000510, 256, 256);
		ReplaceTex("MAP_MR_S", "map_mrs_e1", "traducidos", "map_mrs_e1", 100000511, 256, 256);
		ReplaceTex("MAP_MR_S", "map_mrs_e2", "traducidos", "map_mrs_e2", 100000512, 256, 256);
		ReplaceTex("MAP_MR_S", "map_mrs_e3", "traducidos", "map_mrs_e3", 100000513, 256, 256);
		ReplaceTex("MAP_MR_S", "map_mrs_e4", "traducidos", "map_mrs_e4", 100000514, 256, 256);
		ReplaceTex("MAP_MR_S", "map_mrs_e5", "traducidos", "map_mrs_e5", 100000515, 256, 256);
		ReplaceTex("MAP_PAST_E", "map_pse_e1", "traducidos", "map_pse_e1", 100000631, 256, 256);
		ReplaceTex("MAP_PAST_E", "map_pse_e2", "traducidos", "map_pse_e2", 100000632, 256, 256);
		ReplaceTex("MAP_PAST_E", "map_pse_e4", "traducidos", "map_pse_e4", 100000634, 256, 256);
		ReplaceTex("MAP_PAST_E", "map_pse_e5", "traducidos", "map_pse_e5", 100000635, 256, 256);
		ReplaceTex("MAP_PAST_S", "map_pss_e0", "traducidos", "map_pss_e0", 100000610, 256, 256);
		ReplaceTex("MAP_PAST_S", "map_pss_e1", "traducidos", "map_pss_e1", 100000611, 256, 256);
		ReplaceTex("MAP_PAST_S", "map_pss_e4", "traducidos", "map_pss_e4", 100000614, 256, 256);
		ReplaceTex("MAP_PAST_S", "map_pss_e5", "traducidos", "map_pss_e5", 100000615, 256, 256);
		ReplaceTex("MAP_SS", "map_ss_e0", "traducidos", "map_ss_e0", 100000710, 256, 256);
		ReplaceTex("MAP_SS", "map_ss_e1", "traducidos", "map_ss_e1", 100000711, 256, 256);
		ReplaceTex("MAP_SS", "map_ss_e2", "traducidos", "map_ss_e2", 100000712, 256, 256);
		ReplaceTex("MAP_SS", "map_ss_e3", "traducidos", "map_ss_e3", 100000713, 256, 256);
		ReplaceTex("MAP_SS", "map_ss_e4", "traducidos", "map_ss_e4", 100000714, 256, 256);
		ReplaceTex("MAP_SS", "map_ss_e5", "traducidos", "map_ss_e5", 100000715, 256, 256);
		ReplaceTex("MIS_C_EN", "m_c_status_00", "traducidos", "m_c_status_00", 710103, 256, 256);
		ReplaceTex("MIS_C_EN", "m_c_status_01", "traducidos", "m_c_status_01", 710103, 256, 256);
		ReplaceTex("MIS_C_EN", "m_c_status_02", "traducidos", "m_c_status_02", 710103, 256, 256);
		ReplaceTex("MIS_C_EN", "m_c_status_03", "traducidos", "m_c_status_03", 710103, 256, 256);
		ReplaceTex("MIS_C_EN", "m_c_status_04", "traducidos", "m_c_status_04", 710103, 128, 128);
		ReplaceTex("MIS_C_EN", "m_c_status_05", "traducidos", "m_c_status_05", 710103, 128, 128);
		ReplaceTex("MIS_C_EN", "m_c_status_06", "traducidos", "m_c_status_06", 710103, 128, 128);
		ReplaceTex("MIS_C_EN", "m_c_status_07", "traducidos", "m_c_status_07", 710103, 128, 128);
		ReplaceTex("MILESRACE", "youwin0", "traducidos", "youwin0", 800, 32, 32);
		ReplaceTex("MILESRACE", "youwin1", "traducidos", "youwin1", 801, 32, 32);
		ReplaceTex("MILESRACE", "youwin2", "traducidos", "youwin2", 802, 32, 32);
		ReplaceTex("MILESRACE", "youwin3", "traducidos", "youwin3", 803, 32, 32);
		ReplaceTex("MILESRACE", "youlose0", "traducidos", "youlose0", 804, 32, 32);
		ReplaceTex("MILESRACE", "youlose1", "traducidos", "youlose1", 805, 32, 32);
		ReplaceTex("MILESRACE", "youlose2", "traducidos", "youlose2", 806, 32, 32);
		ReplaceTex("MILESRACE", "youlose3", "traducidos", "youlose3", 807, 32, 32);
		ReplaceTex("MP_10000_POLICE", "611000", "traducidos", "611000", 611007, 128, 128);
		ReplaceTex("MP_10000_POLICE", "611010", "traducidos", "611010", 611016, 128, 128);
		ReplaceTex("OBJ_CASINO9", "cas_moniter08", "traducidos", "cas_moniter08", 95613, 32, 32);
		ReplaceTex("OBJ_CASINO9", "cas_map", "traducidos", "cas_map", 95622, 128, 128);
		ReplaceTex("OBJ_MINI_CART", "cart_lap0", "traducidos", "cart_lap0", 324038, 64, 32);
		ReplaceTex("OBJ_MINI_CART", "hyoji_head_cart", "traducidos", "hyoji_head_cart", 324043, 64, 64);
		ReplaceTex("OBJ_MINI_CART", "hyoji_lap1", "traducidos", "hyoji_lap1", 324044, 64, 32);
		ReplaceTex("OBJ_MINI_CART", "hyoji_lap2", "traducidos", "hyoji_lap2", 324045, 64, 32);
		ReplaceTex("OBJ_MINI_CART", "hyoji_lap3", "traducidos", "hyoji_lap3", 324046, 64, 32);
		ReplaceTex("OBJ_MINI_CART", "hyoji_lap4", "traducidos", "hyoji_lap3", 324047, 64, 32);
		ReplaceTex("OBJ_SS", "exit6", "traducidos", "exit6", 206584, 64, 64);
		ReplaceTex("OBJ_SS", "circuit02", "traducidos", "circuit02", 206600, 128, 128);
		ReplaceTex("OBJ_SS", "twkanbanmoji04", "traducidos", "twkanbanmoji04", 206347, 64, 64);
		ReplaceTex("OBJ_SS", "twkanbanmoji01", "traducidos", "twkanbanmoji01", 206349, 128, 128);
		ReplaceTex("OBJ_SS", "s1rsolta", "traducidos", "s1rsolta", 206411, 32, 32);
		ReplaceTex("OBJ_SS", "min_pass9", "traducidos", "min_pass9", 206555, 64, 64);
		ReplaceTex("SEGALOGO_E", "segalogo0", "traducidos", "segalogo0", 9420000, 256, 256);
		ReplaceTex("SEGALOGO_E", "segalogo1", "traducidos", "segalogo1", 9420001, 256, 256);
		ReplaceTex("SEGALOGO_E", "segalogo2", "traducidos", "segalogo2", 9420002, 256, 256);
		ReplaceTex("SEGALOGO_E", "segalogo3", "traducidos", "segalogo3", 9420003, 256, 256);
		ReplaceTex("SEGALOGO_E", "segalogo4", "traducidos", "segalogo4", 9420004, 256, 256);
		ReplaceTex("SEGALOGO_E", "segalogo5", "traducidos", "segalogo5", 9420005, 256, 256);
		ReplaceTex("SEGALOGO_E", "stlogo1", "traducidos", "stlogo1", 100000017, 256, 256);
		ReplaceTex("SEGALOGO_E", "stlogo4", "traducidos", "stlogo4", 100000020, 256, 256);
		ReplaceTex("SS_KANBAN", "s1kan_d", "traducidos", "s1kan_d", 204600, 64, 64);
		ReplaceTex("SS_KANBAN", "s1kan_n", "traducidos", "s1kan_n", 204602, 64, 64);
		ReplaceTex("SS_TWINS", "park4", "traducidos", "park4", 204750, 128, 128);
		ReplaceTex("SS_TWINS", "circuit02", "traducidos", "circuit02", 204751, 128, 128);
		ReplaceTex("SSCAR", "sspd", "traducidos", "sspd", 204505, 64, 64);
		ReplaceTex("TUTO_CMN_E", "title_game_setu_e", "traducidos", "title_game_setu_e", 10000451, 256, 32);
		ReplaceTex("TUTO_CMN_E", "title_sousa_setu_e", "traducidos", "title_sousa_setu_e", 10000452, 512, 32);

		if (DCconversion)
		{
			ReplaceTex("ADV_MR00", "mr_064o_kbn01", "traducidos", "mr_064o_kbn01", 227477, 64, 64);
			ReplaceTex("ADV_MR00", "mr_128o_kbn02", "traducidos", "mr_128o_kbn02", 227609, 128, 128);
			ReplaceTex("ADVSS00", "du64pos04", "traducidos", "du64pos04", 206022, 64, 64);
			ReplaceTex("ADVSS00", "du64pos01", "traducidos", "du64pos01", 206020, 64, 64);
			ReplaceTex("ADVSS00", "mark_cityoffice", "traducidos", "mark_cityoffice", 206430, 64, 64);
			ReplaceTex("ADVSS01", "bst_swb", "traducidos", "bst_swb", 206236, 128, 128);
			ReplaceTex("ADVSS03", "ss_kiosk10", "traducidos", "ss_kiosk10", 206696, 64, 64);
			ReplaceTex("ADVSS03", "ekiname02", "traducidos", "ekiname02", 206649, 128, 128);
			ReplaceTex("ADVSS03", "du64pos01", "traducidos", "du64pos01", 206020, 64, 64);
			ReplaceTex("AVA_GTITLE0_DC", "hyoji_pressstart", "traducidos", "pressstart", 10000106, 256, 32);
			ReplaceTex("AVA_GTITLE0_DC_HD", "pressstart", "traducidos", "pressstart", 3489661269, 256, 32);
			ReplaceTex("AVA_SNDTEST_E", "ST_AB", "traducidos", "ST_AB", 10000526, 512, 64);
			ReplaceTex("CASINO01", "cas_map", "traducidos", "cas_map", 95622, 128, 128);
			ReplaceTex("EGM1LAND", "mr_128o_kbn02", "traducidos", "mr_128o_kbn02", 229033, 128, 128);
			ReplaceTex("EGM2_TIKEI", "bst_swb", "traducidos", "bst_swb", 1087083, 128, 128);
			ReplaceTex("TUTO_CMN_E", "bar_ab", "traducidos", "bar_ab", 10000527, 512, 32);
		}
		else
		{
			ReplaceTex("ADV_MR00", "mr_128o_kbn02", "traducidos", "mr_128o_kbn02", 821034, 128, 128);
			ReplaceTex("ADVSS00", "du64pos04", "traducidos", "du64pos04", 103, 64, 64);
			ReplaceTex("ADVSS00", "du64pos01", "traducidos", "du64pos01", 108, 64, 64);
			ReplaceTex("ADVSS00", "mark_cityoffice", "traducidos", "mark_cityoffice", 116, 64, 64);
			ReplaceTex("ADVSS00", "ss_kanban3", "traducidos", "ss_kanban3", 15, 64, 64);
			ReplaceTex("ADVSS00", "ss_kanban4", "traducidos", "ss_kanban4", 17, 64, 64);
			ReplaceTex("ADVSS00", "st1_1", "traducidos", "st1_1", 16, 64, 64);
			ReplaceTex("ADVSS01", "bst_swb", "traducidos", "bst_swb", 82, 64, 64);
			ReplaceTex("ADVSS01", "casinom_kanban", "traducidos", "casinom_kanban", 169, 128, 128);
			ReplaceTex("ADVSS01", "denkou", "traducidos", "denkou", 218, 128, 128);
			ReplaceTex("ADVSS03", "ss_kiosk10", "traducidos", "ss_kiosk10", 167, 64, 64);
			ReplaceTex("ADVSS03", "ekiname02", "traducidos", "ekiname02DX", 169, 128, 128);
			ReplaceTex("ADVSS03", "oda_ekiname02", "traducidos", "oda_ekiname02", 151, 128, 128);
			ReplaceTex("ADVSS03", "oda_ss_pos01", "traducidos", "du64pos01", 109, 64, 64);
			ReplaceTex("ADVSS03", "oda_ss_tex20", "traducidos", "oda_ss_tex20", 54, 128, 128);
			ReplaceTex("ADVSS03", "ss_tex_60", "traducidos", "ss_tex_60", 36, 128, 128);
			ReplaceTex("AVA_SNDTEST_E", "ST_AB", "traducidos", "ST_ABDX", 10000526, 512, 64);
			ReplaceTex("CASINO01", "cas_map", "traducidos", "cas_map", 97, 128, 128);
			ReplaceTex("EGM1LAND", "mr_064o_kbn01", "traducidos", "mr_064o_kbn01", 824549, 128, 128);
			ReplaceTex("EGM1LAND", "mr_128o_kbn02", "traducidos", "mr_128o_kbn02", 824520, 128, 128);
			ReplaceTex("EGM2_TIKEI", "bst_swb", "traducidos", "bst_swb", 69, 128, 128);
			ReplaceTex("EGM2_TIKEI", "casinom_kanban", "traducidos", "casinom_kanban", 172, 128, 128);
			ReplaceTex("EGM2_TIKEI", "denkou", "traducidos", "denkou", 222, 128, 128);
			ReplaceTex("TUTO_CMN_E", "bar_ab", "traducidos", "bar_abDX", 10000527, 512, 32);
		}

		ReplacePVM("PRESSSTART", "PRESSSTART_sp");
		ReplacePVM("PRESSSTART_DC", "PRESSSTART_dcsp");
		ReplacePVM("PRESSSTART_HD", "PRESSSTART_dcsp");
		ReplacePVM("SCORE_ACT_E", "SCORE_ACT_E_sp");
		ReplacePVM("SCORE_ACT_E_DC", "SCORE_ACT_E_sp");
		ReplacePVM("SCORE_ACT_E_HD", "SCORE_ACT_E_sp");
		ReplacePVM("SCORE_BOARD_E", "SCORE_BOARD_E_sp");
		ReplacePVM("SCORE_BOARD_E_DC", "SCORE_BOARD_E_sp");
		ReplacePVM("SCORE_BOARD_E_HD", "SCORE_BOARD_E_sp");
		ReplacePVM("SCORE_BOSS_E", "SCORE_BOSS_E_sp");
		ReplacePVM("SCORE_BOSS_E_DC", "SCORE_BOSS_E_sp");
		ReplacePVM("SCORE_BOSS_E_HD", "SCORE_BOSS_E_sp");
		ReplacePVM("SCORE_CART_E", "SCORE_CART_E_sp");
		ReplacePVM("SCORE_CART_E_DC", "SCORE_CART_E_sp");
		ReplacePVM("SCORE_CART_E_HD", "SCORE_CART_E_sp");
		ReplacePVM("SCORE_MOLE_E", "SCORE_MOLE_E_sp");
		ReplacePVM("SCORE_MOLE_E_DC", "SCORE_MOLE_E_sp");
		ReplacePVM("SCORE_MOLE_E_HD", "SCORE_MOLE_E_sp");
		ReplacePVM("SCORE_RESULT_E", "SCORE_RESULT_E_sp");
		ReplacePVM("SCORE_RESULT_E_DC", "SCORE_RESULT_E_sp");
		ReplacePVM("SCORE_RESULT_E_HD", "SCORE_RESULT_E_sp");
		ReplacePVM("SCORE_SHOOT_E", "SCORE_SHOOT_E_sp");
		ReplacePVM("SCORE_SHOOT_E_DC", "SCORE_SHOOT_E_sp");
		ReplacePVM("SCORE_SHOOT_E_HD", "SCORE_SHOOT_E_sp");

		if (MusicaDub)
		{
			helperFunctions.ReplaceFile("system\\sounddata\\bgm\\wma\\chaos_p1.wma", "system\\sounddata\\bgm\\wma\\chaos_p1_s.wma");
			helperFunctions.ReplaceFile("system\\sounddata\\bgm\\wma\\mainthem.wma", "system\\sounddata\\bgm\\wma\\mainthem_s.wma");
			helperFunctions.ReplaceFile("system\\sounddata\\bgm\\wma\\sprsonic.wma", "system\\sounddata\\bgm\\wma\\sprsonic_s.wma");
		}
		
		if (Dub == Mexicano)
		{
			helperFunctions.ReplaceFile("system\\sounddata\\voice_us\\wma\\0244.wma", "system\\sounddata\\voice_us\\wma\\0244m.wma");
			helperFunctions.ReplaceFile("system\\sounddata\\voice_us\\wma\\0251.wma", "system\\sounddata\\voice_us\\wma\\0251m.wma");
			helperFunctions.ReplaceFile("system\\sounddata\\voice_us\\wma\\0866.wma", "system\\sounddata\\voice_us\\wma\\0866m.wma");
		}
		else if (Dub == Chileno)
		{
			helperFunctions.ReplaceFile("system\\sounddata\\voice_us\\wma\\0244.wma", "system\\sounddata\\voice_us\\wma\\0244c.wma");
			helperFunctions.ReplaceFile("system\\sounddata\\voice_us\\wma\\0606.wma", "system\\sounddata\\voice_us\\wma\\0606c.wma");
			helperFunctions.ReplaceFile("system\\sounddata\\voice_us\\wma\\0681.wma", "system\\sounddata\\voice_us\\wma\\0681c.wma");
			helperFunctions.ReplaceFile("system\\sounddata\\voice_us\\wma\\1034.wma", "system\\sounddata\\voice_us\\wma\\1034c.wma");
			helperFunctions.ReplaceFile("system\\sounddata\\voice_us\\wma\\1068.wma", "system\\sounddata\\voice_us\\wma\\1068c.wma");
			helperFunctions.ReplaceFile("system\\sounddata\\voice_us\\wma\\1087.wma", "system\\sounddata\\voice_us\\wma\\1087c.wma");
		}
		else
		{
			return;
		}
	}

	__declspec(dllexport) void __cdecl OnFrame()
	{
		VoiceVolume = VoiceVolumeConv;
		VoiceVolumeBK = VoiceVolumeConv;
		if (!CreditsLoaded)
		{
			if (DCconversion)
			{
				LoadSA1DCCredits();
			}
			CreditsLoaded = true;
		}
	}
	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}