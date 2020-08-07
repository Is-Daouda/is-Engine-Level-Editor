#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

#include "../../../isEngine/system/entity/MainObject.h"

class Tile : public is::MainObject
{
public:
    Tile(sf::Texture &tex, int tileNum, int tileMin, float x, float y);

    void showError(sf::Texture &tex);
    void step(float const &DELTA_TIME) {}
    void draw(sf::RenderTexture &surface);

    int m_tileNum;
};

#endif // TILE_H_INCLUDED
