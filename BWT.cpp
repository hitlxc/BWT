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


char seq[MAX] = "ACGTGATTA$";
char seqSon[MAX] = "GTG";

char BWTMatrix[MAX][MAX]; //BWT矩阵
char order[MAX]; //记录顺序
map<char, int> siteMapFrom;//记录BWT序列中每个字符出现的位置
char BWTSeq[MAX];
map<char, int> siteMapTo;
map<char, int> OccFlag[MAX];


int compare(const void *a, const void *b)
{
	return strcmp((char *)a, (char *)b);
	//return strcmp(*(char **)a, *(char **)b);   针对char *str[8]的写法
}

//字符串ch循环右移steps位
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

//查询site位点前（包含site，从0开数）有多少个base碱基
int OccSearch(char base, int site) {
	int num = OccFlag[ (site-1) / occStep ][base];
	cout << "site , base , site / occStep * occStep : " << site << " " << base << " " << site / occStep * occStep << endl;
	cout << site-1 / occStep * occStep << "前有多少个" << base << " : " << num <<endl;
	for (int i = (site-1 )/ occStep * occStep+1; i < site;i++) {
		if (BWTSeq[i] == base) {
			num++;
		}
	}
	return num;
}

void setBWT() {
	int numA = 0, numT = 0, numG = 0, numC = 0;
	int len = strlen(seq);
	for (int i = 0; i < len; i++) {
		order[i] = BWTMatrix[i][len];
		BWTSeq[i] = BWTMatrix[i][len - 1];
		if (siteMapFrom.find(BWTMatrix[i][0]) == siteMapFrom.end()) {
			siteMapFrom[BWTMatrix[i][0]] = i;
			if (i > 0) {
				siteMapTo[BWTMatrix[i - 1][0]] = i - 1;
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
		if (i%occStep == 0) {
			OccFlag[i / occStep]['A'] = numA;
			OccFlag[i / occStep]['T'] = numT;
			OccFlag[i / occStep]['G'] = numG;
			OccFlag[i / occStep]['C'] = numC;
		}
	}
	siteMapTo['T'] = len - 1;
}

int main()
{
	//cin >> seq;
	int len = strlen(seq);
	cout <<"母串长度:"<< len<<endl;
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

	setBWT();
	

	int lenSon = strlen(seqSon);
	int from = siteMapFrom[seqSon[lenSon-1]];
	int to = siteMapTo[seqSon[lenSon-1]];
	//cout << OccSearch('A', 5) <<endl;
	/*cout << OccSearch('A', 1) << endl;
	cout << OccSearch('C', 5) << endl;
	cout << OccSearch('G', 5) << endl;
	cout << OccSearch('T', 5) << endl;
	cout << OccSearch('A', 7) << endl;
	cout << OccSearch('C', 7) << endl;*/

	int step = lenSon-1;
	while (  step-- ) {
		/*cout << "from to :" << from << to << endl;
		cout << seqSon[step] << endl;
		cout << OccSearch(seqSon[step], from) << "    " << siteMapFrom[seqSon[step]] << endl;
		
		cout << OccSearch(seqSon[step], to) << "    " << siteMapFrom[seqSon[step]] << endl;*/

		from = OccSearch(seqSon[step], from) + siteMapFrom[seqSon[step]];
		to = OccSearch(seqSon[step], to) + siteMapFrom[seqSon[step]];
		if (from >= to) break;
	}

	if (from > to - 1) {
		cout << "没查到" << endl;
	}

	for (int i = from; i < to; i++) {
		cout << "在原序列的第 " << len - order[i] << " 位"<< endl;
	}

	system("pause");
    return 0;
}

