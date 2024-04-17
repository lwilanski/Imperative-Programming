#include <stdio.h>

#define STACK_SIZE 10

enum state { OK = 0, UNDERFLOW = -1, OVERFLOW = -2 };

int stack[STACK_SIZE];
int top = -1;

int stack_push(int x) {
	if(top==9){
		return OVERFLOW;
	}
	top+=1;
	stack[top]=x;
	return OK;
}

int stack_pop(void) {
	if(top==-1){
		return UNDERFLOW;
	}
	top-=1;
	return stack[top+1];
}

int stack_state(void) {
	return top+1;
}

// FIFO queue with shifts

#define QUEUE_SIZE 10

int queue[QUEUE_SIZE];
int in = 0, curr_nr = 0;

int queue_push(int in_nr) {
	int e=0;
	while(in_nr>0){
		if(in<10){
			queue[in]=curr_nr+1;
			in+=1;
		}
		else{
			e=1;
		}
		curr_nr+=1;
		in_nr-=1;
	}
	if(e==1){
		return OVERFLOW;
	}
	else{
		return OK;
	}
}

int queue_pop(int out_nr) {
	while(out_nr>0 && in>0){
		for(int i=0; i<in-1; i++){
			queue[i]=queue[i+1];
		}
		queue[in-1]=0;
		out_nr-=1;
		in-=1;
	}
	if(out_nr>0){
		return UNDERFLOW;
	}
	return OK;
}

int queue_state(void) {
	return in;
}

void queue_print(void) {
	for(int i=0; i<in; i++){
		printf("%d ", queue[i]);
	}
}

// Queue with cyclic buffer

#define CBUFF_SIZE 10

int cbuff[CBUFF_SIZE];
int out = 0, len = 0;


int cbuff_push(int cli_nr) {
	if(len==10){
		return OVERFLOW;
	}
	int i=(out+len)%10;
	cbuff[i]=cli_nr;
	len+=1;
	return OK;
}

int cbuff_pop(void) {
	int z;
	if(len==0){
		return UNDERFLOW;
	}
	z=cbuff[out];
	cbuff[out]=0;
	out=(out+1)%10;
	len-=1;
	return z;
}

int cbuff_state(void) {
	return len;
}

void cbuff_print(void) {
	int k;
	for(int i=0; i<len; i++){
		k=(i+out)%10;
		printf("%d ", cbuff[k]);
	}
}

int main(void) {
	int to_do, n, client_no, answer;
	scanf("%d", &to_do);
	switch(to_do) {
		case 1: // stack
			do {
				scanf("%d", &n);
				if (n > 0) {
					if ((answer = stack_push(n)) < 0) printf("%d ", answer);
				} else if (n < 0) {
					printf("%d ", stack_pop());
				} else printf("\n%d\n", stack_state());
			} while(n != 0);
			break;
		case 2: // FIFO queue with shifts
			do {
				scanf("%d", &n);
				if (n > 0) {
					if ((answer = queue_push(n)) < 0) printf("%d ", answer);
				} else if (n < 0) {
					if ((answer = queue_pop(-n)) < 0) printf("%d ", answer);
				} else {
					printf("\n%d\n", queue_state());
					queue_print();
				}
			} while(n != 0);
			break;
		case 3: // queue with cyclic buffer
			client_no = 0;
			do {
				scanf("%d", &n);
				if (n > 0) {
					if ((answer = cbuff_push(++client_no)) < 0) printf("%d ", answer);
				} else if (n < 0) {
					printf("%d ", cbuff_pop());
				} else {
					printf("\n%d\n", cbuff_state());
					cbuff_print();
				}
			} while(n != 0);
			break;
		default: 
			printf("NOTHING TO DO!\n");
	}
	return 0;
}
