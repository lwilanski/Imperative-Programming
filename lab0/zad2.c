#include <stdio.h>

int fibonacci(int n)
{
	int a=0, b=1, c;
	while (a*b<=n){
		if (a*b==n){
			return 1;
		}
		c=a+b;
		a=b;
		b=c;
	}
	return 0;
}
int main()
{
	int n;
	printf("Enter n: ");
	scanf("%d", &n);
	if (fibonacci(n)==1){
		printf("Jest iloczynem");
	}
	else{
		printf("Nie jest iloczynem");
	}
}