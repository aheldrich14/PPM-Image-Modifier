#include "RectangleClass.h"

RectangleClass::RectangleClass()
{
    height = 0;
    width = 0;
    fill = false;
}
void RectangleClass::createRectangle()
{
    setSize();
    setFill();
    setColor("rectangle");
}
void RectangleClass::setSize()
{
    const int CORNER_POS = 1;
    const int WDTH_HGHT= 2;
    const int CENTER = 3;
    const int MNU_CHOICES = 3;
    int menuChoice = 1;
    string mainMenuMsg = "Enter int for rectangle specification method: ";
    
    cout << "1. Specify upper left and lower right corners of rectangle";
    cout << endl;
    cout << "2. Specify upper left corner and dimensions of rectangle";
    cout << endl;
    cout << "3. Specify extent from center of rectangle" << endl;
        
    menuChoice = checkMenuChoice(mainMenuMsg, MNU_CHOICES);

    if (menuChoice == CORNER_POS)
    {
        useCornerPos();  //upper left and lower right
    }
    else if (menuChoice == WDTH_HGHT)
    {
        useWdthHght();  //upper left and height/width
    }
    else if (menuChoice == CENTER)
    {
        useCenter();  //center and half # rows/cols
    }
}
void RectangleClass::useCornerPos()
{
    RowColumnClass lowerRight;
    string upLeDesc= "upper left corner";
    string lowRiDesc = "lower right corner";
    const int MIN_ROW_COL = 0;  //force user to enter at least [0][0]
    const int ROW_COL_OFFSET = 1;
    int inHeight = 0;
    int inWidth = 0;

    setUpperLeft(upLeDesc, MIN_ROW_COL, MIN_ROW_COL);

    //lower right must have at least same row/col as upper left
    lowerRight.promptRowColInput(lowRiDesc, 
                                upperLeft.getRow(),
                                upperLeft.getCol());

    inHeight = lowerRight.getRow() - upperLeft.getRow() + ROW_COL_OFFSET;
    inWidth = lowerRight.getCol() - upperLeft.getCol() + ROW_COL_OFFSET;
    setHghtWdth(inHeight, inWidth);

}
void RectangleClass::useWdthHght()
{
    string upLeDesc = "upper left corner";
    string hghtMsg = "Enter int for number of rows: ";
    string wdthMsg = "Enter int for number of columns: "; 
    const int MIN_ROW_COL = 0; //force user to enter at least [0][0]
    const int MIN_HGHT_WDTH = 1;
    int inHeight = 0;
    int inWidth = 0;

    setUpperLeft(upLeDesc, MIN_ROW_COL, MIN_ROW_COL);
    inHeight = promptIntInput(hghtMsg, MIN_HGHT_WDTH);
    inWidth = promptIntInput(wdthMsg, MIN_HGHT_WDTH);
    setHghtWdth(inHeight, inWidth);
}
void RectangleClass::useCenter()
{
    string centerDesc = "rectangle center";
    string rowMsg = "Enter int for half number of rows: ";
    string colMsg = "Enter int for half number of columns: ";
    RowColumnClass center;
    int rowHalf = 0;
    int colHalf = 0;
    int inRow = 0;
    int inCol = 0;
    int inHeight = 0;
    int inWidth = 0;
    const int FACTOR = 2; //always need to double input
    const int CENTER_OFFSET = 1;
    const int MIN_CENTER_ROW_COL = 1; //at min, center must be at [1][1]
    const int MIN_HALF_ROW_COL = 1;
    bool validInput = false;

    while (!validInput)
    {
        center.promptRowColInput(centerDesc, 
                                MIN_CENTER_ROW_COL,
                                MIN_CENTER_ROW_COL);
        
        rowHalf = promptIntInput(rowMsg, MIN_HALF_ROW_COL);
        colHalf = promptIntInput(colMsg, MIN_HALF_ROW_COL); 

        //we're forcing the min center to be [1][1]
        if (rowHalf > center.getRow() || colHalf > center.getCol())
        {
            cout << "Error: Distance from center is out of bounds" << endl;
        }
        else
        {
            validInput = true;
        }
    }

    //height/width must always be odd for there to be center
    inHeight = rowHalf * FACTOR + CENTER_OFFSET;
    inWidth = colHalf * FACTOR + CENTER_OFFSET;
    setHghtWdth(inHeight, inWidth);

    inRow = center.getRow() - rowHalf;
    inCol = center.getCol() - colHalf;
    upperLeft.setRowCol(inRow, inCol);

}
void RectangleClass::setFill()
{
    const int FILL = 2;
    const int MNU_CHOICES = 2;
    int menuChoice = 1;
    string mainMenuMsg = "Enter int for rectangle fill option: ";
    
    cout << "1. No" << endl;
    cout << "2. Yes" << endl;
        
    menuChoice = checkMenuChoice(mainMenuMsg, MNU_CHOICES);

    if (menuChoice == FILL)
    {
        fill = true;
    }
    else 
    {
        fill = false;
    }
}
void RectangleClass::setColor(string desc)
{
    color.promptColorInput(desc);
}
int RectangleClass::promptIntInput(string msg, int minNum)
{
    int input;
    bool validInputFound = false;

    while (!validInputFound)
    {
        cout << msg;
        cin >> input;
        validInputFound = checkIntInput(input, minNum);
    }
    
    cin.ignore(200, '\n'); //ignore anything left in buffer

    return input;
}
bool RectangleClass::checkIntInput(int input, int minNum)
{
    string msg = "Int must be at least ";
    bool validInputFound = false;

    if (cin.fail())
    {   
        cin.clear(); 
        cin.ignore(200, '\n');
        cout << endl;
    }
    else if (input < minNum)
    {
        cout << msg << minNum << endl;
        cin.ignore(200, '\n');
    }
    else
    {
        validInputFound = true;
    }

    return validInputFound;
}
RowColumnClass RectangleClass::getUpperLeft()
{
    return upperLeft;
}

RowColumnClass RectangleClass::getLowerRight()
{
    RowColumnClass lowerRight;
    const int ROW_COL_OFFSET = 1;
    int inRow = 0;
    int inCol = 0;

    inRow = upperLeft.getRow() + height - ROW_COL_OFFSET;
    inCol = upperLeft.getCol() + width - ROW_COL_OFFSET;
    lowerRight.setRowCol(inRow, inCol);

    return lowerRight;
}
bool RectangleClass::checkBorder(int rowIdx, int colIdx)
{
    bool isBorder = false;
    RowColumnClass lowerRight;

    lowerRight = getLowerRight();

    //border is anything on first/last row/col
    if (rowIdx == upperLeft.getRow() || rowIdx == lowerRight.getRow())
    {
        isBorder = true;
    }
    else if (colIdx == upperLeft.getCol() || colIdx == lowerRight.getCol())
    {
        isBorder = true;
    }

    return isBorder;
}
ColorClass RectangleClass::getColor()
{
    return color;
}
bool RectangleClass::getFill()
{
    return fill;
}
void RectangleClass::setHghtWdth(int inHeight, int inWidth)
{
    height = inHeight;
    width = inWidth;
}
void RectangleClass::setUpperLeft(string desc, int minRow, int minCol)
{
    upperLeft.promptRowColInput(desc, minRow, minCol);
}
int RectangleClass::getHght()
{
    return height;
}
int RectangleClass::getWdth()
{
    return width;
}
int RectangleClass::getEndRow()
{
    int endRow = 0;

    endRow = upperLeft.getRow() + height;

    return endRow;
}
int RectangleClass::getEndCol()
{
    int endCol = 0;

    endCol = upperLeft.getCol() + width;

    return endCol;
}
int RectangleClass::getUpperLeftRow()
{
    return upperLeft.getRow();
}
int RectangleClass::getUpperLeftCol()
{
    return upperLeft.getCol();
}
void RectangleClass::translateIdx(int &rowIdx, int &colIdx)
{
    //input indexes are offset by upper left position
    //if upper left is [1][1], that is actually [0][0] in rectangle
    rowIdx -= upperLeft.getRow();
    colIdx -= upperLeft.getCol();
}


