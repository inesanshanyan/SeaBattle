#include <iostream>
#include <ncurses.h>
#include <cstring>
#include <vector>


class GUI {
public:
    const int WIDTH = 3;
    const int HEIGHT = 2;
    WINDOW* Board1[10][10];
    WINDOW* Board2[10][10];
    char player1[20];
    char player2[20];

    void menu() {
        // screen size x = 34, y = 117
        int height = 12, width = 36;
        int x, y;
       
        getmaxyx(stdscr, x, y);
        WINDOW* menu = newwin(height, width, (x - height)/2, (y - width)/2);
        box(menu, 0, 0);

        mvwprintw(menu, 2, (width - 10)/2, "SEA BATTLE");
        mvwprintw(menu, 4, 2, "Enter PLAYER 1 name ");
        mvwprintw(menu, 6, 2, "Enter PLAYER 2 name ");

        wmove(menu, 4, 22);
        wgetstr(menu, player1);
        wmove(menu, 6, 22);
        wgetstr(menu, player2);
        //curs_set(0);
        mvwprintw(menu, 8, 2, "Press any key to start...");
        wrefresh(menu);
        getch();
        clear();
        interface();
    }

    void create_board(WINDOW* Board[10][10], int x, int y) {
        int starty = y, startx = 0;

        for (int i = 0; i < 10; ++i) {
            starty += HEIGHT;
            startx = x;

            for (int j = 0; j < 10; ++j) {
                startx += WIDTH;
                Board[i][j] = newwin(HEIGHT, WIDTH, starty, startx);
                box(Board[i][j], 0, 0);
                wrefresh(Board[i][j]);
            }
        }
        getch();
    }

    void cover_board(WINDOW* Board[10][10]) {
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                mvwaddch(Board[i][j], 0.7, 0.5, 'X');
                wrefresh(Board[i][j]);
            }
        }
    }

    void interface() {
        refresh();
        curs_set(0);
        int x, y;
        getmaxyx(stdscr, x, y);

        mvprintw(0, (y/2 - strlen(player1))/2, "%s board ", player1);
        create_board(Board1, (y/2 - 10 * WIDTH) / 2, 2);
        cover_board(Board1);

        mvprintw(0, y/2 + (y / 2 - strlen(player1)) / 2, "%s board ", player2);
        create_board(Board2, y/2 + (y / 2 - 10 * WIDTH) / 2, 2);
        cover_board(Board2);

        getch();
    }
};

int main() {
    GUI gui;

    initscr();
    cbreak();
    refresh();

    gui.menu();

    getch();
    endwin();

    return 0;
}