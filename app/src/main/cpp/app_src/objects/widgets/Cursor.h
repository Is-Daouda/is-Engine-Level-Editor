#ifndef CURSOR_H_INCLUDED
#define CURSOR_H_INCLUDED

#include "../../../isEngine/system/entity/MainObject.h"
#include "../../../isEngine/system/display/GameDisplay.h"
#include "../../../isEngine/ext_lib/TinyFileDialogs/TinyDialogBox.h"

/// represent the tile
enum TilesObject
{
    OBJ_BLOCK,
    OBJ_BONUS = 100,
    OBJ_ENEMY = 200,
    OBJ_PLAYER = 300,
    OBJ_GAMEPLAY = 400,
    OBJ_TILE = 500
};

class Cursor : public is::MainObject
{
public:
    Cursor(is::GameDisplay *scene);

    void loadResources(sf::Texture *texCursor,
                       sf::Texture *texBlock = nullptr,
                       sf::Texture *texBonus = nullptr,
                       sf::Texture *texEnemy = nullptr,
                       sf::Texture *texPlayer = nullptr,
                       sf::Texture *texGamePlay = nullptr,
                       sf::Texture *texTiles = nullptr
                       );

    void changeTile(int id, sf::Texture *tex)
    {
        m_tileNum = id;
        m_tileMin = m_tileNum;
        m_tileMax = (tex->getSize().x / 32); // get number of sub image
        m_sprParent.setTexture((*tex));
        m_sprParent.setTextureRect(sf::IntRect(0, 0, 32, 32));
        m_clearTile = false;
    }
    void setBlockTile()
    {
        if (m_texBlock != nullptr)
        {
            changeTile(TilesObject::OBJ_BLOCK, m_texBlock);
        }
        else is::TinyDialogBox::showDialogBox("Error",
                                              "Can't use this tile because the texture has't been loaded!",
                                              is::TinyDialogBox::DialogType::OK,
                                              is::TinyDialogBox::IconType::ERROR_ICO);
    }
    void setBonusTile()
    {
        if (m_texBonus != nullptr)
        {
            changeTile(TilesObject::OBJ_BONUS, m_texBonus);
        }
        else is::TinyDialogBox::showDialogBox("Error",
                                              "Can't use this tile because the texture has't been loaded!",
                                              is::TinyDialogBox::DialogType::OK,
                                              is::TinyDialogBox::IconType::ERROR_ICO);
    }
    void setEnemyTile()
    {
        if (m_texEnemy != nullptr)
        {
            changeTile(TilesObject::OBJ_ENEMY, m_texEnemy);
        }
        else is::TinyDialogBox::showDialogBox("Error",
                                              "Can't use this tile because the texture has't been loaded!",
                                              is::TinyDialogBox::DialogType::OK,
                                              is::TinyDialogBox::IconType::ERROR_ICO);
    }
    void setPlayerTile()
    {
        if (m_texPlayer != nullptr)
        {
            changeTile(TilesObject::OBJ_PLAYER, m_texPlayer);
        }
        else is::TinyDialogBox::showDialogBox("Error",
                                              "Can't use this tile because the texture has't been loaded!",
                                              is::TinyDialogBox::DialogType::OK,
                                              is::TinyDialogBox::IconType::ERROR_ICO);
    }
    void setGameplayTile()
    {
        if (m_texGameplay != nullptr)
        {
            changeTile(TilesObject::OBJ_GAMEPLAY, m_texGameplay);
        }
        else is::TinyDialogBox::showDialogBox("Error",
                                              "Can't use this tile because the texture has't been loaded!",
                                              is::TinyDialogBox::DialogType::OK,
                                              is::TinyDialogBox::IconType::ERROR_ICO);
    }
    void setLevelTile()
    {
        if (m_texTiles != nullptr)
        {
            changeTile(TilesObject::OBJ_TILE, m_texTiles);
        }
        else is::TinyDialogBox::showDialogBox("Error",
                                              "Can't use this tile because the texture has't been loaded!",
                                              is::TinyDialogBox::DialogType::OK,
                                              is::TinyDialogBox::IconType::ERROR_ICO);
    }
    void setClearTile()
    {
        if (!m_clearTile)
        {
            changeTile(0, m_texCursor);
            m_clearTile = true;
        }
    }

    void step(float const &DELTA_TIME, int const &levelW, int const &levelH);

    int m_tileNum, m_tileMin, m_tileMax;
    bool m_clearTile, m_hideGrid;

private:
    is::GameDisplay *m_scene;
    sf::Texture *m_texCursor, *m_texBlock, *m_texBonus, *m_texEnemy, *m_texPlayer, *m_texGameplay, *m_texTiles;
};

#endif // CURSOR_H_INCLUDED
