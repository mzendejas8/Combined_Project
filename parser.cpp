#include<iostream>
#include <string>
#include <stack>
#include<queue>
#include <fstream>
#include<vector>
#include "Lex.h"
#include<unordered_map>
#include<map>


string production_Rules(char row, char col)
{   
    map< char,map<char,string> > ruleTable;
    
       //Row S
    ruleTable['S']['i']= "A";
    ruleTable['S']['x']= "D";
    ruleTable['S']['y']= "D";
    ruleTable['S']['z']= "D";
    ruleTable['S']['b']= "W";
    ruleTable['S']['a'] = "I";
    ruleTable['S']['}']= "epsilon";
    ruleTable['S']['c'] ="epsilon";
    

        //Row W
    
    ruleTable['W']['b']= "bE{S}";
    
    ruleTable['I']['a'] ="a(C){S}c{S}";
        //Row A
    ruleTable['A']['i']= "i=EN;";
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
    ruleTable['M'][';']= ";iM";
        //Row E T-> TQ
    ruleTable['E']['i']= "TQ";
    ruleTable['E']['(']= "TQ";
    ruleTable['E']['n']= "TQ";
    ruleTable['L']['<']= "<";
    ruleTable['L']['>']= ">";

   
        //Row Q Q-> +TQ|-TQ
    ruleTable['Q']['+']= "+TQ";
    ruleTable['Q']['-']= "-TQ";
    ruleTable['Q'][')']= "epsilon";
    ruleTable['Q']['$']= "epsilon";
    ruleTable['Q'][';']= "epsilon";
    ruleTable['Q']['>']= "epsilon";
    ruleTable['Q']['<']= "epsilon";
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
    ruleTable['R']['>']= "epsilon";
    ruleTable['R']['<']= "epsilon";
    
            //ROW F F- > i|(E)|n
    ruleTable['F']['i']= "i";
    ruleTable['F']['(']= "(E)";
    ruleTable['F']['n']= "n"; 

    ruleTable['F']['n']= "n"; 
    ruleTable['C']['i'] = "ELE";


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
    
   //vector iterator to access the lexeme, token and the line it was found on.
    vector<Tokens>::iterator it = vecTokens.begin(); 
   
   for(int i = 0; i < vecTokens.size(); i++ )
   {
       input.push(vecTokens[i].chLex);
     
   }
   //add $ at the end of the input , it is used to symbolized the end of the queue
    input.push('$');
    
   
    // initiate the stack by pushing the $ to symbolize the end of the stack. 
    st.push('$'); // $
    //push the first rule for statement.
    st.push('S');  // S
    
    cout << "Token: " <<it ->tokens <<"     Lexeme: "<<it->lexemes<< "\n";
        
   while(st.top()!='$')
    {
        //cout << "Top of Stack: "<< st.top()<<" Front of Stack: "<< input.front() << endl;

        row = st.top();
        col = input.front();
        prodRule = production_Rules(row,col);
        

        if(st.top()== input.front())
        {
            //processes input after ; or after }
            if((st.top()==';' and input.front()==';') or (st.top()=='}' and input.front()=='}'))
            {
                st.pop();
                input.pop();
                //we still have input.
                if(input.front()!='$')
                {   // if there is input still there push S into the stack again.
                    st.push('S');
                    
                } 
            }
            else
            {
            //if both the top of stack and front queue are eqaul pop both.
            st.pop();
            input.pop();
            it++;
            cout << "Token: " <<it ->tokens <<"     Lexeme: "<<it->lexemes<< "\n";
            
            }

              
        }
        else
        {
            //S-> A
           if(prodRule=="A")
            {
                st.pop();
                st.push('A');
               
                cout << "      <Statement> -> <Assignment> \n";

            }
            //S ->A
            else if(prodRule=="D")
            {
                st.pop();
                st.push('D');
                cout << "       <Statement> -> <Declerative> \n";
            }
            //S->W
            else if(prodRule=="W")
            {
                st.pop();
                st.push('W');
                cout << "<Statement> -> <WhileLoop>\n"; 

            }
            //S-> I
            else if(prodRule=="I")
            {
                st.pop();
                st.push('I');
                cout <<  "<Statement> -> <If Statement>\n";
            }
            // A -> i=E;
           else if(prodRule == "i=EN;")
            { 
                st.pop();
                st.push(';');
                st.push('E');
                st.push('=');
                st.push('i');
               
                cout <<"     <Assign> -> <Identifier> = <Expression> ;\n";
            }
            // E-> TQ
           else if(prodRule == "TQ")
           {
               st.pop();
               st.push('Q');
               st.push('T');
               cout<< "     <Expression> -> <Term><Expression Prime>\n";
           }
           // Q -> +TQ
          else if(prodRule == "+TQ")
            { 
                st.pop();
                st.push('Q');
                st.push('T');
                st.push('+');
                cout<< "    <Exp Prime> -> + <Term><Exp Prime>\n";
            }
            // Q -> -TQ
             else if(prodRule == "-TQ")
            { 
                st.pop();
                st.push('Q');
                st.push('T');
                st.push('-');
                cout<< "    <Exp Prime> -> -<Term><Exp Prime>\n";
            }
            //T -> FR
            else if(prodRule == "FR")
            {
                st.pop();
                st.push('R');
                st.push('F');
                cout << "     <Term> ->  <Factor><Term Prime>\n";
            }
            // T->*FR
            else if(prodRule == "*FR")
            { 
                st.pop();
                st.push('R');
                st.push('F');
                st.push('*');
                cout<< "        <Term> -> *<Factor><Term Prime>\n";
            }
            //T->/FR
             else if(prodRule == "/FR")
            { 
                st.pop();
                st.push('R');
                st.push('F');
                st.push('/');
                cout<< "        <Term> -> *<Factor><Term Prime>\n";
            }
            //T -> identifier

              else if(prodRule == "i")
            { 
                st.pop();
                st.push('i');
                cout<< "     <Term> -> <Identifier>\n";
            }
                //T->(E)

              else if(prodRule == "(E)")
            { 
                st.pop();
                st.push(')');
                st.push('E');
                st.push('(');
                cout<< "        <Term> -> (<Expression>)\n";
            }
                // T -> number
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
            // Type -> x(int)
            else if(prodRule == "x")
            {
                st.pop();
                st.push('x');
                cout  << "      <Type> -> <int>      \n";
            }
            // Type -> y(Float)
            else if(prodRule == "y")
            {
                st.pop();
                st.push('y');
                cout  << "      <Type> -> <float>      \n";

            }
            //Type -> z(bool)
            else if(prodRule == "z")
            {
                st.pop();
                st.push('z');
                cout  << "      <Type> -> <bool>      \n";
            }
            // M -> ,idM
            else if(prodRule==",iM")
            {
                st.pop();
                st.push('M');
                st.push('i');
                st.push(',');

                cout << "          <MoreIds> -> ,<id><MoreIds> \n";

            }
            //S -> W
            else if(prodRule=="bE{S}")
            {
                st.pop();
                st.push('}');
                st.push('S');
                st.push('{');
                st.push(')');
                st.push('E');
                st.push('(');
                st.push('b');
               

                cout << "  <Statement >  -> while <expression> do <Statement> else \n";

            
            }
            //S-> I
            else if(prodRule=="a(C){S}c{S}")
            {
                st.pop();
                st.push('}');
                st.push('S');
                st.push('{');
                st.push('c');
                st.push('}');
                st.push('S');
                st.push('{');
                st.push(')');
                st.push('C');
                st.push('(');
                st.push('a');
                cout << "  <Statement >  -> IF Statement \n";



            }
            else if (prodRule =="ELE")
            {
                st.pop();
                st.push('E');
                st.push('L');
                st.push('E');
                    cout <<"<Conditional> -> <Expression><relop><Expression>\n";
            }

            else if (prodRule == "<")
            {
                st.pop();
                st.push('<');
                cout << "<realop> -> < \n";

            }
            else if (prodRule == ">")
            {
                st.pop();
                st.push('>');

                cout << "<realop> -> > \n";

            }
            
            // Epsilon Rules
            else if(prodRule == "epsilon" )
            { 
                if(st.top() == 'S')
                {
                    cout << "     <Statement> -> \u03B5 \n"  ;

                }
                
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
                if(st.top() == 'Y')
                {
                    cout << "     <Type> -> \u03B5 \n"  ;

                }



                
                st.pop();
            }
            

            else
            {
                cout << "Error  at line: "<< it->line_found << endl;
                
                return 0;
            }
            
        }
          

    }
        
  if(st.top()== '$' and input.front() == '$')
  {    
    cout << "input parsed correctly  " << endl;
  }
  else 
  {
      cout << "input parsed incorrectly  " << endl;
      cout << "Error  at line: "<< it->line_found << endl;

  }

  cout <<"Number of lines: " <<line<< endl;

  





return 0;
}