#include <vector>
#include "Store.h"

int Store::AddUser(User *new_user) {
    users_.insert({new_user->get_user_id(), new_user});
    return new_user->get_user_id();
}

void Store::AddProduct(Product *new_product) {
    products_.insert({new_product->get_product_id(), new_product});
}

bool Store::CheckIsUser(int id) {
    if(users_.find(id) == users_.end()){
        return false;
    }
    else{
        return true;
    }
}

void Store::PrintProducts() {
    auto itter = products_.begin();
    while(itter != products_.end()){
        Product *temp = itter->second;
        cout << "-----------------------------------------\n";
        cout << "Product: " << temp->get_product_name() << endl;
        cout << endl;
        cout << "Description: " << temp->get_product_desc() << endl;
        cout << endl;
        cout << "Current Price: " << temp->get_current_price() << endl;
        cout << endl;
        cout << "Min bid price: " << temp->get_min_bid() << endl;
        cout << endl;
        cout << "Is closed: " << boolalpha << temp->get_is_closed() << endl;
        cout << endl;
        cout << "Product ID: " << temp->get_product_id() << endl;
        cout << "-----------------------------------------\n";
        cout << endl << endl;

        ++itter;
    }
}

void Store::PlaceBid(Buyer &buyer) {
    int product_id;
    double bid_amount;
    cout << "What is the id of the product you would like to buy?\n";
    cin >> product_id;
    cout << "What is the amount you would like to bid?\n$";
    cin >> bid_amount;

    map<int, Product*>::iterator it = products_.find(product_id);
    if(it != products_.end()){
        Product * temp = it->second;
        if(temp->get_min_bid() < bid_amount){
            if(buyer.CheckAccount() > bid_amount){
                temp->set_current_price(bid_amount);
                cout << "You bid has been registered!" << endl;
                buyer.set_ballance((buyer.CheckAccount() - bid_amount));
                int user_id = temp->get_user_id();
                map<int, User*>::iterator found = users_.find(user_id);
                Bid b = Bid(bid_amount,temp,buyer, found->second);
                bids_.push_back(b);
            }
            else{
                cout << "You do not have sufficent funds to place that bid." << endl;
            }
        }
        else{
            cout << "The amount that you entered is the less then the min bid." << endl;
        }
    }
    else{
        cout << "The product id you entered is incorrect." << endl;
    }
}

void Store::ViewBidsSeller(User &u) {
    bool isIn = false;
    for(int i = 0; i< bids_.size(); i++){
        User * seller = bids_[i].seller_;
        int id = seller->get_user_id();
        if(u.get_user_id() == id){
            isIn = true;
            cout << "---------------------------" << endl;
            cout << "Buyer: " + bids_[i].buyer_.get_name() << endl;
            cout << "Product: " + bids_[i].product_->get_product_name() << endl;
            cout << "Bid Amount: $";
            cout << bids_[i].amount_ << endl;
            cout << "---------------------------" << endl;
            cout << endl;
        }
    }

    if(!isIn){
        cout << "There is no bids for you at  this time.\n";
    }

}

void Store::ViewBidsBuyer(User &u) {
    bool isIn = false;
    for(int i = 0; i< bids_.size(); i++){
        User & buyer = bids_[i].buyer_;
        int id = buyer.get_user_id();
        if(u.get_user_id() == id){
            isIn = true;
            cout << "---------------------------" << endl;
            cout << "Seller: " + bids_[i].seller_->get_name() << endl;
            cout << "Product: " + bids_[i].product_->get_product_name() << endl;
            cout << "Bid Amount: $";
            cout << bids_[i].amount_ << endl;
            cout << "---------------------------" << endl;
            cout << endl;
        }
    }
    if(!isIn){
        cout << "There is no bids for you at  this time.\n";
    }
}

void Store::ViewUsers() {
    auto itter = users_.begin();
    while(itter != users_.end()){
        cout << "-------------------" << endl;
        cout << "User Id: " << itter->first << endl;
        cout << "User's name: " << itter->second->get_name() << endl;
        cout << "User's rating: " << itter->second->get_rating() << endl;
        cout << "--------------------" << endl;
        ++itter;
    }
}

void Store::RateUser(User *u) {
    int user_id;
    cout << "what is the user ID of the person you want to rate" << endl;
    cin >> user_id;
    map<int,User*>::iterator it = users_.find(user_id);
    if(it != users_.end()){
        int rating;
        cout << "What is your rating (1-5)" << endl;
        cin >> rating;
        it->second->set_rating(rating);
    }
    else{
        cout << "That user id does not exist in our system" << endl;
    }
}

Store::Store(){
}