/******************************************************************************
*******************************************************************************
 
 This is the file "CubeInit.c" and it contains the routines to set up the 

*******************************************************************************
******************************************************************************/

#include "CubeHeader.h"

/******************************************************************************
 This function initialises the arrays used in solving the puzzle, and also
pre-calculates the comparison of all possible piece's edges with all other
piece's edges and stores the results in a lookup table.
******************************************************************************/

void initialise(int shape)
{
 int loop1,
     loop2,
     arg1,
     arg2,
     arg3,
     square,
     square1,
     edge,
     edge1,
     lug_no,
     rel_dir,
     base_rot,
     base_dir,
     rot,
     start_rot,
     dir,
     start_dir;

/* The data entered for the description of the pieces needs inverting so that
  a piece can be considered in an up-side-down state. This is done by reading
  the least significant bit out of the bit pattern for the normal orientation,
  and placing it into the new bit pattern by performing a left shift and then
  putting it in, the bit pattern for the normal orientation is then shifted
  right by one and then the processed is repeated until the pattern is fully
  inverted.
   In doing this all the lugs of all the pieces are manipulated individually.
  This gives a great opportunity to validate the data for the pieces. All the
  individual colours in the puzzle form a cube of side 5, so each set of
  colours should have 44 lugs to form a complete cube (3 (lugs) *12 (sides) +
  1 (lug) * 8 (corners) = 44 (lugs)). Thus a count of the lugs of all the
  pieces of one colour should reveal any extra/missing lugs. */

 /* For all the pieces. */
 for(square=0;square<=no_of_squ;square++)
   {
    /* If we are on a new colour... */
    if(mod(square,6)==0)
      {
       /* ...reset the running total. */
       arg3=0;
      }

    /* arg1 is the edge data for the given direction. */
    arg1=sides[square][0];                       
    /* arg2 is 0, ready to take the inverted pattern. */
    arg2=0;

    /* For all the lugs on the piece. */
    for(loop2=0;loop2<=16;loop2++)
      {
       /* Make space for new bit. */
       arg2<<=1;
       /* Insert new bit. */
       arg2=arg2+(arg1 & 1);

       /* Don't count the first bit since it is the same as the last bit... */
       if(loop2>0)
         {
          /* ...and add up edge elements for validation. */
          arg3=arg3+(arg1 & 1);
         }

       /* If at a corner then... */
       if(loop2%4==0)
         {   
          /* ...record the lug at the corner for the inverted direction... */
          if(loop2>0)
            {
             piece_corner[square][4-(loop2/4)][2]=(arg1 & 1);
            }
          /* ...record the lug at the corner for the normal direction. */
          if(loop2<16)
            {
             piece_corner[square][3-(loop2/4)][0]=(arg1 & 1);
            }
         }

       /* If next to a corner then... */
       if(loop2%2==1)
         {
          /* ...find which corner we are next to... */
          lug_no=mod(loop2-(mod(loop2+1,4)-1),16);    
          /* ...and set the arrays which hold the information about lugs
             adjacent to corners of pieces for both the normal and inverted
             directions. */
          no_adjacent_to_piece_corner[square][mod(4-(lug_no/4),4)][2]+=
                                                                 (arg1 & 1);
          no_adjacent_to_piece_corner[square][mod(3-(lug_no/4),4)][0]+=
                                                                 (arg1 & 1);
         }
       /* Update source. */
       arg1>>=1;
      }
    /* Write inverted bit pattern to the array. */
    sides[square][1]=arg2;
    /* If added up a full coluor's lugs then... */
    if((square+1)%6==0)
      {
       /* Report any invalid bit patterns. */
       if(arg3!=44)
         printf("Cube %d is incorrect.\n",square/6);
      }
   }

/* Set up the array of comparisons between pieces. */

 /* For all the pieces... */
 for(square=0;square<=no_of_squ;square++)
  {
   /* ...in relation to all other pieces... */
   for(square1=square+1;square1<=no_of_squ;square1++)
    {
     /* ...for all egdes of the first piece... */
     for(edge=0;edge<=3;edge++)
      {
       /* ...and all edges of the second piece... */
       for(edge1=0;edge1<=3;edge1++)
        {
         /* ...in similar or contrary orientation. */
         for(rel_dir=-1;rel_dir<=1;rel_dir+=2)
          {
           /* Compare the two edges in the appropriate direction. */
           if(piece_compare(square,edge,square1,edge1,rel_dir)==true)
            {
             /* If they fit then record as such... */
             piece_comparisons[square][edge][square1][edge1][rel_dir+1]=true;
             piece_comparisons[square1][edge1][square][edge][rel_dir+1]=true;
            }
           else
            {
             /* ...else record that they didn't. */
             piece_comparisons[square][edge][square1][edge1][rel_dir+1]=false;
             piece_comparisons[square1][edge1][square][edge][rel_dir+1]=false;
            }
          }
        }
      }
    }
  }

/* The searching rejects certain orientations of pieces for testing if the
  piece has already been tried in an orientation which yields an identical
  shape to this one (only if the user doesn't want symmetrical solutions).
  To save time on these comparisons, all the pieces are tested here for
  symmetries and the results stored in a lookup table. */

 /* Initialise the symmetry array. */
 for(square=0;square<=35;square++)
   {
    for(rot=0;rot<=3;rot++)
      {
       for(dir=0;dir<=1;dir++)
         symmetry[square][rot][dir]=false;
      }
   }

/* Calculate symmetrys of pieces and store in 'symmetry' array. */

 /* For all squares... */
 for(square=0;square<=35;square++)
   {
    /* ...in normal and inverted directions... */
    for(base_dir=1;base_dir>=-1;base_dir-=2)
      {
       /* ...in all orientations. */
       for(base_rot=0;base_rot<=3;base_rot++)
         {
          /* Calculate which orientations to compare itself to. */
          start_rot=mod(base_rot+1,4);
          start_dir=base_dir;
          if(start_rot==0)
            {
             start_dir=-1;
             if(base_dir==-1)
               start_rot=4;
            }
          /* For all directions and... */
          for(dir=start_dir;dir>=-1;dir-=2)
            {
             /* ...all rotations to compare itself to. */
             for(rot=start_rot;rot<=3;rot++)
               {
                /* Compare the square with itself in the other direction... */
                if(piece_comp(square,base_rot,base_dir,rot,dir)==true)
                  {
                   /* ...and store in the array. */
                   symmetry[square][rot][(1-dir)>>1]=true;
                  }
               }
             start_rot=0;
            }
         }
      }
   }

/* The program uses a linked list to store the pieces to use. It is created
  as an array of type "struct free_piece_list_elt" and then the pointers
  are set up to re-order the elements later. */

 for(loop1=0;loop1<=no_of_squ;loop1++)
   {
    /* Initialise array version of the free piece list. */
    free_list[loop1].piece_no=loop1;
    free_list[loop1].status=piece_free;
    /* If this isn't the start or end of the list then... */
    if(loop1!=no_of_squ && loop1!=0)
      {
       /* ...set the previous and next pointers to point to the last and next
          element of the array creating the list initially in the same order
          as the array. */
       free_list[loop1].previous=free_list+loop1-1;
       free_list[loop1].next=free_list+loop1+1;
      }
    /* ...otherwise... */
    else
      {
       /* ...if this is the first element in the list, then just set up the
          next pointer... */
       if(loop1==0)
         {
          free_list[loop1].next=free_list+loop1+1;
         }
       /* ...otherwise it must be the end of the list so just set up the
          previous pointer. */
       else
         {
          free_list[loop1].previous=free_list+loop1-1;
         }
      }
   }

 /* Set up the terminals so they are back to back, i.e. the empty list. */
 free_list_start->piece_no=start_terminal;
 free_list_start->status=piece_used;
 free_list_start->previous=NULL;
 free_list_start->next=free_list_end;

 free_list_end->piece_no=end_terminal;
 free_list_end->status=piece_used;
 free_list_end->previous=free_list_start;
 free_list_end->next=NULL;

/* When searching the space, a 'look ahead' technique is employed which checks
  that there is at least one piece left that can fit into each of the free
  spaces next to the piece just placed in. In this implementation the first
  piece on the free list to fit is taken to signify that at least one piece
  exists that will fit in. This is recorded so that when it is one of these
  hole's turns to be filled the search doesn't have to be done again, and any
  subsequent search can start with this piece (all previous pieces obviously
  won't fit). This piece of code initialises this array. */

 /* For every hole in the solution. */
 for(loop1=0;loop1<=no_in_sol;loop1++)
   {
    piece_to_start_from[loop1]=free_list_start;
    rot_to_start_from[loop1]=0;
    dir_to_start_from[loop1]=1;
   }


/* The program works by searching for a piece to fit and when it finds it, it
  is stored in some arrays. It also uses some arrays to hold the data of how
  the shape to make looks. This piece of code initialises these arrays. */

 /* For all possible holes. */
 for(loop1=0;loop1<=no_in_sol;loop1++)
   {
    /* These arrays describe how a particular piece fits into a hole. */
    squ_no[loop1]=NULL;
    squ_rot[loop1]=false;
    squ_dir[loop1]=false;
    
    /* For each side of the hole. */
    for(loop2=0;loop2<=3;loop2++)
      {
       /* These arrays describe which hole is next to another in a shape. */
       link_squ[loop1][loop2]=false;
       link_side[loop1][loop2]=false;
       link_dir[loop1][loop2]=false;
      }
   }
 /* For the expected number of solutions. */
 for(loop1=0;loop1<=expect_no_of_unique_sol;loop1++)
   {
    /* For each piece in the solution. */
    for(loop2=0;loop2<=no_to_use;loop2++)
      {
       /* Set the arrays to say that no previous solutions have been found. */
       previous_squ_no[loop1][loop2]=false;
       previous_squ_rot[loop1][loop2]=false;
       previous_squ_dir[loop1][loop2]=false;
      }
   }

/* Now fill out the arrays describing the shape to make with the shape chosen
   by the user. */
 switch(shape)
   {
    case 1:small_cube();
      break;
    case 2:two_cube_beam();
      break;
    case 3:three_cube_beam();
      break;
    case 4:the_big_cube();
      break;
    case 5:the_star();
      break;
   }

/* In describing the shapes above, not all the associations are described. For
  example, if piece one side one connects to piece two side three is given in
  the above description, then piece two side three connects to piece one side
  one, won't be. The following piece of code fills in these complementary 
  links automatically. */

 for(loop1=0;loop1<=no_to_use;loop1++)
   {
    for(loop2=0;loop2<=3;loop2++)
      {
       arg1=link_squ[loop1][loop2];
       arg2=link_side[loop1][loop2];
       if(link_squ[arg1][arg2]==false)
         {
          link_squ[arg1][arg2]=loop1;
          link_side[arg1][arg2]=loop2;
          link_dir[arg1][arg2]=link_dir[loop1][loop2];
         }
      }
   }

/* The program uses extra arrays to deal with the corners since they are a 
  special part of the comparison where more than two pieces interact. This
  code initialises these arrays. */

 /* For all possible elements of the corner array... */
 for(loop1=0;loop1<(no_in_sol+1)*4;loop1++)
   {
    /* ...initialise the arrays. */
    no_lugs_at_cor[loop1]=0;
    no_lugs_adjacent_to_cor[loop1]=0;
   }
    
 /* Set up the corners of the shape so that they are numbered and that each
    hole in the solution has a lookup table entry saying which corner of the
    solution it is from. */
 init_corner();
 
}

/******************************************************************************
 This function first initialises an array which records which corners have been
given references. Then it goes to each corner of each hole and calls the
function check_cor which gives all holes around that corner the same reference.
This is so that each corner of the shape to make have all the holes associated
holes with it to hand so that counts of the number of lugs at a corner of the
shape can be maintained, e.t.c.
******************************************************************************/

void init_corner(void)
{
 hole pos=0;
 int corner=0;              

 /* For all the possible corners. */
 for(pos=0;pos<=no_to_use;pos++)
   {

    /* For all the corners of the holes. */
    for(corner=0;corner<=3;corner++)
      {
       /* Set each square's corners so that they are initially not associated
          with any corner of the shape to make. */
       used_cor[pos][corner]=false;
      }
   }                            

 /* Now walk over all the holes in the solution shape. */
 for(pos=0;pos<=no_to_use;pos++)
   {

    /* And walk over the corners of each square. */
    for(corner=0;corner<=3;corner++)
      {
      
       /* If a corner of a hole hasn't already been associated with a corner
          of the shape then... */
       if(used_cor[pos][corner]==false)
         {

          /* Set this corner of this hole (and all other corners of holes)
             to be referred to as a corner of the solution numbered 'index'. */
          check_cor(pos,corner);
          corners_index++;
         }
      }
   }
 corners_index--;
}

/******************************************************************************
 This function looks at the corner of the hole passed and gives it a reference
given it doesn't already have one. It then recursively moves to the hole next
to this one and makes sure that the same corner has the same reference when
looked up form this hole.
******************************************************************************/

void check_cor(hole pos,int pos_corner)
{
 /* If this hole's corner hasn't already been given a reference then... */
 if(used_cor[pos][pos_corner]==false)
   {

    /* ...signal that it now is to be given one. */
    used_cor[pos][pos_corner]=true;

    /* Show that another hole has been found that impinges on this corner of
       the shape, this gives a count of how many pieces. */
    total_no_at_cor[corners_index]++;
    
    /* Set the reference of this hole's corner to the corner of the shape. */
    corn[pos][pos_corner]=corners_index;
    
    /* Check to see if the corner of the hole next to this hole (which shares
       this corner) has been given a reference, and if not, then do it. */
    check_cor(link_squ[pos][pos_corner],
              mod(link_side[pos][pos_corner]-link_dir[pos][pos_corner],4)
             );
   }
}

/*****************************************************************************/
