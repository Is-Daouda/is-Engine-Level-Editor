#include "GameSystemExtended.h"

namespace is
{
GameSystemExtended::GameSystemExtended(sf::RenderWindow &window) :
    GameSystem(window)
{
    m_enableLoadTex = false;
    m_enableAutoSave = true;
    m_filePath = "";

    // Default position of the Virtual Pad Game on the screen
    m_defaultPadDirXPos = -250.f;
    m_defaultPadDirYPos = 170.f;
    m_defaultPadActionXPos = 245.f;
    m_defaultPadActionYPos = 200.f;

    // Configurable position of the Virtual Pad Game on the screen
    m_padDirXPos = m_defaultPadDirXPos;
    m_padDirYPos = m_defaultPadDirYPos;
    m_padActionXPos = m_defaultPadActionXPos;
    m_padActionYPos = m_defaultPadActionYPos;
    m_permutePadAB = false;
    m_padAlpha = 255;
}

void GameSystemExtended::initSystemData()
{
    // global variable
    m_gameLanguage = 0;
    m_firstLaunch = true;
}
}
