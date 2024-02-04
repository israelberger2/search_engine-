#include <iostream>
#include <ncurses.h>

int main() {
    initscr();  // Initialize the ncurses library
    raw();      // Disable line buffering
    keypad(stdscr, TRUE);  // Enable special keys

    refresh();

    while (getch() != 27) {  // 27 is the key code for Esc
        // Add your code here for the action you want to take on key press
    }

    endwin();  // End the ncurses library

    return 0;
}
