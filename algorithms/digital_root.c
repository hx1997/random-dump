/* 数字乘积根 
 * Author: hx1997
 * Desc: 计算输入的正整数的数字乘积根 
 */ 

#include <stdio.h>
#include <stdlib.h>

int find_digital_root(int num) {
	int lsig_digit = 0; 
	int product = 1;
	
	while (num) {
		lsig_digit = num % 10;
		if (lsig_digit) product *= lsig_digit;
		num /= 10;
	}
	
	if (product < 10)
		return product;
	else
		return find_digital_root(product);
}

int main(void) {
	int num;
	
	printf("Input an integer: ");
	scanf("%d", &num);
	
	printf("%d is the digital product root of %d.\n", find_digital_root(num), num);
	
	return 0;
}
