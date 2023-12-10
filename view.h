#ifndef VIEW_H
#define VIEW_H

#include <vector>
#include <iostream>

class VIEW {
public:
    VIEW();
    void printMatrix(const std::vector<std::vector<int>>& matrix);
    void print(std::string text);
    void getShootCoord(int& shootX, int& shootY);
    void getShipDirections(std::vector<std::vector<int>>& shipData);
private:
    
};

#endif
