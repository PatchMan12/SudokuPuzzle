#pragma once
using namespace System;
using namespace System::Windows::Forms;

ref class SudokuSolver
{
public:
    // Determine the grid size based on input
    static int GetGridSize(array<TextBox^, 2>^ grid)
    {
        return grid->GetLength(0); // Assuming square grid
    }

    // Determine the subgrid size (sqrt of grid size)
    static int GetSubgridSize(int gridSize)
    {
        return (int)Math::Sqrt(gridSize);
    }

    // Check if number is valid in a given position
    static bool IsValid(array<TextBox^, 2>^ grid, int row, int col, int num)
    {
        int gridSize = GetGridSize(grid);
        int subgridSize = GetSubgridSize(gridSize);

        // Check row and column
        for (int i = 0; i < gridSize; i++)
        {
            if (grid[row, i]->Text == num.ToString()) return false;
            if (grid[i, col]->Text == num.ToString()) return false;
        }

        // Check sub-grid
        int startRow = (row / subgridSize) * subgridSize;
        int startCol = (col / subgridSize) * subgridSize;
        for (int i = 0; i < subgridSize; i++)
        {
            for (int j = 0; j < subgridSize; j++)
            {
                if (grid[startRow + i, startCol + j]->Text == num.ToString()) return false;
            }
        }

        return true;
    }

    // Find empty cell (returns true if found)
    static bool FindEmptyCell(array<TextBox^, 2>^ grid, int% row, int% col)
    {
        int gridSize = GetGridSize(grid);
        for (row = 0; row < gridSize; row++)
        {
            for (col = 0; col < gridSize; col++)
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
        int gridSize = GetGridSize(grid);

        // If no empty cell is found, puzzle is solved
        if (!FindEmptyCell(grid, row, col)) return true;

        // Try numbers 1 to gridSize
        for (int num = 1; num <= gridSize; num++)
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
        int gridSize = GetGridSize(grid);
        int subgridSize = GetSubgridSize(gridSize);

        for (int i = 0; i < gridSize; i++)
        {
            array<bool>^ rowCheck = gcnew array<bool>(gridSize + 1);
            array<bool>^ colCheck = gcnew array<bool>(gridSize + 1);

            for (int j = 0; j < gridSize; j++)
            {
                // Check row
                if (!String::IsNullOrWhiteSpace(grid[i, j]->Text))
                {
                    int num = Int32::Parse(grid[i, j]->Text);
                    if (num < 1 || num > gridSize) return true; // Invalid input
                    if (rowCheck[num]) {
                        MessageBox::Show("Duplicate number found in row " + (i + 1), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                        return true;
                    }
                    rowCheck[num] = true;
                }

                // Check column
                if (!String::IsNullOrWhiteSpace(grid[j, i]->Text))
                {
                    int num = Int32::Parse(grid[j, i]->Text);
                    if (num < 1 || num > gridSize) return true; // Invalid input
                    if (colCheck[num]) {
                        MessageBox::Show("Duplicate number found in column " + (i + 1), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                        return true;
                    }
                    colCheck[num] = true;
                }
            }
        }

        // Check sub-grid for duplicates
        for (int boxRow = 0; boxRow < subgridSize; boxRow++)
        {
            for (int boxCol = 0; boxCol < subgridSize; boxCol++)
            {
                array<bool>^ boxCheck = gcnew array<bool>(gridSize + 1);
                for (int i = 0; i < subgridSize; i++)
                {
                    for (int j = 0; j < subgridSize; j++)
                    {
                        int row = boxRow * subgridSize + i;
                        int col = boxCol * subgridSize + j;
                        if (!String::IsNullOrWhiteSpace(grid[row, col]->Text))
                        {
                            int num = Int32::Parse(grid[row, col]->Text);
                            if (num < 1 || num > gridSize) return true; // Invalid input
                            if (boxCheck[num]) {
                                MessageBox::Show("Duplicate number found in subgrid starting at row " + (boxRow * subgridSize + 1) + " and column " + (boxCol * subgridSize + 1), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                                return true;
                            }
                            boxCheck[num] = true;
                        }
                    }
                }
            }
        }
        return false;
    }
};