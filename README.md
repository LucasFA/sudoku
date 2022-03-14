# Sudoku
## Objective
A sudoku solver for a given sudoku problem

## Means
Instead of just backtracking, the final objective is to improve performance through the use of deductions when possible
## Deduction rules
We well use several rules:
### Rule 1: Only possibility in cell
If a cell has only one possibility, assign that value.
### Rule 2: Only possibility in neighbourhood
Given a neighbourhood and a number, does there exist only one location for it? Then fill that value.

### Backtracking.
After all the above has been applied, assign a possible value to a cell and apply recursively the deduction rules section. See related, Nishio method.