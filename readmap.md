# Backtracking and Combinatorics Roadmap

This roadmap is designed to help you solve problems like `powerset`, `permutations`, `n-queens`, and `tsp`.

## Recommended Difficulty Order

1. `powerset`
2. `permutations`
3. `n-queens`
4. `tsp`

`rip` depends on the exact statement, but it usually fits between `permutations` and `n-queens` for typical recursion/backtracking variants.

## What You Need to Know

- Recursion basics: base case, recursive case, call stack
- Backtracking pattern: choose -> recurse -> un-choose
- Complexity intuition:
  - powerset: `O(2^n)`
  - permutations: `O(n!)`
  - n-queens: exponential with pruning
  - tsp brute force: `O(n!)`
  - tsp DP + bitmask: `O(n^2 * 2^n)`
- State representations:
  - arrays/lists
  - `used[]`
  - sets/boolean constraints
  - bitmasks
- Pruning only when logically safe
- Output formatting discipline

## 7-Day Study Plan

### Day 1 - Powerset + Subset Sum (today)

- Learn include/exclude recursion
- Implement `powerset` with target sum
- Handle negative numbers correctly (no invalid pruning like `sum > target`)
- Confirm empty subset behavior when target is `0`

### Day 2 - Permutations

- Implement using `used[]`
- Implement in-place swap version
- Practice explicit backtracking (choose/recurse/un-choose)

### Day 3 - N-Queens

- Implement classic backtracking
- Add pruning with column and diagonal constraints
- Verify correctness first, then optimize

### Day 4 - Bitmask Basics

- Set/test/clear bit operations
- Enumerate subsets with bitmask
- Revisit powerset and n-queens using bitmasks

### Day 5 - TSP Brute Force

- Graph representation (matrix/list)
- Generate city orderings and compute total path cost
- Understand why brute force does not scale

### Day 6 - TSP DP + Bitmask (Held-Karp)

- Define DP state: `dp[mask][last]`
- Implement transitions and base states
- Recover final answer and validate complexity

### Day 7 - Consolidation + Exam Speed

- Solve powerset, permutations, n-queens from memory
- Rebuild tsp DP structure from memory
- Time-box each problem and debug under pressure

## Powerset Subject Checklist (for your current assignment)

- Parse: `target = argv[1]`, set values from `argv[2..]`
- Recurse with index progression only (`i -> i + 1`)
- Track current sum and chosen elements
- At end of set, print subset if sum equals target
- Keep element order identical to input order
- Print empty line for empty subset when valid
- On `malloc` failure, exit code `1`

## Minimal Backtracking Template to Memorize

```text
dfs(index, sum, chosen):
    if index == n:
        if sum == target: print(chosen)
        return

    dfs(index + 1, sum, chosen)                  // skip
    chosen.push(a[index])
    dfs(index + 1, sum + a[index], chosen)       // take
    chosen.pop()
```

## Daily Practice Rule

For each new problem:

1. Write state variables first
2. Write base case second
3. Write two or more choices
4. Add pruning only after correctness is proven
