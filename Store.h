#include <iostream>
#include "User.h"
#include <vector>
#include <map>

struct Bid{
    Bid(double amount, Product * product, Buyer &buyer, User * seller) : buyer_(buyer){
        amount_ = amount;
        product_ = product;
        product_ = product;
        seller_ = seller;
    }
    double amount_;
    Product * product_;
    User & buyer_;
    User * seller_;
};

struct Messages{
    Messages(int to_id, int from_id, string message){
        to_id_ = to_id;
        from_id_ = from_id;
        message_ = message;
    }
    int to_id_;
    int from_id_;
    string message_;
};



class Store{
public:
    Store();
    int AddUser(User* new_user);
    void RemoveUser(int user_id);
    void MessageUser(int from_id, int to_id, string message);
    void RateUser(int from_id, int to_id, string message);
    void AddProduct(Product *new_product);
    void OpenProduct(int product_id);
    void closeProduct(int product_id);
    Product* GetProduct(int product_id);
    void RemoveProduct(int product_id);
    void PrintProducts();
    void ViewBidsSeller(User &u);
    void ViewBidsBuyer(User &u);
    void ViewUsers();
    void RateUser(User * u);
    map<pair<int, string>,string> ProductTable;
    map<int, float> BidTableProduct(int product_id);
    void PlaceBid(Buyer &buyer);
    bool CheckIsUser(int id);
    void SendMessage(User & from);
    void ViewMessages(User & from);
    void AddMessage(Messages m);
//    Buyer& GetBuyer(int id);
//    User GetSeller(int id);
    User& GetUser(int id);
private:
    vector<Bid> bids_;
    vector<Messages> messages_;
    map<int, User*> users_;
    map<int, Product*> products_;
    map<int, map<string,int>> ratings_;
    map<int, pair<int, float>> final_bids_;
    unsigned int next_id_;
};