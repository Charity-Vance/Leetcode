/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
 

int count;

void dfs(int* nums,int numsSize,int depth,int* cur,bool* used,int** res){
    if(depth==numsSize){
        res[count]=(int*)malloc(numsSize*sizeof(int));
        memcpy(res[count++],cur,numsSize*sizeof(int));
        return;
    }

    for(int i=0;i<numsSize;++i){
        if(used[i]==true) continue;
        cur[depth]=nums[i];
        used[i]=true;
        //++depth;

        dfs(nums,numsSize,depth+1,cur,used,res);
        
        //--depth;
        used[i]=false;
    }
}

int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    int s=1;
    for(int i=1;i<=numsSize;++i) s*=i;
    int** res=(int**)malloc(s*sizeof(int*));

    bool* used=(bool*)malloc(numsSize*sizeof(bool));
    memset(used,0,numsSize*sizeof(bool));

    int* cur=(int*)malloc(numsSize*sizeof(int));

    count=0;
    dfs(nums,numsSize,0,cur,used,res);
    
    *returnSize=s;
    *returnColumnSizes=(int*)malloc(s*sizeof(int));
    for(int i=0;i<s;++i) (*returnColumnSizes)[i]=numsSize;

    return res;
}

作者：goner
链接：https://leetcode-cn.com/problems/permutations/solution/46quan-pai-lie-ti-jie-by-goner/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。