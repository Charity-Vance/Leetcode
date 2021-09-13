/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int count_number(int *arr,int arrSize){
    int count=0;
    for (int i=0;i<arrSize;i++){
        if (arr[i]==1)
            count++;
        else
            break;
    }
    return count;
}
int comp(const void *a,const void *b){
    return *(int*)a - *(int*)b;
}

int* kWeakestRows(int** mat, int matSize, int* matColSize, int k, int* returnSize){
    int *soldiers;
    *returnSize = k;
    soldiers = (int*)malloc(sizeof(int)*matSize);
    for (int i=0;i<matSize;i++){
        soldiers[i] = count_number(mat[i],matColSize[i])*matSize + i;
    }
    qsort(soldiers,matSize,sizeof(int),comp);
    for (int i=0;i<matSize;i++){
        soldiers[i] = soldiers[i]%matSize;
    }
    return soldiers;
}

作者：p781709996
链接：https://leetcode-cn.com/problems/the-k-weakest-rows-in-a-matrix/solution/shuang-bai-fang-zhen-cyu-yan-ban-by-p781709996/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。