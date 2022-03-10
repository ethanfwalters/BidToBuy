#include "Store.h"
#include <vector>
#include <iostream>
#include <string>
#include <map>

bool sellerOrBuyer() {
    int userIn;
    cout << "Are you a (0)buyer or (1)seller?\n";
    cin >> userIn;
    return (userIn == 1);
}

// this intakes the seller and sees if they are are already in the data base or not.
Seller& sellerIntake(Store& store) {
    bool isDone = false;
    while(!isDone) {
        int isInSystem;
        cout << "Do you already have an account? (0) no (1) yes." << endl;
        cin >> isInSystem;
        if (isInSystem == 1) {
            int account_num;
            cout << "Please enter your user ID\n";
            cin >> account_num;
            bool isInStore = store.CheckIsUser(account_num);
            if(isInStore){
                // TODO:
                // they are in the store
                // need to return the user
                isDone = true;
            }
            else{
                // not in store
                cout << "----------------------------------------------------------------\n";
                cout << "The user was not found in the store! please create a new account" << endl;
                cout << "----------------------------------------------------------------\n";
            }
        }
        else if (isInSystem == 0) {
            // new user and needs to add them into the system
            string name;
            double account_balance;
            cout << "Please enter your name!" << endl;
            cin >> name;
            cout << "Please enter the amount you want to transfer into your account!\n$";
            cin >> account_balance;
            static Seller s = Seller(name, account_balance);
            store.AddUser(&s);
            isDone = true;
            return s;
        }
        else{
            cout << "Please enter either 0 or 1." << endl;
        }
    }
}

// This is the buyer intake
// I think i could have made these two smaller
Buyer& buyerIntake(Store& store) {
    bool isDone = false;
    while(!isDone) {
        int isInSystem;
        cout << "Do you already have an account? (0) no (1) yes." << endl;
        cin >> isInSystem;
        if (isInSystem == 1) {
            // they say they already have an account
            int account_num;
            cout << "Please enter your user ID\n";
            cin >> account_num;
            bool isInStore = store.CheckIsUser(account_num);
            if(isInStore){
                // TODO:
                // they are in the store
                // need to return the user
                isDone = true;
            }
            else{
                // not in store
                cout << "----------------------------------------------------------------\n";
                cout << "The user was not found in the store! please create a new account" << endl;
                cout << "----------------------------------------------------------------\n";
            }
        }
        else if (isInSystem == 0) {
            // new user and needs to add them into the system
            string name;
            double account_balance;
            cout << "Please enter your name!" << endl;
            cin >> name;
            cout << "Please enter the amount you want to transfer into your account!\n$";
            cin >> account_balance;
            static Buyer b = Buyer(name, account_balance);
            store.AddUser(&b);
            isDone = true;
            return b;
        }
        else{
            cout << "Please enter either 0 or 1." << endl;
        }
    }
}

void AddProduct(Seller &seller, Store &pStore) {
    double min_bid;
    string product_name;
    string product_desc;
    string titles[] = {"Enter the product name\n", "Enter the product description\n:"};
    // i do not know why i need this other getline and it doesnt seem like it is very good practice but it works i think?
    string temp;
    getline(cin, temp);
    cout << titles[0];
    getline(cin, product_name);
    cout << titles[1];
    getline(cin, product_desc);
//    cout << titles[0];
//    cin >> product_name;
//    cout << titles[1];
//    cin >> product_desc;
    cout << "Please enter the min bid price\n$";
    cin >> min_bid;
    //Product nProduct = Product(product_name, product_desc, min_bid);
    Product * newPro = Product::Clone(product_name,product_desc,min_bid);
    pStore.AddProduct(newPro);
    seller.AddProductForSale(newPro);
}

void UpdateInfo(User *u){
    // name, account ballance
    string name;
    double account_bal;
    string temp;
    getline(cin, temp);
    cout << "Your current name is " + u->get_name() + " what would you like to change it to?\n:";
    getline(cin, name);
    cout << "Your current ballance is ";
    cout << u->CheckAccount();
    cout << " what would you like to change it to?\n:";
    cin >> account_bal;
    u->set_name(name);
    u->set_ballance(account_bal);
    cout << "All done, thanks!" << endl;

}

void OpenProduct(Seller &seller){
    int id;
    cout << "What is the id of the product you want to open?\n";
    cin >> id;
    seller.OpenProduct(id);
}

int main(){
    // need to figure out how to add from the csv file

    Store store = Store();
    bool isSeller = sellerOrBuyer();
    if(isSeller){
        // this is if the user is a seller
        Seller &s = sellerIntake(store);
        bool isDone = false;
        // while loop for doing things
        while (!isDone){
            int userChoice;
            s.DisplayMenu();
            cin >> userChoice;
            switch(userChoice){
                case 1:
                    AddProduct(s,store);
                    break;
                case 2:
                    cout << "\n------------------------------------------------\n";
                    cout << "The account balance for " + s.get_name() + " is $";
                    cout << s.CheckAccount() << endl;
                    cout << "\n------------------------------------------------\n";
                    break;
                case 3:
                    cout << "Rate a buyer\n";
                    break;
                case 4:
                    UpdateInfo(&s);
                    break;
                case 5:
                    s.ViewProducts();
                    break;
                case 6:
                    cout << "View Bids\n";
                    break;
                case 7:
                    OpenProduct(s);
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
        Buyer &b = buyerIntake(store);
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
                case 5:
                    cout << "\n------------------------------------------------\n";
                    cout << "The account balance for " + b.get_name() + " is $";
                    cout << b.CheckAccount() << endl;
                    cout << "\n------------------------------------------------\n";
                    break;
                default:
                    cout << "Goodbye!\n";
                    isDone = true;
                    break;
            }
        }
    }
    return 0;
}