#include <stdio.h>
#define N 10
#define FALSE 0
#define TRUE 1

int main(int argc, char const *argv[])
{
	void bubble(int a[]);
	void bubble2(int a[]);
	int a[N];
	for (int i = 0; i < N; ++i)
	{
		scanf("%d", &a[i]);
	}
	bubble(a);
	for (int i = 0; i < N; ++i)
	{
		printf("%3d", a[i]);
	}
	printf("\n");
	return 0;
}

void bubble(int a[])
{
	int i,j,temp;
	for (int i = 1; i < N; ++i)
	{
		for (int j = 0; j < N-i; ++j)
		{
			if (a[j]>a[j+1])
			{
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}
}

void bubble2(int a[])
{
	int i,j,temp,change;
	i = N-1;
	do
	{
		change = FALSE;
		for (int j = 0; j < i; ++j)
		{
			if (a[j]>a[j+1])
			{
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = a[j];
				change = TRUE;
			}
		}
	}while(change && --i>=1);
}