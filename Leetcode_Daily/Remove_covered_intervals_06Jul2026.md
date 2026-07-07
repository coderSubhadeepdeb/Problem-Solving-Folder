# Explanation of `removeCoveredIntervals`

## Code

```cpp
int removeCoveredIntervals(vector<vector<int>>& arr) {
    int n = arr.size();

    sort(arr.begin(), arr.end(), [](vector<int> v1, vector<int> v2) {
        if (v1[0] == v2[0]) return v1[1] > v2[1];
        return v1[0] < v2[0];
    });

    int r = arr[0][1];
    int cnt = 1;

    for (int i = 1; i < n; ++i) {
        if (r >= arr[i][1])
            continue;

        r = arr[i][1];
        cnt++;
    }

    return cnt;
}
```

---

# Intuition

A brute-force solution compares every interval with every other interval to check whether it is covered, resulting in **O(n²)** time complexity.

The key observation is that if we sort the intervals in a clever way, we can determine whether an interval is covered by looking only at the intervals that appeared before it.

This reduces the complexity to **O(n log n)**.

---

# Sorting

```cpp
sort(arr.begin(), arr.end(), [](vector<int> v1, vector<int> v2) {
    if (v1[0] == v2[0])
        return v1[1] > v2[1];
    return v1[0] < v2[0];
});
```

The intervals are sorted by:

1. **Starting point in ascending order**
2. **Ending point in descending order if the starting points are equal**

---

## Why sort by starting point?

An interval `[a, b)` can only be covered by an interval whose starting point is **less than or equal to** `a`.

After sorting by starting point,

```
previous.start <= current.start
```

is always true.

Therefore, we never need to check the left endpoint again.

---

## Why sort equal starting points by decreasing end?

Suppose we have

```
[1,4]
[1,7]
```

If we sort by increasing end:

```
[1,4]
[1,7]
```

we process the smaller interval first even though it is covered by the larger one.

Instead we sort as

```
[1,7]
[1,4]
```

Now the longest interval comes first.

Every later interval having the same starting point is automatically covered.

---

# Meaning of `r`

```cpp
int r = arr[0][1];
```

`r` stores the **maximum ending point** among all intervals that have been kept so far.

Think of `r` as the farthest right endpoint seen till now.

---

# Meaning of `cnt`

```cpp
int cnt = 1;
```

Initially we keep the first interval because there is no previous interval that could cover it.

`cnt` stores the number of intervals that are **not covered**.

---

# Traversal

```cpp
for (int i = 1; i < n; ++i) {

    if (r >= arr[i][1])
        continue;

    r = arr[i][1];
    cnt++;
}
```

For every interval there are only two possibilities.

---

## Case 1

```
current.end <= r
```

Example

```
r = 10

current = [6,8]
```

Since

```
8 <= 10
```

and sorting guarantees

```
previous.start <= current.start
```

there exists a previous interval

```
[previous.start,10]
```

that satisfies

```
previous.start <= current.start
10 >= 8
```

Therefore the current interval is covered.

We skip it.

---

## Case 2

```
current.end > r
```

Example

```
r = 10

current = [6,13]
```

Since

```
13 > 10
```

no previous interval reaches endpoint 13.

Therefore the current interval cannot be covered.

We keep it.

```
r = 13
cnt++
```

---

# Why checking only the ending point works

The definition of coverage is

```
previous.start <= current.start
previous.end >= current.end
```

After sorting,

```
previous.start <= current.start
```

is already guaranteed.

So the only remaining condition is

```
previous.end >= current.end
```

Since `r` stores the largest previous endpoint,

```cpp
if (r >= current.end)
```

is enough to determine whether the interval is covered.

---

# Dry Run

Input

```
[[1,4],[3,6],[2,8]]
```

After sorting

```
[1,4]
[2,8]
[3,6]
```

Initialization

```
r = 4
cnt = 1
```

Process `[2,8]`

```
8 > 4
```

Keep it.

```
r = 8
cnt = 2
```

Process `[3,6]`

```
6 <= 8
```

Covered.

Skip it.

Final Answer

```
2
```

---

# Time Complexity

Sorting:

```
O(n log n)
```

Traversal:

```
O(n)
```

Overall:

```
O(n log n)
```

---

# Space Complexity

```
O(1)
```

Ignoring the recursion stack used internally by `std::sort`.

Otherwise,

```
O(log n)
```

due to the recursive calls made by the sorting algorithm.

---

# Key Insight

The custom sorting ensures that:

- Every possible covering interval appears before the interval it can cover.
- Among intervals with the same starting point, the longest interval appears first.

Because of this ordering, a single variable `r` (the maximum endpoint seen so far) is sufficient to determine whether the current interval is covered.

This eliminates the need for nested loops and reduces the solution from **O(n²)** to **O(n log n)**.