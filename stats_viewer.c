char current_username[30], stats_file_path[100];

void stats_view_selector();
void view_stats();
void select_game_page();

void stats_view_selector() {
    title("The Main Menu", 2);
    char options[][30] = {"Play Games", "My Stats", "Log Out"};
    int ch = create_menu_traditional(3, options, 2, "Enter a choice: ", title_pipe("The Main Menu"));

    if (ch == 0) select_game_page();
    else if (ch == 1) view_stats();
    else if (ch == 2) user_conf_page();
}

void view_stats() {
    system("cls");
    printf("----User:%s----\n\n", current_username);

    int total_games_played = 0, individual_games_played = 0;

    //HANGMAN
    int win = fetch(stats_file_path, 0), lose = fetch(stats_file_path, 1), draw = 0;
    individual_games_played = win + lose;
    printf("--Hangman--\n-----------\n");
    if (individual_games_played) printf("Total: %d\t  Win: %d\t  Lose: %d\n\n", win + lose, win, lose);
    else printf("No data available!\n\n");
    total_games_played += win + lose;

    //Rock Paper Scissors
    win = fetch(stats_file_path, 2);
    lose = fetch(stats_file_path, 3);
    draw = fetch(stats_file_path, 4);
    individual_games_played = win + lose + draw;
    printf("--Rock-Paper-Scissors--\n-----------------------\n");
    if (individual_games_played) printf("Total: %d\t  Win: %d\t  Lose: %d\t  Draw: %d\n\n", win + lose + draw, win, lose, draw);
    else printf("No data available!\n\n");
    total_games_played += win + lose + draw;

    //Tic Tac Toe
    printf("--Tic-Tac-Toe--\n---------------\n\n");
    // Easy
    win = fetch(stats_file_path, 5);
    lose = fetch(stats_file_path, 6);
    draw = fetch(stats_file_path, 7);
    individual_games_played = win + lose + draw;
    printf("-Easy-\n");
    if (individual_games_played) printf("Total: %d\t  Win: %d\t  Lose: %d\t  Draw: %d\n\n", win + lose + draw, win, lose, draw);
    else printf("No data available!\n\n");
    total_games_played += win + lose + draw;

    // Normal
    win = fetch(stats_file_path, 8);
    lose = fetch(stats_file_path, 9);
    draw = fetch(stats_file_path, 10);
    individual_games_played = win + lose + draw;
    printf("-Normal-\n");
    if (individual_games_played) printf("Total: %d\t  Win: %d\t  Lose: %d\t  Draw: %d\n\n", win + lose + draw, win, lose, draw);
    else printf("No data available!\n\n");
    total_games_played += win + lose + draw;

    // Hard
    win = fetch(stats_file_path, 11);
    lose = fetch(stats_file_path, 12);
    draw = fetch(stats_file_path, 13);
    individual_games_played = win + lose + draw;
    printf("-Hard-\n");
    if (individual_games_played) printf("Total: %d\t  Win: %d\t  Lose: %d\t  Draw: %d\n\n", win + lose + draw, win, lose, draw);
    else printf("No data available!\n\n");
    total_games_played += win + lose + draw;

    printf("Total Games Played: %d", total_games_played);
    getch();
    stats_view_selector();
}