#include "BVEC.hpp"

//get and set bit functions
//cheap bit tricks were used to implement them
//The value of n must be as follows:
//0 <= n <= ULONG1_SIZE
//THIS IS NOT CHECKED,MUST BE ENSURED BY THE CALLER

bool get_nth_bit(ulong1 number,int n)
{
    //0th bit is the least significant bit
    ulong1 mask = 1 << n;
    //returns true if the bit is 1 and false otherwise
    return bool(mask & number);
}

//set the nth bit to 1
void set_nth_bit_1(ulong1& number,int n)
{
    //0th bit is the least significant bit
    ulong1 mask = 1 << n;
    number = number | mask;
    return;
}

//set the nth bit to 0
void set_nth_bit_0(ulong1& number,int n)
{
    //0th bit is the least significant bit
    ulong1 mask = 1 << n;
    number = number & (~mask);
    return;
}

//converts a binary word to a hex char
/*
This function is used while converting the bit array to the hex string after it has been constructed.
A std::string is returned instead of a char to allow simplicity in the final code,otherwise a typecast 
would be needed while printing
*/
std::string bin_to_hex(std::string word)
{
    std::string hex_char;
    /*
    The word size need not be exactly 4.This would occur in cases when the width of the
    bit array is not a multiple of 4.As a result we have to check a lot more cases to return the
    exact hex character.One solution could have been to just pad zeros to the word if it's size is not exactly
    4.This would be "slightly" inefficient in terms of memory.
    */
    if(word == "0" || word == "00" || word == "000" || word == "0000")
    {
        hex_char += "0";
        return hex_char;
    } 
    if(word == "1" || word == "01" || word == "001" || word == "0001")
    {
        hex_char += "1";
        return hex_char;
    } 
    if(word == "10" || word == "010" || word == "0010")
    {
        hex_char += "2";
        return hex_char;
    } 
    if(word == "11" || word == "011" || word == "0011")
    {
        hex_char += "3";
        return hex_char;
    } 
    if(word == "100" || word == "0100")
    {
        hex_char += "4";
        return hex_char;
    } 
    if(word == "101" || word == "0101")
    {
        hex_char += "5";
        return hex_char;
    } 
    if(word == "110" || word == "0110")
    {
        hex_char += "6";
        return hex_char;
    } 
    if(word == "111" || word == "0111")
    {
        hex_char += "7";
        return hex_char;
    } 
    if(word == "1000")
    {
        hex_char += "8";
        return hex_char;
    } 
    if(word == "1001")
    {
        hex_char += "9";
        return hex_char;
    } 
    if(word == "1010")
    {
        hex_char += "a";
        return hex_char;
    } 
    if(word == "1011")
    {
        hex_char += "b";
        return hex_char;
    } 
    if(word == "1100")
    {
        hex_char += "c";
        return hex_char;
    } 
    if(word == "1101")
    {
        hex_char += "d";
        return hex_char;
    } 
    if(word == "1110")
    {
        hex_char += "e";
        return hex_char;
    } 
    if(word == "1111")
    {
        hex_char += 'f';
        return hex_char;
    }
    //The word will always be of size less than equal to 4 and will consist only of ones and zeros
    //This is ensured by the caller function BVEC::show_hexstr()
    //So a default return value has not been explicitly defined and a PARSING_ERROR exception is thrown instead
    throw PARSING_ERROR;
} 

//IMPLEMENTATION OF THE CLASS BVEC

//non-default constructor for the class BVEC
BVEC::BVEC(ulong1 _width,std::string& hex_string)
{
    width = _width;
    //fill the vector with zeros
    ulong1_vec.assign(width/WORD_SIZE +1,0);
    
    int str_index = hex_string.length() - 1;
    for(int index = 0;;str_index--)
    {
        //case 1 : width > 4 * hex_string.length()
        //we need not do anything here as a ulong1 already has zeros padded at the front
        //only we need to break out of the loop
        if(str_index == -1)
        {
            break;
        }

        //case 2 : width  < 4 * hex_string.length()
        //we need to stop
        //this is done by the if statements after each bit is set

        //case default : width = 4 * hex_string.length()
        //brute-force bit pushing in the ulong_vec elements
        //Lord save us all!
        if(hex_string[str_index] == '0')
        {
            set_nth_bit_0(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_0(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_0(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_0(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
        }
        else if(hex_string[str_index] == '1')
        {
            set_nth_bit_1(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_0(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_0(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_0(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
        }
        else if(hex_string[str_index] == '2')
        {
            set_nth_bit_0(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_1(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_0(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_0(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
        }
        else if(hex_string[str_index] == '3')
        {
            set_nth_bit_1(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_1(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_0(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_0(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
        }
        else if(hex_string[str_index] == '4')
        {
            set_nth_bit_0(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_0(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_1(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_0(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
        }
        else if(hex_string[str_index] == '5')
        {
            set_nth_bit_1(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_0(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_1(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_0(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
        }
        else if(hex_string[str_index] == '6')
        {
            set_nth_bit_0(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_1(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_1(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_0(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
        }
        else if(hex_string[str_index] == '7')
        {
            set_nth_bit_1(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_1(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_1(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_0(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
        }
        else if(hex_string[str_index] == '8')
        {
            set_nth_bit_0(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_0(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_0(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_1(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
        }
        else if(hex_string[str_index] == '9')
        {
            set_nth_bit_1(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_0(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_0(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_1(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
        }
        else if(hex_string[str_index] == 'a')
        {
            set_nth_bit_0(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_1(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_0(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_1(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
        }
        else if(hex_string[str_index] == 'b')
        {
            set_nth_bit_1(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_1(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_0(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_1(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
        }
        else if(hex_string[str_index] == 'c')
        {
            set_nth_bit_0(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_0(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_1(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_1(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
        }
        else if(hex_string[str_index] == 'd')
        {
            set_nth_bit_1(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_0(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_1(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_1(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
        }
        else if(hex_string[str_index] == 'e')
        {
            set_nth_bit_0(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_1(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_1(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_1(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
        }
        else if(hex_string[str_index] == 'f')
        {
            set_nth_bit_1(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_1(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_1(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
            set_nth_bit_1(ulong1_vec[index/ULONG1_SIZE],index % ULONG1_SIZE);
            index++;
            if(index >= width){break;}
        }
    } 
}

//prints the bit array representation of the bit string
void BVEC::show()
{
    //the output is stored in a buffer as the final output needs to be reversed
    std::string buffer;
    buffer.reserve(width);
    for(int bit_index = 0;bit_index < width;bit_index++)
    {
        //set each element of the buffer according to the value of the corresponding bit in ulong1_vec
        buffer += get_nth_bit(ulong1_vec[bit_index/ULONG1_SIZE],bit_index % ULONG1_SIZE) ? '1' : '0';
    }
    std::reverse(buffer.begin(),buffer.end());
    std::cout<<buffer.c_str();
    return;
}

//prints the hex string representation of the stored/processed bit string    
void BVEC::show_hexstr()
{
    std::string buffer;
    std::string word;
    word.reserve(4);
    for(int bit_index = 0;bit_index < width;)
    {
        word += (get_nth_bit(ulong1_vec[bit_index/ULONG1_SIZE],bit_index % ULONG1_SIZE)) ? "1" : "0";
        bit_index++;
        //if the index is greater than the width,just convert that part to binary and break out of the loop
        if(bit_index >= width)
        {
            std::reverse(word.begin(),word.end());
            buffer += bin_to_hex(word);
            word.erase();
            break;
        }
        if(word.length() == 4)
        {
            std::reverse(word.begin(),word.end());
            buffer += bin_to_hex(word);
            word.erase();
            continue;
        }
    }
    std::reverse(buffer.begin(),buffer.end());
    std::cout<<buffer;
    return;
}

//addition of two BVECs implemented using bitwise operations for efficiency
BVEC BVEC::operator+(BVEC& bv2)
{
    //the final BVEC which stores the sum
    BVEC result;
    //the initial width of the BVEC will be the maximum of the two widths of the operands
    //this width may change by one depending on the presence of a final carry in the sum
    result.width = (width > bv2.width) ? width : bv2.width;
    //initially fill the result with zeros to avoid any garbage values
    result.ulong1_vec.assign(result.width,0); 
    
    //store a copy of the ulong1_vec of the one of the  operands as its value will be padded by zeros to have
    //the width same as the other
    std::vector<ulong1>temp_vec;
    if(width > bv2.width)
    {
        temp_vec = bv2.ulong1_vec;
        bv2.ulong1_vec.resize(ulong1_vec.size(),0);
    }
    else
    {
        temp_vec = ulong1_vec;
        bv2.ulong1_vec.resize(bv2.ulong1_vec.size(),0);
    }

    //the bitwise sum and carry for each bitwise addition
    bool sum;
    bool carry = false;
    ulong1 bit_index = 0;
    while(bit_index < result.width)
    {
        //implementing a full adder for 3 bits
        //cheap bit tricks for addition
        //calculating the sum bit
        sum = get_nth_bit(ulong1_vec[bit_index / ULONG1_SIZE],bit_index % ULONG1_SIZE) ^ get_nth_bit(bv2.ulong1_vec[bit_index / ULONG1_SIZE],bit_index % ULONG1_SIZE)^ carry;
        //calculating the carry bit 
        bool carry1 = get_nth_bit(ulong1_vec[bit_index / ULONG1_SIZE],bit_index % ULONG1_SIZE) & get_nth_bit(bv2.ulong1_vec[bit_index / ULONG1_SIZE],bit_index % ULONG1_SIZE);
        bool carry2 = get_nth_bit(ulong1_vec[bit_index / ULONG1_SIZE],bit_index % ULONG1_SIZE) & carry; 
        bool carry3 = get_nth_bit(bv2.ulong1_vec[bit_index / ULONG1_SIZE],bit_index % ULONG1_SIZE) & carry;
        carry = carry1 | carry2 | carry3;
        
        if(sum)
        {
            set_nth_bit_1(result.ulong1_vec[bit_index / ULONG1_SIZE],bit_index % ULONG1_SIZE);
            bit_index++;
        }
        else
        {
            set_nth_bit_0(result.ulong1_vec[bit_index / ULONG1_SIZE],bit_index % ULONG1_SIZE);
            bit_index++;
        }
    }
    //set the next bit of the result if a final carry is present
    //also increase the width of the result by 1 
    if(carry)
    {
        set_nth_bit_1(result.ulong1_vec[bit_index / ULONG1_SIZE],bit_index % ULONG1_SIZE);
        result.width++;
    }
    //restore the non-padded bit arrays 
    if(width > bv2.width)
    {
        bv2.ulong1_vec = temp_vec;
    }
    else
    {
       ulong1_vec = temp_vec;
    }
    return result;
}

//select bits from hi_index to lo_index(both inclusive) and return the BVEC formed by those bits
//INDEXING STARTS FROM THE LSB 
//INDEX(LSB) = 0    
BVEC BVEC::select(ulong1 hi_index,ulong1 lo_index)
{
    if(hi_index < lo_index || lo_index < 0 || hi_index > (width - 1))
    {
        throw INDEX_ERROR;
    }
    BVEC result;
    result.width = hi_index - lo_index + 1;
    result.ulong1_vec.resize(result.width/ULONG1_SIZE + 1,0);

    for(int index = 0;index < result.width;index++)
    {
        if(get_nth_bit(ulong1_vec[(index + lo_index) / ULONG1_SIZE],(index + lo_index) % ULONG1_SIZE))
        {
            set_nth_bit_1(result.ulong1_vec[index  / ULONG1_SIZE],index % ULONG1_SIZE);
        }
        else
        {
            set_nth_bit_0(result.ulong1_vec[index / ULONG1_SIZE],index % ULONG1_SIZE);
        }
    }
    return result;
}

