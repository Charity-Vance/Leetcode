/*输入: strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
输出: [["bat"],["nat","tan"],["ate","eat","tea"]]
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 10000
#define STRSIZE 1000

struct SortArray {
    int index;  //字符串在原数组的编号
    char str[STRSIZE];//存放字符串，可放1000个字节
};

int StrCompare(const void *a, const void *b)
{
    struct SortArray temp1 = *(struct SortArray *)a;
    struct SortArray temp2 = *(struct SortArray *)b;
    return strcmp(temp1.str, temp2.str);
}
int Cmp(const void *a, const void *b)
{
    return *(char *)a - *(char *)b;
}
char ***groupAnagrams(char **strs, int strsSize, int *returnSize, int **returnColumnSizes)
{
    *returnSize = 0;
    if ((strs == NULL) || (strsSize == 0)) {
        return NULL;
    }
    char ***ret = (char ***)malloc(sizeof(char **) * strsSize);
    *returnColumnSizes = (int *)malloc(sizeof(int) * MAXSIZE);
    struct SortArray *ans = (struct SortArray *)malloc(sizeof(struct SortArray) * strsSize);
    memset(ans, 0, sizeof(struct SortArray) * strsSize);
    int i, j;
    for (i = 0; i < strsSize; i++) {
        ans[i].index = i;
        strcpy(ans[i].str, strs[i]);
        qsort(ans[i].str, strlen(strs[i]), sizeof(ans[i].str[0]), Cmp);
    }
    qsort(ans, strsSize, sizeof(ans[0]), StrCompare);
    int left = 0;
    int right = 0;
    int index = 0;
    int curLen;
    while (right <= strsSize) {
        if ((right == strsSize) || (strcmp(ans[right].str, ans[left].str) != 0)) {
            curLen = right - left;
            ret[*returnSize] = (char **)malloc(sizeof(char *) * curLen);
            (*returnColumnSizes)[*returnSize] = curLen;
            index = 0;
            for (i = left; i < right; i++) {
                ret[*returnSize][index] = (char *)malloc(sizeof(char) * (strlen(ans[i].str) + 1));
                strcpy(ret[*returnSize][index], strs[ans[i].index]);
                index++;
            }
            (*returnSize)++;
            left = right;
        }
        right++;
    }
    return ret;
}

作者：codec-2
链接：https://leetcode-cn.com/problems/group-anagrams/solution/ke-yi-bu-yong-uthashzhi-jie-qsortshuang-zhi-zhen-x/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。