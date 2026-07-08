# Intuition

For every query `[l, r]`, we need to:

1. Remove all `'0'` characters from the substring `s[l...r]`.
2. Form the number using the remaining digits.
3. Compute the sum of those remaining digits.
4. Return `(number × sum) mod (10^9 + 7)`.

Doing this independently for every query would require scanning the entire substring, leading to **O(N × Q)** complexity, which is too slow.

Instead, we preprocess prefix information so that each query can be answered in **O(1)**.

---

# Approach

## 1. Prefix Number

Traverse the string from left to right.

Whenever the current character is non-zero:

```text
number = number × 10 + digit
```

This constructs the number formed by all non-zero digits seen so far.

Store this value in:

```cpp
numbers[i]
```

So,

```text
numbers[i]
= number formed by all non-zero digits in s[0...i]
```

---

## 2. Prefix Digit Sum

Maintain the sum of all non-zero digits.

```cpp
prefSum[i]
```

stores the sum of all non-zero digits up to index `i`.

---

## 3. Prefix Count of Non-Zero Digits

Maintain how many non-zero digits have appeared.

```cpp
lenOfNonZeroDig[i]
```

stores the count of non-zero digits in `s[0...i]`.

This allows us to know how many digits belong to any queried substring.

---

## 4. Powers of 10

Precompute

```cpp
10^0
10^1
10^2
...
```

modulo `MOD`.

This is needed while removing the prefix number.

---

# Answering a Query

Suppose the query is

```text
[l, r]
```

### Step 1

Find the number of non-zero digits inside the substring.

```text
k =
lenOfNonZeroDig[r]
-
lenOfNonZeroDig[l-1]
```

---

### Step 2

Let

```text
P = number formed before index l
```

To remove this prefix from the complete prefix number, shift it left by `k` digits.

```text
P × 10^k
```

Therefore,

```text
number =
numbers[r]
-
numbers[l-1] × 10^k
```

Everything is computed modulo `MOD`.

---

### Step 3

Digit sum is simply

```text
prefSum[r]
-
prefSum[l-1]
```

---

### Step 4

Return

```text
(number × sum) mod MOD
```

---

# Correctness Proof

We prove that the algorithm correctly answers every query.

### Lemma 1

`numbers[i]` equals the number formed by concatenating every non-zero digit in `s[0...i]`.

**Proof**

Initially the number is 0.

Whenever a non-zero digit `d` is encountered, we perform

```text
number = number × 10 + d
```

which appends `d` to the previously formed number.

Zeros are skipped entirely.

Hence after processing index `i`, `numbers[i]` is exactly the required number.

---

### Lemma 2

`prefSum[i]` equals the sum of every non-zero digit in `s[0...i]`.

**Proof**

Each non-zero digit is added exactly once while zeros are ignored.

Therefore the prefix sum is correct.

---

### Lemma 3

`lenOfNonZeroDig[i]` equals the number of non-zero digits in `s[0...i]`.

**Proof**

The counter is increased exactly when a non-zero digit is encountered.

Hence it stores the correct count.

---

### Lemma 4

For a query `[l, r]`, the reconstructed number equals the number formed by all non-zero digits inside the substring.

**Proof**

Let

```text
A = number formed before index l
B = number formed inside [l,r]
```

Then

```text
numbers[r]
=
A × 10^k + B
```

where `k` is the number of non-zero digits in `[l,r]`.

Therefore

```text
B
=
numbers[r]
-
A × 10^k
```

which is exactly the expression used in the algorithm.

Thus the reconstructed number is correct.

---

Since both the reconstructed number and digit sum are correct, their product is also correct.

Hence every query is answered correctly.

---

# Complexity Analysis

Let

- `N = s.length()`
- `Q = queries.size()`

### Preprocessing

Each array is computed once.

```text
Time: O(N)
```

---

### Each Query

Every query performs only constant-time operations.

```text
Time: O(1)
```

---

### Overall

```text
Time: O(N + Q)
```

```text
Space: O(N)
```

---

# C++ Code

```cpp
class Solution {
public:
    const int MOD = 1e9 + 7;

    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        int n = s.length();

        vector<long long> numbers(n);
        vector<long long> prefSum(n);
        vector<long long> lenOfNonZeroDig(n);
        vector<long long> pow10(n + 1, 1);

        long long num = 0;
        long long sum = 0;
        long long len = 0;

        for (int i = 0; i < n; i++) {
            if (s[i] != '0') {
                num = (num * 10 + (s[i] - '0')) % MOD;
                sum = (sum + (s[i] - '0')) % MOD;
                len++;
            }

            numbers[i] = num;
            prefSum[i] = sum;
            lenOfNonZeroDig[i] = len;
            pow10[i + 1] = (pow10[i] * 10) % MOD;
        }

        vector<int> ans;

        for (auto &q : queries) {
            int l = q[0];
            int r = q[1];

            int k = lenOfNonZeroDig[r] - (l == 0 ? 0 : lenOfNonZeroDig[l - 1]);
            long long number = (numbers[r] - ((l == 0 ? 0 : numbers[l - 1]) * pow10[k]) % MOD + MOD) % MOD; //This mod technique is very important
            long long digitSum = (prefSum[r] - (l == 0 ? 0 : prefSum[l - 1]) + MOD) % MOD;
            ans.push_back((int)((number * digitSum) % MOD));
        }

        return ans;
    }
};
```