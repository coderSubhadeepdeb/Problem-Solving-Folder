# Maximum Total Subarray Value 1( Leetcode 3689)

## Problem Statement
You are given an integer array nums of length n and an integer k.

You need to choose exactly k non-empty subarrays nums[l..r] of nums. Subarrays may overlap, and the exact same subarray (same l and r) can be chosen more than once.

The value of a subarray nums[l..r] is defined as: max(nums[l..r]) - min(nums[l..r]).

The total value is the sum of the values of all chosen subarrays.

Return the maximum possible total value you can achieve.

## Key Observations

- We can choose the same subarray multiple times.
- `The whole Array` will contain the `Max Element` and `Min Element` as every sub array is part of the whole array. 

## Approach

Just find the `MAX_ELEMENT` and the `MIN_ELEMENT` for the whole array and multiply their difference with `k` i.e `"k * (MAX_ELEMENT - MIN_ELEMENT)"`

## Complexity Analysis

- Time Complexity: `O(n)`--> for one traversal to find the maxi and mini
- Space Complexity: `O(1)`

## Code( C++)

```cpp
class Solution {
public:
    long long maxTotalValue(vector<int>& nums, int k) {
        long long mini = (long long)*min_element(nums.begin(),nums.end()); 
        long long maxi = (long long)*max_element(nums.begin(),nums.end()); 
        return (long long)k*(maxi-mini);
    }
};