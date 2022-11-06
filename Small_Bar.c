/******************************************************************************
*******************************************************************************
 
 This is the file "Small_Bar.c" and it contains the definition of the shape of
the two colour bar.

*******************************************************************************
******************************************************************************/

#include "CubeHeader.h"

/*****************************************************************************/

void two_cube_beam(void)
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
 link_squ[2][2]=6;
 link_side[2][2]=0;
 link_dir[2][2]=-1;
 link_squ[2][3]=3;
 link_side[2][3]=1;
 link_dir[2][3]=-1;
 link_squ[3][2]=7;
 link_side[3][2]=0;
 link_dir[3][2]=-1;
 link_squ[3][3]=4;
 link_side[3][3]=1;
 link_dir[3][3]=-1;
 link_squ[4][2]=8;
 link_side[4][2]=0;
 link_dir[4][2]=-1;
 link_squ[5][1]=8;
 link_side[5][1]=3;
 link_dir[5][1]=-1;
 link_squ[5][2]=9;
 link_side[5][2]=0;
 link_dir[5][2]=-1;
 link_squ[5][3]=6;
 link_side[5][3]=1;
 link_dir[5][3]=-1;
 link_squ[6][2]=9;
 link_side[6][2]=3;
 link_dir[6][2]=-1;
 link_squ[6][3]=7;
 link_side[6][3]=1;
 link_dir[6][3]=-1;
 link_squ[7][2]=9;
 link_side[7][2]=2;
 link_dir[7][2]=-1;
 link_squ[7][3]=8;
 link_side[7][3]=1;
 link_dir[7][3]=-1;
 link_squ[8][2]=9;
 link_side[8][2]=1;
 link_dir[8][2]=-1;
 
 /* This is the number of pieces in the puzzle. */
 no_to_use=9;
}

/*****************************************************************************/
