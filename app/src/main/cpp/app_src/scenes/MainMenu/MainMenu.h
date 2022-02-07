#ifndef MAINMENU_H_INCLUDED
#define MAINMENU_H_INCLUDED

#include <memory>

#include "../../../isEngine/system/display/GameDisplay.h"
#include "../../../isEngine/ext_lib/TinyFileDialogs/TinyDialogBox.h"
#include "../../language/GameLanguage.h"

class MainMenu : public is::GameDisplay
{
public:
    MainMenu(is::GameSystemExtended &gameSysExt);
    virtual ~MainMenu();

    void step();
    void draw();

    void loadResources();

private:
    sf::Sprite m_sprPad1, m_sprPad2, m_sprScreenBG;

    sf::Text m_txtGameTitle, m_txtStartGame, m_txtContinue;
    sf::Text m_txtOptionValue[5];

    sf::Keyboard::Key m_keyBack;

    int m_gameOptionIndex;
    float m_oscillation, m_xPos, m_yPos, m_bgX, m_bgY, m_sprButtonPemuteScale, m_timeClick;
    float m_txtOptionScale[6];

    bool m_isClicked;
    bool m_isStart, m_saveFileOpen;
    bool m_closeApplication;
};

#endif // MAINMENU_H_INCLUDED
