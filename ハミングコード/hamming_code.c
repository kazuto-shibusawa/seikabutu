#include <stdio.h>
#include <stdlib.h>

/*ハミング符号(7, 4) 検査行列*/
static int hamming74_H[3][7] =	{{1, 1, 1, 0,   1, 0, 0},
						  {0, 1, 1, 1,   0, 1, 0},
						  {1, 1, 0, 1,   0, 0, 1}};

/*信語(0と1だけの長さ7の文字列)を引数とし、シンドロームを返す関数
 */
int* hamming74_syndrome(char y[]) {
	int *s, i, j;
	if ((s = (int*)malloc(sizeof(int) * 3)) == NULL) {
		printf("hamming74_syndrome() malloc error!\n");
		exit(1);
	}
	for (i = 0; i < 3; ++i) {
		for (j = 0, s[i] = 0; j < 7; ++j) {
			s[i] ^= hamming74_H[i][j] * (y[j] - '0');
		}
	}
	return s;
}

/*受信語を引数とし、誤りが無ければ0、誤りがあった場合はそのビットの位置を返す関数
 *受信語に0と1以外の文字が含まれていた場合-1、受信語の長さが合わない場合-2を返す
 */
int hamming74_check(char y[]) {
	int *s, i, j;
	for (j = 0; j < 7; ++j) {
		if (y[j] == '\0') return -2;
		if (y[j] != '0' && y[j] != '1') return -1;
	}
	if (y[7] != '\0') return -2;

	s = hamming74_syndrome(y);

	for (i = 0; i < 3; ++i) if (s[i] != 0) break;
	if (i == 3) {
		free(s);
		return 0;
	}

	for (j = 0; j < 7; ++j) {
		for (i = 0; i < 3; ++i) if (hamming74_H[i][j] != s[i]) break;
		if (i == 3) {
			free(s);
			return j + 1;
		}
	}

	free(s);
	return -3;
}

/*受信語と反転する添え字を引数とし、指定された添え字の0、1を反転する関数
 */
char* hamming74_correction(char y[], int n) {
	if (n > 0) y[n - 1] += ('0' + '1') - (y[n - 1] << 1);
	return y;
}

char* read_line(void) {
	static int length = 0;
	char* str, c;
	if ((c = getchar()) != '\n' && c != EOF) {
		++length;
		str = read_line();
		str[--length] = c;
		return str;
	}
	if ((str = (char*)malloc((length + 1) * sizeof(char))) == NULL) {
		printf("read_line() malloc error!\n");
		exit(1);
	}
	str[length] = '\0';
	return str;
}

int main(int argc, char const *argv[]) {
	char* y;
	int n;

	printf("Input receiving word : ");
	y = read_line();

	switch (n = hamming74_check(y)) {
		case -3:
			printf("hamming74_check() unknown error!\n");
			break;

		case -2:
			printf("Receiving word length error!\n");
			break;

		case -1:
			printf("Receiving word character error!\n");
			break;

		case 0:
			printf("The received word is correct.\n");
			break;

		default:
			printf("The received word is incorrect.\n");
			printf("The incorrect bit is %dth.\n", n);
			printf("The correct received word is %s.\n", hamming74_correction(y, n));
			break;
	}

	free(y);
	return 0;
}