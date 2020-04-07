#include "LevelEditor.h"

void LevelEditor::draw()
{
    if (!m_cursor.m_hideGrid) m_surface.draw(m_sprGridCaseBg);

    // draw tiles
    WITH(m_tileList.size())
    {
        if (is::instanceExist(m_tileList[_I]))
        {
            if (m_tileList[_I]->inViewRec(*this))
            {
                m_tileList[_I]->draw(m_surface);
            }
        }
    }

    m_txtLevelEditorInfo.setString("x : " + is::numToStr(m_cursor.getX())   + " (" + is::numToStr(m_cursor.getX() / 32) + ")" +
                               "\ny : " + is::numToStr(m_cursor.getY()) + " (" + is::numToStr(m_cursor.getY() / 32) + ")" +
                               "\nLevel W : " + is::numToStr(m_levelWidth * 32)  + " (" + is::numToStr(m_levelWidth) + ")" +
                               "\nLevel H : " + is::numToStr(m_levelHeight * 32) + " (" + is::numToStr(m_levelHeight) + ")"
                               );
    is::setSFMLObjX_Y(m_txtLevelEditorInfo, m_viewX - 300.f, m_viewY - 230.f);
    m_surface.draw(m_txtLevelEditorInfo);

    // draw menu selection list
    if (m_showItemMenuList)
    {
        for (unsigned int i(0); i < is::arraySize(m_recItemMenuList); i++)
        {
            m_surface.draw(m_recItemMenuList[i]);
        }
        for (unsigned int i(0); i < is::arraySize(m_txtItemMenuList); i++)
        {
            m_surface.draw(m_txtItemMenuList[i]);
        }
    }
    else // draw cursor
        m_cursor.draw(m_surface);

    ///////////////////////////////////////
    // message box
    drawMsgBox();
    ///////////////////////////////////////
}
