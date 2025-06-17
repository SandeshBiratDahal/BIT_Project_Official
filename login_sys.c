#include<stdio.h>

void user_conf_page();
void login_page();
void signup_page();

void user_conf_page(){
    system("cls");
    printf("----The Game Library----\n\n");
    char options[][30] = {"Log In", "Sign Up"};
    int ch = 0;
    ch = create_menu_traditional(2, options, 1, "Choose an option: ");
    
    system("cls");
    if (ch == 0) login_page();
    else if (ch == 1) signup_page();
}

void signup_page(){
    FILE *fp;
    fp = fopen("data/credentials/creds.txt", "a");

    printf("----Sign Up----\n\n");
    char username[30], password[30];
    printf("Choose a username: ");
    scanf("%s", username);
    fflush(stdin);
    printf("Choose a password: ");
    scanf("%s", password);

    fprintf(fp, "%s,%s,", username, password);
    fclose(fp);

    printf("\nSuccessfully created a new account!!");
    getch();
    system("cls");
    user_conf_page();
}

void login_page(){
    FILE *fp;
    fp = fopen("data/credentials/creds.txt", "r");

    printf("----Log In----\n\n");
    char username[30], password[30], nusername[30], npassword[30];
    printf("Enter username: ");
    scanf("%s", username);
    fflush(stdin);
    printf("Enter password: ");
    scanf("%s", password);

    int found = 0;

    while (fscanf(fp, "%29[^,],%29[^,],", nusername, npassword) != EOF) {
        if (strcmp(nusername, username) == 0 && strcmp(npassword, password) == 0) {
            printf("\nSuccessfully logged in as %s!!", nusername);
            found = 1;
            break;
        }
    }

    if (!found){
        printf("\nIncorrect username or password!");
        getch();
        user_conf_page();
    }
    fclose(fp);
    
}