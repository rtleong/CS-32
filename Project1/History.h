#ifndef HISTORY_H
#define HISTORY_H
#include "globals.h"


class History
{
public:
	History(int nRows, int nCols);
	bool record(int r, int c);
	void display() const;

private:
	int h_rows;							
	int h_cols;
	int arr[MAXROWS][MAXCOLS];		//integer array used for indexing
	char displayGrid[MAXROWS][MAXCOLS];//char array responsible for displaying the history letters
};

#endif