#include "History.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols) {
	h_rows = nRows;
	h_cols = nCols;	//uses priv member variables to create history construction

	for (int i = 0; i < h_rows; i++) {
		for (int k = 0; k < h_cols; k++) {
			arr[i][k] = 0;	//sets value of int array to 0.
		}
	}

	for (int p = 0; p < h_rows; p++) {
		for (int m = 0; m < h_cols; m++) {
			displayGrid[p][m] = '.';	//gives dots as beginning display of h grid
		}
	}
}

bool History::record(int r, int c)
{
	//updates display grid with "A" then "B" and so on when a carrot is dropped
	if (r < 1 || r > h_rows || c < 1 || c > h_cols) {
		return false;
	}
	arr[r - 1][c - 1]++;
	if (arr[r - 1][c - 1] == 1) {
		displayGrid[r - 1][c - 1] = 'A';
		return true;
	}
	else if (arr[r - 1][c - 1] > 1 && arr[r-1][c-1] < 27) {
		displayGrid[r - 1][c - 1]++;
		return true;
	}
	else { //greater than 27 means stays at Z
		return true;
	}
}

void History::display() const
{
	clearScreen();

	int r, c;

	// Fill displayGrid with dots (took from Arena Class that was given :))
	for (r = 0; r < h_rows; r++) {
		for (c = 0; c < h_cols; c++)
			cout << displayGrid[r][c];
		cout << endl;//endline after alotted grid space col
	}
	cout << endl;//endline at end to prompt user
}