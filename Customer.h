#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "utilesWet2.h"

class Customer{
private:
    int c_id;
    int phone;
    bool isClubMember;
    double expense;
    static const int NO_EXPANSE = 0;
    static const int TEMP = 0;
public:
    // Construtor / Destructor
    Customer(int id, int phone);
    explicit Customer (int id);
    ~Customer() = default;

    //Getters
    int get_id() const;
    int get_phone() const;
    bool get_isMember() const;
    double get_expense() const;

    //Setters
    StatusType set_club_member();
    void update_expense(double amount);

};

// Operator overloading
bool operator>(const Customer &customer1, const Customer &customer2);
bool operator<(const Customer& customer1, const Customer& customer2);
bool operator==(const Customer& customer1, const Customer& customer2);


#endif