#include <curses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    // Initialize curses
    initscr();

    // Set up some variables for paging
    int ch;
    int lines_per_page = LINES - 2;  // subtract 2 for top and bottom borders
    int current_line = 0;
    int current_page = 0;
    int total_pages = 100 / lines_per_page;  // Total number of pages
    char pages[total_pages][lines_per_page][256];  // Array to save pages

    // Print some lines to the screen
    for (int i = 0; i < 100; i++) {
        char line[256];
        sprintf(line, "Line %d", i);
        mvprintw(current_line, 0, line);
        strcpy(pages[current_page][current_line], line);
        current_line++;
        if (current_line >= lines_per_page) {
            current_line = 0;
            current_page++;
            refresh();
            // Wait for user to press a key before continuing
            ch = getch();
            if (ch == 'q') {
                break;
            } else if (ch == 'b') {
                if (current_page > 1) {
                    current_page--;
                } else if(current_page == 1) {
                    current_page = 0;
                }
                wclear(stdscr);
                for (int j = 0; j < lines_per_page; j++) {
                    mvprintw(j, 0, pages[current_page][j]);
                }
                refresh();
                current_line = lines_per_page;
            }
        }
    }

    // Clean up curses
    endwin();
    return 0;
}
