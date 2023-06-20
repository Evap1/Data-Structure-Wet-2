
#ifndef AVL_H
#define AVL_H

#include<iostream>
#include "utilesWet2.h"

using namespace std;

//TODO: DELETE PRINT FUNCTIONS

// Implementation later on
template <class T>
class TreeNode;

// Node
template <class T>
class Node{
public:
    friend class TreeNode<T>;

    explicit Node(const T& value) : key(value) , left(NULL), right(NULL), height(0), rank(0) {}

    ~Node() = default;
    Node<T>& operator = (const Node<T>&other);

// GETTERS:
    const T& get_key();
    T get_key_to_set();
    T* get_key_by_ref();

    Node<T>* get_left_nonConst();
    const Node<T>* get_left();

    Node<T>* get_right_nonConst();
    const Node<T>* get_right();

    int get_hight() const;
    double get_rank() const;
    void add_rank(double amount);
    void set_hight(int amount);

private:
    T key;
    Node<T>* left;
    Node<T>* right;
    int height;
    double rank;
};

// AVL Tree
template <class T>
class TreeNode
{
private:
    Node<T> *root;
    int elementsCount;

    // Rotation methods
    int get_balance_factor(Node<T> *v);
    void updateHeight(Node<T>* v);
    Node<T>* right_rotate(Node<T>* B);
    Node<T>* left_rotate(Node<T>* A);
    Node<T>* rotate_LL(Node<T> *v);
    Node<T>*  rotate_RL(Node<T>  *v);
    Node<T>*  rotate_LR(Node<T> *v);
    Node<T>*  rotate_RR(Node<T> *v);
    Node<T>*  balance_Tree(Node<T>* node);

    // additional methods
    double getRankAux(Node<T> *v, const T& value);
    Node<T>* insert(Node<T>* node, const T& value);
    Node<T>* remove(const T& value, Node<T> *v);
    Node<T>* find(Node<T>* v, const T &value) const;
    Node<T>* findMinAux(Node<T>* v) const;
    Node<T>* findMaxAux (Node<T>* v) const;
    Node<T>* findClosestMinAux(Node<T> *current, Node<T> *max, const T& value) const;
    Node<T>* findClosestMaxAux(Node<T> *current, Node<T> *min, const T& value) const;

    Node<T>* find_by_id(int value);

    //printing/listing
    void inorder(Node<T>* v);
    int list_inorder_aux( Node<T>* v, Node<T> **arr, int index);
    void printBT(const std::string& prefix, const Node<T>* node, bool isLeft);

public:
    TreeNode();
    ~TreeNode();
    void delete_tree(Node<T>* v);
    // Getters
    int get_height();
    int get_counter();
    Node<T>* get_root();
    double get_rank(const T& value);

    // Additional
    StatusType insert(const T& value);
    StatusType remove(const T& value);
    StatusType delete_tree();
    Node<T>* find(const T& value) const;
    Node<T>* findMax () const;
    Node<T>* findMin() const;
    Node<T>* findClosestMax(const T& value) const ;
    Node<T>* findClosestMin(const T& value) const ;



        // Printing/listing
    void list_inorder(Node<T>** arr);
    void print_tree();
    void printBT(const TreeNode& tree);

};
// -----------------------------------------NODE CLASS---------------------------------------

// -----------------------------------------Constructor----------------------------------------

/// @brief Node operator= overload
template<class T>
Node<T> &Node<T>::operator=(const Node<T> &other) {
    if (this == other) return *this;
    key = other.key;
    left = other.left;
    right = other.right;
    height = other.height;
    rank = other.rank;
    return *this;
}

//Node() : key(NULL), left(NULL), right(NULL), height(0), rank(0) {}

// -----------------------------------------GETTERS/SETTERS---------------------------------------
template <class T>
const T& Node<T>::get_key(){
    return key;
}

template <class T>
T Node<T>::get_key_to_set(){
    return key ;
}

template <class T>
T* Node<T>::get_key_by_ref(){
    return &key ;
}

template <class T>
Node<T>* Node<T>::get_left_nonConst() {
    return left;
}

template <class T>
const Node<T>* Node<T>::get_left() {
    return left;
}


template <class T>
Node<T>* Node<T>::get_right_nonConst() {
    return right;
}

template <class T>
const Node<T>* Node<T>::get_right() {
    return right;
}

template <class T>
int Node<T>::get_hight() const {
    return height;
}

template <class T>
double Node<T>::get_rank() const{
    return rank;
}
template <class T>
void Node<T>::add_rank(double amount){
    rank += amount;
}

template <class T>
void Node<T>::set_hight(int amount){
    height = amount;
}


// -----------------------------------------TREENODE CLASS---------------------------------------

// -----------------------------------------Constructor----------------------------------------
// @brief private constructor to be accessed once: defines our root to be empty.
template <class T>
TreeNode<T>::TreeNode() :
        root(NULL),
        elementsCount(0)
        {}


// -----------------------------------------Destructor----------------------------------------
// TODO: make sure valngrid
template <class T>
TreeNode<T>::~TreeNode(){
    delete_tree(root);
}

/// @brief Additional helper method for destructor. Recursive method since we have no parent pointers and
/// @tparam T
/// @param v
template<class T>
void TreeNode<T>::delete_tree(Node<T> *v) {
    if (v == NULL){
        return;
    }
    delete_tree(v->left);
    delete_tree(v->right);
    try {
        delete v;
    }
    catch (...){
        throw StatusType::ALLOCATION_ERROR;
    }
}

/// @brief outside helper method to delete a tree without destructor (used with ptrs)
/// @tparam T
/// @return
template<class T>
StatusType TreeNode<T>::delete_tree(){
    try {
        delete_tree(root);
    }
    catch (...){
        cout << "AVLTree, delete_tree(root) has a problem." << endl;
    }
    return StatusType::SUCCESS;
}
// ---------------------------------------------ROTATION METHODS-------------------------------

// When lowest node is on the LL path from v.
template<class T>
Node<T>* TreeNode<T>::rotate_LL(Node<T> *v) {
    return right_rotate(v) ;
}

// When lowest node is on the RR path from v.
template<class T>
Node<T>* TreeNode<T>::rotate_RR(Node<T> *v) {
    return left_rotate(v) ;
}

// When lowest node is on the RL path from v.
template<class T>
Node<T>* TreeNode<T>::rotate_RL(Node<T> *v) {
    Node<T>* vr = v->right;
    v->right = right_rotate(vr);
    return left_rotate(v) ;
}

// When lowest node is on the LR path from v.
template<class T>
Node<T>* TreeNode<T>::rotate_LR(Node<T> *v) {
    Node<T>* vl = v->left;
    v->left = left_rotate(vl);
    return right_rotate(v) ;
}

// performing left rotation when A was the src root and then B is the final root.
template<class T>
Node<T>* TreeNode<T>::left_rotate(Node<T> *A) {
    //Sub-trees and nodes to be modified
    Node<T>* B= A->right;
    Node<T>* Bl = B->left;

    //update the ranks:
    int a_rank = A->rank;
    int b_rank = B->rank;
    A->rank = -b_rank;
    B->rank += a_rank;
    Bl->rank += b_rank;

    //make rotation
    B->left = A;
    A->right= Bl;

    //update height
    updateHeight(A);
    updateHeight(B);

    //return new root
    return B;
}

// performing right rotation when B was the src root and then A is the final root.
template<class T>
Node<T>* TreeNode<T>::right_rotate(Node<T> *B) {
    //Sub-trees and nodes to be modified
    Node<T>* A = B->left;
    Node<T>* Ar = A->right;

    //update ranks:
    int b_rank = B->rank;
    int a_rank = A->rank;
    A->rank += b_rank;
    B->rank = -a_rank;
    Ar->rank += b_rank;

    //make rotation
    A->right = B;
    B->left = Ar;

    //update height
    updateHeight(A);
    updateHeight(B);

    //return new root
    return A;
}

/// @brief check if the current node is balance and rotate if needed
/// @tparam T
/// @param node
/// @return balanced node
template <class T>
Node<T>* TreeNode<T>::balance_Tree(Node<T>* node)
{
    if (get_balance_factor(node) == -2){
        if (get_balance_factor(node->right) == 1){
            node = rotate_RL(node);
        }
        else node = rotate_RR(node);
    }

    if (get_balance_factor(node) == 2){
        if (get_balance_factor(node->left) == -1){
            node = rotate_LR(node);
        }
        else node = rotate_LL(node);
    }
    return node;
}

/// @brief updating the height of node v. dealing with possibility that we are too low in the tree
/// @tparam T - class type of the node.
/// @param v - node to update
template<class T>
void TreeNode<T>::updateHeight(Node<T>* v) {
    if (v->left == NULL){
        if (v->right == NULL){
            v->height=0;
        }
        else v->height = v->right->height + 1;
    }
    else if (v->right == NULL){
        v->height = v->left->height + 1;
    }
    else{
        int maxHight =v->right->height;
        if(v->left->height > v->right->height)
            maxHight = v->left->height;
        v->height = 1 + maxHight;
    }
}

/// @brief Get the balance factor of a node
/// @tparam T
/// @param v
/// @return integer in the range of [-2,-1,0,1,2]
template<class T>
int TreeNode<T>::get_balance_factor(Node<T> *v) {
    if (v == NULL)
        return 0;
    int l = 0, r = 0;

    if (v->left == NULL)
    {
        l = -1;
        if (v->right == NULL) return 0;
        else r = v->right->height;
    }
    else if (v->right == NULL)
    {
        r = -1;
        l = v->left->height;
    }
    else
    {
        l = v->left->height;
        r = v->right->height;
    }
    return l - r;
}


// -----------------------------------------ADDITIONAL METHODS-----------------------------------------

/// @brief Method to determine whether some value already exist
/// @tparam T - the class type
/// @param v - usually called with root with public func find.
/// @param value - to find.
/// @return  - NULL if not found , the ptr to element if found.
template<class T>
Node<T>* TreeNode<T>::find(Node<T>* v, const T &value) const {
    if (v == NULL) return NULL;

    if (v->key == value){
        return v;
    }
    else if (v->key < value){
        return find(v->right, value);
    }
    else{
        return find(v->left, value);
    }
}

/// @brief Insert new node as a leaf and make rotations if needed to remain balanced tree- all the way to the root.
/// @tparam T - the class type
/// @param node - usually called with root with public func find.
/// @param value - to insert
/// @return - ptr to the original node.
template<class T>
Node<T> *TreeNode<T>::insert(Node<T>* node, const T& value) {
    if (node == NULL){
        node = new Node<T>(value);
        elementsCount++;
    }
    else{
        if (node->key < value){
            node->right = insert(node->right, value);
        }

        if (node->key > value){
            node->left = insert(node->left, value);
        }
    }

    node = balance_Tree(node);
    updateHeight(node);
    return node;
}

/// @brief insert one element with a value. PUBLIC
/// @tparam T -class type
/// @param value - to be added.
/// @return Status of the operation.
template<class T>
StatusType TreeNode<T>::insert(const T& value) {
    //if (value == nullptr) return StatusType::FAILURE;

    // inserting one element only if NOT exists
    if (find(root, value) == NULL){
        try {
            root = insert(root, value);
        }
        catch (const std::bad_alloc&){
            return StatusType::ALLOCATION_ERROR;
        }
        return StatusType::SUCCESS;
    }
    // already exists
    return StatusType::FAILURE;
}

// Delete a node and re-balance the tree - all the way to the root.
template<class T>
Node<T>* TreeNode<T>::remove(const T& value, Node<T> *v) {
    Node<T>* temp;

    // if value not found, remove returns NULL.
    if (v == NULL){
        return NULL;
    }

        // binary search for the element. ALL CASES ONLY FOR FOUND ELEMENT
        // case1: value to be found is smaller than current value
    else if ( value < v->key){
        v->left = remove(value, v->left);
    }
        // case2: value to be found is greater than current value
    else if ( value > v->key){
        v->right = remove(value, v->right);
    }
        // case3.1: element is found with two subtrees, we make copies and "roll" until
        //  we reach the level of a leaf. and make deletion the the last else.
    else if (v->left != NULL && v->right != NULL){
        //find the new head of the right subtree
        temp = findMin(v->right);
        //copy the min element in right subtree
        v->key = temp->key;
        //delete other(!) element which we have just copied.
        v->right = remove(v->key, v->right);
    }
        // case3.2: element is found with one or none subtrees
    else {
        temp = v;
        if (v->right == NULL && v->left == NULL){
            delete temp;
        }
        else if (v->left == NULL){
            v = v->right;
            delete temp;
        }
        else if (v->right == NULL){
            v = v->left;
            delete temp;
        }
    }

    //in case v is the last on any subtree;
    if ( v == NULL ){
        return v;
    }
    //update new heights:
    updateHeight(v);

    //rotations if needed, from bottom -> up:
    v = balance_Tree(v);
    return v;
}

/// @brief remove one element with a value. PUBLIC
/// @tparam T -class type
/// @param value - to be removed
/// @return Status of the operation.
template<class T>
StatusType TreeNode<T>::remove(const T &value) {
    //if (value == NULL) return StatusType::FAILURE;

    // removing one element only if exists
    if (find(root, value) != NULL){
        try {
            root = remove(value,root);
        }
        catch(...){
            return StatusType::ALLOCATION_ERROR;
        }
        elementsCount--;
        return StatusType::SUCCESS;
    }
    // value not found:
    return StatusType::FAILURE;
}

/// @brief search for an element PUBLIC
/// @tparam T - class
/// @param value - to search
/// @return - NULL if not found , the ptr to element if found.
template<class T>
Node<T> *TreeNode<T>::find(const T &value) const {
    // if(value == NULL)
    //     return NULL;
    return find(root,value);
}

/// @brief search for an element BY ID ONLY
/// @tparam T - class
/// @param value - to search
/// @return - NULL if not found , the ptr to element if found.
template<class T>
Node<T>* TreeNode<T>::find_by_id(int value) {
    T* temp = new T(value);
    Node<T>* current = find(root, *temp);
    delete temp;
    return current;
}

/// @brief Find max value IN THE WHOLE TREE and return it's node.
/// @tparam T
/// @param v
/// @return max node inth e whole tree
template<class T>
Node<T>* TreeNode<T>::findMax() const{
    return findMaxAux(root);
}

/// @brief helper for findMax method
/// @tparam T
/// @param v - accessed with root
/// @return max node in the subtrees of v
template<class T>
Node<T>* TreeNode<T>::findMaxAux(Node<T> *v) const{
    if (v == NULL){
        return NULL;
    }
    else if (v->right == NULL){
        return v;
    }
    else return findMaxAux(v->right);
}

/// @brief Find min value and return it's node.
/// @tparam T
/// @param v
/// @return min node in the subtrees of v
template<class T>
Node<T>* TreeNode<T>::findMin() const{
    return findMinAux(root);
}

/// @brief Find min value and return it's node.
/// @tparam T
/// @param v
/// @return min node in the subtrees of v
template<class T>
Node<T>* TreeNode<T>::findMinAux(Node<T> *v) const{
    if ( v == NULL){
        return NULL;
    }
        //min is only on sub left tree
    else if (v->left == NULL){
        return v;
    }
        //min will be found on subtree on the left only
    else return findMinAux(v->left);
}

template<class T>
Node<T>* TreeNode<T>::findClosestMin(const T& value) const {
    return findClosestMinAux(root, root, value);
}


// assuming we didnt find the needed value so we are looking for the closest from above
template<class T>
Node<T>* TreeNode<T>::findClosestMinAux(Node<T> *current, Node<T> *max, const T& value) const{
    if (current == NULL) return max;

    //we are still greater then needed, do left to search search smaller
    else if (current->key > value){
        return findClosestMinAux(current->left, current, value);
    }
        //if(current->key > value )
    else {
        //we can search smaller but it's already greater
        if (current->right != NULL && current->right->key > value){
            return max;
        }
        return findClosestMinAux(current->right, current, value);
    }
}

template<class T>
Node<T>* TreeNode<T>::findClosestMax(const T& value) const {
    return findClosestMaxAux(root, root, value);
}


template<class T>
Node<T>* TreeNode<T>::findClosestMaxAux(Node<T> *current, Node<T> *min, const T& value) const {
    if (current == NULL) return min;

    //we are still smallet then needed, do right to search greateer
    else if (current->key < value){
        return findClosestMaxAux(current->right, current, value);
    }
    //if(current->key > value )
    else {
        //we can search smaller but it's already greater
        if (current->left != NULL && current->left->key > value){
            return min;
        }
        return findClosestMaxAux(current->left, min, value);
    }
}


// -----------------------------------------Getters-----------------------------------------
template<class T>
int TreeNode<T>::get_height() {
    if (this == NULL) return -1;
    return this->height;
}

template<class T>
int TreeNode<T>::get_counter() {
    return this->elementsCount;
}

template<class T>
Node<T> *TreeNode<T>::get_root() {
    return root;
}



/// \tparam T
/// \param key
/// \return -1 incase the key does not exist
template <class T>
double TreeNode<T>::get_rank(const T& value)
{
    return getRankAux(root, value);
}

//user has to check v indeed exists
template <class T>
double TreeNode<T>::getRankAux(Node<T> *v, const T& value)
{
    if (v->key == value){
        return v->get_rank();
    }
    if ( v->key < value){
        double temp = getRankAux(v->right, value);
        return v->get_rank() + temp;
    }
    else{
        double temp = getRankAux(v->left, value);
        return v->get_rank()+ temp;
    }
}


// -----------------------------------------LISTING METHODS-----------------------------------------

/// @brief Store inordered tree into a given array. PUBLIC
/// @tparam T - type of the elements
/// @param arr - arr of the elements
template<class T>
void TreeNode<T>::list_inorder(Node<T> **arr) {
    list_inorder_aux(root, arr, 0);
}

/// @brief recursive helper for the outward method. PRIVATE
/// @tparam T
/// @param v
/// @param arr
/// @param index (!) - always need be called with 0
/// @return the current index to fill
template<class T>
int TreeNode<T>::list_inorder_aux(Node<T>* v, Node<T> **arr, int index) {
    if (v ==NULL) return index;

    index = list_inorder_aux(v->left, arr, index);
    arr[index++] = v;
    list_inorder_aux(v->right, arr, index);
    return index;
}

// -----------------------------------------PRINT METHODS-----------------------------------------

// TODO: dont forget to delete
template<class T>
void TreeNode<T>::printBT(const std::string& prefix, const Node<T>* node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        std::cout << node->key << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "│   " : "    "), node->left, true);
        printBT( prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

template<class T>
void TreeNode<T>::print_tree() {
    inorder(root);
    cout << endl;
}

template<class T>
void TreeNode<T>::printBT(const TreeNode& tree)
{
    printBT("", tree.root, false);    
}

// Print function to show the current tree. left, root, right.
template<class T>
void TreeNode<T>::inorder(Node<T> *v) {
    if (v == NULL) return;
    inorder(v->left);
    cout << v->key << " , ";
    inorder(v->right);
}


#endif //AVL_H
