
void select_game_page(){
    system("cls");
    printf("----Games List----\n\n");
    char games[][30] = {"Hangman", "Tic-Tac-Toe", "Rock-Paper-Scissors"};
    int ch = 0;
    ch = create_menu_traditional(3, games, 2, "Choose a game: ");

    if (ch == 0) hangman();
}