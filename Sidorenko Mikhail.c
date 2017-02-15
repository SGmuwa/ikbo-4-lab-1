#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_FILE_OPEN -3
#define LENGHT_STRING_INPUT 256

struct FileSegment
{
	int a;
	char str[255];
	float f;
};

void RawnStruct(struct FileSegment* a, struct FileSegment* b)
{
	int i;
	a->a = b->a;
	a->f = b->f;
	for (i = 0; i < 255; i++)
	{
		a->str[i] = b->str[i];
	}
}

void PrintFileSegment(struct FileSegment a)
{
	printf("%d\t%s\t%f\n", a.a, a.str, a.f);
}

void OpenArg(int argc, char ** argv, char * strFile, FILE ** input)
{
	int i = 0;
	if (argc > 1)
	{
		for (i = strlen(argv[1]); i >= 0 && i < LENGHT_STRING_INPUT; i--)
		{
			strFile[i] = argv[1][i];
		}
		fopen_s(input, strFile, "rb");
		if (input == NULL)
		{
			puts("File in argument not found.\n");
			strFile = 0;
		}
		else
		{
			puts(strFile);
		}
	}
}

int main(int argc, char ** argv)
{
	FILE * input = NULL;
	char strFile[LENGHT_STRING_INPUT] = { 0 };
	struct FileSegment buffer = { 0, {0}, 0 };
	int i;
	int count = 0;
	puts("Hello world!\n");
	OpenArg(argc, argv, strFile, &input);
	if(strFile[0] == 0) do
	{
		puts("No arguments.\nFilename: ");
		gets_s(strFile, LENGHT_STRING_INPUT);
		fopen_s(&input, strFile, "rb");
		if (input == NULL)
		{
			puts("File not found.\n");
		}
	} while (input == NULL);
	do
	{
		i = fread(&buffer, sizeof(struct FileSegment), 1, input);
		if (i > 0)
		{
			count++;
			PrintFileSegment(buffer);
		}
	} while (i > 0);
	printf("SIZE: %ld", count * sizeof(struct FileSegment));
}
