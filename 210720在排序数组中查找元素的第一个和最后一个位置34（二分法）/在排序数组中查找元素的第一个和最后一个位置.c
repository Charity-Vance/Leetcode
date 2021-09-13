/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int* searchRange(int* nums, int numsSize, int target, int* returnSize){

    int *res = (int *)malloc(sizeof(int *) * 2);
    int n = numsSize, l, r, mid, t_loc;

    *returnSize = 1;
    // if( nums[0] == target ){
    //     res[0] = target;
    // }
    // if( nums[n-1] == target ){
    //     res[1] = target;
    // }
    if( nums[0] == target || nums[n-1] == target ){
        res[0] = target;
        res[1] = target;
    }
    l = 0;  r = n-1;
    while( l <= r ){
        t_loc = ( l + r )/2;
        if( nums[t_loc] == target )
            break;
        if( nums[t_loc] < target )
            l = t_loc + 1;
        if( nums[t_loc] > target )
            r = t_loc - 1;
    }
    if( l > r ){
        res[0] = -1;
        res[1] = -1;
        return res;
    }
    l = 0;  r = n-1;
    while( l <= t_loc ){
        if( nums[0] == target ){
            res[0] = target;
            break;
        }
        mid = ( l + t_loc )/2;
        if( nums[mid] == target && nums[mid-1] < target ){
            res[0] = mid;
            break;
        }
        else if( nums[mid] == target )
            r = mid - 1;
        else
            l = mid + 1;
    }
    l = 0;  r = n-1;
    while( t_loc <= r ){
        if( nums[n-1] == target ){
            res[n-1] = target;
            break;
        }
        mid = ( r + t_loc )/2;
        if( nums[mid] == target && nums[mid-1] > target ){
            res[1] = mid;
            break;
        }
        else if( nums[mid] == target )
            l = mid + 1; 
        else
            r = mid - 1;       
    }   
    return res; 
}