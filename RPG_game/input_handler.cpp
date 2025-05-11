#include "input_handler.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

int InputHandler::getIntInput(const string& prompt, int min, int max) {
    int choice;
    while (true) {
        cout << prompt;
        cin >> choice;

        if (cin.fail() || choice < min || choice > max) {
            cin.clear(); // clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << "Invalid input. Please enter a number between " << min << " and " << max << "." << endl;
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard extra input
            return choice;
        }
    }
}

string InputHandler::getStringInput(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

bool InputHandler::getYesNoInput(const string& prompt) {
    string response;
    while (true) {
        cout << prompt << " (yes/no): ";
        cin >> response;
        if (response == "yes" || response == "y") {
            return true;
        }
        else if (response == "no" || response == "n") {
            return false;
        }
        else {
            cout << "Invalid input. Please enter 'yes' or 'no'." << endl;
        }
    }
}