# Notes from this chat

Everything I learned, in one place. Three problems (powerset, permutations, n-queens) → two flavors of recursion → one mental model that makes them all easy.

---

## Part 1 — Powerset

### What it is
The **powerset** of a set S = the set of all subsets of S, including the empty set and S itself.

For S = {1, 2, 3}:
```
{}, {1}, {2}, {3}, {1,2}, {1,3}, {2,3}, {1,2,3}
```
That's 2³ = 8.

### Why 2ⁿ?
For each element you have a binary choice: **include it** or **skip it**. n independent yes/no choices ⇒ 2ⁿ combinations.

That binary choice IS the key insight for the recursion.

### The problem
Given target `n` and set `s`, print every subset whose elements sum to `n`. Elements must appear in original input order (so `1 2` and `2 1` don't both appear).

### The recursion idea — decision tree
At each element, branch into two universes:
- **Skip it** — move on
- **Take it** — add to current subset, move on

When you've decided about every element, you have one complete subset → check if sum matches → print if yes.

### Code mapping (your solve())
```c
void solve(int *set, int *subset, int size, int n,
           int index, int sum, int len)
```

| param    | meaning                                                |
|----------|--------------------------------------------------------|
| `set`    | original input (never modified)                        |
| `subset` | scratch buffer holding currently chosen elements       |
| `size`   | total elements in `set`                                |
| `n`      | target sum                                             |
| `index`  | which element we're deciding about (depth in the tree) |
| `sum`    | running sum of chosen elements                         |
| `len`    | how many elements currently sit in `subset`            |

```c
if (index == size) {
    if (sum == n)
        print_solve(subset, len);
    return;
}
solve(..., index + 1, sum, len);                 // SKIP branch
subset[len] = set[index];
solve(..., index + 1, sum + set[index], len + 1);// TAKE branch
```

### Why no explicit "undo" / backtrack is needed here
- The skip branch never touches `subset` — `len` stays the same.
- The take branch writes `subset[len]` and passes `len + 1` down. When that call returns, the parent uses the old `len`, so anything past `len` is garbage and ignored.
- You don't erase; you just don't read past the boundary.

### Why duplicates can't happen
Elements are always processed in input order. The recursion never goes back to put `set[0]` after `set[1]`. Built-in ordering is enforced by the tree structure itself.

---

## Part 2 — Permutations

### What it is
A **permutation** of a sequence = every possible ordering.

For `abc`: `abc, acb, bac, bca, cab, cba`. That's 3! = 6.

### Why n!?
Building a permutation:
- 1st slot: n options
- 2nd slot: n − 1 remaining
- 3rd slot: n − 2 remaining
- ...

Total = n × (n−1) × ... × 1 = **n!**

### Alphabetical order requirement
Sort the input string first. Then the recursion's natural left-to-right scan produces alphabetical output automatically.

### The recursion idea — fill the slots
Unlike powerset (walk elements, ask "include/skip"), permutations walks **output positions** and asks **"which unused character goes here?"**

```
[ ][ ][ ]   depth=0, all chars free
[a][ ][ ]   pick 'a' at depth=0, mark used
[a][b][ ]   pick 'b' at depth=1
[a][b][c]   pick 'c' at depth=2 → print "abc"
```

Then unwind, unmark, try next unused.

### Code mapping
```c
static void permute_rec(const char *s, char *used, char *out,
                        int depth, int len)
```

| param   | meaning                                                       |
|---------|---------------------------------------------------------------|
| `s`     | sorted input (never modified)                                 |
| `used`  | array of length `len`; `used[i]=1` if `s[i]` already placed   |
| `out`   | buffer being built — `out[0..depth]` is current partial perm  |
| `depth` | which output slot we're filling (0..len)                      |
| `len`   | total length                                                  |

```c
if (depth == len) {
    out[len] = '\0';
    ft_putstr_nl(out);
    return;
}
i = 0;
while (i < len) {
    if (!used[i]) {
        used[i] = 1;            // claim
        out[depth] = s[i];
        permute_rec(..., depth + 1, ...);
        used[i] = 0;            // RELEASE — backtrack
    }
    i++;
}
```

### Why explicit backtracking IS needed here
`used[]` is **shared** across all recursion levels. If you set `used[0] = 1`, recurse, and return — without `used[0] = 0`, the next sibling iteration thinks `'a'` is still in use and skips it. The whole `b...` and `c...` branches break.

`used[i] = 0` makes sibling branches independent. This is the **classic backtracking pattern**:
```
make choice → recurse → undo choice
```

---

## Part 3 — Two flavors of recursion side by side

| aspect             | Powerset                          | Permutations                       |
|--------------------|-----------------------------------|------------------------------------|
| Choice at each step| binary: include / skip            | n-ary: which unused element        |
| Recursive calls    | exactly 2 per level               | one per available choice (loop)    |
| State tracked      | `index`, `sum`, `len`             | `used[]`, `depth`                  |
| Backtracking       | implicit (no explicit undo)       | explicit (`used[i] = 0` after)     |
| Total leaves       | 2ⁿ                                | n!                                 |
| Iterates over...   | **elements** (decide each one)    | **positions** (fill each slot)     |

Two skeletons to remember:

**Include/skip skeleton** — for SUBSET enumeration:
```
solve(index):
    if index == size:
        check / record
        return
    solve(index + 1)              # skip
    apply choice
    solve(index + 1)              # take
```

**Fill-the-slots skeleton** — for ARRANGEMENT enumeration:
```
fill(slot):
    if slot == total_slots:
        record
        return
    for each available choice c:
        place c
        mark c used
        fill(slot + 1)
        unmark c                  # backtrack
```

Same skeletons reappear in: N-Queens (fill-the-slots), sudoku (fill-the-slots), coin change (include/skip variant), word break (variant), maze solving (fill-the-slots variant).

---

## Part 4 — How to actually think about recursion

**The biggest insight: don't trace the tree mentally. Nobody does.**

### The recursive leap of faith (induction)
When writing or reading a recursive function, verify exactly two things:

1. **Base case is correct.** When the function decides "I'm done," does it do the right thing?
2. **One step is correct.** Assuming the recursive call works correctly on smaller input, does *this* level do the right thing?

If both hold → the whole thing is correct, by induction. The computer handles the stack bookkeeping. You don't.

### Treat the recursive call as `magic_solve()`
Pretend the recursive call is a black box that already returns the correct answer for the smaller problem. Just ask: "if that's correct, is what I do here correct?"

### When you DO need to trace
- Only on paper, only for n ≤ 3.
- Track one path from root to leaf, not the whole tree.
- For real code, add indented debug prints. The terminal shows the tree shape for you.

### The mental shift
You are **describing a rule**, not a sequence of steps. You tell the computer how to solve size n given solutions to size n−1. You write the rule. The machine unrolls it.

### Concrete drill
1. Open a recursive function.
2. Cover the recursive call lines with your hand.
3. Pretend the recursive call is a working black box.
4. Read just the current level. Ask: "If the call works for smaller input, does this code produce the right answer?"
5. If yes — done.

If you can convince yourself recursion is correct *without tracing*, you've internalized it.

---

## Quick reference: which skeleton for which problem?

- **Subsets / "include or skip"** → powerset skeleton (2 calls per level, implicit backtrack)
- **Arrangements / orderings** → fill-the-slots skeleton (loop + explicit backtrack)
- **Constraint satisfaction** (N-Queens, sudoku) → fill-the-slots + a check before recursing
- **Path finding** → fill-the-slots variant where "slot" is the current node and choices are neighbors

Pick the skeleton first. Fill in the problem-specific check second.
