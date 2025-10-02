#ifndef BOOK_H
#define BOOK_H
#include "product.h"
#include <iostream>
#include <string>
#include <set>
#include <map> 
#include <vector>
#include <algorithm>

class Book : public Product {

public: 
    Book ();
    Book (const std::string& ISBN, const std::string& author, const std::string category, 
        const std::string name, double price, int qty);
    virtual ~Book(); 
    virtual std::set<std::string> keywords() const ;
    virtual std::string displayString () const;
    virtual void dump(std::ostream& os) const; 

private: 
    std::string author_;
    std::string ISBN_;
    std::map<std::string, std::set<std::string>> keywords_; 
};
#endif