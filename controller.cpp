#include <iostream>
#include <vector>

class CORE {
public:
    VIEW view;
    MODEL model;
    
    int SIZE = 10;

    CORE() : Board1(SIZE, std::vector<int>(SIZE, 0)), Board2(SIZE, std::vector<int>(SIZE, 0)),
        sizeRow(0), directionRow(1), xRow(2), yRow(3),
        shipData({4, 3, 3, 2, 2, 2, 1, 1, 1, 1} ); // setting ship size

    void Print(const std::vector<std::vector<int>>&matrix) {
        for (const std::vector<int>& row : matrix) {
            for (int element : row) {
                std::cout << element << " ";
            }
            std::cout << std::endl;
        }
    }

    void ShipDirections() {
        view.getShipDirections(std::vector<std::vector<int>>&shipData);
        model.setShips(const std::vector<std::vector<int>>&shipData, std::vector<std::vector<int>>&Board1);
        view.getShipDirections(std::vector<std::vector<int>>&shipData);
        model.setShips(const std::vector<std::vector<int>>&shipData, std::vector<std::vector<int>>&Board2);
    }

    void ShootShips() {
        int shootX, shootY;
        std::vector<std::vector<int>> shootingBoard;
        bool continue_ = 1;
        bool player = 0; // 0 - player1, 1 - player2
        while (continue_) {
            while (player == 0){
                view.getShootCoord(int& shootX, int& shootY);
                model.Shoot(std::vector<std::vector<int>>&Board2, const int& shootX, const int& shootY, bool& player);
            }
            model.isFinished(bool& continue_);
            while (player == 1) {
                view.getShootCoord(int& shootX, int& shootY);
                model.Shoot(std::vector<std::vector<int>>&Board1, const int& shootX, const int& shootY, bool& player);
            }
            model.isFinished(bool& continue_);
        }
    }
    
private: 
    std::vector<std::vector<int>> shipData;
    std::vector<std::vector<int>> Board1;
    std::vector<std::vector<int>> Board2;
    int sizeRow, directionRow, xRow, yRow;
};


