#include <stdio.h>
void display(char current_word[], char guessed_word[], int word_length, int number_of_attempts);
int check_letter(char word[], char letter, int word_length);
int compare_words(char current_word[], char guessed_word[], int word_length);

void hangman(){
    char words[][100] = {
        "account", "balance", "blanket", "bottle", "brother", "camera", "carpet", "cartoon", "ceil", "charger",
        "college", "comfort", "counter", "curtain", "customer", "dance", "daytime", "decision", "dessert", "dinner",
        "dolphin", "draw", "drive", "even", "exercise", "family", "feather", "fiction", "flavor", "flowers",
        "football", "freezer", "friends", "grocery", "hammer", "hang", "holiday", "homework", "husband", "iceberg",
        "insects", "jacket", "jealous", "kitchen", "laundry", "lemonade", "library", "listen", "luggage", "manager",
        "message", "morning", "mountain", "muffins", "napkins", "notebook", "outside", "package", "painter", "parents",
        "passenger", "peaches", "pencil", "picture", "plastic", "popcorn", "printer", "problem", "process", "read",
        "receipt", "remote", "rest", "run", "sandbox", "school", "screen", "section", "shampoo", "shelter",
        "shop", "shout", "sidewalk", "sleep", "soccer", "station", "storage", "student", "subject", "sunrise",
        "teacher", "text", "traffic", "train", "travel", "truck", "vacuum", "wait", "walk", "weather"
    };
    int number_of_words = 100;

    srand(time(0));
    int current_word_index = rand() % number_of_words;
    char current_word[10], guessed_word[10] = "__________", current_letter;
    strcpy(current_word, words[current_word_index]);

    int word_length = strlen(current_word), number_of_attempts = 5, successfully_guessed = 0, letter_in_word = 0, i;

    while (1){
        display(current_word, guessed_word, word_length, number_of_attempts);
        fflush(stdin);
        printf("Enter a letter: ");
        scanf("%c", &current_letter);

        letter_in_word = check_letter(current_word, current_letter, word_length);

        if (!letter_in_word) {
            printf("Letter not in the word!!");
            getch();
            number_of_attempts--;
        }
        else {
            for (i = 0; i < word_length; i++){
                if (current_word[i] == current_letter) {
                    guessed_word[i] = current_letter;
                }
            }
            successfully_guessed = compare_words(current_word, guessed_word, word_length);
        }

        if (!number_of_attempts || successfully_guessed){
            break;
        }
    }

}

void display(char current_word[], char guessed_word[], int word_length, int number_of_attempts){
    system("cls");
    printf("----Hangman----\n\n\n");

    int i;
    
    for (i = 0; i < word_length; i++) printf("%c  ", guessed_word[i]);
    printf("\t\tAttempts Left: %d\n\n", number_of_attempts);
}

int check_letter(char word[], char letter, int word_length){
    int i;
    for (i = 0; i < word_length; i++) {
        if (word[i] == letter) return 1;
    }
    return 0;
}

int compare_words(char current_word[], char guessed_word[], int word_length){
    int i;
    for (i = 0; i < word_length; i++){
        if (current_word[i] != guessed_word[i]) return 0;
    }
    return 1;
}