#include<bits/stdc++.h>
using namespace std;

//type 1: Constant Window ---->
//  MAX SUM OF SUBARRAY OF LENGTH EXACTLY K
int sumSubarrayLengthEqualto_K(vector<int>&nums, int k){
    int r = 0, l = 0, sum = 0, maxsum = 0;
    while(r < nums.size()){
        sum = sum + nums[r];
        if((r-l+1) > k){
            sum = sum - nums[l];
            l++;
        }

        if((r-l+1) == k) maxsum = max(sum,maxsum);
        r++;
    }
    return maxsum;
}


//type 2: Longest Substring

int longestSubstring(vector<int>&nums,int k){
    int r = 0, l = 0, len = 0, maxlen = 0;
    while(r < nums.size()){
        //update the required variable with nums[r];
        if(<condition to shrink>){ // we didnot use WHILE LOOP because we are asked longest string so no need to decrease the length
            // perform shrink properly
            l++;
        }

        if(<condition to update the maxlen>) maxlen = max(maxlen,len);
        r++;
    }
    return maxlen;
}

//type 3: Number of substring with <condition>

int numberOfSubstring(vector<int>&nums, int val){
    int r = 0, l = 0;
    int cnt = 0;
    while(r < nums.size()){
        //update the variable whichever needed with nums[r];

        while(<condition to shrink>){
            //have to use while cz we are counting the number of substring not the max length
            if(<condition>) //do whatever needed;
            l++;
        }

        if(<favourable condition>){
            // upfate the cnt variable
        }
        r++;
    }
    return cnt;
}