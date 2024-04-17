#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REL_SIZE 100
#define MAX_RANGE 100

typedef struct {
	int first;
	int second;
} pair;

// Case 1:

// The relation R is reflexive if xRx for every x in X
int is_reflexive(const pair *relation, int size) {
    int max_value = 0;

    for (int i = 0; i < size; i++) {
        if (relation[i].first > max_value) {
            max_value = relation[i].first;
        }
        if (relation[i].second > max_value) {
            max_value = relation[i].second;
        }
    }
	for(int x=0; x<max_value+1; x++){
		int found1=0;
		int found2=0;
		for(int i=0; i<size; i++){
			if (relation[i].first == x && relation[i].second == x) {
                found2 = 1;
				break;
			}
			if (relation[i].first == x || relation[i].second == x){
				found1 = 1;
			}
		}
		if(found1 && !found2){
			return 0;
		}
	}
	return 1;
}

// The relation R on the set X is called irreflexive
// if xRx is false for every x in X
int is_irreflexive(const pair *relation, int size){
	for(int i=0; i<size; i++){
		if (relation[i].first == relation[i].second) {
			return 0;
		}	
	}
	return 1;
}

// A binary relation R over a set X is symmetric if:
// for all x, y in X xRy <=> yRx
int is_symmetric(const pair *relation, int size){
	for(int i=0; i<size; i++){
		if(relation[i].first!=relation[i].second){
			int found=0;
			for(int j=0; j<size; j++){
				if(relation[i].first==relation[j].second && relation[i].second==relation[j].first){
					found=1;
					break;
				}
			}
			if(!found){
				return 0;
			}
		}
	}
	return 1;
}

// A binary relation R over a set X is antisymmetric if:
// for all x,y in X if xRy and yRx then x=y
int is_antisymmetric(const pair *relation, int size){
	for(int i=0; i<size; i++){
		if(relation[i].first!=relation[i].second){
			for(int j=0; j<size; j++){
				if(relation[i].first==relation[j].second && relation[i].second==relation[j].first){
					return 0;
				}
			}
		}
	}
	return 1;
}

// A binary relation R over a set X is asymmetric if:
// for all x,y in X if at least one of xRy and yRx is false
int is_asymmetric(const pair *relation, int size){
	for(int i=0; i<size; i++){
		if(relation[i].first!=relation[i].second){
			for(int j=0; j<size; j++){
				if(relation[i].first==relation[j].second && relation[i].second==relation[j].first){
					return 0;
				}
			}
		}
		else{
			return 0;
		}
	}
	return 1;
}

// A homogeneous relation R on the set X is a transitive relation if:
// for all x, y, z in X, if xRy and yRz, then xRz
int is_transitive(const pair *relation, int size){
	for(int i=0; i<size; i++){
		if(relation[i].first!=relation[i].second){
			for(int j=0; j<size; j++){
				if(relation[j].first!=relation[j].second && relation[i].second==relation[j].first){
					int found=0;
					for(int k=0; k<size; k++){
						if(relation[k].first==relation[i].first && relation[k].second==relation[j].second){
							found=1;
							break;
						}
					}
					if(!found){
						return 0;
					}
				}
			}
		}
	}
	return 1;
}

// Case 2:

// A partial order relation is a homogeneous relation that is
// reflexive, transitive, and antisymmetric
int is_partial_order(const pair *relation, int size){
	int a=is_reflexive(relation, size);
	int b=is_transitive(relation, size);
	int c=is_antisymmetric(relation, size);
	if(a && b && c){
		return 1;
	}
	else{
		return 0;
	}
}

// A total order relation is a partial order relation that is connected
int is_total_order(const pair *relation, int size){
	int a=is_partial_order(relation, size);
	int b=is_connected(relation, size);
	if(a && b){
		return 1;
	}
	else{
		return 0;
	}
}

// Relation R is connected if for each x, y in X:
// xRy or yRx (or both)
int is_connected(const pair *relation, int size){
	int dom[MAX_REL_SIZE];
	int ldom;
	ldom=get_domain(relation, size, dom);
	for(int i=0; i<ldom; i++){
		for(int j=i+1; j<ldom; j++){
			int found=0;
			for(int k=0; k<size; k++){
				if((relation[k].first==dom[i] && relation[k].second==dom[j]) || (relation[k].first==dom[j] && relation[k].second==dom[i])){
					found=1;
					break;
				}
			}
			if(!found){
				return 0;
			}
		}
	}
	return 1;
}

int find_max_elements(const pair *relation, int size, int *max_elem){
	int dom[MAX_REL_SIZE];
	int ldom, lm=0;
	ldom=get_domain(relation, size, dom);
	for(int i=0; i<ldom; i++){
		int found=0;
		for(int j=0; j<size; j++){
			if(relation[j].first!=relation[j].second && relation[j].first==dom[i]){
				found=1;
				break;
			}
		}
		if(!found){
			max_elem[lm]=dom[i];
			lm+=1;
		}
	}
	return lm;
}

int find_min_elements(const pair *relation, int size, int *min_elem){
	int dom[MAX_REL_SIZE];
	int ldom, lm=0;
	ldom=get_domain(relation, size, dom);
	for(int i=0; i<ldom; i++){
		int found=0;
		for(int j=0; j<size; j++){
			if(relation[j].first!=relation[j].second && relation[j].second==dom[i]){
				found=1;
				break;
			}
		}
		if(!found){
			min_elem[lm]=dom[i];
			lm+=1;
		}
	}
	return lm;
}

int get_domain(const pair *relation, int size, int *domain){
	int max_value = 0, n=0;
	
    for (int i = 0; i < size; i++) {
        if (relation[i].first > max_value) {
            max_value = relation[i].first;
        }
        if (relation[i].second > max_value) {
            max_value = relation[i].second;
        }
    }
	
	for(int x=0; x<max_value+1; x++){
		for(int i=0; i<size; i++){
			if(relation[i].first==x || relation[i].second==x){
				domain[n]=x;
				n+=1;
				break;
			}
		}
	}
	return n;
}

// Case 3:

int composition (const pair *relation1, int size1, const pair *relation2, int size2, pair *result){
	int n=0;
	pair t;
	for(int i=0; i<size1; i++){
		for(int j=0; j<size2; j++){
			if(relation1[i].second==relation2[j].first){
				t.first=relation1[i].first;
				t.second=relation2[j].second;
				result[n]=t;
				n+=1;
			}
		}
	}
	for(int i=0; i<n; i++){
		for(int j=i+1; j<n; j++){
			if(result[i].first==result[j].first && result[i].second==result[j].second){
				n-=1;
				break;
			}
		}
	}
	return n;
}

// Comparator for pair
int cmp_pair (const void *a, const void *b) {
}

int insert_int (int *tab, int n, int new_element) {
}

// Add pair to existing relation if not already there
int add_relation (pair *tab, int n, pair new_pair) {
	for(int i=0; i<n; i++){
		if(tab[i].first==new_pair.first && tab[i].second==new_pair.second){
			return n;
		}
	}
	tab[n]=new_pair;
	n+=1;
	return n;
}

// Read number of pairs, n, and then n pairs of ints
int read_relation(pair *relation) {
	int n;
	pair x;
	scanf("%d", &n);
	for(int i=0; i<n; i++){
		scanf("%d %d\n", &x.first, &x.second);
		relation[i]=x;
	}
	return n;
}

void print_rel(pair *relation, int n) {
	printf("%d\n", n);
	for(int i=0; i<n; i++){
		printf("%d %d", relation[i].first, relation[i].second);
	}
}

void print_int_array(const int *array, int n){
	printf("%d\n", n);
	for(int i=0; i<n; i++){
		printf("%d ", array[i]);
	}
	printf("\n");
}

int main(void) {
	int to_do;
	pair relation[MAX_REL_SIZE];
	pair relation_2[MAX_REL_SIZE];
	pair comp_relation[MAX_REL_SIZE];
	int domain[MAX_REL_SIZE];
	int max_elements[MAX_REL_SIZE];
	int min_elements[MAX_REL_SIZE];

	scanf("%d",&to_do);
	int size = read_relation(relation);
	int ordered, size_2, n_domain;

	switch (to_do) {
		case 1:
			printf("%d ", is_reflexive(relation, size));
			printf("%d ", is_irreflexive(relation, size));
			printf("%d ", is_symmetric(relation, size));
			printf("%d ", is_antisymmetric(relation, size));
			printf("%d ", is_asymmetric(relation, size));
			printf("%d\n", is_transitive(relation, size));
			break;
		case 2:
			ordered = is_partial_order(relation, size);
			n_domain = get_domain(relation, size, domain);
			printf("%d %d\n", ordered, is_total_order(relation, size));
			print_int_array(domain, n_domain);
			if (!ordered) break;
			int no_max_elements = find_max_elements(relation, size, max_elements);
			int no_min_elements = find_min_elements(relation, size, min_elements);
			print_int_array(max_elements, no_max_elements);
			print_int_array(min_elements, no_min_elements);
			break;
		case 3:
			size_2 = read_relation(relation_2);
			printf("%d\n", composition(relation, size, relation_2, size_2, comp_relation));
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}
	return 0;
}

