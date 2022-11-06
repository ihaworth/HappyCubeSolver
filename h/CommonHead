/******************************************************************************
*******************************************************************************

 This is the file "CommonHead.h", it holds all the definitions that all other
files need and is included in these indirectly by being included inside the
headers "MainHeader.h" and "CubeHeader.h".

*******************************************************************************
******************************************************************************/

#include <stdio.h>
#include <time.h>

/******************************************************************************
 These are the boolean values.
******************************************************************************/

#define true (0)
#define false (-1)

/******************************************************************************
 Define piece numbers that can be used for the start and end terminals of the
free piece list.
******************************************************************************/

#define start_terminal (-1)
#define end_terminal (-2)

/******************************************************************************
 Define some useful constants for the program.
******************************************************************************/

/* This is the maximum number of holes in the solution (minus 1). */
#define no_in_sol (35)

/* This is the total number of pieces available to make shape from (minus 1) */
#define no_of_squ (35)

/* This is the maximum expected number of solutions for any particular shape.
   It is used to set up an array which will hold the solutions found so that
   symmetrical and identical solutions are not displayed more than once. */
#define expect_no_of_unique_sol (125)

#ifndef CLOCKS_PER_SEC
  #define CLOCKS_PER_SEC (1000000)
#endif

/******************************************************************************
 These macros are used instead of functions within the code because inline code
is faster than calling a function especially when the overhead of calling the
function will be about equal to the amount of processing the function will do
(which arises because the function is so small), and this shows up when the
function is used frequently within loops e.t.c.
******************************************************************************/

/* This macro gives true mathematical modulo functionality. */
#define mod(number,base) (((number)>=0)?(number)%(base):((((number)%(base))+(base))%(base)))

/* The following macros deal with the relationship between the edges of a
   piece and the sides of the hole it is placed into, where 'rot' is the
   rotation of the piece measured by the number of clockwise 90 degree
   rotations the zero the edge of the piece has to undergo from being in line
   with the zero the side of the hole to ending up in the position being
   considered. */

/* This macro generates the number of the edge which is against a particular
   side of a hole when the piece is place in with rotation rot and direction
   dir. */
#define sider(side,rot,dir) mod((dir)*((side)-(rot)),4)

/* This macro generates the side of a hole corresponding to a given edge of a
   piece inserted in the hole with rotation rot and direction dir. */
#define strong_sider(edge,rot,dir) (mod((rot)+(dir)*(edge),4))

/******************************************************************************
 The following are types used throughout the program to help the reader
distinguish between the many different but similar entities therein.
******************************************************************************/

/* These types are for parts of the empty shell. */

typedef int hole;           /* This is a space where a piece can be placed. */
typedef int hole_side;      /* Numbers 0-3 describe the 4 sides of a hole. */
                            

/* These types describe the pieces of the puzzle. */

typedef int piece;          /* Numbers 0-35, are pieces of the puzzle. */
typedef int piece_edge;     /* Numbers 0-3 describe the 4 edges of a piece. */


/* These types describe the relationship between 'holes' and 'pieces'. */

typedef int rotation;       /* This is the number of clockwise 90 degree
                              rotations of the piece's 0 edge from the hole's
                              0 side. */
typedef int direction;      /* This is +1 if a square's sequence of 'edges' is
                              0,1,2,3 is clockwise and -1 if it is 0,3,2,1. */


/* This type is a standard true/false type. */

typedef int boolean;        /* This type is either true or false. */

/* This type describes a new solution in terms of an old solution. */

enum sol_type {new,         /* This is a solution never seen before. */
               identical,   /* This is a copy of a previous solution. */
               symmetric};  /* This is a copy of a previous solution but with
                               symmetrical pieces in other orientations. */


/* These types are used to describe the list of free pieces. */

/* This describes whether or not a piece has been used in the solution yet. */
enum piece_state {piece_free, piece_used};

/* This structure is the one that is used to make nodes on the
   free piece list. */
struct free_piece_list_elt{
                           piece piece_no;
                           enum piece_state status;
                           struct free_piece_list_elt *previous;
                           struct free_piece_list_elt *next;
                          };

/******************************************************************************
 These are the pre-declarations of all the functions in the program.
******************************************************************************/

/* This function is used to to compare two pieces' edges. It is used to
  construct the lookup table of comparisons between edges. */
boolean piece_compare(piece,piece_edge,piece,piece_edge,int);

/* This function tests to see if a piece has any axes of symmetry. */
int piece_comp(int,int,int,int,int);

/* This function is used to test whether a piece in a certain orientation will
  fit into a given hole in the solution shape. */
boolean fit(hole,piece,rotation,direction,struct free_piece_list_elt **,
            int *,int *,int *);

/* This function is used when checking that there is at least one fit for each
  empty neighbour of a hole which to be filled with a piece.*/
boolean cornerless_update_fit(hole,piece,rotation,direction,
                              struct free_piece_list_elt **);

/* This is the main function that does the searching. It is recursively called
  to place pieces in successive 'holes' in the solution. */
void test(hole);

/* This function returns the bit pattern representing the edge of a piece, in
  a given orientation. */
int edge_pattern(piece,rotation,direction,hole_side);

/* This function copies a solution from the current shape into the 'previous'
  arrays so that it can be used to compare with future solutions. */
void copy(void);

/* This function waits for a key press and returns 'true' if 'Y' or 'y' are
  pressed and 'false' if 'N' or 'n' are pressed. */
int ask(void);

/* This function is used to set up the free piece list in the order dictated by
  the starting position entered by the user. */
void recurse(int,int,int *,int *,unsigned int);

/* This function prints out the free list, it is not used in the program but it
  was used to debug the program. */
void print_free_list(struct free_piece_list_elt*);

/* This function, when called, looks at the current complete solution and
  compares it to the solutions previously found. */
enum sol_type similar(void);

/* This function recursively walks a previous solution and the current
  solution. Piece, by piece it compares the solutions checking to see if the
  new solution is identical, symmetrical or different to the previous one. */
enum sol_type search(int,int,int,int,int,int);

/* This function initialises the arrays used in solving the puzzle, and also
  pre-calculates the comparison of all possible piece's edges with all other
  piece's edges and stores the results in a lookup table. */
void initialise(int);

/* This function goes to each corner of each hole and sets the corner
  references. */
void init_corner(void);

/* This function looks at the corner of the hole passed and gives it a
  reference. It then recursively moves to the hole next to this one and makes
  sure that the same corner has the same reference when looked up from this
  hole. */
void check_cor(hole,int);

/* This is the function which sets up the arrays holding the shape to make 
  to contain the small cube data.*/
void small_cube(void);

/* This is the function which sets up the arrays holding the shape to make 
  to contain small bar data.*/
void two_cube_beam(void);

/* This is the function which sets up the arrays holding the shape to make 
  to contain the large bar data.*/
void three_cube_beam(void);

/* This is the function which sets up the arrays holding the shape to make 
  to contain the big cube data.*/
void the_big_cube(void);

/* This is the function which sets up the arrays holding the shape to make 
  to contain the star data.*/
void the_star(void);

/* This function writes the information about the corners of the piece being
  placed into the solution into the arrays holding the information about the
  corners of the solution. */
void update_corner(int *,int *,int *);

/* This function removes the information about the corners of a piece, that is
  being removed from the solution on backtracking, from the arrays holding the
  information about the corners of the solution. */
void return_corner(int *,int *,int *);

/* This function checks the empty neighbouring holes to the hole where a piece
 has just been inserted to make sure that there is still at least one piece
 that fits in each hole. */
void check_empty_neighbouring_holes(hole, hole_side,
                                    struct free_piece_list_elt **);

/* This function takes an argument which is an indication of the symmetry of
 this solution in relation to other previously found solutions, and then
 prints the solution according to whether it is sufficiently unique to qualify
 for displaying. */
void print(enum sol_type);

/*****************************************************************************/
