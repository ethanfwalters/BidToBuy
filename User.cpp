#include "User.h"
#include <vector>
using namespace std;

//class user

int User::num_users_ = 0;

/**
 * constructor for the users; main one that is always called
 * @param name of the new user
 * @param account_balance of the new user
 */
User::User(string name, double account_balance){
    num_users_++;
    account_balance_ = account_balance;
    name_ = name;
    user_id_ = num_users_;
    rating_ = -1;
}

/**
 * returns the account ballance for the user
 * @return account balance
 */
double User::CheckAccount() {
    return account_balance_;
}

/**
 * sets the rating
 * @param rating
 */
void User::set_rating(int rating) {
    rating_ = rating;
}

// class seller:

/**
 * shows all of the options that the seller can take
 */
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
    cout << "(9) Send a message\n";
    cout << "(10) View messages\n";
    cout << "(11) Exit system\n";
}

/**
 * adds a product to the array of products in the user
 * takes in the new procut that will be added
 * @param for_sale
 */
void Seller::AddProductForSale(Product *for_sale) {
    current_for_sale_.push_back(for_sale);
}

/**
 * opens a product
 * takes in the id of the product trying to be found
 * @param target_product
 * @return if the product was opened or not
 */
bool Seller::OpenProduct(int target_product){
    bool isOpened = false;
    // find the product in the product array
    for(int i = 0; i < current_for_sale_.size(); i++){
        if(current_for_sale_[i]->get_product_id() == target_product){
            current_for_sale_[i]->set_is_closed(false);
            isOpened = true;
        }
    }
    return isOpened;
}

/**
 * closes a product
 * takes in id of the product trying to be found
 * @param target_product
 * @return if the product was found and closed
 */
bool Seller::CloseProduct(int target_product) {
    bool isClosed = false;
    // find product in product array
    for(int i =0; i < current_for_sale_.size(); i++){
        if(current_for_sale_[i]->get_product_id() == target_product){
            current_for_sale_[i]->set_is_closed(true);
            isClosed = true;
        }
    }
    return isClosed;
}

/**
 * goes though and prints out all the products in the array of products
 */
void Seller::ViewProducts() {
    // looping through the array of products in user
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

/**
 * shows the options that the buyer can take
 */
void Buyer::DisplayMenu() {
    cout << "What would you like to do?\n";
    cout << "(1) View products\n";
    cout << "(2) Place a bid!\n";
    cout << "(3) Rate a seller\n";
    cout << "(4) View my Bids\n";
    cout << "(5) Check account\n";
    cout << "(6) Send Message\n";
    cout << "(7) View Message\n";
    cout << "(8) Exit system\n";
}