#pragma once
#include "HuffTree.h"
#include <iostream>
//ͳ�������ļ����ַ�Ƶ�Ȳ����ַ������벢������ļ�
void char_code();
//�������ļ����벢�����������浽һ���������ļ�
void File_code();
////�ļ�����
void File_Decode();
//�����ı��ļ���ͳ��Ƶ�Ȳ�Ϊ0���ַ�������ӦƵ�ȼ�w ������num
bool Stat(char *s, int *w, int &num);
//�����ַ�������ӦƵ�Ⱥ͸���num������������
HuffTree<char> *HuffManBuild(char *s, int *w, int num);
//�ӹ����õ�huffman���ĸ���ʼ�Ը���Ҷ�ӽڵ���벢���������
void HuffmanCode(HuffNode<char> *ht1, char *Code, int length);
//��ttree��ѡ��Ȩֵ��С������Ԫ�أ������±�Ϊs1, s2
void min(int &s1, int &s2, HuffTree<char> *ttree[], const int num);
//��ttree��ɾ���±�Ϊmax(s1, s2)��Ԫ��
void Delete(HuffTree<char> *ttree[], int &s2, int &num);