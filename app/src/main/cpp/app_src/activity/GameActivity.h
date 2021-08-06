#ifndef GAMEACTIVITY_H_INCLUDED
#define GAMEACTIVITY_H_INCLUDED

#include "../scenes/Intro/Intro.h"
#include "../scenes/MainMenu/MainMenu.h"
#include "../scenes/LevelEditor/LevelEditor.h"

// example
// #include "../scenes/YourScene/YourScene.h"

////////////////////////////////////////////////////////////
/// Allows to manage the different scenes of the game
////////////////////////////////////////////////////////////
class GameActivity
{
private:
    std::shared_ptr<is::GameDisplay> m_gameScene;

public:
    bool m_changeActivity = false;
    GameActivity(is::GameSystemExtended &gameSysExt)
    {
        m_gameScene = nullptr;
////////////////////////////////////////////////////////////

        // Allows to choose the scene that will be launched
        switch (gameSysExt.m_launchOption)
        {
        case is::DisplayOption::INTRO:
            m_gameScene = std::make_shared<Intro>(gameSysExt);
        break;
        case is::DisplayOption::MAIN_MENU:
            m_gameScene = std::make_shared<MainMenu>(gameSysExt);
        break;
        case is::DisplayOption::LEVEL_EDITOR:
            m_gameScene = std::make_shared<LevelEditor>(gameSysExt);
        break;

        // example
        // case is::DisplayOption::YOUR_SCENE:
        // m_gameScene = std::make_shared<YourScene>(gameSysExt);
        // break;

        default:
			is::showLog("ERROR: Scene not found !", true);
		break;
        }
        m_gameScene->loadResources();
    }

    virtual void onUpdate()
    {
        if (m_gameScene->getIsRunning()) m_gameScene->step();
        else
        {
            if (!m_changeActivity) m_changeActivity = true;
        }
    }

    virtual void onDraw() {m_gameScene->drawScreen();}

    virtual ~GameActivity() {}
};

#endif // GAMEACTIVITY_H_INCLUDED
