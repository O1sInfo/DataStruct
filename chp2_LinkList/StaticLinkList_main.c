#include "myheader.h"
#include "StaticLinkList.h"

int main(int argc, char const *argv[])
{
	SLinkList La;
	int k, i;
	difference(&La, &k);
	i = La[k].cur;
	while(i){
		printf("%3d", La[i].data);
		i = La[i].cur;
	}
	printf("\n");
	return 0;
}