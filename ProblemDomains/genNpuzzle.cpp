/* 
 * Original file created by Andrea Centeno
 * This file generates PSVN files for the N-puzzle
*/

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <assert.h>
#include <cmath>

using namespace std;


/* GLOBAL VARIABLES */
int N; // N 
int raiz;
int mincost, maxcost, range;
bool printcost;

string convertInt(int number)
{
   ostringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

void puzzle_rule_right_cost(int r) {
    string tstr1="";
    string tstr2="";
    if((r+1) % raiz != 0){
        for (int i=0; i<r; i++)  
        {
            tstr1=tstr1+"-  ";
            tstr2=tstr2+"-  ";
        }    
        tstr1=tstr1+"b ";  
        tstr2=tstr2+"X"+" ";
        tstr1=tstr1+"X"+" ";  
        tstr2=tstr2+"b ";
        for (int i=r+2; i<N; i++)  
        {
            tstr1=tstr1+"-  ";
            tstr2=tstr2+"-  ";
        }
    
    cout << tstr1 << "=> " << tstr2 << "LABEL RightAt" << convertInt(r);

    int cost=mincost;
    if (range > 1) { cost = mincost + (rand()%range); } // set the operator cost randomly
    if (printcost) { cout << " COST " << convertInt(cost); }
    cout << endl ;
    }
}

void puzzle_rule_left_cost(int r) {
    string tstr1="";
    string tstr2="";
    if((r % raiz) != 0){
        for (int i=0; i<r-1; i++)  
        {
            tstr1=tstr1+"-  ";
            tstr2=tstr2+"-  ";
        }     
        tstr2=tstr2+"b ";
        tstr2=tstr2+"X"+" ";
        tstr1=tstr1+"X"+" "; 
        tstr1=tstr1+"b ";  
        for (int i=r+1; i<N; i++)  
        {
            tstr1=tstr1+"-  ";
            tstr2=tstr2+"-  ";
        }
    
    cout << tstr1 << "=> " << tstr2 << "LABEL LeftAt" << convertInt(r);

    int cost=mincost;
    if (range > 1) { cost = mincost + (rand()%range); } // set the operator cost randomly
    if (printcost) { cout << " COST " << convertInt(cost); }
    cout << endl ;
    }
}

void puzzle_rule_up_cost(int r) {
    string tstr1="";
    string tstr2="";
    if(r >= raiz){
        for (int i=0; i<r-raiz; i++)  
        {
            tstr1=tstr1+"-  ";
            tstr2=tstr2+"-  ";
        }  
        tstr1=tstr1+"X"+" ";
        tstr2=tstr2+"b ";  
        for (int i=r-raiz+1; i<r; i++)  
        {
            tstr1=tstr1+"-  ";
            tstr2=tstr2+"-  ";
        }    
        tstr2=tstr2+"X"+" ";  
        tstr1=tstr1+"b ";
        for (int i=r+1; i<N; i++)  
        {
            tstr1=tstr1+"-  ";
            tstr2=tstr2+"-  ";
        }

      cout << tstr1 << "=> " << tstr2 << "LABEL UpAt" << convertInt(r);

      int cost=mincost;
      if (range > 1) { cost = mincost + (rand()%range); } // set the operator cost randomly
      if (printcost) { cout << " COST " << convertInt(cost); }
      cout << endl ;

    }
    
}

void puzzle_rule_down_cost(int r) {
    string tstr1="";
    string tstr2="";
    if(r < N-raiz){
        for (int i=0; i<r; i++)  
        {
            tstr1=tstr1+"-  ";
            tstr2=tstr2+"-  ";
        }  
        tstr1=tstr1+"b ";  
        tstr2=tstr2+"X"+" ";
        for (int i=r+1; i<r+raiz; i++)  
        {
            tstr1=tstr1+"-  ";
            tstr2=tstr2+"-  ";
        }    
        tstr1=tstr1+"X"+" ";  
        tstr2=tstr2+"b ";
        for (int i=r+raiz+1; i<N; i++)  
        {
            tstr1=tstr1+"-  ";
            tstr2=tstr2+"-  ";
        }
    
    cout << tstr1 << "=> " << tstr2 << "LABEL DownAt" << convertInt(r);

    int cost=mincost;
    if (range > 1) { cost = mincost + (rand()%range); } // set the operator cost randomly
    if (printcost) { cout << " COST " << convertInt(cost); }
    cout << endl ;

    }
}

int main(int argc, char *argv[])
{
    int seed;

/******* EXTRACT COMMAND LINE ARGUMENTS ************/

    if ( (argc < 2) || (argc == 4) || (argc > 6) ) {
      cerr << "You must provide 2, 2, or 4 integers on the command line." << endl;
      cerr << "The first integer is the number of tokens. The second is the size of the turntable." << endl;
      cerr << "If there are no other integers, operator costs will all be 1." << endl;
      cerr << "If there is one other integer, operator costs will all be that value." << endl;
      cerr << "If there are three additional integers, operator costs will be generated at random, and" << endl;
      cerr << "these three integers are: the minimum cost, the maximum cost, and the random number seed." << endl;
      exit( -1 );
    }

    if( (!sscanf( argv[1], "%d", &N ))
          || N <= 1 ) {
        cerr << "bad number of tokens (must be at least 2): " << argv[1] << endl;
        exit( -1 );
    }
    if (argc == 2) {
        mincost = maxcost = 1;
    } else if (argc == 3) { // uniform costs of a specified value
        if( (!sscanf( argv[2], "%d", &mincost ))
              || mincost < 0 ) {
            cerr << "bad operator cost: " << argv[2] << endl;
            exit( -1 );
        }
        maxcost = mincost;
    } else {              // argc==6
        if( (!sscanf( argv[2], "%d", &mincost ))
              || mincost < 0 ) {
            cerr << "bad minimum operator cost: " << argv[2] << endl;
            exit( -1 );
        }
        if( (!sscanf( argv[3], "%d", &maxcost ))
              || maxcost < 0 ) {
            cerr << "bad maximum operator cost: " << argv[3] << endl;
            exit( -1 );
        }
        if( ( mincost > maxcost )) {
            cerr << "minimum cost must be less than maximum cost" << endl;
            exit( -1 );
        }
        if( (!sscanf( argv[4], "%d", &seed ))
              || seed < 2 ) {
            cerr << "bad random seed (must be 2 or larger): " << argv[4] << endl;
            exit( -1 );
        }
    }

    range = maxcost-mincost+1;
    if (range != 1) { srand(seed); }  // initialize the random number generator
    printcost = (range > 1) || (mincost > 1) ;


/******* CREATE THE PSVN FILE ************/

    cout << "# This file was created by genNpuzzle.cpp with the following command line parameters:\n# ";

    raiz = sqrt(N);
    cout << convertInt(N/raiz) << "x" << convertInt(raiz) << endl;

    cout << "\nDOMAIN tile " << convertInt(N) << endl;
    cout << "      ";
    for (int i=1;i<N;i++)  { cout << " " << convertInt(i); };
    cout << " b";  

    cout << "\n\n# a state is a vector of length " << convertInt(N) << endl;
    cout << convertInt(N) << endl;

    string Nstring = convertInt(N);
    cout << "\n# All state variables have "  << Nstring << " possible values."<< endl;
    for (int i=0;i<N;i++)  { cout << "tile " ; }; 

    cout << "\n\n";

    for (int r=0; r<N; r++)  
    {
        puzzle_rule_right_cost(r);
    }
    for (int r=0; r<N; r++)  
    {
        puzzle_rule_left_cost(r);
    }
    for (int r=0; r<N; r++)  
    {
        puzzle_rule_up_cost(r);
    }
    for (int r=0; r<N; r++)  
    {
        puzzle_rule_down_cost(r);
    }

    cout << endl;

/* In this encoding there are N different goal states, all the cyclic permutations of 0...(N-1) */    
    cout << "GOAL b " ;
    for (int i=0;i<N-1;i++)
    {
        cout << convertInt(i+1) << " ";
    }
    cout << endl;

    return (EXIT_SUCCESS);
}


