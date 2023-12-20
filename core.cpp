#include <iostream>
#include <vector>

#include "core.h"
#include "view.h"

CORE::CORE(){
    
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
    //player1 = "player1";
    //player2 = "player2";
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

void CORE::setShips(std::vector<std::vector<int>>& Board, int boardNumber) {
    int validX, validY, validDir;
    for (int index = 0; index < shipData[directionRow].size(); ++index) {
        int size = shipData[sizeRow][index];
        view.print(view.getPlayerName(boardNumber));
        view.getShipDirections(validX, validY, validDir, shipData[sizeRow][index]);

        bool checkValues_ = checkValues(validDir, validX, validY);
        bool checkInBoard_ = checkInBoard(validDir, validX, validY, size);
        bool checkOtherShips_ = checkOtherShips(Board, validX, validY, size, validDir);
        while (!checkValues_ || !checkInBoard_ || !checkOtherShips_) {
            if (!checkValues_) {
                view.print("Enter valid values!");
            }
            else if (!checkInBoard_) {
                view.print("The ship can't fit!");
            } 
            else if (!checkOtherShips_) {
                view.print("Overlapping with a ship!");
            }
        

            view.getShipDirections(validX, validY, validDir, shipData[sizeRow][index]);
            checkValues_ = checkValues(validDir, validX, validY);
            checkInBoard_ = checkInBoard(validDir, validX, validY, shipData[sizeRow][index]);
            checkOtherShips_ = checkOtherShips(Board, validX, validY, size, validDir);
        }

        shipData[xRow][index] = validX - 1;
        shipData[yRow][index] = validY - 1;
        shipData[directionRow][index] = validDir;


        int x = shipData[xRow][index];
        int y = shipData[yRow][index];
        int dir = shipData[directionRow][index];        

        switch (dir) {
        case 0: // horizontal case  
            for (int s = 0; s < size; ++s) {
                Board[x][y + s] = 1;
            }
            break;
        case 1: // vertical case
            for (int s = 0; s < size; ++s) {
                Board[x + s][y] = 1;
                                
            }
            break;
        }
        setBoundaries(Board, x, y, size, dir);
        switch (boardNumber) {
        case 1:
            view.setGrid(view.getGrid(boardNumber), Board);
            break;
        case 2:
            view.setGrid(view.getGrid(boardNumber), Board);
            break;
        }

    }
}

void CORE::shootingShips() {
    int shootX, shootY;
    std::vector<std::vector<int>> shootingBoard;
    bool continue_ = 1;
    bool player = 0; // 0 - player1, 1 - player2   
    bool checkShootCoord_;
    while (continue_) {
        while (player == 0 && continue_ != 0) { // 0 - player1
            view.print(view.getPlayerName(1));
            view.getShootCoord(shootX, shootY);
            checkShootCoord = checkShootCoord(shootX, shootY)
            while (!checkShootCoord_) {
                view.print("Enter valid coords!");
                view.getShootCoord(shootX, shootY);
                checkShootCoord(shootX, shootY)
            }
            shoot(Board2, shootX - 1, shootY - 1, player);
            view.coverGrid(view.getGrid(2), Board2);
            isFinished(continue_, Board2);
        }
        
        while (player == 1 && continue_ != 0) { // 1 - player2
            view.print(view.getPlayerName(2));
            view.getShootCoord(shootX, shootY);

            shoot(Board1, shootX - 1, shootY - 1, player);
            view.coverGrid(view.getGrid(1), Board1);
            isFinished(continue_, Board1);
        }
    }
    winner(player);
}
    
void CORE::shoot(std::vector<std::vector<int>>& Board, const int& shootX, const int& shootY, bool& player) {
    std::string text = "you shot a ship";
    //std::cout << "checking in shoot\n";
	if (Board[shootX][shootY] == 1) {
        Board[shootX][shootY] = 2;
        return;
    }
    else if (Board[shootX][shootY] == 0) {
        Board[shootX][shootY] = 3;
    }
    
    player = !player;
}

void CORE::winner(const bool& player) {
    switch (player) {
    case 0: // player 1
        view.print("PLAYER 1 WINS !");
        break;
    case 1: // player 2
        view.print("PLAYER 2 WINS !");
        break;
    }
}

void CORE::isFinished(bool& continue_, std::vector<std::vector<int>>& Board){
    continue_ = 0;
    for (int row = 0; row < SIZE; ++row) {
        for (int column = 0; column < SIZE; ++column) {
            if (Board[row][column] == 1){
                //std::cout << "somehow in isFinished true state\n";
                continue_ = 1;
                return;
            }
        }
    }
}

void CORE::game() {
    initValues();
    menu();
    view.drawBoard(Board1, Board2);
    view.drawControlBoard();

    
    setShips(Board1, 1);
    view.coverGrid(view.getGrid(1), Board1);

    setShips(Board2, 2);
    view.coverGrid(view.getGrid(2), Board2);

    shootingShips();
}

void CORE::menu() {
    view.menu();
}

bool CORE::checkValues(int dir, int x, int y) {
    bool check = true;
    if (dir == 2) {
        check = false;
    }

    if (x <= 0 || x > SIZE) {
       check = false;
    } 
    if (y <= 0 || y > SIZE) {
       check = false;
    }
    std::cout << "check = " << check;
    return check;
}



bool CORE::checkInBoard(int dir, int x, int y, int size) {
    bool check = true;
    switch (dir) {
    case 0: // horizontal
        if (x + size - 1 > SIZE) {
            check = false;
        }
        break;
    case 1: // vertical
        if (y + size - 1 > SIZE) {
            check = false;
        }
        break;
    default: 
        check = false;
        break;
    }
    return check;
}

void CORE::setBoundaries(std::vector<std::vector<int>>& Board, int x, int y, int size, int dir) {
    int startX = (x > 0) ? x - 1 : x;
    int startY = (y > 0) ? y - 1 : y;
    int endX = x, endY = y;

    switch (dir) {
    case 0: // horizontal
        endX = (x + 1 < SIZE) ? x + 1 : x;
        endY = (y + size < SIZE) ? y + size : y;
        break;
    case 1: // vertical
        endX = (x + size < SIZE) ? x + size : x;
        endY = (y + 1 < SIZE) ? y + 1 : y;
        break;
    }

    for (int i = startX; i <= endX; ++i) {
        for (int j = startY; j <= endY; ++j) {
            if (Board[i][j] != 1) {
                Board[i][j] = 4;
            }
        }
    }
}

bool CORE::checkOtherShips(std::vector<std::vector<int>>& Board, int x, int y, int size, int dir) {
    int startX = (x > 0) ? x - 1 : x;
    int startY = (y > 0) ? y - 1 : y;
    int endX = x, endY = y;

    switch (dir) {
    case 0: // horizontal
        endX = (x + 1 < SIZE) ? x + 1 : x;
        endY = (y + size < SIZE) ? y + size - 1 : y;
        break;
    case 1: // vertical
        endX = (x + size < SIZE) ? x + size - 1 : x;
        endY = (y + 1 < SIZE) ? y + 1 : y;
        break;
    }

    for (int i = startX; i < endX; ++i) {
        for (int j = startY; j < endY; ++j) {
            if (Board[i][j] == 1 || Board[i][j] == 4) {
                return false; 
            }
        }
    }
    return true;
}

bool CORE::checkShootCoord(int shootX, int shootY) {
    if (shootX <= 0 || shootX > SIZE) {
        return false;
    }
    if (shootY <= 0 || shootY > SIZE) {
        return false;
    }
    return true;
}
