#include <iostream>
#include <vector>
#include "Product.h"

class User{
public:
    User(string name, double account_balance);
    void DisplayMessages(int form_id);
    void DisplayAllMessages();
    void ReceiveMessage(int from_id, string message);
    bool SendMessage(int to_id, string message);
    double CheckAccount();
    int get_user_id(){return user_id_;};
    string get_name(){return name_;};
private:
    int user_id_;
    double account_balance_;
    string name_;
    int id_;
    vector<string> received_messages_;
    static int num_users_;
};


class Seller : public User{
public:
    Seller(string name, double account_balance) : User(name, account_balance){};
    void DisplayMenu();
    bool AddProductForSale(Product* for_sale);
    bool RateBuyer(int buyer_id, int rating, string message);
    void UpdateUserInfo(Seller s);
    void ViewProducts();
    void ViewBids(Product on);
    bool OpenProduct(int target_product);
    bool CloseProduct(int target_product);
private:
    vector<int> current_for_sale_;
};

class Buyer : public User{
public:
    Buyer(string name, double account_balance) : User(name, account_balance){};
    void DisplayMenu();
    void ViewProducts();
    bool PlaceBid(int product_id, float bid);
    bool RateSeller(int seller_id, string message);
    void ViewMyBids();
private:
    vector<int> bid_products_;
};