#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <vector>

#include "view.h"

class CORE {
public:
    CORE(); 
    void initValues();
    void printMatrix(const std::vector<std::vector<int>>& matrix);

    void setShips(std::vector<std::vector<int>>& Board, int boardNumber, bool option);
    void shootingShips(bool option);
    void shoot(std::vector<std::vector<int>>& Board, const int& shootX, const int& shootY, bool& player);
    void isFinished(bool& continue_, std::vector<std::vector<int>>& Board);
    void menu();
    void game();
    void winner(const bool& player);

    //check functions
    bool checkValues(int dir, int x, int y);
    bool checkInBoard(int dir, int x, int y, int size);
    bool checkOtherShips(std::vector<std::vector<int>>& Board, int x, int y, int size, int dir);
    void setBoundaries(std::vector<std::vector<int>>& Board, int x, int y, int size, int dir);
    bool checkShootCoord(int x, int y);
    
private:
    std::vector<std::vector<int>> shipData;
    std::vector<std::vector<int>> Board1;
    std::vector<std::vector<int>> Board2;
    int sizeRow, directionRow, xRow, yRow;
    int SIZE = 10;
    VIEW view;
   
};

#endif
