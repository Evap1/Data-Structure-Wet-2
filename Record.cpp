#include "Record.h"

Record::Record(int id, int copies) : r_id(id), copies(copies), purchases(NO_PURCHASES) {};


//--------------------------------------GETTERS/SETTERS------------------------------------------------------

int Record::get_id() const{
    return r_id;
}
int Record::get_copies() const{
    return copies;
}
int Record::get_purchases() const{
    return purchases;
}

void Record::set_r_id(int id){
    r_id = id;
}
void Record::set_copies(int count){
    copies=count;
}

/// \param count add the count to the already gained purchases
void Record::raise_purchases(int count){
    purchases += count;
}

//--------------------------------------OPERATOR OVERLOADING------------------------------------------------------

bool operator>(const Record &record1, const Record &record2){
    return (record1.get_id() > record2.get_id());
}
bool operator<(const Record& record1, const Record& record2){
    return (record1.get_id() < record2.get_id());
}
bool operator==(const Record& record1, const Record& record2){
    return (record1.get_id() == record2.get_id());
}


