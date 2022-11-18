#include "LevelEditor.h"

void LevelEditor::gamePlay()
{
//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      VIEW
//////////////////////////////////////////////////////////////////////////////////////////////////////
    if (!m_showItemMenuList)
    {
        updateObjView();
    }
    m_cursor.step(DELTA_TIME, m_levelWidth, m_levelHeight);

    is::setSFMLObjX_Y(m_sprGridCaseBg, m_viewX - 320.f, m_viewY - 240.f);

    // when user right mouse button clicked
    if (!m_gameSysExt.isPressed() &&
        !m_gameSysExt.keyIsPressed(sf::Keyboard::Left) &&
        !m_gameSysExt.keyIsPressed(sf::Keyboard::Right) &&
        !m_gameSysExt.keyIsPressed(sf::Keyboard::F3) &&
        !m_gameSysExt.keyIsPressed(sf::Keyboard::S) &&
        !m_gameSysExt.keyIsPressed(sf::Keyboard::L) &&
        !m_gameSysExt.keyIsPressed(sf::Keyboard::H) &&
        !m_gameSysExt.keyIsPressed(sf::Keyboard::B) &&
        !m_gameSysExt.keyIsPressed(sf::Keyboard::I) &&
        !m_gameSysExt.keyIsPressed(sf::Keyboard::E) &&
        !m_gameSysExt.keyIsPressed(sf::Keyboard::P) &&
        !m_gameSysExt.keyIsPressed(sf::Keyboard::G) &&
        !m_gameSysExt.keyIsPressed(sf::Keyboard::T) &&
        !m_gameSysExt.keyIsPressed(sf::Mouse::Right)
        )
            m_gameSysExt.m_keyIsPressed = false;

    if (!m_gameSysExt.m_keyIsPressed)
    {
        // hide / show grid
        if (m_gameSysExt.keyIsPressed(sf::Keyboard::F3))
        {
            m_cursor.m_hideGrid = !m_cursor.m_hideGrid;
            m_gameSysExt.m_keyIsPressed = true;
        }

        // save level
        if ((m_gameSysExt.keyIsPressed(sf::Keyboard::S) && m_gameSysExt.keyIsPressed(sf::Keyboard::LControl)))
        {
            saveLevelEditor(false);
            m_gameSysExt.m_keyIsPressed = true;
        }

        // reload the current level
        if ((m_gameSysExt.keyIsPressed(sf::Keyboard::L) && m_gameSysExt.keyIsPressed(sf::Keyboard::LControl)))
        {
            reloadLevelEditor();
            m_gameSysExt.m_keyIsPressed = true;
        }

        // save level as C header
        if ((m_gameSysExt.keyIsPressed(sf::Keyboard::H) && m_gameSysExt.keyIsPressed(sf::Keyboard::LControl)))
        {
            saveMapAsCHeader();
            m_gameSysExt.m_keyIsPressed = true;
        }

        // show item menu list
        if (m_gameSysExt.keyIsPressed(sf::Mouse::Right))
        {
            if (m_showItemMenuList) m_showItemMenuList = false;
            else
            {
                m_showItemMenuList = true;
                m_itemMenuListPostion.x = m_cursor.getX();
                m_itemMenuListPostion.y = m_cursor.getY();
            }
            m_gameSysExt.m_keyIsPressed = true;
        }

        // allows to choose block
        if (m_gameSysExt.keyIsPressed(sf::Keyboard::B))
        {
            m_cursor.setBlockTile();
            m_gameSysExt.m_keyIsPressed = true;
        }

        // allows to choose bonus
        if (m_gameSysExt.keyIsPressed(sf::Keyboard::I))
        {
            m_cursor.setBonusTile();
            m_gameSysExt.m_keyIsPressed = true;
        }

        // allows to choose enemy
        if (m_gameSysExt.keyIsPressed(sf::Keyboard::E))
        {
            m_cursor.setEnemyTile();
            m_gameSysExt.m_keyIsPressed = true;
        }

        // allows to choose player
        if (m_gameSysExt.keyIsPressed(sf::Keyboard::P))
        {
            m_cursor.setPlayerTile();
            m_gameSysExt.m_keyIsPressed = true;
        }

        // allows to choose game play object
        if (m_gameSysExt.keyIsPressed(sf::Keyboard::G))
        {
            m_cursor.setGameplayTile();
            m_gameSysExt.m_keyIsPressed = true;
        }

        // allows to choose tile
        if (m_gameSysExt.keyIsPressed(sf::Keyboard::T))
        {
            m_cursor.setLevelTile();
            m_gameSysExt.m_keyIsPressed = true;
        }

        // delete tile
        if (m_gameSysExt.keyIsPressed(sf::Keyboard::BackSpace))
        {
            m_cursor.setClearTile();
            m_gameSysExt.m_keyIsPressed = true;
        }

        // Quit level editor
        if (m_keyBackPressed)
        {
            showMessageBox(is::lang::msg_quit_editor[m_gameSysExt.m_gameLanguage]);
            m_optionIndex = 10;
            m_keyBackPressed = false;
        }

        // insert / delete tiles
        if (m_gameSysExt.isPressed() && !m_showItemMenuList)
        {
            auto changeEditorState = [this]()
            {
                if (!m_levelIsChanged)
                {
                    m_window.setTitle(is::GameConfig::GAME_NAME + "*");
                    m_levelIsChanged = true;
                }
            };

            m_gameSysExt.m_keyIsPressed = true;

            WITH(m_gridCaseList.size())
            {
                auto it = &m_gridCaseList[_I];
                if (is::instanceExist(*it))
                {
                    // select the grid case that was clicked
                    if (static_cast<int>((*it)->getX()) == static_cast<int>(m_cursor.getX()) &&
                        static_cast<int>((*it)->getY()) == static_cast<int>(m_cursor.getY()))
                    {
                        // this will add tile or display an error when there is a duplicate tile
                        if (!m_cursor.m_clearTile)
                        {
                            auto t = std::make_shared<Tile>(setCorrespondingTex(m_cursor.m_tileNum),
                                                                                   m_cursor.m_tileNum, m_cursor.m_tileMin,
                                                                                   m_cursor.getX(), m_cursor.getY());
                            m_tileList.push_back(t);

                            // insert tile num in grid case
                            if (!(*it)->insertTileNum(m_cursor.m_tileNum, m_cursor.m_tileMin))
                            {
                                t->showError(GRMgetTexture("cursor"));
                                GSMplaySound("cancel");
                            }
                            else
                            {
                                changeEditorState();
                                GSMplaySound("select_option");
                            }
                        }
                        else // clear tiles in grid case
                        {
                            // clear tile
                            bool isDeleted(false);
                            WITH(m_tileList.size())
                            {
                                if (is::instanceExist(m_tileList[_I]))
                                {
                                    if (static_cast<int>(m_tileList[_I]->getX()) == static_cast<int>(m_cursor.getX()) &&
                                        static_cast<int>(m_tileList[_I]->getY()) == static_cast<int>(m_cursor.getY()))
                                    {
                                        isDeleted = true;
                                        m_tileList[_I].reset();
                                    }
                                }
                            }
                            if (isDeleted)
                            {
                                GSMplaySound("select_option");
                                changeEditorState();
                            }
                            else GSMplaySound("cancel");

                            // clear tile num in grid case
                            (*it)->clearTileArray();
                        }
                    }
                }
            }
        }
    }
}

void LevelEditor::updateObjView()
{
    // move the view if cursor is active
    if (m_cursor.getIsActive())
    {
        float const VIEW_SPEED((is::VALUE_CONVERSION * 7.f) * DELTA_TIME);
        if (m_cursor.getX() > 0.f && (m_cursor.getX() + 32.f) < static_cast<float>(m_levelWidth * 32))
        {
            if (m_cursor.getX() + 32.f > static_cast<float>(m_levelWidth * 32) - 48.f &&
                (m_viewX + (m_viewW / 2.f)) < m_cursor.getX())
                m_viewX = (static_cast<float>(m_levelWidth * 32) - (m_viewW / 2.f));

            if (m_cursor.getX() < 48.f && (m_viewX - (m_viewW / 2.f)) > m_cursor.getX())
                m_viewX = (m_viewW / 2.f);

            if (m_cursor.getX() > m_viewX + ((m_viewW / 2.f) - 32.f)) m_viewX += VIEW_SPEED;
            if (m_cursor.getX() < m_viewX - ((m_viewW / 2.f) - 32.f)) m_viewX -= VIEW_SPEED;
        }
        if (m_cursor.getY() > 0.f && m_cursor.getY() < static_cast<float>(m_levelHeight * 32))
        {
            if (m_cursor.getY() + 32.f > static_cast<float>(m_levelHeight * 32) - 48.f &&
                (m_viewY + (m_viewH / 2.f)) < m_cursor.getY())
                m_viewY = (static_cast<float>(m_levelHeight * 32) - (m_viewH / 2.f));

            if (m_cursor.getY() < 48.f && (m_viewY - (m_viewH / 2.f)) > m_cursor.getY())
                m_viewY = (m_viewH / 2.f);

            if (m_cursor.getY() > m_viewY + ((m_viewH / 2.f) - 32.f)) m_viewY += VIEW_SPEED;
            if (m_cursor.getY() < m_viewY - ((m_viewH / 2.f) - 32.f)) m_viewY -= VIEW_SPEED;
        }
    }

    // update view
    setView();
}

void LevelEditor::updateItemListObj()
{
    if (m_showItemMenuList)
    {
        bool mouseInCollison(false);

        // menu selection list objects position
        for (unsigned int i(0); i < is::arraySize(m_recItemMenuList); i++)
        {
            is::setSFMLObjX_Y(m_recItemMenuList[i],
                              m_itemMenuListPostion.x, m_itemMenuListPostion.y + (i * 25.f));
            is::setSFMLObjX_Y(m_txtItemMenuList[i],
                              is::getSFMLObjX(m_recItemMenuList[i]) - (is::getSFMLObjWidth(m_recItemMenuList[i]) / 2.1f),
                              is::getSFMLObjY(m_recItemMenuList[i]) - 8.f);
        }

        // mouse hover effect
        auto setTxtOpionScale = [this](short int m_txtOptionIndex)
        {
            GSMplaySound("change_option");
            m_itemMenuListScale[m_txtOptionIndex] = 1.2f;
            m_optionIndex = m_txtOptionIndex;
        };

        for (unsigned int i(0); i < is::arraySize(m_txtItemMenuList); i++)
        {
            if (mouseCollision(m_txtItemMenuList[i]))
            {
                mouseInCollison = true;

                // faire l'animation une seul fois
                if (static_cast<unsigned int>(m_optionIndex) != i) setTxtOpionScale(i);
            }
        }

        // menu selection texts animation
        for (unsigned int i(0); i < is::arraySize(m_txtItemMenuList); i++)
        {
            is::setTextAnimation(m_txtItemMenuList[i], m_optionIndex, i);
            is::scaleAnimation(DELTA_TIME, m_itemMenuListScale[i], m_txtItemMenuList[i]);
        }

        if (m_gameSysExt.isPressed() && mouseInCollison && !m_gameSysExt.m_keyIsPressed && m_waitTime == 0)
        {
            switch (m_optionIndex)
            {
                // insert block tile
                case 0: m_cursor.setBlockTile(); break;

                // insert bonus tile
                case 1: m_cursor.setBonusTile(); break;

                // insert enemy tile
                case 2: m_cursor.setEnemyTile(); break;

                // insert player tile
                case 3: m_cursor.setPlayerTile(); break;

                // insert gameplay tile
                case 4: m_cursor.setGameplayTile(); break;

                // insert level tile
                case 5: m_cursor.setLevelTile(); break;

                // clear tile
                case 6: m_cursor.setClearTile(); break;

                // save level
                case 7:
                    saveLevelEditor(false);
                break;

                // generate c header
                case 8:
                    saveMapAsCHeader();
                break;

                // reload levl
                case 9:
                    showMessageBox(is::lang::msg_reload_map[m_gameSysExt.m_gameLanguage]);
                break;

                // quit editor
                case 10:
                    showMessageBox(is::lang::msg_quit_editor[m_gameSysExt.m_gameLanguage]);
                break;
            }
            if (m_optionIndex <= 8) m_showItemMenuList = false;
            GSMplaySound("select_option");
            m_gameSysExt.m_keyIsPressed = true;
        }
    }
}

void LevelEditor::createGridCase()
{
    for (unsigned int i = 0; i < m_levelHeight; i++)
    {
        for (unsigned int j = 0; j < m_levelWidth; j++)
        {
            m_gridCaseList.push_back(std::make_shared<GridCase>(j * 32.f, i * 32.f));
        }
    }
}

bool LevelEditor::saveLevelEditor(bool autoSaveCall)
{
    std::string filePath(m_levelName + ".sav");
    if (!autoSaveCall)
    {
        if (m_levelPath == "")
        {
            m_levelPath = is::TinyDialogBox::showFileDialogBox(is::TinyDialogBox::FileDialogType::SAVE_FILE,
                                                                 "Save Level",
                                                                 m_gameSysExt.TINY_FILTER_PATTERNS,
                                                                 m_levelName.c_str(),
                                                                 "Can't save file!");
        }
        filePath = m_levelPath;
    }
    else
    {
        if (m_levelPath != "") filePath = m_levelPath;
    }

    std::ofstream file(filePath);
    if (file)
    {
        file << m_levelName << std::endl;
        file << "map size : width / height (change this value to modify the size of the map) : " << std::endl;
        file << m_levelWidth << std::endl;
        file << m_levelHeight << std::endl;
        file << "old size : width / height (do not change this value) : " << std::endl;
        file << m_levelWidth << std::endl;
        file << m_levelHeight << std::endl;

        file << m_texBlockPath << std::endl;
        file << m_texBonusPath << std::endl;
        file << m_texEnemyPath << std::endl;
        file << m_texPlayerPath << std::endl;
        file << m_texGameplayPath << std::endl;
        file << m_texTilesPath << std::endl;

        WITH(m_gridCaseList.size())
        {
            for (unsigned int i(0); i < is::arraySize(m_gridCaseList[_I]->m_tileNumArray); i++)
            {
                file << m_gridCaseList[_I]->m_tileNumArray[i] << std::endl;
                file << m_gridCaseList[_I]->m_tileMinArray[i] << std::endl;
            }
        }
        m_window.setTitle(is::GameConfig::GAME_NAME);
        m_levelIsChanged = false;
    }
    else
    {
        is::showLog("Error can't save file !");
        return false;
    }
    return true;
}

bool LevelEditor::loadLevelEditor()
{
    if (m_levelPath == "") return false;
    std::string read;
    std::ifstream file(m_levelPath);
    if (file)
    {
        std::getline(file, m_levelName);
        std::string valW, valH, valOldW, valOldH;
        std::getline(file, read);
        std::getline(file, valW);
        m_levelWidth = is::strToNum<int>(valW);
        std::getline(file, valH);
        m_levelHeight = is::strToNum<int>(valH);

        std::getline(file, read);
        std::getline(file, valOldW);
        float oldLevelWidth = is::strToNum<float>(valOldW);
        std::getline(file, valOldH);
        float oldLevelHeigth = is::strToNum<float>(valOldH);

        createGridCase();

        std::getline(file, m_texBlockPath);
        std::getline(file, m_texBonusPath);
        std::getline(file, m_texEnemyPath);
        std::getline(file, m_texPlayerPath);
        std::getline(file, m_texGameplayPath);
        std::getline(file, m_texTilesPath);

        WITH(m_gridCaseList.size())
        {
            if (m_gridCaseList[_I]->getX() < oldLevelWidth * 32.f && m_gridCaseList[_I]->getY() < oldLevelHeigth * 32.f)
            {
                for (unsigned int i(0); i < is::arraySize(m_gridCaseList[_I]->m_tileNumArray); i++)
                {
                    std::string val1, val2;
                    std::getline(file, val1);
                    m_gridCaseList[_I]->m_tileNumArray[i] = is::strToNum<int>(val1);
                    std::getline(file, val2);
                    m_gridCaseList[_I]->m_tileMinArray[i] = is::strToNum<int>(val2);
                    if (m_gridCaseList[_I]->m_tileNumArray[i] > -1)
                    {
                        // insert tile
                        auto t = std::make_shared<Tile>(setCorrespondingTex(m_gridCaseList[_I]->m_tileNumArray[i]),
                                                                               m_gridCaseList[_I]->m_tileNumArray[i],
                                                                               m_gridCaseList[_I]->m_tileMinArray[i],
                                                                               m_gridCaseList[_I]->getX(), m_gridCaseList[_I]->getY());
                        m_tileList.push_back(t);
                    }
                }
            }
        }
        m_window.setTitle(is::GameConfig::GAME_NAME);
        m_levelIsChanged = false;
    }
    else
    {
        is::showLog("Error can't load file !");
        return false;
    }
    return true;
}

void LevelEditor::reloadLevelEditor()
{
    WITH(m_gridCaseList.size())
    {
        if (is::instanceExist(m_gridCaseList[_I]))
        {
            m_gridCaseList[_I].reset();
        }
    }
    m_gridCaseList.clear();
    WITH(m_tileList.size())
    {
        if (is::instanceExist(m_tileList[_I]))
        {
            m_tileList[_I].reset();
        }
    }
    m_tileList.clear();
    loadLevelEditor();
}

bool LevelEditor::saveMapAsCHeader()
{
    std::string headerFilePath;
    tinyString lFilterPatterns[2] = {
                                    #if !defined(SFML_SYSTEM_LINUX) && !defined(IS_ENGINE_LINUX)
                                    L"*.h", L"*.header"
                                    #else
                                    "*.h", "*.header"
                                    #endif
                                    };
    headerFilePath = is::TinyDialogBox::showFileDialogBox(is::TinyDialogBox::FileDialogType::SAVE_FILE,
                                                          "Save Level As C Header",
                                                          lFilterPatterns,
                                                          m_levelName.c_str(),
                                                          "Can't save file as C Header!");
    std::ofstream file(headerFilePath);
    if (file)
    {
        // allows you to organize the characters in the c header file by making newlines (for more readability)
        int countWord(0);
        auto doLineBreak = [this, &countWord, &file]()
        {
            countWord++;
            if (countWord > 8)
            {
                file << std::endl;
                countWord = 0;
            }
        };

        auto strToUpper = [this](std::string &str)
        {
            std::string upperStr(str);
            for (unsigned int i(0); i < upperStr.size(); ++i)
            {
                upperStr[i] = toupper(upperStr[i]) ;
            }
            return upperStr;
        };

        file << "#ifndef _" + strToUpper(m_levelName) + "_MAP" << std::endl;
        file << "#define _" + strToUpper(m_levelName) + "_MAP" << std::endl;
        file << std::endl;
        file << "const short " + strToUpper(m_levelName) + "_MAP[] =" << std::endl;
        file << "{" << std::endl;

        unsigned int n = 0;
        for (unsigned int i = 0; i < m_levelHeight; i++)
        {
            for (unsigned int j = 0; j < m_levelWidth; j++)
            {
                bool haveObject(false);
                for (unsigned int a = 0; a < is::arraySize(m_gridCaseList[n]->m_tileNumArray); a++)
                {
                    if (m_gridCaseList[n]->m_tileNumArray[a] >= 0)
                    {
                        haveObject = true;
                        file << m_gridCaseList[n]->m_tileNumArray[a] << ", ";
                        doLineBreak();
                    }
                }
                if (!haveObject) file << "1000, "; // represent empty space
                file << "1001, "; // move the cursor
                doLineBreak();
                n++;
            }
            file << "1002, "; // line break
            doLineBreak();
        }
        file << "1003"; // represent map end
        file << "};" << std::endl;
        file << std::endl;
        file << "#endif // _" + strToUpper(m_levelName) + "_MAP";
    }
    else
    {
        is::showLog("Error can't save level as C header !");
        return false;
    }
    return true;
}
