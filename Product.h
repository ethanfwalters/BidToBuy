using namespace std;
#include <vector>
#include <iostream>

class Product{
public:
    Product(string name, string desc, double min_price, int user_id);
    int get_product_id(){return product_id_;};
    string get_product_name(){return product_name_;};
    string get_product_desc(){return product_description_;};
    double get_current_price(){return current_price_;};
    void set_current_price(double price){current_price_ = price;};
    double get_min_bid(){return min_bid_;};
    bool get_is_closed(){return is_closed_;};
    int get_user_id(){return user_id_;};
    void set_is_closed(bool is_closed){is_closed_ = is_closed;};
    static Product* Clone(string name, string desc, double min_price, int user_id){return new Product(name, desc, min_price, user_id);};
    static int num_Products;
private:
    int user_id_;
    string product_name_;
    int product_id_;
    string product_description_;
    double current_price_;
    double min_bid_;
    bool is_closed_;
};