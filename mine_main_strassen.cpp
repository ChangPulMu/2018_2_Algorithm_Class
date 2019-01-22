#include <iostream>
void strassen(int n, int ** A, int ** B, int ** C);
int main(void) {
	int num = 4, a = 1, b = 2; // 4x4 ����̱� ������ num ������ 4�� �ʱ�ȭ
	int ** Am, ** Bm, ** Cm; // �Է� : Am, Bm 4x4 ��İ�, ��� : Cm 4x4 ���

	Am = new int*[num]; // ��ĵ��� num ����ŭ �����Ҵ� ���ִ� �۾�
	Bm = new int*[num];
	Cm = new int*[num];
	for (int i = 0; i < num; i++) {
		Am[i] = new int[num];
		Bm[i] = new int[num];
		Cm[i] = new int[num];
	}

	for (int i = 0; i < num; i++) { // ������ ���� �Է� �����ͷ� Am, Bm ��Ŀ� ���� ����
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

	strassen(num, Am, Bm, Cm); // strassen �Լ� ȣ��

	std::cout << "��� A" << std::endl; // ��� A�� ���� ���� ���

	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			std::cout << Am[i][j] << ' ';
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	std::cout << "��� B" << std::endl; // ��� B�� ���� ���� ���

	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			std::cout << Bm[i][j] << ' ';
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	std::cout << "��� C = A X B" << std::endl; // ��� C�� ���� ���� ���

	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			std::cout << Cm[i][j] << ' ';
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	for (int i = 0; i < num; i++) { // ���� �Ҵ������ ��ĵ��� �޸� �ݳ�
		delete Am[i];
		delete Bm[i];
		delete Cm[i];
	}
	delete Am;
	delete Bm;
	delete Cm;

	return 0;
}