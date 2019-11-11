#include<iostream>
#include <string>
#include <stack>
#include<queue>
#include <fstream>
#include<vector>




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
};







// Function that checks to see if the value is key word.
bool  isKeyword( string &str)
{
// stored all keywords in an array to for comparing.
    string keywordCollec [18]={"int","float","bool","if", "else","then", "endif",
    "while","whileend","do","doend","for","forend","input","output","and","or","function"};
    bool flag=false;
// compares the string passed to it to see if matching keyword is found.   
    for(int i= 0; i<18 ; i++)
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
        case '_' : return 13;
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
{char currch;
    string str;
    int col ;
    int currst = 0;
    Tokens one;
    string nums;
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
                       one.lexemes="";
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
                       one.lexemes = "";
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
                            one.chLex= 'k';
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
                            one.chLex = ' ';
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
                            one.chLex = ' ';
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






enum Terminal
{ //Non Terminals:
    S=0,    //0
    A,      //1
    E,      //2
    EPR,    //3
    T ,     //4
    TPR,    //5
    F ,     //6
   
 // Terminals:
    ADD,    //7
    MULT,   //8
    LP,     //9
    RP,     //10
    ID,     //11
    DOLL,   //12
    MIN,    //13
    DIV,    //14
    SEMI,    //15
    EQUAL   //16


};
enum RULES
{
    
    R_A = 0, //S -> A
    R_ID_EQ_E,//A -> id = E;
    R_T_EPR, //E -> TE'
    R_PL_T_EPR,//E'-> +TE'
    R_SU_T_EPR, //E'-> -TE'
    R_F_TPR, //T -> FT'
    R_MULT_F_TPR, //T'-> *FT'
    R_DIV_F_TPR,//T'-> /FT'
    R_PAR_E_PAR,//F -> (E)
    R_ID,//F -> id
    
    E_ep,
    EP_ep,
    T_ep,
    TP_ep,
    F_ep,
    ER = -1 //ERROR

};
int Table(int row, int col)
{           
            int table [7][10] ={    
                            //     ID           +           -               *           /           (           )       $     ;    =
                        /*S*/     R_A       , ER        , ER        , ER          , ER         , ER         , ER    , ER    , ER    , ER    , 
                        /*A*/     R_ID_EQ_E , ER        , ER        , ER          , ER         , ER         , ER    , ER    , ER    , ER    , 
                        /*E*/     R_T_EPR   , ER        , ER        , ER          , ER         , R_T_EPR    , ER    , ER    , E_ep  , ER    , 
                        /*E'*/    ER        , R_PL_T_EPR, R_SU_T_EPR, ER          , ER         , ER         , E_ep  , E_ep  , E_ep  ,E_ep   , 
                        /*T*/     R_F_TPR   , ER        , ER        , ER          , ER         , R_F_TPR    , ER    , ER    , T_ep  , T_ep  , 
                        /*T'*/    ER        , TP_ep     ,TP_ep      , R_MULT_F_TPR, R_DIV_F_TPR, ER         , TP_ep , TP_ep , TP_ep , TP_ep , 
                        /*F*/     R_ID      , ER        , ER        , ER          , ER         , R_PAR_E_PAR, ER    , ER    , F_ep  , F_ep                 
         };

    return table[row][col];
}





int get_col(char c)
{
switch(c)
    {
        case 'i': 
        return 0;
        case '+':
        return 1;
        case '-':
        return 2;
        case '*':
        return 3;
        case '/':
        return 4;
        case '(':
        return 5;
        case ')':
        return 6;
        case '$':
        return 7;
        case ';':
        return 8;
        case '=':
        return 9;
    }

    return -1;
}


int main()
{   vector <Tokens> vecTokens;
    
        lexxer(vecTokens);
    

    string tableValue;
    stack<int> st;
    queue <char> input;
    int row;
    int col;
    
   for(int i = 0; i < vecTokens.size(); i++ )
   {
       input.push(vecTokens[i].chLex);

       cout << vecTokens[i].chLex << endl;
   }
    

    input.push('$');
    
   

    st.push(DOLL); // $
    st.push(S);  // S
    int curr_st;
    
    
   while(st.top()!=DOLL and input.front()!= '$')
    { 
        col = get_col(input.front());
        row = st.top();
      

        
      if((st.top()== ADD and input.front()=='+') or (st.top()== MULT and input.front()=='*') or (st.top()== LP and input.front()=='(') 
      or (st.top()== RP and input.front()==')') or (st.top()== ID and input.front()=='i') or (st.top()== MIN and input.front()=='-') or
      (st.top()== DIV and input.front()=='/') or (st.top()== SEMI and input.front()==';') or (st.top()== EQUAL and input.front()=='=')  )
      {
          st.pop();
          input.pop();
      }
      
        else
            {
                
                curr_st = Table(row,col);
                switch(curr_st)
                {   
                     //S -> A
                    case R_A:
                    st.pop();
                    st.push(A);
                    cout << "<Statement> -> <Assign>" << endl;
                    break;
                    //A -> id = E;
                    case R_ID_EQ_E: 
                    st.pop();
                    st.push(SEMI);
                    st.push(E);
                    st.push(EQUAL);
                    st.push(ID);
                    cout << "<Assing> -> <identifier> = <Expression>;"<< endl;
                    break;
                    //E -> TE'
                    case  R_T_EPR:
                    st.pop();
                    st.push(EPR);
                    st.push(T);
                    cout << "<Expression> -> <Term><Exp Prime>" << endl;
                    break;
                    //E'-> +TE'
                    case  R_PL_T_EPR:
                    st.pop();
                    st.push(EPR);
                    st.push(T);
                    st.push(ADD);
                    cout << "<Exp Prime> -> + <Term><Exp Prime>" << endl;
                    break;
                    //E'-> -TE'
                    case R_SU_T_EPR:
                    st.pop();
                    st.push(EPR);
                    st.push(T);
                    st.push(MIN);
                    cout << "<Exp Prime> -> - <Term><Exp Prime>" <<endl;
                    break;
                    //T -> FT'
                    case R_F_TPR:
                    st.pop();
                    st.push(TPR);
                    st.push(F);
                    cout << "<Term> -> <Factor><Term Prime>"<< endl;
                    break;
                    //T'-> *FT'
                    case R_MULT_F_TPR:
                    st.pop();
                    st.push(TPR);
                    st.push(F);
                    st.push(MULT);
                    cout << "<Term Prime> -> *<Factor><Term Prime>" << endl;
                    break;
                    //T'-> /FT'
                    case R_DIV_F_TPR:
                    st.pop();
                    st.push(TPR);
                    st.push(F);
                    st.push(DIV);
                    cout << "<Term Prime> -> /<Factor><Term Prime>"<< endl;
                    break;
                    //F -> (E)
                    case R_PAR_E_PAR:
                    st.pop();
                    st.push(RP);
                    st.push(E);
                    st.push(LP);
                    cout << "<Factor> -> <(Expression)>" << endl;
                    break;
                    //F -> id
                    case R_ID:
                    st.pop();
                    st.push(ID);
                    cout <<"<Factor> -> <identifier>" << endl;
                    break;
                    //EPSILON
                    case E_ep:
                    st.pop();
                    cout << "<Expression> -> \u03B5" << endl;
                    break;

                    case EP_ep:
                    st.pop();
                    cout << "<Expression Prime> -> \u03B5" << endl;
                    break;

                    case T_ep:
                    st.pop();
                    cout << "<Term> -> \u03B5" << endl;
                    break;

                    case TP_ep:
                    st.pop();
                    cout << "<Term Prime> -> \u03B5" << endl;
                    break;

                    case F_ep:
                    st.pop();
                    cout << "<Factor> -> \u03B5" << endl;
                    break;
                    

                    case ER:
                    cout << "ERROR" << endl;
                    return 0;
                    break;        
        }
        
            }
    }
    
 cout << "input parsed correctly  " << endl;
    





return 0;
}