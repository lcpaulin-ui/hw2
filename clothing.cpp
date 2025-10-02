#include <iostream>
#include <sstream>
#include <cctype>
#include "util.h"
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

    std::string display = "{ name: " + name_ + ",\n" 
    + "info: Size: " +   size_ + " Brand : " + brand_ + ",\n" 
    + " stock: " + std::to_string(qty_) + ",\n" + 
    " price: " + std::to_string(price_) + "}"; 
    return display;
}


void Clothing::dump(std::ostream& os) const {
    os << category_  << "\n" << name_ << "\n" << price_ << "\n" << qty_ << std::endl;

}

bool Clothing::isMatch(std::vector<std::string>& searchTerms) const{
    return false;
}