#include<stdbool.h>
#include<string.h>
int minOperations(char* s){
    int n=strlen(s);
    char mn=s[0];
    char mx=s[0];
    for(int i=1;i<n;i++){
        if(s[i]<mn){
            mn=s[i];
        }
        if(s[i]>mx){
            mx=s[i];
        }
    }
    bool sorted =true;
    for(int i=1;i<n;i++){
        if(s[i-1]>s[i]){
            sorted=false;
            break;
        }
    }
    if(sorted){
        return 0;
    }
    if(n==2){
        return -1;
    }
    if(s[0]==mn||s[n-1]==mx){
        return 1;
    }
    for(int i =1;i<n-1;i++){
        if(s[i]==mn||s[i]==mx){
            return 2;
        }
    }
    return 3;
}