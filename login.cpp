#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int get_account_type(const char *username, const char *password)
{
	FILE *fp = fopen("user.txt", "r");
	if (fp == NULL)
	{
		return -1;
	}

	char file_user[256];
	char file_pass[256];
	char type_str[256];

	while (fgets(file_user, sizeof(file_user), fp) != NULL)
	{
		file_user[strcspn(file_user, "\n")] = '\0';

		if (fgets(file_pass, sizeof(file_pass), fp) == NULL)
		{
			fclose(fp);
			return -1;
		}
		file_pass[strcspn(file_pass, "\n")] = '\0';

		if (fgets(type_str, sizeof(type_str), fp) == NULL)
		{
			fclose(fp);
			return -1;
		}
		type_str[strcspn(type_str, "\n")] = '\0';

		if (strcmp(username, file_user) == 0 && strcmp(password, file_pass) == 0)
		{
			fclose(fp);
			return atoi(type_str);
		}
	}

	fclose(fp);
	return -1;
}
