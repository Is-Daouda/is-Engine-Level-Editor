#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include <windows.h>
#include <memory>

#include "../../../isEngine/system/display/GameDisplay.h"
#include "../../../isEngine/system/function/GameTime.h"
#include "../../../isEngine/ext_lib/TinyFileDialogs/TinyDialogBox.h"

#include "../../language/GameLanguage.h"
#include "../../objects/widgets/Tile.h"
#include "../../objects/widgets/GridCase.h"
#include "../../objects/widgets/Cursor.h"

class LevelEditor : public is::GameDisplay
{
public:
    LevelEditor(sf::RenderWindow &window, sf::View &swooshView, sf::RenderTexture &surface, GameSystemExtended &gameSysExt);
    ~LevelEditor();

    void createGridCase();
    void updateItemListObj();
    void step();
    void draw();

    /// return level W
    virtual float getLevelW() const {return m_levelWidth;}

    /// return level H
    virtual float getLevelH() const {return m_levelHeight;}

    sf::Texture& setCorrespondingTex(int tileNum)
    {
        if (tileNum >= TilesObject::OBJ_TILE) return m_texTiles;
        else if (tileNum >= TilesObject::OBJ_GAMEPLAY) return m_texGameplay;
        else if (tileNum >= TilesObject::OBJ_PLAYER) return m_texPlayer;
        else if (tileNum >= TilesObject::OBJ_ENEMY) return m_texEnemy;
        else if (tileNum >= TilesObject::OBJ_BONUS) return m_texBonus;
        else return m_texBlock;
    }

    bool loadResources();
    bool saveLevelEditor(bool autoSaveCall);
    bool loadLevelEditor();
    void reloadLevelEditor();
    bool saveMapAsCHeader();

private:
    void gamePlay();
    void updateObjView();

private:
    std::vector<std::shared_ptr<Tile>> m_tileList;
    std::vector<std::shared_ptr<GridCase>> m_gridCaseList;

    std::string m_levelPath, m_texBlockPath, m_texPlayerPath, m_texGameplayPath,
                m_texTilesPath, m_texEnemyPath, m_texBonusPath;
    std::string m_levelName;

    sf::Texture m_texPad, m_texToolsPad;
    sf::Texture m_texCursor, m_texBlock, m_texPlayer, m_texGameplay, m_texTiles, m_texEnemy, m_texBonus;

    sf::Texture m_texGridCaseBg;
    sf::Sprite m_sprGridCaseBg;

    sf::RectangleShape m_recItemMenuList[11];
    sf::Text m_txtItemMenuList[11];
    sf::Vector2f m_itemMenuListPostion;

    sf::Text m_txtLevelEditorInfo;

    // represents the maximum time to make a auto save of the level
    const unsigned int AUTO_SAVE_MINUTE;

    // allow to manage auto save time
    is::GameTime m_gameTime;

    Cursor m_cursor;

    bool m_closeLevelEditor, m_showItemMenuList, m_levelIsChanged;
    unsigned int m_levelWidth, m_levelHeight;
    int m_restartTime, m_validationKeyPressedTime;
    float m_itemMenuListScale[11];
};

#endif // LEVELEDITOR_H
