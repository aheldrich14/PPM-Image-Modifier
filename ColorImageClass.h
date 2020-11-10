#ifndef _COLORIMAGECLASS_H_
#define _COLORIMAGECLASS_H_

#include <fstream>
#include "RowColumnClass.h"
#include "ColorClass.h"
#include "RectangleClass.h"
#include "PatternClass.h"
#include "constants.h"

class ColorImageClass
{
    public:
        ColorImageClass();

        //cleans up memory
        ~ColorImageClass();

        //set pixel at location to color
        //returns true if the pixel was updated
        bool setColorAtLocation(RowColumnClass &inRowCol, ColorClass &inColor);

        //outputs outColor to color at location
        //returns True if the location is a valid row/column for image
        //otherwise outColor is not updated
        bool getColorAtLocation(RowColumnClass &inRowCol, ColorClass &outColor);

        //reads in file from user input
        //returns false if invalid image file found or unable to open file
        bool readImageFile(string &errMsg);

        //writes file with user-specified filename
        //returns false if unable to open file
        bool writeImageFile(string &errMsg);

        //adds rectangle to image at user-specified location
        //returns false if rectangle cannot be added 
        bool annotateRectangle(string &errMsg);

        //adds pattern to image at user-specified location
        //returns false if pattern cannot be added 
        bool addPattern(string &errMsg);

        //returns true if we have an allocated pixel array
        bool checkArrValid(string &errMsg);

        //inserts image at user-specified location
        //returns false if image cannot be inserted or is an invalid image  
        bool insertImage(string &errMsg);

        //outputs errors in msg string from any operation
        //resets hasError and errMsg
        void outputErrors(bool &hasError, string errMsg);

    private:
        ColorClass **pixelArr;
        RectangleClass imgRec;

        //prompts user for input file, returns true if file is open
        bool openInputFile(ifstream &inFile, string imgFileMsg, string &errMsg);

        //prompts user for input file, returns true if file is open
        bool openOutputFile(ofstream &outFile,
                            string imgFileMsg,
                            string &errMsg);
        
        //returns true if file contains P3 in header
        bool processMagicNum(ifstream &inFile, string &errMsg);

        //returns true if file contains valid width and height.
        //updates rectangle attribute
        bool processHghtWdth(ifstream &inFile, string &errMsg);

        //returns true if file contains correct max rbg value of 255
        bool checkRbgVal(ifstream &inFile, string &errMsg);

        //returns true if file contains valid RBG values for entire image
        //populates pixel array
        bool processPixels(ifstream &inFile, string &errMsg);

        //allocates memory for pixel array according to width and height
        void initPixelArr();

        //writes pixels to output file
        void writePixels(ofstream &outFile);

        //writes P3 to header of output file
        void writeMagicNum(ofstream &outFile);

        //writes width/height of image to output file
        void writeHghtWdth(ofstream &outFile);

        //writes 255 to output file
        void writeMaxRbg(ofstream &outFile);

        //returns true if pixel at location should be updated (ie does not match
        //transparency color). 
        bool checkTransparency(int rowIdx, int colIdx, ColorClass &pixel);

};

#endif