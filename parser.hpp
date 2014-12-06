#ifndef PARSER_HPP
#define PARSER_HPP

#include <stack>
#include <queue>
#include <iostream>
#include "errors.h"
#include "parser.hpp"

class Token
{
    friend class Parser;
    private:
        enum TOKEN_TYPE
        {
            C,
            NUMBER_STRING,
            ADD,
            SELECT,
            BVEC,
            LPAREN,
            RPAREN,
            SEMICOLON,
            UNKNOWN
        };
    public:
        //store the token type
        TOKEN_TYPE token_type;

        //string storing the token
        std::string token;

    //constructor for the Token class
    public:
        Token();

    //functions
    public:
        //stores the token attributes and returns the iterator to the next element in the string expr
        std::string::iterator get_token(std::string expr, std::string::iterator it_expr);
};

//contains methods for parsing and evaluating an expression
class Parser
{
    //constructor for the class Parser
    public:
        Parser()
        {}

    public:
        //the parsed expression in RPN form as a vector of tokens
        std::queue<Token> expr_rpn;

    //functions
    public:
       void parse(std::string expr);
       void eval(std::queue<Token> expr_rpn);

};

#endif
