// BWT.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <map>

#define MAX 1000
#define occStep 3

using namespace std;

int compare(const void *a, const void *b)
{
	return strcmp((char *)a, (char *)b);
	//return strcmp(*(char **)a, *(char **)b);   针对char *str[8]的写法
}

void loopMove(char *ch, int steps)
{
	char temp[MAX];
	char*p;
	int n = strlen(ch) - steps;
	p = ch + n;
	memcpy(temp, p, steps);
	memcpy(temp + steps, ch, n);
	memcpy(ch, temp, strlen(ch));
}

char BWTMatrix[MAX][MAX]; //BWT矩阵
char order[MAX]; //记录顺序
map<char, int> siteMapFrom;//记录BWT序列中每个字符出现的位置
char BWTSeq[MAX]; 
map<char, int> siteMapTo;
map<char, int> OccFlag[MAX];

int main()
{
	char seq[MAX] = "ACGTGATTA$";
	//seq = new char[MAX];
	char seqSon[MAX] = "CGT";
	//cin >> seq;
	//seq = "ACGTTA\0";
	int len = strlen(seq);
	cout << len;
	for (int i = 0; i < strlen(seq); i++) {
		memcpy(BWTMatrix[i], seq, strlen(seq));
		loopMove(seq, 1);
		BWTMatrix[i][len] = '0'+i;
	}
	//cout << seq << endl;

	//char *str[8] = { "ACGTTA$","CGTTA$A","GTTA$AC","TTA$ACG","TA$ACGT","A$ACGTT","$ACGTTA" };
	//qsort(str, 7, sizeof(str[0]), compare);
	/*cout << sizeof(bwtmatrix[0]) << endl;
	cout << strlen(bwtmatrix[0]) << endl;
	cout << sizeof(str[0]) << endl;
	cout << strlen(str[0]) << endl;
	cout << str[0] << endl;*/
	//qsort(str, 7, 8, compare);
	qsort(&BWTMatrix, len, MAX, compare);
	/*构建BWT矩阵和BWT序列*/

	
	int numA = 0, numT = 0, numG = 0, numC = 0;
	for (int i = 0; i < len; i++) {
		order[i] = BWTMatrix[i][len];
		BWTSeq[i] = BWTMatrix[i][len-1];
		if (siteMapFrom.find(BWTMatrix[i][0]) == siteMapFrom.end()) {
			siteMapFrom[BWTMatrix[i][0]] = i;
			if (i > 0) {
				siteMapTo[BWTMatrix[i-1][0]] = i-1;
			}
		}
		switch (BWTSeq[i])
		{
		case 'A':
			numA++;
			break;
		case 'T':
			numT++;
			break;
		case 'G':
			numG++;
			break;
		case 'C':
			numC++;
			break;
		default:
			break;
		}
		cout << numA << numT << numG << numC << endl;
		if (i%occStep) {
			OccFlag[i / occStep]['A'] = numA;
			OccFlag[i / occStep]['T'] = numT;
			OccFlag[i / occStep]['G'] = numG;
			OccFlag[i / occStep]['C'] = numC;
		}
	}
	siteMapTo['T'] = len - 1;

	int lenSon = strlen(seqSon);
	int from = siteMapFrom[seqSon[lenSon]];
	int to = siteMapTo[seqSon[lenSon]];
	while (  --lenSon ) {
		
	}

	system("pause");
    return 0;
}

