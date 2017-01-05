/* 自守数 
 * Author: hx1997
 * Desc: 判断一个给定自然数是否为自守数（该数本身平方后的数仍以该数结尾的数） 
 */ 

#include <stdio.h>

int is_automorphic(int num) {
	int sqrd = num * num;
	int lsig_digit; int lsig_digit_sqrd;
	
	if(num > 44720) return -1;
	
	for(; num > 0; num /= 10, sqrd /= 10) {
		lsig_digit = num % 10;
		lsig_digit_sqrd = sqrd % 10;
		if(lsig_digit != lsig_digit_sqrd) return 0;
	}
	
	return 1;
}

int main(void) {
	int num_to_check;
	
	printf("Input a non-negative integer less than 44720: ");
	scanf(" %d", &num_to_check);
	
	if(num_to_check > 44720)
		printf("Invalid input.\n");
	else
		printf("%d is%s an automorphic number.\n", num_to_check, (is_automorphic(num_to_check) ? "" : " not"));
	
	return 0;
}
