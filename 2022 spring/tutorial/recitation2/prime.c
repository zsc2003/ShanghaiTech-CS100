#include <stdio.h>
int main(){
    int num = 0;
    scanf("%d", &num);
    for (int i = 2; i < num; i++){
        if (num % i == 0){
            printf("%d is not a prime.\n", num);
            return 0;
        }
    }
    printf("%d is a prime.\n", num);
    return 0;
}