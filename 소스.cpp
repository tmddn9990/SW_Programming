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
	int strSize = getSize(str), targetSize = getSize(target), j = 0;
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

void quick_sort1(inform* arr, int left, int right)
{
	int i, j;
	inform temp;
	int pivot = arr[left].numOfTarget;
	if (left < right)
	{
		i = left;
		j = right + 1;
		while (i <= j)
		{
			do
				i++;
			while (arr[i].numOfTarget > pivot);
			do j--;
			while (arr[j].numOfTarget < pivot);
			if (i < j)
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
			else
				break;
		}
		temp = arr[j];
		arr[j] = arr[left];
		arr[left] = temp;
		quick_sort1(arr, left, j - 1);
		quick_sort1(arr, j + 1, right);
	}
}
void quick_sort2(inform* arr, int left, int right) {
	int i, j;
	inform temp;
	float pivot = arr[left].density;
	if (left < right) {
		i = left;
		j = right + 1;
		while (i <= j) {
			do	i++;
			while (arr[i].density > pivot);
			do  j--;
			while (arr[j].density < pivot);
			if (i < j) {
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
			else
				break;
		}
		temp = arr[j];
		arr[j] = arr[left];
		arr[left] = temp;
		quick_sort2(arr, left, j - 1);
		quick_sort2(arr, j + 1, right);
	}
}


inform inf[1000];
int main(void) {
	printf("�ܾ�˻� ���α׷�\n�������̹�¡ ����\n20135730\n�ֽ¿�\n\n");
	char target[50] = "";
	printf("�˻��� �ܾ �Է��Ͻÿ� : ");
	scanf("%s", target);
	for (int i = 0; target[i] != '\0'; i++)
	{
		if (target[i] >= 'A'&&target[i] <= 'Z')
			target[i] -= ('A' - 'a');
	}
	_finddatai64_t findFile;
	FILE *fp;
	int hFile;
	char path[] = "C://dataset/";
	char path2[1000];
	char path3[1000];
	sprintf_s(path2, "%s*.txt", path);
	char content[10000];
	char c;
	int idx, fileNum, targetNum = 0;
	char mode;


	if ((hFile = _findfirsti64(path2, &findFile)) == -1L) 
	{
		switch (errno) 
		{
		case 2:
		printf("������ �����ϴ�.\n"); break;
		case 22:
		printf("�߸��� ����Դϴ�.\n"); exit(1); break;
		case 12:
		printf("���� �̸��� �ʹ� ��ϴ�.\n"); exit(1); break;
		default:
		printf("�� �� ���� �����Դϴ�.\n"); exit(1); break;
		}
	}
	else {
	printf("--------------------------------���� ���--------------------------------\n");
	fileNum = 0;
	do {

		idx = 0;
		for (idx = 0; findFile.name[idx] != NULL; idx++)
			inf[fileNum].name[idx] = findFile.name[idx];

		idx = 0;
		sprintf_s(path3, "C://dataset/%s", findFile.name);
		fp = fopen(path3, "r");
		if (fp == NULL)
		{
			printf("���� ���� �Ұ�\n");
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
	printf("����\t���� �̸�\t\t\tȽ��\t\t������ ����\t\t��\n");

	for (int i = 0; i < fileNum; i++)
	{
		if (inf[i].numOfTarget > 0) {
			targetNum++;
			printf("%4d", i + 1);
			printf("%20s\t\t", inf[i].name);
			printf("%d\t\t", inf[i].numOfTarget);
			printf("%d\t\t", inf[i].length);
			printf("%15f\t\t\n", inf[i].density);

		}
	}
	printf("��ü ���� ���� : %d\n", fileNum);
	printf("ã�� ���� ���� : %d\n", targetNum);
	while (1) {
		printf("\n\n------------------------��带 �����Ͻÿ�.------------------------\n1 - �ܾ��� Ƚ�� 2 - �ܾ��� �� 3 - ���α׷� ����\n");
		getchar();
		scanf("%c", &mode);
		if (mode == '1')
		{
			quick_sort1(inf, 0, fileNum - 1);

		}
		else if (mode == '2')
		{
			quick_sort2(inf, 0, fileNum - 1);
		}
		else if (mode == '3')
		{
			printf("���α׷��� �����մϴ�.\n");
			return 0;
		}
		else
		{
			printf("�߸��� �Է��Դϴ�.\n");
			continue;
		}
		printf("--------------------------------���� ���--------------------------------\n");
		printf("����\t���� �̸�\t\t\tȽ��\t\t������ ����\t\t��\n");
		for (int i = 0; i < fileNum; i++)
		{
			if (inf[i].numOfTarget > 0) {
				printf("%4d", i + 1);
				printf("%20s\t\t", inf[i].name);
				printf("%d\t\t", inf[i].numOfTarget);
				printf("%d\t\t", inf[i].length);
				printf("%15f\t\t\n", inf[i].density);
			}
		}

	}






	return 0;
}