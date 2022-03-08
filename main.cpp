#include "Store.h"
#include <vector>
#include <map>

bool sellerOrBuyer() {
    int userIn;
    cout << "Are you a (0)buyer or (1)seller?\n";
    cin >> userIn;
    return (userIn == 1);
}

int main(){
    // need to figure out how to add from the csv file
    // need to instantiate the store object
    bool isSeller = sellerOrBuyer();
    if(isSeller == true){
        // this is if the user is a seller
        Seller s;
        bool isDone = false;
        // while loop for doing things
        while (!isDone){
            int userChoice;
            s.DisplayMenu();
            cin >> userChoice;
            switch(userChoice){
                case 1:
                    cout << "Add a product for sale\n";
                    break;
                case 2:
                    cout << "Check Account balance\n";
                    break;
                case 3:
                    cout << "Rate a buyer\n";
                    break;
                case 4:
                    cout << "Update user information \n";
                    break;
                case 5:
                    cout << "View Products\n";
                    break;
                case 6:
                    cout << "View Bids\n";
                    break;
                case 7:
                    cout << "Open a new Product\n";
                    break;
                case 8:
                    cout << "Close a product\n";
                    break;
                default:
                    cout << "Goodbye!\n";
                    isDone = true;
                    break;
            }
        }
    }
    else{
        // this is if the user is a buyer
        Buyer b;
        bool isDone = false;
        // while loop for doing things
        while (!isDone){
            int userChoice;
            b.DisplayMenu();
            cin >> userChoice;
            switch(userChoice){
                case 1:
                    cout << "View Products\n";
                    break;
                case 2:
                    cout << "Place a bid\n";
                    break;
                case 3:
                    cout << "Rate a seller\n";
                    break;
                case 4:
                    cout << "View my Bids \n";
                    break;
                default:
                    cout << "Goodbye!\n";
                    isDone = true;
                    break;
            }
        }
    }
}