
#include "Customer.h"

//-----------------------------------CONSTRUCTOR/DESTRUCTOR------------------------------------------------

Customer::Customer(int id, int phone) : c_id(id), phone(phone), isClubMember(false), expense(NO_EXPANSE){}

//--------------------------------------GETTERS/SETTERS------------------------------------------------
const int Customer::get_c_id() const
{
    return c_id;
}

 const int Customer::get_phone() const
{
    return phone;
}                                       

 const bool Customer::get_isMember() const
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
    return (customer1.get_c_id() > customer2.get_c_id());
}
bool operator<(const Customer& customer1, const Customer& customer2){
    return (customer1.get_c_id() < customer2.get_c_id());
}
bool operator==(const Customer& customer1, const Customer& customer2){
    return (customer1.get_c_id() == customer2.get_c_id());
}