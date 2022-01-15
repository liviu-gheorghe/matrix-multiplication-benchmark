#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

unsigned long long score[] = {0,0,0,0,0,0,0};
double time_arr[] = {0,0,0,0,0,0,0};

int randNumber(int start, int end) {
    return rand() % (end - start + 1) + start;
}

int min(int a, int b) {
    return a < b ? a : b;
}

void printUsage() {
    puts(
         "utilizare: ./mmb <N> <mode> <test_count> <block_size> <outfile>\n"
         "\tN = dimensiunea matricei\n"
         "\tmode = tipul de inmultire -> 1 pt A*A, 2 pt A(t)*A, 3 pt A*A(t), 4 pt A(t)*A(t)\n"
         "\ttest_count = numarul de teste\n"
         "\tblock_size = dimensiunea blocului pt inmultirea block to block\n"
         "\toutfile = fisierul in care se vor scrie datele\n"
    );
}

int main(int argc, char* argv[]) {

    if(argc < 6 || !strcmp("--help", argv[1])) {
        printUsage();
        exit(0);
    }

    double cpu_time_used;
    clock_t start_time, end_time;

    int score_idx = 0;
    int prevA = 0, prevB = 0, prevX = 0;
    char statsCliFormat[] = "Scorul pt var%d (%s) este %lld, iar timpul de executie este %f, ratia scor/timp = %f\n";

    FILE* outfile;

    int N;
    int BLOCK_SIZE;
    int mode;
    int test_count;

    N = atoi(argv[1]);
    mode = atoi(argv[2]);

    test_count = atoi(argv[3]);
    BLOCK_SIZE = atoi(argv[4]);

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
    for(u_int32_t i = 0; i<7; i++) {
        score[i] = 0;
    }

    outfile = fopen(argv[5], "a");

    for(int i=0;i<N;++i) {
        for (int j = 0; j < N; ++j) {
            A[i][j] = randNumber(1, 0xA);
            X[i][j] = 0;
        }
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

    printf(statsCliFormat,score_idx, "ijk", score[score_idx], cpu_time_used, score[score_idx] / cpu_time_used);

    score_idx++;

    if(N<=25)
    for(int i=0;i<N;++i) {
        for(int j=0;j<N;++j)
        {
            printf("%lld ", X[i][j]);
        }
        printf("\n");
    }

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

    printf(statsCliFormat,score_idx, "jik", score[score_idx], cpu_time_used, score[score_idx] / cpu_time_used);
    score_idx++;

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

    printf(statsCliFormat,score_idx, "kij", score[score_idx], cpu_time_used, score[score_idx] / cpu_time_used);
    score_idx++;

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

    printf(statsCliFormat,score_idx, "kji", score[score_idx], cpu_time_used, score[score_idx] / cpu_time_used);
    score_idx++;

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
    printf(statsCliFormat,score_idx, "ikj", score[score_idx], cpu_time_used, score[score_idx] / cpu_time_used);
    score_idx++;

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
    printf(statsCliFormat,score_idx, "jki", score[score_idx], cpu_time_used, score[score_idx] / cpu_time_used);
    score_idx++;

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
    printf(statsCliFormat,score_idx, "block", score[score_idx], cpu_time_used, score[score_idx] / cpu_time_used);
    score_idx++;

    fprintf(
        outfile,
        "%d,%lld,%lld,%lld,%lld,%lld,%lld,%lld,%f,%f,%f,%f,%f,%f,%f,%d\n",
        N,
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
        time_arr[6],
        BLOCK_SIZE
    );

    fclose(outfile);

    }
    return 0;
}
