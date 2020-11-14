#include "string.h"

char
peak(const char *p)
{
	return *(const char *)(&p + 1)[-1];
}
