/******************************************************************************
*******************************************************************************

  This is the file "MainHeader.h". It is included by the file "CubeMain.c" and
 it creates the explicit declarations of all the global variables.

*******************************************************************************
******************************************************************************/

#include "CommonHead.h"


/******************************************************************************
 These variables hold the information about the shapes of the pieces used to
build the puzzles.
******************************************************************************/

/* This array contains the data about the shape of each piece in the puzzle. 
  The data is stored in the form of a bitmap referring to the lugs around the
  edge of the pieces. The bit pattern starts at the west end of edge 0 (north)
  and reads along this edge going east, then south down edge 1 (east), then
  west along edge 2 (south), and finally north along edge 3 back to the start,
  re-recording the north-west corner. The corner is re-recorded so that it
  is easily referenced by side 0 or side 3, rather for one side having to look
  it up in the other side's data.

            start      N
                 \  --->
                  .----------.
                  |    0     |
                ^ |          | |
             W  | | 3      1 | | E
                | |          | |
                | |    2     | V
                  `----------'
                       <---
                       S
   The array is set up with the data for the piece in it's normal position.
  Then an inversion is done to calculate the bitmap for the piece when it is
  inverted, i.e. when the sides are ordered 0,3,2,1. This is calculated and
  not typed to save time on behalf of the user and to reduce the number of
  errors.
*/
int sides[no_of_squ+1][2]={
                            /* Purple (0-5) */

                            {0xa634,0},
                            {0x42a4,0},
                            {0x3b4a,0},
                            {0x7476,0},
                            {0x1a247,0},
                            {0x5a3a,0},

                            /* Yellow (6-11) */

                            {0x5c5a,0},
                            {0x5b5a,0},
                            {0x4aa4,0},
                            {0xaa34,0},
                            {0x1aa45,0},
                            {0x4b4a,0},

                            /* Green (12-17) */

                            {0xaa4a,0},
                            {0x4b44,0},
                            {0x1b445,0},
                            {0x45ba,0},
                            {0x4a4a,0},
                            {0x1ab5b,0},

                            /* Red (18-23) */

                            {0xb3b6,0},
                            {0x1a6a5,0},
                            {0x15a43,0},
                            {0x84aa,0},
                            {0x1b465,0},
                            {0x44a4,0},

                            /* Orange (24-29) */

                            {0x12b5b,0},
                            {0x15a4b,0},
                            {0xc464,0},
                            {0xab58,0},
                            {0x6ab4,0},
                            {0x44a8,0},

                            /* Blue (30-35) */

                            {0x4444,0},
                            {0x15b5b,0},
                            {0x4a44,0},
                            {0xa5ba,0},
                            {0xab4a,0},
                            {0xaba4,0}
                            };

/* A lookup table to tell whether a particular corner of a piece has a lug in
  it. */
int piece_corner[no_of_squ+1][4][3];

/* A lookup table of how many lugs surround a particular corner of a piece. */
int no_adjacent_to_piece_corner[no_of_squ+1][4][3];

/* Record of pieces which have axes of symmetry. */
int symmetry[no_of_squ+1][4][2];

/* Result of comparing two sides of two pieces with a relative dir (plus 1) */
boolean piece_comparisons[no_of_squ+1][4][no_of_squ+1][4][3];


/******************************************************************************
 These variables tell which colour pieces are to be used to solve the puzzle
and in which order they should be taken.
******************************************************************************/

/* This flag is set if the chosen puzzle to build is the star or the big cube,
  which both require all the pieces. */
boolean use_all_colours=false;

/* This is an array of flags which show which colours have already been placed
  in order for the current starting position. */
int used[6]={false,false,false,false,false,false};

/* This is the starting position currently being searched from. */
int used_index=0;

/* This flag indicated whether the run is only for one starting position where
  the execution should be unterminated, or whether several starting positions
  should be considered, each for a limited amount of time. */
int get_out=false;


/******************************************************************************
 These arrays are where the the puzzle will be built during searching.
******************************************************************************/

/* This is an array where the pieces (from the free piece list) will be placed
  when they are placed in a hole of the shape. */
struct free_piece_list_elt *squ_no[no_in_sol+1];

/* This is the rotation each piece will take in the appropriate hole of the
  solution. */
int squ_rot[no_in_sol+1];

/* This is the orientation that the piece is placed into the hole with, either
  +1 for normal or -1 for inverted. */ 
int squ_dir[no_in_sol+1];


/******************************************************************************
 These arrays hold the info as to how the shape to be made fits together.
******************************************************************************/

/* This is the array telling which hole is adjacent to the side of the hole
  given. */
int link_squ[no_in_sol+1][4];

/* This array gives the hole's side which is adjacent to the side of the hole
  given. */
int link_side[no_in_sol+1][4];

/* This array gives the relative orientation of two adjacent holes. */
int link_dir[no_in_sol+1][4];


/******************************************************************************
 These arrays remember how far along the free list a search has already has
gone when testing a hole as a neighbour of another hole, so that when it comes
to searching properly, no time is wasted in repeating the search for these
known pieces on the list.
******************************************************************************/

/* This is the next known piece that fits for each hole in the shape. */
struct free_piece_list_elt *piece_to_start_from[no_in_sol+1];

/* This is the rotation that the piece is placed in the puzzle with. */
rotation  rot_to_start_from[no_in_sol+1];

/* This is the orientation the piece is placed in the puzzle with. */
direction dir_to_start_from[no_in_sol+1];


/******************************************************************************
 This array is how the structs holding the pieces on the free piece list are
created. As an array this can be done easily rather than mallocing lots of
individual memory.
******************************************************************************/

/* This is the array from which the free piece list is constructed. */
struct free_piece_list_elt free_list[no_of_squ+1];

/* These are the two terminals for the free piece list. */
struct free_piece_list_elt free_list_terminals[2];

/* These are easier names to read for the terminals than the array elements. */
struct free_piece_list_elt *free_list_start=free_list_terminals;
struct free_piece_list_elt *free_list_end=free_list_terminals+1;

/******************************************************************************
 These arrays are used by the corner testing routine.
******************************************************************************/

/* This is a count of how many lugs (0 or 1) are at each corner of the shape
  during the searching process. */
int no_lugs_at_cor[(no_in_sol+1)*4];

/* This is the number of lugs that is adjacent to each of the shape's corners
  during the searching process. */
int no_lugs_adjacent_to_cor[(no_in_sol+1)*4];

/* This is the total number of holes that converge on one particular corner of
  the shape. */
int total_no_at_cor[(no_in_sol+1)*4];

/* This lookup table returns which corner of the shape a particular a hole's
  corner is supposed to fit into. */
int corn[no_in_sol+1][4];

/* This records which hole's corners have been referenced to the corners of
  the shape. */
int used_cor[no_in_sol+1][4];

/* This is the number of corners the shape contains. */
int corners_index=0;

/******************************************************************************
 These variables relate to the solutions that have already been found.
******************************************************************************/

/* These are which pieces fit in which holes. */
int previous_squ_no[expect_no_of_unique_sol+1][no_in_sol+1];

/* These are the rotations of each piece in each hole. */
int previous_squ_rot[expect_no_of_unique_sol+1][no_in_sol+1];

/* These are all the orientations of the pieces in the holes. */
int previous_squ_dir[expect_no_of_unique_sol+1][no_in_sol+1];

/* This array records which holes have been compared when a checking the
  solution just found to a previously found solution. */
int tested_squ[no_in_sol+1];

/* This is how many unique solutions have been found. */
int no_done=-1;


/******************************************************************************
 These variables are used record how the user wants the program to work.
******************************************************************************/

/* This toggle is set to indicate whether symmetric solutions should be
  displayed or not. */
int symm_toggle;

/* This is the number of pieces that are used to build the shape to make
  (minus 1). */
int no_to_use;

/* This is the maximum depth reached so far in searching form the current
  starting point. */
int depth=0;

/* This is a measure of how much work was done in solving the puzzle. */
int no_comparisons;

/* This is the time that the program started searching from the current
  starting position. */
clock_t start_time;

/* This is the time beyond the start time that the program should run for
  when a timed run is in progress. */
clock_t stop_time;

/* This flag indicates whether the execution should be timed or whether it
  should go on forever. */
boolean timed_run=false;

/* This toggle indicates whether printout should be given during the searching
  process or not. */
boolean diagnostics_toggle;

/*****************************************************************************/
