#include <stdio.h>
#include <stdarg.h>

int main(int argc, char const *argv[])
{
	int max_int(int n, ...);
	printf("%d\n", max_int(6,1,2,3,4,5,6));
	return 0;
}

int max_int(int n, ...){
	va_list ap;
	int sum = 0;
	va_start(ap, n);
	for (int i = 0; i < n; ++i)
		sum += va_arg(ap, int);
	return sum;
}