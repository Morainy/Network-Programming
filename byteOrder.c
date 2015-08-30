/*
 * =====================================================================================
 *
 *       Filename:  byteOrder.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年08月22日 14时40分47秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>

void byteOrder()
{
	union{
		short value;
		char union_bytes[sizeof(short)];
	}test;
	test.value = 0x0102;
	if((test.union_bytes[0] == 1) && (test.union_bytes[1] == 2)){
		printf("big endian\n");
	}
	else if((test.union_bytes[0] == 2) && (test.union_bytes[1] == 1)){
		printf("little endian\n");
	}else{
		printf("unknown...\n");
	}
}

int main(int argc , char* argv[])
{
	byteOrder();
	return 0;
}
