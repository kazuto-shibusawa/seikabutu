#include <stdio.h>
#include <stdlib.h>

static int C[3][7] = {{1, 1, 1, 0, 1, 0, 0},
					  {0, 1, 1, 1, 0, 1, 0},
					  {1, 1, 0, 1, 0, 0, 1}};

int* ham_syn(char q[]) {
	int *p, i, j;

	if ((p = (int*)malloc(sizeof(int) * 3)) == NULL) {
		printf("Out of memory!\n");
		exit(1);
	}

	for (i = 0; i < 3; i++) {
		for (j = 0, p[i] = 0; j < 7; j++) {
			p[i] = (p[i] + C[i][j] * (q[j] - '0')) % 2;
		}
	}

	return p;
}

int ham_che(char q[]) {
	int *p, i, j;

	for (j = 0; j < 7; j++) {
		if (q[j] == '\0') {
			return 10;
		}
		if (q[j] != '0' && q[j] != '1') {
			return 9;
		}
	}

	if (q[7] != '\0') {
		return 10;
	}

	p = ham_syn(q);

	for (i = 0; i < 3; i++) {
		if (p[i] != 0) {
			break;
		}
	}

	if (i == 3) {
		free(p);
		return 8;
	}

	for (j = 0; j < 7; j++) {
		for (i = 0; i < 3; i++) {
			if (C[i][j] != p[i]) {
				break;
			}
		}
		if (i == 3) {
			free(p);
			return j + 1;
		}
	}

	free(p);
	return 11;
}

char* ham_inv(char q[], int n) {
	if (n > 0) {
		q[n - 1] += ('0' + '1') - (q[n - 1] << 1);
	}

	return q;
}

char* read_line(void) {
	static int length = 0;
	char* str, a;

	if ((a = getchar()) != '\n' && a != EOF) {
		++length;
		str = read_line();
		str[--length] = a;
		return str;
	}

	if ((str = (char*)malloc((length + 1) * sizeof(char))) == NULL) {
		printf("Out of memory!\n");
		exit(1);
	}

	str[length] = '\0';
	return str;
}

int main(void) {
	char* q;
	int n;

	printf("Input received word (seven letters) : ");
	q = read_line();

	switch (n = ham_che(q)) {
		case 11:
			printf("Error!\n");
			break;

		case 10:
			printf("Received word is length defoult!\n");
			break;

		case 9:
			printf("Received word is different character!\n");
			break;

		case 8:
			printf("The received word is correct.\n");
			break;

		default:
			printf("The received word is wrong.\n");
			printf("The wrong bit is %dth.\n", n);
			printf("The correct received word is %s.\n", ham_inv(q, n));
			break;
	}

	free(q);
	return 0;
}