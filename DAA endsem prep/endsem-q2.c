/*
Closed Hashing with linear probing
5bad 6dab 7dac 8cad
hash function - sum of ascii value divided by user (here 10)
while searching cad and the number of probes 

size 15
battle rattle tattle 
search cat adn return search result and number of probes
if not found return -1 and print not found
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
    int n;
    printf("Enter the length of the hash (hash function) : ");
    scanf("%d",&n);
    char** hash = (char**) calloc(n,sizeof(char*));
    for(int i = 0 ; i < n ; i++){
        hash[i] = (char*) calloc(30,sizeof(char));
        hash[i] = "NULL";
    }
    int i = 0;
    while(i<=n-1){
        char *string = (char*)calloc(30,sizeof(char));
        printf("\nEnter String to save (enter 1 to break): ");
        scanf("%s",string);
        if(strcmp(string,"1") == 0){
            break;
        }else{
            int ascii = 0;
            for(int i = 0 ; i < strlen(string);i++){
                ascii += string[i];
            }
            int index = ascii%n;
            int j = 0;
            while(1){
                if((index + j)%n == index && j!=0) {
                    printf("Hash Full");
                    break;
                }
                if(strcmp(hash[(index + j)%n],"NULL") != 0){
                    j++;
                    continue;
                }else if(strcmp(hash[(index + j)%n],"NULL") == 0){
                    printf("%d",j);
                    hash[(index+j)%n] = string;
                    for(int i = 0 ; i < n ; i++){
                        printf("%d. %s\t",i,hash[i]);
                    }
                    break;
                }
                break;
            }
        }
    }
    for(int i = 0 ; i < n ; i++){
        printf("%d. %s\t",i,hash[i]);
    }
    while(1){
        char* string = (char*)calloc(30,sizeof(char));
        printf("\nEnter function to find (1 to exit):");
        scanf("%s",string);
        if(strcmp(string,"1")==0) break;
        else{
            int ascii = 0;
            for(int i = 0 ; i < strlen(string);i++){
                ascii += string[i];
            }
            int index = ascii%n;
            int j = 0;
            while(1){
                if((index + j)%n == index && j!=0) {
                    printf("Not found");
                    break;
                }
                if(strcmp(hash[(index+j)%n],string) == 0){
                    printf("\nString found at %d with %dth probes\n",index+j,j+1);
                    break;
                }else if(strcmp(hash[(index+j)%n],string) != 0){
                    j++;
                }
            }
        }
    }
    
}