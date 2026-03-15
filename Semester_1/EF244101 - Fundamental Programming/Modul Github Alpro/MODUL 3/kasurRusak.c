#include <stdio.h>
#include <string.h>
// daad, 0 1 2 3, len /2

void hilang(char arr[], int kata){
    if (kata % 2 == 0){
        for (int i = 0; i < kata; i++){
            if (arr[i] == arr[kata - i]){

            }
        }
    }
}

int main() {
    char kata[100];
    scanf("%s", &kata);
    int len = strlen(kata);
}