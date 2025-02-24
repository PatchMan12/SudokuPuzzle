#pragma once
#include "SudokuSolver.h"  

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
			this->SudokuPanel->Name = L"SudokuPanel";
			this->SudokuPanel->Size = System::Drawing::Size(415, 405);
			this->SudokuPanel->TabIndex = 0;
			this->SudokuPanel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::SudokuPanel_Paint);
			// 
			// SOLVEBUTTON
			// 
			this->SOLVEBUTTON->Location = System::Drawing::Point(552, 145);
			this->SOLVEBUTTON->Name = L"SOLVEBUTTON";
			this->SOLVEBUTTON->Size = System::Drawing::Size(113, 41);
			this->SOLVEBUTTON->TabIndex = 1;
			this->SOLVEBUTTON->Text = L"SOLVE";
			this->SOLVEBUTTON->Click += gcnew System::EventHandler(this, &Form1::SOLVEBUTTON_Click);
			// 
			// CLEAR
			// 
			this->CLEAR->Location = System::Drawing::Point(552, 254);
			this->CLEAR->Name = L"CLEAR";
			this->CLEAR->Size = System::Drawing::Size(113, 41);
			this->CLEAR->TabIndex = 2;
			this->CLEAR->Text = L"CLEAR";
			this->CLEAR->Click += gcnew System::EventHandler(this, &Form1::CLEAR_Click);
			// 
			// Form1
			// 
			this->ClientSize = System::Drawing::Size(726, 500);
			this->Controls->Add(this->SudokuPanel);
			this->Controls->Add(this->SOLVEBUTTON);
			this->Controls->Add(this->CLEAR);
			this->Name = L"Form1";
			this->Text = L"Sudoku Grid";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);

		}

	private:
		System::Void Form1_Load(System::Object^ sender, System::EventArgs^ e) {
			GenerateSudokuGrid();
		}

		void GenerateSudokuGrid()
		{
			int cellSize = 45;        // Size of each TextBox
			int subgridSize = 3;      // 3x3 subgrid size
			int gridSize = 9;         // Sudoku grid size
			int gapSize = 5;          // Space between 3x3 subgrids

			SudokuGrid = gcnew array<TextBox^, 2>(gridSize, gridSize);

			// Set the background color of the main Sudoku panel to light green
			SudokuPanel->BackColor = System::Drawing::Color::DarkGreen;

			// Create a 3x3 subgrid panels with spacing
			array<Panel^, 2>^ subgridPanels = gcnew array<Panel^, 2>(subgridSize, subgridSize);

			for (int subRow = 0; subRow < subgridSize; subRow++)
			{
				for (int subCol = 0; subCol < subgridSize; subCol++)
				{
					// Create a panel for each 3x3 subgrid
					Panel^ subgridPanel = gcnew Panel();
					subgridPanel->Size = System::Drawing::Size(cellSize * subgridSize, cellSize * subgridSize);
					subgridPanel->Location = System::Drawing::Point(
						subCol * (cellSize * subgridSize + gapSize),  // X position with gap
						subRow * (cellSize * subgridSize + gapSize)   // Y position with gap
					);
					subgridPanel->BorderStyle = BorderStyle::FixedSingle; // Creates bold borders
					subgridPanel->BackColor = System::Drawing::Color::White; // Ensure the 3x3 grid is clear

					// Add panel to SudokuPanel
					SudokuPanel->Controls->Add(subgridPanel);
					subgridPanels[subRow, subCol] = subgridPanel;
				}
			}

			for (int row = 0; row < gridSize; row++)
			{
				for (int col = 0; col < gridSize; col++)
				{
					TextBox^ textBox = gcnew TextBox();
					textBox->Size = System::Drawing::Size(cellSize, cellSize);
					textBox->Location = System::Drawing::Point(
						(col % subgridSize) * cellSize,
						(row % subgridSize) * cellSize
					);
					textBox->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18);
					textBox->TextAlign = HorizontalAlignment::Center;
					textBox->MaxLength = 1;
					textBox->BorderStyle = BorderStyle::FixedSingle;

					// Determine which 3x3 subgrid panel this cell belongs to
					int subgridRow = row / subgridSize;
					int subgridCol = col / subgridSize;

					// Add TextBox to corresponding 3x3 subgrid panel
					subgridPanels[subgridRow, subgridCol]->Controls->Add(textBox);

					// Store the reference in the SudokuGrid array
					SudokuGrid[row, col] = textBox;
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
					SudokuGrid[row, col]->Text = "";
					SudokuGrid[row, col]->BackColor = System::Drawing::Color::White;
				}
			}
		}
	private: System::Void SudokuPanel_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
};
}
