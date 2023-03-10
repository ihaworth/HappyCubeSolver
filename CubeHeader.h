/******************************************************************************
*******************************************************************************

  This is the file "CubeHeader.h". It is included by all files except
 "CubeMain.c" and it creates the external references to all the global
 variables.

*******************************************************************************
******************************************************************************/

#include "CommonHead.h"

/******************************************************************************
 These variables hold the information about the shapes of the pieces used to
build the puzzles.
******************************************************************************/

/* This array contains the data about the shape of each piece in the puzzle. */
extern int sides[no_of_squ+1][2];

/* A lookup table to tell whether a particular corner of a piece has a lug in
  it. */
extern int piece_corner[no_of_squ+1][4][3];

/* A lookup table of how many lugs surround a particular corner of a piece. */
extern int no_adjacent_to_piece_corner[no_of_squ+1][4][3];

/* Record of pieces which have axes of symmetry. */
extern int symmetry[no_of_squ+1][4][2];

/* Result of comparing two sides of two pieces with a relative dir (plus 1) */
extern boolean piece_comparisons[no_of_squ+1][4][no_of_squ+1][4][3];


/******************************************************************************
 These variables tell which colour pieces are to be used to solve the puzzle
and in which order they should be taken.
******************************************************************************/

/* This flag is set if the chosen puzzle to build is the star or the big cube,
  which both require all the pieces. */
extern boolean use_all_colours;

/* This is an array of flags which show which colours have already been placed
  in order for the current starting position. */
extern int used[6];

/* This is the starting position currently being searched from. */
extern int used_index;

/* This flag indicated whether the run is only for one starting postition where
  the execution should be unterminated, or whether several starting positions
  should be considered, each for a limited amount of time. */
extern int get_out;


/******************************************************************************
 These arrays are where the the puzzle will be built during searching.
******************************************************************************/

/* This is an array where the pieces (from the free piece list) will be placed
  when they are placed in a hole of the shape. */
extern struct free_piece_list_elt *squ_no[no_in_sol+1];

/* This is the rotation each piece will take in the appropriate hole of the
  solution. */
extern int squ_rot[no_in_sol+1];

/* This is the orientation that the piece is placed into the hole with, either
  +1 for normal or -1 for inverted. */ 
extern int squ_dir[no_in_sol+1];


/******************************************************************************
 These arrays hold the info as to how the shape to be made fits together.
******************************************************************************/

/* This is the array telling which hole is adjacent to the side of the hole
  given. */
extern int link_squ[no_in_sol+1][4];

/* This array gives the hole's side which is adjacent to the side of the hole
  given. */
extern int link_side[no_in_sol+1][4];

/* This array gives the relative orientation of two adjacent holes. */
extern int link_dir[no_in_sol+1][4];


/******************************************************************************
 These arrays remember how far along the free list a search has already has
gone when testing a hole as a neighbour of another hole, so that when it comes
to searching properly, no time is wasted in repeating the search for these
known pieces on the list.
******************************************************************************/

/* This is the next known piece that fits for each hole in the shape. */
extern struct free_piece_list_elt *piece_to_start_from[no_in_sol+1];

/* This is the rotation that the piece is placed in the puzzle with. */
extern rotation  rot_to_start_from[no_in_sol+1];

/* This is the orientation the piece is placed in the puzzle with. */
extern direction dir_to_start_from[no_in_sol+1];


/******************************************************************************
 This array is how the structs holding the pieces on the free piece list are
created. As an array this can be done easily rather than mallocing lots of
individual memory.
******************************************************************************/

/* This is the array from which the free piece list is constructed. */
extern struct free_piece_list_elt free_list[no_of_squ+1];

/* These are the two terminals for the free piece list. */
extern struct free_piece_list_elt free_list_terminals[2];

/* These are easier names to read for the terminals than the array elements. */
extern struct free_piece_list_elt *free_list_start;
extern struct free_piece_list_elt *free_list_end;

/******************************************************************************
 These arrays are used by the corner testing routine.
******************************************************************************/

/* This is a count of how many lugs (0 or 1) are at each corner of the shape
  during the searching process. */
extern int no_lugs_at_cor[(no_in_sol+1)*4];

/* This is the number of lugs that is adjacent to each of the shape's corners
  during the searching process. */
extern int no_lugs_adjacent_to_cor[(no_in_sol+1)*4];

/* This is the total number of holes that converge on one particular corner of
  the shape. */
extern int total_no_at_cor[(no_in_sol+1)*4];

/* This lookup table returns which corner of the shape a particular a hole's
  corner is supposed to fit into. */
extern int corn[no_in_sol+1][4];

/* This records which hole's corners have been referenced to the corners of
  the shape. */
extern int used_cor[no_in_sol+1][4];

/* This is the number of corners the shape contains. */
extern int corners_index;

/******************************************************************************
 These variables relate to the solutions that have already been found.
******************************************************************************/

/* These are which pieces fit in which holes. */
extern int previous_squ_no[expect_no_of_unique_sol+1][no_in_sol+1];

/* These are the rotations of each piece in each hole. */
extern int previous_squ_rot[expect_no_of_unique_sol+1][no_in_sol+1];

/* These are all the orientations of the pieces in the holes. */
extern int previous_squ_dir[expect_no_of_unique_sol+1][no_in_sol+1];

/* This array records which holes have been compared when a checking the
  solution just found to a previously found solution. */
extern int tested_squ[no_in_sol+1];

/* This is how many unique solutions have been found. */
extern int no_done;


/******************************************************************************
 These variables are used record how the user wants the program to work.
******************************************************************************/

/* This toggle is set to indicate whether symmetric solutions should be
  displayed or not. */
extern int symm_toggle;

/* This is the number of pieces that are used to build the shape to make
  (minus 1). */
extern int no_to_use;

/* This is the maximum depth reached so far in searching form the current
  starting point. */
extern int depth;

/* This is a measure of how much work was done in solving the puzzle. */
extern int no_comparisons;

/* This is the time that the program started searching from the current
  starting position. */
extern clock_t start_time;

/* This is the time beyond the start time that the program should run for
  when a timed run is in progress. */
extern clock_t stop_time;

/* This flag indicates whether the execution should be timed or whether it
  should go on forever. */
extern boolean timed_run;

/* This toggle indicates whether printout should be given during the searching
  process or not. */
extern boolean diagnostics_toggle;

/***************************************************************************/
