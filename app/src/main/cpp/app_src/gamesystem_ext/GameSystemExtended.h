#ifndef GAMESYSTEMEXTENDED_H_INCLUDED
#define GAMESYSTEMEXTENDED_H_INCLUDED

#include "../../isEngine/system/function/GameFunction.h"
#include "../../isEngine/ext_lib/TinyFileDialogs/TinyDialogBox.h"
#include "../config/GameConfig.h"

////////////////////////////////////////////////////////////
/// \brief Class derived from GameSystem to manage the
/// different engine components
///
/// Allows to manage the saving / loading of game and
/// configuration data, manipulate the data of the virtual
/// Game Pad and act on the different scenes of the game
////////////////////////////////////////////////////////////
namespace is
{
class GameSystemExtended : public is::GameSystem
{
public:
    GameSystemExtended();

    /// Initialize the data link to the game engine
    void initSystemData();

    /// Save config data
    void saveConfig(std::string const &fileName)
    {
        FILE *file = NULL;
        file = fopen(fileName.c_str(), "wb");

        if (file != NULL)
        {
            fwrite(&m_enableSound, sizeof(bool), 1, file);
            fwrite(&m_enableLoadTex, sizeof(bool), 1, file);
            fwrite(&m_enableAutoSave, sizeof(bool), 1, file);
            fwrite(&m_gameLanguage, sizeof(int), 1, file);
            fwrite(&m_firstLaunch, sizeof(bool), 1, file);
            fclose(file);
        }
    }

    /// Load config data
    void loadConfig(std::string const &fileName)
    {
        FILE *file = NULL;
        file = fopen(fileName.c_str(), "rb");

        if (file != NULL)
        {
            fread(&m_enableSound, sizeof(bool), 1, file);
            fread(&m_enableLoadTex, sizeof(bool), 1, file);
            fread(&m_enableAutoSave, sizeof(bool), 1, file);
            fread(&m_gameLanguage, sizeof(int), 1, file);
            fread(&m_firstLaunch, sizeof(bool), 1, file);
            fclose(file);
        }
    }

    /// default filter patterns
    tinyString TINY_FILTER_PATTERNS[2] = {
                                             #if !defined(SFML_SYSTEM_LINUX)
                                             L"*.sav", L"*.save"
                                             #else
                                             "*.sav", "*.save"
                                             #endif
                                             };

    /// Allows to choose the scene that will be launched
    is::DisplayOption m_launchOption = is::GameConfig::LAUNCH_OPTION; // Represents the first scene to be launched

    bool  m_enableLoadTex;
    bool  m_enableAutoSave;
    std::string m_filePath;
};

}

#endif // GAMESYSTEMEXTENDED_H_INCLUDED
