#ifndef CLOTHING_H
#define CLOTHING_H

#include "product.h"
#include <iostream>
#include <string>
#include <set>
#include <map> 
#include <vector>
#include <algorithm>

class Clothing : public Product {

public: 
    Clothing ();
    Clothing(const std::string& size, const std::string& brand, const std::string category, 
        const std::string name, double price, int qty);
    virtual ~Clothing(); 
    virtual std::set<std::string> keywords() const ;
    virtual std::string displayString () const;
    virtual void dump(std::ostream& os) const; 
    virtual bool isMatch(std::vector<std::string>& searchTerms) const;

private: 
    std::string size_;
    std::string brand_;
    std::map<std::string, std::set<std::string>> keywords_; 
};
#endif