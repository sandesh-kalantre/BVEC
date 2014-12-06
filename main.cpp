#include <iostream>
#include <string>
#include "parser.hpp"

using namespace std;
int main()
{
    //create a Parser object
    Parser parser;

    //the loop that runs the program
    while(true)
    {
        parser = Parser();
        string expr;
        string::iterator it_expr;

        //the prompt
        cout<<"BEE>";
        getline(cin,expr);

        //break if a single ; on a line is entered marking the end of the program
        //or if "exit()" is entered
        if(expr == ";" || expr.compare("exit") == 0 || cin.eof())
        {
            cout<<"Thank You!"<<endl;
            return 0;
        }

        //to ensure that even if ; is forgotten at the end of input
        //the program still runs without an error
        expr += ";";

        try
        {
            it_expr = expr.begin();
            parser.parse(expr);
            parser.eval(parser.expr_rpn);
        }
        catch(const char* str)
        {
            std::cout<<str<<std::endl;
            continue;
        }
    }
	return 0;
}
