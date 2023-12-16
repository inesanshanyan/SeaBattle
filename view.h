#ifndef VIEW_H
#define VIEW_H

#include <vector>
#include <iostream>
#include <ncurses.h>

class VIEW {
public:
    VIEW();
    void printMatrix(const std::vector<std::vector<int>>& matrix);
    void print(std::string text);
    void getShootCoord(int& shootX, int& shootY);
    void getShipDirections(std::vector<std::vector<int>>& shipData);
    void menu();
    void drawBoard(const std::vector<std::vector<int>>& Board1, const std::vector<std::vector<int>>& Board2);
    
    void setGrid(WINDOW* Grid, const std::vector<std::vector<int>>& Board);
    void setLines(WINDOW* Grid, int height, int width);
    void setCoord(WINDOW* Grid);
    void drawControlBoard();
    void coverBoard(WINDOW* Grid);

    ~VIEW();
private:
    std::string player1, player2;
    int max_height, max_width;
    const int SIZE = 10;
    int height = 23, width = 44;
    int disFromCorners = 6;
    int controlHeight = 8, controlWidth = 20;
    WINDOW* Grid1;
    WINDOW* Grid2;
    WINDOW* Control;
    //std::string player1, player2;
};

#endif
