//
// Created by Eva Poluliakhov on 16/06/2023.
//

#include "recordsCompany.h"


StatusType RecordsCompany::newMonth(int *records_stocks, int number_of_records){

}


StatusType RecordsCompany::addCostumer(int c_id, int phone){
    if (c_id < 0 || phone < 0){
        return StatusType::INVALID_INPUT;
    }

    if (customers.find(c_id) != NULL){
        return StatusType::ALREADY_EXISTS;
    }

    auto toAdd = make_shared<Customer>(c_id, phone);
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

    return clubMembers.insert(*customer);
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
    if (customer == NULL || r_id > records.getSize()){
        return StatusType::DOESNT_EXISTS;
    }

    auto record = records.find(r_id);
    // if the customer is a club member
    if (customer->get_isMember()){
        int expense = BASE_EXPENSE + record->get_purchases();
        Customer* temp = new Customer(c_id);
        clubMembers.find(*temp)->get_key_by_ref()->update_expense(expense);
        delete temp;
    }
    record->raise_purchases(1);
    return StatusType::SUCCESS;
}

// assuming c_id indeed exist
void RecordsCompany::addAux(int c_id, double amount, Node<Customer>* start, bool wasRight){

    // found the element
    if (start->get_key().get_id() == c_id){
        //we didnt add yet
        if (!wasRight){
            start->add_rank(amount);

            // the right side is out of range
            if (start->get_right()!= NULL){
                start->get_right_nonConst()->add_rank((-1)*amount);
            }
        }
    }

    // need to search right
    else if (start->get_key().get_id() < c_id){
        //update the field
        if (!wasRight){
            start->add_rank(amount);
        }
        //go  -> right
        auto rightSon = start->get_right_nonConst();

        //found the element
        if (rightSon->get_key().get_id() == c_id){
            return addAux(c_id, amount, rightSon, true);
        }
        //go  -> right -> right
        if (rightSon->get_key().get_id() < c_id) {
            return addAux(c_id, amount, rightSon, true);
        }
        //go  -> right -> left
        if (rightSon->get_key().get_id() > c_id){
            //update the root which is too big
            rightSon->add_rank((-1)*amount);
            //update the subtree which need the raise
            rightSon->get_left_nonConst()->add_rank(amount);
            return addAux(c_id, amount, rightSon, true);
        }
    }

    // need to search left
    else if (start->get_key().get_id() > c_id){
        //go  -> left
        auto leftSon = start->get_left_nonConst();

        //found the needed value
        if (leftSon->get_key().get_id() == c_id) {
            return addAux(c_id, amount, leftSon, false);
        }

        //go -> left -> right
        if (leftSon->get_key().get_id() < c_id){
            //update the field
            leftSon->add_rank(amount);
            //right subtree doesnt need, update it:
            leftSon->get_right_nonConst()->add_rank((-1)*amount);
            return addAux(c_id, amount, leftSon, true);
        }
        //go -> left -> left
        else if (leftSon->get_key().get_id() > c_id){
            return addAux(c_id, amount, leftSon, false);
        }

    }
}

// add to all until cid2-1 because we dont want to give to cid2 and reduce to all to cid1
StatusType RecordsCompany::addPrize(int c_id1, int c_id2, double  amount){
    if (amount <= 0 || c_id1 < 0 || c_id2 < 0 ){
        return StatusType::INVALID_INPUT;
    }

    auto customer1 = customers.find(c_id1);
    auto customer2 = customers.find(c_id2);

    if (customer1 == NULL || customer2 == NULL){
        return StatusType::DOESNT_EXISTS;
    }

    auto rootMembers = clubMembers.get_root();
    addAux(c_id2 -1 ,amount, rootMembers, false);
    addAux(c_id1, (-1)*amount, rootMembers, false);
    return StatusType::SUCCESS;
}

//double RecordsCompany::sumRanks(int c_id,  Node<shared_ptr<Customer>>* current){
//
//    if (current->get_key()->get_id() == c_id){
//        return current->get_rank();
//    }
//    else if (current->get_key()->get_id() < c_id){
//        double temp = sumRanks(c_id, current->get_right_nonConst());
//        return current->get_rank() + temp;
//    }
//    else {
//        double temp = sumRanks(c_id, current->get_left_nonConst());
//        return current->get_rank() + temp;
//    }
//}

Output_t<double> RecordsCompany::getExpenses(int c_id){
    if (c_id < 0 ){
        return StatusType::INVALID_INPUT;
    }

    auto customer = customers.find(c_id);
    if (customer == NULL){
        return StatusType::DOESNT_EXISTS;
    }

    double discount = clubMembers.get_rank(*customer);
    double expense = customer->get_expense();
    auto temp = Output_t<double>(expense-discount);
    return temp;
}


StatusType RecordsCompany::putOnTop(int r_id1, int r_id2)
{
    if(r_id1 < 0 || r_id2 < 0)
        return StatusType::INVALID_INPUT;

    if(r_id1 >= records.getSize() || r_id2 >= records.getSize())
        return StatusType::DOESNT_EXISTS;

    shared_ptr<Record> record1 = records.find(r_id1);
    shared_ptr<Record> record2 = records.find(r_id2);

    if((record1 == NULL || record2 == NULL) || (*record1 == *record2))
        return StatusType::FAILURE;

    shared_ptr<Record> groupRecord = records.union_PutOnTop(r_id1, r_id2);
    if(groupRecord == NULL)
        return StatusType::FAILURE;

    return StatusType::SUCCESS;
}


StatusType RecordsCompany::getPlace(int r_id, int *column, int *hight)
{
    if(r_id < 0)
        return StatusType::INVALID_INPUT;

    if(r_id >= records.getSize())
        return StatusType::DOESNT_EXISTS;

    bool flag = records.getPlace(r_id, column, hight);
    if(flag)
        return StatusType::SUCCESS;
    return StatusType::FAILURE;
}





