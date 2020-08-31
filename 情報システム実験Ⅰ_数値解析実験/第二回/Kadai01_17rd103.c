#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IMAX 3

typedef struct{
	double mat[IMAX][IMAX];
} matrix;

matrix inverseMatrix(matrix aInv){
	int i,j,k;
	double c,u;
	//double det;
	
	//det = 1;
	//////////////////////////////////////
	//step 2(a)
	for(k = 0; k < IMAX; k++){
		c = aInv.mat[k][k];
		//det = c*det;//determinant
		
		for(j = 0; j < IMAX; j++){
			aInv.mat[k][j] = aInv.mat[k][j] / c;
		}
		aInv.mat[k][k] = 1.0 / c;
		
		//====================================
		//step 2(b)
		for(i = 0; i < IMAX; i++){
		  if( i != k ){
			u = aInv.mat[i][k];
			for(j = 0; j < IMAX; j++){
			  if( j != k ){
			     aInv.mat[i][j]=aInv.mat[i][j]-aInv.mat[k][j]*u;
			  }else{
				 aInv.mat[i][j] = -u/c;
			  }					
			}
		  }
		}//step 2(b) End
		//====================================

	}//step 2(a) End
	//////////////////////////////////////
	
	return aInv;
}

matrix square_matrix_multiplication(matrix x, matrix y, matrix multipli) {
	int i, j, k;

	for (k = 0; k < IMAX; k++) {
		for (j = 0; j < IMAX; j++) {
			for (i = 0; i < IMAX; i++) {
				multipli.mat[k][j] += x.mat[k][i] * y.mat[i][j];
			}
		}
	}
	return multipli;
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
void printMatrix(FILE *fp, matrix a, int mm, int nn, char *matrixName){
	int i,j;

	printf("Matrix %s\n", matrixName);
	fprintf(fp, "Matrix %s\n", matrixName);

	for(i = 0; i< mm; i++){
		for(j = 0; j< nn; j++){
			printf("%.2f",a.mat[i][j]);
			fprintf(fp,"%.2f",a.mat[i][j]);
			if(j==nn-1){ 
				printf("\n");
				fprintf(fp,"\n");
			}else{
				printf("\t");
				fprintf(fp,",");
			}
		}
	}
	printf("\n");	
}
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

int main (void){
	char *dir = "InverseMatrix01data01.csv";
	int i,j;
	double vector_b[IMAX] = {0, -2, 1}, vector_x[3];
	matrix a ={2,1,3,
	           4,5,4,
	           3,1,5};
	matrix aInv;
	matrix multipli;
	FILE *fp;

	/////////////////////////////////////////////////////////
	//(1. FILE OPEN)/////////////////////////////////////////

	if ((fp = fopen(dir, "w")) == NULL) {
		printf("File Open Error \n");
		exit(1);
	}
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	printf("Vector b\n");
	fprintf(fp,"Vector b\n");
	for (i = 0; i < IMAX; i++) {
		printf("%.2f\n", vector_b[i]);
		fprintf(fp,"%.2f\n", vector_b[i]);
	}
	printf("\n");
	printMatrix(fp, a, IMAX, IMAX, "A");
					
	aInv = inverseMatrix(a);
	printMatrix(fp, aInv, IMAX, IMAX, "A^-1");
	multipli = square_matrix_multiplication(a, aInv, multipli);
	printMatrix(fp, multipli, IMAX, IMAX, "AA^-1");
	multipli = square_matrix_multiplication(aInv, a, multipli);
	printMatrix(fp, multipli, IMAX, IMAX, "A^-1A");
	printf("Vector x\n");
	fprintf(fp,"%s\n","Vector x");
	for (i = 0; i < IMAX; i++) {
		for (j = 0; j < IMAX; j++) {
			vector_x[i] += aInv.mat[i][j] * vector_b[j];
		}
		printf("%.2f\n", vector_x[i]);
		fprintf(fp, "%.2f\n", vector_x[i]);
	}

	/////////////////////////////////////////////////////////
	fclose(fp);	//(2. FILE CLOSE)
	/////////////////////////////////////////////////////////	
	return 0;
}
