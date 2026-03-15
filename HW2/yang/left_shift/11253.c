#include <stdio.h>
#include "function.h"
int main(){
	char str[111];
	int n,l,r;
	scanf("%s",str);
	scanf("%d",&n);
	while(n--){
		scanf("%d%d",&l,&r);
		shift(&str[l-1], &str[r-1]);
	}
	printf("%s\n",str);
}