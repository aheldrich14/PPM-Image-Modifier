#include "ColorClass.h"

ColorClass::ColorClass()
{
    setToWhite();
}

ColorClass::ColorClass(int inRed, int inGreen, int inBlue)
{
    setTo(inRed, inGreen, inBlue);
}

void ColorClass::setToBlack()
{
    setTo(minRbg, minRbg, minRbg);
}

void ColorClass::setToRed()
{
    setTo(maxRbg, minRbg, minRbg);
}

void ColorClass::setToGreen()
{
    setTo(minRbg, maxRbg, minRbg);
}

void ColorClass::setToBlue()
{
    setTo(minRbg, minRbg, maxRbg);
}

void ColorClass::setToWhite()
{
    setTo(maxRbg, maxRbg, maxRbg);
}

bool ColorClass::setTo(int inRed, int inGreen, int inBlue)
{
    int numClips = 0;  //keep track of how many times we clipped rbg values
    bool clipped = false;
    
    red = checkColorValue(inRed, numClips);
    green = checkColorValue(inGreen, numClips);
    blue = checkColorValue(inBlue, numClips);

    if (numClips > 0)   // if any rbg value was clipped, we want to return true
    {
        clipped = true;
    }

    return clipped;
}

bool ColorClass::setTo(ColorClass &inColor)
{
    //returns true if values clipped
    return setTo(inColor.red, inColor.green, inColor.blue);
}

bool ColorClass::addColor(ColorClass &rhs)
{
    int newRed = red + rhs.red;
    int newGreen = green + rhs.green;
    int newBlue = blue + rhs.blue;

    //returns true if values clipped
    return setTo(newRed, newGreen, newBlue);

}

bool ColorClass::subtractColor(ColorClass &rhs)
{
    int newRed = red - rhs.red;
    int newGreen = green - rhs.green;
    int newBlue = blue - rhs.blue;

    //returns true if values clipped
    return setTo(newRed, newGreen, newBlue);
}

bool ColorClass::adjustBrightness(double adjFactor)
{
    double newAdjFactor = adjFactor;
    const double MIN_FACTOR = 0;

    if (adjFactor < MIN_FACTOR)  // neg adj factor doesn't make any sense
    {
        newAdjFactor = MIN_FACTOR;
    }
    
    int newRed = int(red * newAdjFactor);
    int newGreen = int(green * newAdjFactor);
    int newBlue = int(blue * newAdjFactor);

    //returns true if values clipped
    return setTo(newRed, newGreen, newBlue);
}

int ColorClass::checkColorValue(int inRbgVal, int &numClips)
{
    int newRbg = inRbgVal; // set new RBG to passed in value by default

    if (inRbgVal < minRbg)
    {
        numClips++;
        newRbg = minRbg;
    }
    else if (inRbgVal > maxRbg)
    {
        numClips++;
        newRbg = maxRbg;
    }

    return newRbg;
}

void ColorClass::printComponentValues()
{
    cout << "R: " << red << " G: " << green << " B: " << blue;
}

bool ColorClass::readImageFile(ifstream &inFile, string &errMsg)
{
    bool success = false;
    int inRed = 0;
    int inGreen = 0;
    int inBlue = 0;
    
    if (inFile >> inRed >> inGreen >> inBlue)
    {
        setTo(inRed, inGreen, inBlue);
        success = true;
    }
    else if (inFile.eof()) //at eof but needed to read in more values
    {
        errMsg = "Not enough pixel values in file.";
    }
    else
    {
        errMsg = "Unable to read integers for red, blue, and green values.";
    }

    return success;
}

void ColorClass::writeImageFile(ofstream &outFile, bool leadingSpace)
{
    if (leadingSpace)
    {
        outFile << " ";
    }
    
    outFile << red << " " << green << " " << blue;
}
void ColorClass::promptColorInput(string desc)
{
    const int RED = 1;
    const int GREEN = 2;
    const int BLUE = 3;
    const int BLACK = 4;
    const int WHITE = 5;
    const int MNU_CHOICES = 5;
    int menuChoice = 1;
    string mainMenuMsg = "Enter int for " + desc + " color: ";
    
    cout << "1. Red" << endl;
    cout << "2. Green" << endl;
    cout << "3. Blue" << endl;
    cout << "4. Black" << endl;
    cout << "5. White" << endl;
        
    menuChoice = checkMenuChoice(mainMenuMsg, MNU_CHOICES);

    if (menuChoice == RED)
    {
        setToRed();
    }
    else if (menuChoice == GREEN)
    {
        setToGreen();
    }
    else if (menuChoice == BLUE)
    {
        setToBlue();
    }
    else if (menuChoice == BLACK)
    {
        setToBlack();
    }
    else if (menuChoice == WHITE)
    {
        setToWhite();
    }
}

bool ColorClass::compareColors(ColorClass &inColor)
{
    bool isSameColor = false;

    if (inColor.red == red && inColor.green == green && inColor.blue == blue)
    {
        isSameColor = true;
    }

    return isSameColor;
}

int ColorClass::maxRbg = 255;

int ColorClass::minRbg = 0;