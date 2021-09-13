/**
 * Note: The returned array must be malloced, assume caller calls free().
 异或（XOR ^ 不同为1）
 */    
int* decode(int* encoded, int encodedSize, int* returnSize){
    int total = 0;
    int odd = 0;
    int i;
    int n = encodedSize + 1;
    int *perm = (int *)malloc(sizeof(int *) * n);

    * returnSize = n;
    for( i=1; i<=n; i++)   /*先计算所有正整数异或的值*/
    {
        total ^= i;
    }
    for( i=1; i<encodedSize; i += 2 )      /*计算除perm[0]外异或的值*/
    {
        odd ^= encoded[i];
    }
    perm[0] = total ^ odd;        /*算出perm[0]的值*/
    for( i=0; i<encodedSize; i++ )
    {
        perm[i+1] = perm[i] ^ encoded[i];
    }
    return perm;
}