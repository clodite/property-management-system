#include <stdio.h>
#include <string.h>

int add_account(const char *username, const char *password)
{
	FILE *fp = fopen("user.txt", "a"); 
	if (fp == NULL)
	{
		return -1; 
	}


	int success = 1;
	if (fprintf(fp, "%s\n%s\n%d\n", username, password, 1) < 0)
	{
		success = -1; 
	}

	fclose(fp);
	return success;
}
