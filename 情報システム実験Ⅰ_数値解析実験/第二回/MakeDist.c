#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//<使い方>
//
//①　セル(1,1) から縦に１列分のデータを並べたcsv形式の入力ファイルを用意する．
//
//②　以下のパラメータを適切に設定する．

#define XMAX 5.0		//x軸の値の配列の最大値
#define XMIN -5.0		//x軸の値の配列の最小値
#define DX 0.1			//x軸の値の配列，区間配列(y[])の差分

#define NMAX 120		//x軸の値(ラベル)の配列(x[])の最大数
						//配列サイズを定義するための定数
						//
						// Nmax ≒ (生データのサイズ)/100 以下程度
						//
						//区間配列の個数(N ≦ Nmax)
						//int N = (int)((xmax -xmin)/dx + 1);\
						//でNが定義されるので，Nmaxを N ≦ Nmax となるよう定める．
						
						
//③　MakeDist.cをコンパイルして実行する．
//
//④　以下のようなExcelのFrequency関数に準じた形式で，
//    データのヒストグラムから得られる確率密度分布が出力される．
//    また，データの平均，分散から得られる正規分布pdfがf(x)として出力される．
/*-----------------------
配列yの個数：N+1
配列xの個数：N

y[i] < y[i-1]
Count[i-1] (y[i] < data ≦ y[i-1]なるdataの数)

-------------------------
y[0]
	x[0]	Count[0]	Dist[0]
y[1]
…
y[i-1]
	x[i-1]	Count[i-1]	Dist[i-1]
y[i]
…
y[N-1]
	x[N-1]	Count[N-1]	Dist[N-1]
y[N]

(N ≦ Nmax)
------------------------
*/
						
int main (void){
	char *dirin = "GaussianRandomNumbers02.csv";
	char *dirout = "Kadai_Dist_data02.csv";

	int i;
	
	//区間配列の個数(N ≦ Nmax)
	int N = (int)((XMAX -XMIN)/DX + 1);
	
	//変数の定義
	double y[NMAX+1];
	double x[NMAX];
	int Count[NMAX];
	double Dist[NMAX];
	double f[NMAX];
	double data;
	int dataSize = 0;	//分布にカウントされるデータ数
	int rawDataSize = 0;	//もとのデータ数
	double ymax = XMAX + 0.5 * DX;
	double ymin = XMIN - 0.5 * DX;
	double dataMax, dataMin;

	double aveData = 0;	//データの平均値
	double varData = 0;	//データの分散
	double SDData = 0;	//データの標準偏差
	double sumData = 0;	//データの和
	double sumSqData = 0;	//データの二乗和

	/////////////////////////////////////////////////////////
	//(1. FILE OPEN)/////////////////////////////////////////
	FILE *fpin;
	FILE *fpout;
		
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
	

	if(N<=NMAX){

		for(i = 0; i< N; i++){
			x[i] = XMAX - i * DX;
			y[i] = ymax - i * DX;
			Count[i] = 0;
		}
		y[N] = ymax - N * DX;
		Count[N] = 0;

		//ひとつめのデータの読み込みと初期値設定
		//最大値・最小値などを決めるため，
		//ひとつめのデータだけwhile文の外で読み込み，初期状態を作る
		fscanf(fpin,"%lf\n",&data);
		dataMax = data;
		dataMin = data;
		sumData = data;
		sumSqData = pow(data,2);
		rawDataSize++;
		
		if(ymin < data && data <= ymax){
			i = (int)((ymax - data)/DX);
			Count[i]++;
			dataSize++;
		}

		//２個目以降のデータの読み込み
		while (!feof(fpin)) {

			fscanf(fpin,"%lf\n",&data);
			rawDataSize++;
			if(dataMax < data){
				dataMax = data;
			}
			if(data < dataMin){
				dataMin = data;
			}
			sumData = sumData + data;
			sumSqData = sumSqData + pow(data,2);			

			if(ymin < data && data <= ymax){
				i = (int)((ymax - data)/DX);
				Count[i]++;
				dataSize++;
			}
      	}

		aveData = sumData / rawDataSize;
        varData = (sumSqData - 2 * aveData * sumData + rawDataSize * pow(aveData, 2)) / (rawDataSize - 1);
		SDData = sqrt(varData);

		for(i = 0; i< N; i++){
			Dist[i] = Count[i]/(DX * dataSize);
			
			//Gaussian
			f[i] = exp(-pow((x[i]-aveData),2.0)/(2*varData))/sqrt(2*M_PI*varData);
		}

		//書き出し
		fprintf(fpout,"Basic Information of Data\n");
		fprintf(fpout,"The Number of Raw Data ,%d\n",rawDataSize);
		fprintf(fpout,"Maximum of Raw Data ,%f\n",dataMax);
		fprintf(fpout,"Minimum of Raw Data ,%f\n",dataMin);
		fprintf(fpout,"Average : E(x) ,%f\n",aveData);
		fprintf(fpout,"Variance : V(x) ,%f\n",varData);
		fprintf(fpout,"Standard Deviation : sqrt(V(x)) ,%f\n",SDData);
		fprintf(fpout,"\n");
		fprintf(fpout,"Histogram Dist(x) and Probability Density Function f(x) \n");
		fprintf(fpout,"The Number of Data for Histogram ,%d\n",dataSize);
		fprintf(fpout,"Data Range to Construct Histogram ,%f < y <eq %f\n",ymin,ymax);
		fprintf(fpout,"Graph Drawing Range ,%f <eq x <eq %f\n",XMIN,XMAX);
		fprintf(fpout,"Step Size : dx ,%f\n",DX);
		fprintf(fpout,"xi , ni/(N*dx), f(x) \r\n");
		for(i = 0; i< N; i++){
			fprintf(fpout,"%f,%f,%f\n",x[i],Dist[i],f[i]);
		}

		printf("The Number of Raw Data = %d\n",rawDataSize);				
		printf("The Number of Data for Histogram = %d\n",dataSize);

	}
	else{
		printf("Error! NMAX is too small!\n");
		printf("Please set as %d <= NMAX\n",N);

	}
	
	/////////////////////////////////////////////////////////
	fclose(fpin);
	fclose(fpout);	//(2. FILE CLOSE)
	/////////////////////////////////////////////////////////
	printf("\nCSV file was made. \n");
	
	return 0;
}
