#include "parser.hpp"
#include "BVEC.hpp"
#include "parser.hpp"

//IMPLEMENTATION OF THE CLASS TOKEN

//default constructor for the Token class
Token::Token()
{
    token_type = UNKNOWN;
}

//gets a token from the expr and return iterator to the next element in the expr
std::string::iterator Token::get_token(std::string expr, std::string::iterator it_expr)
{
    //skip all kinds of whitespace
    while(std::isspace(*it_expr))
    {
        it_expr++;
    }
    //the C token
    if(*it_expr == 'C')
    {
        token_type = C;
        token += *it_expr;
        it_expr++;
        return it_expr;
    }
    //alphanumeric tokens:add,select or number-string
    if(std::isalnum(*it_expr))
    {
        while(std::isalnum(*it_expr))
        {
            token += *it_expr;
            it_expr++;
        }
        if(token == "add")
        {
            token_type = ADD;
            return it_expr;
        }
        if(token == "select")
        {
            token_type = SELECT;
            return it_expr;
        }
        else
        {
            token_type = NUMBER_STRING;
            return it_expr;
        }
    }
    //left parentheses token
    if(*it_expr == '(')
    {
        token_type = LPAREN;
        token += *it_expr;
        it_expr++;
        return it_expr;
    }
    //right parentheses token
    if(*it_expr == ')')
    {
        token_type = RPAREN;
        token += *it_expr;
        it_expr++;
        return it_expr;
    }
    //semicolon token,used internally to denote end of an expression
    if(*it_expr == ';')
    {
        token_type = SEMICOLON;
        token += *it_expr;
        it_expr++;
        return it_expr;
    }
    //else throw unknown token exception
    throw UNKNOWN_TOKEN;
}

//IMPLEMENTATION OF THE CLASS PARSER

//parse the expr string and create a rpn queue of Tokens
void Parser::parse(std::string expr)
{
    //get set:
    std::string::iterator it_expr = expr.begin();
    //store the operators on a stack
    std::stack<Token> operator_stack;
    
    while(true)
    {
        Token token;
        //go:let the parsing begin
        it_expr = token.get_token(expr,it_expr);
        if(token.token_type == Token::C)
        {
            expr_rpn.push(token);
            continue;
        }
        if(token.token_type == Token::NUMBER_STRING)
        {
            expr_rpn.push(token);
            continue;
        }
        if(token.token_type == Token::LPAREN)
        {
            operator_stack.push(token);
            continue;
        }
        if(token.token_type == Token::RPAREN)
        {
            while(!operator_stack.empty() && operator_stack.top().token_type != Token::LPAREN)
            {
                expr_rpn.push(operator_stack.top());
                operator_stack.pop();
                if(operator_stack.empty())
                {
                    throw MISSING_LPAREN;
                }
            }
            //pop the LPAREN
            operator_stack.pop();
            continue;
        }
        if(token.token_type == Token::ADD)
        {
            operator_stack.push(token);
            continue;
        }
        if(token.token_type == Token::SELECT)
        {
            operator_stack.push(token);
            continue;
        }
        if(token.token_type == Token::SEMICOLON)
		{
			break;
		}
    }
    //pop the remaining operators on to the rpn queue
    while(!operator_stack.empty())
    {
        expr_rpn.push(operator_stack.top());
        operator_stack.pop();
    }
    return;
}

//evaluate the rpn
void Parser::eval(std::queue<Token> expr_rpn)
{
    //BVEC stack for storing earlier results of compuatations
    std::stack<BVEC> BVEC_STACK;
    //number stack to store arguments for select
    std::stack<unsigned long> number_stack;
    
    while(!expr_rpn.empty())
    {
        if(expr_rpn.front().token_type == Token::C)
        {
            //BVEC starts
            unsigned long width;
            std::string number_string;
            expr_rpn.pop();

            //width
            if(expr_rpn.front().token_type == Token::NUMBER_STRING)
            {
                width = atoi(expr_rpn.front().token.c_str());
                expr_rpn.pop();
            }
            else
            {
                throw PARSING_ERROR;
            }

            //the hex_string
            if(expr_rpn.front().token_type == Token::NUMBER_STRING || expr_rpn.front().token_type == Token::ADD )
            {
                number_string = expr_rpn.front().token;
                expr_rpn.pop();
            }
            else
            {
                throw PARSING_ERROR;
            }

            BVEC bvec(width,number_string);
            BVEC_STACK.push(BVEC(width,number_string));
            std::cout<<"Evaluating (C "<<width<<" "<<number_string.c_str()<<") gives (C "<<width<<" ";
            bvec.show_hexstr();
            std::cout<<")"<<std::endl;
            continue;
        }
        if(expr_rpn.front().token_type == Token::ADD)
        {
            //check is 2 bvecs exist on the stack
            if(BVEC_STACK.size() < 2)
            {
                throw PARSING_ERROR;
            }
            BVEC bvec1 = BVEC_STACK.top();
            BVEC_STACK.pop();
            BVEC bvec2 = BVEC_STACK.top();
            BVEC_STACK.pop();

            BVEC result = bvec1 + bvec2;
            std::cout<<"Evaluating (add (C "<<bvec1.width<<" ";
            bvec1.show_hexstr();
            std::cout<<") (C "<<bvec2.width<<" ";
            bvec2.show_hexstr();
            std::cout<<") gives "<<" (C "<<result.width<<" ";
            result.show_hexstr();
            std::cout<<")"<<std::endl;
            BVEC_STACK.push(result);
            expr_rpn.pop();
            continue;
        }
        //if simply a number string without C then it is a part of select
        if(expr_rpn.front().token_type == Token::NUMBER_STRING)
        {
            number_stack.push((unsigned)atoi(expr_rpn.front().token.c_str()));
            expr_rpn.pop();
            continue;
        }
        if(expr_rpn.front().token_type == Token::SELECT)
        {
            if(BVEC_STACK.size() < 1)
            {
                throw PARSING_ERROR;
            }
            BVEC bvec1 = BVEC_STACK.top();
            BVEC_STACK.pop();
            if(number_stack.size() < 2)
            {
                throw PARSING_ERROR;
            }
            unsigned long hi_index,lo_index;
            hi_index = number_stack.top();
            number_stack.pop();
            lo_index = number_stack.top();
            number_stack.pop();

            BVEC result = bvec1.select(hi_index,lo_index);
            std::cout<<"Evaluating (select (C "<<bvec1.width<<" ";
            bvec1.show_hexstr();
            std::cout<<") "<<lo_index<<" "<<hi_index<<") gives (C "<<result.width<<" ";
            result.show_hexstr();
            std::cout<<")"<<std::endl;
            BVEC_STACK.push(result);
            expr_rpn.pop();
            continue;
        }
    }
    return;
}

