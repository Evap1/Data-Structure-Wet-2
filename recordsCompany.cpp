//
// Created by Eva Poluliakhov on 16/06/2023.
//

#include "recordsCompany.h"

RecordsCompany::RecordsCompany()
{
    records = make_unique<UnionFind>();
}

StatusType RecordsCompany::newMonth(int *records_stocks, int number_of_records)
{
    if(number_of_records < 0)
        return StatusType::INVALID_INPUT;

    try
    {
        newMounthForUnionFind(records_stocks, number_of_records);
        newMounth_resetClubTree();
        reset_expense(customers.get_size(), customers.get_buckets());
    }
    catch(const std::exception& e)
    {
       // std::cerr << e.what() << '\n';
       return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}


void RecordsCompany::newMounthForUnionFind(int *records_stocks, int number_of_records)
{
    records.reset();
    records = make_unique<UnionFind>();
    for(int i = 0; i< number_of_records; i++)
    {
        // i will be the Record's ID
        shared_ptr<Record> recordToAdd = make_shared<Record>(i,records_stocks[i]);
        records->makeSet(recordToAdd);
    }
}


void RecordsCompany::newMounth_resetClubTree()
{
    resetClubTree(clubMembers.get_root());
}

void RecordsCompany::resetClubTree(Node<Customer> *root)
{
    if( root == NULL)
        return;
    resetClubTree(root->get_right_nonConst());
    resetClubTree(root->get_left_nonConst());
    root->get_key_to_set().resetExpenses();
}

void RecordsCompany::reset_expense(int arrSize, LinkedNode<Customer>** buckets){
    LinkedNode<Customer>* current;
    for (int i = 0; i < arrSize; ++i)
    {
        if (buckets[i])
        {
            current = buckets[i];
            while (current != nullptr)
            {
                current->value->resetExpenses();
                current = current->next;
            }
        }
    }
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
    customer->set_club_member();
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

//HAS PROBLEM
StatusType RecordsCompany::buyRecord(int c_id, int r_id){
    if (c_id < 0 || r_id < 0){
        return StatusType::INVALID_INPUT;
    }

    auto customer = customers.find(c_id);
    if (customer == NULL || r_id > records->getSize()){
        return StatusType::DOESNT_EXISTS;
    }

    auto record = records->findSpecified(r_id);
    // if the customer is a club member
    int expense = BASE_EXPENSE + record->get_purchases();
    if (customer->get_isMember()){
        Customer* temp = new Customer(c_id);
        clubMembers.find(*temp)->get_key_by_ref()->update_expense(expense);
        delete temp;
    }
    customer->update_expense(expense);
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

//    auto maxCustomer = clubMembers.findMax();
//    auto minCustomer = clubMembers.findMin();
//
//    int max = c_id2 - 1 ;
//    if (maxCustomer->get_key().get_id() < max){
//        max = maxCustomer->get_key().get_id();
//    }
//
//    int min = c_id1;
//    if (minCustomer->get_key().get_id() > min){
//        min = minCustomer->get_key().get_id();
//    }
    Customer* tempMin = new Customer(c_id1);
    Customer* tempMax = new Customer((c_id2-1));
    auto closestMaxCustomer = clubMembers.findClosestMax(*tempMax);
    auto closestMinCustomer = clubMembers.findClosestMin(*tempMin);
    delete tempMin;
    delete tempMax;
    int max = closestMaxCustomer->get_key().get_id();
    int min = closestMinCustomer->get_key().get_id();
    auto rootMembers = clubMembers.get_root();

    addAux( max ,amount, rootMembers, false);
    addAux( min , (-1)*amount, rootMembers, false);
    return StatusType::SUCCESS;
}

// double RecordsCompany::sumRanks(int c_id,  Node<shared_ptr<Customer>>* current){

//     if (current->get_key()->get_id() == c_id){
//         return current->get_rank();
//     }
//     else if (current->get_key()->get_id() < c_id){
//         double temp = sumRanks(c_id, current->get_right_nonConst());
//         return current->get_rank() + temp;
//     }
//     else if (current->get_key()->get_id() > c_id){
//         double temp = sumRanks(c_id, current->get_left_nonConst());
//         return current->get_rank() + temp;
//     }
// }

Output_t<double> RecordsCompany::getExpenses(int c_id){
    if (c_id < 0 ){
        return StatusType::INVALID_INPUT;
    }

    auto customer = customers.find(c_id);
    if (customer == NULL){
        return StatusType::DOESNT_EXISTS;
    }
    double discount = 0;
    if (customer->get_isMember()){
        discount = clubMembers.get_rank(*customer);
    }
    double expense = customer->get_expense();
    auto temp = Output_t<double>(expense-discount);
    return temp;
}



StatusType RecordsCompany::putOnTop(int r_id1, int r_id2)
{
    if(r_id1 < 0 || r_id2 < 0)
        return StatusType::INVALID_INPUT;

    if(r_id1 >= records->getSize() || r_id2 >= records->getSize())
        return StatusType::DOESNT_EXISTS;

    shared_ptr<Record> record1 = records->find(r_id1);
    shared_ptr<Record> record2 = records->find(r_id2);

    if((record1 == NULL || record2 == NULL) || (*record1 == *record2))
        return StatusType::FAILURE;

    shared_ptr<Record> groupRecord = records->union_PutOnTop(r_id1, r_id2);
    if(groupRecord == NULL)
        return StatusType::FAILURE;

    return StatusType::SUCCESS;
}


StatusType RecordsCompany::getPlace(int r_id, int *column, int *hight)
{
    if(r_id < 0)
        return StatusType::INVALID_INPUT;

    if(r_id >= records->getSize())
        return StatusType::DOESNT_EXISTS;

    bool flag = records->getPlace(r_id, column, hight);
    if(flag)
        return StatusType::SUCCESS;
    return StatusType::FAILURE;
}







