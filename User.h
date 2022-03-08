#include <iostream>
#include <vector>
#include "Product.h"

class User{
public:
    User();
    void DisplayMessages(int form_id);
    void DisplayAllMessages();
    void ReceiveMessage(int from_id, string message);
    bool SendMessage(int to_id, string message);
private:
    int user_id_;
    float account_balance_;
    string name_;
    int id_;
    vector<string> received_messages_;
};


class Seller : public User{
public:
    Seller() : User(){}
    void DisplayMenu();
    bool AddProductForSale(Product* for_sale);
    double CheckAccount();
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
    Buyer() : User(){};
    void DisplayMenu();
    void ViewProducts();
    bool PlaceBid(int product_id, float bid);
    bool RateSeller(int seller_id, string message);
    void ViewMyBids();
private:
    vector<int> bid_products_;
};