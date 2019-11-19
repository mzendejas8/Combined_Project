#include<iostream>
#include <string>
#include <stack>
#include<queue>
#include <fstream>
#include<vector>

int line  = 1;



using namespace std;

enum name
{
    START = 0,
    IIDENT,
    EIDENT,
    INNUM,
    EDNUM,
    ICOMM,
    E_COMM,
    ISSEP,
    ISOP,
    IFLOAT,
    EFLOAT
};



struct Tokens{
    string tokens;
    string lexemes;
    char chLex;
    int line_found;
   
};


class Lex{

private:

    char currch;
    string str;
    int col ;
    int currst ;
    Tokens one;
    string nums;

public:
 

// Function that checks to see if the value is key word.
bool  isKeyword( string &str)
{
// stored all keywords in an array to for comparing.
    string keywordCollec [20]={"int","float","bool","if", "else","then", "endif",
    "while","whileend","do","doend","for","forend","input","output","and","or","function","begin","end"};
    bool flag=false;
// compares the string passed to it to see if matching keyword is found.   
    for(int i= 0; i<20 ; i++)
    {
        if(str == keywordCollec[i])
        {    
        return true;
        } 
    }
     return false;
}
// Function that will get the coressponding column for the state table. 
int getCol(char x) 
{
// checks to see if character is a letter or $ 
    if (isalpha(x) or x == '$')
    {
        return 0;
    }
// checks to see if char is a digit  
  else if(isdigit(x))
    {
        return 1;
    }
// checks to see if the char is any type of white space 
    else if (x == '\t' or x =='\n' or x == ' ')
    {
        if(x=='\n'){
        line++;
        one.line_found=line;
        }
       
        return 2;
    }
//  switch statement used to check for operators and seperators
      switch(x)
    {   
        case '\'' : return 3;
                    break;
        case '(' : return 4;
                    break;
        case ')' : return 5;
                    break;
        case '{' : return 6;
                    break;
        case '}' : return 7;
                    break;
        case '.' : return 8;
                    break;
        case ':' : return 9;
                    break;
        case '!' : return 10;
                    break; 
        case '*' : return 11;
                    break;
        case '+' : return 12;
                    break;
        case '-' : return 13;
                    break;
        case '=' : return 14;
                    break;
        case '/' : return 15;
                    break;
        case '<' : return 16;
                    break;
        case '>' : return 17;
                    break; 
        case '%': return 18;
                    break;
        case ',': return 19;
                    break;
        case ';':  return 20;
                    break;          
                
    }  
   return 0;           
}



int st_tab(int row , int col)
{


 // state table in an array of size 11 x 21
        int stateTable[11][21]=
        { 
 //     0  1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20
 //     L  D   sp  '   (	)  {	}	.	:	!	*	+	-	=	/	<	>	%   ,   ;
//     ----------------------------------------------------------------------------------- 
        1,	3,	0,	7,	7,	7,	7,	7,	7,	7,	5,	8,	8,	8,	8,	8,	8,	8,	8,	7, 7, // 0
        1,	1,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2, 2, // 1
        0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, 0, // 2
        4,	3,	4,	4,	4,	4,	4,	4,	9,	4,	5,	4,	4,	4,	4,	4,	4,	4,	4,	4, 4, // 3
        0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, 0, // 4 
        5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	6,	5,	5,	5,	5,	5,	5,	5,	5,	5, 5, // 5
        0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, 0, // 6
        0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, 0, // 7 
        0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, 0, // 8
        10,	9,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,10,// 9
        0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,  0};//10 



    return stateTable[row][col];


}

void lexxer(vector<Tokens> & vecTokens)
{
        // fstream class used to input and output text to and from files.
        ifstream inFile;
       
        inFile.open("input.txt");
        
        // checks to see if either filed correctly opened.
        if(!inFile.is_open())
        {
            cout << "error opening file" << endl;
            return;
        }

        //Loop that starts reading characters in one by one.
        while(inFile.get(currch))
        {
            
        //  we set col to the appropriate number according to the char that is passed to the function.
            col = getCol(currch);
            
        // if statement used to find a operator.
              if (st_tab(currst,col)==ISOP)
                   { 
                       //cout    << "Operator    =   " <<currch << endl;
                       one.tokens = "Operator";
                       one.lexemes= currch;
                       one.chLex = currch;
                       vecTokens.push_back(one);
                       inFile.unget();

                       
                   }
        // if statement used to find seperator.         
            else if (st_tab(currst,col)==ISSEP)
                    {
                        //cout    <<"Seperator   =   " <<currch  << endl;
                       one.tokens = "Seperator";
                       one.chLex = currch;
                       one.lexemes = currch;
                       vecTokens.push_back(one);
                       inFile.unget();
                        
                    } 
        // if statement used to start storing chars into the string.  
            else if (st_tab(currst,col)==IIDENT) 
                    {
                        str+=currch;
                    } 
        // if statement used to pass the string to keyword function and check for keyword.
            else if (st_tab(currst,col)==EIDENT) 
                    {
                        if(isKeyword(str))
                        {   
                            //cout    << "Keyword     =   " << str << endl;   
                            one.tokens = "Keyword";
                            one.lexemes = str;
                            if(str == "int")
                            {one.chLex= 'x';}
                           else if(str == "float")
                            {one.chLex= 'y';}
                            else if(str == "bool")
                            {one.chLex='z';}
                            else if (str == "if")
                            {one.chLex='a';}
                            else if (str == "while")
                            {one.chLex='b';}
                            // need to change
                            else if (str == "else")
                            {one.chLex='c';}

                            vecTokens.push_back(one);  
                             
                        }
                        else 
                        {
                            //cout    << "Identifier  =   " << str << endl;
                            one.tokens = "Identifier";
                            one.lexemes = str;
                            one.chLex = 'i';
                            vecTokens.push_back(one); 
     
                        }
                        str = "";
                        inFile.unget();
                        inFile.unget();
                    } 
        //if statement that starts reading int into a string
            else if (st_tab(currst,col)==INNUM) 
                        {
                             nums += currch;
                        }
        //if that is used when the int state is reached
             else if (st_tab(currst,col)==EDNUM)
                        {
                            //cout    << "Int         =   " << nums << endl;
                            one.tokens = "Int";
                            one.lexemes = nums;
                            one.chLex = 'n';
                            vecTokens.push_back(one);
                            nums="";
                            inFile.unget();
                            inFile.unget();
                        }
        // if statement that is used when read float is reached               
            else if ( st_tab(currst,col)==IFLOAT )
                         {
                             nums += currch;  
                         } 
        // if statement that is used when float state is reached. 
            else if (st_tab(currst,col)==EFLOAT)
                        {
                           // cout    <<"Float       =   " << nums << endl;
                           one.tokens = "Float";
                            one.lexemes = nums;
                            one.chLex = 'n';
                            vecTokens.push_back(one);
                           
                            nums ="";
                            inFile.unget();
                            inFile.unget();
                            
                        }
        // sets the column to the new state.
                 currst = st_tab(currst,col);
        }
        // close both the iput and output file.
        inFile.close();   
}

};

