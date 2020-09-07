#include "GridCase.h"

GridCase::GridCase(float x, float y) :
    MainObject(x, y)
{
    clearTileArray();
}

bool GridCase::insertTileNum(int tileNum, int tileMin)
{
    int tileIndexInArray = 0;
    for (auto x : m_tileNumArray)
    {
        if (x == tileNum)
        {
            return false;
        }

        // if the case of array already contains a tile number
        if (x > 0) tileIndexInArray++;
    }
    m_tileNumArray[tileIndexInArray] = tileNum;
    m_tileMinArray[tileIndexInArray] = tileMin;
    return true;
}
