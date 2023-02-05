#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#define UNK '.'
#define HASH '#'
#define MAX 20
#define MAX_CARS 26
#define QMAX 20000
#define HORIZONTAL 1
#define VERTICAL 2
struct carpark
{
  char b2d[MAX][MAX];
  int length;
  int width;
  int count;
  int sz;
};
typedef struct carpark carpark;
struct car
{
  int row;
  int col;
  int orientation;
  int letter;
  int size;
};
typedef struct car car;
void test (void);
void printboard (carpark * b);
bool Cshape (carpark * b);
void int_carpark (carpark * b, car * car1);
void children (carpark * park);
void move_car (carpark * b, car * car1);
bool is_board_solved (carpark * b);
bool str2board(carpark* b, char* str);

int main (int argc, char *argv[])
{
  if (argc >= 2)
    {
      carpark b[QMAX];
      car car1;
      FILE *ptr = fopen (argv[1], "r");
      if (ptr == NULL)
	{
	  printf ("no such file");
	  return 0;
	}
      fscanf (ptr, "%ix%i\n", &b[0].length, &b[0].width);
      for (int i = 0; i <= b[0].length; i++)
	{
	  for (int j = 0; j < b[0].width; j++)
	    {
	      fscanf (ptr, "%c", &b[0].b2d[i][j]);
	    }
	  char c;
	  fscanf (ptr, "%c", &c);
	}
      test();
      assert (Cshape (&b[0]) == true);
      assert (Cshape (&b[1]) == false);
      assert (is_board_solved(&b[0]) == false);
      int_carpark (&b[0], &car1);
      move_car (&b[0], &car1);
    }
  else
    {
      printf ("invalid argument\n");
      exit(EXIT_FAILURE);
    }
  return 0;
}
//Any exits?
bool Cshape (carpark * b)
{
  for (int i = 0; i < b[0].width; i++)
    {
      if (b[0].b2d[0][i] == UNK || b[0].b2d[b[0].length - 1][i] == UNK)
	{
	  return true;
	}
    }
  for (int i = 0; i < b[0].length; i++)
    {
      if (b[0].b2d[i][0] == UNK || b[0].b2d[i][b[0].width - 1] == UNK)
	{
	  return true;
	}
    }
  return false;
}
void printboard (carpark * b)
{
  printf ("\nGrid: \n");
  for (int i = 0; i <= b[0].length - 1; i++)
    {
      for (int j = 0; j < b[0].width; j++)
	{
	  printf ("%c", b[0].b2d[i][j]);
	} printf ("\n");
    }
}
//SPECIFICATION OF EACH CAR
void int_carpark (carpark * b, car * car1)
{
  char c;
  int id = 0;
  int nid = 0;
  int count = 1;
  for (int i = 0; i <= b[0].length - 1; i++)
    {
      count = 1;
      for (int j = 0; j < b[0].width; j++)
	{
	  c = b[0].b2d[i][j];
	  id = c - 'A';
	  if (id >= 0 && id <= 26)
	    {
	      //Number of the car
	      nid = id;
	      //Assign spec for the car
	      car1[id].letter = nid;
	      car1[id].row = i;
	      car1[id].col = j;
	      //horizontal
	      if (b[0].b2d[i][j - 1] == nid + 65)
		{
		  count++;
		  car1[id].size = count;
		  car1[id].orientation = HORIZONTAL;
		}
	      //vertical
	      if (b[0].b2d[i + 1][j] == nid + 65)
		{
		  count++;
		  car1[id].size = count;
		  car1[id].orientation = VERTICAL;
		}
	    }
	  b[0].count = nid + 1;
	}
    }
}

void move_car (carpark * b, car * car1)
{
  int f = 0;
  int child = 0;
  char temp;
  int i = 0;
  char c;
  int current = 1;
  int current1 = 1;
  int child1 = 0;
  int result=0;
  //While there is no solution
  while (result==0)
    {
      temp = car1[i].letter + 65;
      //horizontal
      if (car1[i].orientation == HORIZONTAL)
	{
	  //move right
	  if (b[child].b2d[car1[i].row][car1[i].col + current] == UNK)
	    {
	      int Ccol = 0;
	      f++;
	      b[f].length = b[0].length;
	      b[f].width = b[0].width;
	      for (int i = 0; i <= b[0].length - 1; i++)
		{
		  for (int j = 0; j < b[0].width; j++)
		    {
		      b[f].b2d[i][j] = b[child].b2d[i][j];
		      c = b[child].b2d[i][j];
		      int id = c - 'A';
		      if (id >= 0 && id <= 26)
			{
			  Ccol = j;
			}
		    }
		}
	      temp = car1[i].letter + 65;
	      b[f].b2d[car1[i].row][Ccol + 1] = temp;
	      b[f].b2d[car1[i].row][Ccol - car1[i].size + 1] = UNK;
	      printboard (&b[f]);
	      //exit?
	      if (Ccol + 1 == b[0].length - 1)
		{
		  for (int i = 0; i <= b[child].length - 1; i++)
		    {
		      for (int j = 0; j < b[child].width; j++)
			{
			  if (b[f].b2d[i][j] == temp)
			    {
			      b[f].b2d[i][j] = UNK;
			    }
			}
		    }
		  printboard (&b[f]);
		}
	    }
	  //move left
	  if (b[child].b2d[car1[i].row][car1[i].col - car1[i].size - child] ==
	      UNK)
	    {
	      int Ccol = 0;
	      f++;
	      b[f].length = b[0].length;
	      b[f].width = b[0].width;
	      for (int i = 0; i <= b[0].length - 1; i++)
		{
		  for (int j = 0; j < b[0].width; j++)
		    {
		      b[f].b2d[i][j] = b[child].b2d[i][j];
		      c = b[child].b2d[i][j];
		      int id = c - 'A';
		      if (id >= 0 && id <= 26)
			{
			  Ccol = j;
			}
		    }
		}
	      temp = car1[i].letter + 65;
	      //car1[i].col = Ccol;
	      b[f].b2d[car1[i].row][Ccol - car1[i].size] = temp;
	      b[f].b2d[car1[i].row][Ccol] = UNK;
	      //printboard (&b[f]);
	      if (Ccol - car1[i].size == b[0].length - b[0].length)
		{
		  for (int i = 0; i <= b[child].length - 1; i++)
		    {
		      for (int j = 0; j < b[child].width; j++)
			{
			  if (b[f].b2d[i][j] == temp)
			    {
			      b[f].b2d[i][j] = UNK;
			    }
			}
		    }
		  printboard (&b[f]);
		}
	    }
	  current++;
	  child++;
	}
      //vertical
      if (car1[i].orientation == VERTICAL)
	{
	  //move down
	  if (b[child1].b2d[car1[i].row + current1][car1[i].col] == UNK)
	    {
	      int Ccol = 0;
	      f++;
	      b[f].length = b[0].length;
	      b[f].width = b[0].width;
	      for (int k = 0; k <= b[0].length - 1; k++)
		{
		  for (int j = 0; j < b[0].width; j++)
		    {
		      b[f].b2d[k][j] = b[child1].b2d[k][j];
		      c = b[child1].b2d[k][j];
		      int id = c - 'A';
		      if (id >= 0 && id <= 26)
			{
			  Ccol = k;
			}
		    }
		}
	      temp = car1[i].letter + 65;
	      b[f].b2d[Ccol + 1][car1[i].col] = temp;
	      b[f].b2d[Ccol - car1[i].size + 1][car1[i].col] = UNK;
	      //printboard (&b[f]);      
	      if (Ccol + 1 == b[0].width - 1)
		{
		  for (int i = 0; i <= b[child].length - 1; i++)
		    {
		      for (int j = 0; j < b[child].width; j++)
			{
			  if (b[f].b2d[i][j] == temp)
			    {
			      b[f].b2d[i][j] = UNK;
			    }
			}
		    }
		  printboard (&b[f]);
		}
	    }
	  //move up
	  if (b[child1].b2d[car1[i].row - car1[i].size - child1][car1[i].col]
	      == UNK)
	    {
	      int Ccol = 0;
	      f++;
	      b[f].length = b[0].length;
	      b[f].width = b[0].width;
	      for (int k = 0; k <= b[0].length - 1; k++)
		{
		  for (int j = 0; j < b[0].width; j++)
		    {
		      b[f].b2d[k][j] = b[child1].b2d[k][j];
		      c = b[child1].b2d[k][j];
		      int id = c - 'A';
		      if (id >= 0 && id <= 26)
			{
			  Ccol = k;
			}
		    }
		}
	      temp = car1[i].letter + 65;
	      b[f].b2d[Ccol - car1[i].size][car1[i].col] = temp;
	      b[f].b2d[Ccol][car1[i].col] = UNK;
	      //printboard (&b[f]);   
	      if (Ccol - car1[i].size == b[0].width - b[0].width)
		{
		  for (int i = 0; i <= b[child].length - 1; i++)
		    {
		      for (int j = 0; j < b[child].width; j++)
			{
			  if (b[f].b2d[i][j] == temp)
			    {
			      b[f].b2d[i][j] = UNK;
			    }
			}
		    }
		  printboard (&b[f]);
		}
	    }
	  current1++;
	  child1++;
	}
	result = is_board_solved(&b[f]);
        if(result == 1)
        {
        printf("%i moves", child+child1);
        exit(EXIT_SUCCESS);
        }
    }
}
bool is_board_solved (carpark * b)
{
  char c;
  int k = 0;
  int countC = 0;
  {
    for (int i = 0; i <= b[k].length - 1; i++)
      {
	for (int j = 0; j < b[k].width; j++)
	  {
	    c = b[k].b2d[i][j];
	    int id = c - 'A';
	    if (id > -1)
	      {
		countC++;
	      }
	  }
      }
    if (countC == 0)
      {
	return true;
      }
  }
  return false;
}

bool str2board(carpark* b, char* str)
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

void test (void)
{ 
    carpark c;
    assert(str2board(&c, "################"));
    assert(Cshape(&c)==false);

    assert(str2board(&c, "#######....##....##....##....#######"));
    assert(is_board_solved(&c)==true);
    assert(Cshape(&c)==false);
}
