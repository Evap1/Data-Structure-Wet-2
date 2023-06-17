#ifndef RECORD_H
#define RECORD_H

#include "utilesWet2.h"

class Record{
private:
    int r_id;
    int copies;
    int purchases;

    static const int NO_PURCHASES = 0;
public:
    // Constructor / Destructor
    Record(int id, int copies);
    ~Record() = default;

    //Getters
    int get_id() const;
    int get_copies() const;
    int get_purchases() const;

    //Setters
    void set_r_id(int id);
    void set_copies(int count);
    void raise_purchases(int count);
    
};

// Operator overloading
bool operator>(const Record &record1, const Record &record2);
bool operator<(const Record& record1, const Record& record2);
bool operator==(const Record& record1, const Record& record2);








#endif //RECORD_H