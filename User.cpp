#include "User.h"
using namespace std;

//class user
User::User(){

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


// class for buyer:

void Buyer::DisplayMenu() {
    cout << "What would you like to do?\n";
    cout << "(1) View products\n";
    cout << "(2) Place a bid!\n";
    cout << "(3) Rate a seller\n";
    cout << "(4) View my Bids\n";
    cout << "(5) Exit system\n";
}