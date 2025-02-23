#pragma once
#include "SudokuSolver.h"  // Include the Sudoku solving logic

namespace SLP {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
		}

	protected:
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::Windows::Forms::Panel^ SudokuPanel;
		array<TextBox^, 2>^ SudokuGrid;
		System::Windows::Forms::Button^ SOLVEBUTTON;
		System::Windows::Forms::Button^ CLEAR;
		System::ComponentModel::Container^ components;

		void InitializeComponent(void)
		{
			this->SudokuPanel = (gcnew System::Windows::Forms::Panel());
			this->SOLVEBUTTON = (gcnew System::Windows::Forms::Button());
			this->CLEAR = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// SudokuPanel
			// 
			this->SudokuPanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->SudokuPanel->Location = System::Drawing::Point(50, 20);
			this->SudokuPanel->Size = System::Drawing::Size(405, 405);
			this->Controls->Add(this->SudokuPanel);

			// 
			// SOLVEBUTTON
			// 
			this->SOLVEBUTTON->Location = System::Drawing::Point(577, 146);
			this->SOLVEBUTTON->Size = System::Drawing::Size(113, 41);
			this->SOLVEBUTTON->Text = L"SOLVE";
			this->SOLVEBUTTON->Click += gcnew System::EventHandler(this, &Form1::SOLVEBUTTON_Click);
			this->Controls->Add(this->SOLVEBUTTON);

			// 
			// CLEAR
			// 
			this->CLEAR->Location = System::Drawing::Point(577, 254);
			this->CLEAR->Size = System::Drawing::Size(113, 41);
			this->CLEAR->Text = L"CLEAR";
			this->CLEAR->Click += gcnew System::EventHandler(this, &Form1::CLEAR_Click);
			this->Controls->Add(this->CLEAR);

			// 
			// Form1
			// 
			this->ClientSize = System::Drawing::Size(726, 500);
			this->Text = L"Sudoku Grid";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);
		}

	private:
		System::Void Form1_Load(System::Object^ sender, System::EventArgs^ e) {
			GenerateSudokuGrid();
		}

		// Function to generate a 9x9 Sudoku Grid
		void GenerateSudokuGrid()
		{
			int cellSize = 45;
			int gridSize = 9;
			SudokuGrid = gcnew array<TextBox^, 2>(gridSize, gridSize);

			for (int row = 0; row < gridSize; row++)
			{
				for (int col = 0; col < gridSize; col++)
				{
					TextBox^ textBox = gcnew TextBox();
					textBox->Size = System::Drawing::Size(cellSize, cellSize);
					textBox->Location = System::Drawing::Point(col * cellSize, row * cellSize);
					textBox->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18);
					textBox->TextAlign = HorizontalAlignment::Center;
					textBox->MaxLength = 1;
					textBox->BorderStyle = BorderStyle::FixedSingle;

					// Add TextBox to Panel
					SudokuGrid[row, col] = textBox;
					SudokuPanel->Controls->Add(textBox);
				}
			}
		}

	private:
		System::Void SOLVEBUTTON_Click(System::Object^ sender, System::EventArgs^ e) {
			if (SudokuSolver::HasDuplicate(SudokuGrid))
			{
				MessageBox::Show("Error: Duplicate numbers found in rows or columns!", "Invalid Input", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			if (SudokuSolver::Solve(SudokuGrid))
			{
				MessageBox::Show("Sudoku Solved!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			else
			{
				MessageBox::Show("No solution exists for this puzzle.", "Failure", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	private:
		System::Void CLEAR_Click(System::Object^ sender, System::EventArgs^ e) {
			for (int row = 0; row < 9; row++) {
				for (int col = 0; col < 9; col++) {
					SudokuGrid[row, col]->Text = ""; // Clear each cell
				}
			}
		}
	};
}
