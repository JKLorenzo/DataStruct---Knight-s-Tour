#include<dos.h>
#include<windows.h>
#define MAXSTACK 100
#define FOREVER TRUE
#define MAXQUEUE 200

using namespace std;

// start stack
struct myStack {
	int tos;
	char s[MAXSTACK];
};

struct myQueue
{
	int head;
	int tail;
	char q[MAXQUEUE];
};

void createS(myStack& S) {

	S.tos = -1;
}

void pushS(myStack& S, char item)
{
	S.s[++S.tos] = item;
}
char popS(myStack& S)
{
	return(S.s[S.tos--]);
}
bool isFullS(myStack S)
{
	if (S.tos == MAXSTACK - 1)
		return(true);
	return false;
}
bool isEmptyS(myStack S) {
	if (S.tos == -1)
		return true;
	return false;
}
//end of stack
void createQ(myQueue& Q) {
	Q.head = 0;
	Q.tail = 0;
}
void addQ(myQueue& Q, char item) {
	Q.q[Q.tail++] = item;
	Q.tail %= MAXQUEUE;
}

char retrieveQ(myQueue& Q) {
	char temp;
	temp = Q.q[Q.head++];
	Q.head %= MAXQUEUE;
	return(temp);
}

bool isFullQ(myQueue& Q) {
	if (Q.tail == Q.head)
		return(true);
	return false;
}

bool isEmptyQ(myQueue Q) {
	if (Q.tail == Q.head)
		return(true);
	return false;
}

void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clrscr() {
	system("CLS");
}

