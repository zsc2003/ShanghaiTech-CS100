#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define MAX_SIZE 103

char valueToChar[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

void read(int *num, int *len);
void reverse(int *num, int len);
void addition(int *num1, int len1, int *num2, int len2);
void subtraction(int *num1, int len1, int *num2, int len2);
// void mutiplication(int *num1, int len1, int *num2, int len2);

int main() {
    //get operator begin
    char operator;
    operator = getchar();
    getchar();  //ignore the '\n'
    //get operator end
    //get num1 begin
    int num1[MAX_SIZE] = {0};
    int len1;
    read(num1, &len1);
    reverse(num1, len1);
    //get num1 end
    //get num2 begin
    int num2[MAX_SIZE] = {0};
    int len2;
    read(num2, &len2);
    reverse(num2, len2);
    //get num2 end
    switch (operator) {
        case '+' : addition(num1, len1, num2, len2);
                   break;
        case '-' : subtraction(num1, len1, num2, len2);
                   break;
    }
    return 0;
}

void read(int *num, int *len) {
    int l = 0;
    int digit = 0;
    while(true) {
        digit = getchar();
        if(digit == '\n') break;
        if(digit >= '0' && digit <= '9') digit -= '0';
        else if (digit >= 'a' && digit <= 'f') digit -= 'a' - 10;
        num[l++] = digit;
    }
    *len = l;
}

void reverse(int *num, int len) {
    int l = 0;
    int r = len - 1;
    while(l < r) {
        int tmp = num[l];
        num[l++] = num[r];
        num[r--] = tmp;
    }
}

void addition(int *num1, int len1, int *num2, int len2) {
    bool num1Longer;
    int lenShorter;
    if(len1 > len2) num1Longer = true, lenShorter = len2;
    else num1Longer = false, lenShorter = len1;
    int carry = 0;
    int answerLen = 0;
    int answer[MAX_SIZE] = {0};
    for(int i = 0 ; i < lenShorter ; ++i) {
        int tmp = carry + num1[i] + num2[i];
        answer[i] = tmp % 16;
        carry = tmp / 16;
    }
    if(num1Longer) {
        for(int i = len2 ; i < len1 ; ++i) {
            int tmp = num1[i] + carry;
            answer[i] = tmp % 16;
            carry = tmp / 16;
        }
        answerLen = len1;
        if(carry) answer[len1] = carry, answerLen++;
    } else {
        for(int i = len1 ; i < len2 ; ++i) {
            int tmp = num2[i] + carry;
            answer[i] = tmp % 16;
            carry = tmp / 16;
        }
        answerLen = len2;
        if(carry) answer[len2] = carry, answerLen++;
    }
    int maxLen = answerLen + 1;
    reverse(num1, len1);
    reverse(num2, len2);
    reverse(answer, answerLen);
    //print the first line
    for(int i = len1 ; i < maxLen ; ++i, printf(" "));
    for(int i = 0 ; i < len1 ; printf("%c", valueToChar[num1[i++]]));
    printf("\n");
    //print the first line end
    //print the second line start
    printf("+");
    for(int i = len2 + 1 ; i < maxLen ; ++i, printf(" "));
    for(int i = 0 ; i < len2 ; printf("%c", valueToChar[num2[i++]]));
    printf("\n");
    //print the second line end
    //print ----- start
    for(int i = 0 ; i < maxLen ; ++i, printf("-"));
    printf("\n");
    //print ----- end
    //print the answer line
    for(int i = answerLen ; i < maxLen ; ++i, printf(" "));
    for(int i = 0 ; i < answerLen ; printf("%c", valueToChar[answer[i++]]));
    printf("\n");
    //print the answer line end
}

void subtraction(int *num1, int len1, int *num2, int len2) {
    int answer[MAX_SIZE] = {0};
    int carry = 0;
    int answerLen = 1;
    for(int i = 0 ; i < len2 ; ++i) {
        int tmp = num1[i] - num2[i] - carry;
        answer[i] = (tmp + 16) % 16;
        carry = tmp < 0;
        if(answer[i]) answerLen = i+1;
    }
    for(int i = len2 ; i < len1 ; ++i) {
        int tmp = num1[i] - carry;
        answer[i] = (tmp + 16) % 16;
        carry = tmp < 0;
        if(answer[i]) answerLen = i+1;
    }
    reverse(answer, answerLen);
    reverse(num1, len1);
    reverse(num2, len2);
    int maxLen = len1+1;

    for(int i = len1 ; i < maxLen ; ++i, printf(" "));
    for(int i = 0 ; i < len1 ; printf("%c", valueToChar[num1[i++]]));
    printf("\n");
    
    printf("-");
    for(int i = len2 + 1 ; i < maxLen ; ++i, printf(" "));
    for(int i = 0 ; i < len2 ; printf("%c", valueToChar[num2[i++]]));
    printf("\n");

    for(int i = 0 ; i < maxLen ; ++i, printf("-"));
    printf("\n");

    for(int i = answerLen ; i < maxLen ; ++i, printf(" "));
    for(int i = 0 ; i < answerLen ; printf("%c", valueToChar[answer[i++]]));
    printf("\n");
}