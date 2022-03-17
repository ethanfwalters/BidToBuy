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
    void UpdateUserInfo();
    double CheckAccount();
    int get_user_id(){return user_id_;};
    string get_name(){return name_;};
    void set_name(string name){name_ = name;};
    void set_ballance(double bal){account_balance_ = bal;};
    void set_rating(int rating);
    int get_rating(){return rating_;};
private:
    int user_id_;
    double account_balance_;
    string name_;
    vector<string> received_messages_;
    static int num_users_;
    int rating_;
};


class Seller : public User{
public:
    Seller(string name, double account_balance) : User(name, account_balance){};
    void DisplayMenu();
    void AddProductForSale(Product* for_sale);
    bool RateBuyer(int buyer_id, int rating);
    void ViewProducts();
    void ViewBids(Product on);
    bool OpenProduct(int target_product);
    bool CloseProduct(int target_product);
    static Seller* Clone(string name, double acc_bal){return new Seller(name,acc_bal);};
private:
    vector<Product*> current_for_sale_;
};

class Buyer : public User{
public:
    Buyer(string name, double account_balance) : User(name, account_balance){};
    void DisplayMenu();
    void ViewProducts();
    bool PlaceBid(int product_id, float bid);
    bool RateSeller(int seller_id, string message);
    void ViewMyBids();
    static Buyer* Clone(string name, double acc_bal){return new Buyer(name,acc_bal);};
private:
    vector<int> bid_products_;
};