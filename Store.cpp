#include <vector>
#include "Store.h"

int Store::AddUser(User *new_user) {
    users_.insert({new_user->get_user_id(), new_user});
    return new_user->get_user_id();
}

bool Store::CheckIsUser(int id) {
    if(users_.find(id) == users_.end()){
        return false;
    }
    else{
        return true;
    }
}

Store::Store(){

}