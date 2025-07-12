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
1. Edit Password/username. Delete account.
*/