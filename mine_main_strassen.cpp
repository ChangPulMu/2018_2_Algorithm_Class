#include <iostream>
void strassen(int n, int ** A, int ** B, int ** C);
int main(void) {
	int num = 4, a = 1, b = 2; // 4x4 행렬이기 때문에 num 변수를 4로 초기화
	int ** Am, ** Bm, ** Cm; // 입력 : Am, Bm 4x4 행렬과, 출력 : Cm 4x4 행렬

	Am = new int*[num]; // 행렬들을 num 값만큼 동적할당 해주는 작업
	Bm = new int*[num];
	Cm = new int*[num];
	for (int i = 0; i < num; i++) {
		Am[i] = new int[num];
		Bm[i] = new int[num];
		Cm[i] = new int[num];
	}

	for (int i = 0; i < num; i++) { // 임의의 자작 입력 데이터로 Am, Bm 행렬에 값을 배정
		for (int j = 0; j < num; j++) {
			Am[i][j] = a;
			Bm[i][j] = b;
			a += 2;
			b += 2;
			if (a == 11)
				a = 1;
			if (b == 12)
				b = 2;
		}
	}

	strassen(num, Am, Bm, Cm); // strassen 함수 호출

	std::cout << "행렬 A" << std::endl; // 행렬 A에 대한 정보 출력

	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			std::cout << Am[i][j] << ' ';
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	std::cout << "행렬 B" << std::endl; // 행렬 B에 대한 정보 출력

	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			std::cout << Bm[i][j] << ' ';
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	std::cout << "행렬 C = A X B" << std::endl; // 행렬 C에 대한 정보 출력

	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			std::cout << Cm[i][j] << ' ';
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	for (int i = 0; i < num; i++) { // 동적 할당해줬던 행렬들의 메모리 반납
		delete Am[i];
		delete Bm[i];
		delete Cm[i];
	}
	delete Am;
	delete Bm;
	delete Cm;

	return 0;
}