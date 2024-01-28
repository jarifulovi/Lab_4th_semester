#include<stdio.h>
#include<string.h>

void decrypt(char str[100],int k){

    // iterate though each character in the string
    for(int i=0;i<strlen(str);i++){
        // check if the character is an uppercase letter
        if(str[i] >= 'A' && str[i] <= 'Z'){
            str[i] = (str[i] - 'A' - k + 26) % 26 + 'A';
        }
        // check if the character is a lowercase letter
        else if (str[i] >= 'a' && str[i] <= 'z') {
            // apply the Caesar cipher encryption for lowercase letters
            str[i] = (str[i] - 'a' - k + 26) % 26 + 'a';
        }
    }
    // print the encrypted string
    printf("Encrypted String: %s\n", str);
}



void encrypt(char str[100],int k){

    if(k<0||k>25){
        printf("Key should be within 0 to 25\n");
        return;
    }
    // iterate through each character in the string
    for (int i = 0; i < strlen(str); i++) {
        // check if the character is an uppercase letter
        if (str[i] >= 'A' && str[i] <= 'Z') {
            // apply the Caesar cipher encryption for uppercase letters
            str[i] = (str[i] - 'A' + k) % 26 + 'A';
        }
        // check if the character is a lowercase letter
        else if (str[i] >= 'a' && str[i] <= 'z') {
            // apply the Caesar cipher encryption for lowercase letters
            str[i] = (str[i] - 'a' + k) % 26 + 'a';
        }
       
    }
    // print the encrypted string
    printf("Encrypted String: %s\n", str);
    decrypt(str,k);
}

int main(){
    char string[100];
    int key;
    printf("Enter a string : ");
    scanf(" %s",string);
    printf("Enter the key : ");
    scanf(" %d",&key);

    encrypt(string,key);
    
}
