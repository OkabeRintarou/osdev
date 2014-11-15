
#include "string.h"

int strlen(const char * str)
{
	if(str == NULL){
		return 0;
	}

	int len = 0;
	while(*str++){
		len++;
	}
	return len;
}

char * strcpy(char * dst,const char * src)
{
	if((dst == NULL) || (src == NULL)){
		return NULL;
	}
	while((*dst++ = *src++) != '\0'){
		;
	}
	return dst;
}

void * memcpy(void * dst,const void * src,size_t num)
{
	if((dst == NULL) || (src == NULL)){
		return NULL;
	}
	void * ret = dst;
	int i;
	for(i = 0; i < num;i++){
		*(char*)dst++ = *(char*)src++;
	}

	return ret;
}

void * memset(void * buffer,int ch,size_t num)
{
	int i;
	void * ret = buffer;
	const unsigned char uc = ch;
	for(i = 0; i < num;i++){
		*(char*)buffer++ = uc;
	}

	return ret;
}
