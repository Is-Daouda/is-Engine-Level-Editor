#include "LevelEditor.h"

void LevelEditor::step()
{
    DELTA_TIME = getDeltaTime();

    updateTimeWait();

    // even loop
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        controlEventFocusClosing(event);
        if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                m_keyBackPressed = true;
            }
        }
        if (event.type == sf::Event::MouseWheelMoved)
        {
            m_cursor.m_tileNum += event.mouseWheel.delta;
        }
    }

    // auto save
    m_gameTime.step(DELTA_TIME);
    if (m_gameTime.getTimeValue() == 0)
    {
        if (m_levelIsChanged) saveLevelEditor(true);

        // save the level every AUTO_SAVE_MINUTE minutes
        m_gameTime.setTimeValue(AUTO_SAVE_MINUTE, 0, 0);
    }

    if (m_closeLevelEditor) m_isRunning = false;

    if (!m_showMsg)
    {
//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      IN GAME
//////////////////////////////////////////////////////////////////////////////////////////////////////
        if (m_windowIsActive)
        {
            gamePlay();
            updateItemListObj();
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
            switch (m_optionIndex)
            {
            case 9:
                if (m_msgAnswer == MsgAnswer::YES)
                {
                    reloadLevelEditor();
                    m_waitTime = 10;
                    m_showItemMenuList = false;
                }
                else m_waitTime = 10;
            break;

            case 10:
                if (m_msgAnswer == MsgAnswer::YES)
                {
                    m_gameSysExt.m_launchOption = is::DisplayOption::MAIN_MENU;
                    m_closeLevelEditor = true;
                }
                else m_waitTime = 10;
            break;
            }
        }
    }
}
