#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "utilities.c"
#include "login_sys.c"
#include "hangman.c"
#include "rockpaperscissors.c"
#include "tictactoe.c"
#include "game_selector.c"

int main(){
    user_conf_page();
    getch();
    while (1) select_game_page();
    return 0;
}