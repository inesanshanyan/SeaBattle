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
    void shipDirections(); 
    void setShips(std::vector<std::vector<int>>& Board, int boardNumber);
    void shootShips();
    void shoot(std::vector<std::vector<int>>& Board, const int& shootX, const int& shootY, bool& player);
    bool check(std::vector<std::vector<int>>& Board, const int& shootX, const int& shootY);
    void isFinished(bool& continue_, std::vector<std::vector<int>>& Board);
    void menu();
    void game();
    void winner(const bool& player);
    
private:
    std::vector<std::vector<int>> shipData;// = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 }; // setting ship size
    std::vector<std::vector<int>> Board1;
    std::vector<std::vector<int>> Board2;
    int sizeRow, directionRow, xRow, yRow;
    int SIZE = 10;
    VIEW view;
   
};

#endif
