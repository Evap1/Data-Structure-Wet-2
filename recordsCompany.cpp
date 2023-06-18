//
// Created by Eva Poluliakhov on 16/06/2023.
//

#include "recordsCompany.h"

StatusType RecordsCompany::addCostumer(int c_id, int phone){
    if (c_id < 0 || phone < 0){
        return StatusType::INVALID_INPUT;
    }

    if (customers.find(c_id) != NULL){
        return StatusType::ALREADY_EXISTS;
    }

    Customer* toAdd = new Customer(c_id, phone);
    return customers.insert(toAdd);
}

Output_t<int> RecordsCompany::getPhone(int c_id){
    if (c_id < 0 ){
        return StatusType::INVALID_INPUT;
    }

    auto customer = customers.find(c_id);
    if (customer == NULL){
        return StatusType::DOESNT_EXISTS;
    }

    auto temp = Output_t<int>(customer->get_phone());
    return temp;
}

StatusType RecordsCompany::makeMember(int c_id){
    if (c_id < 0){
        return StatusType::INVALID_INPUT;
    }

    auto customer = customers.find(c_id);
    if (customer == NULL){
        return StatusType::DOESNT_EXISTS;
    }
    if (customer->get_isMember()){
        return StatusType ::ALREADY_EXISTS;
    }

    clubMembers.insert(customer);
}

Output_t<bool> RecordsCompany::isMember(int c_id){
    if (c_id < 0){
        return StatusType::INVALID_INPUT;
    }

    auto customer = customers.find(c_id);
    if (customer == NULL){
        return StatusType::DOESNT_EXISTS;
    }

    bool isMember = customer->get_isMember();
    auto temp = Output_t<bool>(isMember);
    return temp;
}

StatusType RecordsCompany::buyRecord(int c_id, int r_id){
    if (c_id < 0 || r_id < 0){
        return StatusType::INVALID_INPUT;
    }

    auto customer = customers.find(c_id);
    if (customer == NULL || r_id > records.get_elements()){
        return StatusType::DOESNT_EXISTS;
    }

    auto record = records.find(r_id);
    // if the customer is a club member
    if (customer->get_isMember()){
        int expense = BASE_EXPENSE + record->get_purchases();
        customer->update_expense(expense);
    }
    record->raise_purchases(1);
    return StatusType::SUCCESS;
}

void RecordsCompany::addAux(int c_id, double amount, Customer* v){

    if (v == NULL) return NULL;

    if (v->get_id() == c_id){
        return v;
    }
    else if (v->get_id() < c_id){
        return addAux(v->get, value);
    }
    else{
        return addAux(v->left, value);
    }
}



StatusType RecordsCompany::addPrize(int c_id1, int c_id2, double  amount){
    auto rootMembers = clubMembers.get_root();

}


Output_t<double> RecordsCompany::getExpenses(int c_id){
    if (c_id < 0 ){
        return StatusType::INVALID_INPUT;
    }

    auto customer = customers.find(c_id);
    if (customer == NULL){
        return StatusType::DOESNT_EXISTS;
    }
    //change the find by id
    Customer* current = clubMembers.find_by_id(c_id);
    // chnage all this places for double
    double expense = current->get_expense();
    auto temp = Output_t<double>(expense);
    return temp;
}




