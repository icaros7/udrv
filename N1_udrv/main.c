#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX 500
#define ITER 100000
#define PI 3.141592654


int main() {
    double count[2 * MAX];                  // double array of count
    double x1, sum, mean, vay, pdis;
    int max = 2;
    int min = 0;

    time_t t;                               // Seed for rand
    FILE *fp;                               // File type pointer
    srand((unsigned) time(&t));  // Seed random function

    // Initializing sum & mean var.
    sum = 0;
    mean = 0;

    // Uniformly distributed random Variable Gen
    for (int k = 0; k < 2 * MAX; k++) { count[k] = 0; }
    for (int i = 0; i < ITER; i++) {
        /*
         * x1 = (double)rand() / RAND_MAX;
         * vay = x1;
         */
        x1 = ((double)rand() / (RAND_MAX + 1)) * (max - (min)) + min; // Set UDRV range (max ~ min)
        vay = x1 / 2; // Set Function c to Function c * 0.5

        for (int k = -MAX; k < MAX; k++) {
            if ((vay >= (double)(k / 200.0)) && vay < (double)(k + 1.0) / 200.0) { count[k + MAX] += 1.0; }
        }

        sum += vay * vay;
        mean += vay;
    }

    for (int k = -MAX; k < MAX; k++) { printf("%lf %lf\n", (double)(k + 1.0) / 100.0, count[k + MAX] / ITER); }

    printf("var = %lf, mean = %lf\n", sum / ITER - pow(mean / ITER, 2), mean / ITER);
    // End of UDRVG


    // For PDF
    if ((fp = fopen("./data1.txt", "w")) == NULL) {
        printf("File %s can not be treated as \"%s\".\n");
        exit(0);
    }

    fprintf(fp, "#==================\n");
    fprintf(fp, "# Iteration = %d\n", ITER);
    fprintf(fp, "# mean = %lf, variance = %lf\n", mean / ITER, sum / ITER - pow(mean / ITER, 2));
    fprintf(fp, "#==================\n");
    fclose(fp);

    fp = fopen("./data1.txt", "a");
    for (int k = -MAX; k < MAX; k++) { fprintf(fp, "%lf %lf\n", (double) (k + 1.0) / 100.0, count[k + MAX] / ITER); }

    fclose(fp);
    // End of PDF

    // For CDF
    if ((fp = fopen("./data2.txt", "w")) == NULL) {
        printf("File %s can not be treated as \"%s\".\n");
        exit(0);
    }

    pdis = 0;
    fp = fopen("./data2.txt", "a");
    for (int k = -MAX; k < MAX; k++) {
        pdis += count[k + MAX];
        fprintf(fp, "%lf %lf\n", (double) (k + 1.0) / 100.0, pdis / ITER);
    }
    fclose(fp);
    // End of CDF

    return 0;
}
