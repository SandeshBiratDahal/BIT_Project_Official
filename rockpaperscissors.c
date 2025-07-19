#include <windows.h>

void display_opponent_move(char move[30]){
    printf("\nYour opponent chose: \n\n");
    Sleep(1000);
    printf("************\n", move);
    if (move[0] == 'R') printf("*   %s   *\n", move);
    else if (move[0] == 'S') printf("* %s *\n", move);
    else if (move[0] == 'P') printf("*  %s   *\n", move);
    printf("************");

}

int check_winner(char move[30], char opp_move[30]){
    if (strcmp(move, opp_move) == 0) return 0;
    if (move[0] == 'R' && opp_move[0] == 'P') return -1;
    else if (move[0] == 'R' && opp_move[0] == 'S') return 1;
    else if (move[0] == 'S' && opp_move[0] == 'R') return -1;
    else if (move[0] == 'S' && opp_move[0] == 'P') return 1;
    else if (move[0] == 'P' && opp_move[0] == 'S') return -1;
    else if (move[0] == 'P' && opp_move[0] == 'R') return 1;
}

void rockpaperscissors(){
    
    title("Rock-Paper-Scissors", 2);
    char options[][30] = {"ROCK", "PAPER", "SCISSORS"}, opponent_move[30], my_move[30];
    int ch = create_menu_traditional(3, options, 2, "Enter your choice: "), winner;
    srand(time(0));
    int random_move = rand() % 3;

    strcpy(opponent_move, options[random_move]);
    strcpy(my_move, options[ch]);
    display_opponent_move(opponent_move);

    winner = check_winner(my_move, opponent_move);
    printf("\n\n");
    if (winner == 0) {
        printf("It's a draw!!");
        edit_file(stats_file_path, 4, 1, 0);
    }
    else if (winner == -1) {
        printf("You lose!!");
        edit_file(stats_file_path, 3, 1, 0);
    }
    else {
        printf("You win!!");
        edit_file(stats_file_path, 2, 1, 0);
    }

    if (confirm("\n\nPress 'y' to play again: ")) {
        rockpaperscissors();
        return;
    }
}