#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void encrypt(int key,char *fileContent,char *encryptFile);

int main(int argc, char const *argv[])
{
	FILE *file;
	char filePath[100];
	char encFileName[100];
	int key;
	long size;
	char *fileContent;
	char *encryptFile;
	
	printf("enter the path of your file:");
	scanf("%s",filePath);

	printf("enter encrypting key:");
	scanf("%d",&key);

	file = fopen(filePath,"rb");
	if(file == NULL){
		printf("could not open file\n");
		return 1;
	}

    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, 0, SEEK_SET);

    fileContent = (char*)malloc(size);
    encryptFile = (char*)malloc(size);

    fread(fileContent, sizeof(char), size, file);

	encrypt(key,fileContent,encryptFile);

	fclose(file);

	printf("enter a name for the encrypted file:");
	scanf("%s",encFileName);

	file = fopen(encFileName,"wb");
	if (file == NULL) {
        printf("Error: could not create output file\n");
        return 1;
    }

	fwrite(encryptFile,sizeof(char),strlen(encryptFile),file);
	fclose(file);

	printf("file encrypted successfuly\n");

	free(fileContent);
	free(encryptFile);

	return 0;
}

void encrypt(int key,char *fileContent,char *encryptFile){
	int length = strlen(fileContent);
	for (int i = 0; i < length; i++)
	{
		char c = fileContent[i];
		if (isalpha(c)) {
		    if (islower(c)) {
		        c = (c - 'a' + key) % 26 + 'a';
		    } else {
		        c = (c - 'A' + key) % 26 + 'A';
		    }
		}
		encryptFile[i] = c;
	}
	encryptFile[length] = '\0';	
}