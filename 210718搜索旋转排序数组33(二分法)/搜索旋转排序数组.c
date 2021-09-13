int search(int* nums, int numsSize, int target){
    int left, right, mid;
    int i;

    left = 0;
    right = numsSize - 1;

    while( left < right ){
        if( nums[left] == target )
            return left;
        if( nums[right] == target )
            return right;

        mid = ( left + right )/2;
        if( (nums[target] > nums[mid] && nums[target] < nums[right]) 
            || (target > nums[right] && nums[mid] > nums[right]) ){
            left = mid;
        }
        if( (nums[target] > nums[left] && nums[target] < nums[mid]) 
            || (target > nums[left] && nums[mid] > nums[left]) ){
            left = mid;
        }
    }
    if( nums[left] = target )
        return left;
    return -1;
}