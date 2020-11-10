#ifndef _RECTANGLECLASS_H_
#define _RECTANGLECLASS_H_

#include <iostream>
#include "ColorClass.h"
#include "RowColumnClass.h"
#include "checkMenuChoice.h"
using namespace std;

class RectangleClass
{
    public:
        RectangleClass();

        //entry point for user prompts to create rectangle
        void createRectangle();

        //returns the upper left position of rectangle
        RowColumnClass getUpperLeft();

        //returns the lower right position of rectangle
        RowColumnClass getLowerRight();

        //returns color of rectangle
        ColorClass getColor();

        //returns if rectangle is filled
        bool getFill();

        //returns true if the current position is on the border of the rectangle
        //inout indexes are relative to upper left position
        bool checkBorder(int rowIdx, int colIdx);

        //sets width and height attributes
        void setHghtWdth(int inHeight, int inWidth);

        //sets upper left position of rectangle from user inputs
        void setUpperLeft(string desc, int minRow, int minCol);

        //sets color of rectanlge from user input
        void setColor(string desc);

        //returns height of rectangle
        int getHght();

        //returns width of rectangle
        int getWdth();

        //returns end row of rectangle based on upper left position.  
        //To be used for looping (use < for arrays)
        int getEndRow();

        //returns end column of rectangle based on upper left position.
        //To be used for looping (use < for arrays)
        int getEndCol();

        //returns upper left row index
        int getUpperLeftRow();

        //returns upper left column index
        int getUpperLeftCol();

        //translates array indexes that are relative to upper left position
        void translateIdx(int &rowIdx, int &colIdx);
    
    private:
        int width;
        int height;
        ColorClass color;
        bool fill;
        RowColumnClass upperLeft;

        //sets size of rectangle based on user input. 3 options
        void setSize();

        //sets size of rectangle based on upper left and lower right row/col
        void useCornerPos();

        //sets size of rectangle based on upper left and height/width
        void useWdthHght();

        //sets size of rectangle based on center and half # of rows/columns
        void useCenter();

        //sets fill attribute based on user input
        void setFill();

        //prompts user for integer input
        int promptIntInput(string msg, int minNum);

        //performs error checking on user input
        bool checkIntInput(int input, int minNum);

};

#endif