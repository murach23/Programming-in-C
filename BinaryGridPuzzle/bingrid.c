#include "bingrid.h"

bool str2board(board* b, char* str)
{
  int count = 0;
  int size = 0;
  int count1 = 0;
  while (str[count] != '\0')
    {
      count++;
    }
  if ((count > 3) && (count % 2 == 0))
    {
      size = sqrt (count);
      b->sz = size;
      for (int k = 0; k < size; k++)
	{
	  for (int j = 0; j < size; j++)
	    {
	      b->b2d[k][j] = str[count1];
	      count1++;
	    }
	}
      return true;
    }
  return false;
}

void board2str(char* str, board* b)
{
 //printf("STRING->");
 int count1 = 0;
 for (int k = 0; k < b->sz; k++)
   {
      for (int j = 0; j < b->sz; j++)
	{ 
	  str[count1] = b->b2d[k][j];
          //printf("%c", str[count1]);
          count1++;
	}
   }
   str[count1] = '\0';
   //printf("<-\n");
}

bool solve_board(board* b)
{
  ///pairs///
  //horizontally//
  int cnt=0;
  while (cnt < 6){
  for (int k = 0; k < b->sz; k++)
    {
      int lp = 0, rp = 1;
      for (int j = 0; j < b->sz; j++)
	{ 
	  if (b->b2d[k][lp] == ZERO && b->b2d[k][rp] == ZERO)
	    {
              if (lp>0 && rp >1){
	      b->b2d[k][lp-1] = ONE;
	      b->b2d[k][rp+1] = ONE;}
	    }
	  if (b->b2d[k][lp] == ONE && b->b2d[k][rp] == ONE)
	    {
              if(lp>0 && rp >1){
	      b->b2d[k][lp-1] = ZERO;
	      b->b2d[k][rp+1] = ZERO;}

	    }
          
           
	    lp = lp + 1;
	    rp = rp + 1;
	}
    }
  //vertically//
  for (int k = 0; k < b->sz; k++)
    {
      int lp = 0, rp = 1;
      for (int j = 0; j < b->sz; j++)
	{
	  if (b->b2d[lp][k] == ZERO && b->b2d[rp][k] == ZERO)
	    {
              if (lp>0 && rp >1){
	      b->b2d[lp - 1][k] = ONE;
	      b->b2d[rp + 1][k] = ONE;
              }
              if (lp==0 && rp ==1)
              {
               b->b2d[rp + 1][k] = ONE;
              }
	    }
             
	  else if ((b->b2d[j][k] == ONE) && (b->b2d[j+1][k] == ONE))
	    {
              if (lp>0 && rp >1){
	      b->b2d[lp - 1][k] = ZERO;
	      b->b2d[rp + 1][k] = ZERO;
              }
              if (lp==0 && rp ==1)
              {
               b->b2d[rp + 1][k] = ZERO;
              }
	    }
	    lp = lp + 1;
	    rp = rp + 1;
	}
    }
    
    ///OXO/// If two the same and there is a gap, opposite num.
    //horizontally
    for (int k = 0; k < b->sz; k++)
    {
      int lp = 0, mp = 1, rp = 2;
      for (int j = 0; j < b->sz; j++)
	{ 
	  if (b->b2d[k][lp] == ZERO && b->b2d[k][rp] == ZERO)
	    {
	      b->b2d[k][mp] = ONE;	      
	    }
	  if (b->b2d[k][lp] == ONE && b->b2d[k][rp] == ONE)
	    {
	      b->b2d[k][mp] = ZERO;
	    }
	    lp = lp + 1;
	    rp = rp + 1;
	    mp = mp + 1;
	}
    }
    //vertically
    for (int k = 0; k < b->sz; k++)
    {
      int lp = 0, mp = 1, rp = 2;
      for (int j = 0; j < b->sz; j++)
	{
	  if (b->b2d[lp][k] == ZERO && b->b2d[rp][k] == ZERO)
	    {
	      b->b2d[mp][k] = ONE;      
	    }
	  if (b->b2d[lp][k] == ONE && b->b2d[rp][k] == ONE)
	    {
	      b->b2d[mp][k] = ZERO;
	    }
	    lp = lp + 1;
	    rp = rp + 1;
	    mp = mp + 1;
	}
    }
    ///Counting///
    //horizontally
    
    for (int k = 0; k < b->sz; k++)
    {
      int mp = 0;
      int count0=0, count1=0, countd=0, countk=0;
      for (int j = 0; j < b->sz; j++)
	{
	  if (b->b2d[k][mp] == ZERO)
	    {
	      count0++;      
	    }
	  if (b->b2d[k][mp] == ONE)
	    {
	      count1++;
	    }
	  if (b->b2d[k][mp] == UNK)
	    {
	      countd = mp;
	      countk++;
	    }
	    if(count0 == (b->sz/2)) 
	      {
                for (int p = 0; p < b->sz; p++){
                if (b->b2d[k][p] == UNK){
	        b->b2d[k][p] = ONE;
                }
                }
	      }

	    if(count1 == (b->sz/2))
	      {
	        for (int p = 0; p < b->sz; p++){
                if (b->b2d[k][p] == UNK){
	        b->b2d[k][p] = ZERO;
                }
                }
	      }  
	      mp = mp + 1;
	}
       
    }

    
    ///vertically
    for (int k = 0; k < b->sz; k++)
    {
      int mp = 0;
      int count0=0, count1=0, countd=0, countk=0;
      for (int j = 0; j < b->sz; j++)
	{
	  if (b->b2d[mp][k] == ZERO)
	    {
	      count0++;      
	    }
	  if (b->b2d[mp][k] == ONE)
	    {
	      count1++;
	    }
	  if (b->b2d[mp][k] == UNK)
	    {
	      countd = mp;
	      countk++;
	    }
	    
	    if(count0 == (b->sz/2)) 
	      {
                for (int p = 0; p < b->sz; p++){
                if (b->b2d[p][k] == UNK){
	        b->b2d[p][k] = ONE;
                }
                }
	      }

	    if(count1 == (b->sz/2))
	      {
	        for (int p = 0; p < b->sz; p++){
                if (b->b2d[p][k] == UNK){
	        b->b2d[p][k] = ZERO;
                }
                }
	      }   
	      mp = mp + 1;
	}
    }
 //printf ("\nGrid: \n");
for (int k = 0; k < b->sz; k++)
    {
      
      for (int j = 0; j < b->sz; j++)
	{
          //printf ("%c", b->b2d[k][j]);
        }//printf ("\n");
    }
    cnt++;
    }
   
  for (int k = 0; k < b->sz; k++)
    {     
      for (int j = 0; j < b->sz; j++)
	{
	  if (b->b2d[k][j] == UNK)
	  {
	  return false;
	  }
	}
    }
  return true;
}

void printboard(board* b)
{
  printf ("\nGrid: \n");
  for (int k = 0; k < b->sz; k++)
    {
      
      for (int j = 0; j < b->sz; j++)
	{
	  printf ("%c", b->b2d[k][j]);
	}
      printf ("\n");
    }
}

void test(void)
{
  /*char str[(MAX*MAX+1)];
  board b;
  assert(str2board(&b, "1...1.1.0.....00...1................"));
  printboard(&b);
  assert(solve_board(&b)==true);
  printboard(&b);
  board2str(str, &b);
  assert(strcmp(str, "101010100101010011011010101100010101")==0);*/ 
}
