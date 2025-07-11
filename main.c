#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "utilities.c"
#include "login_sys.c"
#include "file_edit.c"
#include "stats_viewer.c"
#include "hangman.c"
#include "rockpaperscissors.c"
#include "tictactoe.c"
#include "game_selector.c"

int main(){
    user_conf_page();
    getch();
    stats_view_selector();
    while (1) select_game_page();
    return 0;
}

/*
TODO: 
1. Improve the game ending screen like adding texts for draw in tictactoe, showing the word after losing in hangman etc.
2. Add play again? feature in each game.
3. Add a "Go Back" and "Quit" option to every menu.
4. Add a separate menu to view the win/lose/draw count and win percentages.
5. Improve the user login system like checking if the username already exists and adding password hints.
6. Small Improvements like:
    Adding a small delay for thinking AI
*/