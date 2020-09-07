#ifndef GAMEACTIVITY_H_INCLUDED
#define GAMEACTIVITY_H_INCLUDED

#include <memory>

#include "SwooshFiles.h"
#include "../scenes/Intro/Intro.h"
#include "../scenes/MainMenu/MainMenu.h"
#include "../scenes/LevelEditor/LevelEditor.h"

using namespace swoosh::intent;

////////////////////////////////////////////////////////////
/// Allows to manage the different scenes of the game and
/// to interconnect the engine and the Swoosh library to make
/// transition effects
////////////////////////////////////////////////////////////
class GameActivity : public Activity
{
private:
    std::shared_ptr<is::GameDisplay> m_gameScene;
    bool m_changeActivity;

public:
    GameActivity(ActivityController& controller, is::GameSystemExtended &gameSysExt) :
                            Activity(&controller),
                            m_changeActivity(false)
    {
        switch (gameSysExt.m_launchOption)
        {
        case is::DisplayOption::INTRO:
            m_gameScene = std::make_shared<Intro>(controller.getWindow(),
                                                     getView(),
                                                     *(this->controller->getSurface()),
                                                     gameSysExt);
        break;
        case is::DisplayOption::MAIN_MENU:
            m_gameScene = std::make_shared<MainMenu>(controller.getWindow(),
                                                        getView(),
                                                        *(this->controller->getSurface()),
                                                        gameSysExt);
        break;
        case is::DisplayOption::LEVEL_EDITOR:
		{
            m_gameScene = std::make_shared<LevelEditor>(controller.getWindow(),
                                                           getView(),
                                                           *(this->controller->getSurface()),
                                                           gameSysExt);
		}
        break;
        default:
			is::showLog("Error : Scene not found !", true);
		break;
        }
        m_gameScene->loadResources();
        this->setBGColor(m_gameScene->getBgColor());
    }

    virtual void onStart()
    {
        // std::cout << "GameActivity OnStart called" << std::endl;
    }

    virtual void onUpdate(double elapsed)
    {
        if (m_gameScene->getIsRunning()) m_gameScene->step();
        else
        {
            if (!m_changeActivity)
            {
                switch (m_gameScene->getGameSystem().m_launchOption)
                {
                    case is::DisplayOption::MAIN_MENU:
                        {
                            using transition = segue<BlackWashFade>;
                            using action = transition::to<GameActivity>;
                            getController().replace<action>(m_gameScene->getGameSystem());
                        }
                    break;

                    case is::DisplayOption::LEVEL_EDITOR:
                        {
                            using transition = segue<VerticalSlice, sec<2>>;
                            using action = transition::to<GameActivity>;
                            getController().replace<action>(m_gameScene->getGameSystem());
                        }
                    break;

                    default:
                        is::showLog("Error : Scene not found !", true);
                    break;
                }
                m_changeActivity = true;
            }
        }
    }

    virtual void onLeave()
    {
        // std::cout << "GameActivity OnLeave called" << std::endl;
    }

    virtual void onExit()
    {
        // std::cout << "GameActivity onExit called" << std::endl;
    }

    virtual void onEnter()
    {
        // std::cout << "GameActivity OnEnter called" << std::endl;
    }

    virtual void onResume()
    {
        // std::cout << "GameActivity OnResume called" << std::endl;
    }

    virtual void onDraw(sf::RenderTexture& surface)
    {
        m_gameScene->drawScreen();
    }

    virtual void onEnd() {}

    ~GameActivity() {}
};

#endif // GAMEACTIVITY_H_INCLUDED
