#include <stdio.h>
#include<math.h>

int czyp(int n){
	int k,i;
	double p=sqrt(n);
	k=ceil(p);
	if (n==2){
		return 1;
	}
	else if (n==1){
		return 0;
	}
	for (i=2; i<=k+1; i++){
		if(n%i==0){
			return 0;
		}
	}
	return 1;
}

int main(){
	int n;
	printf("Podaj n: ");
	scanf("%d", &n);
	printf("%d", czyp(n));
}
	
	
	