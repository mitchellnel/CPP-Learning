# CPP-Learning
Repository for storing mini-projects dedicated to getting to grips with certain concepts in programming (and C++).

## Control Flow (Fine)
Concepts:
* If-else statements
* Comparison and logical operators
* User input (for various data types)

This program takes in various information about a "defendant's" circumstances to calculate a bribery fine for them.

Improvements:
* getline() should've been used instead of just cin >> for the fake athlete check; currently, if a user inputs a string, the first letter is kept and the remaining letters are truncated, and this is not the correct behaviour: inputting a string for this check should be invalid

I have also made a Python 3.7 version of this program to help me learn Python.

## Functions (Plot)
(grid.h and grid.cpp were externally provided)
Concepts:
* Functionalisation of code
* Passing by reference
* Loops

This program takes a "command string" from the user that has a variety of plotting commands and parameters within it. Based on what the user inputs, the program then plots lines of a user-specified characters onto a grid in the console.

Improvements:
* Although I've divided portions of the programme up into functions, there is a large amount of code duplication; I should be able to cut this down by functionalising more into things like checking for numbers after a line plotting command etc.

I have also made a (WIP) Python 3.7 version of this program to help me learn Python. In addition, this version of the project has better coding practice (i.e. working on the improvement mentioned above).

## Recursion (linear, maze, tree)
Concepts:
* Recursion

The linear mini-project involves implementing 4 functions that return values based on whether values in an array match somePredicate function by making use of recursion. The 5th function returns a Boolean value based on whether one array is a not-necessarily contiguous subsequence of another array, again using recursion.

The maze mini-project is based off of the pathExists function in the [Maze Solving](https://github.com/mitchellnel/Maze-Solving) project. However, this version implements pathExists as a recursive function that checks the possibility of moving down each possible pathway, instead of using stacks and queues. The overall result is the same.

The tree mini-project involves implementing 3 functions that manipulate arrays using recursive methods. 

This was likely my favourite concept to learn about. I think that recursion is a powerful tool when used correctly and in the right circumstances. It helps make code a lot more readable and easy to digest, especially when it can replace a large if-else block or a loop. However, I do recognise that in some cases it can have very large overhead with the amound of assembly jumps and space that must be allocated on the stack during recursive calls.

## Inheritance (event)
Concepts:
* Inheritance
* Virtual and pure virtual functions

This mini-project was a very shallow dive into the basics of inheritance and it's potential for creating higher quality code. I defined and implemented 4 types of classes, an Event class (the base/parent class for all the following classes), a BasketballGame class, a Concert class and a HockeyGame class (all 3 of which extended the Event class). By using inheritance, I was able to avoid code duplication for several member functions that would be shared across all 3 child classes, but also learn how to use virtual functions to either implement additional functionality following on from the parent class' implementation (i.e. Event::parentMethod(); ...extra stuff...) or completely override the functionality of the parent class (e.g. where a Concert should return false for isSport()).

I would like to look at more applications of pure virtual functions to better understand where they are most valuable to a programmer.

## Templates (Map)
Concepts:
* C++ templates

This mini-project involved slightly altering the implementation of the [circular, doubly linked list implementation of a Map](https://github.com/mitchellnel/Map-Implementations/tree/master/Map%20(as%20Linked%20List)/Map) so that, instead of using the KeyType and ValueType type aliases, we used class templates so that the same implementation of Map can be used with various data types, simply by creating the Map object as Map<int, std::string> or as Map<double, bool>

I thought that this was a very useful method of creating readable code and avoiding code duplication. However, if I was creating my own class template, I would need to make sure that I avoid issues where functions do not work well with specific data types, e.g. creating an object that allows its data members to be added would obviously not work with Booleans. Is there some way to use inheritance and templates together to get around this?

## Sorting (sorts)
Concepts:
* Sorting methods
* Time complexity (Big O notation)

This was not so much a project, but more of a learning experience and investigation into how different the time-to-completion takes for different sorting methods. This involved implementing my own version of insertion sort (using a textbook) to sort a non-trivially large array of Student objects based on their GPA, and then comparing the time it takes for insertion sort to complete, versus the time it takes for the STL sort() to complete (which I believe uses IntroSort).

I found this investigation very useful for more practically observing how different algorithms implemented by the programmer can affect time complexity, and how I can make deliberate choices in my work to "optimise" code and choose algorithms that create code that runs efficiently.
