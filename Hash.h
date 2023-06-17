//
// Created by Eva Poluliakhov on 16/06/2023.
//

#ifndef WET2_HASH_H
#define WET2_HASH_H

class Record;
class Customer;
// Linked List node
template <class T>
class LinkedNode {
public:
    T value;
    LinkedNode* next;

    LinkedNode() = default;
    explicit LinkedNode(T* value) : value(value) , next(nullptr){}
};

template <class T>
class Hash
{
private:
    int elements;
    int arrSize;
    LinkedNode<T>** buckets;

    int h(int id) const;

    void increaseSize();
    static const int STARTING_SIZE = 10;
    static const int ALPHA = 4;
public:
    Hash();
    ~Hash();

    Hash(const Hash&) = delete;
    Hash& operator=(const Hash&) = delete;

    StatusType insert(const T& element);
    T find (int id);

};

//-----------------------------------------Constructor/ Destructor--------------------------------------

template <class T>
Hash<T>::Hash() : elements(0), arrSize(STARTING_SIZE), buckets(new LinkedNode<T>*[STARTING_SIZE])
{
    for (int i = 0; i < arrSize; ++i)
    {
        buckets[i] = nullptr;
    }
}

template <class T>
Hash<T>::~Hash()
{
    LinkedNode<T>* current, *toDelete;
    for (int i = 0; i < arrSize; ++i)
    {
         if (buckets[i])
         {
            current = buckets[i];
            while (current != nullptr)
            {
                delete current->value;
                toDelete = current;
                current = current->next;
                delete toDelete;
            }
         }
    }
    delete[] buckets;
}

//-----------------------------------------Private Methods--------------------------------------
//uses arr elements! make sure to update this field before use.
template <class T>
int Hash<T>::h(int id) const
{
    return (id % arrSize);
}

template <class T>
void Hash<T>::increaseSize(){
    arrSize *= 2;

    Node<T>** newArr = new LinkedNode<T>*[arrSize];
    for (int i = 0; i < arrSize; i ++){
        newArr[i] = nullptr;
    }

    // now we sort buckets again
    LinkedNode<T>* toDelete, *temp, *current;
    for (int i = 0; i < arrSize; i ++){
        current = buckets[i];

        while (current != nullptr){
            //find the new location on the node
            int newLocation = h(current->value->get_id());
            //preserve the next node in queue and take out the current node.
            temp = current->next;

            //insert the current node in top of the linked list
            current->next = newArr[newLocation];
            newArr[newLocation] = current;
            //go back to the source linked list
            current = temp;
        }
    }
    //preserve the old arr for deleting memory
    toDelete = buckets;
    buckets = newArr;
    delete[] toDelete;
}

//-----------------------------------------Public Methods--------------------------------------

template <class T>
StatusType Hash<T>::insert(const T& element){
    int id = element->get_id();
    if (find(id) != nullptr){
        return StatusType::ALREADY_EXISTS;
    }

    LinkedNode<T>* bucket = buckets[h(id)];
    while (bucket->next != nullptr){
        bucket = bucket->next;
    }
    LinkedNode<T>* toInsert = new LinkedNode<T>(element);
    bucket->next = toInsert;
    elements++;
    // m * alpha = n while m is the arrSize and n is the elements
    if (arrSize * ALPHA <= elements){
        increaseSize();
    }
    return StatusType ::SUCCESS;
}

/// \tparam T
/// \param id
/// \return nullptr if not found. else return the data of the node.
template <class T>
T Hash<T>::find(int id){
    LinkedNode<T>* bucket = buckets[h(id)];
    while (bucket->value->get_id() != id){
        if (bucket->next == nullptr){
            return nullptr;
        }
        bucket = bucket->next;
    }
    return bucket->value;
}

#endif //WET2_HASH_H
