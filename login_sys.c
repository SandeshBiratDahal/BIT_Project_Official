#include<stdio.h>

char current_username[30], stats_file_path[100];

void user_conf_page();
void login_page();
void signup_page();
void edit_page();

void user_conf_page(){
    system("cls");
    printf("----The Game Library----\n\n");
    char options[][30] = {"Log In", "Sign Up", "Edit Account"};
    int ch = 0;
    ch = create_menu_traditional(3, options, 1, "Choose an option: ");
    
    system("cls");
    if (ch == 0) login_page();
    else if (ch == 1) signup_page();
    else if (ch == 2) edit_page();
}

void signup_page(){
    FILE *fp, *np;
    fp = fopen("data/credentials/creds.txt", "a");
    np = fopen("data/credentials/creds.txt", "r");

    printf("----Sign Up----\n\n");
    char username[30], password[30], nusername[30], npassword[30];;
    printf("Choose a username: ");
    scanf("%s", username);
    fflush(stdin);
    printf("Choose a password: ");
    scanf("%s", password);

    while (fscanf(np, "%29[^,],%29[^,],", nusername, npassword) != EOF){
        if (strcmp(nusername, username) == 0) {
            printf("Username already exists!");
            getch();
            user_conf_page();
            return;
        }
    }

    fclose(np);

    fprintf(fp, "%s,%s,", username, password);
    fclose(fp);

    char extention[10] = ".txt", path[50] = "data/stats/";
    strcpy(stats_file_path, strcat(path, strcat(username, extention)));
    fp = fopen(stats_file_path, "w");
    fprintf(
        fp,
        "0,0,0,0,0,0,0,0,0,0,0,0,0,0,"
    ); //Hangman win/lose, RockPaperScissors win/lose/draw, Tictactoe easy/normal/hard win/lose/draw

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
            strcpy(current_username, nusername);
            char extention[10] = ".txt", path[50] = "data/stats/";
            strcpy(stats_file_path, strcat(path, strcat(nusername, extention)));
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

void edit_page() {
    title("Account Editor", 2);
    char options[][30] = {"Change Username", "Change Password", "Delete Account"};
    int ch = create_menu_traditional(3, options, 1, "Enter a choice: ");

    if (ch == 0) {
        title("Change Username", 2);
        FILE *fp, *np;
        char username[30], password[30], nusername[30], npassword[30], prev_username[30];
        int found = 0;
        printf("Enter current username: ");
        scanf("%s", username);
        strcpy(prev_username, username);
        printf("Enter password: ");
        scanf("%s", password);

        fp = fopen("data/credentials/creds.txt", "r");
        while (fscanf(fp, "%29[^,],%29[^,],", nusername, npassword) != EOF) {
            if (strcmp(nusername, username) == 0 && strcmp(password, npassword) == 0) {

                printf("Enter new username: ");
                scanf("%s", username);

                fseek(fp, 0, SEEK_SET);
                while (fscanf(fp, "%29[^,],%29[^,],", nusername, npassword) != EOF) {
                    if (strcmp(username, nusername) == 0) {
                        printf("Username already exists!");
                        getch();
                        fclose(fp);
                        user_conf_page();
                        return;
                    }
                }
                fseek(fp, 0, SEEK_SET);
                np = fopen("data/credentials/temp.txt", "w");
                while (fscanf(fp, "%29[^,],%29[^,],", nusername, npassword) != EOF) {
                    if (strcmp(nusername, prev_username)) {
                        fprintf(np, "%s,%s,", nusername, npassword);
                    }
                }
                fprintf(np, "%s,%s,", username, password);
                fclose(np);
                
                printf("\nSuccessfully changed the username from '%s' to '%s'!", prev_username, username);
                found = 1;
                break;
            }
        }

        fclose(fp);

        if (!found) {
            printf("\nIncorrect username or password!");
        }
        else {
            remove("data/credentials/creds.txt");
            rename("data/credentials/temp.txt", "data/credentials/creds.txt");
        }
    }
    else if (ch == 1) {
        
    }
    getch();
    user_conf_page();
}