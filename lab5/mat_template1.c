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
			if(A[i][j]==0){
				printf("-%.4f ", A[i][j]);
			}
			else{
				printf("%.4f ", A[i][j]);
			}
		}
		printf("\n");
	}
}
void clone_arr(double A[], double B[], int n){
	for(int i=0; i<n; i++){
		B[i]=A[i];
	}
}

void clone_matrix(double A[][SIZE], double B[][SIZE], int n){
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			B[i][j]=A[i][j];
		}
	}
}

void print_matrix(double A[][SIZE], int h, int w){
	printf("\n");
	for(int i=0; i<h; i++){
		for(int j=0; j<w; j++){
			printf("%.1f ", A[i][j]);
			if(j==((w/2)-1)){
				printf(" ");
			}
		}
		printf("\n");
	}
	printf("\n");
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
	double det=1;
    if(n==1) {
        return 0;
    }
    for(int i=0; i<n-1; i++){
        if(A[i][n-1]!=0){
            double w=(A[i][n-1])/(A[n-1][n-1]);
            for(int j=0; j<n; j++){
				A[i][j]-=(A[n-1][j])*w;
            }
        }
    }
	gauss_simplified(A, n-1);
	for(int i=0; i<n; i++){
		det=det*A[i][i];
	}
	if(det==0){
		return NAN;
	}
	else{
		return det;
	}
}

void backward_substitution_index(double A[][SIZE], const int indices[], double x[], int n) {
}

// 3. Matrix triangulation, determinant calculation, and Ax = b solving - extended version
// (Swap the rows so that the row with the largest, leftmost nonzero entry is on top. While
// swapping the rows use index vector - do not copy entire rows.)
// If max A[i][i] < eps, function returns 0.
// If det != 0 && b != NULL && x != NULL then vector x should contain solution of Ax = b.

double gauss(double A[][SIZE], const double b[], double x[], const int n) {
	double w,ws;
	double B[SIZE][SIZE], C[SIZE][SIZE];
	clone_matrix(A, B, n);
	w=gauss_simplified(A, n);
	if(isnan(w)){
		w=0;
	}
	else{
		for(int i=0; i<n; i++){
			clone_matrix(B, C, n);
			for(int j=0; j<n; j++){
				C[j][i]=b[j];
			}
			ws=gauss_simplified(C, n);
			x[i]=(ws/w);
		}
	}
	return w;

}

double gauss_inv(double A[][SIZE], int n, int p) {
	double det=1;
    if(n==1) {
        return 0;
    }
    for(int i=0; i<n-1; i++){
        if(A[i][n-1]!=0){
            double w=(A[i][n-1])/(A[n-1][n-1]);
            for(int j=0; j<2*p; j++){
				A[i][j]-=(A[n-1][j])*w;
            }
        }
    }
	gauss_inv(A, n-1, p);
	for(int i=0; i<n; i++){
		det=det*A[i][i];
	}
	if(det==0){
		return NAN;
	}
	else{
		return det;
	}
}

// 4. Returns the determinant; B contains the inverse of A (if det(A) != 0)
// If max A[i][i] < eps, function returns 0.
double matrix_inv(double A[][SIZE], double B[][SIZE], int n) {
	double w, x, y;
	for(int i=0; i<n; i++){
		for(int j=n; j<2*n; j++){
			A[i][j]=0;
		}
		A[i][n+i]=1;
	}
	w=gauss_inv(A, n, n);
	if(isnan(w)){
		w=0;
	}
	else{
		for(int i=0; i<n-1; i++){
			for(int j=i+1; j<n; j++){
				x=(A[j][i]/A[i][i]);
				for(int k=0; k<2*n; k++){
					A[j][k]-=(A[i][k])*x;
				}
			}
		}
		for(int i=0; i<n; i++){
			y=A[i][i];
			for(int j=0; j<(2*n); j++){
				A[i][j]=(A[i][j])/y;
				if(j>n-1){
					B[i][j-n]=A[i][j];
				}
			}
			for(int i=0; i<n; i++){
				for(int j=0; j<n; j++){
					if(A[i][j]==0){
						w=w*(-1);
					}
				}
			}
		}
	}
	return w;
}

int main(void) {

	double A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];
	double b[SIZE], x[SIZE], det;

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
			det = gauss(A, b, x, n);
			printf("%.4f\n", det);
			if (det) print_vector(x, n);
			break;
		case 4:
			scanf("%d", &n);
			read_mat(A, n, n);
			det = matrix_inv(A, B, n);
			printf("%.4f\n", det);
			if (det) print_mat(B, n, n);
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}
	return 0;
}

