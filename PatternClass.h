#ifndef _PATTERNCLASS_H_
#define _PATTERNCLASS_H_

#include <iostream>
#include <fstream>
#include <string>
#include "checkMenuChoice.h"
#include "ColorClass.h"
#include "RowColumnClass.h"
#include "RectangleClass.h"
using namespace std;

class PatternClass
{
    public:
        PatternClass();

        //clean up memory
        ~PatternClass();

        //reads in user-specified file
        //returns false if pattern file is invalid
        bool readPatternFile(string &errMsg);

        //returns true if pattern array exists
        bool checkArrValid(string &errMsg);

        //returns rectangle attribute
        RectangleClass getRec();

        //returns pattern value (0/1) at location
        //input index is relative to upper left position
        int getPatternVal(int rowIdx, int colIdx);
    
    private:
        int **patternArr;
        RectangleClass patternRec;

        //opens input pattern file. Returns true if file is open
        bool openInputFile(ifstream &inFile, string patFileMsg, string &errMsg);

        //returns true if valid height/width in file
        bool processHghtWdth(ifstream &inFile, string &errMsg);

        //returns true if file contains valid pattern values.
        //updates pattern array
        bool processPattern(ifstream &inFile, string &errMsg);

        //allocates memory for pattern array according to height and width
        void initPatternArr();
};

#endif