#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX 500
#define ITER 1000000                        // Set iterator to 1,000,000
#define PI 3.141592654
#define SIGMA 0.5

int main() {
    double count[2 * MAX];                  // double array of count
    double x1, x2, sum, mean, vay, pdis;

    time_t t;                               // Seed for rand
    FILE *fp;                               // File type pointer
    srand((unsigned) time(&t));         // Seed random function

    // Initializing sum & mean var.
    sum = 0;
    mean = 0;

    // Gaussian random Variable Gen
    for (int k = 0; k < 2 * MAX; k++) { count[k] = 0; }
    for (int i = 0; i < ITER; i++) {
        x1 = (double)rand() / RAND_MAX;                                 // range(0, 1)
        x2 = (double)rand() / RAND_MAX;                                 // range(0, 1)
        vay = (double)(sqrt(-2 * SIGMA * SIGMA * log(1 - x1))) * (double)cos(2 * PI * x2);       // Var for Gaussian random variable

        for (int k = -MAX; k < MAX; k++) {
            if ((vay >= (double)(k / 100.0)) && vay < (double)(k + 1.0) / 100.0) { count[k + MAX] += 1.0; }
        }

        sum += vay * vay;
        mean += vay;
    }
    // End of UDRVG


    // For PDF
    if ((fp = fopen("./gaussian_pdf.txt", "w")) == NULL) {
        printf("File %s can not be treated as \"%s\".\n");
        exit(0);
    }

    fprintf(fp, "#==================\n");
    fprintf(fp, "# Iteration = %d\n", ITER);
    fprintf(fp, "# mean = %lf, variance = %lf\n", mean / ITER, sum / ITER - pow(mean / ITER, 2));
    fprintf(fp, "#==================\n");
    fclose(fp);

    fp = fopen("./gaussian_pdf.txt", "a");
    for (int k = -MAX; k < MAX; k++) { fprintf(fp, "%lf %lf\n", (double) (k + 1.0) / 100.0, count[k + MAX] / ITER); }

    fclose(fp);
    // End of PDF

    // For CDF
    if ((fp = fopen("./gaussian_cdf.txt", "w")) == NULL) {
        printf("File %s can not be treated as \"%s\".\n");
        exit(0);
    }

    pdis = 0;
    fp = fopen("./gaussian_cdf.txt", "a");
    for (int k = -MAX; k < MAX; k++) {
        pdis += count[k + MAX];
        fprintf(fp, "%lf %lf\n", (double) (k + 1.0) / 100.0, pdis / ITER);
    }
    fclose(fp);
    // End of CDF

    return 0;
}

