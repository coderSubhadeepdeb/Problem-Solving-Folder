# LeetCode 3312 - Sorted GCD Pair Queries

## Idea

The brute force approach is to generate the GCD of every pair, sort them, and answer the queries.

If `n = 10^5`, the number of pairs is

\[
\frac{n(n-1)}{2} \approx 5\times10^9
\]

which is impossible to generate.

So instead of finding the GCD of every pair, we solve the reverse problem:

> **For every possible GCD `g`, count how many pairs have GCD exactly equal to `g`.**

Once we know that, we can answer every query without constructing the actual sorted GCD array.

---

# Step 1 - Count frequency of every number

Initially,

```cpp
for(auto num : nums)
    exactGcd[num]++;
```

Here,

```text
exactGcd[x]
```

stores

> frequency of number `x`.

Example

```text
nums = [2,4,6,8]
```

After this loop

| Number | Frequency |
|---------|----------:|
|1|0|
|2|1|
|3|0|
|4|1|
|5|0|
|6|1|
|7|0|
|8|1|

---

# Step 2 - Count how many numbers are divisible by every `g`

```cpp
for(int i = 1; i <= maxi; i++){
    for(int j = i * 2; j <= maxi; j += i){
        exactGcd[i] += exactGcd[j];
    }
}
```

This is the key observation.

Instead of asking

> "How many numbers are equal to `g`?"

we ask

> "How many numbers are divisible by `g`?"

Suppose

```text
nums = [2,4,6,8]
```

For

```text
g = 2
```

the multiples are

```text
2
4
6
8
```

All of them contribute.

So

```text
exactGcd[2] = 4
```

For

```text
g = 4
```

multiples are

```text
4
8
```

Therefore

```text
exactGcd[4] = 2
```

After this loop,

```text
exactGcd[g]
```

means

> Number of elements divisible by `g`.

---

# Step 3 - Count every possible pair

Now we know how many numbers are divisible by every `g`.

If

```text
cnt = exactGcd[g]
```

then the number of pairs that can be formed is

\[
\binom{cnt}{2}
=
\frac{cnt(cnt-1)}{2}
\]

Code

```cpp
for(int i = 1; i <= maxi; i++){
    exactGcd[i] = (exactGcd[i] * (exactGcd[i] - 1)) / 2;
}
```

Example

If

```text
exactGcd[2] = 4
```

then

```text
Pairs = 4C2 = 6
```

But notice carefully...

These are **NOT** necessarily pairs whose GCD is exactly `2`.

These are pairs whose GCD is

- 2
- 4
- 6
- 8
- ...

because every pair is divisible by 2.

So we still have to remove the pairs whose GCD is actually a larger multiple of 2.

---

# Step 4 - Inclusion Exclusion

This is the most important part of the solution.

```cpp
for (int i = maxi; i >= 1; i--) {
    for (int j = i * 2; j <= maxi; j += i) {
        exactGcd[i] -= exactGcd[j];
    }
}
```

Initially,

```text
exactGcd[i]
```

contains

> Number of pairs where **both numbers are divisible by `i`**.

This includes pairs having GCD

```text
i
2i
3i
4i
...
```

To get only

```text
GCD == i
```

we subtract every multiple.

Mathematically,

\[
Exact(i)
=
PairsDivisibleBy(i)
-
Exact(2i)
-
Exact(3i)
-
Exact(4i)
-
...
\]

This works because we process from

```text
max -> 1
```

so every larger multiple has already been computed.

---

# Example

Suppose

```text
nums = [2,4,8]
```

For

```text
g = 2
```

Numbers divisible by 2

```text
2
4
8
```

Total pairs

```text
3C2 = 3
```

Pairs are

```text
(2,4) -> gcd 2

(2,8) -> gcd 2

(4,8) -> gcd 4
```

Initially

```text
exactGcd[2] = 3
```

After subtracting

```text
exactGcd[4] = 1
```

we get

```text
exactGcd[2] = 2
```

which is correct.

---

# Step 5 - Prefix Sum

```cpp
for(int i = 1; i <= maxi; i++)
    exactGcd[i] += exactGcd[i - 1];
```

Now

```text
exactGcd[i]
```

means

> Number of pairs having

```text
GCD <= i
```

Example

Suppose

| GCD | Count |
|----:|------:|
|1|5|
|2|3|
|3|2|
|4|4|

After prefix

| GCD | Prefix |
|----:|-------:|
|1|5|
|2|8|
|3|10|
|4|14|

Meaning

Indices

```text
0-4  -> gcd = 1

5-7  -> gcd = 2

8-9  -> gcd = 3

10-13 -> gcd = 4
```

We never build

```text
[1,1,1,1,1,2,2,2,3,3,4,4,4,4]
```

The prefix array stores all necessary information.

---

# Step 6 - Answer Queries

```cpp
int pos = upper_bound(exactGcd.begin(), exactGcd.end(), query) - exactGcd.begin();
```

Suppose

```text
Prefix

0
5
8
10
14
```

Query

```text
7
```

We need the first prefix greater than 7.

```
5   ❌

8   ✅
```

Answer

```text
2
```

because index 7 lies in the GCD = 2 block.

This is exactly what

```cpp
upper_bound()
```

returns.

---

# Why `upper_bound` instead of `lower_bound`?

Suppose

```text
Prefix

5
8
10
```

Query = 5

Index 5 belongs to GCD = 2, not GCD = 1.

```
Indices

0 1 2 3 4 -> GCD = 1

5 6 7     -> GCD = 2
```

`upper_bound(5)` returns `8`, whose index corresponds to GCD = 2.

`lower_bound(5)` would incorrectly point to GCD = 1.

Hence we use **upper_bound**.

---

# Dry Run

Input

```text
nums = [2,4,6]
```

### Frequency

```text
2 -> 1

4 -> 1

6 -> 1
```

---

### Numbers divisible by every value

|g|Count|
|--:|----:|
|1|3|
|2|3|
|3|1|
|4|1|
|5|0|
|6|1|

---

### Total pairs

|g|Pairs|
|--:|----:|
|1|3|
|2|3|
|3|0|
|4|0|
|5|0|
|6|0|

---

### Inclusion Exclusion

|g|Exact GCD Pairs|
|--:|-------------:|
|1|0|
|2|3|
|3|0|
|4|0|
|5|0|
|6|0|

---

### Prefix

|g|Prefix|
|--:|-----:|
|1|0|
|2|3|
|3|3|
|4|3|
|5|3|
|6|3|

Queries

```text
0
1
2
```

All belong to

```text
GCD = 2
```

Output

```text
[2,2,2]
```

---

# Complexity Analysis

Let

- `n = nums.size()`
- `M = max(nums)`

### Time Complexity

Building frequency

\[
O(n)
\]

Counting divisible numbers

\[
O(M\log M)
\]

Inclusion-Exclusion

\[
O(M\log M)
\]

Each query

\[
O(\log M)
\]

Overall

\[
O(n + M\log M + q\log M)
\]

---

### Space Complexity

Frequency / exact GCD array

\[
O(M)
\]

---

# Key Takeaways

- Never generate all GCD pairs.
- Count **how many numbers are divisible by each divisor**.
- Compute all possible pairs using `nC2`.
- Use **Inclusion-Exclusion** to obtain the count of pairs having **GCD exactly equal to `g`**.
- Convert the counts into a prefix sum to represent the sorted GCD array implicitly.
- Use `upper_bound()` to answer each query in `O(log M)` without ever constructing the actual sorted array.

---

# Complete C++ Solution

```cpp
class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int maxi = *max_element(nums.begin(), nums.end());
        vector<long long> exactGcd(maxi + 1, 0);

        // Frequency of each number
        for (auto num : nums) {
            exactGcd[num]++;
        }

        // Count how many numbers are divisible by every possible gcd
        for (int i = 1; i <= maxi; i++) {
            for (int j = i * 2; j <= maxi; j += i) {
                exactGcd[i] += exactGcd[j];
            }
        }

        // Count total pairs divisible by each gcd
        for (int i = 1; i <= maxi; i++) {
            exactGcd[i] = (exactGcd[i] * (exactGcd[i] - 1)) / 2;
        }

        // Inclusion-Exclusion:
        // Remove pairs whose gcd is a multiple of the current gcd
        for (int i = maxi; i >= 1; i--) {
            for (int j = i * 2; j <= maxi; j += i) {
                exactGcd[i] -= exactGcd[j];
            }
        }

        // Prefix sum:
        // exactGcd[i] = number of pairs having gcd <= i
        for (int i = 1; i <= maxi; i++) {
            exactGcd[i] += exactGcd[i - 1];
        }

        vector<int> ans;

        for (auto query : queries) {
            int pos = upper_bound(exactGcd.begin(), exactGcd.end(), query) - exactGcd.begin();
            ans.push_back(pos);
        }

        return ans;
    }
};
```