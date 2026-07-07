# Explanation of `sumAndMultiply`

## Code

```cpp
class Solution {
public:
    long long sumAndMultiply(int n) {
        string m = to_string(n);

        long long ans = 0;
        long long sum = 0;

        for (auto it : m) {
            if (it != '0') {
                ans = ans * 10 + (it - '0');
                sum += (it - '0');
            }
        }

        return ans * sum;
    }
};
```

---

# Intuition

The problem requires us to:

1. Remove all the digits `0` from the given number.
2. Form a new number using the remaining digits while preserving their original order.
3. Compute the sum of the remaining digits.
4. Return the product of the newly formed number and the digit sum.

Instead of creating another string and converting it back to an integer, we can construct the number directly while traversing the digits once.

This allows us to solve the problem in a single pass.

---

# Step 1: Convert the integer to a string

```cpp
string m = to_string(n);
```

The integer is converted into a string so that every digit can be processed individually.

Example

```
n = 5040302

m = "5040302"
```

---

# Step 2: Initialize variables

```cpp
long long ans = 0;
long long sum = 0;
```

### `ans`

Stores the number obtained after removing all zeroes.

### `sum`

Stores the sum of all non-zero digits.

---

# Step 3: Traverse every digit

```cpp
for (auto it : m)
```

Each character represents one digit.

Example

```
"5040302"

↓

'5'
'0'
'4'
'0'
'3'
'0'
'2'
```

---

# Step 4: Ignore zeroes

```cpp
if (it != '0')
```

Only non-zero digits are processed.

Zeroes are skipped because they should not appear in the new number.

---

# Step 5: Form the new number

```cpp
ans = ans * 10 + (it - '0');
```

Suppose

```
Current ans = 54
Current digit = 3
```

Then

```
ans = 54 × 10 + 3
    = 543
```

Each new digit is appended to the right while maintaining the original order.

---

# Step 6: Update the digit sum

```cpp
sum += (it - '0');
```

Example

```
Digits processed

5
4
3
2
```

Then

```
sum = 5 + 4 + 3 + 2
    = 14
```

---

# Step 7: Return the final answer

```cpp
return ans * sum;
```

The required result is simply

```
(New Number) × (Sum of Digits)
```

---

# Dry Run

## Example

```
n = 5040302
```

Initial values

```
ans = 0
sum = 0
```

### Digit = '5'

```
ans = 0 × 10 + 5 = 5
sum = 5
```

---

### Digit = '0'

Ignored.

```
ans = 5
sum = 5
```

---

### Digit = '4'

```
ans = 5 × 10 + 4 = 54
sum = 9
```

---

### Digit = '0'

Ignored.

---

### Digit = '3'

```
ans = 54 × 10 + 3 = 543
sum = 12
```

---

### Digit = '0'

Ignored.

---

### Digit = '2'

```
ans = 543 × 10 + 2 = 5432
sum = 14
```

Final answer

```
5432 × 14 = 76048
```

---

# Correctness

The algorithm processes every digit exactly once.

For every non-zero digit:

- It is appended to the new number while preserving its position relative to other non-zero digits.
- It contributes exactly once to the digit sum.

Since all zeroes are skipped, the constructed number is precisely the original number with all zeroes removed.

Finally, the algorithm returns the product of this number and the digit sum, which matches the required output.

---

# Time Complexity

Let **d** be the number of digits in the integer.

Converting to a string:

```
O(d)
```

Traversing the string:

```
O(d)
```

Overall:

```
O(d)
```

---

# Space Complexity

The string created by `to_string()` stores all digits.

```
O(d)
```

where **d** is the number of digits in the input integer.