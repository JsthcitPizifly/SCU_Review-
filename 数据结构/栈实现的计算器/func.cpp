#include "FUNC.H"
#include <math.h>
#include <string>
#include <sstream>
#include <iostream>
#include <Windows.h>

using namespace std;

int isp(char ch) {
	switch (ch) {
	case'=': 
		return 0; 
	case'+':
	case'-': 
		return 3; 
	case'*':
	case'/':
	case'%': 
		return 5; 
	case'(': 
		return 1; 
	case')': 
		return 8; 
	case'^':
	case'&': 
		return 7; 
	default: 
		return 0;
	}
}
int osp(char ch) {
	switch (ch) {
	case'=': 
		return 0;
	case'+':
	case'-': 
		return 2;
	case'*':
	case'/':
	case'%': 
		return 4; 
	case'(': 
		return 8; 
	case')': 
		return 1; 
	case'^':
	case'&': 
		return 6; 
	default: 
		return 0;
	}
}
bool cal(char op, double x, double y, double & r)
{
	if (!IsOperator(op))
		return false;

	switch (op) {
	case '+':
		r = x + y;
		break;
	case '*':
		r = x * y;
		break;
	case '-':
		r = y - x;
		break;
	case '/':
		r = y / x;
		break;
	case '^':
		r = pow(y, x);
		break;
	case '&':
		r = pow(y, 1.0 / x);
		break;
	case '%':
		r = int(x) % int(y);
		break;
	default :
		return false;
	}

	return true;
}
void GetNextchar(char &ch)
{
	cin >> ch;
}
bool isdigit(char ch)
{
	if (ch >= '0' && ch <= '9')
		return true;
	return false;
}
bool IsOperator(char ch)
{
	switch (ch) {
	case '+':
	case '-':
	case '*':
	case '/':
	case '^':
	case '&':
	case '%':
	case '=':
	case '(':
	case ')':
		return true;
	}
	return false;
}
bool Get2Operands(LStack<double>& opnd  , double & x , double & y)
{
	if (opnd.pop(x) && opnd.pop(y))
		return true;
	return false;
}
//UI
void pos(int x, int y)
{
	COORD posPoint = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), posPoint);
}
void UI()
{
	system("cls");
	system("color F0");
	system("mode con cols=65 lines=25");
	pos(2, 1);
	cout << "=======================��ӭʹ�ü�����======================" << endl;
	pos(2, 20);
	cout << "===========================================================" << endl;
	for (int i = 1, j = 2; j < 20; j++)
	{
		pos(i, j);
		cout << "�U";
	}
	for (int i = 60, j = 2; j < 20; j++)
	{
		pos(i, j);
		cout << "�U";
	}
	pos(4, 3);
	cout << "ʹ��˵��:" << endl;
	pos(4, 4);
	cout << "���ʽ�ɰ���:" << endl;
	pos(4, 5);
	cout << "1.��+ ��- ��* ��/ ��ģ�� ����& �˷�^" << endl;
	pos(4, 6);
	cout << "2.����" << endl;
	pos(4, 8);
	cout << "��������ʽ���ԡ�=���Ž���:" << endl;
	pos(4, 9);
}
