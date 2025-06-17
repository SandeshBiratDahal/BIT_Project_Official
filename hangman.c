
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
    char current_word[10], guessed_word[10] = "__________";
    strcpy(current_word, words[current_word_index]);

    int word_length = strlen(current_word);



    printf("---%s---%d---", current_word, word_length);
}