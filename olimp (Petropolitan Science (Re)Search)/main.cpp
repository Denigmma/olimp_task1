#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void printSudoku(const vector<vector<int>>& sudoku) {
	for (const auto& row : sudoku) {
		for (int num : row) {
			cout << num << " ";
		}
		cout << endl;
	}
}

// ������� ��� ��������, ����� �� ��������� ����� � ������ ������
bool isValid(const vector<vector<int>>& sudoku, int row, int col, int num, int size) {
	// ��������� ������
	for (int i = 0; i < size; ++i) {
		if (sudoku[row][i] == num) {
			return false;
		}
	}
	// ��������� �������
	for (int i = 0; i < size; ++i) {
		if (sudoku[i][col] == num) {
			return false;
		}
	}
	return true;
}

// ������� ��� ������� ������
bool solveSudoku(vector<vector<int>>& sudoku, int size) {
	// ������� ������������� ������
	int row = -1, col = -1;
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (sudoku[i][j] == 0) {
				row = i;
				col = j;
				break;
			}
		}
		if (row != -1) {
			break;
		}
	}

	// ���� ��� ������ ���������, ������ ������
	if (row == -1) {
		return true;
	}

	// ������� ��������� ����� �� 1 �� size
	for (int num = 1; num <= size; ++num) {
		if (isValid(sudoku, row, col, num, size)) {
			sudoku[row][col] = num;
			// ���������� ������ ���������� ����� ������
			if (solveSudoku(sudoku, size)) {
				return true;
			}
			// ���� �� ������� ����� �������, �������� ��������� ����������
			sudoku[row][col] = 0;
		}
	}
	// ���� �� ������� ����� �������
	return false;
}



int main() {
	ifstream inputFile("sudoku.txt");
	if (!inputFile) {
		cerr << "Unable to open file sudoku.txt";
		return 1;
	}

	int size;
	inputFile >> size; // ������ ������ ������
	cout << "Size of sudoku: " << size << endl;

	vector<vector<int>> sudoku(size, vector<int>(size));

	// ������ ������ �� �����
	cout << "Sudoku read from file:" << endl;
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			inputFile >> sudoku[i][j];
			cout << sudoku[i][j] << " ";
		}
		cout << endl;
	}

	inputFile.close();

	if (solveSudoku(sudoku, size)) {
		cout << "Solved sudoku:" << endl;
		printSudoku(sudoku);
	}
	else {
		cout << "Invalid field" << endl;
	}
	return 0;
}