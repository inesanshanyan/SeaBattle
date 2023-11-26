#include <iostream>
#include <string>
#include <vector>
// 0 - empty, 1 - ship, 2 - shoot
class MODEL {
public:
    const int SIZE = 10;
    CORE core;
    MODEL() : Board1(SIZE, std::vector<int>(SIZE, 0)), Board2(SIZE, std::vector<int>(SIZE, 0));

    void PrintBoard(const std::vector<std::vector<int>>& matrix) {
        for (const std::vector<int>& row : matrix) {
            for (int element : row) {
                std::cout << element << " ";
            }
            std::cout << std::endl;
        }
    }

    void setShips(std::vector<std::vector<int>>& shipData, std::vector<std::vector<int>>& Board) {
        for (int dir = 0; dir < shipData.size(); ++dir)
        {
            switch (shipData[core.directionRow][dir]) {
            case 0: // horizontal case
                for (int size = 0; size < shipData[core.sizeRow][dir]; ++size) {
                    Board[shipData[core.Xrow] + size][shipData[core.yRow]] = 1;
                }
                break;
            case 1: // vertical case
                for (int size = 0; size < shipData.size(); ++size) {
                    Board[shipData[core.Xrow]][shipData[core.yRow] + size] = 1;
                }
                break;
            }
        }
    }

    void Shoot(std::vector<std::vector<int>>& Board, const int& shootX, const int& shootY, bool& player) {
        if (Board[shootX][shootY] == 1) {
            Board[shootX][shootY] = 2;
            Check((std::vector<std::vector<int>>&Board, const int& shootX, const int& shootY);
        }
        else {
            player = !player;
        }

    }

    void Check(std::vector<std::vector<int>>& Board, const int& shootX, const int& shootY) {
        if( ( Board[shootX + 1][shootY] == 0 || Board[shootX + 1][shootY] == 2 ) &&
            ( Board[shootX - 1][shootY] == 0 || Board[shootX - 1][shootY] == 2 ))
            // ...
    }

private:
    std::vector<std::vector<int>> Board1;
    std::vector<std::vector<int>> Board2;
    
};

