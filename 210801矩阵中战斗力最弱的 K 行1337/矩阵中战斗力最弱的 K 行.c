/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int cmp( const void *a, const void *b ){ 
    return ((int *)a)[1] - ((int *)b)[1];
}

int* kWeakestRows(int** mat, int matSize, int* matColSize, int k, int* returnSize){
    int i, j;

    int **ans = (int **)malloc(sizeof(int *) * matSize);
    for( i=0; i<matSize; i++ ){
        ans[i] = malloc(sizeof(int) * 2);
        ans[i][0] = i;
        ans[i][1] = 0;
        for( j=0; j<matColSize[i]; j++ ){
            if( mat[i][j] == 1 ){
                ans[i][1]++;
            }
        }
    }
    qsort( ans, matSize, sizeof(int)*2, cmp );
    int *ret = (int)malloc(sizeof(int) * k);
    for( i=0; i<k; i++ ){
        ret[i] = ans[i][0];
    }
    *returnSize = k;

    return ret;
}
