#ifndef _ROWCOLUMNCLASS_H_
#define _ROWCOLUMNCLASS_H_

#include <iostream>
#include <string>
using namespace std;

class RowColumnClass
{
    public:
        //Default ctor, initializes row/columns -99999
        RowColumnClass();

        //initializes object with passed in values
        RowColumnClass(int inRow, int inCol);
        
        //sets the row and column values to corresponding parameter values
        void setRowCol(int inRow, int inCol);

        //sets the row attribute to the corresponding parameter value
        void setRow(int inRow);

        //sets the column attribute to the corresponding parameter value
        void setCol(int inCol);

        //gets the row attribute
        int getRow();

        //gets the column attribute
        int getCol();

        //adds the row and column index value of the passed in object
        // to the row and column index of the calling object
        void addRowColTo(RowColumnClass &inRowCol);

        //prompts user for row/col indexes and sets attributes
        void promptRowColInput(string desc, int minRow, int minCol);

    private:
        int row;
        int col;
};

#endif