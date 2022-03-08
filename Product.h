using namespace std;
#include <vector>
#include <iostream>

class Product{
public:
    Product(string name, string desc);
    static Product* CreateProduct(string name, string desc);
    Product* Clone();
private:
    string product_name_;
    int product_id_;
    string product_description_;
};