#include "checkMenuChoice.h"

int checkMenuChoice(string menuMsg, const int NUM_CHOICES)
{
    int menuChoice;
    bool validInputFound = false;
    const int MIN_CHOICES = 1; //cant have < 1 choice

    while (!validInputFound)
    {
        cout << menuMsg;
        cin >> menuChoice;

        if (cin.fail())
        {   
            cin.clear(); 
            cin.ignore(200, '\n');
            cout << endl;
        }
        else if (menuChoice > NUM_CHOICES || menuChoice < MIN_CHOICES)
        {
            cin.ignore(200, '\n');  //ignore anything left in buffer
            cout << "Int must be between 1 and " << NUM_CHOICES;
            cout << endl;
        }
        else
        {
            validInputFound = true;
        }
    }

    cin.ignore(200, '\n'); //ignore anything left in buffer
    
    return menuChoice;
}