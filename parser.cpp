#include<iostream>
#include <string>
#include <stack>
#include<queue>
#include <fstream>
#include<vector>
#include "Lex.h"
#include<unordered_map>




int main()
{  
    unordered_map< char,unordered_map<char,string> > ruleTable;
    vector <Tokens> vecTokens;
    Lex one;
    one.lexxer(vecTokens);
    
    stack <char> st;
    queue <char> input;

    char row;
    char col;
    string prodRule;
    
     //Row S

    ruleTable['S']['i']= "i=E;";
    ruleTable['S']['+']= ", cant start at with +";
    ruleTable['S']['-']= ", cant start at with -";
    ruleTable['S']['*']= ", cant start at with *";
    ruleTable['S']['/']= ", cant start at with /";
    ruleTable['S']['(']= "ERROR ";
    ruleTable['S'][')']= ", cant start at with )";
    ruleTable['S']['n']= "ERROR";
    ruleTable['S']['$']= "ERROR";

    
        //Row E T-> TQ
    ruleTable['E']['i']= "TQ";
    ruleTable['E']['+']= ", cant start at with +";
    ruleTable['E']['-']= ", cant start at with -";
    ruleTable['E']['*']= ", cant start at with *";
    ruleTable['E']['/']= ", cant start at with /";
    ruleTable['E']['(']= "TQ";
    ruleTable['E'][')']= ", cant start at with )";
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







    
   for(int i = 0; i < vecTokens.size(); i++ )
   {
       input.push(vecTokens[i].chLex);
       cout  <<vecTokens[i].chLex;
      

       

   }
   cout << "\n";
    input.push('$');
    
   

    st.push('$'); // $
    st.push('S');  // S
    
    
    
     //cout << "Token:        Lexeme: "   << endl;
    int i = 1;
   while(st.top()!='$')
    {
        //cout << "Top of Stack: "<< st.top()<<" Front of Stack: "<< input.front() << endl;


        row = st.top();
        col = input.front();
        prodRule = ruleTable[row][col];
        
       
       
        if(st.top()== input.front())
        {
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
            {st.pop();
            input.pop();
            //cout << "Token:       Lexeme: "  << endl;
            }
        }
           else if(prodRule == "i=E;")
            { 
                st.pop();
                st.push(';');
                st.push('E');
                st.push('=');
                st.push('i');
                cout << "    <Statement> -><Assign>\n";
                cout <<"     Assign> -> <Identifier> = <Expression> ;\n";
            }

        else
        {

           if(prodRule == "TQ")
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
                st.pop();
            }
            

            else
            {
                cout << "Error " <<prodRule << endl;
                
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
    

cout << "number of lines "<< line_number << endl;



return 0;
}