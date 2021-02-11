#include <cstdio>
#include <cstdlib>


extern "C" int CalcMatrixRowColSums_(const int *x, int nrows, int ncols,
                                 int *row_sums, int *col_sums);

void CalcMatrixRowColSumsCpp(const int *x, int nrows, int ncols,
                             int *row_sums, int *col_sums){
    for(int j=0; j<ncols; ++j) col_sums[j] = 0;

    for(int i=0; i<nrows; ++i){
        row_sums[i] = 0;
        int k=i*ncols;

        for(int j=0; j<ncols; ++j){
            int temp = x[k+j];
            row_sums[i] += temp;
            col_sums[j] += temp;
        }
    }
}

void PrintResult(const int *x, int nrows, int ncols,
                 int *row_sums, int *col_sums){
    for(int i = 0; i < nrows; ++i){
        int k = i * ncols;
        for(int j = 0; j < ncols; ++j){
            printf("  %4d", x[k + j]);
        }
        printf("  --  %d\n", row_sums[i]);
    }
    for(int j = 0; j < ncols; ++j){
        printf("  %4d", col_sums[j]);
    }
    printf("\n");
}

int main(void){
    const int nrows = 7, ncols = 5;
    int x[nrows][ncols];

    srand(13);
    for(int i = 0; i < nrows; ++i){
        for(int j = 0; j < ncols; ++j){
            x[i][j] = rand()%100;
        }
    }

    int row_sum1[nrows], col_sum1[ncols];
    int row_sum2[nrows], col_sum2[ncols];

    CalcMatrixRowColSumsCpp((const int*)x, nrows, ncols, row_sum1, col_sum1);
    printf("Results using CalcMatrixRowColSumsCpp()\n");
    PrintResult((const int*)x, nrows, ncols, row_sum1, col_sum1);

    CalcMatrixRowColSums_((const int*)x, nrows, ncols, row_sum2, col_sum2);
    printf("Results using CalcMatrixRowColSums_()\n");
    PrintResult((const int*)x, nrows, ncols, row_sum2, col_sum2);

    return 0;
}
