#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "view.h"
#include <ncurses.h>

VIEW::VIEW() {
	//screen size 34, y = 117
}

void VIEW::print(std::string text) {
	std::cout << text << "\n";
}

void VIEW::menu(const char* header, const char* player1_text, const char* player2_text, char& player1, char& player2) {
    initscr();
    cbreak();
    refresh();
    // screen size x = 34, y = 117
    int height = 12, width = 36;
    int x, y;
    getmaxyx(stdscr, x, y);
    WINDOW* menu = newwin(height, width, (x - height) / 2, (y - width) / 2);
    box(menu, 0, 0);

    mvwprintw(menu, 2, (width - 10) / 2, "a");
    mvwprintw(menu, 4, 2, player1);
    mvwprintw(menu, 6, 2, player2);

    wmove(menu, 4, 22);
    wgetstr(menu, player1_name);
    wmove(menu, 6, 22);
    wgetstr(menu, player2_name);
    //curs_set(0);
    mvwprintw(menu, 8, 2, "Press any key to start...");
    wrefresh(menu);
    getch();
    clear();


    getch();
    endwin();
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
    std::cout << "enter shoot x y: ";
    std::cin >> shootX >> shootY;
	//shootY = std::rand() % 10;
}

