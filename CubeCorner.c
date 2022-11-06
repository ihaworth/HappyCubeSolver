/******************************************************************************
*******************************************************************************
 
  This is the file "CubeCorner.c" and it contains routines that process 
 information to do with the corners of the solution.

*******************************************************************************
******************************************************************************/

#include "CubeHeader.h"

/******************************************************************************
  This function writes the information about the corners of the piece being
 placed into the solution into the arrays holding the information about the
 corners of the solution. 
******************************************************************************/

void update_corner(int *corners,int *next_to_corners,int *sol_corners)
{
 int corner,
     sol_corner;
 for(corner=0;corner<=3;corner++)
   {
    sol_corner=sol_corners[corner];
    no_lugs_at_cor[sol_corner]=no_lugs_at_cor[sol_corner]+corners[corner];
    no_lugs_adjacent_to_cor[sol_corner]+=next_to_corners[corner];
   }
}

/******************************************************************************
  This function removes the information about the corners of a piece, that is
 being removed from the solution on backtracking, from the arrays holding the
 information about the corners of the solution.
******************************************************************************/

void return_corner(int *corners,int *next_to_corners,int *sol_corners)
{
 int corner,
     sol_corner;
 for(corner=0;corner<=3;corner++)
   {
    sol_corner=sol_corners[corner];
    no_lugs_at_cor[sol_corner]=no_lugs_at_cor[sol_corner]-corners[corner];
    no_lugs_adjacent_to_cor[sol_corner]-=next_to_corners[corner];
   }
}

/*****************************************************************************/
