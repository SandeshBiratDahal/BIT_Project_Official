char current_username[30], stats_file_path[100];

void stats_view_selector();
void view_stats();

void stats_view_selector() {
    title("Main Menu", 2);
    char options[][30] = {"Play Games", "View Stats"};
    int ch = create_menu_traditional(2, options, 1, "Enter a choice: ");

    if (ch == 0) return;
    else if (ch == 1) view_stats();
}

void view_stats() {
    system("cls");
    printf("----User:%s----\n\n", current_username);

    int total_games_played = 0;

    //HANGMAN
    int win = fetch(stats_file_path, 0), lose = fetch(stats_file_path, 1), draw = 0;
    printf("--Hangman--\n  Total: %d\n  Win: %d\n  Lose:%d\n\n", win + lose, win, lose);
    total_games_played += win + lose;

    //Rock Paper Scissors
    win = fetch(stats_file_path, 2);
    lose = fetch(stats_file_path, 3);
    draw = fetch(stats_file_path, 4);
    printf("--Rock-Paper-Scissors--\n  Total: %d\n  Win: %d\n  Lose: %d\n  Draw: %d\n\n", win + lose + draw, win, lose, draw);
    total_games_played += win + lose + draw;

    //Tic Tac Toe
    printf("--Tic-Tac-Toe--\n\n");
    // Easy
    win = fetch(stats_file_path, 5);
    lose = fetch(stats_file_path, 6);
    draw = fetch(stats_file_path, 7);
    printf("-Easy-\n  Total: %d\n  Win: %d\n  Lose: %d\n  Draw: %d\n\n", win + lose + draw, win, lose, draw);
    total_games_played += win + lose + draw;

    // Normal
    win = fetch(stats_file_path, 8);
    lose = fetch(stats_file_path, 9);
    draw = fetch(stats_file_path, 10);
    printf("-Normal-\n  Total: %d\n  Win: %d\n  Lose: %d\n  Draw: %d\n\n", win + lose + draw, win, lose, draw);
    total_games_played += win + lose + draw;

    // Hard
    win = fetch(stats_file_path, 11);
    lose = fetch(stats_file_path, 12);
    draw = fetch(stats_file_path, 13);
    printf("-Hard-\n  Total: %d\n  Win: %d\n  Lose: %d\n  Draw: %d\n\n", win + lose + draw, win, lose, draw);
    total_games_played += win + lose + draw;

    printf("Total Games Played: %d", total_games_played);
    getch();
}