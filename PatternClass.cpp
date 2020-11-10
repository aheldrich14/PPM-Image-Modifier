#include "PatternClass.h"

PatternClass::PatternClass()
{
    patternArr = 0;
}
PatternClass::~PatternClass()
{
    if (patternArr) //only delete pointers if they exist
    {
        for (int i = 0; i < patternRec.getHght(); i++)
        {
            delete [] patternArr[i];
        }
        delete [] patternArr;
    }
}
bool PatternClass::readPatternFile(string &errMsg)
{
    ifstream inFile;
    bool success = false;
    bool isOpen = false;
    string patFileMsg = "Enter string for file name containing pattern: ";
    const int MIN_ROW_COL = 0;
    string desc = "pattern";
    string upLeDesc = "upper left corner";
    ColorClass patternColor;
    string eofVals = "";

    isOpen = openInputFile(inFile, patFileMsg, errMsg);

    if (isOpen)
    {
        if (processHghtWdth(inFile, errMsg) && processPattern(inFile, errMsg))
        {
            inFile >> eofVals; //extract anything leftover

            //make sure no extra values/junk at end of file
            if (inFile.eof() && eofVals == "")
            {
                success = true;
                patternRec.setUpperLeft(upLeDesc, MIN_ROW_COL, MIN_ROW_COL);
                patternRec.setColor(desc);
            }
            else
            {
                errMsg = "Too many pattern values for width and height.";
            }
        }
        
        inFile.close(); //always close file
    }

    return success;
}
bool PatternClass::openInputFile(ifstream &inFile,
                                    string patFileMsg,
                                    string &errMsg)
{
    string imgFileName;
    bool success = false;

    cout << patFileMsg;
    cin >> imgFileName;

    inFile.open(imgFileName.c_str());

    if (inFile.fail())
    {
        errMsg = "Unable to open pattern file!";
    }
    else
    {
        success = true;
    }
    
    return success;
}
bool PatternClass::processHghtWdth(ifstream &inFile, string &errMsg)
{
    bool success = false;
    const int MIN_WDTH_HGHT = 1;
    int inWidth = 0;
    int inHeight = 0;

    if (inFile >> inWidth >> inHeight)
    {
        if (inWidth >= MIN_WDTH_HGHT && inHeight >= MIN_WDTH_HGHT)
        {
            success = true;
            patternRec.setHghtWdth(inHeight, inWidth);
        }
        else
        {
            errMsg = "Pattern width and height must be at least 1 pixel.";
        }
        
    }
    else
    {
        errMsg = "Unable to read integers for width and height of pattern.";
    }
    

    return success;
}
bool PatternClass::processPattern(ifstream &inFile, string &errMsg)
{
    int pattern;
    const int NO_PATTERN = 0;
    const int PATTERN = 1;
    bool success = false;
    bool patternSuccess = true;

    initPatternArr();  //allocate pattern array

    //do not continue if we find one bad pattern value
    for (int i = 0; i < patternRec.getHght() && patternSuccess; i++)
    {
        for (int j = 0; j < patternRec.getWdth() && patternSuccess; j++)
        {
           
           if(inFile >> pattern)
           {
                if (pattern != NO_PATTERN && pattern != PATTERN)
                {
                    patternSuccess = false; //pattern must be 1/0
                    errMsg = "Pattern value must be 1 or 0.";
                }
                else  //successfully read 1 or 0
                {
                    patternArr[i][j] = pattern;
                }
           }
           else if (inFile.eof())
           {
               //we ran out of patterns to read in!
               patternSuccess = false;
               errMsg = "Not enough pattern values in file.";
           }
           else  //didn't read in an int
           {
               patternSuccess = false; 
               errMsg = "Unable to read integer for pattern value";
           }
           
        }
    }
    
    if (patternSuccess) //if all pattern vals look good, return true
    {
        success = true;
    }

    return success;
}
void PatternClass::initPatternArr()
{
    patternArr = new int*[patternRec.getHght()];

    for (int i = 0; i < patternRec.getHght(); i++)
    {
        patternArr[i] = new int[patternRec.getWdth()];
    }
}
RectangleClass PatternClass::getRec()
{
    return patternRec;
}
int PatternClass::getPatternVal(int rowIdx, int colIdx)
{
    //input index is currently relative to upper left position
    //need to convert it to actual location in array
    patternRec.translateIdx(rowIdx, colIdx);
 
    return patternArr[rowIdx][colIdx];
}

