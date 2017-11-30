#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 
#include <io.h>

struct inform
{
	char name[260];
	int numOfTarget;
	int length;
	float density;
};

int pi[10000] = { 0 };
int getSize(char str[])
{
	int size = 0;
	while (str[size] != '\0')
	{
		size++;
	}
	return size;
}
void getPi(char str[])
{
	int size = getSize(str);
	int begin = 1, match = 0;
	while (begin + match < size)
	{
		if (str[begin + match] == str[match])
		{
			++match;
			pi[begin + match - 1] = match;
		}
		else
		{
			if (match == 0)
				++begin;
			else {
				begin += match - pi[match - 1];
				match = pi[match - 1];
			}
		}
	}
}
int KMP(char str[], char target[])
{
	int ans = 0;
	int strSize = getSize(str), targetSize=getSize(target),j = 0; 
	getPi(target);
	for (int i = 0; i < strSize; i++)
	{
		while (j > 0 && str[i] != target[j])
			j = pi[j - 1];
		if (str[i] == target[j])
		{
			if (j == targetSize - 1)
			{
				ans++;
				j = pi[j];
			}
			else
				j++;
		}
	}
	return ans;
}

void swap(inform* a, inform* b) {
	inform tmp = *a;
	*a = *b;
	*b = tmp;
}


void quick_sort1(inform* array, int start, int end) {

	if (start >= end) return;

	int mid = (start + end) / 2;
	float pivot = array[mid].numOfTarget;

	swap(&array[start], &array[mid]);

	int p = start + 1, q = end;

	while (1) {
		while (array[p].numOfTarget >= pivot) { p++; }
		while (array[q].numOfTarget<pivot) { q--; }

		if (p>q) break;

		swap(&array[p], &array[q]);
	}
	swap(&array[start], &array[q]);
	quick_sort1(array, start, q - 1);
	quick_sort1(array, q + 1, end);
}
void quick_sort2(inform* array, int start, int end) {

	if (start >= end) return;

	int mid = (start + end) / 2;
	float pivot = array[mid].density;

	swap(&array[start], &array[mid]);

	int p = start + 1, q = end;

	while (1) {
		while (array[p].density >= pivot) { p++; }
		while (array[q].density<pivot) { q--; }

		if (p>q) break;

		swap(&array[p], &array[q]);
	}
	swap(&array[start], &array[q]);
	quick_sort2(array, start, q - 1);
	quick_sort2(array, q + 1, end);
}



inform inf[10000];
int main(void) {
	printf("단어검색 프로그램\n디지털이미징 전공\n20135730\n최승우\n\n");
	char target[50] = "";
	printf("검색할 단어를 입력하시오 : ");
	scanf("%s", target);
	for (int i = 0; target[i] != '\0'; i++)
	{
		if (target[i] >= 'A'&&target[i] <= 'Z')
			target[i] -= ('A' - 'a');
	}
	_finddatai64_t findFile;
	FILE *fp;
	int hFile;
	char path[] = "*.txt";
	char content[10000];
	char c;
	int idx,fileNum;
	int mode;
	

	if ((hFile = _findfirsti64(path, &findFile)) == -1L) {
		switch (errno) {
		case 2:
			printf("파일이 없습니다.\n"); break;
		case 22:
			printf("잘못된 경로입니다.\n"); exit(1); break;
		case 12:
			printf("파일 이름이 너무 깁니다.\n"); exit(1); break;
		default:
			printf("알 수 없는 오류입니다.\n"); exit(1); break;
		}
	} 
	else {
		printf("--------------------------------파일 목록--------------------------------\n");
		fileNum = 0;
		do {
			
			idx = 0;
			for(idx=0; findFile.name[idx]!=NULL;idx++)
				inf[fileNum].name[idx] = findFile.name[idx];
			
			idx = 0;

			fp = fopen(findFile.name, "r");
			if (fp == NULL)
			{
				printf("파일 오픈 불가\n");
				fclose(fp);
			}
			while ((c = getc(fp)) != EOF) {
				if (c >= 'A'&&c <= 'Z')
					c -= ('A' - 'a');
				content[idx++] = c;
			}
			content[idx] = '\0';
			inf[fileNum].numOfTarget = KMP(content, target);
			inf[fileNum].length = getSize(content);
			inf[fileNum].density = inf[fileNum].numOfTarget / (float)inf[fileNum].length;
			fclose(fp);
			fileNum++;
		} while (_findnexti64(hFile, &findFile) == 0);
		_findclose(hFile); 

	} 
	printf("순번\t파일 이름\t\t\t횟수\t\t파일의 길이\t\t빈도\n");

	for (int i = 0; i < fileNum; i++)
	{
		printf("%4d", i + 1);
		printf("%20s\t\t", inf[i].name);
		printf("%d\t\t", inf[i].numOfTarget);
		printf("%d\t\t", inf[i].length);
		printf("%15f\t\t\n", inf[i].density);
	}

	printf("전체 파일 갯수 : %d\n", fileNum);
	while (1) {
		printf("\n\n------------------------모드를 선택하시오.------------------------\n1 - 단어의 횟수 2 - 단어의 빈도\n");
		scanf("%d", &mode);
		if (mode == 1)
		{
			quick_sort1(inf, 0, fileNum - 1);
			break;
		}
		else if (mode == 2)
		{
			quick_sort2(inf, 0, fileNum - 1);
			break;
		}
		else
			printf("잘못된 입력입니다.\n");
	}
	printf("--------------------------------정렬 결과--------------------------------\n");
	printf("순위\t파일 이름\t\t\t횟수\t\t파일의 길이\t\t빈도\n");
	for (int i = 0; i < fileNum; i++)
	{
		printf("%4d", i + 1);
		printf("%20s\t\t", inf[i].name);
		printf("%d\t\t", inf[i].numOfTarget);
		printf("%d\t\t", inf[i].length);
		printf("%15f\t\t\n", inf[i].density);
	}





	return 0;
}