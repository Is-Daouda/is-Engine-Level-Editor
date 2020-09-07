#ifndef INTRO_H_INCLUDED
#define INTRO_H_INCLUDED

#include "../../../isEngine/system/display/GameDisplay.h"
#include "../../../isEngine/system/entity/parents/Step.h"
#include "../../language/GameLanguage.h"
#include "../../../isEngine/ext_lib/TinyFileDialogs/TinyDialogBox.h"

class Intro : public is::GameDisplay, public is::Step
{
public:
    Intro(sf::RenderWindow &window, sf::View &view, sf::RenderTexture &surface, is::GameSystemExtended &gameSysExt);
    void step();
    void draw();

    void loadResources();

private:
    sf::Font m_fontTitle;
    sf::Texture m_texPad;
    sf::Sprite m_sprPadFr;
    sf::Text m_txtChooseLanguage, m_txtLangEng, m_txtLangFr;
    sf::RectangleShape m_recChooseLanguage;

    float m_recScale;
    bool m_isOnPad;
};

#endif // INTRO_H_INCLUDED
