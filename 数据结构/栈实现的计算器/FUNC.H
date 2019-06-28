#pragma once
#include "LSTACK.H"
//获取并返回操作符的栈内优先级
int isp(char ch);
//获取并返回操作符的栈外优先级
int osp(char ch);
//计算r = x op y, 计算成功 返回true
bool cal(char op, double x, double y, double &r);
//从输入的表达式中获取一个字符
void GetNextchar(char &ch);
//判断是否为数字0-9
bool isdigit(char ch);
//判断ch是否为操作符
bool IsOperator(char ch);
//从操作栈中取两个操作符
bool Get2Operands(LStack<double>&opnd, double &x, double &y);
//UI界面
void UI();
//移动光标
void pos(int x, int y);