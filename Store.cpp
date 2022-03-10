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

Store::Store(){
}