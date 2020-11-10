#include <string>
#include "ColorImageClass.h"
#include "checkMenuChoice.h"
using namespace std;


//Author: Andrew Heldrich
//Date: 28 10 2020
//Purpose:  implements menu for reading, writing, annotating, altering, etc
//          ppm imagaes

//Revision History:

int main()
{
    bool hasError = false;
    bool isDone = false;
    const int ANNOTATE_REC = 1;
    const int ADD_PATTERN = 2;
    const int INSERT_IMG = 3;
    const int WRITE_IMG = 4;
    const int EXIT_MENU = 5;
    const int MAIN_MNU_CHOICES = 5;
    int menuChoice = EXIT_MENU;
    string mainMenuMsg = "Enter int for main menu choice: ";
    ColorImageClass image;
    string errMsg = "";

    hasError = !image.readImageFile(errMsg);

    while ( !hasError && !isDone)  //main menu
    {
        cout << "1. Annotate image with rectangle" << endl;
        cout << "2. Annotate image with pattern from file" << endl;
        cout << "3. Insert another image" << endl;
        cout << "4. Write out current image" << endl;
        cout << "5. Exit the program" << endl;
        
        menuChoice = checkMenuChoice(mainMenuMsg, MAIN_MNU_CHOICES);

        if (menuChoice == ANNOTATE_REC)
        {
            hasError = !image.annotateRectangle(errMsg);
        }
        else if (menuChoice == ADD_PATTERN)
        {
            hasError = !image.addPattern(errMsg);
        }
         else if (menuChoice == INSERT_IMG)
        {
            hasError = !image.insertImage(errMsg);
        }
         else if (menuChoice == WRITE_IMG)
        {
            hasError = !image.writeImageFile(errMsg);
        }
         else if (menuChoice == EXIT_MENU)
        {
            isDone = true;
            cout << "Thank you for using this program." << endl;
        }
        
        //this resets errors so we go back to menu
        image.outputErrors(hasError, errMsg); 
    }
    
    image.outputErrors(hasError, errMsg);

    return 0;
}