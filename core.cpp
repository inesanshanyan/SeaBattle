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

void CORE::setShips(std::vector<std::vector<int>>& Board, int boardNumber, bool option) {
    int validX, validY, validDir;
    int shipCount = shipData[directionRow].size();
    for (int index = 0; index < shipCount; ++index) {
        int size = shipData[sizeRow][index];
        view.print(view.getPlayerName(boardNumber));
        view.getShipDirections(validX, validY, validDir, size, option);

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
        

            view.getShipDirections(validX, validY, validDir, size, option);
            checkValues_ = checkValues(validDir, validX, validY);
            checkInBoard_ = checkInBoard(validDir, validX, validY, size);
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

void CORE::shootingShips(bool option) {
    int shootX, shootY;
    std::vector<std::vector<int>> shootingBoard;
    bool continue_ = 1;
    bool player = 0; // 0 - player1, 1 - player2   
    bool checkShootCoord_;
    while (continue_) {
        while (player == false && continue_) { // player1
            view.print(view.getPlayerName(1));
            shootX = 0; shootY = 0;
            view.getShootCoord(shootX, shootY, true);
            checkShootCoord_ = checkShootCoord(shootX, shootY);
            while (!checkShootCoord_) {
                view.print("Enter valid coords!");
                shootX = 0; shootY = 0;
                view.getShootCoord(shootX, shootY, true);
                checkShootCoord_ = checkShootCoord(shootX, shootY);
            }
            
            shoot(Board2, shootX - 1, shootY - 1, player);
            view.coverGrid(view.getGrid(2), Board2);
            isFinished(continue_, Board2);
        }
        
        while (player == true && continue_) {  // player2
            view.print(view.getPlayerName(2));
            view.getShootCoord(shootX, shootY, option);

            checkShootCoord_ = checkShootCoord(shootX, shootY);
            while (!checkShootCoord_) {
                view.print("Enter valid coords!");
                view.getShootCoord(shootX, shootY, option);
                checkShootCoord_ = checkShootCoord(shootX, shootY);
            }

            shoot(Board1, shootX - 1, shootY - 1, player);            
            view.coverGrid(view.getGrid(1), Board1);
            isFinished(continue_, Board1);
        }
    }
    winner(player);
}
    
void CORE::shoot(std::vector<std::vector<int>>& Board, const int& shootX, const int& shootY, bool& player) {
    if (Board[shootX][shootY] == 1) {
        Board[shootX][shootY] = 2;
        return;
    }
    else if (Board[shootX][shootY] == 0 || Board[shootX][shootY] == 4) {
        Board[shootX][shootY] = 3;
    }
    
    player = !player;
}

void CORE::winner(const bool& player) {
    switch (player) {
    case 0: // player 1
        view.print("player 1 wins");
        break;
    case 1: // player 2
        view.print("player 2 wins");
        break;
    }
    view.pause();
    view.pause();
    game();

}

void CORE::isFinished(bool& continue_, std::vector<std::vector<int>>& Board){
    continue_ = 0;
    for (int row = 0; row < SIZE; ++row) {
        for (int column = 0; column < SIZE; ++column) {
            if (Board[row][column] == 1){
                continue_ = 1;
                return;
            }
        }
    }
}

void CORE::game() {
    initValues();
    menu();

}

void CORE::menu() {
    bool option = true;
    int select = 0;
    while (select != 1 && select != 2 && select != 3) {
        select = view.mainMenu();
    }
    switch (select) {
    case 1:
        break;
    case 2:
        option = false;
        break;
    case 3:
        view.quitGame();
        break;
    }
    view.menuPlayers(select);

    view.drawBoard(Board1, Board2);
    view.drawControlBoard();

    setShips(Board1, 1, true);
    view.coverGrid(view.getGrid(1), Board1);
    
    
   
    setShips(Board2, 2, option);
    view.coverGrid(view.getGrid(2), Board2);
    
    
    shootingShips(option);
}

bool CORE::checkValues(int dir, int x, int y) {
    bool check = true;
    if (dir != 0 && dir != 1) {
        check = false;
    }

    if (x <= 0 || x > SIZE) {
       check = false;
    } 
    if (y <= 0 || y > SIZE) {
       check = false;
    }
    return check;
}



bool CORE::checkInBoard(int dir, int x, int y, int size) {
    bool check = true;
    switch (dir) {
    case 1: // vertical
        if (x + size - 1 > SIZE) {
            check = false;
        }
        break;
    case 0: // horizontal
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
    int endX, endY;

    switch (dir) {
    case 0: // horizontal
        endX = (x + 1 < SIZE) ? x + 1 : x;
        endY = (y + size  < SIZE ) ? y + size : y + size - 1;
        break;
    case 1: // vertical
        endX = (x + size  < SIZE ) ? x + size: x + size - 1;
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
    size -= 1;
    x -= 1;
    y -= 1;
    if (Board[x][y] != 1 && Board[x][y] != 4) {
        switch (dir) {
        case 0: // h
            if (Board[x][y + size] != 1 && Board[x][y + size] != 4) {
                return true;
            }
            break;
        case 1: // v
            if (Board[x + size][y] != 1 && Board[x + size][y] != 4) {
                return true;
            }
            break;
        }
    }
    return false;
}

bool CORE::checkShootCoord(int shootX, int shootY) {
    bool check = true;
    if (shootX <= 0 || shootX > SIZE) {
        check = false;
    }
    if (shootY <= 0 || shootY > SIZE) {
        check = false;
    }
    return check;
}
