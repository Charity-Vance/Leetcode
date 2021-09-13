int search(int* nums, int numsSize, int target){
    int l, r, mid;
    int i, n;

    l = 0;
    n = numsSize;
    r = n - 1;

    if (n == 0) {
        return -1;
    }
    if (n == 1) {
        return nums[0] == target ? 0 : -1;
    }

    while( l <= r ){
        mid = ( l + r )/2;

        if( nums[mid] == target )
            return mid;
        if (nums[0] <= nums[mid]) {
            if (nums[0] <= target && target < nums[mid]) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        } else {
            if (nums[mid] < target && target <= nums[n - 1]) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
    }
    return -1;
}
