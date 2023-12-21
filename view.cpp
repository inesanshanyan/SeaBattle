#include <iostream>
#include <ncurses.h> //gui

#include <cstdlib> //random values

#include <vector> // manipulating vectors
#include <string> // and strings

#include <ctime> // time
#include <thread>
#include <chrono>

#include "view.h"


VIEW::VIEW() {
    //creating main window
    initscr();
    cbreak();
    refresh();
    getmaxyx(stdscr, max_height, max_width);
        
    //creating Grids and Control Window
    Grid1 = newwin(height, width, 4, disFromCorners);
    Grid2 = newwin(height, width, 4, max_width - disFromCorners - width);
    Control = newwin(controlHeight, controlWidth, 8, (max_width - controlWidth)/2);
    start_color(); 
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    
 }

void VIEW::pause() {
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}


void VIEW::print(std::string text) {
    int printHeight = 3, printWidth = 30;
    init_pair(7, COLOR_RED, COLOR_WHITE);

    WINDOW* printWindow = newwin(printHeight, printWidth, 3, (max_width - printWidth) / 2);
    werase(printWindow);
    box(printWindow, 0, 0);
    wbkgd(printWindow, COLOR_PAIR(1));
    
    
    wattron(printWindow, COLOR_PAIR(7));
    mvwprintw(printWindow, 1, (printWidth - text.size())/2, "%s", text.c_str());
    wattroff(printWindow, COLOR_PAIR(7));

    wrefresh(printWindow);
}

int VIEW::mainMenu() {
    werase(stdscr);
    int select;
    char buffer[0];
    int menuHeight = 12, menuWidth = 46;
    WINDOW* menu = newwin(menuHeight, menuWidth, (max_height - menuHeight) / 2, (max_width - menuWidth) / 2);
    box(menu, 0, 0);
    wbkgd(menu, COLOR_PAIR(1));

    mvwprintw(menu, 2, (menuWidth - 15) / 2, "SEA BATTLE MENU");
    mvwprintw(menu, 4, 2, "1.Start for two players");
    mvwprintw(menu, 6, 2, "2.Start for one player");
    mvwprintw(menu, 8, 2, "3.Quit");
    mvwprintw(menu, 10, 2, "Enter an option");

    wmove(menu, 10, 20);
    wgetstr(menu, buffer);
    select = std::stoi(buffer);
    wrefresh(menu);
    getch();
    clear();

    return select;
}
void VIEW::menuPlayers(int select) {
    werase(stdscr);
    
    char buffer[50];
    int menuHeight = 12, menuWidth = 46;

    WINDOW* menu = newwin(menuHeight, menuWidth, (max_height - menuHeight) / 2, (max_width - menuWidth) / 2);
    box(menu, 0, 0);    
    wbkgd(menu, COLOR_PAIR(1));

    if (select == 1) mvwprintw(menu, 2, (menuWidth - 20) / 2, "Game for two players");
    else mvwprintw(menu, 2, (menuWidth - 20) / 2, "Game for one player");
    mvwprintw(menu, 4, 2, "Enter a name for player 1 ");

    if (select == 1) mvwprintw(menu, 6, 2, "Enter a name for player 2 ");

    wmove(menu, 4, 28);
    wgetstr(menu, buffer);
    player1 = buffer;
    if (select == 1) {
        wmove(menu, 6, 28);
        wgetstr(menu, buffer);
        player2 = buffer;
    }
    else player2 = "computer";
    
    mvwprintw(menu, 8, 2, "Press any key to start...");
    wrefresh(menu);
    getch();
    clear();

    getch();
 }


void VIEW::drawBoard(const std::vector<std::vector<int>>& Board1, const std::vector<std::vector<int>>& Board2) {
    
    init_pair(6, COLOR_WHITE, COLOR_BLACK);
    wattron(stdscr, COLOR_PAIR(6));

    mvwprintw(stdscr, 1, disFromCorners + (width - player1.size())/2, "%s", player1.c_str());
    box(Grid1, 0, 0);
    wbkgd(Grid1, COLOR_PAIR(1));
    setLines(Grid1, height, width);
    setCoord(Grid1);
    setGrid(Grid1, Board1);

    mvwprintw(stdscr, 1, max_width - disFromCorners - (width - player2.size())/2, "%s", player2.c_str());
    box(Grid2, 0, 0);
    wbkgd(Grid2, COLOR_PAIR(1));
    setLines(Grid2, height, width);
    setCoord(Grid2);
    setGrid(Grid2, Board2); 

    wattroff(stdscr, COLOR_PAIR(6));
    wrefresh(Grid1);
    wrefresh(Grid2);
    wrefresh(stdscr);
   
}

void VIEW::drawControlBoard() {
    box(Control, 0, 0);
    wbkgd(Control, COLOR_PAIR(1));
    wrefresh(Control); 
}


void VIEW::setCoord(WINDOW* Grid) {
    init_pair(2, COLOR_BLUE, COLOR_WHITE);
    wattron(Grid, COLOR_PAIR(2));
    for (int coord = 0; coord < SIZE; ++coord) {        
        mvwprintw(Grid, coord * 2 + 3, 1, "%d", coord + 1); // horizontal
        mvwprintw(Grid, 1, coord * 4 + 5, "%d", coord + 1); // vertical
    }
    wattroff(Grid, COLOR_PAIR(2));
}

void VIEW::setLines(WINDOW* Grid, int height, int width) {
    for (int size = 0; size <= height; ++size) {
        mvwhline(Grid, size * 2 + 2, 2, ACS_HLINE, width * 3);
    }

    for (int size = 0; size <= width ; ++size) {
        mvwvline(Grid, 1, size * 4 + 3, ACS_VLINE, height * 2);
    }
}

void VIEW::setGrid(WINDOW* Grid, const std::vector<std::vector<int>>& Board) {
    char charToPrint;
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    init_pair(4, COLOR_BLUE, COLOR_WHITE);
    init_pair(5, COLOR_RED, COLOR_WHITE);
    for (int row = 0; row < SIZE; ++row) {
        for (int column = 0; column < SIZE; ++column) {
            switch (Board[row][column]){
            case 0:
                wattron(Grid, COLOR_PAIR(3));
                charToPrint = ' ';
                break;
            case 1:
                wattron(Grid, COLOR_PAIR(2));
                charToPrint = 'O';
                break;
            case 2:
                wattron(Grid, COLOR_PAIR(5));
                charToPrint = ' ';
                break;
            case 3:
                wattron(Grid, COLOR_PAIR(4));
                charToPrint = ' ';
                break;
            case 4:
                wattron(Grid, COLOR_PAIR(2));
                charToPrint = '-';
                break;
            }

            mvwprintw(Grid, row * 2 + 3, column * 4 + 5, "%c", charToPrint);
            wattroff(Grid, A_ATTRIBUTES);
            wrefresh(Grid);
        }
    }
}

void VIEW::coverGrid(WINDOW* Grid, const std::vector<std::vector<int>>& Board) {
    char charToPrint;
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    init_pair(4, COLOR_BLUE, COLOR_WHITE);
    init_pair(5, COLOR_RED, COLOR_WHITE);
    werase(Grid);
    setCoord(Grid);
    setLines(Grid, height, width);
    for (int row = 0; row < SIZE; ++row) {
        for (int column = 0; column < SIZE; ++column) {
            switch (Board[row][column]) {
            case 0:
                //wattron(Grid, COLOR_PAIR(3));
                charToPrint = ' ';
                break; 
            case 1:
                //wattron(Grid, COLOR_PAIR(3));
                charToPrint = ' ';
                break;
            case 2:
                wattron(Grid, COLOR_PAIR(5));
                charToPrint = 'X';
                break;
            case 3:
                wattron(Grid, COLOR_PAIR(4));
                charToPrint = '+';
                break;
            case 4:
                //wattron(Grid, COLOR_PAIR(3));
                charToPrint = ' ';
                break;
            }
            
            mvwprintw(Grid, row * 2 + 3, column * 4 + 5, "%c", charToPrint);
            wattroff(Grid, A_ATTRIBUTES);
            wrefresh(Grid);
            
        }
    }
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

void VIEW::getShipDirections(int& validX, int& validY, int& validDir, int size, bool option) {
  
    box(Control, 0, 0);
    mvwprintw(Control, 2, 2, "Size : %d ", size);
    mvwprintw(Control, 4, 2, "Enter x y : ");
    mvwprintw(Control, 8, 2, "Enter direction(h or v) : ");

    wmove(Control, 6, 2);
    if (option) {
        mvwscanw(Control, 6, 2, "%d %d", &validX, &validY);
        wmove(Control, 10, 2);
        char dir;
        mvwscanw(Control, 10, 2, "%c", &dir);

        switch (tolower(dir)) {
        case 'h':
            validDir = 0;
            break;
        case 'v':
            validDir = 1;
            break;
        default:
            validDir = 2;
        }
    }
    else {
        pause();
        validX = rand() % 10 + 1;
        validY = rand() % 10 + 1;
        validDir = rand() % 2;
    }
 
    werase(Control);
}


WINDOW* VIEW::getGrid(int gridNumber) {

    switch (gridNumber) {
    case 1:
        return Grid1;
    case 2:
        return Grid2;
    case 3:
        return Control;
    default:
        return nullptr;
    }

}

std::string VIEW::getPlayerName(int playerNum) {
    std::string error_ = "Error in getPlayerName";
    switch (playerNum) {
    case 1:
        return player1;
    case 2:
        return player2;
    default:
        return error_;
    }
}

void VIEW::getShootCoord(int& shootX, int& shootY, bool option) {
    werase(Control);
    box(Control, 0, 0);
    mvwprintw(Control, 4, 2, "Enter shoot x y : ");

    if (option) {
        wmove(Control, 6, 2);
        mvwscanw(Control, 6, 2, "%d %d", &shootX, &shootY);

        std::cout << "x y : " << shootX << " " << shootY << std::endl;

        char ch;
        if ((ch = getch()) == 'q') endwin();
    }
    else {
        pause();
        shootY = std::rand() % 10 + 1;
        pause();
        shootX = std::rand() % 10 + 1;
    }

}


void VIEW::quitGame() {
    endwin();
    exit(0);
}

VIEW::~VIEW() {
    endwin();
}



