# LeetCode 3020 - Find the Maximum Number of Elements in Subset

## Problem

You are given an integer array `nums`.

Select a subset of elements such that it forms the sequence:

```
x, x², x⁴, x⁸, ...,x^(k/2), x^k, x^(k/2), ..., x⁴, x², x
```

where:

- Every element except the last must appear **at least twice** in `nums`.
- The last element appears **exactly once**.
- Return the maximum possible length of such a subset.

---

## Constraints

- `2 <= nums.length <= 10^5`
- `1 <= nums[i] <= 10^9`

---

# Approach

## Observation 1

The only possible chain starting from a number `x` is

```
x → x² → x⁴ → x⁸ → ...
```

There is no choice once the starting number is fixed.

---

## Observation 2

For every element except the last one, we need **two copies**.

Hence,

- if a number appears at least twice, it contributes **2** to the answer.
- the last number contributes **1**.

---

## Special Case: `1`

Since

```
1² = 1
```

the chain never changes.

Therefore,

- if frequency of `1` is odd, all occurrences can be used.
- otherwise one occurrence must be discarded.

Example:

```
freq(1) = 7  -> answer = 7
freq(1) = 6  -> answer = 5
```

---

## Algorithm

1. Count the frequency of every number using a hash map.
2. Handle the special case of `1`.
3. For every distinct number except `1`:
   - repeatedly square the current value.
   - while its frequency is at least `2`, add `2` to the answer.
   - when the chain ends,
     - if the current value exists exactly once, add `1`
     - otherwise remove one from the length because the previous number cannot be the last element.
4. Return the maximum length obtained.

---

## Time Complexity

Let `k` be the number of distinct values.

Each chain grows as

```
x → x² → x⁴ → ...
```

which increases extremely fast.

Therefore each chain has at most

```
O(log log 10^9)
```

steps.

Overall complexity:

```
O(n + k log log 10^9) but as log log 10⁹ ≈ 5. So, k log log 10^9 ≈ 5k ≈ 5n (as k<=n)
So, O(n + 5n) ≈ O(n)
```

which is effectively

```
O(n)
```

---

## Space Complexity

```
O(k)
```

where `k` is the number of distinct elements.

---

# C++ Solution

```cpp
class Solution {
public:
    int maximumLength(vector<int>& nums) {
        unordered_map<int,int> mpp;

        for (auto it : nums)
            ++mpp[it];

        int maxlen = 1;

        // Special handling for value 1
        if (mpp.count(1)) {
            if (mpp[1] & 1)
                maxlen = max(maxlen, mpp[1]);
            else
                maxlen = max(maxlen, mpp[1] - 1);
        }

        for (auto it : mpp) {
            long long val = it.first;

            if (val == 1)
                continue;

            int len = 0;

            while (val <= 1000000000LL &&
                   mpp.count(val) &&
                   mpp[val] >= 2) {

                len += 2;
                val = val * val;
            }

            if (val <= 1000000000LL &&
                mpp.count(val) &&
                mpp[val] == 1)
                len += 1;
            else
                len -= 1;

            maxlen = max(maxlen, len);
        }

        return maxlen;
    }
};
```