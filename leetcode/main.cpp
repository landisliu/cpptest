#include "stdio.h"
#include "string.h"
extern "C"
{
	#include "roman_to_int.h"
#include "longest_string_in_array.h"
};

int main()
{
	char* str[3] ={""};
	printf("%s\n", longestCommonPrefix(str, 1));
	int c=0;
	scanf("%d",c);
	return 0;
}