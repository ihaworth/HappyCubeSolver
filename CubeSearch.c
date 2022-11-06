/******************************************************************************
*******************************************************************************
 
 This is the file "CubeSearch.c" and it contains the main searching routines.

*******************************************************************************
******************************************************************************/

#include "CubeHeader.h"

/******************************************************************************
  This is the main function that does the searching. It is recursively called
 to place pieces in successive 'holes' in the solution.
******************************************************************************/

void test(hole pos)
{                   
 /* These are the arrays which will hold the information about about the
    corners of the current piece being tried in the current hole. */
 int corners[4]={0,0,0,0},
     next_to_corners[4]={0,0,0,0},
     sol_corners[4];
 
 /* These are the pointers to the structures on the list of free pieces that
    represent the current piece, being tested in the current hole, and the
    pieces adjacent to this hole. */
 struct free_piece_list_elt *current_piece;
 struct free_piece_list_elt *contents_of_adjacent_holes[4];
 
 /* These variables are the number of the current piece being tested, and the
    rotation and direction at which it is trying to be fitted into the hole. */
 piece square;
 rotation rot;
 direction dir;

 /* This is a counter used to count round the edges of the current hole. */
 hole_side side;

 /* If the call to this function is to find a piece to fit into the solution
    at a greater depth than has been reached before, and such information has
    been requested by the user then dispay it. */
 if(pos>depth)
   {
    depth=pos;
    if(diagnostics_toggle==true)
      printf("Max depth reached=%d, at time %.2f, after %d comparisons.\n",
           depth,((float)(clock()-start_time))/CLOCKS_PER_SEC,no_comparisons);
   }                                             

 /* If an interrupt to the execution has occurred by a key being pressed or by
    the time running out on a timed run then exit. */
 if(get_out==true || (timed_run==true && clock()>stop_time))
   get_out=true;
 /* Otherwise just try to find a fit for the current hole. */
 else
   {
    
    /* Find the neighbours of the free hole trying to be filled. */
    for(side=0;side<=3;side++)
       contents_of_adjacent_holes[side]=squ_no[link_squ[pos][side]];
    
    /* Some previous calculations may have been performed on this position so
       take these into account by starting at the appropriate point in the
       free list for this hole. */
    current_piece=piece_to_start_from[pos];

    /* If this piece is being used, then given this piece isn't the last piece
       on the list, see if the next piece is free, i.e. find the first free
       piece on the list. */
    while(current_piece->status==piece_used && current_piece->next!=NULL)
      current_piece=current_piece->next;

    /* If the piece indicated by the previous calculations is free... */
    if(current_piece==piece_to_start_from[pos])
      {
       /* ...then start the search from the appropriate rotation and
             direction too. */
       dir=dir_to_start_from[pos];
       rot=rot_to_start_from[pos];
      }
    else
      {
       /* ...Otherwise start from the next free piece with the default
          rotational and directional settings. */
       dir=1;
       rot=0;
      }

    /* Search from this starting point through the list of pieces. */
    while(current_piece->next!=NULL)
      {
       /* Find the number linked with this structure on the free list. */
       square=current_piece->piece_no;

       /* Try each piece in both directions. */
       while(dir>=-1)
         {

          /* Try each piece in all rotations for both directions. */
          while(rot<=3)
            {

             /* If this is a symmetric orientation to one already used then
                skip it since it can reveal no new information. */
             if(symmetry[square][rot][(1-dir)>>1]==false || symm_toggle==true)
               {

                /* If the piece fits in the hole then... */
                if(fit(pos,square,rot,dir,contents_of_adjacent_holes,corners,
                           next_to_corners,sol_corners)==true)
                  {
                   /* Place the piece into the record of solution. */
                   squ_no[pos]=current_piece;
                   squ_rot[pos]=rot;
                   squ_dir[pos]=dir;
                   
                   /* Remove this piece from the list of free pieces. */
                   current_piece->status=piece_used;
                   (current_piece->previous)->next=current_piece->next;
                   (current_piece->next)->previous=current_piece->previous;

                   /* Write the information about the corners of the new piece
                      into the arrays holding the information about the
                      corners of the pieces in the solution. */
                   update_corner(corners,next_to_corners,sol_corners);

                   /* If this is the last piece to place in the solution... */
                   if(pos==no_to_use)
                     {
                      /* ... then print out the complete solution. */
                      print(similar());
                     }
                   else
                      /* Otherwise check to see if the as yet unfilled
                         neighbouring holes of the hole just filled can still
                         be filled with this new piece in place. */
                      check_empty_neighbouring_holes(pos, 0,
                                                 contents_of_adjacent_holes);

                   /* If reached here, then must be back-tracking so remove
                      the current piece form the solution,... */
                   squ_no[pos]=NULL;
                   squ_rot[pos]=false;
                   squ_dir[pos]=false;
                   
                   /* ...return the piece to the free piece list, and... */
                   current_piece->status=piece_free;
                   (current_piece->previous)->next=current_piece;
                   (current_piece->next)->previous=current_piece;

                   /* ...restore the information about the corners of the
                      solution to their previous values. */
                   return_corner(corners,next_to_corners,sol_corners);
                  }
               }

             /* Try to fit the same piece in the next rotation. */
             rot++;
            }

          /* Try to fit the piece in for all rotations in the opposite
             directions. */
          rot=0;
          dir-=2;
         }

       /* Try the next piece from the default starting positions. */
       dir=1;
       current_piece=current_piece->next;
      }
   }
}

/******************************************************************************
  This function checks the empty neighbouring holes to the hole where a piece
 has just been inserted to make sure that there is still at least one piece
 that fits in each hole. If there wasn't such a piece for every free hole then
 the puzzle would not be solvable from this position and so a backtrack is
 invoked to remove the offending piece. These flaws in the solution would
 eventually be found without this process by the basic searching mechanism,
 however this routine uses this idea to 'prune' the search space allowing
 much greater efficiency in searching for solutions.
  The function is called recursively four times, once for each of the
 immediate neighbours to the piece just fitted.
******************************************************************************/

void check_empty_neighbouring_holes(hole pos, hole_side neighbour,
                      struct free_piece_list_elt **contents_of_adjacent_holes)
{
 /* This is the hole number in the solution, of the neighbour of the piece
    just fitted that is being dealt with by this particular call to this
    function, i.e. the 'neighbour'th side off the hole 'pos'. */
 hole neighbours_hole_no;

 /* This is the number of the piece being tested the the neighbouring hole. */
 piece square;

 /* This is the pointer to the piece being tested. */ 
 struct free_piece_list_elt *current_piece;

 /* These are the pieces surrounding the neighbour being tested. */
 struct free_piece_list_elt *contents_of_neighbours_adjacent_holes[4];

 /* These 'old' variables are used to hold the values of the arrays that hold
    starting positions. When the first fit is found for a neighbour, the
    starting position arrays are updated to prevent re-searching for the piece
    and so wasting processing time. These variables are used to return these
    arrays to their original state by remembering their 'old' values before
    being written to. */
 struct free_piece_list_elt *old_piece_to_start_from;
 rotation old_rot_to_start_from;
 direction old_dir_to_start_from;

 /* These variables hold the information about the orientation of the current
    piece being tested. */
 rotation rot;
 direction dir;

 /* This is just a temporary variable used for simple tasks of short extent. */
 int temp;
 
 /* If the four neighbouring holes haven't been tested then... */
 if(neighbour<4)
   {

    /* ...If the neighbouring hole being considered is is not filled then... */
    if(contents_of_adjacent_holes[neighbour]==NULL)
      {
       /* Find the neighbouring hole to be considered. */
       neighbours_hole_no=link_squ[pos][neighbour];

       /* Find the pieces adjoining the hole being considered. */
       for(temp=0;temp<=3;temp++)
         contents_of_neighbours_adjacent_holes[temp]=
                                    squ_no[link_squ[neighbours_hole_no][temp]];

       /* Start at the appropriate point in the free list for this hole (some
          pre-calculation may already have been performed). */
       current_piece=piece_to_start_from[neighbours_hole_no];

       /* If this piece is being used, then given it isn't the last piece on
          the list, see if the next piece is free, i.e. find the first free
          piece on the list. */

       /* If the piece to start from has already been take then find the next
          free one. */
       while(current_piece->status==piece_used && current_piece->next!=NULL)
         current_piece=current_piece->next;
       
       /* If the piece to start from is free then... */
       if(current_piece==piece_to_start_from[neighbours_hole_no])
         {
          /* ...start the searching from the position recorded. */
          dir=dir_to_start_from[neighbours_hole_no];
          rot=rot_to_start_from[neighbours_hole_no];
         }
       else
         {       
          /* ...else start the searching form the default orientation. */
          dir=1;
          rot=0;
         }
         
       /* Search through the free list. */
       while(current_piece->next!=NULL)
         {
          /* Find the number linked with this structure on the free list. */
          square=current_piece->piece_no;

          /* Try each piece in both directions. */
          while(dir>=-1)
            {
             /* Try each piece in all rotations for both directions. */
             while(rot<=3)
               {
                /* If this is a symmetric orientation to one already used then
                   skip it since it can reveal no new information. */
                if(symmetry[square][rot][(1-dir)>>1]==false)
                  {
                   /* If the piece fits in the hole then... */
                   if(cornerless_update_fit(neighbours_hole_no,square,rot,dir,
                          contents_of_neighbours_adjacent_holes)==true)
                     {
                      /* ...this must be the first fit. */
                      /* Remember the old starting positions so can undo on
                         backtracking. */
                      old_piece_to_start_from=
                                    piece_to_start_from[neighbours_hole_no];
                      old_rot_to_start_from=
                                    rot_to_start_from[neighbours_hole_no];
                      old_dir_to_start_from=
                                    dir_to_start_from[neighbours_hole_no];
                      
                      /* Set the starting positions to the piece, rotation and
                         direction just found. */
                      piece_to_start_from[neighbours_hole_no]=current_piece;
                      rot_to_start_from[neighbours_hole_no]=rot;
                      dir_to_start_from[neighbours_hole_no]=dir;
                      
                      /* Mission accomplished, i.e. found a fit for this hole,
                         so go on to find fits for the next hole or to
                         search for new pieces to put in if this is the last
                         neighbour to find a fit for. */
                      
                      check_empty_neighbouring_holes(pos,neighbour+1,
                                                  contents_of_adjacent_holes);

                      /* Backtracking now, so restore the old starting
                         positions. */
                      piece_to_start_from[neighbours_hole_no]=
                                                    old_piece_to_start_from;
                      rot_to_start_from[neighbours_hole_no]=
                                                    old_rot_to_start_from;
                      dir_to_start_from[neighbours_hole_no]=
                                                    old_dir_to_start_from;

                      /* Set up loop arguments so fall out, we only want to
                         know that there is at least one fit. */

                      rot=3;
                      dir=-1;
                      current_piece=free_list_end->previous;
                     }
                  }
                rot++;
               }
             rot=0;
             dir-=2;
            }
          dir=1;
          current_piece=current_piece->next;
         }
      }
    else
       /* If there is already a piece in the current neighbour's hole then
          go on to see if the next neighbour is free. */
       check_empty_neighbouring_holes(pos,neighbour+1,
                                                  contents_of_adjacent_holes);
   }
 else
    /* If have found fit's for all the neighbours then continue to search 
       for pieces to put in the solution. */
    test(pos+1);
}

/******************************************************************************
  This function is used to test whether a piece in a certain orientation will
 fit into a given hole in the solution shape. It returns information about the
 ways the corners are changed if the piece does fit in the three arrays
 'corners', 'next_to_corners', and 'sol_corners'.
******************************************************************************/

boolean fit(hole pos,piece square,rotation rot,direction dir,
            struct free_piece_list_elt **edges,int *corners,
            int *next_to_corners, int *sol_corners)
{
 /* This variable will hold the number of the piece edge being tested
    against. */
 piece_edge edge;
 
 /* These are variables to deal with the corner matching. */
 int corner_sum,
     sol_corner;
 
 /* This is the hole hole next to the hole being checked which contains the
    piece to be tested against. */
 hole adjacent_hole;

 /* This is the side of the hole where the piece is to be put. */
 hole_side side;

 /* This is the flag which is set to false if the test fails and it is the 
    return value of the function. */
 boolean flag=true;

 /* Increment the counter which is a measure of how much work is being done. */
 no_comparisons++;
 
 /* Match across all the sides of the hole which the piece is to be
    fitted in until an inconsistency is found. */
 for(side=0;side<=3 && flag==true;side++)
   {
    adjacent_hole=link_squ[pos][side];

    /* Find the edge of the piece which will be in this 'side' of the hole
       when it is inserted in it's orientation. */
    edge=sider(side,rot,dir);

    /* If there is a piece to test against, and...*/
    if(edges[side]!=NULL &&
       /* comparing the edges reveals a mismatch... */
       piece_comparisons[square]
                        [edge]
                        [squ_no[adjacent_hole]->piece_no]
                        [sider(link_side[pos][side],
                               squ_rot[adjacent_hole],
                               squ_dir[adjacent_hole])]
                        [1+dir*squ_dir[adjacent_hole]*link_dir[pos][side]]
                        ==false
      )
       /* ...then fail and get out. */
       flag=false;

    else /* ...otherwise either there is no piece to match against or there is
            a piece which must match. In both these cases we just need to
            check the corners. */
      {
       /* All the vertices of the shape to make are numbered, find the index
          of the solution corner that corresponds to the corner of the side
          being tested. */
       sol_corner=sol_corners[side]=corn[pos][side];

       /* Depending on the rotation of the piece, find the corner. */
       corners[side]=piece_corner[square][edge][dir+1];
       
       /* Calculate the number of 'lugs' that will be at a corner if the piece
          being tested is actually inserted. */
       corner_sum=corners[side]+no_lugs_at_cor[sol_corner];

       /* If the corner being considered is filled then O.K. otherwise...*/
       if(corner_sum!=1)
         {
          /* ...if try to put a lug in a corner where there already is one
             then fail. */
          if(corner_sum>=2)
            flag=false;

          /* ...if there are no lugs at the corner then...*/
          else
           {
            /* ... if the corner is surrounded by lugs so could never fill
               the corner, then...*/
            if((next_to_corners[side]=
                            no_adjacent_to_piece_corner[square][edge][dir+1])
               +no_lugs_adjacent_to_cor[sol_corner]
                                           >=total_no_at_cor[sol_corner])

               /* ...fail. */
               flag=false;
           }
         }
      }
   }

 /* Let calling routine know if it fitted or not. */
 return flag;
}

/******************************************************************************
  This function is used when checking that there is at least one fit for each
 empty neighbour of a hole which to be filled with a piece. It is very similar
 to the function fit but does not return the information about the corners
 since the piece will not be put in, just remembered so that when filling the
 neighbouring hole in the future, the searching can begin from the first free
 piece found.
******************************************************************************/

boolean cornerless_update_fit(hole pos,piece square,rotation rot,direction dir,
                              struct free_piece_list_elt **edges)
{
 /* This variable will hold the number of the piece edge being tested
    against. */
 piece_edge edge;
 
 /* These are variables to deal with the corner matching. */
 int corner_sum,
     next_to_corners,
     sol_corner;
 
 /* This is the hole hole next to the hole being checked which contains the
    piece to be tested against. */
 hole adjacent_hole;

 /* This is the side of the hole where the piece is to be put. */
 hole_side side;

 /* This is the flag which is set to false if the test fails and it is the 
    return value of the function. */
 boolean flag=true;

 /* Increment the counter which is a measure of how much work is being done. */
 no_comparisons++;
 
 /* Match across all the sides of the hole which the piece is to be
    fitted in until an inconsistency is found. */
 for(side=0;side<=3 && flag==true;side++)
   {
    adjacent_hole=link_squ[pos][side];

    /* Find the edge of the piece which will be in this 'side' of the hole
       when it is inserted in it's orientation. */
    edge=sider(side,rot,dir);

    /* If there is a piece to test against, and...*/
    if(edges[side]!=NULL &&
       /* comparing the edges reveals a mismatch... */
       piece_comparisons[square]
                        [edge]
                        [squ_no[adjacent_hole]->piece_no]
                        [sider(link_side[pos][side],
                               squ_rot[adjacent_hole],
                               squ_dir[adjacent_hole])]
                        [1+dir*squ_dir[adjacent_hole]*link_dir[pos][side]]
                        ==false
      )
       /* ...then fail and get out. */
       flag=false;


   else   /* ...otherwise either there is no piece to match against or there
             is a piece which must match. In both these cases we just need
             to check the corners. */
      {
       /* All the vertices of the shape to make are numbered, find the index
          of the solution corner that corresponds to the corner of the side
          being tested. */
       sol_corner=corn[pos][side];

       /* Calculate the number of 'lugs' that will be at a corner if the piece
          being tested is actually inserted. */
       corner_sum=piece_corner[square][edge][dir+1]+no_lugs_at_cor[sol_corner];

       /* If the corner being considered is filled then O.K. otherwise...*/
       if(corner_sum!=1)
         {
          /* ...if try to put a lug in a corner where there already is one
             then fail. */
          if(corner_sum>=2)
            flag=false;
          else

          /* ...if there are no lugs at the corner then...*/
           {
            /* ... if the corner is surrounded by lugs so could never fill
               the corner, then...*/
            next_to_corners=no_adjacent_to_piece_corner[square][edge][dir+1];
            if(next_to_corners+no_lugs_adjacent_to_cor[sol_corner]
                                             >=total_no_at_cor[sol_corner])

               /* ...fail. */
               flag=false;
           }
         }
      }
   }

 /* Let calling routine know if it fitted or not */
 return flag;
}

/******************************************************************************
  This function tests to see if a piece has any axes of symmetry.
******************************************************************************/

int piece_comp(int square,int base_rot,int base_dir,int rot,int dir)
{
 int base_pattern,
     comp_pattern,
     flag=true,
     base_edge;
 for(base_edge=0;base_edge<=3 && flag==true;base_edge=base_edge+1)
   {
    base_pattern=edge_pattern(square,base_rot,base_dir,base_edge);
    comp_pattern=edge_pattern(square,rot,dir,base_edge);
    if(base_pattern!=comp_pattern)
      flag=false;
   }
 return flag;
}

/******************************************************************************
  This function is used to to compare two pieces' edges. It is used to
 construct the lookup table of comparisons between edges. 
******************************************************************************/

boolean piece_compare(piece square1,piece_edge side1,
                      piece square2,piece_edge side2,int product)
{                                     /* product is the rel dir +/- 1. */
 int dir,
     pattern1,
     pattern2,
     pattern,
     flag=true;

 /* +1 -> 0, -1 -> 1 to access array. */
 dir=(2-(product+1))>>1;

 /* Edge of first piece being tested. */
 pattern1=sides[square1][0]>>((3-side1)<<2);

 /* Edge of second piece. */
 pattern2=sides[square2][dir]>>(((1-dir)*3-(product*side2))<<2);

 /* Exclusive OR of these sides */
 pattern=pattern1^pattern2;

 /* If the inner three notches of two edges don't match exactly then... */
 if((pattern&14)!=14)
   /* ...fail. */
   flag=false;
 
 /* ...otherwise... */
 else
   {
    /* ... if the outermost notches (at the corners) coincide then... */
    if(((pattern1&pattern2)&17)>0)
       /* ...edges don't match and indicate so. */
       flag=false;
   }
 return flag;
}

/***************************************************************************/
