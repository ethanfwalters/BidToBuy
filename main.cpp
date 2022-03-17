#include "Store.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>

/**
 * takes in if they user is a seller or buyer
 * @return true if seller false if buyer
 */
bool sellerOrBuyer() {
    int userIn;
    cout << "Are you a (0)buyer or (1)seller?\n";
    cin >> userIn;
    return (userIn == 1);
}

/**
 * takes in the if the person is a seller.  tells if they are in the store or not
 * @param store the store object that it is working on
 * @return the user that will be working in the system
 */
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
                // sends the seller if they are already in the store
                return reinterpret_cast<Seller &>(store.GetUser(account_num));
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
            // intake new user and needs to add them into the system
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

/**
 * registers if there is a buyer, if not makes a new one.
 * @param store that is being worked on
 * @return addres of the buyer that is interacting with store
 */
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
                // in store, returning the buyer
                return reinterpret_cast<Buyer &>(store.GetUser(account_num));
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

/**
 * this adds a product into the system.  mainly takes in user input, then adds it to the store vector and user vector
 * @param seller the seller that is adding a product
 * @param pStore the store that is being added to
 */
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
    cout << titles[0];
    cin >> product_name;
    cout << titles[1];
    cin >> product_desc;
    cout << "Please enter the min bid price\n$";
    cin >> min_bid;
    Product *newPro = Product::Clone(product_name,product_desc,min_bid,seller.get_user_id());
    pStore.AddProduct(newPro);
    seller.AddProductForSale(newPro);
}

/**
 * takes in the user, and updated the info that needs to be updated
 * @param u user that is updating
 */
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

/**
 * opens the product
 * @param seller that has the product
 */
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

/**
 * closes a product
 * @param seller that has the product
 */
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

/**
 * imports seller from the CSV
 * csv file needs to be in the format:  name,account ballance
 * @param store that sellers are being added to
 */
void SellerFromCSV(Store &store){
    fstream fin;
    fin.open("sellers.csv", ios::in);
    string temp = "";
    while(getline(fin, temp)){
        string name;
        double acc_bal;
        string tempstring;
        stringstream inputString(temp);
        getline(inputString, name, ',');

        getline(inputString, tempstring, ',');
        acc_bal = atof(tempstring.c_str());
        store.AddUser(Seller::Clone(name, acc_bal));
        temp = "";
    }
}

/**
 * imports the buyers to the store
 * csv file needs to be in the format: name,account ballance
 * @param store that the buyers are being added to
 */
void BuyerFromCSV(Store &store){
    fstream fin;
    fin.open("buyer.csv", ios::in);
    string temp = "";
    while(getline(fin, temp)){
        string name;
        double acc_bal;
        string tempstring;
        stringstream inputString(temp);
        getline(inputString, name, ',');

        getline(inputString, tempstring, ',');
        acc_bal = atof(tempstring.c_str());
        store.AddUser(Buyer::Clone(name, acc_bal));
        temp = "";
    }
}

/**
 * adding the products to the store
 * csv file needs to be in format: name,description,minimum price,user id that owns the product(int)
 * @param store that the products are being added to
 */
void ProductFromCSV(Store &store){
    fstream fin;
    fin.open("product.csv", ios::in);
    string temp = "";
    while(getline(fin, temp)){
        string name;
        string description;
        double min_price;
        int user_id;
        string temp_min_price;
        string temp_user_id;
        stringstream inputString(temp);
        //cout << "temp: " << temp << endl;
        getline(inputString, name, ',');
        getline(inputString, description, ',');
        getline(inputString, temp_min_price, ',');
        getline(inputString, temp_user_id, ',');
        min_price = atof(temp_min_price.c_str());
        user_id = atoi(temp_user_id.c_str());
        //need to add to store and to the seller's vectors
        Product *newPro = Product::Clone(name, description, min_price, user_id);
        Seller & seller_from_file = reinterpret_cast<Seller &> (store.GetUser(user_id));
        cout << seller_from_file.get_name() << endl;
        store.AddProduct(newPro);
        seller_from_file.AddProductForSale(newPro);
        temp = "";
    }
}

/**
 * adding the messages to the store
 * csv file needs to be in format: message,user id to,user id from
 * @param store
 */
void MessagesFromCSV(Store &store){
    fstream fin;
    fin.open("messages.csv", ios::in);
    string temp = "";
    while(getline(fin, temp)){
        string message;
        int user_to;
        int user_from;
        string temp_user_to;
        string temp_user_from;
        stringstream inputString(temp);
        getline(inputString, message, ',');
        getline(inputString, temp_user_to, ',');
        getline(inputString, temp_user_from, ',');
        user_to = atoi(temp_user_to.c_str());
        user_from = atoi(temp_user_from.c_str());
        Messages m = Messages(user_to, user_from, message);
        store.AddMessage(m);
        temp = "";
    }
}

int main(){
    // need to figure out how to add from the csv file
    Store store = Store();
    SellerFromCSV(store);
    BuyerFromCSV(store);
    ProductFromCSV(store);
    MessagesFromCSV(store);
    store.ViewUsers();
    bool isSeller = sellerOrBuyer();
    if(isSeller){
        // this is if the user is a seller
        Seller &s = sellerIntake(store);
        bool isDone = false;
        // while loop for doing things
        while (!isDone){
            int userChoice;
            s.DisplayMenu();
            cout << ":";
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
                case 9:
                    store.SendMessage(s);
                    break;
                case 10:
                    store.ViewMessages(s);
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
            cout << ":";
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
                case 6:
                    store.SendMessage(b);
                    break;
                case 7:
                    store.ViewMessages(b);
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