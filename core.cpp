#include <iostream>
#include <vector>

#include "core.h"
#include "view.h"

VIEW view;    


CORE::CORE(){/* : SIZE(10), Board1(SIZE, std::vector<int>(SIZE, 0)), Board2(SIZE, std::vector<int>(SIZE, 0)),
    sizeRow(0), directionRow(1), xRow(2), yRow(3) {
    shipData = {
        {4, 3, 3, 2, 2, 2, 1, 1, 1, 1}, {}, {}, {}            
    };
    
    //std::cout << "size of shipData in core: " << shipData.size() << std::endl;
    //printMatrix(shipData);    
    printMatrix(Board1);*/
}

void CORE::initValues() {
    sizeRow = 0;
    directionRow = 1;
    xRow = 2;
    yRow = 3;
    SIZE = 10;
    Board1.resize(SIZE, std::vector<int>(SIZE, 0));
    Board2.resize(SIZE, std::vector<int>(SIZE, 0));
    shipData.resize(4, std::vector<int>(SIZE, 0));
    shipData = {
        {4, 3, 3, 2, 2, 2, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
}

void CORE::printMatrix(const std::vector<std::vector<int>>& matrix) {
    for (const std::vector<int>& row : matrix) {
        for (int element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "\n\n";
}

void CORE::shipDirections() {
    view.getShipDirections(shipData);
    setShips(shipData, Board1);
    printMatrix(Board1);
    for (double i = 0; i <= 1e+8; ++i);
    view.getShipDirections(shipData);
    setShips(shipData, Board2);
    printMatrix(Board2);
}

void CORE::setShips(std::vector<std::vector<int>>& shipData, std::vector<std::vector<int>>& Board) {
    for (int index = 0; index < shipData[directionRow].size(); ++index) {
        int x = shipData[xRow][index];
        int y = shipData[yRow][index];
        //std::cout << "checking for Board2\n";
        switch (shipData[directionRow][index]) {       
            case 0: // horizontal case              
                for (int size = 0; size < shipData[sizeRow][index]; ++size) {
                    Board[x][y + size] = 1;
                    //std::cout << "Board2 x y size : " << x << " " << y << " " << shipData[sizeRow][index] << std::endl;
                }
                break;
            case 1: // vertical case
                for (int size = 0; size < shipData[sizeRow][index]; ++size) {
                    Board[x + size][y] = 1;
                    //std::cout << "checking for Board 2 in switch case 0\n";
                }
                break;
        }
    }
}

void CORE::shootShips() {
    int shootX, shootY;
    std::vector<std::vector<int>> shootingBoard;
    bool continue_ = 1;
    bool player = 0; // 0 - player1, 1 - player2
    while (continue_) {
        while (player == 0) { // 0 - player1
            view.getShootCoord(shootX, shootY);
            std::cout << "x y player 1:" << shootX << " " << shootY << std::endl;
            shoot(Board2, shootX, shootY, player);
            printMatrix(Board2);
        }
        isFinished(continue_, Board2);
        while (player == 1) { // 1 - player2
            view.getShootCoord(shootX, shootY);
            std::cout << "x y player 2:" << shootX << " " << shootY << std::endl;
            shoot(Board1, shootX, shootY, player);
            printMatrix(Board1);
        }
        isFinished(continue_, Board1);
    }
}
    
void CORE::shoot(std::vector<std::vector<int>>& Board, const int& shootX, const int& shootY, bool& player) {
    std::string text = "you shot a ship";
	if (Board[shootX][shootY] == 1) {
        Board[shootX][shootY] = 2;
        if (check(Board, shootX, shootY)) {
            view.print(text);
        }
    }
    else {
        player = !player;
    }

}

bool CORE::check(std::vector<std::vector<int>>& Board, const int& shootX, const int& shootY) {
    bool checkX = 0, checkY = 0;
    if (Board[shootX][shootY] == 0) {
        if (Board[shootX + 1][shootY] == 0 || Board[shootX + 1][shootY] == 2) {
            checkX = 1;
        }
    }
    else if (Board[shootX][shootY] == SIZE - 1) {
        if (Board[shootX - 1][shootY] == 0 || Board[shootX - 1][shootY] == 2) {
            checkX = 1;
        }
    }
    else if ((Board[shootX + 1][shootY] == 0 || Board[shootX + 1][shootY] == 2) &&
        (Board[shootX - 1][shootY] == 0 || Board[shootX - 1][shootY] == 2)) {
        checkX = 1;
    }
    if (Board[shootX][shootY] == 0) {
        if (Board[shootX][shootY + 1] == 0 || Board[shootX][shootY + 1] == 2) {
            checkY = 1;
        }
    }
    else if (Board[shootX][shootY] == SIZE - 1) {
        if (Board[shootX][shootY - 1] == 0 || Board[shootX][shootY - 1] == 2) {
            checkY = 1;
        }
    }
    else if ((Board[shootX][shootY + 1] == 0 || Board[shootX][shootY + 1] == 2) && 
        (Board[shootX][shootY - 1] == 0 || Board[shootX][shootY - 1] == 2)) {
        checkY = 1;
    }
    if (checkX == 1 && checkY == 1) {
        return true;
    }
    else {
        return false;
    }
}

void CORE::isFinished(bool& continue_, std::vector<std::vector<int>>& Board){
    continue_ = 0;
    for (int row = 0; row < SIZE; ++row) {
        for (int column = 0; column < SIZE; ++column) {
            if (Board[row][column] == 1){
                std::cout << "somehow in isFinished true state\n";
                continue_ = 1;
                break;
            }
        }
    }
}

void CORE::game() {
    initValues();
    shipDirections();
    shootShips();
}