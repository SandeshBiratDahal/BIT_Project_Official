#include <stdio.h>
#include <stdlib.h>
#include "utilities.c"

//MENUS
void user_conf_page();
void login_page();
void signup_page();

int main(){
    system("cls");
    user_conf_page();
    return 0;
}

void user_conf_page(){
    printf("----The Game Library----\n\n");
    char options[][30] = {"Log In", "Sign Up"};
    int ch = 0;
    ch = create_menu_traditional(2, options, 1, "Choose an option: ");
    
    if (ch == 0) login_page();
    else if (ch == 1) signup_page();
}

void signup_page(){
    FILE *fp;
    fp = fopen("data/credentials/creds.txt", "ab");

    char username[30], password[30];
    printf("Choose a username: ");
    scanf("%s", username);
    printf("Choose a password: ");
    scanf("%s", password);

    fprintf(fp, "%s,%s", username, password);
    fclose(fp);
}

void login_page(){

}