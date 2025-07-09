void print_board(char board[]);
int get_user_input(char board[]);
int check_winner_tic_tac_toe(char board[]);

void tictactoe(){
    system("cls");
    printf("----Games List----\n\n");
    char options[][30] = {"Vs Computer", "Vs Human"};
    int ch = create_menu_traditional(2, options, 1, "Select an option: ");

    srand(time(0));
    int turn = 0, player = rand() % 2, user_move = -1, win_id = 0;
    char board[9] = ".........";
    char winner;

    while (1){
        
        if (ch) {
            system("cls");
            printf("----Tic-Tac-Toe----\n\n\n");
            print_board(board);
            user_move = get_user_input(board);
            board[user_move] = turn % 2? 'O': 'X';
            turn++;

            win_id = check_winner_tic_tac_toe(board);
            if (win_id) {
                system("cls");
                printf("----Tic-Tac-Toe----\n\n\n");
                print_board(board);

                if (win_id == -1) winner = 'O';
                else winner = 'X';

                printf("\n%c is the winner!", winner);
                getch();
                return;
            }
        }
        else {
            system("cls");
            printf("---Play As---\n\n");
            char options[][30] = {"Random", "Play as X", "Play as O"};
            int choice = create_menu_traditional(3, options, 1, "Enter a choice: ");
        }
    }
}

void print_board(char board[]){
    printf("%c              %c             %c\n\n\n", board[0], board[1], board[2]);
    printf("%c              %c             %c\n\n\n", board[3], board[4], board[5]);
    printf("%c              %c             %c\n", board[6], board[7], board[8]);
}

int get_user_input(char board[]){
    int choice = -1;
    printf("\n");
    while (choice < 1 || choice > 9){
        printf("Enter your move[1-9]: ");
        scanf("%d", &choice);
        if (board[choice - 1] == 'X' || board[choice - 1] == 'O') choice = -1;
    }

    return choice - 1;
}

int check_winner_tic_tac_toe(char board[]){
    int winner = 0;
    int winning_conditions[][3] = {
        {0, 1, 2},
        {0, 3, 6},
        {0, 4, 8},
        {1, 4, 7},
        {2, 5, 8},
        {2, 4, 6},
        {3, 4, 5},
        {6, 7, 8},
        {3, 4, 5}
    };

    for(int i = 0; i < 9; i++) {
        if (board[winning_conditions[i][0]] == board[winning_conditions[i][1]] && board[winning_conditions[i][1]] == board[winning_conditions[i][2]] && board[winning_conditions[i][0]] != '.'){
            if (board[winning_conditions[i][0]] == 'X') return 1;
            else return -1;
        }
    }

    return 0;
}