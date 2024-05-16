#include <iostream>


/*
* All the best with this one. :)
*/
int** strassens(int a[][2], int b[][2], int size) {

	// WRONG IMPLEMENTATION
	int s1, s2, s3, s4, s5, s6, s7, s8, s9, s10;
	s1 = b[0][1] - b[1][1];
	s2 = a[0][0] + a[0][1];
	s3 = a[1][0] + a[1][1];
	s4 = b[1][0] + b[0][0];
	s5 = a[0][0] + a[1][1];
	s6 = b[0][0] + b[1][1];
	s7 = a[0][1] - a[1][1];
	s8 = b[1][0] + b[1][1];
	s9 = a[0][0] - a[1][0];
	s10 = b[0][0] + b[0][1];

	int p1, p2, p3, p4, p5, p6, p7;
	p1 = s1 * a[0][0];
	p2 = s2 * b[1][1];
	p3 = s3 * b[0][0];
	p4 = s4 * a[1][1];
	p5 = s5 * s6;
	p6 = s7 * s8;
	p7 = s9 * s10;

	int** c = new int* [2];
	for (int i = 0; i < 2; i++) {
		c[i] = new int[2];
	}

	c[0][0] = p5 + p4 - p2 + p6;
	c[0][1] = p1 + p2;
	c[1][0] = p3 + p4;
	c[1][1] = p5 + p1 - p3 - p7;
	
	return c;
}

void run_strassens() {
	int size = 2;
	int matrix_a[][2] = {
		{ 1, 0,},
		{ 0, 1,}
	};

	int matrix_b[][2] = {
		{ 1, 0, },
		{ 0, 1, },
	};

	int** result = strassens(matrix_a, matrix_b, size);

	std::cout << "Result: " << std::endl;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			std::cout << result[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

//int main() {
//	run_strassens();
//	return 0;
//}