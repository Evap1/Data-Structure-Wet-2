#ifndef RECORDS_COMPANY_H
#define RECORDS_COMPANY_H

#include "utilesWet2.h"



class RecordsCompany {
  private:
    // todo
  public:
    RecordsCompany();
    ~RecordsCompany();

    /// @brief first, update the record id for all records and re-arrange records according to it.
    ///        second, upfate the amount of money each customer has to pay (if club member)
    /// @param records_stocks - array of records, holding number of copies of a record.
    /// @param number_of_records - size of the array above (e.g. number of records the store is holding)
    /// @param COMPLEXITY - O(n+m)
    /// @return INVALID_INPUT if number of records < 0
    ///         ALLOCATION_ERROR in case of problems with memory alloctions
    ///         SUCCESS in case everything is working
    StatusType newMonth(int *records_stocks, int number_of_records);

    /// @brief add new customer
    /// @param c_id 
    /// @param phone 
    /// @param COMPLEXITY - aprrox: O(1)
    /// @return INVALID_INPUT if any param < 0
    ///         ALREADY_EXISTS if user exists
    ///         ALLOCATION_ERROR in case of problems with memory alloctions
    ///         SUCCESS in case everything is working
    StatusType addCostumer(int c_id, int phone);

    /// @brief finds phone number of a user
    /// @param c_id - user id 
    /// @param COMPLEXITY - aprrox: O(1)
    /// @return INVALID_INPUT if c_id  < 0
    ///         DOESNT_EXISTS if user doesnt exist
    Output_t<int> getPhone(int c_id);

    /// @brief make the given customer, a club member
    /// @param c_id - id of user to make a club member
    /// @param COMPLEXITY - O(logn)
    /// @return INVALID_INPUT if c_id  < 0
    ///         ALREADY_EXISTS if user exists
    ///         DOESNT_EXISTS if user doesnt exist
    ///         ALLOCATION_ERROR in case of problems with memory alloctions
    ///         SUCCESS in case everything is working
    StatusType makeMember(int c_id);

    /// @brief determaine whether this customer is a club member
    /// @param c_id id of a user to check
    /// @param COMPLEXITY - approx O(1)
    /// @return INVALID_INPUT if c_id  < 0
    ///         DOESNT_EXISTS if user doesnt exist
    ///         SUCCESS in case everything is working
    Output_t<bool> isMember(int c_id);

    /// @brief firstly, if user is club member add value for the monthly expense
    ///                 if user is not a club member, pay the price for the record
    ///        secondly, add one purchase for the record
    /// @param c_id - user who purchasees the record
    /// @param r_id - record to purchase 
    /// @param COMPLEXITY - O(logn)
    /// @return INVALID_INPUT if any param is  < 0
    ///         DOESNT_EXISTS if user doesnt exist or r_id > number of records
    ///         SUCCESS in case everything is working
    StatusType buyRecord(int c_id, int r_id);

    /// @brief make a discount for all *club members* in the range between c_id1, c_id2
    /// @param c_id1 - start range (included)
    /// @param c_id2 - end range
    /// @param amount - to substruct for the monthly expense
    /// @param COMPLEXITY - O(logn)
    /// @return INVALID_INPUT if amount  <= 0 or c_id1/2 <0
    ///         SUCCESS in case everything is working
    StatusType addPrize(int c_id1, int c_id2, double  amount);

    /// @brief get how much club member has to pay (after discount)
    /// @param c_id
    /// @param COMPLEXITY - O(logn)
    /// @return INVALID_INPUT if any param is  < 0
    ///         DOESNT_EXISTS if user doesnt exist or r_id > number of records
    ///         value of all expenses of the current club member
    Output_t<double> getExpenses(int c_id);

    /// @brief stack the stack where first record is in on top of the stack where the second 
    ///        record is in. height of each record1 is raised by the height of the record2.
    ///        
    /// @param r_id1 
    /// @param r_id2 
    /// @param COMPLEXITY - O(log*m)
    /// @return INVALID_INPUT if any param is  < 0
    ///         DOESNT_EXISTS r_id1 or r_id2 >= number of records
    ///         FAILURE if the stacks are already on top of each other
    ///         SUCCESS in case everything is working
    StatusType putOnTop(int r_id1, int r_id2);

    /// @brief returns the location r_id is stored, in terms of coumn and height(row)
    /// @param r_id 
    /// @param column 
    /// @param hight
    /// @param COMPLEXITY - O(log*m) 
    /// @return INVALID_INPUT if r_id < 0 or height/column is null
    ///         DOESNT_EXISTS r_id >= number of records
    ///         SUCCESS in case everything is working
    StatusType getPlace(int r_id, int *column, int *hight);
};

#endif