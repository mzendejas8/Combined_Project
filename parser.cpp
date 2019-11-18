#include<iostream>
#include <string>
#include <stack>
#include<queue>
#include <fstream>
#include<vector>
#include "Lex.h"
#include<unordered_map>


string production_Rules(char row, char col)
{   
    unordered_map< char,unordered_map<char,string> > ruleTable;
    
       //Row S
    ruleTable['S']['i']= "A";
    ruleTable['S']['x']= "D";
    ruleTable['S']['y']= "D";
    ruleTable['S']['z']= "D";
    
        //Row A
    ruleTable['A']['i']= "i=E;";

        //Row D D-> TidM;
    ruleTable['D']['x']= "YiM;";
    ruleTable['D']['y']= "YiM;";
    ruleTable['D']['z']= "YiM;";
    ruleTable['D']['$']="epsilon";

        //Row Y Y -> x|y|z
    ruleTable['Y']['x']= "x";
    ruleTable['Y']['y']= "y";
    ruleTable['Y']['z']= "z";
    ruleTable['Y']['i']= "epsilon";
        //Row M M -> ,M
    ruleTable['M'][',']= ",iM";
    ruleTable['M'][';']= "epsilon";
        //Row E T-> TQ
    ruleTable['E']['i']= "TQ";
    ruleTable['E']['(']= "TQ";
    ruleTable['E']['n']= "TQ";
    ruleTable['E']['$']= "ERROR";
    
        //Row Q Q-> +TQ
    ruleTable['Q']['+']= "+TQ";
    ruleTable['Q']['-']= "-TQ";
    ruleTable['Q'][')']= "epsilon";
    ruleTable['Q']['$']= "epsilon";
    ruleTable['Q'][';']= "epsilon";

        //Row T T-> FR
    ruleTable['T']['i']= "FR";
    ruleTable['T']['(']= "FR";
    ruleTable['T']['n']= "FR";
        //ROW R R-> *FR
    ruleTable['R']['+']= "epsilon";
    ruleTable['R']['-']= "epsilon";
    ruleTable['R']['*']= "*FR";
    ruleTable['R']['/']="/FR";
    ruleTable['R'][')']= "epsilon"; 
    ruleTable['R']['$']= "epsilon";
    ruleTable['R'][';']= "epsilon";
    
        //ROW F F- > i|(E)|n
    ruleTable['F']['i']= "i";
    ruleTable['F']['(']= "(E)";
    ruleTable['F']['n']= "n"; 



    return ruleTable[row][col];
}

int main()
{  
    // vector of struct Token that will hold the tokens and lexemes.
    vector <Tokens> vecTokens;
    // Lexxer object to access lexical analyzer.
    Lex one;
    // passing the vector by referecen to get tokens and lexemes from lexical analyzer.
    one.lexxer(vecTokens);
    char row;
    char col;
    // stack that will be used to hold production rules.
    stack <char> st;
    // queue that will hold our input.
    queue <char> input;
    // string that will hold the current production rule.
    string prodRule;
    
  


    

    // Loop that accesses all the tokens from the vector and stores it in the queue in the form of char.
    //i was used to represent  identifier.
    //x, y , and z where used for int, float, bool in that order.
    //operators and and separators are stored as is.
   for(int i = 0; i < vecTokens.size(); i++ )
   {
       input.push(vecTokens[i].chLex);
       cout  <<vecTokens[i].chLex;  
   }
   cout << "\n";
    input.push('$');
    
   

    st.push('$'); // $
    st.push('S');  // S

   while(st.top()!='$')
    {
        //cout << "Top of Stack: "<< st.top()<<" Front of Stack: "<< input.front() << endl;

        row = st.top();
        col = input.front();
        prodRule = production_Rules(row,col);

        if(st.top()== input.front())
        {
            //processes input after ;
            if(st.top()==';' and input.front()==';')
            {
                st.pop();
                input.pop();
                //we still have input.
                if(input.front()!='$')
                {
                    st.push('S');
                }

            }
            else
            {
            st.pop();
            input.pop();
            
            }
               
        }
        else
        {

           if(prodRule=="A")
            {
                st.pop();
                st.push('A');
               
                cout << "      <Statement> -> <Assignment> \n";

            }
            else if(prodRule=="D")
            {
                st.pop();
                st.push('D');
                cout << "       <Statement> -> <Declerative> \n";
            }
           else if(prodRule == "i=E;")
            { 
                st.pop();
                st.push(';');
                st.push('E');
                st.push('=');
                st.push('i');
               
                cout <<"     Assign> -> <Identifier> = <Expression> ;\n";
            }
           else if(prodRule == "TQ")
           {
               st.pop();
               st.push('Q');
               st.push('T');
               cout<< "     <Expression> -> <Term><Expression Prime>\n";
           }
          else if(prodRule == "+TQ")
            { 
                st.pop();
                st.push('Q');
                st.push('T');
                st.push('+');
                cout<< "    <Exp Prime> -> + <Term><Exp Prime>\n";
            }
             else if(prodRule == "-TQ")
            { 
                st.pop();
                st.push('Q');
                st.push('T');
                st.push('-');
                cout<< "    <Exp Prime> -> -<Term><Exp Prime>\n";
            }
            else if(prodRule == "FR")
            {
                st.pop();
                st.push('R');
                st.push('F');
                cout << "     <Term> ->  <Factor><Term Prime>\n";
            }
            else if(prodRule == "*FR")
            { 
                st.pop();
                st.push('R');
                st.push('F');
                st.push('*');
                cout<< "        <Term> -> *<Factor><Term Prime>\n";
            }
             else if(prodRule == "/FR")
            { 
                st.pop();
                st.push('R');
                st.push('F');
                st.push('/');
                cout<< "        <Term> -> *<Factor><Term Prime>\n";
            }

              else if(prodRule == "i")
            { 
                st.pop();
                st.push('i');
                cout<< "     <Term> -> <Identifier>\n";
            }

              else if(prodRule == "(E)")
            { 
                st.pop();
                st.push(')');
                st.push('E');
                st.push('(');
                cout<< "        <Term> -> (<Expression>)\n";
            }
               else if(prodRule == "n")
            { 
                st.pop();
                st.push('n');
                
                cout<< "      <Term> -> <number>\n";
            }
            // Declarative Rules
            else if(prodRule == "YiM;")
            {
                st.pop();
                st.push(';');
                st.push('M');
                st.push('i');
                st.push('Y');
                cout  << "      <Declarative> -> <Type><Identifier><MoreIds>;\n";
            }
            else if(prodRule == "x")
            {
                st.pop();
                st.push('x');
                cout  << "      <Type> -> <int>      \n";
            }
            else if(prodRule == "y")
            {
                st.pop();
                st.push('y');
                cout  << "      <Type> -> <float>      \n";

            }
            else if(prodRule == "z")
            {
                st.pop();
                st.push('z');
                cout  << "      <Type> -> <bool>      \n";
            }
            else if(prodRule==",iM")
            {
                st.pop();
                st.push('M');
                st.push('i');
                st.push(',');

                cout << "          <MoreIds> -> ,<id><MoreIds> \n";

            }

            else if(prodRule == "epsilon" )
            { 
                
                
                if(st.top() == 'Q')
                {
                    cout << "     <Expression Prime> -> \u03B5 \n"  ;

                }
                else if (st.top() == 'R')
                {
                        cout << "     <Term Prime> -> \u03B5 \n"  ;

                }
                else if (st.top() == 'D')
                {
                        cout << "     <Declerative> -> \u03B5 \n"  ;

                }
                else if (st.top() == 'Y')
                {
                        cout << "     <Type> -> \u03B5 \n"  ;

                }
                else if (st.top() == 'M')
                {
                        cout << "     <MoreIds> -> \u03B5 \n"  ;

                }
                st.pop();
            }
            

            else
            {
                cout << "Error  at line: " << endl;
                
                return 0;
            }
            
        }
          

    }

        
  if(st.top()== '$' and input.front() == '$')
  {    
    cout << "input parsed correctly  " << endl;
  }
  else 
  cout << "  \n";
    





return 0;
}