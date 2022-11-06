/******************************************************************************
*******************************************************************************
 
 This is the file "Small_Cube.c" and it contains the definition of the shape of
the small cube.

*******************************************************************************
******************************************************************************/

#include "CubeHeader.h"

/*****************************************************************************/

void small_cube(void)
{
 /* This is the shape of the puzzle. */ 
 link_squ[0][0]=1;
 link_side[0][0]=0;
 link_dir[0][0]=-1;
 link_squ[0][1]=2;
 link_side[0][1]=0;
 link_dir[0][1]=-1;
 link_squ[0][2]=3;
 link_side[0][2]=0;
 link_dir[0][2]=-1;
 link_squ[0][3]=4;
 link_side[0][3]=0;
 link_dir[0][3]=-1;
 link_squ[1][1]=4;
 link_side[1][1]=3;
 link_dir[1][1]=-1;
 link_squ[1][2]=5;
 link_side[1][2]=0;
 link_dir[1][2]=-1;
 link_squ[1][3]=2;
 link_side[1][3]=1;
 link_dir[1][3]=-1;
 link_squ[2][2]=5;
 link_side[2][2]=3;
 link_dir[2][2]=-1;
 link_squ[2][3]=3;
 link_side[2][3]=1;
 link_dir[2][3]=-1;
 link_squ[3][2]=5;
 link_side[3][2]=2;
 link_dir[3][2]=-1;
 link_squ[3][3]=4;
 link_side[3][3]=1;
 link_dir[3][3]=-1;
 link_squ[4][2]=5;
 link_side[4][2]=1;
 link_dir[4][2]=-1;
 
 /* This is the number of pieces in the puzzle. */
 no_to_use=5;
}

/*****************************************************************************/
