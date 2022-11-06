/******************************************************************************
*******************************************************************************
 
 This is the file "CubeSim.c" and it contains the routines used to decide
whether the solution just found is identical, symmetrical or different to the
solutions previously found.

*******************************************************************************
******************************************************************************/

#include "CubeHeader.h"

/******************************************************************************
  This function, when called, looks at the current complete solution and
 compares it to the solutions previously found. If the current solution is
 distinct from the previous ones then 'new' is returned. If the solution is
 just a rotation of a previous solution then 'identical' is returned. If the
 solution is the same as a previous one apart from rotation of pieces with
 symmetries then 'symmetric' is returned.
******************************************************************************/

enum sol_type similar(void)
{
 int solution,
     rel_dir;
 piece square;
 hole counter;
 enum sol_type temp=new,
               flag=new;

 /* Look over all previously found solutions, until a match is found. */
 for(solution=0;solution<=no_done && temp!=identical;solution++)
   {

    /* Starting from the first piece. */
    square=0;
    
    /* Find which piece fits in the first 'hole' in the solution. */
    while(previous_squ_no[solution][0]!=squ_no[square]->piece_no)
      square++;
    
    /* Initialise array saying that which holes have been compared. */
    for(counter=0;counter<=no_to_use;counter++)
      tested_squ[counter]=false;

    /* Find how the current solution relates to the solution to be
       compared against. */
    rel_dir=squ_dir[square]*previous_squ_dir[solution][0];

    /* Start comparing the two solutions. */
    temp=search(solution,
                0,
                0,
                square,
                strong_sider(sider(0,
                                   previous_squ_rot[solution][0],
                                   previous_squ_dir[solution][0]),
                             squ_rot[square],
                             squ_rot[square]),
                rel_dir);

    /* If the new solution matches somehow then record this. */
    if(temp!=new)
      flag=temp;
   }

 return flag;
}

/******************************************************************************
 This function recursively walks a previous solution and the current solution.
Piece, by piece it compares the solutions checking to see if the new solution
is identical, symmetrical or different to the previous one.
******************************************************************************/

enum sol_type search(int solution,int old_squ,int old_on,
                        int new_squ,int new_on,int rel_dir)
{
 int edge,
     old_off,
     new_off,
     old_rot,
     new_rot,
     old_dir,
     new_dir;
 enum sol_type flag=identical,
               temp=identical;

 if(tested_squ[old_squ]==true)
   flag=identical;   /* This is not a new solution. */
 else
   {
    tested_squ[old_squ]=true;
    if(previous_squ_no[solution][old_squ]!=squ_no[new_squ]->piece_no)
      flag=new;     /* So far this solution is new. */
    else
      {
       old_rot=previous_squ_rot[solution][old_squ];
       new_rot=squ_rot[new_squ];
       old_dir=previous_squ_dir[solution][old_squ];
       new_dir=squ_dir[new_squ];
       for(edge=0;edge<=3 && flag==identical;edge++)
         {
          if(squ_no[link_squ[new_squ]
                            [strong_sider(edge,new_rot,new_dir)]]->piece_no!=
             previous_squ_no[solution]
                            [link_squ[old_squ][strong_sider(edge,
                                                            old_rot,
                                                            old_dir)]])
            {
             flag=symmetric;   /* The solution is symmetrical. */
            }
         }
       for(edge=0;edge<=3 && temp!=new;edge++)
         {
          old_off=strong_sider(edge,old_rot,old_dir);
          new_off=mod(new_on-rel_dir*(old_on-old_off),4);
          temp=search(solution,
                      link_squ[old_squ][old_off],
                      link_side[old_squ][old_off],
                      link_squ[new_squ][new_off],
                      link_side[new_squ][new_off],
                      rel_dir);
          if(temp==new)
            {
             flag=new;         /* The solution is unique. */
            }
          else
            {
             if(flag==symmetric || temp==symmetric)
               flag=symmetric; /* The solution is symmetrical. */
             else
               flag=identical; /* The solution is just a rotation of the
                                  previous solution. */
            }
         }
      }
   }
 return flag;
}

/*****************************************************************************/
