#include<stdio.h>
#include<stdlib.h>

char current_username[30], stats_file_path[100];

void user_conf_page();
void login_page();
void signup_page();
void edit_page();
void stats_view_selector();

void user_conf_page(){
    title("The Game Library", 2);
    char options[][30] = {"Log In", "Sign Up", "Edit Account", "Exit"};
    int ch = 0;
    ch = create_menu_traditional(4, options, 1, "Choose an option: ");
    
    if (ch == 0) login_page();
    else if (ch == 1) signup_page();
    else if (ch == 2) edit_page();
    else if (ch == 3) 
    {
        printf("Goodbye!");
        exit(0);
    }
    stats_view_selector();
}

void signup_page(){
    FILE *fp, *np;
    fp = fopen("data/credentials/creds.bin", "ab");
    np = fopen("data/credentials/creds.bin", "rb");

    title("Sign Up", 2);

    char username[30], password[30], nusername[30], npassword[30];;
    printf("Choose a username: ");
    scanf("%s", username);
    fflush(stdin);
    printf("Choose a password: ");
    scanf("%s", password);

    for (int i = 0; username[i] != '\0'; i++) {
        if (username[i] == ',') {
            printf("\nUsername can not contain the character ','!");
            getch();
            user_conf_page();
        }
    }

    while (fscanf(np, "%29[^,],%29[^,],", nusername, npassword) != EOF){
        if (strcmp(nusername, username) == 0) {
            printf("\nUsername already exists!");
            getch();
            user_conf_page();
            return;
        }
    }

    fclose(np);

    fprintf(fp, "%s,%s,", username, password);
    fclose(fp);

    char extention[10] = ".bin", path[50] = "data/stats/";
    strcpy(stats_file_path, strcat(path, strcat(username, extention)));
    fp = fopen(stats_file_path, "wb");
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
    fp = fopen("data/credentials/creds.bin", "rb");
    title("Log In", 2);
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
            char extention[10] = ".bin", path[50] = "data/stats/";
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
    getch();
}

void edit_page() {
    title("Account Editor", 2);
    char options[][30] = {"Change Username", "Change Password", "Delete Account", "Go Back"};
    int ch = create_menu_traditional(4, options, 1, "Enter a choice: ");

    if (ch == 0) {
        title("Change Username", 2);
        FILE *fp, *np;
        char username[30], password[30], nusername[30], npassword[30], prev_username[30];
        int found = 0;
        printf("Enter current username: ");
        scanf("%s", username);
        fflush(stdin);
        strcpy(prev_username, username);
        printf("Enter password: ");
        scanf("%s", password);

        fp = fopen("data/credentials/creds.bin", "rb");
        while (fscanf(fp, "%29[^,],%29[^,],", nusername, npassword) != EOF) {
            if (strcmp(nusername, username) == 0 && strcmp(password, npassword) == 0) {
                fflush(stdin);
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
                np = fopen("data/credentials/temp.bin", "wb");
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

        if (!found) printf("\nIncorrect username or password!");
        else {
            remove("data/credentials/creds.bin");
            rename("data/credentials/temp.bin", "data/credentials/creds.bin");
            char extention[10] = ".bin", old_name[100] = "data/stats/", new_name[100] = "data/stats/";
            strcat(prev_username, extention);
            strcat(username, extention);
            strcat(old_name, prev_username);
            strcat(new_name, username);
            rename(old_name, new_name);
        }
    }
    else if (ch == 1) {
        title("Change Password", 2);
        FILE *fp, *np;
        char username[30], password[30], nusername[30], npassword[30];
        int found = 0;

        printf("Enter username: ");
        scanf("%s", username);
        fflush(stdin);
        printf("Enter current password: "); 
        scanf("%s", password);
        fp = fopen("data/credentials/creds.bin", "rb");
        np = fopen("data/credentials/temp.bin", "wb");

        while ((fscanf(fp, "%29[^,],%29[^,],", nusername, npassword) != EOF)) {
            if (strcmp(username, nusername) == 0 && strcmp(password, npassword) == 0) {
                printf("Enter new password: ");
                scanf("%s", password);
                fprintf(np, "%s,%s,", username, password);
                found = 1;
            }
            else {
                fprintf(np, "%s,%s,", nusername, npassword);
            }
        }

        fclose(fp);
        fclose(np);

        if (!found) printf("\nIncorrect username or password!");
        else {
            remove("data/credentials/creds.bin");
            rename("data/credentials/temp.bin", "data/credentials/creds.bin");
            printf("\nSuccessfully changed the password for the account '%s'!", username);
        }
        
    }
    else if (ch == 2) {
        title("Delete Account", 2);
        FILE *fp, *np;

        char username[30], password[30], nusername[30], npassword[30], conf;
        int deleted = 0, found = 0;
        printf("Enter username: ");
        scanf("%s", username);
        fflush(stdin);
        printf("Enter password: ");
        scanf("%s", password);
        
        fp = fopen("data/credentials/creds.bin", "rb");
        np = fopen("data/credentials/temp.bin", "wb");

        while ((fscanf(fp, "%29[^,],%29[^,],", nusername, npassword) != EOF)) {
            if (strcmp(nusername, username) == 0 && strcmp(npassword, password) == 0) {
                found = 1;
                fflush(stdin);
                printf("Enter 'y' to permanently delete all records of the account '%s': ", username);
                scanf("%c", &conf);
                if (conf != 'y') {
                    fprintf(np, "%s,%s,", nusername, npassword);
                }
                else{
                    deleted = 1;
                    printf("\nSuccessfully deleted the account '%s'!", username);
                }
            }
            else {
                fprintf(np, "%s,%s,", nusername, npassword);
            }
        }

        fclose(np);
        fclose(fp);

        remove("data/credentials/creds.bin");
        rename("data/credentials/temp.bin", "data/credentials/creds.bin");

        if (deleted) {
            char path[100] = "data/stats/", extention[10] = ".bin";
            strcat(username, extention);
            strcat(path, username);
            remove(path);
        }
        if (!found) printf("\nIncorrect username or password!");
    }
    else if (ch == 3) user_conf_page();
    getch();
    user_conf_page();
}