#include "process.h"

int main(){
    space_counter();
    root = load_data_from_file(root);
    cleaning_remaining_data();
    user_sector();
    return 0;
}

//to add account lv and tran limit
