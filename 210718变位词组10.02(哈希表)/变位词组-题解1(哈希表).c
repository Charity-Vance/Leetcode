/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
typedef struct Data
{
    char* key;//键值
    char* value;//字符串
    struct Data* next;
}*List;//数据项

typedef struct
{
    List* infos;
    int tableSize;//哈希表容量
}HashNode;

typedef HashNode* HashTable;//哈希表

int cmp(const void*a,const void* b)//按升序排列字符
{
    return (*(char*)a-*(char*)b);
}

int hash(char* key,int tableSize)//计算哈希值，除留余数法
{
    int index=0;
    for(int i=0;key[i]!='\0';i++)
    {
        index=index*33+key[i];//33怎么来的？瞎写的，取大一点哈希冲突概率低
        index=index%tableSize;//避免溢出
    }
    return index;
}

void insert(char* str,HashTable ht)//插入数据
{
    int len=strlen(str);
    char* key=(char*)malloc(sizeof(char)*(len+1));
    strcpy(key,str);
    //让排序好的字符串做键值
    qsort(key,len,sizeof(char),cmp);
    int index=hash(key,ht->tableSize);//获取哈希值

    if(ht->infos[index]==NULL)//当前位置没有数据
    {
        ht->infos[index]=(List)calloc(1,sizeof(struct Data));
        ht->infos[index]->key=(char*)malloc(sizeof(char)*(len+1));
        ht->infos[index]->value=(char*)malloc(sizeof(char)*(len+1));
        strcpy(ht->infos[index]->key,key);
        strcpy(ht->infos[index]->value,str);
    }
    else//当前位置有数据
    {
        if(strcmp(ht->infos[index]->key,key)==0)//如果键值相等
        {

            List p=ht->infos[index];
            while(p->next)//同理
                p=p->next;
            p->next=(List)calloc(1,sizeof(struct Data));
            p->next->key=(char*)malloc(sizeof(char)*(len+1));
            p->next->value=(char*)malloc(sizeof(char)*(len+1));
            strcpy(p->next->key,key);
            strcpy(p->next->value,str);
        }
        else//发生哈希冲突
        {
            while(ht->infos[index]!=NULL&&strcmp(ht->infos[index]->key,key)!=0)//线性探测
            {
                index++;
                index%=ht->tableSize;
            }
            if(ht->infos[index]==NULL)//说明遇到空位置，把数据插进去
            {
                ht->infos[index]=(List)calloc(1,sizeof(struct Data));
                ht->infos[index]->key=(char*)malloc(sizeof(char)*(len+1));
                ht->infos[index]->value=(char*)malloc(sizeof(char)*(len+1));
                strcpy(ht->infos[index]->key,key);
                strcpy(ht->infos[index]->value,str);
            }
            else//这是个坑，此时的index指向的元素的键值与key都和index改变前指向的元素的键值发生了哈希冲突
            {   //有点绕，比如说之前表里有个"abc"，然后插入了个"bcd"，然后发生了哈希冲突（我瞎算的），
                //然后通过线性探测法使得"bcd"指向了表后面的某个位置，现在遇到了个数据"dcb"，
                //显然也和"abc"发生冲突，因为其和"bcd"要放在同一个位置，所以我们不能向后找新的位置插入前者
                List p=ht->infos[index];
                while(p->next)
                    p=p->next;
                p->next=(List)calloc(1,sizeof(struct Data));
                p->next->key=(char*)malloc(sizeof(char)*(len+1));
                p->next->value=(char*)malloc(sizeof(char)*(len+1));
                strcpy(p->next->key,key);
                strcpy(p->next->value,str);   
            }
        }
    }
}


char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes){
    char*** res=(char***)calloc(10000,sizeof(char**));//开10000是我怕它不够用
    *returnColumnSizes=(int*)calloc(10000,sizeof(int));
    HashTable ht=(HashTable)calloc(1,sizeof(HashNode));
    ht->infos=(List*)calloc(10000,sizeof(List));
    ht->tableSize=10000;
    *returnSize=0;
    for(int i=0;i<strsSize;i++)//将字符串插入表中
        insert(strs[i],ht);
    for(int i=0;i<ht->tableSize;i++)
    {
        if(ht->infos[i]!=NULL)//遍历表，取出数据
        {
           List p=ht->infos[i];
           List q=p;
           while(q)//获取相同键值的字符串长度
           {
                q=q->next;
                (*returnColumnSizes)[*returnSize]++;
           }
           res[*returnSize]=(char**)calloc((*returnColumnSizes)[*returnSize],sizeof(char*));
           int j=0;
           while(p)//把字符串放进结果矩阵中
           {
               int len=strlen(p->key);
               res[*returnSize][j]=(char*)malloc(sizeof(char)*(len+1));
               strcpy(res[*returnSize][j],p->value);
               j++;
               p=p->next;
           }
           (*returnSize)++;
        }
    }
    return res;
}

作者：mrggls-t
链接：https://leetcode-cn.com/problems/group-anagrams-lcci/solution/zhen-nan-ren-du-zhi-jie-qiang-xie-ha-xi-biao-by-mr/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。