//210730二叉树寻路
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
void swap(int* a, int* b) {
    int t = *a;
    *a = *b, *b = t;
}

void reverse(int* arr, int left, int right) {
    while (left < right) {
        swap(&arr[left], &arr[right]);
        left++, right--;
    }
}

int getReverse(int label, int row) {    //偶数行进行标记翻转
    return (1 << row - 1) + (1 << row) - 1 - label;
}

int* pathInZigZagTree(int label, int* returnSize) {
    int row = 1;    //行数
    int rowStart = 1;
    while (rowStart * 2 <= label) {
        row++;
        rowStart *= 2;
    }
    if (row % 2 == 0) {
        label = getReverse(label, row);
    }
    int* path = malloc(sizeof(int) * 20);
    *returnSize = 0;
    while (row > 0) {
        if (row % 2 == 0) { //偶数行，节点标号需进行翻转操作
            path[(*returnSize)++] = getReverse(label, row);
        } else {
            path[(*returnSize)++] = label;
        }
        row--;
        label >>= 1;    //父节点标号为label/2
    }
    reverse(path, 0, *returnSize - 1);
    return path;
}
