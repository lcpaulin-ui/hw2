#include "mydatastore.h"
#include <sstream>
#include <iomanip>
#include <cctype>
#include <algorithm>
using namespace std;

MyDataStore::MyDataStore() {

}

MyDataStore::~MyDataStore() {

}

void MyDataStore::addProduct(Product *p){
    products_.insert(p);
    std::set<std::string> keys = p->keywords();
    std::set<std::string>::iterator it = keys.begin(); 
    

    for ( ; it != keys.end(); ++it) {
        index[*it].insert(p);
    }  
}

/**
 * Adds a user to the data store
 */
void MyDataStore::addUser(User* u){
    std::vector<Product*> prods; 
    std::string uname = convToLower(u->getName()); 
    carts_[uname] = prods;
    uname_match[uname] = u; 
}

/**
 * Performs a search of products whose keywords match the given "terms"
 *  type 0 = AND search (intersection of results for each term) while
 *  type 1 = OR search (union of results for each term)
 */

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){

    std::vector<Product*> match;
    std::set<Product*> result;
    std::set<Product*> adding;

    // find 'base' or first one and go from there 
    if (terms.empty()){
        //return; 
    }

    std::vector<std::string>:: iterator x; 
    std::map<std::string, std::set<Product*>>::iterator it; 

    x = terms.begin(); 
    it = index.find(*x); 

    if (it == index.end() && type == 0){
        return match; 
    }

    // else, i found a match.
    result = it->second; 

    // now, just do the set union and / or intersection until the end of the terms
    ++x; 
    
    for ( ; x != terms.end(); ++x) {
        it = index.find(*x); 
        if (it != index.end()){
            
            adding = it->second; 
            if(type == 1){
                result = setIntersection(result, adding); 
            }
            else if (type == 2){
                result = setUnion(result, adding); 
            }



        }
    }

    std::set<Product*>::iterator res = result.begin(); {
        match.push_back(*res); 
    }

    return match; 

}

/**
 * Reproduce the database file from the current Products and User values
 */
void MyDataStore::dump(std::ostream& ofile) {

    ofile << "<products>" << std::endl;
    std::set<Product*>:: iterator it = products_.begin(); 
    for ( ; it != products_.end(); ++it){
        (*it)->dump(ofile); 
    }

    ofile << "</products>" << std::endl;


    ofile << "<users>" << std::endl;
    std::set<User*>:: iterator y = users_.begin(); 
    for ( ; y != users_.end(); ++y){
        (*y)->dump(ofile); 
    }

    ofile << "</users>" << std::endl;

}

void MyDataStore::add_to_cart(std::string uname, Product* p) {
    carts_[uname].push_back(p); 
}

std::vector<Product*> MyDataStore::getCart(std::string uname){
    std::map<std::string, std::vector<Product*>>::iterator it = carts_.begin(); 
    std::vector<Product*> prods; 
    it = carts_.find(uname); 
    if (it != carts_.end()){
        prods = it->second; 
    }
    return prods; 
}

User* MyDataStore::getUser(std::string uname){
    std::map<std::string, User*>::iterator it = uname_match.begin(); 
    User* usr = nullptr; 
    it = uname_match.find(uname); 
    if (it != uname_match.end()){
        usr = it->second; 
    }
    return usr; 
}
