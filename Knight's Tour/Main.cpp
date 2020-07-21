#include <iostream>
#include <windows.h>
#include "ecpe202.h"

#define MAX 100
using namespace std;

void SetSpaceForProcess(int col, int endlines);
void SetSpaceForOutput(int endlines);
void CreateBoard(int type, int data[][8]);
void ResetScreen();
void gotoxy(int x, int y);
void PrintSplash();
int debugrow = 0, debugrow2 = 0, outputrow = 0;

int main() {
	int I, J, intTemp;
	int BOARD[8][8], BOARD2[8][8], movement[65][2];
	int KTMOV1[] = { -2, -1, 1, 2, 2, 1, -1, -2 };
	int KTMOV2[] = { 1, 2, 2, 1, -1, -2, -2, -1 };
	char getColEq[] = { 'A','B','C','D','E','F','G','H' };
	char letter, temp[MAX];

	PrintSplash();

	// Initialize Chessboard
	for (int row = 0; row < 8; row++)
		for (int col = 0; col < 8; col++)
			BOARD[row][col] = 0;

	// Display Empty Board
	CreateBoard(1, BOARD);
	cout << endl;

	// Set Starting Position
	cout << "Set Starting Position:\n";
	cout << "J(A-H): ";
	cin >> letter;
	intTemp = (int)letter;
	for (int nOc = 0; nOc < 8; nOc++) {
		if (intTemp == int(getColEq[nOc])) {
			J = nOc;
		}
	}
	cout << "I(1-8): ";
	cin >> temp;
	I = atoi(temp) - 1;
	
	BOARD[I][J] = 1;

	// Loop
	for (int M = 2; M <= 64; M++) {
		ResetScreen();

		// Form set of possible next squares
		SetSpaceForProcess(1,0);
		cout << "*****Form Set Of Possible Next Squares*****";
		int NPOS = 0, L = 0;
		int NEXTI[8], NEXTJ[8];
		for (int K = 0; K < 8; K++) {
			NEXTI[L] = I + KTMOV1[K];
			NEXTJ[L] = J + KTMOV2[K];

			SetSpaceForProcess(1,0);
			
			if (NEXTI[L] < 0 || NEXTI[L] >= 8 || NEXTJ[L] < 0 || NEXTJ[L] >= 8) {
				if (NEXTJ[L] < 0 || NEXTJ[L] >= 8) {
					cout <<  "- , ";
				}
				else {
					cout << getColEq[NEXTJ[L]] << " , ";
				}
				if (NEXTI[L] < 0 || NEXTI[L] >= 8) {
					cout << "-";
				}
				else {
					cout << NEXTI[L] + 1;
				}
				cout << "\t== INVALID (OUTOFBOUNDS)";
			}
			else {
				cout << getColEq[NEXTJ[L]] << " , " << NEXTI[L] + 1;
				if (BOARD[NEXTI[L]][NEXTJ[L]] != 0) {
					cout << "\t== INVALID (OCCUPIED)";
				}
				else {
					NPOS++;
					L++;
					cout << "\t== " << NPOS;
				}
			}
			cout << endl;
		}
		// Test Special Cases
		SetSpaceForProcess(1,1);
		cout << "*****Test Special Cases*****";
		int MIN = -1;
		if (NPOS == 0) {
			SetSpaceForProcess(1,0);
			cout << "***Special Case***";
			SetSpaceForProcess(1,0);
			cout << "Premature End";
			return -1;
		}
		else if (NPOS == 1) {
			SetSpaceForProcess(1,0);
			cout << "***Special Case***";
			SetSpaceForProcess(1,0);
			cout << "Only 1 Possibility";
			SetSpaceForProcess(1,1);
			cout << "Minimum Exits (1) at Array Index 0";
			MIN = 0;
		}
		else {
			// Find Next Square With Minimum Exits
			SetSpaceForProcess(2,0);
			cout << "*****Find Next Square With Minimum Exits*****";
			int EXITS[8];
			for (L = 0; L < NPOS; L++) {
				cout << endl;
				int exits = 0;
				for (int K = 0; K < 8; K++) {
					int NextI = NEXTI[L] + KTMOV1[K];
					int NextJ = NEXTJ[L] + KTMOV2[K];

					SetSpaceForProcess(2,0);
					
					if (NextI < 0 || NextI >= 8 || NextJ < 0 || NextJ >= 8) {
						if (NextJ < 0 || NextJ >= 8) {
							cout << "- , ";
						}
						else {
							cout << getColEq[NextJ] << " , ";
						}
						if (NextI < 0 || NextI >= 8) {
							cout << "-";
						}
						else {
							cout << NextI + 1;
						}
						cout << "\t== INVALID (OUTOFBOUNDS)";
					}
					else {
						cout << getColEq[NextJ] << " , " << NextI + 1;
						if (BOARD[NextI][NextJ] != 0) {
							cout << "\t== INVALID (OCCUPIED)";
						}
						else {
							exits++;
							cout << "\t== " << exits;
						}
					}
					cout << endl;
				}
				SetSpaceForProcess(2, 0);
				EXITS[L] = exits;
			}
			// Find Index with lowest Exits
			int min;
			SetSpaceForProcess(1,2);
			cout << "***Setting Minimum Exit***";
			for (L = 0; L < NPOS; L++) {
				SetSpaceForProcess(1, 0);
				if (L == 0) {
					min = EXITS[L];
					MIN = L;
					cout << min << " > -";
				}
				else {
					cout << min << " > " << EXITS[L];
				}
				if (L == 0 || min > EXITS[L] && EXITS[L] != 0) {
					min = EXITS[L];
					MIN = L;
					cout << "\t= TRUE (Set Array Index " << L << " as Minimum)";
				}
				else {
					cout << "\t= FALSE";
				}
				cout << endl;
			}
			SetSpaceForProcess(1,1);
			cout << "Minimum Exits (" << min << ") at Array Index " << MIN;
		}
		
		// Print Movement Board
		SetSpaceForOutput(0);
		cout << "\t     *****Movement Tracker*****";
		CreateBoard(1, BOARD);
		// Print Possibility Board
		SetSpaceForOutput(20);
		cout << "\t     *****Posibility Finder*****";
		for (int r = 0; r < 8; r++) {
			for (int c = 0; c < 8; c++) {
				if (I == r && J == c) {
					BOARD2[r][c] = 'K';
				}
				else if (BOARD[r][c] != 0) {
					BOARD2[r][c] = 'x';
				}
				else {
					bool isPossible = false;
					for (L = 0; L < NPOS; L++) {
						if (NEXTI[L] == r && NEXTJ[L] == c) {
							BOARD2[r][c] = 49 + L;
							isPossible = true;
						}
					}
					if (!isPossible)
						BOARD2[r][c] = 255;
				}
			}
		}
		CreateBoard(2, BOARD2);

		// Move Knight
		Sleep(500);
		SetSpaceForProcess(1,1);
		cout << "*****Move Knight*****";
		movement[M - 1][0] = I;
		movement[M - 1][1] = J;
		I = NEXTI[MIN];
		J = NEXTJ[MIN];
		movement[M][0] = I;
		movement[M][1] = J;
		SetSpaceForProcess(1,0);
		cout << "Move " << M << " at Coordinates (" << getColEq[J] << " , " << I + 1 << ")";
		BOARD[I][J] = M;

		// Print Final Position
		if (M == 64) {
			ResetScreen();
			// Print Movement Breakdown
			SetSpaceForProcess(2, 2);
			SetSpaceForProcess(1, 2);
			cout << "\t\t\t\t*****Movement Breakdown*****";
			SetSpaceForProcess(2, 1);
			SetSpaceForProcess(1, 1);
			for (int move = 1; move <= 64; move++) {
				if (move >= 33) {
					SetSpaceForProcess(2, 0);
				}
				else {
					SetSpaceForProcess(1, 0);
				}
				cout << "Move " << move << " at Coordinates (" << getColEq[movement[move][1]] << " , " << movement[move][0] + 1 << ")";
			}
			// Print Movement Board
			SetSpaceForOutput(0);
			cout << "\t     *****Movement Tracker*****";
			CreateBoard(1, BOARD);
			// Print Possibility Board
			SetSpaceForOutput(20);
			cout << "\t     *****Posibility Finder*****";
			for (int r = 0; r < 8; r++) {
				for (int c = 0; c < 8; c++) {
					if (I == r && J == c) {
						BOARD2[r][c] = 'K';
					}
					else if (BOARD[r][c] != 0) {
						BOARD2[r][c] = 'x';
					}
					else {
						bool isPossible = false;
						for (L = 0; L < NPOS; L++) {
							if (NEXTI[L] == r && NEXTJ[L] == c) {
								BOARD2[r][c] = 49 + L;
								isPossible = true;
							}
						}
						if (!isPossible)
							BOARD2[r][c] = 255;
					}
				}
			}
			CreateBoard(2, BOARD2);
		}
	}
	return 0;
}

void SetSpaceForProcess(int col, int endlines) {
	if (col == 1) {
		for (int i = 0; i < endlines; i++)
			debugrow++;
		gotoxy(55, debugrow++);
	}
	else {
		for (int i = 0; i < endlines; i++)
			debugrow2++;
		gotoxy(105, debugrow2++);
	}
}

void SetSpaceForOutput(int endlines) {
	for (int i = 0; i < endlines; i++)
		outputrow++;
	gotoxy(0, outputrow++);
}

void CreateBoard(int type, int data[][8]) {
	// Create Raw Board
	cout << endl;
	int grid[18][50] = { {255,255,255,255, 65,255,255,255,255,255, 66,255,255,255,255,255, 67,255,255,255,255,255, 68,255,255,255,255,255, 69,255,255,255,255,255, 70,255,255,255,255,255, 71,255,255,255,255,255, 72,255,255,255},
						 {255,218,196,196,196,196,196,194,196,196,196,196,196,194,196,196,196,196,196,194,196,196,196,196,196,194,196,196,196,196,196,194,196,196,196,196,196,194,196,196,196,196,196,194,196,196,196,196,196,191},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
						 {255,192,196,196,196,196,196,193,196,196,196,196,196,193,196,196,196,196,196,193,196,196,196,196,196,193,196,196,196,196,196,193,196,196,196,196,196,193,196,196,196,196,196,193,196,196,196,196,196,217} };
	// Create Raw Board Raw Content
	int content[2][50] = { {255,179,255,255,255,255,255,179,255,255,255,255,255,179,255,255,255,255,255,179,255,255,255,255,255,179,255,255,255,255,255,179,255,255,255,255,255,179,255,255,255,255,255,179,255,255,255,255,255,179},
						   {255,195,196,196,196,196,196,197,196,196,196,196,196,197,196,196,196,196,196,197,196,196,196,196,196,197,196,196,196,196,196,197,196,196,196,196,196,197,196,196,196,196,196,197,196,196,196,196,196,180} };
	// Set Raw Board Raw Content
	for (int r = 2; r < 17; r++) {
		for (int c = 0; c < 50; c++) {
			if (r % 2 == 0) {
				grid[r][c] = content[0][c];
			}
			else {
				grid[r][c] = content[1][c];
			}
		}
	}
	int rnum = 2, cnum = 4;
	int rcnt = 0, ccnt = 0;
	// Print Board
	for (int r = 0; r < 18; r++) {
		for (int c = 0; c < 50; c++) {
			if (r == rnum && c == 0) {
				// Print Row Number
				cout << rnum - (rnum / 2);
				// Reset Writable Column
				ccnt = 0;
				cnum = 4;
				continue;
			} 
			else if (r == rnum && c == 49) {
				// Set Writable Row
				rcnt++;
				rnum += 2;
			}
			// Write Table
			if (r == rnum && c == cnum) {
				if (type == 1) {
					if (data[rcnt][ccnt] != 0) {
						// Check content length
						int input = data[rcnt][ccnt];
						int intlength = 0;
						while (input > 0) {
							input /= 10;
							intlength++;
						}
						// Remove 1 space to fit content
						if (intlength >= 2) {
							cout << "\b";
						}
						// Write Raw Content
						cout << data[rcnt][ccnt];
					}
					else {
						// Write Table
						cout << (char)grid[r][c];
					}
				}
				else {
					if ((char)data[rcnt][ccnt] != 255) {
						// Write ASCII Content
						cout << (char)data[rcnt][ccnt];
					}
					else {
						// Write Table
						cout << (char)grid[r][c];
					}
				}
				// Set Writable Column
				ccnt++;
				cnum += 6;
			}
			else {
				// Write Table
				cout << (char)grid[r][c];
			}
		}
		cout << endl;
	}
}

void PrintSplash() {
	cout << "              *                                                                 " << endl;
	cout << "*        *      *             * * * * * * *                                     " << endl;
	cout << "*      *        *                   *                                           " << endl;
	cout << "*    *        *                     *                                           " << endl;
	cout << "*  *                                *                                           " << endl;
	cout << "* *                 * * *           *          * *        *     *      *  * *   " << endl;
	cout << "*  *               *                *        *     *      *     *      * *      " << endl;
	cout << "*    *              * * *           *        *     *      *     *      *        " << endl;
	cout << "*      *                 *          *        *     *      *     *      *        " << endl;
	cout << "*        *          * * *           *          * *         * * *       *        " << endl;
	cout << "                                                       BY: JURUEL KEANU LORENZO " << endl;
	cout << endl;
	cout << "A knight's tour is a sequence of moves of a knight on a chessboard such that the knight visits every square only once." << endl;
	cout << endl;
	cout << "Implementing Warnsdorff's Rule:" << endl << endl;
	cout << "Warnsdorff's rule is a heuristic for finding a single knight's tour." << endl
		<< "The knight is moved so that it always proceeds to the square from which the knight will have the fewest onward moves." << endl
		<< "When calculating the number of onward moves for each candidate square, we do not count moves that revisit any square already visited." << endl
		<< "It is possible to have two or more choices for which the number of onward moves is equal; there are various methods for breaking such ties," << endl
		<< "including one devised by Pohl and another by Squirrel and Cull." << endl;
	cout << endl;
}

void ResetScreen() {
	debugrow = 0;
	debugrow2 = 0;
	outputrow = 0;
	Sleep(1000);
	clrscr();
}
