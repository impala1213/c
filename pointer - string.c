#include <stdio.h>
#include <stdlib.h>

void strcpy(char s[], char t[]) {
    int i = 0;
    while ((t[i] = s[i]) != '\0') {
        i++;
    }
    printf("%s", t);
}

int main(void){
    char a[100];
    strcpy("hello",a);
}
