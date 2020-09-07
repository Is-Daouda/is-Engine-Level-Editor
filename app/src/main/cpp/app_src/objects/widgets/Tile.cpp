#include "Tile.h"

Tile::Tile(sf::Texture &tex, int tileNum, int tileMin, float x, float y) :
    is::MainObject(x, y)
{
    m_tileNum = tileNum;
    m_sprParent.setTexture(tex);
    is::setSFMLObjX_Y(m_sprParent, x, y);
    is::setFrame(m_sprParent, m_tileNum - tileMin, (tex.getSize().x / 32), 32, 32, 32);
}

void Tile::showError(sf::Texture &tex)
{
    is::createSprite(tex, m_sprParent, sf::IntRect(32, 0, 32, 32), sf::Vector2f(m_x, m_y), sf::Vector2f(0.f, 0.f));
    is::showLog("error !");
}
