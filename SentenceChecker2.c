#include<stdio.h>
#include<string.h>
#include<ctype.h>
char *str;//input string
//char *res;//output string
char endChar[] = {'.', ';', ',', '!', '?'};
long size;//file size
int l;//input string length
int wordcount = 0;//number of word in the input paragraph
int charcount = 0;//number of character in the input paragraph
//Check uppercase errors
int checkUpperCaseError() {
	int i;
	for (i = 0; i < l; ++i) {
		if (isupper(str[i]) && (!validUpperCase(i))) {
			str[i] = tolower(str[i]);
			//printf("check\n");
		}			
	}	
	return 0;
}

int validUpperCase(int i) {
	int j;
	// Return true if i is the first character of the paragraph
	for (j = 0; j < l; j++) {
		if (j > i) return 0;
		if ((j == i) && (str[j] != ' ')) return 1;
		if (str[j] != ' ') break;
	}
	if (i == 0) return 1;
	for (j = i - 1; j > -1; --j) {
		if (isAnEndChar(j)) return 1;//True if it's after a '.'
		else if (str[j] != ' ') return 0;//False otherwise
	}
	return 0;
}

//Check lowercase errors
int checkLowerCaseError() {
	int i;
	for (i = 0; i < l; ++i) {
		if (validUpperCase(i)) {
			str[i] = toupper(str[i]);
			//printf("check\n");
		}			
	}	
	return 0;
}

//Get the initial information of the paragraph
//wordcount, charcount, etc...
int getInfo() {
	//l = strlen(str);//l is the length of the input string.
	l = size;
	printf ("Size of myfile.txt: %ld bytes.\n",l);
	int i, j, wordcheck;
	wordcheck = 0;
	for (i = 0; i < l; ++i) {
		//a character != ' ' marks the beginning of a word
		if (!wordcheck && (str[i]!= ' ')) { 
			wordcount++;
			wordcheck = 1;
		}
		//character ' ' means it is not within a word
		if (str[i] == ' ') {			
			wordcheck = 0;
		}				
		else charcount++;
	}	
	str[l - 1] = ' ';//last barrier
}

//Check if str[i] if it's one of the characters .,!;?
int isAnEndChar(int i) {
	int j;
	for (j = 0; j < strlen(endChar); ++j) 
		if (str[i] == endChar[j]) return 1;
	return 0;
}

//check if character str[i] is valid in the paragraph
int validCharacter(int i) {	
	if ((str[i] == ' ') && (str[i+1] == ' ')) return 0;
	else if ((str[i] == ' ') && isAnEndChar(i+1)) return 0;
	else if (
		isAnEndChar(i) 
		&& !isAnEndChar(i+1) 
		&& (str[i+1] != ' ')
	) return 0;
	else if (isAnEndChar(i) && isAnEndChar(i+1)) return 0;	
	return 1;
}

//Correct spaces error
int removeSpaces() {	
	//remove spaces at the beginning of the paragraph	
	int i, j;
	for (i = 0; i < l; ++i) {
		if (str[i] != ' ') break;
	}
	//remove multiple spaces between 2 words
	j = 0;	
	for (; i < l; ++i)	 {
		if (validCharacter(i)) {//not 2 spaces near each other
			str[j++] = str[i];
		}
	}	
	l = j - 3;//new length
	//while (str[l] == ' ') l = l - 1;//remove spaces at the end of the string
	//printf("%c", str[l]);
	return 0;
}

int main() {
	//Open file containing input.
	FILE *input, *output;
	input = fopen("input.txt" , "r");
	output = fopen("output.txt" , "w");
	//File errors handling
	if(input == NULL) {
    perror("Error opening file");
    return(-1);
  }
  else {
    fseek (input, 0, SEEK_END);   // non-portable
    size=ftell (input);
    //fclose (pFile);
    printf ("Size of myfile.txt: %ld bytes.\n",size);
    fseek (input, 0, SEEK_SET);
    str = (char *)malloc(sizeof(char) * size);    
    fgets(str, size+1, input);
	}	
	fclose(input);
	//Get input paragraph information
	getInfo();	
	//Remove spaces at start of the paragraph
	removeSpaces();
	//Check uppercase errors
	checkUpperCaseError();
	
	//Check lowercase errors
	checkLowerCaseError();	
	int i;
	// paste result	
	printf ("Size of myfile.txt: %ld bytes.\n",l);
	//res = (char *)malloc(sizeof(char) * 52);
	for (i = 0; i < l; ++i) {
		//res[i] = str[i];
		fprintf(output, "%c", str[i]);	
	}	
	//fprintf(output, "%s", res);	
	free(str);
	fclose(output);
	return 0;
}
