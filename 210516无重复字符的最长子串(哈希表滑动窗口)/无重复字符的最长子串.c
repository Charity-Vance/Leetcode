struct HashTable {
    int key;
    char val;
    UT_hash_handle hh;
};

int lengthOfLongestSubstring(char * s)
{
    char *target = s;
    char strDes[50];
    struct HashTable* hashTable = NULL;
    struct HashTable* tmp;
    int i=0, x = 0, j=0, maxnum=0;

    while( i<strlen(s) )
    {
        HASH_FIND_INT(hashTable, &s[i], tmp);
        if( tmp == NULL )   //哈希表中没有找到该值
        {
            tmp = malloc(sizeof(struct HashTable));
            tmp->key = i;
            tmp->val = s[i];
            HASH_ADD_INT(hashTable, key, tmp);
            target[j] = s[i];
            i++;    
            j++;
            maxnum = maxnum > j ? maxnum : j;
        }
        else
        {
            tmp = malloc(sizeof(struct HashTable));
            tmp->key = i;
            tmp->val = s[i];
            HASH_ADD_INT(hashTable, key, tmp);
            i = tmp->key + 1;
            // if( maxnum < j )
            // {
            //     strcpy( strDes, target );
            //     strDes[j] = '\0';
            // }
            j = 0;
        }
    }
    return maxnum;
}