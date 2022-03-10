using namespace std;
#include <vector>
#include <iostream>

class Product{
public:
    Product(string name, string desc, double min_price);
    static Product* CreateProduct(string name, string desc);
    Product* Clone();
    int get_product_id(){return product_id_;};
    string get_product_name(){return product_name_;};
    string get_product_desc(){return product_description_;};
    double get_current_price(){return current_price_;};
    double get_min_bid(){return min_bid_;};
    bool get_is_closed(){return is_closed_;};
    void set_is_closed(bool is_closed){is_closed_ = is_closed;};
    static Product* Clone(string name, string desc, double min_price){return new Product(name, desc, min_price);};
    static int num_Products;
private:
    string product_name_;
    int product_id_;
    string product_description_;
    double current_price_;
    double min_bid_;
    bool is_closed_;
};