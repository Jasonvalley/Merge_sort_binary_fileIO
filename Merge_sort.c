#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
void generate_random_num(char filename[]);
enum generate_random_num{generated_number=2000000,intial_runsize=10000,range_number=2000000};
//intial_runsize<240000
void merge_sort(int list[], int n);
void merge_sort_2(int list[], int templist[], int runsize,int n);
int main(void) {
	generate_random_num("input.txt","w");
}
void generate_random_num(char filename[])
{
	FILE *f = fopen(filename, "w");
	int i,j,*randlist=(int*)malloc(sizeof(int)*intial_runsize);
	srand(time(NULL));
	//generate randomnum and store
	for (i = 0; i < generated_number/intial_runsize; i++) {
		//generate rand list
		for (j = 0; j < intial_runsize; j++) {
			randlist[j] = rand() % range_number + 1;
		}
		merge_sort(randlist, intial_runsize);
		//store file name
		for (j = 0; j < intial_runsize; j++) {
			fprintf(f, "%d ", randlist[j]);
		}
		fprintf(f, "\n\n");
	}
	free(randlist);
}
void merge_sort(int list[], int n)
{
	int runsize = 1,*tempList=(int*)malloc(sizeof(int)*n);
	while (runsize < n) {
		merge_sort_2(list, tempList, runsize,n);	runsize *= 2;
		merge_sort_2(tempList, list, runsize,n);	runsize *= 2;
	}
}
void merge_sort_2(int list[], int templist[], int runsize,int n)
{
	long int startpoint = 0,store_count = 0;
	//n=runsize*2*count+a
	//ruusize*2*count
	for (; startpoint + 2 * runsize-1 < n; startpoint += runsize * 2) {
		int point1 = startpoint, point2 = startpoint + runsize, end1 = startpoint + runsize, end2 = startpoint + runsize * 2;
		while (point1 < end1 &&point2 < end2) {
			if (list[point1] < list[point2]) {
				templist[store_count] = list[point1];	store_count++;	point1++;
			}
			else {
				templist[store_count] = list[point2];	store_count++;	point2++;
			}
		}
		//take extra
		if (point1 < end1) {
			while (point1 <end1) {
				templist[store_count] = list[point1];	store_count++;	point1++;
			}
		}
		else if (point2 < end2) {
			while (point2 < end2) {
				templist[store_count] = list[point2];	store_count++;	point2++;
			}
		}
	}
	int extra_num = n - startpoint;
	//0<a<runsize
	if (extra_num < runsize) {
		while (startpoint < n) {
			templist[store_count] = list[startpoint]; startpoint++;
		}
	}
	//runsize<a
	else if (runsize < extra_num) {
		int point1=startpoint,point2 = startpoint + runsize,end1=startpoint+runsize,end2=n;
		while (point1 < end1 &&point2 < end2) {
			if (list[point1] < list[point2]) {
				templist[store_count] = list[point1];	store_count++;	point1++;
			}
			else {
				templist[store_count] = list[point2];	store_count++;	point2++;
			}
		}
		//take extra
		if (point1 < end1) {
			while (point1 < end1) {
				templist[store_count] = list[point1];	store_count++;	point1++;
			}
		}
		else if (point2 < end2) {
			while (point2 < end2) {
				templist[store_count] = list[point2];	store_count++;	point2++;
			}
		}
	}
}
