#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    float weight;
    int height;
    float score;
} Data;

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    Data *arr = (Data *)malloc(sizeof(Data) * n);


    FILE *fp_txt = fopen("input.txt", "w");
    if (fp_txt == NULL) {
        printf("input.txt File Open Error\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        scanf("%d %f %d %f", &arr[i].id, &arr[i].weight, &arr[i].height, &arr[i].score);
        fprintf(fp_txt, "%d %f %d %f\n", arr[i].id, arr[i].weight, arr[i].height, arr[i].score);
    }
    fclose(fp_txt);

    fp_txt = fopen("input.txt", "r");
    FILE *fp_bin = fopen("test.bin", "wb");
    if (fp_txt == NULL || fp_bin == NULL) {
        printf("File Open Error\n");
        exit(1);
    }

    Data temp;
    while (fscanf(fp_txt, "%d %f %d %f", &temp.id, &temp.weight, &temp.height, &temp.score) != EOF) {
        fwrite(&temp, sizeof(Data), 1, fp_bin);
    }

    fclose(fp_txt);
    fclose(fp_bin);

    fp_bin = fopen("test.bin", "rb");
    if (fp_bin == NULL) {
        printf("test.bin File Open Error\n");
        exit(1);
    }

    fseek(fp_bin, k, SEEK_SET);
    int output;
    fread(&output, sizeof(int), 1, fp_bin);
    printf("%d", output);

    fclose(fp_bin);
    free(arr);

    return 0;
}
