#include "ColorImageClass.h"

ColorImageClass::ColorImageClass()
{
    pixelArr = 0;
}

ColorImageClass::~ColorImageClass()
{
    if (pixelArr) //only delete pointers if they exist
    {
        for (int i = 0; i < imgRec.getHght(); i++)
        {
            delete [] pixelArr[i];
        }
        delete [] pixelArr;
    }
}

bool ColorImageClass::readImageFile(string &errMsg)
{
    ifstream inFile;
    bool success = false;
    bool isOpen = false;
    string imgFileMsg = "Enter string for PPM image file name to load: ";
    string eofVals = "";

    isOpen = openInputFile(inFile, imgFileMsg, errMsg);

    if (isOpen)
    {
        //file must contain valid header, height/width, max RBG, and pixels
        if (processMagicNum(inFile, errMsg) &&
            processHghtWdth(inFile, errMsg) && 
            checkRbgVal(inFile, errMsg) && 
            processPixels(inFile, errMsg))
        {
            inFile >> eofVals; //extract anything leftover

            //make sure no extra values/junk at end of file
            if (inFile.eof() && eofVals == "")
            {
                success = true;
            }
            else
            {
                errMsg = "Too many pixel values for width and height.";
            }
        }
        
        inFile.close(); //always close file
    }

    return success;
}

bool ColorImageClass::openInputFile(ifstream &inFile, 
                                    string imgFileMsg,
                                    string &errMsg)
{
    string imgFileName;
    bool success = false;

    cout << imgFileMsg;
    cin >> imgFileName;

    inFile.open(imgFileName.c_str());

    if (inFile.fail())
    {
        errMsg = "Unable to open input file!";
    }
    else
    {
        success = true;
    }
    
    return success;
}

bool ColorImageClass::processMagicNum(ifstream &inFile, string &errMsg)
{
    bool success = false;
    string magicNum;

    if (inFile >> magicNum)
    {
        success = (magicNum == MAGIC_NUM);

        if (!success)
        {
            errMsg = "File header does not contain P3";
        }
        
    }
    else
    {
        errMsg = "Unable to read file header.";
    }
    

    return success;
}
bool ColorImageClass::processHghtWdth(ifstream &inFile, string &errMsg)
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
            imgRec.setHghtWdth(inHeight, inWidth);
        }
        else
        {
            //technically this is valid, but let's error out b/c we can't
            //do anything with a blank image
            errMsg = "Image is blank.";
        }
        
    }
    else
    {
        errMsg = "Unable to read integers for width and height.";
    }
    

    return success;
}

bool ColorImageClass::checkRbgVal(ifstream &inFile, string &errMsg)
{
    bool success = false;
    int rbg;

    if (inFile >> rbg)
    {
        success = (rbg == MAX_RBG);

        if (!success)
        {
            errMsg = "Max pixel value does not equal 255";
        }
    }
    else
    {
        errMsg = "Unable to read integer for max pixel value.";
    }
    

    return success;
}

bool ColorImageClass::processPixels(ifstream &inFile, string &errMsg)
{
    ColorClass pixel;
    bool success = false;
    bool pixelSuccess = true;

    initPixelArr();  //allocate pixel array

    for (int i = 0; i < imgRec.getHght() && pixelSuccess; i++)
    {
        for (int j = 0; j < imgRec.getWdth() && pixelSuccess; j++)
        {
           pixelSuccess = pixel.readImageFile(inFile, errMsg);
           
           if (pixelSuccess)
           {
               pixelArr[i][j] = pixel;
           }
        }
    }
    
    if (pixelSuccess) //if all pixels look good, return true
    {
        success = true;
    }

    return success;
}

void ColorImageClass::initPixelArr()
{
 pixelArr = new ColorClass*[imgRec.getHght()];

    for (int i = 0; i < imgRec.getHght(); i++)
    {
        pixelArr[i] = new ColorClass[imgRec.getWdth()];
    }
}

bool ColorImageClass::writeImageFile(string &errMsg)
{
    ofstream outFile;
    bool success = false;
    bool isOpen = false;
    string imgFileMsg = "Enter string for PPM image file name to output: ";

    isOpen = openOutputFile(outFile, imgFileMsg, errMsg);

    if (isOpen)
    {
        success = true;
        writePixels(outFile);   
        outFile.close(); //always close file
    }

    return success;
}

bool ColorImageClass::openOutputFile(ofstream &outFile,
                                        string imgFileMsg,
                                        string &errMsg)
{
    string imgFileName;
    bool success = false;

    cout << imgFileMsg;
    cin >> imgFileName;

    outFile.open(imgFileName.c_str());

    if (outFile.fail())
    {
        errMsg = "Unable to open output file!";
    }
    else
    {
        success = true;
    }
    
    return success;
}

void ColorImageClass::writePixels(ofstream &outFile)
{
    ColorClass pixel;
    bool leadingSpace = false;
    int fistCol = 0;
    
    writeMagicNum(outFile);
    writeHghtWdth(outFile);
    writeMaxRbg(outFile);
    
    for (int i = 0; i < imgRec.getHght(); i++)
    {
        outFile << "\n";

        for (int j = 0; j < imgRec.getWdth(); j++)
        {
           pixel = pixelArr[i][j];

           //no leading space for first value in row
           leadingSpace = (j != fistCol);
           pixel.writeImageFile(outFile, leadingSpace); 
        }
    }
}

void ColorImageClass::writeMagicNum(ofstream &outFile)
{
    outFile << MAGIC_NUM;
}

void ColorImageClass::writeHghtWdth(ofstream &outFile)
{
    outFile << "\n" << imgRec.getWdth() << " " << imgRec.getHght();
}

void ColorImageClass::writeMaxRbg(ofstream &outFile)
{
    outFile << "\n" << MAX_RBG;
}

bool ColorImageClass::setColorAtLocation(
                      RowColumnClass &inRowCol,
                      ColorClass &inColor
                      )
{
    int inRow = inRowCol.getRow();
    int inCol = inRowCol.getCol();
    ColorClass pixel;
    bool isLocValid = getColorAtLocation(inRowCol, pixel);
    
    if (isLocValid)  //only update if location is valid
    {
        pixel.setTo(inColor); 
        pixelArr[inRow][inCol] = pixel;
    } 
    
    //if the location is valid the pixel will always be updated
    return isLocValid;
}

bool ColorImageClass::getColorAtLocation(
                      RowColumnClass &inRowCol,
                      ColorClass &outColor
                      )
{
    bool isValidLoc = false;
    int inRow = inRowCol.getRow();
    int inCol = inRowCol.getCol();
    const int MIN_ROW_COL = 0;
    
    //check if passed in rowCol is within size of image
    //rowCol class not guaranteed to be positive, so need to check
    //first and last pixel
    if ( inRow < imgRec.getHght() && inCol < imgRec.getWdth() && 
         inRow >= MIN_ROW_COL && inCol >= MIN_ROW_COL
        )  
    {
        isValidLoc = true;
        outColor = pixelArr[inRow][inCol];
    }

    return isValidLoc;
}

bool ColorImageClass::annotateRectangle(string &errMsg)
{
    RectangleClass  annotateRec;
    bool success = false;
    RowColumnClass currentRowCol;
    bool foundInvalidLoc = false;
    annotateRec.createRectangle();  //create rectangle from user inputs
    int startRowIdx = annotateRec.getUpperLeftRow();
    int startColIdx = annotateRec.getUpperLeftCol();
    ColorClass pixel = annotateRec.getColor();

    //safety check since this is public: must have valid image loaded
    if (checkArrValid(errMsg))
    {
        for (int i = startRowIdx; i < annotateRec.getEndRow(); i++)
        {
            for (int j = startColIdx; j < annotateRec.getEndCol(); j++)
            {
                currentRowCol.setRowCol(i, j);
                
                //set pixel if we're filling in entire rectangle or 
                //we're on the border
                if (annotateRec.getFill() || annotateRec.checkBorder(i, j))
                {
                    
                    if (setColorAtLocation(currentRowCol, pixel))
                    {
                        success = true;  //if we update one pixel, we succeed
                    }
                    else
                    {
                        foundInvalidLoc = true;
                    }
                }
            }
        }

        if (success && foundInvalidLoc)
        {
            cout << "Warning: Only partial rectangle added to image" << endl;
        }
        else if (!success)
        {
            errMsg = "Rectangle did not fit within image";
        }
    }

    return success;
}

bool ColorImageClass::addPattern(string &errMsg)
{
    PatternClass pattern;
    RectangleClass patternRec;
    ColorClass patternColor;
    int startRowIdx = 0;
    int startColIdx = 0;
    RowColumnClass currentRowCol;
    bool foundInvalidLoc = false;
    bool foundPattern = false;
    bool success = false;
    
    //must have valid image loaded and successfully read in pattern file
    if (checkArrValid(errMsg) && pattern.readPatternFile(errMsg))
    {
        //get pattern rectangle
        patternRec = pattern.getRec();
        patternColor = patternRec.getColor();
        startRowIdx = patternRec.getUpperLeftRow();
        startColIdx = patternRec.getUpperLeftCol();
        
        for (int i = startRowIdx; i < patternRec.getEndRow(); i++)
        {
            for (int j = startColIdx; j < patternRec.getEndCol(); j++)
            {
                currentRowCol.setRowCol(i, j);

                //only update pixel if pattern value = 1
                if(pattern.getPatternVal(i, j))
                {
                    foundPattern = true;
                    
                    if (setColorAtLocation(currentRowCol, patternColor))
                    {
                        success = true;  //if we update one pixel, we succeed
                    }
                    else
                    {
                        foundInvalidLoc = true;
                    }
                }
            }
        }

        if (success && foundInvalidLoc)
        {
            cout << "Warning: Only partial pattern added to image" << endl;
        }
        else if (!foundPattern)
        {
            //pattern could be all zeroes, so technically this is valid
            //but lets warn the user
            success = true;
            cout << "Warning: Pattern is blank. Image not updated" << endl;
        }
        else
        {
            errMsg = "Pattern outside bounds of image";
        }
        
    }

    return success;
}

bool ColorImageClass::checkArrValid(string &errMsg)
{
    bool isValid = false;
    
    if (!pixelArr)  //don't operate on null pointer
    {
        errMsg = "No valid image file currently loaded";
    }
    else
    {
        isValid = true;
    }
    
    return isValid;
}

bool ColorImageClass::insertImage(string &errMsg)
{
    ColorImageClass insrtImg;
    bool success = false;
    int startRowIdx = 0;
    int startColIdx = 0;
    ColorClass pixel;
    RowColumnClass currentRowCol;
    RowColumnClass insrtImgRowCol;
    bool foundInvalidLoc = false;
    bool foundNonTransparent = false;
    string upLeDesc = "upper left corner";
    string colorDesc = "transparency";
    const int MIN_ROW_COL = 0;

    //must have valid image loaded and successfully read in image file
    if (checkArrValid(errMsg) && insrtImg.readImageFile(errMsg))
    {
        //set position/color of insertion image
        insrtImg.imgRec.setUpperLeft(upLeDesc, MIN_ROW_COL , MIN_ROW_COL);
        insrtImg.imgRec.setColor(colorDesc);

        startRowIdx = insrtImg.imgRec.getUpperLeftRow();
        startColIdx = insrtImg.imgRec.getUpperLeftCol();
        
        for (int i = startRowIdx; i < insrtImg.imgRec.getEndRow(); i++)
        {
            for (int j = startColIdx; j < insrtImg.imgRec.getEndCol(); j++)
            {
                currentRowCol.setRowCol(i, j);
                //set pixel only if not transparentColor
                if (insrtImg.checkTransparency(i, j, pixel))
                {
                    foundNonTransparent = true;
                    
                    if (setColorAtLocation(currentRowCol, pixel))
                    {
                        success = true;  //if we update one pixel, we succeed
                    }
                    else
                    {
                        foundInvalidLoc = true;
                    }
                }
            }
        }

        if (success && foundInvalidLoc)
        {
            cout << "Warning: Only partial image inserted" << endl;
        }
        else if (!foundNonTransparent)
        {
            //we never found a pixel that did not match transparency color
            success = true;
            cout << "Warning: Insertion image is completely transparent. "; 
            cout << "Image not updated" << endl;
        }
        else
        {
            errMsg = "Insertion outside bounds of image.";
        }
        
    }
    
    return success;
}

bool ColorImageClass::checkTransparency(int rowIdx, 
                                        int colIdx, 
                                        ColorClass &pixel)
{
    bool updatePixel = false;
    ColorClass transparencyColor;
    RowColumnClass rowCol;
    
    //indexes currently relative to upper left position
    imgRec.translateIdx(rowIdx, colIdx);

    rowCol.setRowCol(rowIdx, colIdx);

    if (getColorAtLocation(rowCol, pixel))
    {
        transparencyColor = imgRec.getColor();
        
        //we want to update pixel if it is not the same as the transparency
        //color and is in a valid location
        updatePixel = !pixel.compareColors(transparencyColor);
    }
    
    return updatePixel;
}

void ColorImageClass::outputErrors(bool &hasError, string errMsg)
{
    if(hasError)
    {
        cout << "Error: " << errMsg << endl;

        //reset
        hasError = false;
        errMsg = "";
    }
}