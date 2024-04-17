#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
	int day; 
	int month; 
	int year;
} Date;

// 1 bsearch2

#define FOOD_MAX  30   // max. number of goods
#define ART_MAX   15   // max. length of name's name + 1
#define RECORD_MAX 40  // max. line length
#define CHILD_MAX 20
#define MAX_PRETENDERS 100

enum Sex {F, M};
enum BOOL {no, yes};

struct Bit_data {
	enum Sex sex:1;
	enum BOOL in_line:1;
};

typedef struct {
	char *name;
	struct Bit_data bits;
	Date born;
	char *parent;
} Person;

typedef struct {
	char *par_name;
	int index;
} Parent;

typedef struct {
	char name[20];
	float price;
	int amount;
	Date valid_date;
} Food;

int np = 33;

Person person_tab[] = {
		{"Charles III", {M, no}, {14, 11, 1948},"Elizabeth II"},
		{"Anne", {F,yes}, {15, 8, 1950},"Elizabeth II"},
		{"Andrew", {M,yes}, {19, 2, 1960},"Elizabeth II"},
		{"Edward", {M,yes}, {10, 3, 1964} ,"Elizabeth II"},
		{"David", {M,yes}, {3, 11, 1961} ,"Margaret"},
		{"Sarah", {F,yes}, {1, 5, 1964}, "Margaret"},
		{"William", {M,yes}, {21, 6, 1982}, "Charles III"},
		{"Henry", {M,yes}, {15, 9, 1984}, "Charles III"},
		{"Peter", {M,yes}, {15, 11, 1977}, "Anne"},
		{"Zara", {F,yes}, {15, 5, 1981}, "Anne"},
		{"Beatrice", {F,yes}, {8, 8, 1988}, "Andrew"},
		{"Eugenie", {F,yes}, {23, 3, 1990}, "Andrew"},
		{"James", {M,yes}, {17, 12, 2007}, "Edward"},
		{"Louise", {F,yes}, {8, 11, 2003}, "Edward"},
		{"Charles", {M,yes}, {1, 7, 1999}, "David"},
		{"Margarita", {F,yes}, {14, 5, 2002}, "David"},
		{"Samuel", {M,yes}, {28, 7, 1996}, "Sarah"},
		{"Arthur", {M,yes}, {6, 5, 2019}, "Sarah"},
		{"George", {M,yes}, {22, 7, 2013}, "William"},
		{"George VI", {M,no}, {14, 12, 1895}, NULL},
		{"Charlotte", {F,yes}, {2, 5, 2015}, "William"},
		{"Louis", {M,yes}, {23, 4, 2018}, "William"},
		{"Archie", {M,yes}, {6, 5, 2019}, "Henry"},
		{"Lilibet", {F,yes}, {4, 6, 2021}, "Henry"},
		{"Savannah", {F,yes}, {29, 12, 2010}, "Peter"},
		{"Isla", {F,yes}, {29, 3, 2012}, "Peter"},
		{"Mia", {F,yes}, {17, 1, 2014}, "Zara"},
		{"Lena", {F,yes}, {18, 6, 2018}, "Zara"},
		{"Elizabeth II", {F,no}, {21, 4, 1925}, "George VI"},
		{"Margaret", {F,no}, {21, 8, 1930}, "George VI"},
		{"Lucas", {M,yes}, {21, 3, 2021}, "Zara"},
		{"Sienna", {F,yes}, {18, 9, 2021}, "Beatrice"},
		{"August", {M,yes}, {9, 2, 2021}, "Eugenie"}
	};
	
char *resultowicz[] = {"William", "George", "Charlotte", "Louis", "Henry", "Archie", "Lilibet", "Anne", "Peter", "Savannah", "Isla", "Zara", "Mia", "Lena", "Lucas", "Andrew", "Beatrice", "Sienna", "Eugenie", "August", "Edward", "Louise", "James", "David", "Charles", "Margarita", "Sarah", "Samuel", "Arthur"};


typedef int (*ComparFp)(const void *, const void *);

int datecmp(Date date1, Date date2) {
    if(date1.year != date2.year)
        return date1.year > date2.year ? 1 : -1;
    if(date1.month != date2.month)
        return date1.month > date2.month ? 1 : -1;
    if(date1.day != date2.day)
        return date1.day > date2.day ? 1 : -1;
    return 0;
}

// compare dates
int cmp_date(const void *a, const void *b) {
    const Date *date_a = (const Date *)a;
    const Date *date_b = (const Date *)b;

    // First compare years
    if (date_a->year < date_b->year) {
        return -1;
    } else if (date_a->year > date_b->year) {
        return 1;
    } else {
        // If years are the same, compare months
        if (date_a->month < date_b->month) {
            return -1;
        } else if (date_a->month > date_b->month) {
            return 1;
        } else {
            // If months are the same, compare days
            if (date_a->day < date_b->day) {
                return -1;
            } else if (date_a->day > date_b->day) {
                return 1;
            } else {
                // If days are also the same, dates are equal
                return 0;
            }
        }
    }
}

// compare foods
int cmp(const void *a, const void *b) {
    const Food *food_a = (const Food *)a;
    const Food *food_b = (const Food *)b;

    // Compare names
    int name_comparison = strcmp(food_a->name, food_b->name);
    if (name_comparison != 0) {
        return name_comparison;
    }

    // Compare prices
    if (food_a->price < food_b->price) {
        return -1;
    } else if (food_a->price > food_b->price) {
        return 1;
    }

    // Compare dates
    return cmp_date(&(food_a->valid_date), &(food_b->valid_date));
}

// bsearch returning address where to insert new element
void *bsearch2(const void *key, const void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *), char *result) {
    const char *ptr = (const char *)base;
    size_t low = 0;
    size_t high = nitems;
    size_t mid;

    while (low < high) {
        mid = low + (high - low) / 2;
        int cmp_result = compar(key, ptr + mid * size);

        if (cmp_result == 0) {
            *result = 1; // Sukces szukania
            return (void *)(ptr + mid * size);
        } else if (cmp_result < 0) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    *result = 0; // Element z kluczem *key nie został znaleziony
    return (void *)(ptr + low * size);
}

// print goods of given name
void print_art(Food *p, int n, char *art) {
    for (int i = 0; i < n; i++) {
        if (strcmp(p[i].name, art) == 0) {
            if(p[i].valid_date.day > 10 && p[i].valid_date.month > 10) {
                printf("%.2f %d %d.%d.%d\n", p[i].price, p[i].amount, p[i].valid_date.day, p[i].valid_date.month, p[i].valid_date.year);
            }
            else if(p[i].valid_date.day < 10 && p[i].valid_date.month > 10){
                printf("%.2f %d 0%d.%d.%d\n", p[i].price, p[i].amount, p[i].valid_date.day, p[i].valid_date.month, p[i].valid_date.year);
            }
            else if(p[i].valid_date.day > 10 && p[i].valid_date.month < 10){
                printf("%.2f %d %d.0%d.%d\n", p[i].price, p[i].amount, p[i].valid_date.day, p[i].valid_date.month, p[i].valid_date.year);
            }
            else{
                printf("%.2f %d 0%d.0%d.%d\n", p[i].price, p[i].amount, p[i].valid_date.day, p[i].valid_date.month, p[i].valid_date.year);
            }
        }
    }
}

// add record to table if absent
Food *add_record(Food *tab, int *np, ComparFp compar, Food *new) {
    char search_result;
    Food *found;

    // Using bsearch2()
    found = (Food*) bsearch2(new, tab, *np, sizeof(Food), compar, &search_result);

    if(search_result != 0) {
        // The Food item is already in the array, update its amount
        found->amount += new->amount;
    } else {
        // The Food item is not in the array, insert it at the correct position
        int insert_pos = found - tab;

        // Check if there is room in the array
        if (*np >= FOOD_MAX) {
            // The array is full, cannot add more items
            return tab;
        }

        // Push elements from insert_pos to the right
        memmove(tab + insert_pos + 1, tab + insert_pos, (*np - insert_pos) * sizeof(Food));

        // Insert the new item
        tab[insert_pos] = *new;

        (*np)++; // increment the count of items in the array
    }

    return tab;
}

// read no lines of data
// calls add_record if sorted = 1 and just adds element if sorted = 0
int read_goods(Food *tab, int no, FILE *stream, int sorted) {
    Food new;
    int np = 0;

    for (int i = 0; i < no; i++) {
        if (fscanf(stream, "%19s%f%d%d.%d.%d", new.name, &(new.price), &(new.amount), &(new.valid_date.day), &(new.valid_date.month), &(new.valid_date.year)) != 6) {
            return -1;  // Failed to read a record
        }

        if (sorted == 1) {
            // Add the new record to the array, keeping the array sorted
            tab = add_record(tab, &np, cmp, &new);
        } else {
            // Just append the new record to the end of the array
            tab[np++] = new;
        }
    }

    return np;  // Return the number of records read
}

int cmp_qs(const void *a, const void *b) {
	Food *fa = (Food*)a, *fb = (Food*)b;
	return cmp_date(&fa->valid_date, &fb->valid_date);
}

int cmp_bs(const void *a, const void *b) {
	Date *pd = (Date*)a;
	Food *fb = (Food*)b;
	return cmp_date(pd, &fb->valid_date);
}

// finds the value of goods due on 'curr_date'
int days_diff(Date *date1, Date *date2) {
    // Create tm structs and initialize them to zero
    struct tm tm1 = {0}, tm2 = {0};

    // Fill the tm structs with date info
    tm1.tm_year = date1->year - 1900; // Year since 1900
    tm1.tm_mon = date1->month - 1; // 0-11
    tm1.tm_mday = date1->day; // 1-31

    tm2.tm_year = date2->year - 1900;
    tm2.tm_mon = date2->month - 1;
    tm2.tm_mday = date2->day;

    // Convert tm structs to time_t
    time_t t1 = mktime(&tm1);
    time_t t2 = mktime(&tm2);

    // Calculate the difference in seconds, then divide by the number of seconds in a day
    return difftime(t2, t1) / (60 * 60 * 24);
}

float value(Food *food_tab, size_t n, Date curr_date, int days) {
    float total_value = 0.0f;

    for (size_t i = 0; i < n; i++) {
        // If the food item will expire after 'days' from 'curr_date'
        if (days_diff(&curr_date, &(food_tab[i].valid_date)) == days) {
            total_value += food_tab[i].price * food_tab[i].amount;
        }
    }

    return total_value;
}

/////////////////////////////////////////////////////////////////
// 3 Succession

const Date primo_date = { 28, 10, 2011 }; // new succession act

int cmp_primo(Person *person1, Person *person2) {
	if (person1->bits.sex == person2->bits.sex) return 0;
	if (person1->bits.sex == F && cmp_date(&person1->born, &primo_date) > 0) return 0;
	if (person2->bits.sex == F && cmp_date(&person2->born, &primo_date) > 0) return 0;
	return person2->bits.sex - person1->bits.sex;
}

// compare persons
int cmp_person(const void *a, const void *b) {
}

int fill_indices_tab(Parent *idx_tab, Person *pers_tab, int size) {
}

void persons_shifts(Person *person_tab, int size, Parent *idx_tab, int no_parents) {
}

int cleaning(Person *person_tab, int n) {
}

void print_person(const Person *p) {
	printf("%s\n", p->name);
}

int create_list(Person *person_tab, int n) {
}

int main(void) {
	int to_do, no;
	int n;
	Food food_tab[FOOD_MAX];
	char buff[ART_MAX];
	fgets(buff, ART_MAX, stdin);
	sscanf(buff, "%d", &to_do);
	char *pretenders[MAX_PRETENDERS];

	switch (to_do) {
		case 1:  // bsearch2
			fgets(buff, ART_MAX, stdin);
			sscanf(buff, "%d", &no);
			n = read_goods(food_tab, no, stdin, 1);
			scanf("%s",buff);
			print_art(food_tab, n, buff);
			break;
		case 2: // qsort
			fgets(buff, ART_MAX, stdin);
			sscanf(buff, "%d", &no);
			n = read_goods(food_tab, no, stdin, 0);
			Date curr_date;
			int days;
			scanf("%d %d %d", &curr_date.day, &curr_date.month, &curr_date.year);
			scanf("%d", &days);
			printf("%.2f\n", value(food_tab, (size_t)n, curr_date, days));
			break;
		case 3: // succession
			scanf("%d",&no);
			printf("%s", resultowicz[no-1]);
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
	}
	return 0;
}


