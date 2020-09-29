//
//  main.cpp
//  Fine
//
//  Created by Mitchell McLinton on 9/10/19.
//  Copyright © 2019 Mitchell McLinton. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

int main() {
    //Declaring constants for the bribe bracket bounds used to calculate suggestedFine; these constants will both be used in control flow
    const double LOWER_BRIBE_BRACKET_BOUND = 40.0;
    const double UPPER_BRIBE_BRACKET_BOUND = 250.0;
    
    //Gathering input data for 3 variables in 3 blocks
    cout << "Defendant: ";
    string defendantName;
    getline(cin, defendantName);
    
    cout << "Amount paid (in thousands): ";
    double amountPaid;
    cin >> amountPaid;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');        //numeric_limits<streamsize>::max() represents the upper limit of the size of the stream, in this case cin
    
    cout << "Fake athlete? (y/n): ";
    char fakeAthlete;
    cin >> fakeAthlete;
    
    //three if statements below to validate user input is in the acceptable ranges/formats; prints error message and returns -1 as error code if data does not validate correctly
    if (defendantName == "") {
        cout << "---" << endl;
        cout << "You must enter a defendant name." << endl;
        return -1;
    }
    
    if (amountPaid <= 0) {
        cout << "---" << endl;
        cout << "The amount paid must not be negative." << endl;
        return -1;
    }
    
    if ( (fakeAthlete != 'y') && (fakeAthlete != 'n') ) {
        cout << "---" << endl;
        cout << "You must enter y or n." << endl;
        return -1;
    }
    
    //Series of if statements form algorithm below to calculate suggestedFine amount
    double suggestedFine = 20.0;      //initialising suggestedFine at 20.0, as this is the base amount of the fine
    
    if (amountPaid <= LOWER_BRIBE_BRACKET_BOUND) {              //this statement checks for the lower 'bribe bracket' of amountPaid <= $40,000
        suggestedFine += 0.66 * amountPaid;
    } else if (amountPaid <= UPPER_BRIBE_BRACKET_BOUND) {      //this statement checks for the middle 'bribe bracket' of $40,000 < amountPaid <= $250,000 (no need to check amountPaid > 40.0)
        suggestedFine += 0.66 * 40.0;
        if (fakeAthlete == 'y') {            //checking whether athlete credentials were faked
            suggestedFine += 0.22 * (amountPaid - 40.0);
        } else {
            suggestedFine += 0.10 * (amountPaid - 40.0);
        }
    } else {           //this statement does not specifically check for anything, but covers the case of the upper 'bribe bracket' of amountPaid > 250,000
        suggestedFine += 0.66 * 40.0;
        if (fakeAthlete == 'y') {
            suggestedFine += 0.22 * 210.0;
        } else {
            suggestedFine += 0.10 * 210.0;
        }
        suggestedFine += 0.14 * (amountPaid - 250.0);
    }
    
    cout.setf(ios_base::fixed);     //sets flag for fixed number of decimal points to be printed for doubles
    cout.precision(1);              //sets precision of the printed decimal points to be that of 1 d.p.
    
    //Printing suggestedFine to the console
    cout << "---" << endl;
    cout << "The suggested fine for " << defendantName << " is $" << suggestedFine << " thousand." << endl;
}
