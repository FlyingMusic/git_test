#include <stdio.h>
#include <string.h>

int main()
{
	char input[] = "hello-world hi-you";
	char *pSave = NULL;
	char *value = strtok_r(input, " -", &pSave);
	printf("value = %s\n", value);
	while(NULL != value) {
		value = strtok_r(NULL, " -", &pSave);
		printf("value = %s\n", value);
	}
}
