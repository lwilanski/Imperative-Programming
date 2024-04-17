#include <stdio.h>
int main(void){
	int sum=0;
	while(1){
		int s,k,w;
		printf("Podaj początek pracy ");
		scanf("%d", &s);
		if(s==0000){
			break;
		}
		printf("Podaj koniec pracy ");
		scanf("%d", &k);
		w=(((k/100)*60)+k%100)-(((s/100)*60)+s%100);
		sum+=w;
	}
	printf("Koniec, suma wynosi %d minut",sum);
}
