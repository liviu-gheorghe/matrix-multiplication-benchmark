#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned long long score[] = {0,0,0,0,0,0,0};
double time_arr[] = {0,0,0,0,0,0,0};

int randNumber(int start, int end) {

    return rand() % (end - start + 1) + start;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {

    double cpu_time_used;
    clock_t start_time, end_time;

    int score_idx = 0;
    int prevA = 0, prevB = 0, prevX = 0;

    FILE* outfile;

    int N;
    int BLOCK_SIZE;
    int mode; // 1 = A*A, 2  = A(t) * A, 3 = A* A(t), 4 = A(t) * A(t)
    int test_count;

    printf("Introduceti dimensiunea matricei si modul (1 = A*A, 2  = A(t) * A, 3 = A* A(t), 4 = A(t) * A(t)):");


    scanf("%d", &N);
    scanf("%d", &mode);

    printf("Introduceti nr de teste si dimensiunea block-ului(pt calcul pe blocuri):");
    scanf("%d", &test_count);
    scanf("%d", &BLOCK_SIZE);

    long long ** A = (long long **) malloc (N * sizeof(long long*));
    for(int i=0;i<N;i++) {
        A[i] = (long long*) malloc(N* sizeof(long long));
    }

    long long ** X = (long long **) malloc (N * sizeof(long long*));
    for(int i=0;i<N;i++) {
        X[i] = (long long*) malloc(N* sizeof(long long));
    }

    for (int test_idx = 0; test_idx < test_count; test_idx++) {

    score_idx = 0;
    score[0] = 0;
    score[1] = 0;
    score[2] = 0;
    score[3] = 0;
    score[4] = 0;
    score[5] = 0;
    score[6] = 0;

    if(mode == 1)
    outfile = fopen("data_axa.csv", "a");
    else if(mode == 2)
    outfile = fopen("data_a(t)xa.csv", "a");
    else if(mode == 3)
    outfile = fopen("data_axa(t).csv", "a");
    else if(mode == 4)
    outfile = fopen("data_a(t)xa(t).csv", "a");
    else printf("Mod incorect");

    for(int i=0;i<N;++i) {
        for (int j = 0; j < N; ++j) {
            A[i][j] = randNumber(1, 0xA);
            X[i][j] = 0;
        }
    }

   if(N<=25)
    for(int i=0;i<N;++i) {
        for(int j=0;j<N;++j) {
            printf("%lld ", A[i][j]);
        }
        printf("\n");
    }

    //VAR 1

    prevA = 0; prevB = 0; prevX = 0;

    start_time = clock();

    for(int i=0;i<N;++i)
    for(int j=0;j<N;++j)
    for(int k=0;k<N;++k)
    {

        switch(mode) {
            case 1:
            X[i][j] += A[i][k] * A[k][j];
            score[score_idx] += abs((N*i+k) - prevA);
            score[score_idx] += abs((N*k+j) - prevB);
            score[score_idx] += abs((N*i+j) - prevX);
            prevX = N*i + j;
            prevA = N*i + k;
            prevB = N*k + j;
            break;
            case 2:
            X[i][j] += A[k][i] * A[k][j];
            score[score_idx] += abs((N*k+i) - prevA);
            score[score_idx] += abs((N*k+j) - prevB);
            score[score_idx] += abs((N*i+j) - prevX);
            prevX = N*i + j;
            prevA = N*k + i;
            prevB = N*k + j;
            break;
            case 3:
            X[i][j] += A[i][k] * A[j][k];
            score[score_idx] += abs((N*i+k) - prevA);
            score[score_idx] += abs((N*j+k) - prevB);
            score[score_idx] += abs((N*i+j) - prevX);
            prevX = N*i + j;
            prevA = N*i + k;
            prevB = N*j + k;
            break;
            case 4:
            X[i][j] += A[k][i] * A[j][k];
            score[score_idx] += abs((N*k+i) - prevA);
            score[score_idx] += abs((N*j+k) - prevB);
            score[score_idx] += abs((N*i+j) - prevX);
            prevX = N*i + j;
            prevA = N*k + i;
            prevB = N*j + k;
            break;
            default:
            break;
        }

    }

    end_time = clock();

    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    time_arr[score_idx] = cpu_time_used;

    printf("Scorul pt var1 (ijk) este %lld, iar timpul de executie este %f, ratia scor/timp = %f\n", score[score_idx], cpu_time_used, score[score_idx] / cpu_time_used);

    score_idx++;


    printf("N=%d\n", N);

    //exit(0);
    printf("===============VAR1==============\n");


    if(N<=25)
    for(int i=0;i<N;++i) {
        for(int j=0;j<N;++j)
        {

            printf("%lld ", X[i][j]);
        }
        printf("\n");
    }

        printf("===============VAR1==============\n");


    for(int i=0;i<N;++i)
    for(int j=0;j<N;++j)
        X[i][j] = 0;


    //VAR 2

        prevA = 0; prevB = 0; prevX = 0;

    start_time = clock();

    for(int j=0;j<N;++j)
    for(int i=0;i<N;++i)
    for(int k=0;k<N;++k)
    {
        switch(mode) {
            case 1:
            X[i][j] += A[i][k] * A[k][j];
            score[score_idx] += abs((N*i+k) - prevA);
            score[score_idx] += abs((N*k+j) - prevB);
            score[score_idx] += abs((N*i+j) - prevX);
            prevX = N*i + j;
            prevA = N*i + k;
            prevB = N*k + j;
            break;
            case 2:
            X[i][j] += A[k][i] * A[k][j];
            score[score_idx] += abs((N*k+i) - prevA);
            score[score_idx] += abs((N*k+j) - prevB);
            score[score_idx] += abs((N*i+j) - prevX);
            prevX = N*i + j;
            prevA = N*k + i;
            prevB = N*k + j;
            break;
            case 3:
            X[i][j] += A[i][k] * A[j][k];
            score[score_idx] += abs((N*i+k) - prevA);
            score[score_idx] += abs((N*j+k) - prevB);
            score[score_idx] += abs((N*i+j) - prevX);
            prevX = N*i + j;
            prevA = N*i + k;
            prevB = N*j + k;
            break;
            case 4:
            X[i][j] += A[k][i] * A[j][k];
            score[score_idx] += abs((N*k+i) - prevA);
            score[score_idx] += abs((N*j+k) - prevB);
            score[score_idx] += abs((N*i+j) - prevX);
            prevX = N*i + j;
            prevA = N*k + i;
            prevB = N*j + k;
            break;
            default:
            break;
        }

    }

    end_time = clock();

    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    time_arr[score_idx] = cpu_time_used;

    printf("Scorul pt var2 (jik) este %lld, iar timpul de executie este %f, ratia scor/timp = %f\n", score[score_idx], cpu_time_used, score[score_idx] / cpu_time_used);
    score_idx++;


    printf("N=%d\n", N);

    printf("===============VAR2==============\n");

    // for(int i=0;i<N;++i) {
    //     for(int j=0;j<N;++j)
    //     {

    //         printf("%d ", X[i][j]);
    //     }
    //     printf("\n");
    // }

        printf("===============VAR2==============\n");



    for(int i=0;i<N;++i)
    for(int j=0;j<N;++j)
        X[i][j] = 0;

    //VAR 3

        prevA = 0; prevB = 0; prevX = 0;


    start_time = clock();

    for(int k=0;k<N;++k)
    for(int i=0;i<N;++i)
    for(int j=0;j<N;++j)
    {

        switch(mode) {
            case 1:
            X[i][j] += A[i][k] * A[k][j];
            score[score_idx] += abs((N*i+k) - prevA);
            score[score_idx] += abs((N*k+j) - prevB);
            score[score_idx] += abs((N*i+j) - prevX);
            prevX = N*i + j;
            prevA = N*i + k;
            prevB = N*k + j;
            break;
            case 2:
            X[i][j] += A[k][i] * A[k][j];
            score[score_idx] += abs((N*k+i) - prevA);
            score[score_idx] += abs((N*k+j) - prevB);
            score[score_idx] += abs((N*i+j) - prevX);
            prevX = N*i + j;
            prevA = N*k + i;
            prevB = N*k + j;
            break;
            case 3:
            X[i][j] += A[i][k] * A[j][k];
            score[score_idx] += abs((N*i+k) - prevA);
            score[score_idx] += abs((N*j+k) - prevB);
            score[score_idx] += abs((N*i+j) - prevX);
            prevX = N*i + j;
            prevA = N*i + k;
            prevB = N*j + k;
            break;
            case 4:
            X[i][j] += A[k][i] * A[j][k];
            score[score_idx] += abs((N*k+i) - prevA);
            score[score_idx] += abs((N*j+k) - prevB);
            score[score_idx] += abs((N*i+j) - prevX);
            prevX = N*i + j;
            prevA = N*k + i;
            prevB = N*j + k;
            break;
            default:
            break;
        }

    }

    end_time = clock();

    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    time_arr[score_idx] = cpu_time_used;

    printf("Scorul pt var3 (kij) este %lld, iar timpul de executie este %f, ratia scor/timp = %f\n", score[score_idx], cpu_time_used, score[score_idx] / cpu_time_used);
    score_idx++;


    printf("N=%d\n", N);

    printf("===============VAR3==============\n");

    // for(int i=0;i<N;++i) {
    //     for(int j=0;j<N;++j)
    //     {

    //         printf("%d ", X[i][j]);
    //     }
    //     printf("\n");
    // }

        printf("===============VAR3==============\n");



    for(int i=0;i<N;++i)
    for(int j=0;j<N;++j)
        X[i][j] = 0;


    //VAR 4

    prevA = 0; prevB = 0; prevX = 0;
    start_time = clock();

    for(int k=0;k<N;++k)
    for(int j=0;j<N;++j)
    for(int i=0;i<N;++i)
    {

        switch(mode) {
            case 1:
            X[i][j] += A[i][k] * A[k][j];
            score[score_idx] += abs((N*i+k) - prevA);
            score[score_idx] += abs((N*k+j) - prevB);
            score[score_idx] += abs((N*i+j) - prevX);
            prevX = N*i + j;
            prevA = N*i + k;
            prevB = N*k + j;
            break;
            case 2:
            X[i][j] += A[k][i] * A[k][j];
            score[score_idx] += abs((N*k+i) - prevA);
            score[score_idx] += abs((N*k+j) - prevB);
            score[score_idx] += abs((N*i+j) - prevX);
            prevX = N*i + j;
            prevA = N*k + i;
            prevB = N*k + j;
            break;
            case 3:
            X[i][j] += A[i][k] * A[j][k];
            score[score_idx] += abs((N*i+k) - prevA);
            score[score_idx] += abs((N*j+k) - prevB);
            score[score_idx] += abs((N*i+j) - prevX);
            prevX = N*i + j;
            prevA = N*i + k;
            prevB = N*j + k;
            break;
            case 4:
            X[i][j] += A[k][i] * A[j][k];
            score[score_idx] += abs((N*k+i) - prevA);
            score[score_idx] += abs((N*j+k) - prevB);
            score[score_idx] += abs((N*i+j) - prevX);
            prevX = N*i + j;
            prevA = N*k + i;
            prevB = N*j + k;
            break;
            default:
            break;
        }

    }

    end_time = clock();

    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    time_arr[score_idx] = cpu_time_used;


    printf("Scorul pt var4 (kji) este %lld, iar timpul de executie este %f, ratia scor/timp = %f\n", score[score_idx], cpu_time_used, score[score_idx] / cpu_time_used);
    score_idx++;


    printf("N=%d\n", N);

    printf("===============VAR4==============\n");

    // for(int i=0;i<N;++i) {
    //     for(int j=0;j<N;++j)
    //     {

    //         printf("%d ", X[i][j]);
    //     }
    //     printf("\n");
    // }

        printf("===============VAR4==============\n");


    for(int i=0;i<N;++i)
    for(int j=0;j<N;++j)
        X[i][j] = 0;



    //VAR 5

    prevA = 0; prevB = 0; prevX = 0;
    start_time = clock();
    for(int i=0;i<N;++i)
    for(int k=0;k<N;++k)
    for(int j=0;j<N;++j)
    {

        switch(mode) {
            case 1:
            X[i][j] += A[i][k] * A[k][j];
            score[score_idx] += abs((N*i+k) - prevA);
            score[score_idx] += abs((N*k+j) - prevB);
            score[score_idx] += abs((N*i+j) - prevX);
            prevX = N*i + j;
            prevA = N*i + k;
            prevB = N*k + j;
            break;
            case 2:
            X[i][j] += A[k][i] * A[k][j];
            score[score_idx] += abs((N*k+i) - prevA);
            score[score_idx] += abs((N*k+j) - prevB);
            score[score_idx] += abs((N*i+j) - prevX);
            prevX = N*i + j;
            prevA = N*k + i;
            prevB = N*k + j;
            break;
            case 3:
            X[i][j] += A[i][k] * A[j][k];
            score[score_idx] += abs((N*i+k) - prevA);
            score[score_idx] += abs((N*j+k) - prevB);
            score[score_idx] += abs((N*i+j) - prevX);
            prevX = N*i + j;
            prevA = N*i + k;
            prevB = N*j + k;
            break;
            case 4:
            X[i][j] += A[k][i] * A[j][k];
            score[score_idx] += abs((N*k+i) - prevA);
            score[score_idx] += abs((N*j+k) - prevB);
            score[score_idx] += abs((N*i+j) - prevX);
            prevX = N*i + j;
            prevA = N*k + i;
            prevB = N*j + k;
            break;
            default:
            break;
        }

    }

    end_time = clock();

    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    time_arr[score_idx] = cpu_time_used;
    printf("Scorul pt var5 (ikj) este %lld, iar timpul de executie este %f, ratia scor/timp = %f\n", score[score_idx], cpu_time_used, score[score_idx] / cpu_time_used);
    score_idx++;



    printf("N=%d\n", N);

    printf("===============VAR5==============\n");

    // for(int i=0;i<N;++i) {
    //     for(int j=0;j<N;++j)
    //     {

    //         printf("%d ", X[i][j]);
    //     }
    //     printf("\n");
    // }

        printf("===============VAR5==============\n");


    for(int i=0;i<N;++i)
    for(int j=0;j<N;++j)
        X[i][j] = 0;


    //VAR 6

    prevA = 0; prevB = 0; prevX = 0;

    start_time = clock();
    for(int j=0;j<N;++j)
    for(int k=0;k<N;++k)
    for(int i=0;i<N;++i)
    {
        switch(mode) {
            case 1:
            X[i][j] += A[i][k] * A[k][j];
            score[score_idx] += abs((N*i+k) - prevA);
            score[score_idx] += abs((N*k+j) - prevB);
            score[score_idx] += abs((N*i+j) - prevX);
            prevX = N*i + j;
            prevA = N*i + k;
            prevB = N*k + j;
            break;
            case 2:
            X[i][j] += A[k][i] * A[k][j];
            score[score_idx] += abs((N*k+i) - prevA);
            score[score_idx] += abs((N*k+j) - prevB);
            score[score_idx] += abs((N*i+j) - prevX);
            prevX = N*i + j;
            prevA = N*k + i;
            prevB = N*k + j;
            break;
            case 3:
            X[i][j] += A[i][k] * A[j][k];
            score[score_idx] += abs((N*i+k) - prevA);
            score[score_idx] += abs((N*j+k) - prevB);
            score[score_idx] += abs((N*i+j) - prevX);
            prevX = N*i + j;
            prevA = N*i + k;
            prevB = N*j + k;
            break;
            case 4:
            X[i][j] += A[k][i] * A[j][k];
            score[score_idx] += abs((N*k+i) - prevA);
            score[score_idx] += abs((N*j+k) - prevB);
            score[score_idx] += abs((N*i+j) - prevX);
            prevX = N*i + j;
            prevA = N*k + i;
            prevB = N*j + k;
            break;
            default:
            break;
        }

    }

    end_time = clock();

    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    time_arr[score_idx] = cpu_time_used;
    printf("Scorul pt var6 (jki) este %lld, iar timpul de executie este %f, ratia scor/timp = %f\n", score[score_idx], cpu_time_used, score[score_idx] / cpu_time_used);
    score_idx++;


    printf("N=%d\n", N);

    printf("===============VAR6==============\n");

    // for(int i=0;i<N;++i) {
    //     for(int j=0;j<N;++j)
    //     {

    //         printf("%d ", X[i][j]);
    //     }
    //     printf("\n");
    // }

        printf("===============VAR6==============\n");




    for(int i=0;i<N;++i)
    for(int j=0;j<N;++j)
        X[i][j] = 0;

    //VAR Block to Block

    prevA = 0; prevB = 0; prevX = 0;

    int ii, jj, kk, maxi, maxk, maxj;


    for(ii = 0; ii < N; ii += BLOCK_SIZE)
    for(kk = 0; kk < N; kk += BLOCK_SIZE)
    for(jj = 0;jj < N; jj += BLOCK_SIZE)
    {
        maxi = min(ii+BLOCK_SIZE, N);
        for(int i=ii;i<maxi;i++) {
            maxk = min(kk+BLOCK_SIZE, N);
            for(int k=kk;k<maxk;k++) {
                maxj = min(jj+BLOCK_SIZE, N);
                for(int j=jj; j<maxj;j++) {
                    X[i][j] += A[i][k] * A[k][j];
                    score[score_idx] += abs((N*i+k) - prevA);
                    score[score_idx] += abs((N*k+j) - prevB);
                    score[score_idx] += abs((N*i+j) - prevX);
                    prevX = N*i + j;
                    prevA = N*i + k;
                    prevB = N*k + j;
                }
            }
        }
    }

    end_time = clock();


    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    time_arr[score_idx] = cpu_time_used;
    printf("Scorul pt var7 (Block) este %lld, iar timpul de executie este %f, ratia scor/timp = %f\n", score[score_idx], cpu_time_used, score[score_idx] / cpu_time_used);
    score_idx++;



    if(N<=25)
    for(int i=0;i<N;++i) {
        for(int j=0;j<N;++j)
        {

            printf("%lld ", X[i][j]);
        }
        printf("\n");
    }

    printf("N=%d\n", N);

    //exit(0);
    printf("===============VAR6==============\n");

    // for(int i=0;i<N;++i) {
    //     for(int j=0;j<N;++j)
    //     {

    //         printf("%d ", X[i][j]);
    //     }
    //     printf("\n");
    // }

        printf("===============VAR6==============\n");




    fprintf(
        outfile,
        "%lld,%lld,%lld,%lld,%lld,%lld,%lld,%f,%f,%f,%f,%f,%f,%f\n",
        score[0],
        score[1],
        score[2],
        score[3],
        score[4],
        score[5],
        score[6],
        time_arr[0],
        time_arr[1],
        time_arr[2],
        time_arr[3],
        time_arr[4],
        time_arr[5],
        time_arr[6]
    );


    fclose(outfile);

    }

    return 0;
}
