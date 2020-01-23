#include <string.h>
#include <stdlib.h>
#define  INT_MAX 2147483647

char * longestCommonPrefix(char ** strs, int strsSize){
	if(strsSize == 0)
		return "";
	int cur_size = 0;
	int equal_size = strlen(*strs);
	for(cur_size = 0; cur_size < strsSize-1; cur_size++)
	{
		int cur_equal_size = 0;
		char* str = *(strs + cur_size);
		char* next_str = *(strs+(cur_size+1));
		while(*str== *next_str && (*str != '\0') && cur_equal_size < equal_size)
		{
			str++;
			next_str++;
			cur_equal_size++;
		}

		if(cur_equal_size == 0)
		{
			return "";
		}

		equal_size = cur_equal_size;
	}

	char* ret = (char*)malloc(equal_size+1);
	memset(ret, 0, equal_size+1);
	strncpy(ret ,*strs, equal_size);
	return ret;
}