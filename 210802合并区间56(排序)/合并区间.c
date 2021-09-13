/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
// int cmp( const void *a, const void *b ){
//     return ((int *)a)[0] - ((int *)b)[0];
// }

// 第一个元素从小到大排序；如果第一个元素相等，则根据第二个元素从小到大排序
int cmp(const void *arr1, const void *arr2) {
    int *ar1 = *(int **)arr1, *ar2 = *(int **)arr2;

    if (ar1[0] != ar2[0]) {
        return ar1[0] - ar2[0];
    }
    return ar1[1] - ar2[1];
}


int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes){
    int Left, Right, len, max;
    int **ret = (int **)malloc(sizeof(int *) * intervalsSize);

    qsort( intervals, intervalsSize, sizeof(intervals[0]), cmp );
    Left = 0;
    Right = 1;
    len = 0;
    max = intervals[Left][1];

    while( Right < intervalsSize ){
        if( max >= intervals[Right][0] ){
            max = max > intervals[Right][1] ? max : intervals[Right][1];
            Right++;
            continue;
        }
        ret[len] = (int *)malloc(sizeof(int) * 2);
        ret[len][0] = intervals[Left][0];
        ret[len][1] = max;
        len++;
        Left = Right;
        max = intervals[Left][1];
        Right++;
    }
    ret[len] = malloc(sizeof(int) * 2);
    ret[len][0] = intervals[Left][0];
    ret[len][1] = max;
    *returnSize = ++len;
    *returnColumnSizes = intervalsColSize;

    return ret;
}