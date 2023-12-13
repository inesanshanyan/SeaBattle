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
    void menu(const char *header, char* player1_text, char* player2_text, char& player1, char& player2);
    void setPlayerName(std::string player);
private:
    
};

#endif
