#include<stdio.h>

void edit_file(char file_path[100], int index, int increase_by, int set_to){
    FILE *fp;
    fp = fopen(file_path, "rb");
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
    fclose(fp);
    fp = fopen(file_path, "wb");
    for (int j = 0; j < i; j++) fprintf(fp, "%d,", tracked_data[j]);
    fclose(fp);
}

int fetch(char file_path[100], int index) {
    FILE *fp;
    fp = fopen(file_path, "rb");
    int i = 0, data;
    while (fscanf(fp, "%d,", &data) != EOF) {
        if (index == i) return data;
        i++;
    }
    return -1;
}