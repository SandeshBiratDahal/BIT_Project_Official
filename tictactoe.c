void print_board(char board[]);
int get_user_input(char board[]);
int check_winner_tic_tac_toe(char board[]);
int get_ai_input(char board[], int difficulty, char play_as);
void display_winner(char board[], int win_id);
int easy_ai(char board[], char play_as);
int normal_ai(char board[], char play_as, int hard_ai);

void tictactoe(){
    system("cls");
    printf("----Games List----\n\n");
    char options[][30] = {"Vs Computer", "Vs Human"};
    int ch = create_menu_traditional(2, options, 1, "Select an option: ");

    srand(time(0));
    int turn = 0, player = rand() % 2, user_move = -1, win_id = 0, opp_move = -1;
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
                display_winner(board, win_id);
                return;
            }
        }
        else {
            int player = 0;
            char player_symbol = 'A', opp_symbol = 'A';
            system("cls");
            printf("---Play As---\n\n");
            char options[][30] = {"Random", "Play as X", "Play as O"};
            int choice = create_menu_traditional(3, options, 1, "Enter a choice: "), difficulty = 0;

            if (choice == 1) player = 1;
            else if (choice == 2) player = -1;
            else{
                srand(time(0));
                player = rand() % 2;
                if (!player) player = -1;
            } 

            if (player == 1) {
                player_symbol = 'X';
                opp_symbol = 'O';
            }
            else {
                player_symbol = 'O';
                opp_symbol = 'X';
            }

            printf("You are playing as %c!", player_symbol);
            getch();

            system("cls");
            printf("---Difficulty Level---\n\n");
            char options1[][30] = {"Easy", "Normal", "Hard"};
            difficulty = create_menu_traditional(3, options1, 1, "Enter a choice: ");

            turn = 0;
            while (1) {
                system("cls");
                printf("---Tic-Tac-Toe---\n\n\n");
                print_board(board);
                if (player == 1) {
                    user_move = get_user_input(board);
                    board[user_move] = player_symbol;

                    win_id = check_winner_tic_tac_toe(board);
                    if (win_id) {
                        display_winner(board, win_id);
                        return;
                    }

                    opp_move = get_ai_input(board, difficulty, opp_symbol);
                    board[opp_move] = opp_symbol;

                    win_id = check_winner_tic_tac_toe(board);
                    if (win_id) {
                        display_winner(board, win_id);
                        return;
                    }
                }
                else {
                    opp_move = get_ai_input(board, difficulty, opp_symbol);
                    board[opp_move] = opp_symbol;

                    win_id = check_winner_tic_tac_toe(board);
                    if (win_id) {
                        display_winner(board, win_id);
                        return;
                    }

                    system("cls");
                    printf("---Tic-Tac-Toe---\n\n\n");
                    print_board(board);
                    user_move = get_user_input(board);
                    board[user_move] = player_symbol;

                    win_id = check_winner_tic_tac_toe(board);
                    if (win_id) {
                        display_winner(board, win_id);
                        return;
                    }
                }
                turn += 2;
            }
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

int get_ai_input(char board[], int difficulty, char play_as) {
    if (difficulty == 0) return easy_ai(board, play_as);

    else if (difficulty == 1) return normal_ai(board, play_as, 0);

    else return normal_ai(board, play_as, 1);
}

void display_winner(char board[], int win_id) {
    char winner;
    system("cls");
    printf("----Tic-Tac-Toe----\n\n\n");
    print_board(board);

    if (win_id == -1) winner = 'O';
    else winner = 'X';

    printf("\n%c is the winner!", winner);
    getch();
}

int easy_ai(char board[], char play_as) {
    int move;
    int remaining_tiles[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1}, index = 0;
    for (int i = 0; i < 9; i++) {
        if (board[i] == '.') {
            remaining_tiles[index] = i;
            index++;
        }
    }
    srand(time(0));
    move = remaining_tiles[rand() % index];
    return move;
}

int normal_ai(char board[], char play_as, int hard_ai) {
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
    }, best_move = -1, i, max_no_of_placed_move = 0, x_count = 0, o_count = 0, dot_count = 0, dot_pos = -1;
    char current_tile_move;

    for (i = 0; i < 9; i++) {
        x_count = 0; o_count = 0; dot_count = 0;
        for (int j = 0; j < 3; j++) {
            current_tile_move = board[winning_conditions[i][j]];
            if (current_tile_move == 'X') x_count++;
            else if (current_tile_move == 'O') o_count++;
            else {
                dot_count++;
                dot_pos = j;
            }
        }

        switch (play_as)
        {
            case 'X':
                if (!o_count) {
                    if (max_no_of_placed_move < x_count) {
                        max_no_of_placed_move = x_count;
                        best_move = winning_conditions[i][dot_pos];

                        if (dot_count == 1) return winning_conditions[i][dot_pos];
                    }
                }
                if (o_count == 2 && hard_ai && dot_count) return winning_conditions[i][dot_pos];
                break;
            
            case 'O':
                if (!x_count) {
                    if (max_no_of_placed_move < o_count) {
                        max_no_of_placed_move = o_count;
                        best_move = winning_conditions[i][dot_pos];

                        if (dot_count == 1) return winning_conditions[i][dot_pos];
                    }
                }
                if (x_count == 2 && hard_ai && dot_count) return winning_conditions[i][dot_pos];
                break;
        }
            
    }
    if (best_move < 0) return easy_ai(board, play_as);
    return best_move;
}