#ifndef GAMELANGUAGE_H_INCLUDED
#define GAMELANGUAGE_H_INCLUDED

/*
 * This file allows you to define the languages you want to use in the game.
 * To use a language you must define a array. the first index represents the first language
 * (e.g lang_array[0] => eng) and the index following its translation (e.g lang_array[1] => fr).
 *
 * example to display several sentences in the dialog manager.
 * lang_array[] = {"eng 1", "translation fr 1", "eng 2", "translation fr 2", ...};
 * (Go to the GameDialog Class to see how we implement languages to make sentences in dialogs)
 */

namespace is
{
//////////////////////////////////////////////////////
/// \brief Access to content that allows internationalization of the game
///
//////////////////////////////////////////////////////
namespace lang
{
////////////////////////////////////////////////////////////
/// \brief Represent the index of each language
///
////////////////////////////////////////////////////////////
enum GameLanguage
{
    ENGLISH,  ///< English language index
    FRANCAIS, ///< French language index
};

// ------------------------ message box answer ------------------------
static std::string pad_answer_ok[] = {"OK", "OK"};
static std::string pad_answer_yes[] = {"YES", "OUI"};
static std::string pad_answer_no[]  = {"NO", "NON"};
// ------------------------ intro ------------------------
static std::string pad_game_language[] = {"English", "French"};

// ------------------------ menu ------------------------
static std::string pad_main_menu[] = {"Main Menu", "Menu Principal"};
static std::string pad_new_game[] = {"New Level", "Nouveau Niveau"};
static std::string pad_continue_game[] = {"Load Level", "Charger Niveau"};

static std::string opt_enable_sound[]      = {"Enable SOUND : YES",        "Activer SON : OUI"};
static std::string opt_disable_sound[]     = {"Enable SOUND : NO",         "Activer SON : NON"};
static std::string opt_enable_load_tex[]   = {"Enable LOAD TEXTURE : YES", "Activer CHARGER TEXTURE : OUI"};
static std::string opt_disable_load_tex[]  = {"Enable LOAD TEXTURE : NO",  "Activer CHARGER TEXTURE : NON"};
static std::string opt_enable_auto_save[]  = {"Enable AUTO SAVE : YES",    "Activer SAUVEGARDE AUTO : OUI"};
static std::string opt_disable_auto_save[] = {"Enable AUTO SAVE : NO",     "Activer SAUVEGARDE AUTO : NON"};
static std::string opt_game_lang[]         = {"Language : ENGLISH",        "Langue : FRANCAIS"};

static std::string msg_quit_game[] = {"Quit Level Editor?", "Quitter l'Editeur de niveau?"};

// ------------------------ menu pause ------------------------
static std::string pad_restart_game[] = {"Restart Game", "Recommencer"};
static std::string pad_quit_game[] = {"Quit Game", "Quitter le Jeu"};

// ------------------------ menu list ------------------------
static std::wstring pad_insert_block[] = {L"Insert Block", L"Inserer Bloc"};
static std::wstring pad_insert_bonus[] = {L"Insert Bonus", L"Inserer Bonus"};
static std::wstring pad_insert_enemy[] = {L"Insert Enemy", L"Inserer Enemmi"};
static std::wstring pad_insert_player[] = {L"Insert Player", L"Inserer Joueur"};
static std::wstring pad_insert_gameplay[] = {L"Insert Gameplay Obj.", L"Inserer Obj. Gameplay"};
static std::wstring pad_insert_tiles[] = {L"Insert Tiles", L"Inserer Tuiles"};
static std::wstring pad_clear_tiles[] = {L"Clear Object", L"Effacer Objet "};
static std::wstring pad_save_level[] = {L"Save Level", L"Sauvegarder Niveau"};
static std::wstring pad_save_header[] = {L"Export Level", L"Exporter Niveau"};
static std::wstring pad_reload_level[] = {L"Reload Level", L"Recharger Niveau"};
static std::wstring pad_quit_editor[] = {L"Quit", L"Quitter"};

static std::wstring msg_reload_map[] = {L"Reload level?",
                                            L"Recharger le niveau?"};
static std::wstring msg_quit_editor[] = {L"Quit Editor?\n(Data not saved will be lost)",
                                            L"Quitter l'Editeur?"};
}
}
#endif // GAMELANGUAGE_H_INCLUDED
