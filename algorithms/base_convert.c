/* 进制转换 
 * Author: hx1997
 * Desc: 将输入的任意进制正整数转换为其他进制 
 */ 

#include <stdio.h>

#define BUFSIZE 100

char hex_digits[17] = "0123456789abcdef";

int hexch2decnum(char hex_ch) {
	if (hex_ch >= '0' && hex_ch <= '9')
		return hex_ch - '0';
	else if (hex_ch >= 'a' && hex_ch <= 'z')
		return hex_ch - 'a' + 10;
	else if (hex_ch >= 'A' && hex_ch <= 'Z')
		return hex_ch - 'A' + 10;
	else
		return -1;
}

int convert(int src_base, char *src_num, int dest_base, char *dest_num) {
	char *p = dest_num;
	int dec = 0, remainder = 0;

	if (dest_base > 16) return -1;
	
	while (*src_num != '\0')
		dec = dec * src_base + hexch2decnum(*src_num++);
	
	for (; dec > 0; dec /= dest_base) {
		remainder = dec % dest_base;
		*dest_num++ = hex_digits[remainder];
	}
	*dest_num-- = '\0';
	
	while (dest_num > p) {
		char tmp = *dest_num;
		*dest_num-- = *p;
		*p++ = tmp;
	}
	
	return 0;
}

int main(void) {
	int src_base, dest_base;
	char src_num[BUFSIZE] = {0}, dest_num[BUFSIZE] = {0};
	
	printf("Input a positive integer and its base, seperated by a space: ");
	scanf(" %s %d", src_num, &src_base);
	
	printf("What base do you want to convert (%s)%d into? (<= 16) ", src_num, src_base);
	scanf(" %d", &dest_base);
	
	if (dest_base > 16) {
		printf("Invalid input.\n");
	} else {
		convert(src_base, src_num, dest_base, dest_num);
		printf("%s\n", dest_num);
	}
	
	return 0;
}
