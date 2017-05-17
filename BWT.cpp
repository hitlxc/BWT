// BWT.cpp : ¶¨Òå¿ØÖÆÌ¨Ó¦ÓÃ³ÌÐòµÄÈë¿Úµã¡£
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

char BWTMatrix[MAX][MAX]; //BWT¾ØÕó
char order[MAX]; //¼ÇÂ¼Ë³Ðò
map<char, int> siteMapFrom;//¼ÇÂ¼BWTÐòÁÐÖÐÃ¿¸ö×Ö·û³öÏÖµÄÎ»ÖÃ
char BWTSeq[MAX];
map<char, int> siteMapTo;
map<char, int> OccFlag[MAX];


int compare(const void *a, const void *b)
{
	return strcmp((char *)a, (char *)b);
	//return strcmp(*(char **)a, *(char **)b);   Õë¶Ôchar *str[8]µÄÐ´·¨
}

//×Ö·û´®chÑ­»·ÓÒÒÆstepsÎ»
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

//²éÑ¯siteÎ»µãÇ°£¨°üº¬site£¬´Ó0¿ªÊý£©ÓÐ¶àÉÙ¸öbase¼î»ù
int OccSearch(char base, int site) {
	int num = OccFlag[ (site-1) / occStep ][base];
	cout << "site , base , site / occStep * occStep : " << site << " " << base << " " << site / occStep * occStep << endl;
	cout << site-1 / occStep * occStep << "Ç°ÓÐ¶àÉÙ¸ö" << base << " : " << num <<endl;
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
	cout <<"Ä¸´®³¤¶È:"<< len<<endl;
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
	/*¹¹½¨BWT¾ØÕóºÍBWTÐòÁÐ*/

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
		cout << "Ã»²éµ½" << endl;
	}

	for (int i = from; i < to; i++) {
		cout << "ÔÚÔ­ÐòÁÐµÄµÚ " << len - order[i] << " Î»"<< endl;
	}

	system("pause");
    return 0;
}

