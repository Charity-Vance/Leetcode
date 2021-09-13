/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
/*
*排序思路加哈希结构表
*首先将单词进行排序，让他们相同的单词放在一起
*然后将单词存入结构表，在按他们出现的次数进行排序
*最后将排好序的单词依次拷贝到输出数组
*/
//结构体啊结构体
typedef struct Hash{
    char *str;
    int count;
}hash;
//按单词字典排序
int cmp_dictionary(const void *word1, const void *word2){
    return strcmp(*(char **)word1, *(char **)word2);
}
//按出现次数排序
int cmp(const void *word1, const void *word2){
    hash *temp1 = (hash *)word1;
    hash *temp2 = (hash *)word2;
    if(temp1->count == temp2->count)
        return strcmp(temp2->str, temp1->str);
    return temp1->count - temp2->count;
}

char ** topKFrequent(char ** words, int wordsSize, int k, int* returnSize){
    char **res = malloc(sizeof(char *)*k); //返回字符数组
//step1：构建结构体数组
    int index = 0; ; hash *hashb = malloc(sizeof(hash)*wordsSize);
    memset(hashb, 0, sizeof(hash)*wordsSize);

//step2：排啊排，第一次排序，按单词字典排序
    qsort(words, wordsSize, sizeof(words[0]), cmp_dictionary);
    //排好序了存起来呀，将单词存入结构体数组
    for(int i=0; i<wordsSize; index++){
        int j=i+1;
        hashb[index].str = words[i];
        hashb[index].count = 1;
        while(j < wordsSize && !strcmp(words[i], words[j])){
            j++; hashb[index].count++;
        }
        i = j;
    }
//step3：排啊排，第二次排序，按出现次数排序
    qsort(hashb, index, sizeof(hashb[0]), cmp);

//step4：完工，进行输出拷贝
    for(int i=0; i<k; i++){
        res[i] = malloc((strlen(hashb[--index].str)+1) * sizeof(char));
        strcpy(res[i], hashb[index].str);
    }
    free(hashb);
    *returnSize = k;
    return res;
}

作者：mei-z0
链接：https://leetcode-cn.com/problems/top-k-frequent-words/solution/pai-xu-ya-pai-xu-by-mei-z0-izqp/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。