#include <stdio.h>

int hw4_islower(int ch)
{
	return ('a' <= ch && ch <= 'z');
}

int hw4_isupper(int ch)
{
	return ('A' <= ch && ch <= 'Z');
}

int hw4_isalpha(int ch)
{
	return (hw4_islower(ch) || hw4_isupper(ch));
}

int hw4_isdigit(int ch)
{
	return ('0' <= ch && ch <= '9');
}

int hw4_tolower(int ch)
{
	return ('A' <= ch && ch <= 'Z') ? ch - 'A' + 'a' : ch;
}

int hw4_toupper(int ch)
{
	return ('a' <= ch && ch <= 'z') ? ch - 'a' + 'A' : ch;
}

size_t hw4_strlen(const char* str)
{
	size_t cnt = 0;
	while (*(str+cnt) != '\0')
		++cnt;
	return cnt;
}

char* hw4_strchr(const char* str, int ch)
{
	size_t i = 0;
	while(1)
	{
		if (*(str + i) == ch)
		{
			char* p = (char*)str;
			return p + i;
		}
		if (*(str + i) == '\0')
			break;
		++i;
	}
	return NULL;
}

char* hw4_strcpy(char* dest, const char* src)
{
	if (dest == NULL || src == NULL)
		return dest;
	size_t i = 0;
	while(1)
	{
		*(dest + i) = *(src + i);
		if (*(src + i) == '\0')
			break;
		++i;
	}
	return dest;
}

char* hw4_strcat(char* dest, const char* src)
{
	char* pos = dest;
    while(*dest != '\0')
        ++dest;
    while(*src != '\0')
    {
        *dest = *src;
        ++src;
        ++dest;
    }
    *dest = *src;
    return pos;

}
int hw4_strcmp(const char* lhs, const char* rhs)
{
	while (*lhs == *rhs)
	{
		if (*lhs == '\0')
			return 0;
		++lhs;
		++rhs;
	}
	if (*lhs > *rhs)
		return 1;
	else
		return -1;
}
