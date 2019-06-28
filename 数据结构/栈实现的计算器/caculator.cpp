// caculator.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "FUNC.H"
#include <math.h>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;



int main()
{
	char choi = 'Y';
	while (choi == 'Y') {
		UI();
		LStack<double> OPND; //操作数栈定义
		LStack<char> OPTR;	//操作符栈定义

		char ch;			//存放表达式的每一个字符
		char prior_char;
		double operand;
		char OPTR_top;
		double res = 0;
		double x, y;
		char optr_n;		//用于处理弹出的操作符栈内最上面元素 


		OPTR.push('=');
		prior_char = '=';
		OPTR.topValue(OPTR_top);
		GetNextchar(ch);
		while (ch != '=' || OPTR_top != '=') {
			if (isdigit(ch) || ch == '.') {
				std::cin.putback(ch);
				std::cin >> operand;
				OPND.push(operand);
				prior_char = '0';
				GetNextchar(ch);
			}
			else if (!IsOperator(ch)) {
				pos(4, 10);
				std::cerr << "表达式中出现非法字符" << std::endl;
				pos(4, 11);
				system("pause");
				exit(1);
			}
			else if (IsOperator(ch)) {
				if ((prior_char == '=' || prior_char == '(') && (ch == '+' || ch == '-'))
					OPND.push(0);
				//如果栈内优先级低于栈外优先级
				if (isp(OPTR_top) < osp(ch)) {
					OPTR.push(ch);
					OPTR.topValue(OPTR_top);
					prior_char = ch;
					GetNextchar(ch);
				}
				else if (isp(OPTR_top) > osp(ch)) {
					if (Get2Operands(OPND, x, y)) {
						OPTR.pop(optr_n);
						cal(optr_n, x, y, res);
						OPND.push(res);
						OPTR.topValue(OPTR_top);
						res = 0;
					}

				}
				else {
					OPTR.pop(prior_char);
					GetNextchar(ch);
				}
			}
			else {
				pos(4, 10);
				std::cerr << "表达式错误" << std::endl;
				pos(4, 11);
				system("pause");
				exit(1);
			}
		}

		OPND.pop(res);
		pos(4, 10);
		std::cout << res << std::endl;
		pos(4, 11);

		std::cout << "是否继续<Y/N>:";
		std::cin >> choi;
		while (choi != 'Y' && choi != 'N') {
			std::cout << "是否继续<Y/N>:";
			std::cin >> choi;
		}
	}
}
