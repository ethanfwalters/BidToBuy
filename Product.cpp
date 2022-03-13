using namespace std;
#include "Product.h"

int Product::num_Products = 0;

Product::Product(string name, string desc, double min_price, int user_id) {
    num_Products++;
    product_name_ = name;
    product_description_ = desc;
    min_bid_ = min_price;
    current_price_ = 0.0;
    product_id_ = num_Products;
    is_closed_ = false;
    user_id_ = user_id;
}
