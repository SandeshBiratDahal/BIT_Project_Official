#include<stdio.h>
#include<stdlib.h>

char current_username[30], stats_file_path[100];

void user_conf_page();
void login_page();
void signup_page();
void edit_page();
void stats_view_selector();
void view_accounts();
void fclose_secure(FILE *fp);

void user_conf_page(){
    title("The Game Library", 2);
    char options[][30] = {"Log In", "Sign Up", "Edit Account", "Saved Accounts", "Exit"};
    int ch = 0;
    ch = create_menu_traditional(5, options, 2, "Choose an option: ", title_pipe("The Game Library"));
    
    if (ch == 0) login_page();
    else if (ch == 1) signup_page();
    else if (ch == 2) edit_page();
    else if (ch == 3) view_accounts();
    else if (ch == 4) 
    {
        printf("Goodbye!");
        exit(0);
    }
    stats_view_selector();
}

void signup_page(){
    FILE *fp, *np;
    fp = fopen("data/credentials/creds.dat", "a");
    np = fopen("data/credentials/creds.dat", "r");

    title("Sign Up", 2);

    char username[100], password[100], nusername[100], npassword[100];;
    printf("\nChoose a username: ");
    scanf("%s", username);
    fflush(stdin);
    printf("Choose a password: ");
    scanf_password(password);

    for (int i = 0; username[i] != '\0'; i++) {
        if (username[i] == ',') {
            printf("\nUsername can not contain the character ','!");
            fclose_secure(fp);
            fclose_secure(np);
            getch();
            user_conf_page();
        }
    }

    while (fscanf(np, "%30[^,],%30[^,],", nusername, npassword) != EOF){
        if (strcmp(nusername, username) == 0) {
            printf("\nUsername already exists!");
            fclose_secure(fp);
            fclose_secure(np);
            getch();
            user_conf_page();
            return;
        }
    }

    fclose(np);

    fprintf(fp, "%s,%s,", username, password);
    fclose(fp);

    char extention[10] = ".dat", path[50] = "data/stats/";
    strcpy(stats_file_path, strcat(path, strcat(username, extention)));
    fp = fopen(stats_file_path, "w");
    fprintf(
        fp,
        "0,0,0,0,0,0,0,0,0,0,0,0,0,0,"
    ); //Hangman win/lose, RockPaperScissors win/lose/draw, Tictactoe easy/normal/hard win/lose/draw

    printf("\nSuccessfully created a new account!!");
    fclose_secure(fp);
    fclose_secure(np);

    getch();
    system("cls");
    user_conf_page();
}

void login_page(){
    FILE *fp;
    fp = fopen("data/credentials/creds.dat", "r");
    title("Log In", 2);
    char username[100], password[100], nusername[100], npassword[100];
    printf("\nEnter username: ");
    scanf("%s", username);
    fflush(stdin);
    printf("Enter password: ");
    scanf_password(password);

    int found = 0;

    while (fscanf(fp, "%30[^,],%30[^,],", nusername, npassword) != EOF) {
        if (strcmp(nusername, username) == 0 && strcmp(npassword, password) == 0) {
            printf("\nSuccessfully logged in as %s!!", nusername);
            strcpy(current_username, nusername);
            char extention[10] = ".dat", path[50] = "data/stats/";
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
    title("The Account Editor", 2);
    char options[][30] = {"Edit Username", "Edit Password", "<- Go Back"};
    int ch = create_menu_traditional(3, options, 2, "Enter a choice: ", title_pipe("The Account Editor"));

    if (ch == 0) {
        title("Edit Username", 2);
        FILE *fp, *np;
        char username[100], password[100], nusername[100], npassword[100], prev_username[100];
        int found = 0;
        printf("\nEnter current username: ");
        scanf("%s", username);
        fflush(stdin);
        strcpy(prev_username, username);
        printf("Enter password: ");
        scanf_password(password);

        fp = fopen("data/credentials/creds.dat", "r");
        fseek(fp, 0, SEEK_SET);
        while (fscanf(fp, "%30[^,],%30[^,],", nusername, npassword) != EOF) {
            if (strcmp(nusername, username) == 0 && strcmp(password, npassword) == 0) {
                fflush(stdin);
                printf("Enter new username: ");
                scanf("%s", username);

                fseek(fp, 0, SEEK_SET);
                while (fscanf(fp, "%30[^,],%30[^,],", nusername, npassword) != EOF) {
                    if (strcmp(username, nusername) == 0) {
                        printf("Username already exists!");
                        getch();
                        fclose(fp);
                        user_conf_page();
                        return;
                    }
                }
                fseek(fp, 0, SEEK_SET);
                np = fopen("data/credentials/temp.dat", "w");
                while (fscanf(fp, "%30[^,],%30[^,],", nusername, npassword) != EOF) {
                    if (strcmp(nusername, prev_username)) {
                        fprintf(np, "%s,%s,", nusername, npassword);
                    }
                }
                fprintf(np, "%s,%s,", username, password);                
                printf("\nSuccessfully changed the username from '%s' to '%s'!", prev_username, username);
                found = 1;
                fclose(np);
                break;
            }
        }

        fclose(fp);

        if (!found) printf("\nIncorrect username or password!");
        else {
            remove("data/credentials/creds.dat");
            rename("data/credentials/temp.dat", "data/credentials/creds.dat");
            char extention[10] = ".dat", old_name[100] = "data/stats/", new_name[100] = "data/stats/";
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
        char username[100], password[100], nusername[100], npassword[100];
        int found = 0;

        printf("\nEnter username: ");
        scanf("%s", username);
        fflush(stdin);
        printf("Enter current password: "); 
        scanf_password(password);
        fp = fopen("data/credentials/creds.dat", "r");
        np = fopen("data/credentials/temp.dat", "w");
        fseek(fp, 0, SEEK_SET);

        while ((fscanf(fp, "%30[^,],%30[^,],", nusername, npassword) != EOF)) {
            if (strcmp(username, nusername) == 0 && strcmp(password, npassword) == 0) {
                printf("Enter new password: ");
                scanf_password(password);
                fprintf(np, "%s,%s,", username, password);
                found = 1;
            }
            else {
                fprintf(np, "%s,%s,", nusername, npassword);
            }
        }

        fclose_secure(fp);
        fclose_secure(np);

        if (!found) printf("\nIncorrect username or password!");
        else {
            remove("data/credentials/creds.dat");
            rename("data/credentials/temp.dat", "data/credentials/creds.dat");
            printf("\nSuccessfully changed the password for the account '%s'!", username);
        }
        
    }
    
    else if (ch == 2) user_conf_page();

    else {
        title("Delete Account", 2);
        FILE *fp, *np;

        char username[100], password[100], nusername[100], npassword[100], conf;
        int deleted = 0, found = 0;
        printf("\nEnter username: ");
        scanf("%s", username);
        fflush(stdin);
        printf("Enter password: ");
        scanf_password(password);
        
        fp = fopen("data/credentials/creds.dat", "r");
        np = fopen("data/credentials/temp.dat", "w");
        fseek(fp, 0, SEEK_SET);

        while ((fscanf(fp, "%30[^,],%30[^,],", nusername, npassword) != EOF)) {
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

        fclose_secure(fp);
        fclose_secure(np);

        remove("data/credentials/creds.dat");
        rename("data/credentials/temp.dat", "data/credentials/creds.dat");

        if (deleted) {
            char path[100] = "data/stats/", extention[10] = ".dat";
            strcat(username, extention);
            strcat(path, username);
            remove(path);
        }
        if (!found) printf("\nIncorrect username or password!");
    }

    getch();
    user_conf_page();
}

void view_accounts() {
    title("Saved Accounts", 2);
    FILE *fp;
    fp = fopen("data/credentials/creds.dat", "r");
    char username[30], password[30];
    int i = 1;
    while ((fscanf(fp, "%30[^,],%30[^,],", username, password) != EOF)) {
        printf("%d. %s\n", i, username);
        i++;
    }
    fclose(fp);

    if (i == 1) printf("No any saved accounts! Select 'Sign Up' to create an account!");

    getch();
    fflush(stdin);
    user_conf_page();
}

void fclose_secure(FILE *fp) {
    if (fp) fclose(fp);
}