#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	FILE *fp;
	char fname[32] = "kadai02data01.csv";
	int d, ret, n = 0, count = 0, M_num = 0;
	double Ave = 0;

	fp = fopen(fname, "r"); //read modeでopen
	if(fp == NULL) { //失敗
		printf("can't open file, %s!!\n", fname);
		exit(1);
	}
	else printf("Open file, %s!!", fname);

	while(1) {
		ret = fscanf(fp, "%d", &d);
		if (ret != 1) break;
		M_num += d;
		count++;
	}
	Ave = (double)M_num / count;
	printf("%lf", Ave);

	fclose(fp);

	return 0;
}