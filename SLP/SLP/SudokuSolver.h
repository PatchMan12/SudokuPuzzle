#pragma once
using namespace System;
using namespace System::Windows::Forms;

ref class SudokuSolver
{
public:
    // Check if number is valid in a given position
    static bool IsValid(array<TextBox^, 2>^ grid, int row, int col, int num)
    {
        // Check row and column
        for (int i = 0; i < 9; i++)
        {
            if (grid[row, i]->Text == num.ToString()) return false;
            if (grid[i, col]->Text == num.ToString()) return false;
        }

        // Check 3x3 sub-grid
        int startRow = (row / 3) * 3;
        int startCol = (col / 3) * 3;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (grid[startRow + i, startCol + j]->Text == num.ToString()) return false;
            }
        }

        return true;
    }

    // Find empty cell (returns true if found)
    static bool FindEmptyCell(array<TextBox^, 2>^ grid, int% row, int% col)
    {
        for (row = 0; row < 9; row++)
        {
            for (col = 0; col < 9; col++)
            {
                if (String::IsNullOrWhiteSpace(grid[row, col]->Text))
                {
                    return true;
                }
            }
        }
        return false;
    }

    // Solve the Sudoku using Backtracking
    static bool Solve(array<TextBox^, 2>^ grid)
    {
        int row, col;

        // If no empty cell is found, puzzle is solved
        if (!FindEmptyCell(grid, row, col)) return true;

        // Try numbers 1 to 9
        for (int num = 1; num <= 9; num++)
        {
            if (IsValid(grid, row, col, num))
            {
                grid[row, col]->Text = num.ToString();  // Assign the number

                if (Solve(grid)) return true;  // Recur to solve the next empty cell

                grid[row, col]->Text = "";  // Undo & backtrack if the solution fails
            }
        }

        return false;  // Trigger backtracking
    }

    // Function to detect duplicates before solving
    static bool HasDuplicate(array<TextBox^, 2>^ grid)
    {
        for (int i = 0; i < 9; i++)
        {
            bool rowCheck[10] = { false };
            bool colCheck[10] = { false };

            for (int j = 0; j < 9; j++)
            {
                // Check row
                if (!String::IsNullOrWhiteSpace(grid[i, j]->Text))
                {
                    int num = Int32::Parse(grid[i, j]->Text);
                    if (num < 1 || num > 9) return true; // Invalid input
                    if (rowCheck[num]) return true;
                    rowCheck[num] = true;
                }

                // Check column
                if (!String::IsNullOrWhiteSpace(grid[j, i]->Text))
                {
                    int num = Int32::Parse(grid[j, i]->Text);
                    if (num < 1 || num > 9) return true; // Invalid input
                    if (colCheck[num]) return true;
                    colCheck[num] = true;
                }
            }
        }
        return false;
    }
};
