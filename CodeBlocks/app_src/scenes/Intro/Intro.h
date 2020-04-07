#ifndef INTRO_H_INCLUDED
#define INTRO_H_INCLUDED

#include "../../../isEngine/system/display/GameDisplay.h"
#include "../../language/GameLanguage.h"

class Intro : public is::GameDisplay
{
public:
    Intro(sf::RenderWindow &window, sf::View &view, sf::RenderTexture &surface, GameSystemExtended &gameSysExt);
    void step();
    void draw();

    bool loadResources();

private:
    sf::Font m_fontTitle;
    sf::Texture m_texLogo, m_texPad;
    sf::Sprite m_sprLogo, m_sprPadFr;
    sf::Text m_txtChooseLanguage, m_txtLangEng, m_txtLangFr;
    sf::RectangleShape m_recTransition, m_recChooseLanguage;

    float m_recScale;
    int m_alphaRec, m_timeEv, m_introStep, m_imgAlpha;
    bool m_blind, m_isOnPad, m_openLanguageMenu;
};

#endif // INTRO_H_INCLUDED
