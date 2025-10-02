#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"
#include "product.h"
#include "book.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/

bool not_char (char c ) {
    return ( c < 97 || c > 122 ); 
}


std::set<std::string> parseStringToWords(string rawWords)
{
    rawWords = convToLower(rawWords); 
    
    set<std::string> keywords;

    // string::iterator it; 
    std::replace_if(rawWords.begin(), rawWords.end(), not_char, ' ');

    string::iterator beg = rawWords.begin();
    string::iterator end = rawWords.end();

    // std::replace_if (beg, end, not_char, ' ');
    // std::cout << *curr << std::endl;

    //  std::cout << *beg << std::endl; 
    //  std::cout << *end << std::endl;

    while (beg != end){

        // FIRST Get to the next non space char
        while(*beg != *end && *beg == ' '){
            ++beg; 
        }
        
        if(beg == end){
            break;
        }

        std::string::iterator curr = beg;
        while (*curr != *end && *curr != ' '){
            ++curr; 
        }
        std::string keyw = rawWords.substr(beg - rawWords.begin(), curr - beg);
        if (keyw.length() >= 2)
        {keywords.insert(keyw);}
        beg = curr; 
    
    }

    return keywords; 
}

int main()
{
//    std::set<string> keywords; 
   
//    keywords = parseStringToWords("i'm jill"); 

//    set<string>::iterator it;
//    for (it = keywords.begin() ; it != keywords.end(); ++it) {
//     std::cout << *it << std::endl;
//    }

//    std::set<string> s1 = {"billie", "crazy rich asians", "batman", "i'm halle b"}; 
//    std::set<string> s2 = {"crazy rich asians", "crazy rich asians", "batman", "billie", "me"}; 

//    std::set<string> inter = setIntersection(s1, s2);
//    std::set<string> uni = setUnion(s1, s2);

//    for (auto x : inter)
//         std::cout << x << std::endl;
//     for (auto x : uni)
//         std::cout << x << std::endl;

    








    return 0;
}

