/* 长整数高精度减法
 * Author: hx1997
 * Desc: 1000 位以内的长整数减法运算
 */ 

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#define BUFSIZE		1001
#define max(a, b)	(a>b?a:b)

#define BORROW		10
#define NO_BORROW	0

int str_to_revi(char *str, int ary[], int arysize) {
	int len = strlen(str);
	
	if(arysize < len)
		return -1;
	
	for(int i = 0; i < len; i++) {
		ary[i] = str[len - i - 1] - '0';
	}
	
	return 0;
}

/* Compares two numbers stored in char arrays
 * Returns:
 * 	1 - op1 > op2
 * 	0 - op1 == op2
 * 	-1 - op1 < op2
 */
int cmp_stri(char *op1, char *op2) {
	int len1, len2;
	
	len1 = strlen(op1);
	len2 = strlen(op2);
	
	if (len1 > len2) {
		return 1;
	} else if (len1 < len2) {
		return -1;
	}
	
	for (int i = 0; i < len1; i++) {
		if (op1[i] > op2[i])
			return 1;
		else if (op1[i] < op2[i])
			return -1;
	}
	
	return 0;
}

char *long_subtract(char *op1, char *op2) {
	char *buf;
	int rev_op1[BUFSIZE] = {0}, rev_op2[BUFSIZE] = {0};
	int len1, len2;
	int state = NO_BORROW;
	int i;
	int diff;
	int sign = 1;	// Determines if '-' sign precedes the outcome
	
	len1 = strlen(op1);
	len2 = strlen(op2);
	
	buf = (char *)calloc(BUFSIZE, sizeof(char));
	
	if(len1 < 10 && len2 < 10) {
		itoa(atol(op1) - atol(op2), buf, 10);
	} else {
		int max_len = max(len1, len2);
		
		/* Make sure op1 >= op2 so we can calculate op1 - op2 correctly */
		if (-1 == cmp_stri(op1, op2)) {
			sign = -1;
			char *tmp = op1;
			op1 = op2;
			op2 = tmp;
		}
		
		str_to_revi(op1, rev_op1, BUFSIZE);
		str_to_revi(op2, rev_op2, BUFSIZE);
		
		for (i = 0; i < max_len; i++) {
			if (state) rev_op1[i]--;	// Borrowed by less significant digit?
			diff = rev_op1[i] - rev_op2[i];
			state = (diff < 0 ? BORROW : NO_BORROW);	// Needs to borrow from more significant digit?
			
			buf[i] = diff + state + '0';
		}
		
		/* Remove trailing zeroes */
		i--;
		while (i > 0) {
			if (buf[i] != '0')
				break;
			else
				buf[i] = '\0';
			
			i--;
		}
		
		/* Add the '-' sign if outcome is negative */
		if (-1 == sign) buf[i+1] = '-';
		
		return strrev(buf);
	}
	
	return buf;
}

int main(void) {
	char op1[BUFSIZE], op2[BUFSIZE];
	
	printf("Input the operands a and b: ");
	scanf(" %s %s", op1, op2);
	
	char *buf = long_subtract(op1, op2);
	printf("a - b = %s", buf);
	
	free(buf);
	
	return 0;
}
