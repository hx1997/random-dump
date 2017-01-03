/* 长整数高精度加法
 * Author: hx1997
 * Desc: 1000 位以内的长整数加法运算
 */ 

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#define BUFSIZE		1001
#define max(a, b)	(a>b?a:b)

#define CARRY		1
#define NO_CARRY	0

int str_to_revi(char *str, int ary[], int arysize) {
	int len = strlen(str);
	
	if(arysize < len)
		return -1;
	
	for(int i = 0; i < len; i++) {
		ary[i] = str[len - i - 1] - '0';
	}
	
	return 0;
}

char *long_add(char *op1, char *op2) {
	char *buf;
	int rev_op1[BUFSIZE] = {0}, rev_op2[BUFSIZE] = {0};
	int len1, len2;
	int state = NO_CARRY;
	int i;
	
	len1 = strlen(op1);
	len2 = strlen(op2);
	
	buf = (char *)calloc(BUFSIZE, sizeof(char));
	
	if(len1 < 10 && len2 < 10) {
		itoa(atol(op1) + atol(op2), buf, 10);
	} else {
		int max_len = max(len1, len2);
		
		str_to_revi(op1, rev_op1, BUFSIZE);
		str_to_revi(op2, rev_op2, BUFSIZE);
		
		for(i = 0; i < max_len; i++) {
			int sum = rev_op1[i] + rev_op2[i] + state;
			state = (sum >= 10 ? CARRY : NO_CARRY);
			
			buf[i] = sum % 10 + '0';
		}
		
		if(state) buf[i] = '1';
		
		return strrev(buf);
	}
	
	return buf;
}

int main(void) {
	char op1[BUFSIZE], op2[BUFSIZE];
	
	printf("Input the operands a and b: ");
	scanf(" %s %s", op1, op2);
	
	char *buf = long_add(op1, op2);
	printf("a + b = %s", buf);
	
	free(buf);
	
	return 0;
}
