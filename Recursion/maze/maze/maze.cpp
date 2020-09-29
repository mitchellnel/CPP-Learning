//
//  main.cpp
//  maze
//
//  Created by Mitchell McLinton on 7/2/20.
//  Copyright © 2020 Mitchell McLinton. All rights reserved.
//

#include <iostream>


/* TODO: REMOVE ALL ABOVE */

/////////////////////////////////////////////
// Coord Class
/////////////////////////////////////////////
class Coord
{
  public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
  private:
    int m_r;
    int m_c;
};

/////////////////////////////////////////////////////////////////////////////////////////////////
// pathExists Implementation (with recursion)
/////////////////////////////////////////////////////////////////////////////////////////////////
bool pathExists(std::string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    const char ENCOUNTERED = '@';   // TODO: ASK IF I CAN KEEP THESE
    const char WALL = 'X';
    Coord start(sr, sc);
    Coord end(er, ec);
    if (start.r() == end.r() && start.c() == end.c())
        return true;
    
    maze[sr][sc] = ENCOUNTERED;
    
    for (int i = 0; i < 4; i++) {
        switch (i) {
            case 0: // NORTH
                if (maze[start.r()-1][start.c()] != WALL && maze[start.r()-1][start.c()] != ENCOUNTERED)
                    if (pathExists(maze, nRows, nCols, start.r()-1, start.c(), end.r(), end.c()))
                        return true;
                break;
                
            case 1: // EAST
                 if (maze[start.r()][start.c()+1] != WALL && maze[start.r()][start.c()+1] != ENCOUNTERED)
                     if (pathExists(maze, nRows, nCols, start.r(), start.c()+1, end.r(), end.c()))
                         return true;
                break;
                
            case 2: // SOUTH
                if (maze[start.r()+1][start.c()] != WALL && maze[start.r()+1][start.c()] != ENCOUNTERED)
                    if (pathExists(maze, nRows, nCols, start.r()+1, start.c(), end.r(), end.c()))
                        return true;
                break;
                
            case 3: // WEST
                if (maze[start.r()][start.c()-1] != WALL && maze[start.r()][start.c()-1] != ENCOUNTERED)
                    if (pathExists(maze, nRows, nCols, start.r(), start.c()-1, end.r(), end.c()))
                        return true;
        }
    }
    return false;
}

/* TODO: REMOVE ALL BELOW */

/////////////////////////////////////////////
// main()
/////////////////////////////////////////////
int main()
{
    std::string maze[10] = {
        "XXXXXXXXXX",
        "X...X..X.X",
        "X.XXX....X",
        "X.X.XXXX.X",
        "XXX......X",
        "X...X.XX.X",
        "X.X.X..X.X",
        "X.XXXX.X.X",
        "X..X...X.X",
        "XXXXXXXXXX"
    };

    if (pathExists(maze, 10,10, 4,3, 1,8))
        std::cout << "Solvable!" << std::endl;
    else
        std::cout << "Out of luck!" << std::endl;
    
    std::string maze2[10] = {
        "XXXXXXXXXX",
        "X...X.XXXX",
        "X.X.X....X",
        "X.X.XXXX.X",
        "X.X......X",
        "XX..XXXX.X",
        "X..XX..X.X",
        "X.X.XX.X.X",
        "X......X.X",
        "XXXXXXXXXX"
    };
    
    if (pathExists(maze2, 10,10, 1,5, 6,5))
        std::cout << "Solvable!" << std::endl;
    else
        std::cout << "Out of luck!" << std::endl;
    
    std::string maze3[4] = {
        "XXXXXXX",
        "X..XX.X",
        "XXX.XXX",
        "XXXXXXX"
    };
    
    if (pathExists(maze3, 4,7, 1,1, 2,3))
        std::cout << "Solvable!" << std::endl;
    else
        std::cout << "Out of luck!" << std::endl;
}
