int create_menu_traditional(
    int number_of_options, char options[][30], int spacing, char query[50]
);

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