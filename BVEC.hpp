#ifndef BVEC_HPP
#define BVEC_HPP

#include "errors.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

//default width of a bit_array
#define DEFAULT_WIDTH 16

//the size of the word in the hex_string which can be completely stored in one ulong1
//WORD_SIZE = ULONG1_SIZE / (number of bits required to represent a hex character( = 4)
#define WORD_SIZE 8 

//the size of data-type used to store the bit-array so that each bit of the type is used
//for example is this size is 32,it will store the bit pattern for each of 8 chars in the hex_string
//this 8 is just the WORD_SIZE
#define ULONG1_SIZE 32

typedef unsigned long ulong1;

//set and get nth bits
void set_nth_bit_1(ulong1& number,int n);
void set_nth_bit_0(ulong1& number,int n);
bool get_nth_bit(ulong1 number,int n);

//convert a binary word of size less than 4 to hex character
std::string bin_to_hex(std::string word);

class BVEC
{
    friend class Parser;
    private:
        //the width of the hex-string as an ulong1
        ulong1 width;
        //the number will be stored as a vector of ulong1s
        //each ulong1 can represent a word of 16chars in the hex-string
        std::vector<ulong1>ulong1_vec;
    public:
        //default constructor
        BVEC()
        {
            width = DEFAULT_WIDTH;
            ulong1_vec.reserve(DEFAULT_WIDTH/WORD_SIZE + 1);
        }
        //constructor which takes the width and the hex_string as an argument
        //and stores the width as the private of this class
        //while the hex_string is converted to the representation of the ulong1_vec
        /*Algorithm:
        >Read a char from the hex-string
        >Set the corresponding 4-bits in the ulong1 manually till the width is reached.
        */
        BVEC(ulong1 _width,std::string& hex_string);

        //will print the BVEC bits
        void show();

        //print the hex_string formed by the constructor
        void show_hexstr();

        //addition
        BVEC operator+(BVEC& b2);

        //bit selection
        BVEC select(ulong1 hi_index,ulong1 lo_index);
};
#endif
