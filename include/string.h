#ifndef _TOYOS_STRING_INCLUDE_
#define _TOYOS_STRING_INCLUDE_

typedef unsigned int size_t;
#undef NULL
#ifndef NULL
#define NULL 0
#endif

int strlen(const char * str);
int strcmp(char * lhs,char * rhs);
int strncmp(char * lsh,char * rhs,int n);
char * strcpy(char * dst,const char * src);
int strncpy(char * dst,char * src,int n);
int strcat(char * dst,char * src);
void * memset(void * buffer,int c,size_t num);
void * memcpy(void * dst,const void * src,size_t num);


#endif //_TOYOS_STRING_INCLUDE_
