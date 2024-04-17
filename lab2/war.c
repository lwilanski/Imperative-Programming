#include <stdio.h>
#include <stdlib.h>

int rand_from_interval(int a, int b) {
	int result,range;
	range=b-a+1;
	result=(rand()%range)+a;
	return result;
}


void read_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }
}


void print_array(int array[], int n){
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
}


void swap (int array[], int i, int k) {
	int temp;
	temp=array[k];
	array[k]=array[i];
	array[i]=temp;
}

void rand_permutation(int n, int array[]) {
	int k;
	for(int i=0; i<n; i++){
		array[i]=i;
	}
	for(int j=0; j<n-1; j++){
		k=rand_from_interval(j, n-1);
		swap(array, j, k);
	}
}

void cbuff_push(int cbuff[], int len, int out, int val){
	int i=(out+len)%52;
	cbuff[i]=val;
}

int cbuff_pop(int cbuff[], int len, int out) {
	int z;
	if(len==0){
		return -1;
	}
	z=cbuff[out];
	cbuff[out]=0;
	return z;
}

void cbuff_print(int cbuff[], int len, int out) {
	int k;
	for(int i=0; i<len; i++){
		k=(i+out)%52;
		printf("%d ", cbuff[k]);
	}
}

void cas_war(int array[], int con){
	int A[52];
	for(int i=0; i<26; i++){
		A[i]=array[i];
	}
    print_array(A, 26);
    printf("\n");
	int B[52];
	for(int j=26; j<52; j++){
		B[j-26]=array[j];
	}
    print_array(B, 26);
    printf("\n\n");
	
	int la=26, oa=0, lb=26, ob=0, counter=0, k1, k2;
	
	while(counter<con && la>0 && lb>0){
		k1=cbuff_pop(A,la,oa);
		la-=1;
		oa=(oa+1)%52;
		k2=cbuff_pop(B,lb,ob);
		lb-=1;
		ob=(ob+1)%52;
        printf("Conflict %d, cards: %d vs %d\n", counter, k1, k2);
		if(k1/4==k2/4){
			cbuff_push(A,la,oa,k1);
			la+=1;
			cbuff_push(B,lb,ob,k2);
			lb+=1;
		}
		else{
			if(k1/4>k2/4){
				cbuff_push(A,la,oa,k1);
				la+=1;
				cbuff_push(A,la,oa,k2);
				la+=1;
			}
			else{
				cbuff_push(B,lb,ob,k2);
				lb+=1;
				cbuff_push(B,lb,ob,k1);
				lb+=1;
			}
		}
        printf("Player A cards after conflict %d: ", counter);
        cbuff_print(A, la, oa);
        printf("\n");

        printf("Player B cards after conflict %d: ", counter);
        cbuff_print(B, lb, ob);
        printf("\n\n");

		counter+=1;
		
	}
	
	if(counter>=con){
		printf("0 %d %d", la, lb);
	}
	
	else{
		if(lb==0){
			printf("2 %d", counter);
		}
		else{
			printf("3\n");
			cbuff_print(B,lb,ob);
		}
	}
		
}

void war(int array[], int con){
	int A[52];
	for(int i=0; i<26; i++){
		A[i]=array[i];
	}
	int B[52];
	for(int j=26; j<52; j++){
		B[j-26]=array[j];
	}
	
	int la=26, oa=0, lb=26, ob=0, counter=0, k1, k2, e=0;
	int RA[52], lenghtA=0, RB[52], lenghtB=0;
	int k3, k4, k5, k6;
	
	while(counter<con && la>0 && lb>0 && e==0){
		k1=cbuff_pop(A,la,oa);
		la-=1;
		oa=(oa+1)%52;
		k2=cbuff_pop(B,lb,ob);
		lb-=1;
		ob=(ob+1)%52;
		if(k1/4==k2/4){
			lenghtA=0;
			lenghtB=0;
			RA[lenghtA]=k1;
			lenghtA+=1;
			RB[lenghtB]=k2;
			lenghtB+=1;
			while(la>1 && lb>1){
				k3=cbuff_pop(A,la,oa);
				la-=1;
				oa=(oa+1)%52;
				k4=cbuff_pop(B,lb,ob);
				lb-=1;
				ob=(ob+1)%52;
				k5=cbuff_pop(A,la,oa);
				la-=1;
				oa=(oa+1)%52;
				k6=cbuff_pop(B,lb,ob);
				lb-=1;
				ob=(ob+1)%52;
				RA[lenghtA]=k3;
				lenghtA+=1;
				RB[lenghtB]=k4;
				lenghtB+=1;
				RA[lenghtA]=k5;
				lenghtA+=1;
				RB[lenghtB]=k6;
				lenghtB+=1;
				if(k5/4>k6/4){
					for(int v=0; v<lenghtA; v++){
						cbuff_push(A,la,oa,RA[v]);
						la+=1;
					}
					for(int g=0; g<lenghtB; g++){
						cbuff_push(A,la,oa,RB[g]);
						la+=1;
					}
					counter+=1;
					break;
				}
				else if(k5/4<k6/4){
					for(int x=0; x<lenghtB; x++){
						cbuff_push(B,lb,ob,RB[x]);
						lb+=1;
					}
					for(int f=0; f<lenghtA; f++){
						cbuff_push(B,lb,ob,RA[f]);
						lb+=1;
					}
					counter+=1;
					break;
				}
				counter+=1;
			}
			if(la<=1 || lb<=1){
				e=1;
			}
		}
		else{
			if(k1/4>k2/4){
				cbuff_push(A,la,oa,k1);
				la+=1;
				cbuff_push(A,la,oa,k2);
				la+=1;
			}
			else{
				cbuff_push(B,lb,ob,k2);
				lb+=1;
				cbuff_push(B,lb,ob,k1);
				lb+=1;
			}
		}
		counter+=1;
		
	}
	
	if(counter>=con){
		printf("0 %d %d", la, lb);
	}
	else if(e==1 && la+lb+lenghtA+lenghtB==52){
		printf("1 %d %d", la+lenghtA, lb+lenghtB);
	}
	else if(lb==0){
		printf("2 %d", counter);
	}
	else{
		printf("3\n");
		cbuff_print(B,lb,ob);
	}
		
}

int main(void) {
	int to_do, seed, con;
	int talia[52];

	scanf("%d %d %d", &seed, &to_do, &con);
    read_array(talia, 52);
    printf("\n");
	srand((unsigned) seed);

	switch(to_do) {
		case 0:
//          rand_permutation(52, talia);
            print_array(talia, 52);
            printf("\n\n");
			war(talia,con);
			break;
		case 1:
//		    rand_permutation(52, talia);
            print_array(talia, 52);
            printf("\n\n");
			cas_war(talia,con);
			break;
		default:
			printf("NOTHING TO DO!\n");
			break;
	}
	return 0;
}