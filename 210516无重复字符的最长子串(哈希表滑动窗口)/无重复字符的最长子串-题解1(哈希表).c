int lengthOfLongestSubstring(char * s) {
    char hash[128] = {0};
    int start = 0;
    int len = strlen(s);
    int max = 0;
    for (int i = 0; i < len; i++) 
    {
        hash[s[i]]++;           //右窗口右移
        while (hash[s[i]] > 1)  //右窗口在哈希表中已有值
        {
            hash[s[start]]--;   //左窗口的值从哈希表中删除
            start++;            //左窗口右移
        }
        max = fmax(max, i - start + 1);
    }
    return max;
}
