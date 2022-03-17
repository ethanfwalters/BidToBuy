#include <vector>
#include "Store.h"

/**
 * addes a new user to the private users map
 * @param new_user (user that will be added)
 * @return (the user id of the new user)
 */
int Store::AddUser(User *new_user) {
    users_.insert({new_user->get_user_id(), new_user});
    return new_user->get_user_id();
}

/**
 * adds a product to the product private vector of products
 * @param new_product (the pointer to the new product)
 */
void Store::AddProduct(Product *new_product) {
    products_.insert({new_product->get_product_id(), new_product});
}

/**
 * checks if the user is in the map of users
 * @param id (id of the user trying to be found)
 * @return (if the user is found or not)
 */
bool Store::CheckIsUser(int id) {
    if(users_.find(id) == users_.end()){
        return false;
    }
    else{
        return true;
    }
}

/**
 * prints the products in the product map
 */
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

/**
 * addes a bid to the bid vector
 * @param buyer (the user placing the bid)
 */
void Store::PlaceBid(Buyer &buyer) {
    // takes in the new bid
    int product_id;
    double bid_amount;
    cout << "What is the id of the product you would like to buy?\n";
    cin >> product_id;
    cout << "What is the amount you would like to bid?\n$";
    cin >> bid_amount;

    //finding the product in the map
    map<int, Product*>::iterator it = products_.find(product_id);
    if(it != products_.end()){
        // if the product is in the map
        Product * temp = it->second;
        //gets the pointer
        if(temp->get_min_bid() < bid_amount){
            // if the bid is high enough
            if(buyer.CheckAccount() > bid_amount){
                //if the buyer has enough money to place the bid
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

/**
 * allows the seller to view the bids
 * @param u (user that is viewing the bids)
 */
void Store::ViewBidsSeller(User &u) {
    bool isIn = false;
    for(int i = 0; i< bids_.size(); i++){
        // looking though the bids vector
        User * seller = bids_[i].seller_;
        // grabs the seller for the bid
        int id = seller->get_user_id();
        if(u.get_user_id() == id){
            // out puts the bid if user's id is equal to id of bid
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

/**
 * views the bids that the buyer has place
 * @param u (the buyer that is trying to view)
 */
void Store::ViewBidsBuyer(User &u) {
    bool isIn = false;
    for(int i = 0; i< bids_.size(); i++){
        User & buyer = bids_[i].buyer_;
        int id = buyer.get_user_id();
        if(u.get_user_id() == id){
            // out puts the bid if user's id is equal to id of bid
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

/**
 * views all of the users in the store.
 */
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

/**
 * takes in the info for the user to rate a person
 * @param u (user that is rating)
 */
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

/**
 * gets a user by thier user id
 * @param id (id of the user trying to get)
 * @return (the addres of the user that is found)
 */
User & Store::GetUser(int id) {
    map<int, User*>::iterator it = users_.find(id);
    return *(it->second);
}


/**
 * takes in message and user id from user and sens message
 * @param from (pointer to the user that is sending the message)
 */
void Store::SendMessage(User &from) {
    string temp, mess;
    getline(cin, temp);
    cout << "What is the message you would like to send?" << endl;
    getline(cin, mess);
    int message_to;
    cout << "What is the id of the person you want to message?" << endl;
    cin >> message_to;
    Messages m = Messages(message_to, from.get_user_id(), mess);
    messages_.push_back(m);
}


/**
 * views the messages for the user that is input; checks both recived messages and sent messages
 * @param from (the user that is checking thier messages
 */
void Store::ViewMessages(User &from) {
    cout << "Received messages:" << endl;
    bool isReceivedMess = false;
    for(int i =0;i<messages_.size(); i++){
        if(messages_[i].to_id_ == from.get_user_id()){
            isReceivedMess = true;
            cout << "-------------------------------------" << endl;
            cout << "User id from: " << messages_[i].from_id_ << endl;
            cout << "Message: " << messages_[i].message_ << endl;
            cout << "-------------------------------------" << endl;
            cout << endl;
        }
    }
    if(!isReceivedMess){
        cout << "---------------------" << endl;
        cout << "No received messages!" << endl;
        cout << "---------------------" << endl;
    }
    cout << "Sent messages: " << endl;
    bool isSentMess = false;
    for(int i = 0; i < messages_.size(); i++){
        if(messages_[i].from_id_ == from.get_user_id()){
            isSentMess = true;
            cout << "-------------------------------------" << endl;
            cout << "User id to: " << messages_[i].to_id_ << endl;
            cout << "Message: " << messages_[i].message_ << endl;
            cout << "-------------------------------------" << endl;
            cout << endl;
        }
    }
    if(!isSentMess){
        cout << "-----------------" << endl;
        cout << "No sent messages!" << endl;
        cout << "-----------------" << endl;
    }
}

/**
 * adds a messages, only used by the MessagesFromCSV function
 * @param m
 */
void Store::AddMessage(Messages m) {
    messages_.push_back(m);
}

/**
 * constructor for the store
 */
Store::Store(){
}