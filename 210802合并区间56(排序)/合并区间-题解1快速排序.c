/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#define MAX_N 10000

// 第一个元素从小到大排序；如果第一个元素相等，则根据第二个元素从小到大排序
int cmp(const void *arr1, const void *arr2) {
    int *ar1 = *(int **)arr1, *ar2 = *(int **)arr2;

    if (ar1[0] != ar2[0]) {
        return ar1[0] - ar2[0];
    }
    return ar1[1] - ar2[1];
}

int **merge(int **intervals, int intervalsSize, int *intervalsColSize, int *returnSize, int **returnColumnSizes)
{
    int i, j;
    int temp_cnt = 0;
    // 第一个元素从小到大排序；如果第一个元素相等，则根据第二个元素从小到大排序
    qsort(intervals, intervalsSize, sizeof(int *), cmp);

    // 定义返回值指针
    int **p = (int **)malloc(sizeof(int *) * MAX_N);
    if (p == NULL) {
        return NULL;
    }
    for (i = 0; i < MAX_N; i++) {
        p[i] = (int *)malloc(sizeof(int) * intervalsColSize[0]);
        if (p[i] == NULL) {
            return NULL;
        }
        memset(p[i], 0, sizeof(int) * intervalsColSize[0]);
    }

    // 先将第一个区间存入
    p[temp_cnt][0] = intervals[0][0];
    p[temp_cnt][1] = intervals[0][1];
    // 遍历将区间合并
    for (i = 1; i < intervalsSize; i++) {
        if (intervals[i][0] <= p[temp_cnt][1] && intervals[i][1] >= p[temp_cnt][1]) { // 当前区间起点小于合并区间终点，同时当前区间终点大于合并区间终点
            p[temp_cnt][1] = intervals[i][1];                                         // 更新合并区间终点
        } else if (intervals[i][0] > p[temp_cnt][1]) {                                // 当前区间起点大于合并区间终点
            (temp_cnt)++;                                                             // 重新开辟合并区间
            p[temp_cnt][0] = intervals[i][0];
            p[temp_cnt][1] = intervals[i][1];
        }
    }
    
    // 结果返回
    *returnSize = temp_cnt + 1;
    *returnColumnSizes = intervalsColSize;
    return p;
}

作者：yuxiaochen99
链接：https://leetcode-cn.com/problems/merge-intervals/solution/cqsortpai-xu-mo-ni-he-bing-qu-jian-by-yu-2yr6/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。