#include<stdio.h>

void edit_file(char file_path[100], int index, int increase_by, int set_to){
    FILE *fp;
    fp = fopen(file_path, "r");
    int data, i = 0;
    int tracked_data[200];
    while (fscanf(fp, "%d,", &data) != EOF) {
        if (index == i) {
            if (increase_by) data += increase_by;
            else data = set_to;
        }
        tracked_data[i] = data;
        i++;
    }
    for (int j = 0; j < i; j++) {
        printf("%d\n", tracked_data[j]);
    }
    fclose(fp);
    fp = fopen(file_path, "w");
    for (int j = 0; j < i; j++) fprintf(fp, "%d,", tracked_data[j]);
    fclose(fp);
}