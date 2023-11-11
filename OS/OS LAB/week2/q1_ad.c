#include<unistd.h>
#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<stdlib.h>
void Sort(char** fnames,int k)
{
    char str1[100];
    char str2[100];
    int n=100;
    char s[100];
    for(int i=0;i<n;i++)
    {
        strcpy(str1,fnames[i]);
      for(int j=i+1;j<n;j++)
      {
        strcpy(str2,fnames[j]);
        if(strcmp(str1,str2)>0)
        {
            strcpy(s,str1);
            strcpy(str1,str2);
            strcpy(str2,s);
        }
      }
   }
}

void printFiles(char* dir)
{
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    dp=opendir(dir);
    char** fnames;
    int k=0;
    fnames=calloc(100,sizeof(char*));
    for(int i=0;i<100;i++)
    {
        fnames[i]=calloc(100,sizeof(char));
    }
    if(!dp)
    {
        printf("Cannot open directory : %s\n",dir);
        exit(0);
    }
    chdir(dir);
    while(entry=readdir(dp))
    {
        lstat(entry->d_name,&statbuf);
        if(S_ISDIR(statbuf.st_mode))
        {
            if(strcmp(entry->d_name,".")==0 || strcmp(entry->d_name,"..")==0)
            {
                continue;
            }
            strcpy(fnames[k++],entry->d_name);
        }
    }
    Sort(fnames,k);
    chdir("..");
    for(int i=0;i<5;i++)
    {
            printf("%s\t",fnames[i]);
    }
}

void main()
{
    char dir[256];
    printf("Enter Directory Name : \t");
    scanf("%s",dir);
    printFiles(dir);
}