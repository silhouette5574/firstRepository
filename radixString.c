# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>

void radix_sort(char **,int,int);

int main()
{
	char **input;
	char ch=' ';
	int n,k,i,j;
	srand(time(NULL));
	scanf("%d",&n);
	scanf("%d",&k);
	input = (char **)malloc(n*sizeof(char *));
	for(i=0;i<n;i++)
	{
		input[i]=(char *)malloc((k+1)*sizeof(char));
		for(j=0;j<k;j++)
			input[i][j]=(rand()%(90 - 65 +1))+65;
		input[i][k]='\0';
	}
	for(i=0;i<n;i++){
		printf("%s\n",input[i]);
	}
	printf("\n\n");
	radix_sort(input,n,k);

	for(i=0;i<n;i++){
		printf("%s\n",input[i]);
	}
	printf("\n");
	return 0;
}

void count_sort(char **input, int n ,int k, int pos){
	printf("In Count Sort\n");
	int i;
	int count[100];
	for(i = 0; i < 100; i++)
		count[i] = 0;
	char **output;
	output = (char **)malloc(n*sizeof(char *));
	for(i = 0; i < n; i++)
		count[input[i][pos]-32]++;
	for(i = 1; i < 100; i++)
		count[i] = count[i] + count[i-1];
	for(i = n-1; i >= 0; i--)
	{
		output[count[input[i][pos]-32]-1] = input[i];
		count[input[i][pos]-32]--;
	}
	for(i = 0; i < n; i++)
		input[i] = output[i];
}

void radix_sort(char **input,int n,int k){
	int i;		
	for(i = k - 1; i >= 0; i--)
		count_sort(input,n,k,i);
}
