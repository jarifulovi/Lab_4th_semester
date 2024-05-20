#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define SIZE 26
char charTable[SIZE][SIZE+1];


void printTable(){
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            printf("%c ",charTable[i][j]);
        }
        printf("\n");
    }
}

void generateTable(){

    int i,j;
    for(i=0;i<SIZE;i++){
      
        for(j=0;j<SIZE;j++){
            int character = 'a' + ((i+j) % SIZE);
            charTable[i][j] = character;
        }
        charTable[i][j] = '\0';
    }
}
void expandKeyword(char keyword[100],char newKeyword[100],int sl,int kl){

    int i;
    for (i = 0; i < sl; i++)
    {
        newKeyword[i] = keyword[i%kl];
    }
    newKeyword[i] = '\0';
}


void generateCypher(char keyword[100],char string[100],char cypher[100]){
    
    // keyword should not be larger than string
    if(strlen(keyword)>strlen(string)){
        printf("keyword is small\n");
        return;
    }
    // expand the keyword into newkeyword
    char newKeyword[100];
    int stringLength = strlen(string);
    int keywordLength = strlen(keyword);
    expandKeyword(keyword,newKeyword,stringLength,keywordLength);
    
    for (int i = 0; i < strlen(string); i++)
    {
        int row = (tolower(string[i]) - 97);
        int col = (tolower(newKeyword[i]) - 97);

        cypher[i] = charTable[row][col];
    }
    
}
void decryption(char keyword[100],char string[100],char decryptString[100]){
    // first expand the keyword
   
    // keyword should not be larger than string
    if(strlen(keyword)>strlen(string)){
        printf("keyword is small\n");
        return;
    }
    // expand the keyword into newkeyword
    char newKeyword[100];
    int stringLength = strlen(string);
    int keywordLength = strlen(keyword);

    expandKeyword(keyword,newKeyword,stringLength,keywordLength);
    int i;
    for (i = 0; i < stringLength; i++)
    {
        int row = 0;
        // Adjust for negative values
        int col = (tolower(string[i]) - tolower(newKeyword[i]) + SIZE) % SIZE;

        decryptString[i] = charTable[row][col];
    }
    decryptString[i] = '\0';
}

int main() {
    char keyword[100],string[100],cypher[100],decryptString[100];
    printf("Enter the keyword : ");
    scanf(" %s",keyword);
    printf("Enter the string : ");
    scanf(" %s",string);
    generateTable();
    printTable();
    generateCypher(keyword,string,cypher);
    printf("The encrypted string : %s\n",cypher);
    decryption(keyword,cypher,decryptString);
    printf("The decrypted string : %s\n",decryptString);
    return 0;
}