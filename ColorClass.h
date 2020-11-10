#ifndef _COLORCLASS_H_
#define _COLORCLASS_H_

#include <iostream>
#include <fstream>
#include <string>
#include "checkMenuChoice.h"
using namespace std;

class ColorClass
{
    public:
        //default ctor, initializes to white
        ColorClass();

        //init class
        ColorClass(int inRed, int inGreen, int inBlue);

        //sets all colors to zeroes
        void setToBlack();

        //sets to full red and all else zeroes
        void setToRed();

        //sets to full green and all else zeroes
        void setToGreen();

        //sets to full blue and all else zeroes
        void setToBlue();

        //sets all colors to full
        void setToWhite();

        //sets rbg attributes 
        //returns True if any values were clipped to remain in allowed range
        bool setTo(int inRed, int inGreen, int inBlue);

        //sets colors to sames colors of passed on object
        //returns True if any values were clipped to remain in allowed range
        bool setTo(ColorClass &inColor);

        //adds colors of passed in obejct to current colors
        //returns True if any values were clipped to remain in allowed range
        bool addColor(ColorClass &rhs);

        //subtracts colors of passed in object from current colors
        //returns True if any values were clipped to remain in allowed range
        bool subtractColor(ColorClass &rhs);

        //brightens current colors by adjustment factor
        //returns True if any values were clipped to remain in allowed range
        bool adjustBrightness(double adjFactor);

        //prints red, green, blue values in format  
        //"R: <red> G: <green> B: <blue>"
        void printComponentValues();

        //reads in values for red, blue, green. Assumes file is already open
        //returns false if RBG values couldn't be read in
        bool readImageFile(ifstream &inFile, string &errMsg);

        //writes RBG values to file
        void writeImageFile(ofstream &outFile, bool leadingSpace);

        //prompts user to set color
        void promptColorInput(string desc);

        //returns true if input color is the same as current color
        bool compareColors(ColorClass &inColor);
    
    private:
        int red;
        int green;
        int blue;

        //checks if color value in range, returns new rbg value in correct range
        //tracks if input value was clipped
        int checkColorValue(int inRbgVal, int &numClips);

        //stores max RBG for class
        static int maxRbg;

        //stores min RBG for class
        static int minRbg;

};

#endif