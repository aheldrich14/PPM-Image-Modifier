#include "RowColumnClass.h"

RowColumnClass::RowColumnClass()
{
    const int DEFAULT_ROW_COL = -99999;
    setRowCol(DEFAULT_ROW_COL, DEFAULT_ROW_COL);
}

RowColumnClass::RowColumnClass(int inRow, int inCol)
{
    setRowCol(inRow,inCol);
}

void RowColumnClass::setRowCol(int inRow, int inCol)
{
    setRow(inRow);
    setCol(inCol);
}

void RowColumnClass::setRow(int inRow)
{
    row = inRow;
}
        
void RowColumnClass::setCol(int inCol)
{
    col = inCol;
}

int RowColumnClass::getRow()
{
    return row;
}

int RowColumnClass::getCol()
{
    return col;
}

void RowColumnClass::addRowColTo(RowColumnClass &inRowCol)
{
    //get row/col of passed in object
    int addRow = inRowCol.getRow();
    int addCol = inRowCol.getCol();

    //get row/col of calling object
    int newRow = getRow();
    int newCol = getCol();

    //add row/cols together
    newRow += addRow;
    newCol += addCol;

    setRowCol(newRow, newCol);
}

void RowColumnClass::promptRowColInput(string desc, int minRow, int minCol)
{
    string msg = "Enter " + desc + " row and column index: ";
    bool validInputFound = false;
    int inRow = 1;
    int inCol = 1;
    string rowErr = "Input row index must be at least ";
    string colErr = "Input column index must be at least ";

    while (!validInputFound)
    {
        cout << msg;
        cin >> inRow >> inCol;

        if (cin.fail())
        {   
            cin.clear(); 
            cin.ignore(200, '\n');
            cout << endl;
        }
        else if (inRow < minRow)
        {
            cout << rowErr << minRow << endl;
        }
        else if (inCol < minCol)
        {
            cout << colErr << minCol << endl;
        }
        else
        {
            validInputFound = true;
        }
    }

    cin.ignore(200, '\n'); //ignore anything left in buffer
    
    setRowCol(inRow, inCol);
}