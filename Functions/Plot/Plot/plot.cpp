//
//  plot.cpp
//  Plot
//
//  Created by Mitchell McLinton on 25/10/19.
//  Copyright © 2019 Mitchell McLinton. All rights reserved.
//

#include "grid.h"
#include <iostream>
#include <string>
using namespace std;

const int HORIZ = 0;
const int VERT = 1;

const int FG = 0;
const int BG = 1;

void bgPlot(int r, int c, char plotChar);

void plotHorizontalLine(int& currentRow, int& currentCol, int distance, char plotChar, int fgbg);
void plotVerticalLine(int& currentRow, int& currentCol, int distance, char plotChar, int fgbg);

bool areAllPointsInGrid(int r, int c, int distance, int dir);
bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg);

bool translateInstructionString(string commandString, char& plotChar, int& mode, int& badPos, bool& syntaxErrorFlag, int& plottingErrorPos);
bool processCCommand(string commandString, int& position, char& plotChar, int& mode, int& currentRow, int& currentCol);
bool processFCommand(string commandString, int& position, char& plotChar, int& mode, int& currentRow, int& currentCol);
bool processBCommand(string commandString, int& position, char& plotChar, int& mode, int& currentRow, int& currentCol);
bool processHCommand(string commandString, int& position, char& plotChar, int& mode, int& currentRow, int& currentCol, bool& syntaxErrorFlag);
bool processVCommand(string commandString, int& position, char& plotChar, int& mode, int& currentRow, int& currentCol, bool& syntaxErrorFlag);

bool scanForSyntax(string commandString, int& badPos);

int performCommands(string commandString, char& plotChar, int& mode, int& badPos);

int main() {
    setSize(20, 30);
    
    char currentChar = '*';
    int currentMode = FG;
    
    for (;;) {
        cout << "Enter a command string: ";
        string commandString;
        getline(cin, commandString);
        
        if (commandString == "") {
            break;
        }
        
        int position;
        int status = performCommands(commandString, currentChar, currentMode, position);

        switch (status) {
            case 0:
                draw();
                break;
            case 1:
                cout << "Syntax error at position " << position+1 << endl;
                break;
            case 2:
                cout << "Cannot perform command at position " << position+1 << endl;
                break;
            default:
                // It should be impossible to get here.
                cerr << "performCommands returned " << status << "!" << endl;
                break;
        }
    }
}

void bgPlot(int r, int c, char plotChar) {
    if (getChar(r, c) == ' ') { //for background plot, it only plots if the existing character at (r, c) is a space (' ');
        setChar(r, c, plotChar);
    }
}

void plotHorizontalLine(int& currentRow, int& currentCol, int distance, char plotChar, int fgbg) {
    if (distance > 0) { //this is the if block for a +ive distance value, which corresponds to a rightward line from (r, c)
        for (int i=currentCol; i<=(currentCol+distance); i++) {
            if (i<=getCols() && i > 0) {
                if (fgbg == FG) {   //checking if we are plotting in foreground or background; for foreground, it plots regardless of the existing character at (r, c)
                    setChar(currentRow, i, plotChar);
                } else if (fgbg == BG) {    //this should always validate to true if the if statement above fails
                    bgPlot(currentRow, i, plotChar);
                }
            }
        }
    } else if (distance < 0) {  //this is the if block for a -ive distance value, which corresponds to a leftward line from (r, c)
        distance = abs(distance);   //setting distance to the absolute value of itself here to get a 'proper distance' value
        for (int i=currentCol; i>=(currentCol-distance); i--) {
            if (i<=getCols() && i > 0) {
                if (fgbg == FG) {   //checking if we are plotting in foreground or background; for foreground, it plots regardless of the existing character at (r, c)
                    setChar(currentRow, i, plotChar);
                } else if (fgbg == BG) {    //this should always validate to true if the if statement above fails
                    bgPlot(currentRow, i, plotChar);
                }
            }
        }
    } else {    //this else statement should cover for distance = 0, which corresponds to a single point plot at (r, c)
        if (currentCol<=getCols() && currentCol > 0) { //this statement should always validate true, as if c is not in bounds, plotLine should've returned false already
            if (fgbg == FG) {   //checking if we are plotting in foreground or background; for foreground, it plots regardless of the existing character at (r, c)
                setChar(currentRow, currentCol, plotChar);
            } else if (fgbg == BG) {    //this should always validate to true if the if statement above fails
                bgPlot(currentRow, currentCol, plotChar);
            }
        }
        //No need to add anything to currentCol as we have plotted at the same point we started at
    }
}

void plotVerticalLine(int& currentRow, int& currentCol, int distance, char plotChar, int fgbg) {
    if (distance > 0) { //this is the if block for a +ive distance value, which corresponds to a downward line from (r, c)
        for (int i=currentRow; i<=(currentRow+distance); i++) {
            if (i<=getRows() && i > 0) {
                if (fgbg == FG) {   //checking if we are plotting in foreground or background; for foreground, it plots regardless of the existing character at (r, c)
                    setChar(i, currentCol, plotChar);
                } else if (fgbg == BG) {    //this should always validate to true if the if statement above fails
                    bgPlot(i, currentCol, plotChar);
                }
            }
        }
        //Add the distance that the 'virtual pen' has moved to the currentRow variable
        currentRow += distance;
    } else if (distance < 0) {  //this is the if block for a -ive distance value, which corresponds to an upward line from (r, c)
        distance = abs(distance);
        for (int i=currentRow; i>=(currentRow-distance); i--) {
            if (i<=getRows() && i > 0) {
                if (fgbg == FG) {   //checking if we are plotting in foreground or background; for foreground, it plots regardless of the existing character at (r, c)
                    setChar(i, currentCol, plotChar);
                } else if (fgbg == BG) {    //this should always validate to true if the if statement above fails
                    bgPlot(i, currentCol, plotChar);
                }
            }
        }
        //Minus the distance that the 'virtual pen' has move to the currentRow variable
        currentRow -= distance;
    } else {    //this else statement should cover for distance = 0, which corresponds to a single point plot at (r, c)
        if (currentRow<=getRows() && currentRow > 0) {
            if (fgbg == FG) {   //checking if we are plotting in foreground or background; for foreground, it plots regardless of the existing character at (r, c)
                setChar(currentRow, currentCol, plotChar);
            } else if (fgbg == BG) {    //this should always validate to true if the if statement above fails
                bgPlot(currentRow, currentCol, plotChar);
            }
        }
        //No need to add anything to currentCol as we have plotted at the same point we started at
    }
}

bool areAllPointsInGrid(int r, int c, int distance, int dir) {  //only plotLine calls this function, so it implicitly relies on the fact that plotLine has already validated r and c
    if (dir == HORIZ) { //using the position iterator for horizontal lines to check if all the points of the line to be plotted are in bounds of the grid
        if (distance > 0) { //checking for a rightwards line
            for (int i=c; i<=(c+distance); i++) {
                if (i>getCols() || i < 0) {
                    cerr << "areAllPointsInGrid: (" << r << ", " << i << ") is beyond the bounds of the grid" << endl;
                    return false;
                }
            }
            return true; //if the loop runs through successfully without returning false, then all points are in the bound of the grid, therefore the function will return true;
        } else if (distance < 0) {  //checking for a leftwards line
            distance = abs(distance);
            for (int i=c; i>=(c-distance); i--) {
                if (i>getCols() || i < 0) {
                    cerr << "areAllPointsInGrid: (" << r << ", " << i << ") is beyond the bounds of the grid" << endl;
                    return false;
                }
            }
            return true; //if the loop runs through successfully without returning false, then all points are in the bound of the grid, therefore the function will return true;
        } else {    //this else block is processed if distance = 0
            return true;    //r and c have already been validated to be in or out of bounds by plotLine, so no further checks are required if distance = 0; therefore true returned automatically
        }
    } else if (dir == VERT) {   //using the position iterator for vertical lines to check if all the points of the line to be plotted are in bounds of the grid
        if (distance > 0) { //checking for a downwards line
            for (int i=r; i<=(r+distance); i++) {
                if (i>getRows() || i < 0) {
                    cerr << "areAllPointsInGrid: (" << i << ", " << c << ") is beyond the bounds of the grid" << endl;
                    return false;
                }
            }
            return true; //if the loop runs through successfully without returning false, then all points are in the bound of the grid, therefore the function will return true;
        } else if (distance < 0) {  //checking for a rightwards line
            distance = abs(distance);
            for (int i=r; i>=(r-distance); i--) {
                if (i>getRows() || i < 0) {
                    cerr << "areAllPointsInGrid: (" << i << ", " << c << ") is beyond the bounds of the grid" << endl;
                    return false;
                }
            }
            return true; //if the loop runs through successfully without returning false, then all points are in the bound of the grid, therefore the function will return true;
        } else {    //this else block is processed if distance = 0
            return true;    //r and c have already been validated to be in or out of bounds by plotLine, so no further checks are required if distance = 0; therefore true returned automatically
        }
    }
    //these two statements will only ever execute if the function was fed a dir value that was neither HORIZ or VET; essentially, these statements should never execute, as plotLine should've already validated the value of dir to be either HORIZ or VERT
    cerr << "areAllPointsInGrid: function fed dir value that was neither HORIZ nor VERT" << endl;
    return false;
}

bool plotLine(int currentRow, int currentCol, int distance, int dir, char plotChar, int fgbg) {
    //Validating r for a row number that is in the bounds of the grid
    if (currentRow <= 0 || currentRow > getRows()) {
        cerr << "plotLine: r is not in correct range of 0 < r < " << getRows() << endl;
        return false;
    }
    
    //Validating c for a column number that is in the bounds of the grid
    if (currentCol <= 0 || currentCol > getCols()) {
        cerr << "plotLine: c is not in correct range of 0 < c < " << getCols() << endl;
        return false;
    }
    
    //Validating whether dir is either HORIZ or VERT
    if (dir != HORIZ && dir != VERT) {
        cerr << "plotLine: dir is not HORIZ or VERT" << endl;
        return false;
    }
    
    //Validating whether plotChar is printable
    if (!isprint(plotChar)) {
        cerr << "plotLine: plotChar is not printable" << endl;
        return false;
    }
    
    //Validating whether fgbg is either FG or BG
    if (fgbg != FG && fgbg != BG) {
        cerr << "plotLine: fgbg is not FG or BG" << endl;
        return false;
    }
    
    //Validating whether all points of the line to be plotted are in the bounds of the grid
    if (!areAllPointsInGrid(currentRow, currentCol, distance, dir)) {
        cerr << "plotLine: not all of the points of the line to be plotted are in the bounds of the grid" << endl;
        return false;
    }
    
    //This is printed to cerr if the parameters are successfully validated
    cerr << "plotLine: all plotLine parameters successfully validated" << endl;
    
    //Controlling flow of function depending on whether HORIZ or VERT has been called for plotLine
    if (dir == HORIZ) {
        plotHorizontalLine(currentRow, currentCol, distance, plotChar, fgbg);
    } else if (dir == VERT) {
        plotVerticalLine(currentRow, currentCol, distance, plotChar, fgbg);
    } else {    //should never get to this else statement as if dir is not HORIZ or VERT function should've already returned false
        cerr << "plotLine: dir is not HORIZ or VERT" << endl;
        return false;
    }
    
    return true;
}



bool processCCommand(string commandString, int& position, char& plotChar, int& mode, int& currentRow, int& currentCol) {
    //Call the grid.cpp clearGrid() function to reset all grid spots to space characters
    clearGrid();
    
    //Set the current position of the 'virtual pen' to (1,1)
    currentRow = 1;
    currentCol = 1;
    
    //Set the current plotting char and the current mode back to '*' and FG, respectively
    plotChar = '*';
    mode = FG;

    cerr << "processCCommand: function executed successfully, grid has been cleared; current grid position is (" << currentRow << ", " << currentCol << "); plotChar is " << plotChar << " and current mode is " << mode << endl;
    position++;
    return true;
}

bool processFCommand(string commandString, int& position, char& plotChar, int& mode) {
    //When this function is called, we already know that commandString[position] = 'F', so advance to next position to get the argument for the F command
    position++;
    
    //If there is no character after the F character, there is a syntax error at position
    if (position == commandString.size()) {
        cerr << "processFCommand: no character found after F command" << endl;
        return false;
    }
    
    //If the character after the F character is not printable, there is a syntax error at position
    if (!isprint(commandString[position])) {
        cerr << "processFCommand: unprintable character found after F command" << endl;
        return false;
    }
    
    //If false has not been returned by now, then the syntax for the F command is correct, so commandString[position] is the new character to be used
    mode = FG;
    plotChar = commandString[position];
    cerr << "processFCommand: command successfully executed, mode set to " << mode << " and plotChar set to " << plotChar << endl;
    
    //Advance position
    position++;
    return true;
}

bool processBCommand(string commandString, int& position, char& plotChar, int& mode) {
    //When this function is called, we already know that commandString[position] = 'B', so advance to next position to get the argument for the B command
    position++;
    
    //If there is no character after the B character, there is a syntax error at position
    if (position == commandString.size()) {
        cerr << "processBCommand: no character found after B command" << endl;
        return false;
    }
    
    //If the character after the B character is not printable, there is a syntax error at position
    if (!isprint(commandString[position])) {
        cerr << "processBCommand: unprintable character found after B command" << endl;
        return false;
    }
    
    //If false has not been returned by now, then the syntax for the B command is correct, so commandString[position] is the new character to be used
    mode = BG;
    plotChar = commandString[position];
    cerr << "processBCommand: command successfully executed, mode set to " << mode << " and plotChar set to " << plotChar << endl;
    
    //Advance position
    position++;
    return true;
}

bool processHCommand(string commandString, int& position, char& plotChar, int& mode, int& currentRow, int& currentCol, bool& syntaxErrorFlag, int& plottingErrorPos) {
    //Initialise a distance variable for the plotLine function
    int distance = 0;
    
    //Storing the positition of the H command in a temp variable in case the points to be plotted are outside the bounds of the grid
    int tempPosition = position;
    
    //We already know that commmandString[position] = 'H', so advance to next position to get the argument for the H command
    position++;
    
    //If the character after the H character is not a minus sign or a digit, there is an error
    if (!isdigit(commandString[position]) && commandString[position] != '-') {
        cerr << "processHCommand: no digit or minus sign found after H command" << endl;
        return false;
    }
    
    //If the character after the H character is a digit, first check if there is another digit after as well
    if (isdigit(commandString[position])) {
        //Add the value of this digit to the distance varialbe
        distance += (commandString[position] - '0');
        //Then check if the next character in commandString is also a digit
        if (isdigit(commandString[position+1])) {
            //If it is, multiply distance by 10 to get the current value of distance (commandString[position]) to be the tens value of the distance
            distance *= 10;
            //Then add on the value of the commandString[position+1] digit to the distance variable
            distance += (commandString[position+1] - '0');
            //Advance position, as we've now read position+1
            position++;
        }
    } else if (commandString[position] == '-') {   //If the character after the H character is a minus sign, then we need to check that there is a digit after it as well
        if (isdigit(commandString[position+1])) {
            //If there is a digit, we can advance the position by 1
            position++;
            
            //Then we add the value of that digit to the distance variable
            distance += (commandString[position] - '0');
            //Then check if the next character in commandString is also a digit
            if (isdigit(commandString[position+1])) {
                //If it is, multiply distance by 10 to get the current value of distance (commandString[position]) to be the tens value of the distance
                distance *= 10;
                //Then add on the value of the commandString[position+1] digit to the distance variable
                distance += (commandString[position+1] - '0');
                //Advance position, as we've now read position+1
                position++;
            }
        } else {    //if it isn't a digit, then there is a syntax error
            cerr << "processHCommand: no digits found after the minus sign" << endl;
            return false;
        }
        //We then multiply distance by -1, as the argument is a negative number
        distance *= -1;
    }
    
    //Execute plotLine function with dir = HORIZ
    if(!plotLine(currentRow, currentCol, distance, HORIZ, plotChar, mode)) {
        //if plotLine returns false, then a plotting command that tried to plot outside the grid was attempted to be executed, so badPos = the position that the plotting command started at
        //Storing the index value of the last character of the plotting command that generates a plotting error
        plottingErrorPos = position;
        //To get this position, we can assign position to the tempPosition of the H command that we saved earlier
        position = tempPosition;
        
        //We set the syntaxErrorFlag to false to indicate that a plotting error has occurred
        syntaxErrorFlag = false;
        
        //then return false as the H command has failed
        return false;

    }
    
    //Update current grid position following plotLine being successfully executed
    //If distance is positive, then add distance to currentCol
    if (distance > 0) {
        currentCol += distance;
    } else if (distance < 0) {  //If distance is negative, then adding distance to current coloumn will subtract abs(distance) from currentCol
        currentCol += distance;
    }
    
    //Advance position
    position++;
    return true;
}

bool processVCommand(string commandString, int& position, char& plotChar, int& mode, int& currentRow, int& currentCol, bool& syntaxErrorFlag, int& plottingErrorPos) {
    //Initialise a distance variable for the plotLine function
    int distance = 0;
    
    //Storing the positition of the V command in a temp variable in case the points to be plotted are outside the bounds of the grid
    int tempPosition = position;
    
    //We already know that commmandString[position] = 'V', so advance to next position to get the argument for the V command
    position++;
    
    //If the character after the V character is not a minus sign or a digit, there is an error
    if (!isdigit(commandString[position]) && commandString[position] != '-') {
        cerr << "processVCommand: no digit or minus sign found after V command" << endl;
        return false;
    }
    
    //If the character after the V character is a digit, first check if there is another digit after as well
    if (isdigit(commandString[position])) {
        //Add the value of this digit to the distance varialbe
        distance += (commandString[position] - '0');
        //Then check if the next character in commandString is also a digit
        if (isdigit(commandString[position+1])) {
            //If it is, multiply distance by 10 to get the current value of distance (commandString[position]) to be the tens value of the distance
            distance *= 10;
            //Then add on the value of the commandString[position+1] digit to the distance variable
            distance += (commandString[position+1] - '0');
            //Advance position, as we've now read position+1
            position++;
        }
    } else if (commandString[position] == '-') {   //If the character after the V character is a minus sign, then we need to check that there is a digit after it as well
        if (isdigit(commandString[position+1])) {
            //If there is a digit, we can advance the position by 1
            position++;
            
            //Then we add the value of that digit to the distance variable
            distance += (commandString[position] - '0');
            //Then check if the next character in commandString is also a digit
            if (isdigit(commandString[position+1])) {
                //If it is, multiply distance by 10 to get the current value of distance (commandString[position]) to be the tens value of the distance
                distance *= 10;
                //Then add on the value of the commandString[position+1] digit to the distance variable
                distance += (commandString[position+1] - '0');
                //Advance position, as we've now read position+1
                position++;
            }
        } else {    //if it isn't a digit, then there is a syntax error
            cerr << "processVCommand: no digits found after the minus sign" << endl;
            return false;
        }
        //We then multiply distance by -1, as the argument is a negative number
        distance *= -1;
    }
    
    //Execute plotLine function with dir = VERT
    if(!plotLine(currentRow, currentCol, distance, VERT, plotChar, mode)) {
        //if plotLine returns false, then a plotting command that tried to plot outside the grid was attempted to be executed, so badPos = the position that the plotting command started at
        //Storing the index value of the last character of the plotting command that generates a plotting error
        plottingErrorPos = position;
        //To get this position, we can assign position to the tempPosition of the H command that we saved earlier
        position = tempPosition;
        
        //We set the syntaxErrorFlag to false to indicate that a plotting error has occurred
        syntaxErrorFlag = false;
        
        //then return false as the H command has failed
        return false;
    }
    
    //Update current grid position following plotLine being successfully executed
    //If distance is positive, then add distance to currentRow
    if (distance > 0) {
        currentRow += distance;
    } else if (distance < 0) {  //If distance is negative, then adding distance to current row will subtract abs(distance) from currentRow
        currentRow += distance;
    }
    
    //Advance position
    position++;
    return true;
}

bool translateInstructionString(string commandString, char& plotChar, int& mode, int& badPos, bool& syntaxErrorFlag, int& plottingErrorPos) {
    int pos = 0;
    //Setting current position to (1, 1)
    int currentRow = 1;
    int currentCol = 1;
    
    while (pos != commandString.size()) {
        //Parsing commandString[pos] to decide what command to do
        
        if (toupper(commandString[pos]) == 'C') {
            //Process C command, but if there is an error, return false and proceed with error printing
            if (!processCCommand(commandString, pos, plotChar, mode, currentRow, currentCol)) {
                return false;
            }
        } else if (toupper(commandString[pos]) == 'F') {
            //Process F command, but if there is an error, return false and proceed with error printing
            if (!processFCommand(commandString, pos, plotChar, mode)) {
                badPos = pos;
                return false;
            }
        } else if (toupper(commandString[pos]) == 'B') {
            //Process B command, but if there is an error, return false and proceed with error printing
            if (!processBCommand(commandString, pos, plotChar, mode)) {
                badPos = pos;
                return false;
            }
        } else if (toupper(commandString[pos]) == 'H') {
            //Process H command, but if there is an error, return false and proceed with error printing
            //The syntaxErrorFlag will be passed-by-reference to the function that processes the H command as the H command can result in both syntax and plotting errors
            if (!processHCommand(commandString, pos, plotChar, mode, currentRow, currentCol, syntaxErrorFlag, plottingErrorPos)) {
                //processHCommand has returned false, so there is an error at pos
                badPos = pos;
                return false;
            }
        } else if (toupper(commandString[pos]) == 'V') {
            //Process V command, but if there is an error, return false and proceed with error printing
            //The syntaxErrorFlag will be passed-by-reference to the function that processes the V command as the V command can result in both syntax and plotting errors
            if (!processVCommand(commandString, pos, plotChar, mode, currentRow, currentCol, syntaxErrorFlag, plottingErrorPos)) {
                //processHCommand has returned false, so there is an error at pos
                badPos = pos;
                return false;

            }
        } else if (commandString == "") {
            //handling the case of the empty string, which is syntactically valid; it performs zero plotting commands, all zero of them successfully
            return true;
        } else {
            //No plotting commands have been detected in the command string, so there is a syntax error at pos
            badPos = pos;
            return false;
        }
    }
    
    if (!syntaxErrorFlag) {
        badPos = plottingErrorPos;
        return false;
    }
    
    //The whole text has been translated without error, so the translation is successful
    return true;
}

bool scanForSyntax(string commandString, int& badPos) {
    //This function is called if a plotting error had been detected in the command string, it scans the remainder of the string that is after the plotting command that caused the error for syntax errors
    //In this case, we are not going to process any of the commands and change any properties of the grid, we will only look for a syntactically valid string
    //This function is passed the substring of the original command string (the part after the command that generated the plotting error)
    int pos = 0;
    while (pos != commandString.size()) {
        if (toupper(commandString[pos]) == 'C') {
            //C command takes no arguments, so it can generate no syntax errors, so we'll just advance the position to the next place in the string
            pos++;
        } else if (toupper(commandString[pos]) == 'F') {
            //Looking for syntax errors related to the F command
            //We will not yet advance the pos command, because there may not be a syntactically valid argument after the F command
            
            //If there is no character after the F character, there is a syntax error at pos+1
            if (pos+1 == commandString.size()) {
                cerr << "scanForSyntax: no character found after F command" << endl;
                badPos = pos + 1;
                return false;
            }
            
            //If the character after the F character is not printable, there is a syntax error at pos+1
            if (!isprint(commandString[pos+1])) {
                cerr << "scanForSyntax: unprintable character found after F command" << endl;
                badPos = pos + 1;
                return false;
            }
            
            //If false has not been returned by now, then the syntax for the F command is correct (commandString[pos+1] is the new character to be used, but we don't care as we're only looking for syntax), so we advance the position twice, once because the argument is valid, and another time to move to the next command in the command string
            pos++;
            pos++;
        } else if (toupper(commandString[pos]) == 'B') {
            //Looking for syntax errors related to the B command
            //We will not yet advance the pos command, because there may not be a syntactically valid argument after the B command
            
            //If there is no character after the B character, there is a syntax error at pos+1
            if (pos+1 == commandString.size()) {
                cerr << "scanForSyntax: no character found after B command" << endl;
                badPos = pos + 1;
                return false;
            }
            
            //If the character after the F character is not printable, there is a syntax error at pos+1
            if (!isprint(commandString[pos+1])) {
                cerr << "scanForSyntax: unprintable character found after B command" << endl;
                badPos = pos + 1;
                return false;
            }
            
            //If false has not been returned by now, then the syntax for the B command is correct (commandString[pos+1] is the new character to be used, but we don't care as we're only looking for syntax), so we advance the position twice, once because the argument is valid, and another time to move to the next command in the command string
            pos++;
            pos++;
        } else if (toupper(commandString[pos]) == 'H') {
            //Looking for syntax errors related to the H command
            //We will not yet advance the pos command, because there may not be a syntactically valid argument after the H command
            
            //If the character after the H character is not a minus sign or a digit, there is a syntax error
            if (!isdigit(commandString[pos+1]) && commandString[pos+1] != '-') {
                cerr << "scanForSyntax: no digit or minus sign found after H command" << endl;
                badPos = pos + 1;
                return false;
            }
            
            //If false has not been returned by now, then the character after the H character is either a minus sign or a digit, so we can advance the position by one
            pos++;
            //We will now check for two cases: if a digit is detected as the character after the H command, then we need to check whether there is a digit (now at pos+1) after that digit (now at pos), and if there is, we will make sure to advance the position in accordance (otherwise this function may process the 2nd digit of the number as a command and return a syntax error, which would be incorrect, as it is part of the H command's argument
            if (isdigit(commandString[pos])) {
                //now we check if the next character is also a digit
                if (isdigit(commandString[pos+1])) {
                    //advance the position in accordance
                    pos++;
                }
            }
            
            //Iff a minus sign is detected after the H character, then we need to check that the character after the minus sign is a digit, or else there is a syntax error. If this case is true, then we will also need to the check if the character after that digit is also a digit, and if it is, we will make sure to advance the position in accordance (otherwise this function may process the 2nd digit of the number as a command and return a syntax error, which would be incorrect, as it is part of the H command's argument
            if (commandString[pos] == '-') {
                if (!isdigit(commandString[pos+1])) {
                    //Character after the minus sign is not a digit, return false as a syntax error has occurred
                    //We return the position of the minus sign, as we are assuming the user made an error here passing a minus sign instead of a digit
                    cerr << "scanForSyntax: minus sign passed to H command, but no digit found afterwards" << endl;
                    badPos = pos;
                    return false;
                } else {    //the character after the minus sign is a digit
                    //advance the position by one as we want to scan the next character
                    pos++;
                    
                    if (isdigit(commandString[pos+1])) {
                        //advance the position in accordance
                        pos++;
                    }
                }
            }
            
            //If false has not been returned by now, the H command is syntactically correct, so we will advance the position by 1 to look at the next character in the command string
            pos++;
        } else if (toupper(commandString[pos]) == 'V') {
            //Looking for syntax errors related to the V command
            //We will not yet advance the pos command, because there may not be a syntactically valid argument after the H command
            
            //If the character after the V character is not a minus sign or a digit, there is a syntax error
            if (!isdigit(commandString[pos+1]) && commandString[pos+1] != '-') {
                cerr << "scanForSyntax: no digit or minus sign found after V command" << endl;
                badPos = pos + 1;
                return false;
            }
            
            //If false has not been returned by now, then the character after the V character is either a minus sign or a digit, so we can advance the position by one
            pos++;
            //We will now check for two cases: if a digit is detected as the character after the H command, then we need to check whether there is a digit (now at pos+1) after that digit (now at pos), and if there is, we will make sure to advance the position in accordance (otherwise this function may process the 2nd digit of the number as a command and return a syntax error, which would be incorrect, as it is part of the H command's argument
            if (isdigit(commandString[pos])) {
                //now we check if the next character is also a digit
                if (isdigit(commandString[pos+1])) {
                    //advance the position in accordance
                    pos++;
                }
            }
            
            //Iff a minus sign is detected after the H character, then we need to check that the character after the minus sign is a digit, or else there is a syntax error. If this case is true, then we will also need to the check if the character after that digit is also a digit, and if it is, we will make sure to advance the position in accordance (otherwise this function may process the 2nd digit of the number as a command and return a syntax error, which would be incorrect, as it is part of the H command's argument
            if (commandString[pos] == '-') {
                if (!isdigit(commandString[pos+1])) {
                    //Character after the minus sign is not a digit, return false as a syntax error has occurred
                    //We return the position of the minus sign, as we are assuming the user made an error here passing a minus sign instead of a digit
                    cerr << "scanForSyntax: minus sign passed to H command, but no digit found afterwards" << endl;
                    badPos = pos;
                    return false;
                } else {    //the character after the minus sign is a digit
                    //advance the position by one as we want to scan the next character
                    pos++;
                    
                    if (isdigit(commandString[pos+1])) {
                        //advance the position in accordance
                        pos++;
                    }
                }
            }
            
            //If false has not been returned by now, the H command is syntactically correct, so we will advance the position by 1 to look at the next character in the command string
            pos++;
        } else if (commandString == "") {
            //handling the case of the empty string, which is syntactically valid; it performs zero plotting commands, all zero of them successfully
            return true;
        } else {
            //No plotting commands have been detected in the command string, so there is a syntax error at pos
            badPos = pos;
            return false;
        }
    }
    
    //The remainder of the commandString has been translated without error, so the translation is successful
    return true;
}


int performCommands(string commandString, char& plotChar, int& mode, int& badPos) {
    //Creating a flag to distinguish between a syntax error and a plotting error
    bool syntaxErrorFlag = true;    //initialised as true because only in two cases will a plotting error occur
    //Creating an int variable to hold the last position + 1 of the plotting command that generates a plotting error
    int plottingErrorPos;
    
    if(translateInstructionString(commandString, plotChar, mode, badPos, syntaxErrorFlag, plottingErrorPos)) {
        //If translateInstructionString returns true, then the command string translation was successful, and no errors were found, thus return 0
        return 0;
    } else {
        if (!syntaxErrorFlag) {
            //Plotting errors are only reported for syntactically valid strings, so the rest of the command string needs to be scanned for correct syntax, before reporting the plotting error
            //otherBadPos will be passed to scanForSyntax and hold the value of the syntactically bad position in the remainder of the command string
            int otherBadPos = 0;
            cerr << plottingErrorPos << endl;
            if (scanForSyntax(commandString.substr(plottingErrorPos+1), otherBadPos)) { // if this returns true, then the rest of the command string's syntax is correct
                return 2;
            } else {    //if scanForSyntax returns false, then there has been a syntax error at position plottingErrorPos+otherBadPos+1, so return 1
                cerr << otherBadPos +1 << endl;
                badPos = plottingErrorPos + otherBadPos + 1;
                return 1;
            }
        } else {
            return 1;
        }
    }
}
