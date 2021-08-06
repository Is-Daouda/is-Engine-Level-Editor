#include "MainMenu.h"

MainMenu::MainMenu(is::GameSystemExtended &gameSysExt):
    GameDisplay(gameSysExt, sf::Color::White),
    m_gameOptionIndex(0),
    m_oscillation(0.f),
    m_xPos(124.f),
    m_yPos(234.f),
    m_bgX(0.f),
    m_bgY(0.f),
    m_sprButtonPemuteScale(1.f),
    m_timeClick(0.f),
    m_isClicked(false),
    m_isStart(true),
    m_saveFileOpen(false),
    m_closeApplication(false)
{
    for (unsigned int i(0); i < is::arraySize(m_txtOptionValue); i++) m_txtOptionScale[i] = 1.f;
    m_gameSysExt.m_filePath = "";
    m_window.setTitle(is::GameConfig::GAME_NAME);

    // define cancel key
    m_keyBack = sf::Keyboard::Escape;
}

MainMenu::~MainMenu() {}

void MainMenu::step()
{
    DELTA_TIME = getDeltaTime();

    updateTimeWait();

    const short OP_START_GAME(0),
                OP_CONTINUE(1);
    const short OP_MENU_SND(0),
                OP_MENU_LOAD_TEX(1),
                OP_MENU_AUTO_SAVE(2),
                OP_MENU_LANG(3);

    // allow to know is mouse is in collision with sprite
    bool mouseInCollisonPad(false);
    bool mouseInCollison(false);

    // even loop
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        controlEventFocusClosing(event);

        if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == m_keyBack)
            {
                m_keyBackPressed = true;
            }
        }
    }

    // Camera
    setView();

    // starting mechanism
    if (m_isStart)
    {
        // window has focus
        if (m_windowIsActive)
        {
            if (!m_showMsg)
            {
                // allow key
                if (!m_gameSysExt.keyIsPressed(sf::Keyboard::Return) &&
                    !m_gameSysExt.isPressed()) m_gameSysExt.m_keyIsPressed = false;

                // m_isClose allow to deactivate scene object
                if (!m_isClose)
                {
//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      MAIN MENU
//////////////////////////////////////////////////////////////////////////////////////////////////////
                    if (mouseCollision(m_sprPad1) || mouseCollision(m_sprPad2)) mouseInCollisonPad = true;
                    if (mouseCollision(m_sprPad1) && m_optionIndex != OP_START_GAME)  setOptionIndex(OP_START_GAME, true);
                    if (mouseCollision(m_sprPad2) && m_optionIndex != OP_CONTINUE)    setOptionIndex(OP_CONTINUE, true);

                    // validate option
                    if ((m_gameSysExt.isPressed() && mouseInCollisonPad) && (m_waitTime == 0 && !m_gameSysExt.m_keyIsPressed))
                    {
                        auto playSelectSnd = [this]()
                        {
                            GSMplaySound("select_option");
                            m_sprButtonSelectScale = 1.4f;
                        };

                        switch (m_optionIndex)
                        {
                        case OP_START_GAME:
                            playSelectSnd();
                            m_gameSysExt.m_launchOption = is::DisplayOption::LEVEL_EDITOR;
                            m_isClose = true;
                        break;

                        // load current level saved
                        case OP_CONTINUE:
                            {
                                GSMplaySound("select_option");
                                m_gameSysExt.m_filePath = is::TinyDialogBox::showFileDialogBox(is::TinyDialogBox::LOAD_FILE,
                                                                                  "Load File",
                                                                                  m_gameSysExt.TINY_FILTER_PATTERNS);
                                if (m_gameSysExt.m_filePath != "")
                                {
                                    m_gameSysExt.m_launchOption = is::DisplayOption::LEVEL_EDITOR;
                                    m_isClose = true;
                                }
                            }
                        break;
                        }
                        m_keyBackPressed = false;
                    }

                    // Quit game
                    if (m_keyBackPressed)
                    {
                        showMessageBox(is::lang::msg_quit_game[m_gameSysExt.m_gameLanguage]);
                        m_closeApplication = true;
                        m_keyBackPressed = false;
                    }

//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      GAME OPTION
//////////////////////////////////////////////////////////////////////////////////////////////////////

                    // check collision with option objects
                    for (unsigned int i(0); i < is::arraySize(m_txtOptionValue); i++)
                    {
                        if (mouseCollision(m_txtOptionValue[i])) mouseInCollison = true;
                    }

                    // mouse hover effect
                    auto setTxtOpionScale = [this](short int m_txtOptionIndex)
                    {
                        //////////////////////////////////////////////////////////
                        #if !defined(__ANDROID__)
                        GSMplaySound("change_option");
                        #endif
                        //////////////////////////////////////////////////////////
                        m_txtOptionScale[m_txtOptionIndex] = 1.2f;
                        m_gameOptionIndex = m_txtOptionIndex;
                    };

                    if (mouseCollision(m_txtOptionValue[OP_MENU_SND]) && m_gameOptionIndex != OP_MENU_SND)
                    {
                        setTxtOpionScale(OP_MENU_SND);
                    }
                    else if (mouseCollision(m_txtOptionValue[OP_MENU_LOAD_TEX]) && m_gameOptionIndex != OP_MENU_LOAD_TEX)
                    {
                        setTxtOpionScale(OP_MENU_LOAD_TEX);
                    }
                    else if (mouseCollision(m_txtOptionValue[OP_MENU_AUTO_SAVE]) && m_gameOptionIndex != OP_MENU_AUTO_SAVE)
                    {
                        setTxtOpionScale(OP_MENU_AUTO_SAVE);
                    }
                    else if (mouseCollision(m_txtOptionValue[OP_MENU_LANG]) && m_gameOptionIndex != OP_MENU_LANG)
                    {
                        setTxtOpionScale(OP_MENU_LANG);
                    }

                    if (m_gameSysExt.isPressed() && mouseInCollison && m_waitTime == 0 && !m_gameSysExt.m_keyIsPressed)
                    {
                        // validate option
                        auto setKeyToTrue = [this](short int m_txtOptionIndex)
                        {
                            m_txtOptionScale[m_txtOptionIndex] = 1.4f;
                            m_gameSysExt.m_keyIsPressed = true;
                            m_gameSysExt.saveConfig(is::GameConfig::CONFIG_FILE);
                        };

                        switch (m_gameOptionIndex)
                        {
                            // activate / deactivate sound
                            case OP_MENU_SND:
                                if (!m_gameSysExt.m_enableSound) m_gameSysExt.m_enableSound = true;
                                else m_gameSysExt.m_enableSound = false;
                                setKeyToTrue(OP_MENU_SND);
                            break;

                            // activate / deactivate load texture
                            case OP_MENU_LOAD_TEX:
                                m_gameSysExt.m_enableLoadTex = !m_gameSysExt.m_enableLoadTex;
                                setKeyToTrue(OP_MENU_LOAD_TEX);
                            break;

                            // activate / deactivate auto save
                            case OP_MENU_AUTO_SAVE:
                                m_gameSysExt.m_enableAutoSave = !m_gameSysExt.m_enableAutoSave;
                                setKeyToTrue(OP_MENU_AUTO_SAVE);
                            break;

                            // change game language
                            case OP_MENU_LANG:
                                // With each click we change the language index
                                m_gameSysExt.m_gameLanguage++;

                                // Here the enumeration FRANCAIS represents the value of the index of the last language
                                // If the variable is greater than this value we return to the first language
                                // because there are more languages
                                if (m_gameSysExt.m_gameLanguage > is::lang::GameLanguage::FRANCAIS) m_gameSysExt.m_gameLanguage = is::lang::GameLanguage::ENGLISH;

                                m_txtStartGame.setString(is::lang::pad_new_game[m_gameSysExt.m_gameLanguage]);
                                m_txtContinue.setString(is::lang::pad_continue_game[m_gameSysExt.m_gameLanguage]);

                                is::centerSFMLObj(m_txtStartGame);
                                is::centerSFMLObj(m_txtContinue);

                                setKeyToTrue(OP_MENU_LANG);
                            break;
                        }
                        GSMplaySound("select_option");
                    }

                    // update game option
                    m_txtOptionValue[OP_MENU_SND].setString(((m_gameSysExt.m_enableSound) ? is::lang::opt_enable_sound[m_gameSysExt.m_gameLanguage] :
                                                                                            is::lang::opt_disable_sound[m_gameSysExt.m_gameLanguage]));
                    m_txtOptionValue[OP_MENU_LOAD_TEX].setString(((m_gameSysExt.m_enableLoadTex) ? is::lang::opt_enable_load_tex[m_gameSysExt.m_gameLanguage] :
                                                                                                   is::lang::opt_disable_load_tex[m_gameSysExt.m_gameLanguage]));
                    m_txtOptionValue[OP_MENU_AUTO_SAVE].setString(((m_gameSysExt.m_enableAutoSave) ? is::lang::opt_enable_auto_save[m_gameSysExt.m_gameLanguage] :
                                                                                                     is::lang::opt_disable_auto_save[m_gameSysExt.m_gameLanguage]));
                    m_txtOptionValue[OP_MENU_LANG].setString(is::lang::opt_game_lang[m_gameSysExt.m_gameLanguage]);

                    // change the color of the texts according to the chosen option
                    setTextAnimation(m_txtStartGame,   m_sprPad1, OP_START_GAME);
                    setTextAnimation(m_txtContinue,    m_sprPad2, OP_CONTINUE);
                }
            }

//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      MESSAGE BOX
//////////////////////////////////////////////////////////////////////////////////////////////////////
            else
            {
                updateMsgBox(DELTA_TIME);

                // when user closes message box in update function execute this instruction
                // "m_waitTime" allow to disable clicks on objects during a moment when user closes message box
                if (!m_showMsg)
                {
                    if (m_closeApplication) // quit game
                    {
                        if (m_msgAnswer == MsgAnswer::YES)
                        {
                            m_window.close();
                            m_isRunning = false;
                        }
                        else
                        {
                            m_waitTime = 20;
                            m_closeApplication = false;
                        }
                    }
                    else
                    {
                        if (m_optionIndex == OP_START_GAME)
                        {
                            if (m_msgAnswer == MsgAnswer::YES)
                            {
                                m_gameSysExt.m_launchOption = is::DisplayOption::LEVEL_EDITOR;
                                m_isClose = true;
                            } else m_waitTime = 20;
                        } else m_waitTime = 20;
                    }
                }
            }
        }
    }

    // title animation
    m_oscillation += is::radToDeg((0.08f * is::VALUE_CONVERSION) * DELTA_TIME);
    is::setSFMLObjX_Y(m_txtGameTitle, 35.f, 32.f + is::lengthDirY(5.f, m_oscillation));

    // background animation
    if (m_bgX > -32.f) m_bgX -= (0.5f * is::VALUE_CONVERSION) * DELTA_TIME; else m_bgX = 0.f;
    if (m_bgY > -32.f) m_bgY -= (0.5f * is::VALUE_CONVERSION) * DELTA_TIME; else m_bgY = 0.f;
    is::setSFMLObjX_Y(m_sprScreenBG, m_bgX, m_bgY);

    // game option texts animation
    for (unsigned int i(0); i < is::arraySize(m_txtOptionValue); i++)
    {
        setTextAnimation(m_txtOptionValue[i], m_gameOptionIndex, i);
        is::scaleAnimation(DELTA_TIME, m_txtOptionScale[i], m_txtOptionValue[i]);
    }

    // PAD animation
    is::scaleAnimation(DELTA_TIME, m_sprButtonSelectScale, m_sprButtonSelect, m_sprPad1.getScale().x);

    if (m_isClose)
    {
        m_isStart = false;
        m_isRunning = false;
    }
}
