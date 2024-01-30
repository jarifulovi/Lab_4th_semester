#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define SIZE 5
char key[5][5];
char bongusChar = 'z';


void printkey(char key[SIZE][SIZE]){
     for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ",key[i][j]);
        }
        printf("\n");
    }
}

void generateKey(char keyword[]) {
  
    char uniqueKey[25] = {0};
    int uniqueKeyIndex = 0;

    for (int i = 0; i < strlen(keyword); i++) {
        // if the keyword charcter is an alphabet
        if (isalpha(keyword[i])) {
            // transform the character into lower case
            char currentChar = tolower(keyword[i]);
            // if the character is not j and not in the uniqueKey array
            if (currentChar != 'j' && !strchr(uniqueKey, currentChar)) {
                uniqueKey[uniqueKeyIndex++] = currentChar;
            }
        }
    }

    // fill the remaining positions in the uniqueKey array with the alphabet
    for (char ch = 'a'; ch <= 'z'; ch++) {
        if (ch != 'j' && !strchr(uniqueKey, ch)) {
            uniqueKey[uniqueKeyIndex++] = ch;
        }
    }

    // fill the keyTable using the uniqueKey array
    int k = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            key[i][j] = uniqueKey[k++];
        }
    }
}
// finding the position (row and col) of a character
void findPosition(char ch,int* row,int* col){
     for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
          
            if((ch=='j' && key[i][j]=='i') || key[i][j]==ch){
                *row = i;
                *col = j;
                
                return;
            }
        }
    }
}


void generateCypher(char keyword[],char string[],char cypher[]){

    generateKey(keyword);
    int row1=0,row2=0,col1=0,col2=0;
    int stringLength = strlen(string);
   
    //char cypher[100];
    int cypherIndex = 0;

    for(int index=0;index<strlen(string);index++){
        char first = string[index++];
        char second;
        // if the string becomes odd then adding the bongus character
        if(index<strlen(string)){
            second = string[index];
        }
        else {
            second = bongusChar;
        }
        // if the characters are same then add bongus char
        if(first==second){
            second = bongusChar;
            index--;
        }

        findPosition(first,&row1,&col1);
        findPosition(second,&row2,&col2);

        if(row1==row2){
            cypher[cypherIndex++] = key[row1][(col1+1)%5];
            cypher[cypherIndex++] = key[row2][(col2+1)%5];
        }
        else if(col1==col2){
            cypher[cypherIndex++] = key[(row1+1)%5][col1];
            cypher[cypherIndex++] = key[(row2+1)%5][col2];
        }
        else {
            cypher[cypherIndex++] = key[row1][col2];
            cypher[cypherIndex++] = key[row2][col1];
        }
        
    }
    cypher[cypherIndex] = '\0';
    //printf("The cypher string is %s",cypher);
}
void removeCharAt(char decryptCypher[],int position,int length){
    for (int i = position; i < length-1; i++)
    {
       decryptCypher[i] = decryptCypher[i+1];
    }
    decryptCypher[length-1] = '\0';
    
}


void decrypt(char keyword[],char string[],char decryptCypher[]){

    if(strlen(string)%2==1){
        printf("The string is not encrypted.\n");
        return ;
    }
    
    generateKey(keyword);
    //printkey(key);

    int cypherIndex=0;
    // reverse the process to find the primary plain text
    for (int index = 0; index < strlen(string); index++)
    {
        char first = string[index++];
        char second = string[index];
        int row1,row2,col1,col2;
       
        findPosition(first,&row1,&col1);
        findPosition(second,&row2,&col2);
    

        if(row1==row2){
            decryptCypher[cypherIndex++] =  key[row1][(col1-1 + SIZE)%SIZE];
            decryptCypher[cypherIndex++] =  key[row2][(col2-1 + SIZE)%SIZE];
          
        }
        else if(col1==col2){
            decryptCypher[cypherIndex++] = key[(row1-1 + SIZE)%SIZE][col1];
            decryptCypher[cypherIndex++] = key[(row2-1 + SIZE)%SIZE][col2];
        }
        else {
            decryptCypher[cypherIndex++] = key[row1][col2];
            decryptCypher[cypherIndex++] = key[row2][col1];
        }
    }
    decryptCypher[cypherIndex] = '\0';
   
    // remove the bongus character 
    int d_length = strlen(decryptCypher);
    if(decryptCypher[d_length-1]==bongusChar) decryptCypher[d_length-1] = '\0';
    // reomove the middle bongus characters
    for(int i = 1; i < d_length-1; i++){
        if(decryptCypher[i-1]==decryptCypher[i+1]){
            if(decryptCypher[i]==bongusChar){
                removeCharAt(decryptCypher,i,d_length);
                i--;
            }
        }
    }

}

int main(){
    char keyword[100];
    char string[100];
    char cypher[100];
    char decryptCypher[100];
    printf("Enter the keyword\n");
    scanf(" %s",&keyword);
    printf("Enter the string \n");
    scanf(" %s",&string);

    // generates the cypher of the string
    generateCypher(keyword,string,cypher);
    printf("The encrypted string is : %s\n",cypher);
    printkey(key);
    // decrypt the cypher
    // there is an issue when decrypting it cannot distinguish
    // between i and j
    decrypt(keyword,cypher,decryptCypher);
    printf("The decrypted string is : %s\n",decryptCypher);
    printf("%c",bongusChar);
    return 0;
}