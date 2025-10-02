#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <map> 
#include <set>
#include <vector>
#include "product.h"
#include "user.h"
#include "util.h"
#include "datastore.h"

class MyDataStore : public DataStore 
{
    public: 
        MyDataStore(); 
        ~MyDataStore();
        void addProduct(Product* p); 
        void addUser(User* u);
        User* getUser(std::string uname); 
        std::vector<Product*> search(std::vector<std::string>& terms, int type);
        void dump(std::ostream& ofile);
        void add_to_cart(std::string uname, Product* p); 
        std::vector<Product*> getCart(std::string uname); 

    private: 
    std::set<User*> users_;
    std::map <std::string, User*> uname_match; 
    std::set<Product*> products_;
    std::map<std::string, std::set<Product*>> index; 
    std::map<std::string, std::vector<Product*>> carts_; 
    std::vector<Product*> hits; 

};
#endif