#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "utilesWet2.h"

class Customer{
private:
    int c_id;
    int phone;
    bool isClubMember;
    int expense;
    static const int NO_EXPANSE = 0;

public:
    // Construtor / Destructor
    Customer(int id, int phone);
    ~Customer() = default;

    //Getters
    int get_id() const;
    int get_phone() const;
    bool get_isMember() const;
    int get_expense() const;

    //Setters
    StatusType set_club_member();
    void update_expense(int amount);

};

// Operator overloading
bool operator>(const Customer &customer1, const Customer &customer2);
bool operator<(const Customer& customer1, const Customer& customer2);
bool operator==(const Customer& customer1, const Customer& customer2);


#endif