#include<stdio.h>
int main(){
     int a = 10, b = 5, times = 4;
     int a_factorial = 1, b_factorial = 1,a_times = 1, b_times = 1;
     for (int i = 1; i <= a; i++)
     {
         a_factorial *= i;
     }
     for (int i = 1; i <= b; i++)
     {
         b_factorial *= i;
     }
     for (int i = times; i > 0; i--)
     {
         a_times *= a;
     }
     for (int i = times; i > 0; i--)
     {
         b_times *= b;
     }
     return a_factorial + b_factorial 
     + a_times + b_times;
 }
 //decomposition ↓↓↓↓↓↓↓↓↓↓
//  int factorial(int a){
//      int a_factorial = 1;
//      for (int i = 1; i <= a; i++)
//      {
//          a_factorial *= i;
//      }
//      return a_factorial;
//  }
//  int times(int a ,int t){
//      int a_times = 1;
//     for (int i = t; i > 0; i--)
//      {
//          a_times *= a;
//      }
//      return a_times;
//  }
//  int main(){
//       int a = 10, b = 5, time = 4;
//       return factorial(a) + factorial(b) + times(a, time) + times(a, time);
//  }