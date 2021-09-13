int majorityElement(int* nums, int numsSize){
    int i=1,count=1,major=nums[0];
    for(;i<numsSize;i++)
    {
        if(count==0)
        {
            count++;
            major=nums[i];
        }
        else if(major==nums[i])
            count++;
        else
            count--;
    }
    return major;
}