#include "Store.h"
#include <vector>
#include <iostream>
#include <fstream>
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
    Product *newPro = Product::Clone(product_name,product_desc,min_bid,seller.get_user_id());
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
    cout << "What is the id of the product you want to open?\n:";
    cin >> id;
    bool opened = seller.OpenProduct(id);
    if(opened){
        cout << "You successfully opened the product!" << endl;
    }
    else{
        cout << "The product was not found!\n";
    }

}

void CloseProduct(Seller &seller){
    int id;
    cout << "What is the id of the product you want to close?\n:";
    cin >> id;
    bool closed = seller.CloseProduct(id);
    if(closed){
        cout << "------------------------------------" << endl;
        cout << "You successfully closed the product!" << endl;
        cout << "------------------------------------" << endl;
    }
    else{
        cout << "--------------------------" << endl;
        cout << "The product was not found!\n";
        cout << "--------------------------" << endl;
    }
}

//void SellerFromCSV(Store &store){
//    fstream fin;
//    fin.open("sellers.csv", ios::in);
//
//
//}

int main(){
    // need to figure out how to add from the csv file

    Store store = Store();
    //SellerFromCSV(&store);
    bool isSeller = sellerOrBuyer();
    if(isSeller){
        // this is if the user is a seller
        Seller &s = sellerIntake(store);
        // TODO: adding things for the buyer testing
        Product toy = Product("toy", "very fun toy", 3, s.get_user_id());
        Product leaf = Product("leaf", "super green", 1.5, s.get_user_id());
        Product bottle = Product("waterbottle", "so thurst", 9.99, s.get_user_id());
        s.AddProductForSale(&toy);
        store.AddProduct(&toy);
        s.AddProductForSale(&leaf);
        store.AddProduct(&leaf);
        s.AddProductForSale(&bottle);
        store.AddProduct(&bottle);
        Buyer b = Buyer("dick", 900);
        store.AddUser(&b);
        store.PrintProducts();
        store.PlaceBid(b);
        // TODO: end the testing
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
                    store.ViewUsers();
                    store.RateUser(&s);
                    break;
                case 4:
                    UpdateInfo(&s);
                    break;
                case 5:
                    s.ViewProducts();
                    break;
                case 6:
                    store.ViewBidsSeller(s);
                    break;
                case 7:
                    OpenProduct(s);
                    break;
                case 8:
                    CloseProduct(s);
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
        // TODO: this is for testing and should be deleted.
        Seller s = Seller("dave", 96.0);
        store.AddUser(&s);
        Product toy = Product("toy", "very fun toy", 3, s.get_user_id());
        Product leaf = Product("leaf", "super green", 1.5, s.get_user_id());
        Product bottle = Product("waterbottle", "so thurst", 9.99, s.get_user_id());
        s.AddProductForSale(&toy);
        store.AddProduct(&toy);
        s.AddProductForSale(&leaf);
        store.AddProduct(&leaf);
        s.AddProductForSale(&bottle);
        store.AddProduct(&bottle);
        //s.ViewProducts();
        //store.PlaceBid(b);
        // TODO: end the deleted things
        while (!isDone){
            int userChoice;
            b.DisplayMenu();
            cin >> userChoice;
            switch(userChoice){
                case 1:
                    store.PrintProducts();
                    break;
                case 2:
                    store.PlaceBid(b);
                    break;
                case 3:
                    store.ViewUsers();
                    store.RateUser(&b);
                    break;
                case 4:
                    store.ViewBidsBuyer(b);
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