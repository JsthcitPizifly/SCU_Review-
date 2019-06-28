#include "func.h"
#include <fstream>
#include <string>
#include <iostream>
constexpr auto NUMBER = 256;

void char_code()
{
	HuffTree<char> *HuffmanTree;
	int n = 0;
	char *Code;
	char s[NUMBER] = { '\0' };
	int w[NUMBER] = { 0 };
	if (!Stat(s, w, n))
		return;
	HuffmanTree = HuffManBuild(s, w, n);
	//HuffmanTree->print();
	std::cout << std::endl << "the coding result is :" << std::endl;
	Code = new char[n];
	HuffmanCode(HuffmanTree->root(), Code, -1);
}

void File_code()
{
	HuffTree<char> *HuffmanTree;
	int n = 0;
	char *Code;
	char s[NUMBER] = { '\0' };
	int w[NUMBER] = { 0 };
	if (!Stat(s, w, n))
		return;
	HuffmanTree = HuffManBuild(s, w, n);
}

void File_Decode()
{

}

bool Stat(char *s, int *w, int &num)
{
	std::fstream fstrm;
	std::string fname;
	std::cout << "请输入文件名如(f1.txt):";
	std::cin >> fname;
	fstrm.open(fname);
	if (fstrm.is_open())
		std::cout << "成功打开文件" << std::endl;
	else {
		std::cout << "failed" << std::endl;
		return false;
	}
	char ch ;
	fstrm >> std::noskipws;
	while (!fstrm.eof()) {
		fstrm >> ch;
		w[ch]++;
		s[ch] = ch;
	}
	
	//统计出现的字符数
	for (int i = 0; i < 256; ++i)
		if (w[i] != 0)
			++num;
	//删除s中频度不为0的元素
	for (int i = 0; i < 256; ++i)
		if (s[i] != '\0')
			for (int j = 0; j < 256; ++j) 
				if (s[j] == '\0') {
					char temp;
					temp = s[i];
					s[i] = s[j];
					s[j] = temp;
				}
	return true;
}

HuffTree<char>* HuffManBuild(char * s, int * w, int num)
{
	//s1为小值下标，s2为大值下标
	int s1, s2;
	HuffTree<char> **ttree = new HuffTree<char>* [num];
	HuffTree<char> *temp;
	for (int i = 0; i < num; ++i)
		ttree[i] = new HuffTree<char>(s[i], w[s[i]]);
	do {
		min(s1, s2, ttree, num);
		temp = new HuffTree<char>(ttree[s1], ttree[s2]);
		ttree[s1] = temp;
		Delete(ttree, s2, num);
	} while (num != 1);
	return ttree[0];
}

void HuffmanCode(HuffNode<char>* ht1, char * Code, int length)
{
	char temp_c[100] = { '\0' };
	if (!ht1)
		return;
	if (ht1->isLeaf()) {
		Code[length + 1] = '\0';
		std::cout << "val:" << ht1->val() << std::endl
			<< "weight:" << ht1->weight() << std::endl
			<< "Code:" << Code << std::endl;
		std::cout << std::endl;
		return;
	}

	if (ht1->left() != NULL) {
		int len = length + 1;
		strncpy_s(temp_c, Code, len);
		temp_c[len] = '0';
		HuffmanCode(ht1->left(), temp_c, len);
	}
	if (ht1->right() != NULL) {
		int len = length + 1;
		strncpy_s(temp_c, Code, len);
		temp_c[len] = '1';
		HuffmanCode(ht1->right(), temp_c, len);
	}
	return;
}

void min(int &s1, int &s2, HuffTree<char>* ttree[], const int num)
{
	s1 = 0;
	s2 = 0;
	for (int i = 0; i < num; ++i)
		if (ttree[s1]->weight() > ttree[i]->weight())
			s1 = i;
	for (int i = 0; i < num; ++i)
		if (ttree[s2]->weight() >= ttree[i]->weight() && i != s1)
			s2 = i;
	
	if (num == 2 && s1 == 0)
		s2 = 1;
	else if (num == 2 && s1 == 1)
		s2 = 0;
	return;
}

void Delete(HuffTree<char>* ttree[], int & s2, int & num)
{
	auto t = ttree[s2];
	ttree[s2] = ttree[num - 1];
	ttree[num - 1] = t;
	
	--num;
}



