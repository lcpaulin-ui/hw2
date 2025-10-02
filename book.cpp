#include <iostream>
#include <sstream>
#include <cctype>
#include "util.h"
#include <algorithm>
#include "book.h"
#include "product.h"

Book::Book(const std::string& ISBN, const std::string& author, const std::string category, 
    const std::string name, double price, int qty) : Product(category, name, price, qty) {
        ISBN_ = ISBN;
        author_ = author; 
    }


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

    std::string display = name_ + "\n" 
    + "Author: " +   author_ + " ISBN : " + ISBN_ + "\n" 
    + std::to_string(price_) + " " + std::to_string(qty_) + " left" "\n";
    return display; 
}


void Book::dump(std::ostream& os) const {
    os << category_  << "\n" << name_ << "\n" << price_ << "\n" << qty_ << std::endl;

}