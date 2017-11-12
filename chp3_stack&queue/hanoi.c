#include <stdio.h>
int c = 0;

void move(char x, int n, char z){
	//
	printf("第%d步：将%d号盘从%c移到%c\n", ++c, n, x, z);
}

void hanoi(int n, char x, char y, char z){
	// 将塔座x上按直径由小至大且自上而下编号1至n的n个圆盘
	if(n==1)
		move(x,1,z);
	else{
		hanoi(n-1, x, z, y);
		move(x, n, z);
		hanoi(n-1, y, x, z);
	}
}

int main(int argc, char const *argv[])
{
	int n;
	printf("3个塔座为a、b、c，圆盘最初在a座，借助b座移到c座。请输入圆盘数：");
	scanf("%d", &n);
	hanoi(n, 'a', 'b', 'c');
	return 0;
}