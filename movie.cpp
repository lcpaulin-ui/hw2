#include <iostream>
#include <sstream>
#include <cctype>
#include "util.h"
#include <algorithm>
#include "movie.h"
#include "product.h"

Movie::Movie(const std::string& name, const std::string& genre, const std::string rating, 
    const std::string category, double price, int qty) : Product(category, name, price, qty), genre_(genre), rating_(rating) {

    }
Movie::~Movie () {}


//     * Returns the appropriate keywords that this product should be associated with

std::set<std::string> Movie::keywords() const {

    // words in brand,also in the product name
    std::vector<std::string> keyw = {name_}; 
    std::set<std::string> keys;
    std::set<std::string> news;  

    std::vector<std::string> ::iterator it = keyw.begin();
    //std::vector<std::string> ::iterator fin = keyw.end();

    for ( ; it != keyw.end() ; ++it ) {
        news = parseStringToWords(*it);
        keys.insert(news.begin(), news.end());
    }

    keys.insert(genre_); 
    return keys;
}

std::string Movie::displayString () const {
         std::string display = "{ name: " + name_ + ",\n" 
        +" info: Genre: " +   genre_ + " Rating : " + rating_ + ",\n" 
        + " stock: " + std::to_string(qty_) + ",\n" + 
        " price: " + std::to_string(price_) + "}"; 
        return display; 
}


void Movie::dump(std::ostream& os) const {
    os << "movie" << std::endl;
    os << name_ << std::endl;
    os << price_ << std::endl;
    os << qty_ << std::endl;
    os << genre_<< std::endl;
    os << rating_ << std::endl;
}

bool Movie::isMatch(std::vector<std::string>& searchTerms) const{
    return false;
}