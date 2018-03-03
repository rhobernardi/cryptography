#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char **create_table();
void print_table(char **);
char search(char **, int, char);
void encrypt(char *, char *, char *, char **);
void decrypt(char *, char *, char *, char **);


int main(int argc, char const *argv[])
{
	if(argc != 3) 
	{
		if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
		{
			printf("usage: %s <OPTION> \"<MESSAGE>\"\n\n", argv[0]);

			printf("OPTION:\n");
			printf("\t-h, --help \t this help.\n");
			printf("\t-e, --encrypt \t encrypt a message with a key.\n");
			printf("\t-d, --decrypt \t decrypt a message with a key.\n");
			printf("\t-ef, --encrypt-file \t encrypt a file with a key.\n");
			printf("\t-df, --decrypt-file \t decrypt a file with a key.\n\n");


			printf("%s --decrypt \"DECRYPT THIS\"\n", argv[0]);
			printf("%s -ef ./decrypted_file.txt\n", argv[0]);
		}

		else
		{
			printf("usage: %s <OPTION> \"<MESSAGE>\"\n\n", argv[0]);
			exit(1);
		}
	}

	char **v_table, *str, *key, *crypt_str;
	v_table = create_table();

	//print_table(v_table);


	if (strcmp(argv[1], "-e") == 0 || strcmp(argv[1], "--encrypt") == 0)
	{
		str = (char *) malloc(strlen(argv[2]) * sizeof(char));
		key = (char *) malloc(strlen(argv[2]) * sizeof(char));
		crypt_str = (char *) malloc(strlen(argv[2]) * sizeof(char));
		strcpy(str, argv[2]);

		printf("Enter the Key: ");
		scanf("%s", key);

		encrypt(crypt_str, key, str, v_table);

		printf("\nEncrypted: %s\n", crypt_str);
		exit(0);
	}

	else if (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--decrypt") == 0)
	{
		str = (char *) malloc(strlen(argv[2]) * sizeof(char));
		key = (char *) malloc(strlen(argv[2]) * sizeof(char));
		crypt_str = (char *) malloc(strlen(argv[2]) * sizeof(char));
		strcpy(crypt_str, argv[2]);

		printf("Enter the Key: ");
		scanf("%s", key);

		decrypt(str, key, crypt_str, v_table);

		printf("\nDecrypted: %s\n", str);
	}

	else if (strcmp(argv[1], "-ef") == 0 || strcmp(argv[1], "--encrypt-file") == 0)
	{
		// NOT WORKING YET
		str = (char *) malloc(strlen(argv[2]) * sizeof(char));
		key = (char *) malloc(strlen(argv[2]) * sizeof(char));
		crypt_str = (char *) malloc(strlen(argv[2]) * sizeof(char));
		strcpy(str, argv[2]);

		//printf("Enter the Key: ");
		//scanf("%s", key);

		//encrypt(crypt_str, key, str, v_table);

		//printf("\nEncrypted: %s\n", crypt_str);
		exit(0);
	}

	else if (strcmp(argv[1], "-df") == 0 || strcmp(argv[1], "--decrypt-file") == 0)
	{
		// NOT WORKING YET
		str = (char *) malloc(strlen(argv[2]) * sizeof(char));
		key = (char *) malloc(strlen(argv[2]) * sizeof(char));
		crypt_str = (char *) malloc(strlen(argv[2]) * sizeof(char));
		strcpy(crypt_str, argv[2]);

		//printf("Enter the Key: ");
		//scanf("%s", key);

		//decrypt(str, key, crypt_str, v_table);

		//printf("\nDecrypted: %s\n", str);
	}

	return 0;
}



void encrypt(char *crypt_str, char *key, char *str, char **table)
{
	for (int i = 0, j = 0; j < strlen(str); ++i, ++j)
	{
		if (str[j] == ' ') 
		{
			--i;
			crypt_str[j] = ' ';
			continue;
		}

		if (i == strlen(key)) i = 0;

		crypt_str[j] = table[key[i]%65][str[j]%65];
	}
}

void decrypt(char *str, char *key, char *crypt_str, char **table)
{
	for (int i = 0, j = 0; j < strlen(crypt_str); ++i, ++j)
	{
		if (crypt_str[j] == ' ')
		{
			--i;
			str[j] = ' ';
			continue;
		}

		if (i == strlen(key)) i = 0;

		str[j] = search(table, key[i]%65, crypt_str[j]);
	}
}

char search(char **table, int index, char letter)
{
	for (int j = 0; j < 26; ++j)
	{
		if (table[index][j] == letter)
		{
			letter = table[0][j];
			break;
		}
	}

	return letter;
}

void print_table(char **table)
{
	for (int i = 0; i < 26; ++i)
	{
		for (int j = 0; j < 26; ++j)
		{
			printf("%c ", table[i][j]);
		}

		printf("\n");
	}
}

char **create_table()
{
	char **table;

	table = (char **) malloc(26 * sizeof(char*));
	for (int i = 0; i < 26; ++i)
		table[i] = (char *) malloc(26 * sizeof(char));

	table[0][0] = 'A';
	table[25][25] = 'Y';

	for (int i = 0; i < 25; ++i)
	{
		for (int j = 0; j < 25; ++j)
		{
			if (table[i][j]+1 > 'z') table[i][j+1] = 'a';
			else if (table[i][j]+1 > 'Z') table[i][j+1] = 'A';
			else table[i][j+1] = table[i][j]+1;
			
			if (table[i][j]+1 > 'z') table[i+1][j] = 'a';
			else if (table[i][j]+1 > 'Z') table[i+1][j] = 'A';
			else table[i+1][j] = table[i][j]+1;
		}
	}
	
	return table;
}