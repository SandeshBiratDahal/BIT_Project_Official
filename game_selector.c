
void select_game_page(){
    title("     List Of Games     ", 2);
    char games[][30] = {"Hangman", "Tic-Tac-Toe", "Rock-Paper-Scissors", "<- Go Back"};
    int ch = 0;
    ch = create_menu_traditional(4, games, 2, "Choose a game: ", title_pipe("     List Of Games     "));

    if (ch == 0) hangman();
    else if (ch == 1) tictactoe();
    else if (ch == 2) rockpaperscissors();
    else if (ch == 3) stats_view_selector();
}