#pragma once
#include "HuffTree.h"
#include <iostream>
//统计输入文件的字符频度并对字符集编码并输出到文件
void char_code();
//对整个文件编码并将编码结果保存到一个二进制文件
void File_code();
////文件解码
void File_Decode();
//读入文本文件并统计频度不为0的字符集，相应频度集w 及个数num
bool Stat(char *s, int *w, int &num);
//利用字符集，相应频度和个数num构建哈夫曼树
HuffTree<char> *HuffManBuild(char *s, int *w, int num);
//从构建好的huffman树的根开始对各个叶子节点编码并输出编码结果
void HuffmanCode(HuffNode<char> *ht1, char *Code, int length);
//从ttree中选择权值最小的两个元素，令其下标为s1, s2
void min(int &s1, int &s2, HuffTree<char> *ttree[], const int num);
//从ttree中删除下标为max(s1, s2)的元素
void Delete(HuffTree<char> *ttree[], int &s2, int &num);