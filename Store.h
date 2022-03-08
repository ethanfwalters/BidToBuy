using namespace std;
#include <iostream>
#include "User.h"
#include <vector>
#include <map>

class Store{
public:
    static Store& GetInstance();
    int AddUser(User* new_user);
    void RemoveUser(int user_id);
    void MessageUser(int from_id, int to_id, string message);
    void RateUser(int from_id, int to_id, string message);
    int AddProduct(Product* new_product);
    void OpenProduct(int product_id);
    void closeProduct(int product_id);
    Product* GetProduct(int product_id);
    void RemoveProduct(int product_id);
    map<pair<int, string>,string> ProductTable;
    map<int, float> BidTableProduct(int product_id);
    void PlaceBid(int product_id, int user_id, float price);
private:
    Store();
    map<int, User*> users_;
    map<int, Product*> products_;
    map<int, map<string,int>> ratings_;
    map<int, pair<int, float>> final_bids_;
    unsigned int next_id_;
};