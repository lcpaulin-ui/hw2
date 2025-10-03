#include "mydatastore.h"
#include <sstream>
#include <iomanip>
#include <cctype>
#include <algorithm>
using namespace std;

MyDataStore::MyDataStore() {

}

// std::set<User*> users_;
// std::map <std::string, User*> uname_match; 
// std::set<Product*> products_;
// std::map<std::string, std::set<Product*>> index; 
// std::map<std::string, std::vector<Product*>> carts_; 
// std::vector<Product*> hits; 
MyDataStore::~MyDataStore() {
    // avoiding memory errors: db parser is allocating memory so i have to make sure to delete it
    // i can't delete it twice so, grab one of the vectors that points to allocated memory and then delete that

    std::set<Product*>::iterator prod = products_.begin();
    for ( ; prod != products_.end(); ++prod) {
        delete *prod; 
    }


    products_.clear(); // making size 0 to make sure i'm donw w everytjing

    std::map <std::string, User*>::iterator it = uname_match.begin();
    for ( ; it != uname_match.end(); ++it) {
        delete it->second; // i can do this bc i'm not deleting member, i'm deleting what it points to
    }
    users_.clear(); // now i am deleting everything
    uname_match.clear();  

}

void MyDataStore::addProduct(Product *p){
    products_.insert(p);
    std::set<std::string> keys = p->keywords();

    std::set<std::string>::iterator it = keys.begin(); 
    

    for ( ; it != keys.end(); ++it) {
        index[convToLower(*it)].insert(p); // making case insensitive work 
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
    users_.insert(u);  
}

/**
 * Performs a search of products whose keywords match the given "terms"
 *  type 0 = AND search (intersection of results for each term) while
 *  type 1 = OR search (union of results for each term)
 */

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){

    //std::vector<Product*> match;
    std::set<Product*> result;
    std::set<Product*> adding;

    // find 'base' or first one and go from there 
    if (terms.empty() ){
        return {}; 
    }

    std::vector<std::string>:: iterator x; 
    std::map<std::string, std::set<Product*>>::iterator it; 

    x = terms.begin(); 
    it = index.find(*x); 
    std::string word = convToLower(terms[0]); // if it's an and search and this product isnt in it, will automatically return empty vec
    if (index.find(word) != index.end() ){
        result = index[word]; // 
    }
   

    // now, just do the set union and / or intersection until the end of the terms
    // int cnt = 0;
    // if (type ==1){cnt = 1;}
    // else {cnt = 0;}
    for (size_t i = 1; i < terms.size(); i++){
        word = convToLower(terms[i]); // case insensitive 

        adding.clear(); // i have to do this bc then if not the "and" will not work, if i dont find it i add empty vec
        if (index.find(word) != index.end()){
            adding = index[word]; }

            if (type == 0){ //and , intersection
                result = setIntersection(result, adding); 
            }
            else if (type == 1){ // or , union 
                result = setUnion(result, adding); 
            }
    }
    std::vector<Product*> match(result.begin(), result.end()); // matching reutrn type  

    
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

std::vector<Product*>& MyDataStore::getCart(std::string uname){
  
    // if (it != carts_.end()){
    //     prods = it->second; 
    // }
    // return prods; 
    uname = convToLower(uname);
    return carts_[uname];  
}

User* MyDataStore::getUser(std::string uname){
    std::map<std::string, User*>::iterator it = uname_match.begin(); 
    User* usr = nullptr; // i will check for null if unvalid user name, since i cant send exception
    it = uname_match.find(uname); 
    if (it != uname_match.end()){
        usr = it->second; 
    }
    return usr; 
}
