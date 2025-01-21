#include <assert.h>

#define Y 20 
#define X 20

// Returns the (minimum) number of moves required to find the exit
// The entrance is (sx, sy) and the exit is (ex, ey)
// The maze is represented by 1s (spaces) and 2s (walls)
int inkblot(int a[Y][X], int sx, int sy, int ex, int ey);

int main(void)
{

   int a[Y][X] = {{2,1,2,2,2,2},
                  {2,1,2,1,1,1},
                  {2,1,1,1,2,2},
                  {2,2,2,2,2,2}};
   assert(inkblot(a, 5, 1, 1, 0)==8);

   int b[Y][X] = {{2,2,2,2,2,2,2},
                  {1,1,2,1,1,1,2},
                  {2,1,2,1,2,1,2},
                  {2,1,1,1,2,1,2},
                  {2,2,1,2,2,1,2},
                  {2,1,1,2,1,1,1},
                  {2,2,2,2,2,2,2}};
   assert(inkblot(b, 0, 1, 6, 5)==15);

   int c[Y][X] = {{2,2,2,2,2,2,2,2,2},
                  {2,1,1,1,1,1,1,1,1},
                  {2,1,2,2,2,2,2,2,2},
                  {2,1,1,1,2,1,1,1,2},
                  {2,2,2,1,2,1,2,1,2},
                  {2,1,1,1,2,1,2,1,2},
                  {2,1,2,2,2,1,2,1,2},
                  {2,1,1,1,1,1,2,1,1},
                  {2,2,2,2,2,2,2,2,2}};
   assert(inkblot(c, 8, 1, 8, 7)==33);

   return 0;
}
