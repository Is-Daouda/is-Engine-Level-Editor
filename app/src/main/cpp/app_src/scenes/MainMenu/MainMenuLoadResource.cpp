#include "MainMenu.h"

void MainMenu::loadResources()
{
    GameDisplay::loadParentResources();

    // load textures
    is::loadSFMLObjResource(m_texPad, is::GameConfig::GUI_DIR + "main_menu_pad.png");
    is::loadSFMLObjResource(m_texPad2, is::GameConfig::GUI_DIR + "option_pad.png");
    is::loadSFMLObjResource(m_texScreenBG, is::GameConfig::GUI_DIR + "screen_background.png");

    // font
    is::loadSFMLObjResource(m_fontTitle, is::GameConfig::FONT_DIR + "space_ranger_3d_mp_pv.otf");

    // load configuration file
    if (m_gameSysExt.fileExist(is::GameConfig::CONFIG_FILE)) m_gameSysExt.loadConfig(is::GameConfig::CONFIG_FILE);

    // game title
    is::createWText(m_fontTitle, m_txtGameTitle, is::GameConfig::GAME_NAME,
                    0.f, 0.f, sf::Color(0, 0, 0), 64);

    float distance(5.f), widgetSpace(65.f);

    // create sprites
    is::createSprite(m_texPad, m_sprPad1, sf::IntRect(0, 0, 192, 48), sf::Vector2f(m_xPos, m_yPos + distance), sf::Vector2f(96.f, 24.f));
    is::createSprite(m_texPad, m_sprPad2, sf::IntRect(0, 0, 192, 48), sf::Vector2f(m_xPos, m_yPos + widgetSpace + distance), sf::Vector2f(96.f, 24.f));
    is::createSprite(m_texPad, m_sprButtonSelect, sf::IntRect(192, 0, 192, 48), sf::Vector2f(m_xPos, m_yPos + distance), sf::Vector2f(96.f, 24.f));
    float btYSize(0.9f);
    is::setSFMLObjScaleX_Y(m_sprPad1, 1.f, btYSize);
    is::setSFMLObjScaleX_Y(m_sprPad2, 1.f, btYSize);

    // sprite background
    is::createSprite(m_texScreenBG, m_sprScreenBG, sf::IntRect(0, 0, 672, 512),sf::Vector2f(m_bgX, m_bgY), sf::Vector2f(0.f , 0.f), true);

    // create text for main menu
    float const TXT_Y_ON_BT(8.f);
    int const _PAD_TXT_SIZE(22);
    is::createText(m_fontSystem, m_txtStartGame, is::lang::pad_new_game[m_gameSysExt.m_gameLanguage],
                   is::getSFMLObjX(m_sprPad1), is::getSFMLObjY(m_sprPad1) - TXT_Y_ON_BT, sf::Color::Blue, true, _PAD_TXT_SIZE);
    is::createText(m_fontSystem, m_txtContinue, is::lang::pad_continue_game[m_gameSysExt.m_gameLanguage],
                   is::getSFMLObjX(m_sprPad2), is::getSFMLObjY(m_sprPad2) - TXT_Y_ON_BT, true, _PAD_TXT_SIZE);

    // create text for game option
    int const _SIZE(22);
    float const _X_OPT(m_viewX - 64.f), _Y_OPT(m_viewY - 30.f), _OPT_SPACE(50.f);
    is::createText(m_fontSystem, m_txtOptionValue[0], is::lang::opt_enable_sound[m_gameSysExt.m_gameLanguage],
                   _X_OPT, _Y_OPT, sf::Color(sf::Color(0, 0, 0)), _SIZE);
    is::createText(m_fontSystem, m_txtOptionValue[1], is::lang::opt_enable_load_tex[m_gameSysExt.m_gameLanguage],
                   _X_OPT, _Y_OPT + _OPT_SPACE, sf::Color(sf::Color(0, 0, 0)), _SIZE);
    is::createText(m_fontSystem, m_txtOptionValue[2], is::lang::opt_enable_auto_save[m_gameSysExt.m_gameLanguage],
                   _X_OPT, _Y_OPT + _OPT_SPACE * 2.f, sf::Color(sf::Color(0, 0, 0)), _SIZE);
    is::createText(m_fontSystem, m_txtOptionValue[3], is::lang::opt_game_lang[m_gameSysExt.m_gameLanguage],
                   _X_OPT, _Y_OPT + _OPT_SPACE * 3.f, sf::Color(sf::Color(0, 0, 0)), _SIZE);
}
