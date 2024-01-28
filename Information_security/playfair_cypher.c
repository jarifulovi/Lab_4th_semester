#include<stdio.h>
#include<string.h>
#include<ctype.h>
char key[5][5];

void printkey(char key[5][5]){
     for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%c ",key[i][j]);
        }
        printf("\n");
    }
}

void generateKey(char keyword[]) {
  
    char uniqueKey[26] = {0};
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
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            key[i][j] = uniqueKey[k++];
        }
    }
}
// finding the position (row and col) of a character
void findPosition(char ch,int* row,int* col){
     for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if(key[i][j]==ch){
                *row = i;
                *col = j;
            }
        }
    }
}


void generateCypher(char string[]){

    int row1=0,row2=0,col1=0,col2=0;
    int stringLength = strlen(string);
    char bongusChar = 'z';
    char cypher[100];
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
        // if the characters are same then add 'x'
        if(first==second){
            second = 'x';
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
    printf("The cypher string is %s",cypher);
}

int main(){
    char keyword[100];
    char string[100];
    printf("Enter the keyword\n");
    scanf(" %s",&keyword);
    printf("Enter the string \n");
    scanf(" %s",&string);
    // first create the 5x5 board of characters
    generateKey(keyword);
    printkey(key);
    // generates the cypher of the string
    generateCypher(string);
    return 0;
}