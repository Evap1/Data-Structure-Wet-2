
#include "Customer.h"

//-----------------------------------CONSTRUCTOR/DESTRUCTOR------------------------------------------------

Customer::Customer(int id, int phone) : c_id(id), phone(phone), isClubMember(false), expense(NO_EXPANSE){}

//--------------------------------------GETTERS/SETTERS------------------------------------------------
int Customer::get_id() const
{
    return c_id;
}

int Customer::get_phone() const
{
    return phone;
}                                       

bool Customer::get_isMember() const
{
    return isClubMember;
} 

StatusType Customer::set_club_member(){
    isClubMember=true;
    return StatusType::SUCCESS;
}

void Customer::update_expense(int amount){
    expense+=amount;
}

//--------------------------------------OPERATOR OVERLOADING------------------------------------------------

bool operator>(const Customer &customer1, const Customer &customer2){
    return (customer1.get_id() > customer2.get_id());
}
bool operator<(const Customer& customer1, const Customer& customer2){
    return (customer1.get_id() < customer2.get_id());
}
bool operator==(const Customer& customer1, const Customer& customer2){
    return (customer1.get_id() == customer2.get_id());
}