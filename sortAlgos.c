//S13 MC01 GROUP 42 - CABRERA,J. DY,S. LU,B. ONG,C
//Combined version of both sorting algorithms
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define max 2049 
//change this value based on the desired size of the string (128, 256, 512... 2^n)

typedef char String[max];

//helper function for generating the random strin
char randc() {
	int r = rand() % 4;
	switch (r) {
		case 0:
			return 'a';
			break;
		case 1:
			return 'c';
			break;
		case 2:
			return 'g';
			break;
		case 3:
			return 't';
			break;
	}
	return 'a';
}

//helper function to get the actual string suffixes
void getSuff(String inputText, String outputText, int index, int n){
	int i;
	outputText[n-index]='\0';
	for(i=index; i<n; i++){
		outputText[i-index]=inputText[i];
	}
}

//helper function to compare strings
int compareString(String text, int i, int j, int n){
	String suff1, suff2;
	getSuff(text, suff1, i, n);
	getSuff(text, suff2, j, n);
	return (strcmp(suff1, suff2));
}

//handles insertion sort
void insertSort(String text, int suffArr[], int n){
    int i,j, key;
    for (j=1;j<n;j++){
        key=suffArr[j];
        i=j-1;
        while(i>=0 && (compareString(text, suffArr[i], key, n)>0)){	
            suffArr[i+1]=suffArr[i];
            i=i-1;
        }
        suffArr[i+1]=key;
    }
}

//merge part of merge sort
void merge(String text, int sub1_suffArr[], int sub2_suffArr[], int suffArr[], int n, int n1, int n2){
	int i, ctr1=0,ctr2=0;
	int textLength = strlen(text);
	for (i=0;i<n1+n2;i++){
		if (ctr2==n2 || (  (ctr1 < n1) && (compareString(text, sub1_suffArr[ctr1], sub2_suffArr[ctr2], textLength )<0 ))){ 
			suffArr[i]=sub1_suffArr[ctr1];
			ctr1++;
		}
		else{
			suffArr[i]=sub2_suffArr[ctr2];
			ctr2++;
		}
	}
}

//handles merge sort
void mergeSort(String text, int suffArr[], int n){
	if (n>1){
		int i, mid = n/2;
		int sub1_suffArr[mid];
		int sub2_suffArr[n-mid];
		for (i=0;i<mid;i++)
			sub1_suffArr[i]=suffArr[i];	
		for (i=0;i<n-mid;i++)
			sub2_suffArr[i]=suffArr[mid+i];
			
		mergeSort(text,sub1_suffArr,mid);
		mergeSort(text,sub2_suffArr,n-mid);
		merge(text, sub1_suffArr, sub2_suffArr, suffArr, n, mid, n-mid);
	}
}

int main(){
	int wordLength = max-1, i=0;
	String text="";
	int suffArr[wordLength];
	srand(time(NULL));
	for (i = 0; i < wordLength; i++){ 
	//generating the random input as well as preparing the initial array
		text[i] = randc();
		suffArr[i]=i;
	}
	text[wordLength]='\0'; //making sure the string is structured properly and ends with a null byte
	
    printf("THE TEXT IS: %s\n", text);
    
    //insertSort(text, suffArr, wordLength);	
    mergeSort(text, suffArr, wordLength);
    //Comment and uncomment the two above functions based on which sorting is to be used
    
    printf("Sorted Suffix Array: ");
	for (i=0;i<wordLength;i++){
		printf("%d ",suffArr[i]);
	}
    printf("\nSorting complete. Total size: %d", wordLength);
        
    return 0;    
}
