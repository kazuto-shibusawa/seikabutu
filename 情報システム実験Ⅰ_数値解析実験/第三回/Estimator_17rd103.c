#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define N 500 //Given Data Size
#define IMAX 2

/////////////////////////////////////////////////////////////////////////////
///Functions for Matrices and vectors 
/////////////////////////////////////////////////////////////////////////////
typedef struct{
	double vec[IMAX];
} vector;

typedef struct{
	double mat[IMAX][IMAX];
} matrix;

matrix inverseMatrix(matrix aInv){
	int i,j,k;
	double c,u;
	//double det;
	
	//det = 1;
	//////////////////////////////////////
	//step1
	for(k = 0; k < IMAX; k++){
		c = aInv.mat[k][k];
		//det = c*det;//determinant
		
		for(j = 0; j < IMAX; j++){
			aInv.mat[k][j] = aInv.mat[k][j] / c;
		}
		aInv.mat[k][k] = 1.0 / c;
		
		//====================================
		//step2
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
		}//step2�I���
		//====================================

	}//step1�I���
	//////////////////////////////////////
	
	return aInv;
}


matrix productMatrix(matrix a1, matrix a2){
	int i,j,k;
	matrix a3;
	
	for(i=0;i<IMAX;i++){
		for(j=0;j<IMAX;j++){
			a3.mat[i][j] = 0;
			for(k=0;k<IMAX;k++){
				a3.mat[i][j] = a3.mat[i][j] + a1.mat[i][k]*a2.mat[k][j];
			
			}
		}
	}
	
	return a3;
}

vector productMatrixVector(matrix a, vector x){
	int i,j,k;
	vector y;
	
	for(i=0;i<IMAX;i++){
		y.vec[i] = 0;
		for(j=0;j<IMAX;j++){
				y.vec[i] = y.vec[i] + a.mat[i][j]*x.vec[j];
		}
	}
	
	return y;
}


void printMatrix(FILE *fp, matrix a, int mm, int nn, char *matrixName){
	int i,j;
	printf("Matrix %s\n", matrixName);
	fprintf(fp, "Matrix %s\n", matrixName);
	for(i = 0; i< mm; i++){
		for(j = 0; j< nn; j++){
			printf("%.2f",a.mat[i][j]);
			fprintf(fp,"%f",a.mat[i][j]);
			
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

void printVector(FILE *fp, vector x, int mm, char *vectorName){
	int i,j;
	printf("Vector %s\n", vectorName);
	fprintf(fp, "Vector %s\n", vectorName);

	for(i = 0; i< mm; i++){
		printf("%.2f\n",x.vec[i]);
		fprintf(fp,"%f\n",x.vec[i]);
	}
	printf("\n");	
}

/////////////////////////////////////////////////////////////////////////////
///Functions for Matrices and vectors (END)
/////////////////////////////////////////////////////////////////////////////



						
int main (void){
	char *dirin = "Given_data01.csv";
	char *dirout = "Output_data01_17rd103.csv";
	
	int i;
	double x[N], y[N];
	double Wx=0, Sx=0, Wxy=0, Sy=0, Wy=0;
	
	vector a,w;
	matrix Z,ZInv,E1,E2;

	FILE *fpin;
	FILE *fpout;
	/////////////////////////////////////////////////////////
	//(1. FILE OPEN)/////////////////////////////////////////		
	if ((fpin = fopen(dirin, "r")) == NULL) {
		printf("File Open Error \n");
		exit(1);
	}
	if ((fpout = fopen(dirout, "w")) == NULL) {
		printf("File Open Error \n");
		exit(1);
	}
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	
	
	

	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/*
		
		Write program codes here for the following (1) and (2):

		(1) Input the contens of "Given_data01.csv" to x[i] and y[i].
			
		(2) Calculate Wx, Sx, Wxy, Sy and Wy.  

	*/
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	for (i = 0; i < N; i++) {
		fscanf(fpin, "%lf, %lf", &x[i], &y[i]);
		Wx += x[i] * x[i];
		Sx += x[i];
		Wxy += x[i] * y[i];
		Sy += y[i];
		Wy += y[i] * y[i];
	}
	
	
	
	Z.mat[0][0] = Wx;
	Z.mat[0][1] = Sx;
	Z.mat[1][0] = Sx;	
	Z.mat[1][1] = N;
	
	w.vec[0] = Wxy;
	w.vec[1] = Sy;
		
	//�����o��
	printVector(fpout, w, IMAX, "w");
	printMatrix(fpout, Z, IMAX, IMAX, "Z");
					
	ZInv = inverseMatrix(Z);
	printMatrix(fpout, ZInv, IMAX, IMAX, "Z^-1");
	
	E1 = productMatrix(Z,ZInv);
	printMatrix(fpout, E1, IMAX, IMAX, "ZZ^-1");
	
	E2 = productMatrix(ZInv,Z);
	printMatrix(fpout, E2, IMAX, IMAX, "Z^-1Z");
	
	a = productMatrixVector(ZInv,w);
	printVector(fpout, a, IMAX, "a (Estimated Parameters)");
	
	fprintf(fpout,"\n");
	fprintf(fpout,"x,y,ax+b\n");
	for(i = 0; i< N; i++){
		fprintf(fpout,"%f,%f,%f\n",x[i],y[i], a.vec[0]*x[i]+a.vec[1]);
	}

	/////////////////////////////////////////////////////////
	fclose(fpin);
	fclose(fpout);	//(2. FILE CLOSE)
	/////////////////////////////////////////////////////////
	printf("\nCSV file was made. \n");
	
	return 0;
}
