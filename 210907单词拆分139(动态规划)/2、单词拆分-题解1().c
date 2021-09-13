bool wordBreak(char * s, char ** wordDict, int wordDictSize){
    int len = strlen(s);
    if (len && wordDictSize == 0) return false;
    int dp[len + 1], wordcolsize[wordDictSize];
    memset(dp, 0, sizeof(int) * (len + 1));
    for (int i = 0; i < wordDictSize; i++) wordcolsize[i] = strlen(wordDict[i]);
    dp[0] = 1;
    for (int i = 1; i <= len; i++) {
        for (int j = 0; j < wordDictSize; j++) {
            int k = i - 1 + wordcolsize[j];
            if (k > len) continue ;
            dp[k] = dp[k] || (dp[i - 1] && (strncmp(s + i - 1, wordDict[j], wordcolsize[j]) == 0));
        }
    }
    return dp[len];
}
