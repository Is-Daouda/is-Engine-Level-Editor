#include "Intro.h"

Intro::Intro(sf::RenderWindow &window, sf::View &view, sf::RenderTexture &surface, is::GameSystemExtended &gameSysExt):
    GameDisplay(window, view, surface, gameSysExt, sf::Color::White),
    Step(),
    m_recScale(0.f),
    m_isOnPad(false)
{
    is::createRectangle(m_recChooseLanguage, sf::Vector2f(650.f, 190.f), sf::Color(0, 0, 0), 320.f, 240.f, true);
    is::setSFMLObjScale(m_recChooseLanguage, m_recScale);
}

void Intro::step()
{
    // DELTA_TIME
    DELTA_TIME = getDeltaTime();

    // even loop
    sf::Event event;
    while (m_window.pollEvent(event)) controlEventFocusClosing(event);

    // Camera
    setView();

    if (m_windowIsActive)
    {
        updateTimeWait(DELTA_TIME);

        // intro step
        switch(m_step)
        {
            case 0:
                {
                    bool mouseInCollison(false);
                    is::increaseVar(DELTA_TIME, m_recScale, 0.08f, 1.f, 1.f);

                    if (!m_gameSysExt.isPressed()) m_gameSysExt.m_keyIsPressed = false;

                    if (mouseCollision(m_sprButtonSelect)) mouseInCollison = true;
                    else if (mouseCollision(m_sprPadFr)) mouseInCollison = true;
                    else m_isOnPad = false;

                    if (!mouseInCollison && m_gameSysExt.isPressed()) m_gameSysExt.m_keyIsPressed = true;
                    auto tempFnct = [this](int index)
                    {
                        m_optionIndex = index;
                        m_isOnPad = true;
                    };

                    if (!m_isOnPad)
                    {
                        if (mouseCollision(m_sprButtonSelect)) tempFnct(is::lang::GameLanguage::ENGLISH);
                        else if (mouseCollision(m_sprPadFr)) tempFnct(is::lang::GameLanguage::FRANCAIS);
                    }

                    if ((m_gameSysExt.keyIsPressed(is::GameConfig::KEY_VALIDATION_KEYBOARD) ||
                        (m_gameSysExt.isPressed() && mouseInCollison)) &&
                        (m_waitTime == 0 && !m_gameSysExt.m_keyIsPressed))
                    {
                        GSMplaySound("select_option");
                        m_gameSysExt.useVibrate(m_vibrateTimeDuration);
                        m_gameSysExt.m_gameLanguage = m_optionIndex;
                        m_gameSysExt.m_firstLaunch = false;
                        m_gameSysExt.saveConfig(is::GameConfig::CONFIG_FILE);
                        m_step++;
                    }
                }
            break;


            case 1:
                m_isRunning = false;  // quit the scene main loop
                m_gameSysExt.m_launchOption = is::DisplayOption::MAIN_MENU;  // go to main menu scene
                m_step++;
            break;
        }
        is::setSFMLObjScale(m_recChooseLanguage, m_recScale);
    }
}

void Intro::draw()
{
    m_surface.draw(m_recChooseLanguage);
    m_surface.draw(m_sprButtonSelect);
    m_surface.draw(m_sprPadFr);
    m_surface.draw(m_txtChooseLanguage);
    m_surface.draw(m_txtLangEng);
    m_surface.draw(m_txtLangFr);
}

void Intro::loadResources()
{
    GameDisplay::loadParentResources();
    m_gameSysExt.loadConfig(is::GameConfig::CONFIG_FILE);

    if (m_gameSysExt.m_firstLaunch)
    {
        is::loadSFMLObjResource(m_texPad, is::GameConfig::GUI_DIR + "main_menu_pad.png");
        is::loadSFMLObjResource(m_fontTitle, is::GameConfig::FONT_DIR + "space_ranger_3d_mp_pv.otf");

        is::createWText(m_fontTitle, m_txtChooseLanguage, L"Choose Language", 0.f, 0.f, sf::Color(255, 255, 255), 48);
        is::centerSFMLObj(m_txtChooseLanguage);
        is::setSFMLObjX_Y(m_txtChooseLanguage, m_viewX, m_viewY - 90.f);

        // create sprites
        float btX(230.f), btY(205.f);
        is::createSprite(m_texPad, m_sprButtonSelect, sf::IntRect(192, 0, 192, 48), sf::Vector2f(btX, btY), sf::Vector2f(96.f, 24.f));
        is::createSprite(m_texPad, m_sprPadFr, sf::IntRect(192, 0, 192, 48), sf::Vector2f(btX, btY + 66.f), sf::Vector2f(96.f, 24.f));
        is::createText(m_fontSystem, m_txtLangEng, is::lang::pad_game_language[is::lang::GameLanguage::ENGLISH],
                       is::getSFMLObjX(m_sprButtonSelect), is::getSFMLObjY(m_sprButtonSelect) - 6.f, sf::Color(255, 255, 255), true, 25);
        is::createText(m_fontSystem, m_txtLangFr, is::lang::pad_game_language[is::lang::GameLanguage::FRANCAIS],
                       is::getSFMLObjX(m_sprPadFr), is::getSFMLObjY(m_sprPadFr) - 6.f, sf::Color(255, 255, 255), true, 25);
    }
    else
    {
        m_windowBgColor = sf::Color::Black;
        m_isRunning = false;
        m_gameSysExt.m_launchOption = is::DisplayOption::MAIN_MENU;
    }
}
