int create_menu_traditional(
    int number_of_options, char options[][30], int spacing, char query[50]
);
void title(char text[50], int spacing);

int create_menu_traditional(int number_of_options, char options[][30], int spacing, char query[50]){
    int i, j, choice = 0;
    for (i = 0 ; i < number_of_options; i++){
        printf("%d. %s", i + 1, options[i]);
        for (j = 0; j < spacing; j++) printf("\n");
    }
    printf("\n");
    while (choice < 1 || choice > number_of_options){
        printf("%s", query);
        scanf("%d", &choice);
    }
    return choice - 1;
}

void title(char text[50], int spacing) {
    system("cls");
    printf("<=--%s--=>", text);
    for (int i = 0; i < spacing; i++) printf("\n");
}

int confirm(char query[50]) {
    fflush(stdin);
    printf("%s", query);
    char choice;
    scanf("%c", &choice);
    if (choice == 'y' || choice == 'Y') return 1;
    return 0;
}

void scanf_password(char* password) {
    char c;
    int i = 0, show = 0;
    while (1) {
        c = getch();

        if (c == 13) break;

        else if (c == 27) {
            if (i > 0){
                if (show == 0){
                    show = 1;
                    for (int j = 0; j < i; j++) printf("\b");
                    password[i] = '\0';
                    printf("%s", password);
                }
                else {
                    for (int j = 0; j < i; j++) printf("\b");
                    for (int j = 0; j < i; j++) printf("#");
                    show = 0;
                }
            }
        }

        //backspace handel
        else if (c == 8) {
            //check if password length is greater than 0
            if (i > 0){
                i--; 
                printf("\b \b");
            }
        }
        else {
            if (!show) printf("#");
            else printf("%c", c);
            password[i] = c;
            i++;
        }
    }
    password[i] = '\0';
    printf("\n");
}