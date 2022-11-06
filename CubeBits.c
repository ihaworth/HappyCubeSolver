/******************************************************************************
*******************************************************************************
 
 This is the file "CubeBits.c" and it contains miscellaneous routines.

*******************************************************************************
******************************************************************************/

#include "CubeHeader.h"

/******************************************************************************
  This function returns the bit pattern representing the edge of a piece, in
 a given orientation where the variable 'counter' indicates which side of the
 hole to look at.
******************************************************************************/

int edge_pattern(piece square,rotation rot,direction dir,hole_side counter)
{
 return((sides[square][(1-dir)>>1]>>
             ((
               ((dir+1)>>1)*
               3-dir*
               sider(counter,rot,dir))
              <<2))
        &31);
}

/******************************************************************************
  This function copies the current solution into the 'previous' arrays so that
 it can be used to compare with future solutions. This allows checking for
 symmetrical solutions and so filters the outputted data reducing it to a
 manageable quantity. This is useful since the computer will find at least 48
 symmetrical versions of a solution (given enough time).
******************************************************************************/

void copy(void)
{
 int counter;
 no_done++;
 for(counter=0;counter<=no_to_use;counter=counter+1)
   {
    previous_squ_no[no_done][counter]=squ_no[counter]->piece_no;
    previous_squ_rot[no_done][counter]=squ_rot[counter];
    previous_squ_dir[no_done][counter]=squ_dir[counter];
   }
}

/******************************************************************************
  This function waits for a key press and returns 'true' if 'Y' or 'y' are
 pressed and 'false' if 'N' or 'n' are pressed.
******************************************************************************/

int ask(void)
{
 int answer;
 char letter=' ';
 while(letter!='y' & letter!='Y' & letter!='n' & letter!='N')
   scanf("%c",&letter);
 if(letter=='y' || letter=='Y')
   answer=true;
 else
   answer=false;
 return answer;
}

/******************************************************************************
  This function is used to set up the free piece list in the order dictated by
 the starting position entered by the user. This starting position refers to
 the leaf of the tree of possible orders to start from. This ordering is of
 the groups of pieces of the same colour, not of individual pieces as this
 far too many combinations to start from (36!=3.72E41).
******************************************************************************/

void recurse(int recurse_depth,int no_of_colours_to_use,
             int *colours_to_be_used,int *beginnings,unsigned int time)
{            
 /* This variable is used to count over the number of colours to use. */
 piece count;

 /* These variables are used to hold the old versions of the free piece list
    so that on backtracking it can be restored. */
 struct free_piece_list_elt *old_start_next,
                            *old_front_previous,
                            *old_block_next,
                            *old_block_previous;

 /* This is a general variable used for simple tasks of short extent. */
 int temp;

/* Fill up the free piece list with a FIFO algorithm, e.g. for the first
   combination, the list will be filled up in the order B at the bottom, then
   O,R,G,Y, and finally P, which is the first colour to be used in this
   instance. This is done to give the greatest variation in starting position
   for the first few starting positions numbers, i.e. with 1, purple is used
   first, 2 uses yellow, e.t.c.  */

 /* For all the colours. */
 for(count=no_of_colours_to_use;count>=0;count--)
   {
    /* Take the first free colour. */
    if(used[colours_to_be_used[count]]==false)
      {
       /* This colour has now been used. */
       used[colours_to_be_used[count]]=true;

       /* Join the new colour's pieces to the front of the free piece list:*/

       /* Firstly, point the end of the new block to the start of
          the current list. */
       old_block_next=free_list[6*colours_to_be_used[count]+5].next;
       free_list[6*colours_to_be_used[count]+5].next=free_list_start->next;
       
       /* Secondly, make the 'previous' pointer from the new block point
          back to the free list start. */
       old_block_previous=free_list[6*colours_to_be_used[count]].previous;
       free_list[6*colours_to_be_used[count]].previous=free_list_start;

       /* Thirdly, make the front of the current list point back to the end of
          the new block. */
       old_front_previous=(free_list_start->next)->previous;
       (free_list_start->next)->previous=
                                    free_list+(6*colours_to_be_used[count]+5);

       /* Finally, make the start terminal point to to the first element
          of the new block. */
       old_start_next=free_list_start->next;
       free_list_start->next=free_list+(6*colours_to_be_used[count]);

       /* If all the colours have been placed. */
       if(recurse_depth==0)
         {
          /* Indicate which leaf has been reached. */
          used_index++;

          /* If this leaf is to be used to search from then... */
          if(beginnings[used_index]==true)
            {
             /* ...Set up the 'start piece to search from' for each hole
                in the solution to the first piece on this ordering of the
                free piece list. */
             for(temp=0;temp<=no_in_sol;temp++)
                piece_to_start_from[temp]=free_list_start->next;
             
             /* Reset the variables holding information about the search
                from the previous search. */
             get_out=false;
             depth=0;
             no_comparisons=0;
             
             /* Reset the measurement of time. */
             start_time=clock();

             /* Calculate the time to stop at. */
             stop_time=start_time+time;
             test(0);
             printf("Start n.o.=%d, depth=%d, comparisons=%d, time=%.2f.\n\n",
                         used_index,depth,no_comparisons,
                         ((float)(clock()-start_time))/CLOCKS_PER_SEC);
            }
         } 

       /* If not reached the position to start from then... */
       else
         {
          /* ...recurse until find a point to start from. */
          recurse(recurse_depth-1,no_of_colours_to_use,colours_to_be_used,beginnings,time);
         }

       /* When backtracking, must undo the last change to the free
          piece list. */
       used[colours_to_be_used[colours_to_be_used[count]]]=false;
       free_list_start->next=old_start_next;
       (free_list_start->next)->previous=old_front_previous;
       free_list[6*colours_to_be_used[count]].previous=old_block_previous;
       free_list[6*colours_to_be_used[count]+5].next=old_block_next;
      }
   }
}

/******************************************************************************
  This function prints out the free list, it is not used in the program but it
 was used to debug the program.
******************************************************************************/

void print_free_list(struct free_piece_list_elt *current)
{
 static int count=0;
 if(current==free_list_start)
   printf("Printing free list for the %dth time.\n",count++);
 if(current!=NULL)
   {
    printf("current->piece_no=%d\n",current->piece_no);
    printf("current->status=%d\n",current->status);
    printf("current->previous=%ld\n",(long)current->previous);
    printf("(current->previous)->piece_no=%d\n",(current->previous)->piece_no);
    printf("current->next=%ld\n",(long)current->next);
    printf("(current->next)->piece_no=%d\n\n",(current->next)->piece_no);
    print_free_list(current->next);
   }
}

/*****************************************************************************/
