#include "MainMenu.h"

void MainMenu::draw()
{
    const short OP_START_GAME(0),
                OP_CONTINUE(1);

    // draw background
    m_surface.draw(m_sprScreenBG);

    // draw game title
    m_surface.draw(m_txtGameTitle);

    // draw button
    if (m_optionIndex != OP_START_GAME) m_surface.draw(m_sprPad1);
    if (m_optionIndex != OP_CONTINUE) m_surface.draw(m_sprPad2);
    m_surface.draw(m_sprButtonSelect);
    m_surface.draw(m_txtStartGame);
    m_surface.draw(m_txtContinue);
    for (unsigned int i(0); i < is::arraySize(m_txtOptionValue); i++) m_surface.draw(m_txtOptionValue[i]);

    ///////////////////////////////////////
    // message box
    drawMsgBox();
    ///////////////////////////////////////
}
