int countTriplets(int* arr, int arrSize) {
    int n = arrSize;
    int s[n + 1];
    s[0] = 0;
    for (int i = 0; i < n; ++i) {
        s[i + 1] = s[i] ^ arr[i];
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int k = i + 1; k < n; ++k) {
            if (s[i] == s[k + 1]) {
                ans += k - i;
            }
        }
    }
    return ans;
}
