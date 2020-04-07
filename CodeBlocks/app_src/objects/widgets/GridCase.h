#ifndef GRIDCASE_H_INCLUDED
#define GRIDCASE_H_INCLUDED

#include "../../../isEngine/system/entity/MainObject.h"
#include "Tile.h"

class GridCase : public is::MainObject
{
public:
    GridCase(float x, float y);

    void step(float const &DELTA_TIME);
    void clearTileArray()
    {
        for (auto &x : m_tileNumArray) {x = -1;}
        for (auto &x : m_tileMinArray) {x = -1;}
    }

    bool insertTileNum(int tileNum, int tileMin);

    void draw(sf::RenderTexture &surface);

    int m_tileMinArray[5];
    int m_tileNumArray[5];
};

#endif // GRIDCASE_H_INCLUDED
