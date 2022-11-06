/******************************************************************************
*******************************************************************************
 
  This is the file "CubePrint.c" and it contains the routine that displays
 the solutions.

*******************************************************************************
******************************************************************************/

#include "CubeHeader.h"

/******************************************************************************
  This function takes an argument which is an indication of the symmetry of
 this solution in relation to other previously found solutions, and then
 prints the solution according to whether it is sufficiently unique to qualify
 for displaying.
******************************************************************************/

void print(enum sol_type sim)
{
 /* This is the number of the hole in the solution for which the piece
    is currently to be placed in (by the person constructing the solution. */
 hole counter;
 
 /* This is the side of the hole where a piece is to be placed. */
 hole_side side;

 /* This is a dummy variable which is used to reduce the number of
    calculations of an array index, it also makes the code clearer. */
 int arg=0;

 /* This flag is used to indicate whether a hole in the solution has any
    neighbours that have had pieces put in them. */
 boolean flag;

 /* This array indicates which holes in the solution have been filled so far
    in the process of constructing the solution. */
 boolean used[no_in_sol+1];

 /* This array holds the information of whether the neighbours of a hole 
    have pieces in them. */
 boolean edges[4];

 /* This is the number of the current solution. */
 static int number=0;

 /* If the solution is not identical to a previous solution then... */
 if(sim!=identical)
   {
    /* ...If the solution is either completely new OR the solution is the
       same as one that has already been found, except for some symmetrical
       pieces being in a different orientation, and moreover the user wants
       to see these symmetrical solutions, then continue and display it. */
    if((sim==new || (sim>=1 && symm_toggle==true)))
      {
       /* Record this solution so it's identical counterparts are not
          displayed too. */
       copy();

       /* Generate the number of this solution. */
       number=number+1;

       /* Print out the header for this solution. */
       printf("\n\nSolution number %d.\n-------------------\n",number);
       printf("Start position=%d, comparisons=%d, time=%.2f.\n",used_index,
              no_comparisons,((float)(clock()-start_time))/CLOCKS_PER_SEC);

       /* If this solution is the same as a previous solution then say so. */
       if(sim>=1)
         printf("This solution is symmetrical.\n");

       /* Walk across the solution, initialising the array which says which
          pieces have been put in the solution. This array helps the computer
          remember which pieces have already been put in and so when putting
          new pieces in it knows which are already there to relate to. */
       for(counter=0;counter<=no_to_use;counter=counter+1)
          used[counter]=false;
       
       /* Walk over the solution... */
       for(counter=0;counter<=no_to_use;counter++)
         {
          /* This flag will indicate whether this hole has any neighbours
             in the solution already filled. */
          flag=false;

          /* Look at all the sides of this hole in the solution. */
          for(side=0;side<=3;side++)
            {
             /* If the side has a piece next to it then... */
             if(used[link_squ[counter][side]]==true)
               {
                /* Remember which side had a piece next to it. */
                edges[side]=true;

                /* Since there is at least one piece next to this hole then
                   it should not be treated as an individual. */
                flag=true;
               } 
             
             /* ...otherwise remember that there isn't a piece next to
                this hole. */
             else
                edges[side]=false;
            }

          /* If there is at least one neighbour with a piece in then...*/
          if(flag==true)
            {
             /* ...print the position of the piece in this hole in relation
                to the pieces already in. */
             printf("Piece %d fits such that:\n",squ_no[counter]->piece_no);
             for(side=0;side<=3;side++)
               {
                arg=link_squ[counter][side];
                if(edges[side]==true)
                  {
                   printf("     piece %d",squ_no[counter]->piece_no);
                   printf(" side %d",sider(side,squ_rot[counter],
                                                 squ_dir[counter]));
                   printf(" connects to piece %d",squ_no[arg]->piece_no);
                   printf(" side %d",sider(link_side[counter][side],
                                                 squ_rot[arg],squ_dir[arg]));
                   printf(" with direction %d\n",squ_dir[counter]*
                                                 squ_dir[link_squ[counter]
                                                                 [side]]*
                                                 link_dir[counter][side]);
                  }
               }
            }

          /* ...otherwise print the information about this piece
             in isolation. */
          else    
             printf("Take piece %d.\n",squ_no[counter]->piece_no);
          
          /* Before going on to print the information for the next piece in
             the solution, signal that this piece is now in and that future
             pieces may be placed in the solution in relation to this one. */
          used[counter]=true;
         }
      }
   }
}

/*****************************************************************************/
