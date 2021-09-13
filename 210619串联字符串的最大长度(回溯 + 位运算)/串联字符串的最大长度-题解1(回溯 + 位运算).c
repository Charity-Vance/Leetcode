int ans;

void backtrack(int* masks, int masksSize, int pos, int mask) {
    if (pos == masksSize) {
        ans = fmax(ans, __builtin_popcount(mask));
        return;
    }
    if ((mask & masks[pos]) == 0) {  // mask 和 masks[pos] 无公共元素
        backtrack(masks, masksSize, pos + 1, mask | masks[pos]);
    }
    backtrack(masks, masksSize, pos + 1, mask);
}

int maxLength(char** arr, int arrSize) {
    ans = 0;
    int masks[arrSize];
    int masksSize = 0;
    for (int i = 0; i < arrSize; ++i) {
        int mask = 0;
        int len = strlen(arr[i]);
        for (int j = 0; j < len; ++j) {
            int ch = arr[i][j] - 'a';
            // 若 mask 已有 ch，则说明 s 含有重复字母，无法构成可行解
            if (((mask >> ch) & 1) != 0) {  
                mask = 0;
                break;
            }
            mask |= 1 << ch;  // 将 ch 加入 mask 中
        }
        if (mask > 0) {
            masks[masksSize++] = mask;
        }
    }

    backtrack(masks, masksSize, 0, 0);
    return ans;
}

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters/solution/chuan-lian-zi-fu-chuan-de-zui-da-chang-d-g6gk/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。