#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "view.h"
#include "core.h"


VIEW::VIEW() {
	// ....
}

void VIEW::print(std::string text) {
	std::cout << text << "\n";
}


void VIEW::printMatrix(const std::vector<std::vector<int>>& matrix) {
    for (const std::vector<int>& row : matrix) {
        for (int element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "\n\n";
}

void VIEW::getShipDirections(std::vector<std::vector<int>>& shipData) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));   
    for (int i = 0; i < 10; ++i) {
        //shipData[1].push_back(std::rand() % 2);
        shipData[1][i] = std::rand() % 2;
        shipData[2][i] = std::rand() % 6;
        shipData[3][i] = std::rand() % 5;
    }
    printMatrix(shipData);
}

void VIEW::getShootCoord(int& shootX, int& shootY) {
	shootX = std::rand() % 10;
	shootY = std::rand() % 10;
}

