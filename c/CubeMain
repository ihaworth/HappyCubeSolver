/******************************************************************************
*******************************************************************************
 
  This is the file "CubeMain.c" and it contains the routine that starts the
program going. It asks questions of the user to decide which shape to make
e.t.c.

*******************************************************************************
******************************************************************************/

#include "MainHeader.h"

/******************************************************************************
 This function is called to start the program. It asks questions as to which
shape to make, calls the initialisation routine and then starts the execution
of the code to search for the solution.
******************************************************************************/

int main()
{
     /* This is a record of how many starting positions are to be used in
        searching for the solution. */ 
 int counter,                         
     
     /* This is a spare variable for use in jobs of short extent. */
     temp,

     /* This is the number of colours to use in making the shape. */
     no_of_colours_to_use=-1,

     /* This array signals which of the colours to use in making the shape. */
     colours_to_be_used[6]={-1,-1,-1,-1,-1,-1},

     /* This is a number referring to which shape to build. */
     shape;

         /* This array holds boolean values saying which starting positions
            are to be used and which are to be skipped. */
 boolean beginnings[721];

              /* This is the number of starting positions to start from. */
 unsigned int no_to_try=0,  

              /* This is the total number of starting positions there are for
                 the chosen shape with the chosen number of colours to use in
                 making it. */
              no_combos=1,
              
              /* This is the time in seconds which should be spent in
                 searching from each starting position. */
              time;

      /* These are the colours of the pieces. The user selects which colours
         to use from this list. */
 char colnames[6][7]={"Purple","Yellow","Green","Red","Orange","Blue"};

 /* Ask the user which puzzle they want solving. */
 printf("Which shape would you like to try to make?\n\n");
 printf("      1) A small cube. (1 to 6 colours)\n");
 printf("      2) A small beam. (2 to 6 colours)\n");
 printf("      3) A large beam. (3 to 6 colours)\n");
 printf("      4) A large cube. (6 colours only)\n");
 printf("      5) A large star. (6 colours only)\n");
 printf("\nPlease enter a number:");
 for(shape=0;shape<1 || shape>5;)
   scanf("%d",&shape);

 /* Set up the arrays and make the shape arrays hold the shape selected. */
 initialise(shape);

 /* If the user didn't select the star or the big cube to make then they
    have a choice of which colour pieces are to be used to make the shape
    from. */
 if(use_all_colours==-1)
   {

    /* Ask the user which of the colours should be used. */
    printf("Please select the colours that you want to use.\n");
    for(temp=0;temp<=5;temp++)
      {
       printf("%s (y/n)?",colnames[temp]);
       if(ask()==true)
         {
          no_of_colours_to_use++;
          colours_to_be_used[no_of_colours_to_use]=temp;
         }
      }
   }

 /* If the star or big cube were chosen then all the colours should be used
    so automatically use all of them. */
 else
   {
    no_of_colours_to_use=5;
    for(temp=0;temp<=5;temp++)
      {
       colours_to_be_used[temp]=temp;
      }
   }

 /* Find out whether the symmetrical versions of each solution are required. */
 printf("Do you want the symmetric solutions to be output?");
 symm_toggle=ask();

 /* Calculate the total number of possible starting position with this choice
    of colours to use. */
 for(temp=no_of_colours_to_use+1;temp>=2;--temp)
   no_combos=no_combos*temp;

 /* Initially have 0 starting positions. */
 counter=0;                                

 /* If the user wants more than one starting position then the search from each
    starting position must be only for a fixed time.*/
 if(no_combos!=1)
   {

    /* Find out how many starting positions are required. */
    printf("How many starting combinations do you want to try 1,...,%u(all)?",
           no_combos);
    while(no_to_try<1 || no_to_try>no_combos)
      scanf("%u",&no_to_try);

    /* If want all possible combinations then... */
    if(no_to_try==no_combos)
      {
       /* ...don't ask the user to type them in, do it by filling array of
          'staring positions to do' with true so that all starting positions
          are done. */
       for(temp=1;temp<=no_combos;temp++)
         beginnings[temp]=true;

       /* Then ask how long should be spent searching from each of these
          starting positions. */
       printf("How long do you want to be spent on each of the above (sec)?");
       scanf("%u",&time);
       time=CLOCKS_PER_SEC*time;
       timed_run=true;
      }

    /* Otherwise, must only require a subset of the possible
       starting positions. */
    else
      {  

       /* Make sure all the starting positions aren't to be used until the
          users says so. */
       for(temp=1;temp<=no_combos;temp++)
         beginnings[temp]=false;

       /* Ask which starting positions are to be considered. */
       printf("Enter numbers for the start positions followed by return, -ve to remove,0 to end:");
       do
         {

          /* Grab the number. */
          scanf("%d",&temp);

          /* If it is negative then remove the start position it refers to
             from the list of ones to be considered... */
          if(-1*no_combos<=temp && temp<0 && beginnings[-1*temp]!=false)
            {
             counter--;
             beginnings[-1*temp]=false;
            }

          /* ...otherwise... */
          else

            /* If it is a positive number then add the starting position it
               refers to to the list of starting positions to be considered. */
            if(1<=temp && temp<no_combos && beginnings[temp]!=true)
              {
               counter++;
               beginnings[temp]=true;
              }
            
            /* If it is neither +ve or -ve then it must be 0 and so will be
               detected by the loop condition. */
         }
       while(temp!=0);
      }
    
    /* If reached this point in the code then the user must have entered a
       number of starting positions. If there is more than one starting
       position then ask for the time for which to execute from each start
       position. */
    if(counter>1)
      {
       printf("How long do you want to be spent on each of the above (sec)?");
       scanf("%u",&time);
       time=CLOCKS_PER_SEC*time;
       timed_run=true;
      }
   }

 /* Otherwise there must be only one possible point from which to start
    e.g. a small cube using only one colour, in which case... */
 else
 
   /* ...set the only starting point to be the only possible one. */
   beginnings[1]=true;

 /* Find out whether the user requires information as to how the program is
    performing during execution. */
 printf("Do you want diagnostics while the program is running?");
 diagnostics_toggle=ask();        

 /* Find the first starting position the user wants to search from and from
    there start the search. */
 recurse(no_of_colours_to_use,no_of_colours_to_use,colours_to_be_used,
         beginnings,time);

 /* Let the user know that the searching is complete. */
 printf("FINISHED!!\n");
}

/*****************************************************************************/
