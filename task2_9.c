#include <stdio.h>
#define N 96

int func2(int j, int k, int i);
int func1(void);

int main()
{
 func1();
 return 0;
}

int func1(void)
{
    int count = 0;
    // Triply nested for loop, that goes through all possibilities from a to z.
    for(int i ='a'; i<='z'; i++){
    int g = i - N;
      for(int k='a'; k<='u'; k++){
      int f = k - N;
        for(int j='a'; j<='z'; j++){
        int h = j - N;
        // Function func2 checks whether the letter is consonant or vowel. If the pattern is 
        // c-v-c func2 returns 1, v-c-c func2 returns 2, else it is invalid.
        func2(j, k, i);
          if (func2(j, k, i)==1)   
          {
            int sum = g+f+h;
            // If statement checks if the sum gives a prime number. 
            if ((sum%2!=0 && sum%3!=0 && sum%5!=0) || sum == 5)
            { 
              count++;
              printf(" %2i ", count);
              printf("  %c%c%c\n", i, k, j);
            }
          }
            else if (func2(j, k, i)==2)
            {
              int sum1 = g+f+h;
              if ((sum1%2!=0 && sum1%3!=0 && sum1%5!=0) || sum1 == 5)
              {
                count++;
                printf(" %2i ", count);
                printf("  %c%c%c\n", i, k, j);
             }
            }
           }
          }
         }
 return 0;
}

int func2(int j, int k, int i)
{
  if(i==j && (k=='a' || k=='e' || k=='i' || k=='o' || k=='u') &&
    (i !='a' && i !='e' && i !='i' && i !='o' && i !='u') &&
    (j !='a' && j !='e' && j !='i' && j !='o' && j !='u'))
   {
     return 1;
   }
     else if((i==j && (i=='a' || i=='e' || i=='i' || i=='o' || i=='u') &&
         (j=='a' || j=='e' || j=='i' || j=='o' || j=='u') &&
         (k !='a' && k !='e' && k !='i' && k !='o' && k !='u'))) 
     {
       return 2;
     }
  return 0;
}
