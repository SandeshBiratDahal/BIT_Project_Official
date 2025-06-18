void print_board(char board[]);

void tictactoe(){
    system("cls");
    printf("----Tic-Tac-Toe----\n\n\n");
    char board[9] = ".........";
    print_board(board);
    getch();
}

void print_board(char board[]){
    printf("%c              %c             %c\n\n\n", board[0], board[1], board[2]);
    printf("%c              %c             %c\n\n\n", board[3], board[4], board[5]);
    printf("%c              %c             %c\n", board[6], board[7], board[8]);
}