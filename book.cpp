#include <iostream>
#include <sstream>
#include <cctype>
#include "util.h"
#include <algorithm>
#include "book.h"
#include "product.h"

Book::Book(const std::string& name, const std::string& author, const std::string ISBN, 
    const std::string category, double price, int qty) : Product(category, name, price, qty), author_(author), ISBN_(ISBN) { 
    }

Book::~Book () {}


//     * Returns the appropriate keywords that this product should be associated with

std::set<std::string> Book::keywords() const {

    // words in authors name , isbn number, name, author, brand 
    std::vector<std::string> keyw = {name_, author_}; 
    std::set<std::string> keys;
    std::set<std::string> news;  

    std::vector<std::string> ::iterator it = keyw.begin();
    //std::vector<std::string> ::iterator fin = keyw.end();

    for ( ; it != keyw.end() ; ++it ) {
        news = parseStringToWords(*it);
        keys.insert(news.begin(), news.end());
    }

    keys.insert(ISBN_); 

    return keys;
}

std::string Book::displayString () const {

    std::string display = "{ name: " + name_ + ",\n" 
    +"info: Author: " +   author_ + " ISBN : " + ISBN_ + ",\n" 
    + " stock: " + std::to_string(qty_) + ",\n" + 
    " price: " + std::to_string(price_) + "}"; 
    return display; 
}


void Book::dump(std::ostream& os) const {
    os << category_  << "\n" << name_ << "\n" << price_ << "\n" << qty_ << std::endl;

}

bool Book::isMatch(std::vector<std::string>& searchTerms) const{
    return false;
}