#include "Cursor.h"

Cursor::Cursor(is::GameDisplay *scene) :
    MainObject(),
    m_scene(scene)
{
    m_texCursor = 0;
    m_texPlayer = 0;
    m_texBlock = 0;
    m_texBonus = 0;
    m_texTiles = 0;
    m_texEnemy = 0;

    m_tileNum = 0;
    m_clearTile = true;
    m_tileMin = 0;
    m_tileMax = 1;
    m_hideGrid = false;

    m_isActive = true;
}

void Cursor::loadResources(sf::Texture *texCursor,
                           sf::Texture *texBlock,
                           sf::Texture *texBonus,
                           sf::Texture *texEnemy,
                           sf::Texture *texPlayer,
                           sf::Texture *texGamePlay,
                           sf::Texture *texTiles)
{
    m_texCursor = texCursor;
    is::createSprite(*m_texCursor, m_sprParent, sf::IntRect(0, 0, 32, 32), sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f));
    if (texBlock != nullptr) m_texBlock = texBlock;
    if (texBonus != nullptr) m_texBonus = texBonus;
    if (texEnemy != nullptr) m_texEnemy = texEnemy;
    if (texPlayer != nullptr) m_texPlayer = texPlayer;
    if (texGamePlay != nullptr) m_texGameplay = texGamePlay;
    if (texTiles != nullptr) m_texTiles = texTiles;
}

void Cursor::step(float const &DELTA_TIME, int const &levelW, int const &levelH)
{
    if (!m_scene->getGameSystem().keyIsPressed(sf::Keyboard::L) &&
        !m_scene->getGameSystem().keyIsPressed(sf::Keyboard::M))
    {
        sf::Vector2i pixelPos = sf::Mouse::getPosition(m_scene->getRenderWindow());
        sf::Vector2f worldPos = getMapPixelToCoords(m_scene, pixelPos);

        int mouseX(worldPos.x);
        int mouseY(worldPos.y);

        // move cursor
        if (mouseY > m_y + 32) m_y += 32;
        else if (mouseY < m_y) m_y -= 32;
        if (m_y < 0) m_y = 0;
        if (m_y > (levelH * 32) - 32) m_y = (levelH * 32) - 32;

        if (mouseX > m_x + 32) m_x += 32;
        else if (mouseX < m_x) m_x -= 32;
        if (m_x < 0) m_x = 0;
        if (m_x > (levelW * 32) - 32) m_x = (levelW * 32) - 32;
    }

    // change tile
    if (!m_clearTile)
    {
        if (!m_scene->getGameSystem().m_keyIsPressed)
        {
            if (m_scene->getGameSystem().keyIsPressed(sf::Keyboard::Down))
            {
                m_tileNum--;
                m_scene->getGameSystem().m_keyIsPressed = true;
            }
            else if (m_scene->getGameSystem().keyIsPressed(sf::Keyboard::Up))
            {
                m_tileNum++;
                m_scene->getGameSystem().m_keyIsPressed = true;
            }
        }
        if (m_tileNum < m_tileMin) m_tileNum = m_tileMin;
        if (m_tileNum > (m_tileMin + (m_tileMax - 1))) m_tileNum = (m_tileMin + (m_tileMax - 1));
        m_frame = static_cast<float>(m_tileNum - m_tileMin);
    }

    is::setFrame(m_sprParent, m_frame, m_tileMax, 32, 32, 32);
    is::setSFMLObjX_Y(m_sprParent, m_x, m_y);
    updateCollisionMask();
}

void Cursor::draw(sf::RenderTexture &surface)
{
    surface.draw(m_sprParent);
}
