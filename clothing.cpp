#include <iostream>
#include <sstream>
#include <cctype>
#include "util.h"
#include <iomanip> 
#include <algorithm>
#include "clothing.h"
#include "product.h"

Clothing::Clothing(const std::string& name, const std::string& size, const std::string brand, 
    const std::string category, double price, int qty) : Product(category, name, price, qty), size_(size), brand_(brand) {
    }
Clothing::~Clothing () {}


//     * Returns the appropriate keywords that this product should be associated with

std::set<std::string> Clothing::keywords() const {

    // words in brand,also in the product name
    std::vector<std::string> keyw = {name_, brand_}; 
    std::set<std::string> keys;
    std::set<std::string> news;  

    std::vector<std::string> ::iterator it = keyw.begin();
    //std::vector<std::string> ::iterator fin = keyw.end();

    for ( ; it != keyw.end() ; ++it ) {
        news = parseStringToWords(*it);
        keys.insert(news.begin(), news.end());
    }

    return keys;
}

std::string Clothing::displayString () const {

    // taking idea of parser: 
    std::stringstream disp; 
    disp << name_ <<  "\n" 
    << "Size: " <<   size_ <<  " Brand: " << brand_ <<  "\n" 
    << std::setprecision(2) << std::fixed << price_ << std::to_string(qty_) << " left. << \n";
    return disp.str();
}


void Clothing::dump(std::ostream& os) const {
    os << "clothing" << std::endl;
    os << name_ << std::endl;
    os << price_ << std::endl;
    os << qty_ << std::endl;
    os << size_<< std::endl;
    os << brand_ << std::endl;

}

bool Clothing::isMatch(std::vector<std::string>& searchTerms) const{
    return false;
}