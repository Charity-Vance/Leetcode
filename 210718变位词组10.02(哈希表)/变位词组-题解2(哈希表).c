/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
struct mys{
    char *s;
    int index;
};
int cmp1(char *a,char *b){
    return (int)a[0]-(int)b[0];
}
int cmp2(struct mys *a,struct mys *b){
    return strcmp(a->s,b->s);
}
char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes){
    struct mys A[strsSize];
    for(int i=0;i<strsSize;i++){
        int len=strlen(strs[i]);
        A[i].s=malloc((len+1)*sizeof(char));
        strcpy(A[i].s,strs[i]);
        qsort(A[i].s,len,sizeof(char),cmp1);
        A[i].index=i;
    }
    qsort(A,strsSize,sizeof(struct mys),cmp2);
    char ***ret=malloc(strsSize*sizeof(char **));
    int *columnSizes=malloc(strsSize*sizeof(int));
    *returnSize=0;
    int i,j;
    for(i=0;i<strsSize;){
        for(j=i+1;j<strsSize && !(strcmp(A[i].s,A[j].s));j++);
        ret[(*returnSize)]=malloc((j-i)*sizeof(char *));
        columnSizes[(*returnSize)]=j-i;
        for(int k=i;k<j;k++){
            ret[(*returnSize)][k-i]=malloc((strlen(strs[A[k].index])+1)*sizeof(char));
            strcpy(ret[(*returnSize)][k-i],strs[A[k].index]);
        }
        (*returnSize)++;
        i=j;
    }
    *returnColumnSizes=columnSizes;
    return ret;
}