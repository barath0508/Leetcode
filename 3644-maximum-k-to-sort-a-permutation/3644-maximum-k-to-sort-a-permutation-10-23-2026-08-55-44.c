int sortPermutation(int* nums, int numsSize) {
    int ans=-1;
    bool misplaced=false;
    for(int i=0;i<numsSize;i++){
        if(nums[i]!=i){
            ans&=nums[i];
            misplaced=true;
        }

    }
    return misplaced ? ans: 0; 
    
}