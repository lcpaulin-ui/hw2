#ifndef MOVIE_H
#define MOVIE_H
#include "product.h"
#include <iostream>
#include <string>
#include <set>
#include <map> 
#include <vector>
#include <algorithm>

class Movie : public Product {

public: 
    Movie();
    Movie(const std::string& genre, const std::string& rating, const std::string category, 
        const std::string name, double price, int qty);
    virtual ~Movie(); 
    virtual std::set<std::string> keywords() const ;
    virtual std::string displayString () const;
    virtual void dump(std::ostream& os) const;
    virtual bool isMatch(std::vector<std::string>& searchTerms) const;
    

private: 
    std::string genre_;
    std::string rating_;
    std::map<std::string, std::set<std::string>> keywords_; 
};
#endif