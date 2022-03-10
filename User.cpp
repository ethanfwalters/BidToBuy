#include "User.h"
#include <vector>
using namespace std;

//class user

int User::num_users_ = 0;

User::User(string name, double account_balance){
    num_users_++;
    account_balance_ = account_balance;
    name_ = name;
    user_id_ = num_users_;
}

double User::CheckAccount() {
    return account_balance_;
}


// class seller:

void Seller::DisplayMenu() {
    cout << "What would you like to do?\n";
    cout << "(1) Add a product for sale\n";
    cout << "(2) Check Account balance\n";
    cout << "(3) Rate a buyer\n";
    cout << "(4) Update user information \n";
    cout << "(5) View Products\n";
    cout << "(6) View Bids\n";
    cout << "(7) Open a new Product\n";
    cout << "(8) Close a product\n";
    cout << "(9) Exit system\n";
}

void Seller::AddProductForSale(Product *for_sale) {
    current_for_sale_.push_back(for_sale);
}

bool Seller::OpenProduct(int target_product){
    bool isOpened = false;
    for(int i = 0; i < current_for_sale_.size(); i++){

    }
}


void Seller::ViewProducts() {
    for(int i = 0; i< current_for_sale_.size();i++){
        cout << "-----------------------------------------\n";
        cout << "Product: " << current_for_sale_[i]->get_product_name() << endl;
        cout << endl;
        cout << "Description: " << current_for_sale_[i]->get_product_desc() << endl;
        cout << endl;
        cout << "Current Price: " << current_for_sale_[i]->get_current_price() << endl;
        cout << endl;
        cout << "Min bid price: " << current_for_sale_[i]->get_min_bid() << endl;
        cout << endl;
        cout << "Is closed: " << boolalpha << current_for_sale_[i]->get_is_closed() << endl;
        cout << endl;
        cout << "Product ID: " << current_for_sale_[i]->get_product_id() << endl;
        cout << "-----------------------------------------\n";
        cout << endl << endl;
    }
}


// class for buyer:

void Buyer::DisplayMenu() {
    cout << "What would you like to do?\n";
    cout << "(1) View products\n";
    cout << "(2) Place a bid!\n";
    cout << "(3) Rate a seller\n";
    cout << "(4) View my Bids\n";
    cout << "(5) Check account\n";
    cout << "(6) Exit system\n";
}