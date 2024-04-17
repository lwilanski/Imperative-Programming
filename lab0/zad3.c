#include <stdio.h>

int czyd(int n){
	int i, sum=0;
	for (i=1; i<=(n/2)+1; i++){
		if (n%i==0 && i<n){
			sum+=i;
		}
	}
	if (sum==n){
		return n;
	}
	else{
		return 0;
	}
}
int main(){
	int p,k,i,licznik=0;
	printf("Podaj początek przedziału: ");
	scanf("%d", &p);
	printf("Podaj koniec przedziału: ");
	scanf("%d", &k);
	for (i=p; i<=k; i++){
		if (czyd(i)!=0){
			printf("%d\n",i);
			licznik+=1;
		}
	}
	printf("%d liczb doskonałych", licznik);
}
			
		
	
	
	
	
	