#include "LevelEditor.h"

void LevelEditor::loadResources()
{
#if defined(IS_ENGINE_SDL_2)
        m_txtMsgBox.m_SDLaddTextRecWSize += 10;
#endif
    GameDisplay::loadParentResources();

    // allow to show level information
    is::createText(getFontSystem(), m_txtLevelEditorInfo, "", 0.f, 0.f, 16);

    // create item list
    is::createText(getFontSystem(), m_txtItemMenuList[0], is::lang::pad_insert_block[m_gameSysExt.m_gameLanguage],
                    0.f, 0.f, sf::Color::Black, 16);
    is::createText(getFontSystem(), m_txtItemMenuList[1], is::lang::pad_insert_bonus[m_gameSysExt.m_gameLanguage],
                    0.f, 0.f, sf::Color::Black, 16);
    is::createText(getFontSystem(), m_txtItemMenuList[2], is::lang::pad_insert_enemy[m_gameSysExt.m_gameLanguage],
                    0.f, 0.f, sf::Color::Black, 16);
    is::createText(getFontSystem(), m_txtItemMenuList[3], is::lang::pad_insert_player[m_gameSysExt.m_gameLanguage],
                    0.f, 0.f, sf::Color::Black, 16);
    is::createText(getFontSystem(), m_txtItemMenuList[4], is::lang::pad_insert_gameplay[m_gameSysExt.m_gameLanguage],
                    0.f, 0.f, sf::Color::Black, 16);
    is::createText(getFontSystem(), m_txtItemMenuList[5], is::lang::pad_insert_tiles[m_gameSysExt.m_gameLanguage],
                    0.f, 0.f, sf::Color::Black, 16);
    is::createText(getFontSystem(), m_txtItemMenuList[6], is::lang::pad_clear_tiles[m_gameSysExt.m_gameLanguage],
                    0.f, 0.f, sf::Color::Black, 16);
    is::createText(getFontSystem(), m_txtItemMenuList[7], is::lang::pad_save_level[m_gameSysExt.m_gameLanguage],
                    0.f, 0.f, sf::Color::Black, 16);
    is::createText(getFontSystem(), m_txtItemMenuList[8], is::lang::pad_save_header[m_gameSysExt.m_gameLanguage],
                    0.f, 0.f, sf::Color::Black, 16);
    is::createText(getFontSystem(), m_txtItemMenuList[9], is::lang::pad_reload_level[m_gameSysExt.m_gameLanguage],
                    0.f, 0.f, sf::Color::Black, 16);
    is::createText(getFontSystem(), m_txtItemMenuList[10], is::lang::pad_quit_editor[m_gameSysExt.m_gameLanguage],
                    0.f, 0.f, sf::Color::Black, 16);

    for (unsigned int i(0); i < is::arraySize(m_recItemMenuList); i++)
    {
        is::createRectangle(m_recItemMenuList[i],
                            sf::Vector2f((m_gameSysExt.m_gameLanguage == is::lang::FRANCAIS) ? 164.f : 152.f, 30.f),
                            sf::Color::White);
        is::setSFMLObjOutlineColor(m_recItemMenuList[i], sf::Color::Black, 0.5f);
    }

    GRMaddTexture("tools_pad", is::GameConfig::GUI_DIR + "tools_pad.png");

    // GUI resources
    GRMaddTexture("pad", is::GameConfig::GUI_DIR + "option_pad.png");

    // sprites
    auto &cursor = GRMaddTexture("cursor", is::GameConfig::SPRITES_DIR + "cursor.png");

    // background
    auto &grid = GRMaddTexture("gridCaseBg", is::GameConfig::SPRITES_DIR + "grid_case.png");

    if (m_texBlockPath == "") m_texBlockPath       = is::GameConfig::SPRITES_DIR + "block.png";
    if (m_texPlayerPath == "") m_texPlayerPath     = is::GameConfig::SPRITES_DIR + "player.png";
    if (m_texGameplayPath == "") m_texGameplayPath = is::GameConfig::SPRITES_DIR + "gameplay.png";
    if (m_texBonusPath == "") m_texBonusPath       = is::GameConfig::SPRITES_DIR + "bonus.png";
    if (m_texEnemyPath == "") m_texEnemyPath       = is::GameConfig::SPRITES_DIR + "enemy.png";
    if (m_texTilesPath == "") m_texTilesPath       = is::GameConfig::SPRITES_DIR + "tiles.png";

    // if the textures were loaded successfully then we integrate them into the level editor
    // to choose them as tiles in order to build the scene
    m_cursor.loadResources(&cursor,
                           ((!m_texBlock.loadFromFile(m_texBlockPath))       ? nullptr : &m_texBlock),
                           ((!m_texBonus.loadFromFile(m_texBonusPath))       ? nullptr : &m_texBonus),
                           ((!m_texEnemy.loadFromFile(m_texEnemyPath))       ? nullptr : &m_texEnemy),
                           ((!m_texPlayer.loadFromFile(m_texPlayerPath))     ? nullptr : &m_texPlayer),
                           ((!m_texGameplay.loadFromFile(m_texGameplayPath)) ? nullptr : &m_texGameplay),
                           ((!m_texTiles.loadFromFile(m_texTilesPath))       ? nullptr : &m_texTiles));

    // set level data
    if (!loadLevelEditor())
    {
    	#if !defined(SFML_SYSTEM_LINUX) && !defined(IS_ENGINE_LINUX)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        #endif
        is::showLog("\n------------------------------------------------------------------");
        is::showLog(" ! Click on the console to enter the information for the level !");
        is::showLog("------------------------------------------------------------------");
        is::showLog("Enter the Level Width  (1 = 32 pixels) : ");
        std::cin >> m_levelWidth;
        is::showLog("Enter the Level Height (1 = 32 pixels) : ");
        std::cin >> m_levelHeight;
        is::showLog("Enter the Level Name (Please avoid the space \" \" character) : ");
        bool errorInLevelEditorName(true);
        while(errorInLevelEditorName)
        {
            bool error(false);
            std::getline(std::cin, m_levelName);
            for (auto &x : m_levelName)
            {
                if (x == ' ')
                {
                    error = true;
                    is::showLog("Please try again ! (Please avoid the space \" \" character) : ");
                }
                errorInLevelEditorName = error;
            }
        }

        // we display the option which allows the user to load these own textures if it has been activated in "Main Menu"
        if (m_gameSysExt.m_enableLoadTex)
        {
            // load texture
            if (is::TinyDialogBox::showDialogBox("Load Texture",
                                                 "Use your own texture to create level objects?",
                                                 is::TinyDialogBox::DialogType::YESNO,
                                                 is::TinyDialogBox::IconType::QUESTION) == 1)
            {
                tinyString lFilterPatterns[2] = {
                                                #if !defined(SFML_SYSTEM_LINUX) && !defined(IS_ENGINE_LINUX)
                                                L"*.png", L"*.PNG"
                                                #else
                                                "*.png", "*.PNG"
                                                #endif
                                                };
                m_texBlockPath = is::TinyDialogBox::showFileDialogBox(is::TinyDialogBox::FileDialogType::LOAD_FILE,
                                                                       "Load Block texture file",
                                                                       lFilterPatterns,
                                                                       "",
                                                                       "Can't load Block texture!");
                m_texBonusPath = is::TinyDialogBox::showFileDialogBox(is::TinyDialogBox::FileDialogType::LOAD_FILE,
                                                                       "Load Bonus texture file",
                                                                       lFilterPatterns,
                                                                       "",
                                                                       "Can't load Bonus texture!");
                m_texEnemyPath = is::TinyDialogBox::showFileDialogBox(is::TinyDialogBox::FileDialogType::LOAD_FILE,
                                                                       "Load Enemy texture file",
                                                                       lFilterPatterns,
                                                                       "",
                                                                       "Can't load Enemy texture!");
                m_texPlayerPath = is::TinyDialogBox::showFileDialogBox(is::TinyDialogBox::FileDialogType::LOAD_FILE,
                                                                       "Load Player texture file",
                                                                       lFilterPatterns,
                                                                       "",
                                                                       "Can't load Player texture!");
                m_texGameplayPath = is::TinyDialogBox::showFileDialogBox(is::TinyDialogBox::FileDialogType::LOAD_FILE,
                                                                       "Load Gameplay object texture file",
                                                                       lFilterPatterns,
                                                                       "",
                                                                       "Can't load Gameplay object texture!");
                m_texTilesPath = is::TinyDialogBox::showFileDialogBox(is::TinyDialogBox::FileDialogType::LOAD_FILE,
                                                                       "Load Tiles texture file",
                                                                       lFilterPatterns,
                                                                       "",
                                                                       "Can't load Tiles texture!");
            }
        }

        if (m_levelWidth < m_viewW / 32) m_levelWidth = m_viewW / 32;
        if (m_levelHeight < m_viewH / 32) m_levelHeight = m_viewH / 32;
        createGridCase();
        #if !defined(SFML_SYSTEM_LINUX) && !defined(IS_ENGINE_LINUX)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        #endif
        is::showLog("\n------------------------------------------------------------------");
        is::showLog("   ! Now you can click on the level editor windows to continue !");
        is::showLog("------------------------------------------------------------------");
#if defined(IS_ENGINE_SFML)
        m_window.requestFocus();
#endif
    }

    // level information
    is::showLog("\nLevel Name        : " + m_levelName +
                "\nLevel Width       : " + is::numToStr(m_levelWidth * 32)  + " (" + is::numToStr(m_levelWidth)  + ")" +
                "\nLevel Height      : " + is::numToStr(m_levelHeight * 32) + " (" + is::numToStr(m_levelHeight) + ")" +
                "\nCase Number       : " + is::numToStr(m_gridCaseList.size()) +
                "\n");

//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      BUILD THE BACKGROUND OF LEVEL
//////////////////////////////////////////////////////////////////////////////////////////////////////
    is::createSprite(grid, m_sprGridCaseBg, sf::IntRect(0, 0, 640, 480), sf::Vector2f(m_viewX - 320.f, m_viewY - 240.f),
                     sf::Vector2f(0.f, 0.f), true);

//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      CREATION OF THE LEVEL
//////////////////////////////////////////////////////////////////////////////////////////////////////

    // set view position in relation to player
    m_viewX = m_cursor.getX();
    m_viewY = m_cursor.getY();

    if (m_viewX < m_viewW / 2) m_viewX = m_viewW / 2;
    if (m_viewX > static_cast<float>(m_levelWidth) * 32.f - m_viewW / 2)
        m_viewX = static_cast<float>(m_levelWidth) * 32.f - m_viewW / 2;

    if (m_viewY < m_viewH / 2) m_viewY = m_viewH / 2;
    if (m_viewY > static_cast<float>(m_levelHeight) * 32.f - m_viewH / 2)
        m_viewY = static_cast<float>(m_levelHeight) * 32.f - m_viewH / 2;

    // set view param
    setView();
}
