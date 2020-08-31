#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main (void){
	char *dir = "Kadai_17RD103_data01.csv";
		
	/////////////////////////////////////////////////////////
	//(1. FILE OPEN)/////////////////////////////////////////
	FILE *fp;
	if ((fp = fopen(dir, "w")) == NULL) {
		printf("File Open Error \n");
		exit(1);
	}
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	
	int i, j;
	double A[3][3] = {{1.0, 3.0, 8.0},
					  {5.0, 3.0, 1.0},
					  {4.0, 4.0, 1.0}};
	
	double x[3] = {10.0, 5.0, 6.0};
	double y[3];

	printf("Vector x\n");
	for (i = 0; i < 3; i++) {
		printf("%f\n", x[i]);
	}

	fprintf(fp,"%s\n","Vector x");
	for (i = 0; i < 3; i++) {
		fprintf(fp, "%f\n", x[i]);
	}

	printf("\nMatrix A\n");
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			printf("%f", A[i][j]);
			if (j == 2) {
				printf("\n");
			} else {
				printf(", ");
			}
		}
	}

	fprintf(fp,"%s\n","Matrix A");
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			fprintf(fp, "%f", A[i][j]);
			if (j == 2) {
				fprintf(fp,"\n");
			} else {
				fprintf(fp,", ");
			}
		}
	}
	
	printf("\nVector y\n");
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			y[i] += A[i][j] * x[j];
		}
	}

	for(i=0; i<3; i++){
		printf("%f\n",y[i]);
	}

	fprintf(fp,"%s\n","Vector y");
	for (i = 0; i < 3; i++) {
		fprintf(fp, "%f\n", y[i]);
	}

	
	/////////////////////////////////////////////////////////
	fclose(fp);	//(2. FILE CLOSE)
	/////////////////////////////////////////////////////////
	
	return 0;
}
