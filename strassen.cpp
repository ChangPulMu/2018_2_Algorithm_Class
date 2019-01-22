#include <iostream>
void strassen(int n, int ** A, int ** B, int ** C) {
	if (n <= 1) { // n이 1보다 같거나 작을 경우 **A, **B는 하나의 스칼라 값을 의미하므로 단순 곱셈 연산을 해준다.
		**C = (**A) * (**B);
	}
	else { // n이 1보다 큰 경우 2x2 이상의 행렬이므로 else 문으로 따로 처리해준다.
		 // 총 21개의 n/2xn/2 행렬을 동적할당 해준다.
		int ** A_11 = new int*[n/2]; // 행렬 A를 A11, A12, A21, A22로 4등분 해줬을 때, 행렬 A_11은 행렬 A11을 의미하고, 행렬 A_1122은 행렬 A11과 행렬 A22의 합을 의미하고, 행렬 A_21_11은 행렬 A21과 행렬 A_11간의 차를 의미한다.
		int ** A_22 = new int*[n/2];
		int ** A_1122 = new int*[n/2];
		int ** A_2122 = new int*[n/2];
		int ** A_1112 = new int*[n/2];
		int ** A_21_11 = new int*[n/2];
		int ** A_12_22 = new int*[n/2];
		int ** B_11 = new int*[n/2]; // 행렬 B 또한 마찬가지이다.
		int ** B_22 = new int*[n/2];
		int ** B_1122 = new int*[n/2];
		int ** B_12_22 = new int*[n/2];
		int ** B_21_11 = new int*[n/2];
		int ** B_1112 = new int*[n/2];
		int ** B_2122 = new int*[n/2];

		int ** M1 = new int*[n / 2]; // 행렬 M1부터 M7은 m1부터 m7 값의 저장을 위해 만들어진 행렬이다.
		int ** M2 = new int*[n / 2];
		int ** M3 = new int*[n / 2];
		int ** M4 = new int*[n / 2];
		int ** M5 = new int*[n / 2];
		int ** M6 = new int*[n / 2];
		int ** M7 = new int*[n / 2];
		
		for (int i = 0; i < n / 2; i++) {
			A_11[i] = new int[n / 2];
			A_22[i] = new int[n / 2];
			A_1122[i] = new int[n / 2];
			A_2122[i] = new int[n / 2];
			A_1112[i] = new int[n / 2];
			A_21_11[i] = new int[n / 2];
			A_12_22[i] = new int[n / 2];
			B_11[i] = new int[n / 2];
			B_22[i] = new int[n / 2];
			B_1122[i] = new int[n / 2];
			B_12_22[i] = new int[n / 2];
			B_21_11[i] = new int[n / 2];
			B_1112[i] = new int[n / 2];
			B_2122[i] = new int[n / 2];

			M1[i] = new int[n / 2];
			M2[i] = new int[n / 2];
			M3[i] = new int[n / 2];
			M4[i] = new int[n / 2];
			M5[i] = new int[n / 2];
			M6[i] = new int[n / 2];
			M7[i] = new int[n / 2];
		}

		for (int i = 0; i < n; i++) { // 행렬 M1부터 M7을 제외한 14개의 행렬에 각각의 특정한 값들을 배정해준다.
			for (int j = 0; j < n; j++) {
				if (i < n / 2 && j < n / 2) {
					A_11[i][j] = A[i][j];
					A_1122[i][j] = A[i][j] + A[i + n / 2][j + n / 2];
					A_1112[i][j] = A[i][j] + A[i][j + n / 2];
					B_11[i][j] = B[i][j];
					B_1122[i][j] = B[i][j] + B[i + n / 2][j + n / 2];
					B_1112[i][j] = B[i][j] + B[i][j + n / 2];
				}
				else if (j >= n / 2 && i < n / 2) {
					A_12_22[i][j - n / 2] = A[i][j] - A[i + n / 2][j];
					B_12_22[i][j - n / 2] = B[i][j] - B[i + n / 2][j];
				}
				else if (j < n / 2 && i >= n / 2) {
					A_2122[i - n / 2][j] = A[i][j] + A[i][j + n / 2];
					A_21_11[i - n / 2][j] = A[i][j] - A[i - n / 2][j];
					B_2122[i - n / 2][j] = B[i][j] + B[i][j + n / 2];
					B_21_11[i - n / 2][j] = B[i][j] - B[i - n / 2][j];
				}
				else {
					A_22[i - n / 2][j - n / 2] = A[i][j];
					B_22[i - n / 2][j - n / 2] = B[i][j];
				}
			}
		}

		strassen(n / 2, A_1122, B_1122, M1); // 행렬 M1부터 M7의 값을 구하기 위해 재귀 호출을 한다.
		strassen(n / 2, A_2122, B_11, M2);
		strassen(n / 2, A_11, B_12_22, M3);
		strassen(n / 2, A_22, B_21_11, M4);
		strassen(n / 2, A_1112, B_22, M5);
		strassen(n / 2, A_21_11, B_1112, M6);
		strassen(n / 2, A_12_22, B_2122, M7);

		for (int i = 0; i < n; i++) { // strassen matrix multiplication에 따른 계산을 통해 C의 값을 구한다.
			for (int j = 0; j < n; j++) {
				if (i < n / 2 && j < n / 2) {
					C[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
				}
				else if (j >= n / 2 && i < n / 2) {
					C[i][j] = M3[i][j - n / 2] + M5[i][j - n / 2];
				}
				else if (j < n / 2 && i >= n / 2) {
					C[i][j] = M2[i - n / 2][j] + M4[i - n / 2][j];
				}
				else {
					C[i][j] = M1[i - n / 2][j - n / 2] + M3[i - n / 2][j - n / 2] - M2[i - n / 2][j - n / 2] + M6[i - n / 2][j - n / 2];
				}
			}
		}

		for (int i = 0; i < n / 2; i++) { // 동적할당했던 21개의 행렬들의 메모리를 반납한다.
			delete A_11[i];
			delete A_22[i];
			delete A_1122[i];
			delete A_2122[i];
			delete A_1112[i];
			delete A_21_11[i];
			delete A_12_22[i];
			delete B_11[i];
			delete B_22[i];
			delete B_1122[i];
			delete B_12_22[i];
			delete B_21_11[i];
			delete B_1112[i];
			delete B_2122[i];

			delete M1[i];
			delete M2[i];
			delete M3[i];
			delete M4[i];
			delete M5[i];
			delete M6[i];
			delete M7[i];
		}

		delete A_11;
		delete A_22;
		delete A_1122;
		delete A_2122;
		delete A_1112;
		delete A_21_11;
		delete A_12_22;
		delete B_11;
		delete B_22;
		delete B_1122;
		delete B_12_22;
		delete B_21_11;
		delete B_1112;
		delete B_2122;

		delete M1;
		delete M2;
		delete M3;
		delete M4;
		delete M5;
		delete M6;
		delete M7;
	}
}