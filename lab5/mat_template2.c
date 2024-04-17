#include <stdio.h>
#include <math.h>

#define SIZE 40

void read_vector(double x[], int n) {
	for(int i = 0; i < n; ++i) {
		scanf("%lf", x++);
	}
}

void print_vector(double x[], int n) {
	for(int i = 0; i < n; ++i) {
		printf("%.4f ", x[i]);
	}
	printf("\n");
}

void read_mat(double A[][SIZE], int m, int n) {
	for(int i = 0; i < m; ++i) {
		for(int j = 0; j < n; ++j) {
			scanf("%lf", &A[i][j]);
		}
	}
}

void print_mat(double A[][SIZE], int m, int n) {
	for(int i = 0; i < m; ++i) {
		for(int j = 0; j < n; ++j) {
			printf("%.4f ", A[i][j]);
		}
		printf("\n");
	}
}

void swap_rows(double A[][SIZE], int a, int b, int l){
	double temp;
	for(int i=0; i<l; i++){
		temp=A[a][i];
		A[a][i]=A[b][i];
		A[b][i]=temp;
	}
}

// 1. Calculate matrix product, AB = A X B
// A[m][p], B[p][n], AB[m][n]
void mat_product(double A[][SIZE], double B[][SIZE], double AB[][SIZE], int m, int p, int n) {
	for(int i=0; i<m; i++){
		for(int j=0; j<n; j++){
			AB[i][j]=0;
		}
	}
	for(int i=0; i<m; i++){
		for(int j=0; j<n; j++){
			for(int k=0; k<p; k++){
				AB[i][j]+=A[i][k]*B[k][j];
			}
		}
	}
}

// 2. Matrix triangulation and determinant calculation - simplified version
// (no rows' swaps). If A[i][i] == 0, function returns NAN.
// Function may change A matrix elements.
double gauss_simplified(double A[][SIZE], int n) {
    double det=1, r;
    for(int k=0; k<n-1; k++){
        if (A[k][k] != 0) {
            for (int j = k + 1; j < n; j++) {
                r = A[j][k] / A[k][k];
                A[j][k] = 0;
                for (int i = k + 1; i < n; i++) {
                    A[j][i] -= (A[k][i]) * r;
                }
            }
        } else
            return NAN;
    }
    for(int i=0; i<n; i++){
        det=det*A[i][i];
    }
    return det;
}

void backward_substitution_index(double A[][SIZE], const int indices[], double x[], int n) {
}

// 3. Matrix triangulation, determinant calculation, and Ax = b solving - extended version
// (Swap the rows so that the row with the largest, leftmost nonzero entry is on top. While
// swapping the rows use index vector - do not copy entire rows.)
// If max A[i][i] < eps, function returns 0.
// If det != 0 && b != NULL && x != NULL then vector x should contain solution of Ax = b.

double gauss(double A[][SIZE], const double b[], double x[], const int n, const double eps) {
	double r, det=1, p;
	int t;
    for(int i=0; i<n; i++){
		A[i][n]=b[i];
	}
	for(int i=0; i<n-1; i++){
		t=i;
		for(int j=i+1; j<n; j++){
			if(fabs(A[j][i])>fabs(A[t][i])){
				t=j;
			}
		}
		if(fabs(A[t][i])<eps){
			return 0;
		}
		if(t!=i){
			swap_rows(A, t, i, n+1);
			det=det*(-1);
		}
		for(int j=i+1; j<n; j++){
			r=A[j][i]/A[i][i];
			A[j][i]=0;
			for(int k=i+1; k<n+1; k++){
				A[j][k]-=(A[i][k])*r;
			}
		}
	}
	for(int i=n-1; i>0; i-=1){
		for(int j=i-1; j>-1; j-=1){
			r=(A[j][i])/(A[i][i]);
			A[j][i]=0;
			for(int k=0; k<i; k++){
				A[j][k]-=(A[i][k]*r);
			}
			A[j][n]-=(A[i][n]*r);
		}
	}
	for(int i=0; i<n; i++){
		p=A[i][i];
		det=det*p;
		A[i][i]=1;
		for(int j=i+1; j<n+1; j++){
			A[i][j]=(A[i][j])/p;
		}
		x[i]=A[i][n];
	}
	return det;
}

// 4. Returns the determinant; B contains the inverse of A (if det(A) != 0)
// If max A[i][i] < eps, function returns 0.
double matrix_inv(double A[][SIZE], double B[][SIZE], int n, double eps) {
	double r, det=1, p;
	int t;
    for(int i=0; i<n; i++){
		for(int j=n; j<2*n; j++){
			A[i][j]=0;
		}
		A[i][n+i]=1;
	}
	for(int i=0; i<n-1; i++){
		t=i;
		for(int j=i+1; j<n; j++){
			if(fabs(A[j][i])>fabs(A[t][i])){
				t=j;
			}
		}
		if(fabs(A[t][i])<eps){
			return 0;
		}
		if(t!=i){
			swap_rows(A, t, i, 2*n);
			det=det*(-1);
		}
		for(int j=i+1; j<n; j++){
			r=A[j][i]/A[i][i];
			A[j][i]=0;
			for(int k=i+1; k<2*n; k++){
				A[j][k]-=(A[i][k])*r;
			}
		}
	}
	for(int i=n-1; i>0; i-=1){
		for(int j=i-1; j>-1; j-=1){
			r=(A[j][i])/(A[i][i]);
			A[j][i]=0;
			for(int k=0; k<i; k++){
				A[j][k]-=(A[i][k]*r);
			}
			for(int v=n; v<2*n; v++){
				A[j][v]-=(A[i][v]*r);
			}
		}
	}
	for(int i=0; i<n; i++){
		p=A[i][i];
		det=det*p;
		A[i][i]=1;
		for(int j=i+1; j<2*n; j++){
			A[i][j]=(A[i][j])/p;
		}
		for(int k=n; k<2*n; k++){
			B[i][k-n]=A[i][k];
		}
	}
	return det;
}

int main(void) {

	double A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];
	double b[SIZE], x[SIZE], det, eps = 1.e-13;

	int to_do;
	int m, n, p;

	scanf ("%d", &to_do);

	switch (to_do) {
		case 1:
			scanf("%d %d %d", &m, &p, &n);
			read_mat(A, m, p);
			read_mat(B, p, n);
			mat_product(A, B, C, m, p, n);
			print_mat(C, m, n);
			break;
		case 2:
			scanf("%d", &n);
			read_mat(A, n, n);
			printf("%.4f\n", gauss_simplified(A, n));
			break;
		case 3:
			scanf("%d", &n);
			read_mat(A,n, n);
			read_vector(b, n);
			det = gauss(A, b, x, n, eps);
			printf("%.4f\n", det);
			if (det) print_vector(x, n);
			break;
		case 4:
			scanf("%d", &n);
			read_mat(A, n, n);
			det = matrix_inv(A, B, n, eps);
			printf("%.4f\n", det);
			if (det) print_mat(B, n, n);
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}
	return 0;
}

