

#ifndef WET2_UNIONFIND_H
#define WET2_UNIONFIND_H

#include "utilesWet2.h"
#include <memory>
#include "Record.h"
#include "Hash.h"

using namespace std;




template <class T>
class UpTreeNode
{
public:
    int groupCount;
    shared_ptr<T> value;
    shared_ptr<UpTreeNode> father;

    // added to the basic union find:
    int semiHight;
    int column;

    UpTreeNode(shared_ptr<T> Value): groupCount(1), value(Value), father(NULL), semiHight(0), column(0){}
    ~UpTreeNode() = default;
    int get_id() {
        return value->get_id();
    }


};


template <class T>
class UnionFind
{

    private:
    shared_ptr<UpTreeNode<T>> root;
    Hash<UpTreeNode<T>> arr;

    int insertionIndex = 0;

    public:

    friend class UpTreeNode<T>;


    UnionFind() = default;
    ~UnionFind() = default;

    UpTreeNode<T>* makeSet(shared_ptr<T> data);
    UpTreeNode<T>* find(shared_ptr<T> data);
    UpTreeNode<T>* unionGroups(shared_ptr<UpTreeNode<T>> tree1, shared_ptr<UpTreeNode<T>> tree2);
    int highFromGround();

    UpTreeNode<T> *union_PutOnTop(shared_ptr<UpTreeNode<Record>> tree1, shared_ptr<UpTreeNode<Record>> tree2);
};

template <class T>
    UpTreeNode<T>* UnionFind<T>::makeSet(shared_ptr<T> data)
    {
        if(arr.find(*data) != NULL)
                return NULL;
        auto toAdd = make_shared<UpTreeNode>(data);
        if(arr.insert(toAdd) != NULL)
        {
            toAdd->column = insertionIndex;
            insertionIndex++;
            return toAdd;
        }
        return NULL;
    }

template <class T>
UpTreeNode<T>* UnionFind<T>::find(shared_ptr<T> data)
    {
        auto node = arr.find(*data);
        if(node != NULL)
            return NULL;

        int sumR = 0;
        int toSubtract = 0;
        // runs to find the group's root
        auto nodeToRun = node;
        while (nodeToRun->father != NULL)
        {
            // used for calculating the hight from ground:
            sumR += nodeToRun->semiHight;
            // ___________________________________

            nodeToRun = nodeToRun->father;
        }
        auto groupFather = nodeToRun;


        int tempR = 0;
        // runs up to the root and change the fathers to point on the group's root
        nodeToRun = node;
        while (nodeToRun->father != NULL)
        {
            // used for calculating the hight from ground:
            tempR = nodeToRun->semiHight;
            nodeToRun->semiHight = sumR-toSubtract;
            toSubtract += nodeToRun->semiHight;
            // ___________________________________


            auto currentFather = nodeToRun->father;
            nodeToRun->father = groupFather;
            nodeToRun = currentFather;
        }
        
        return groupFather;
    }




template <class T>
UpTreeNode<T>* UnionFind<T>::unionGroups(shared_ptr<UpTreeNode<T>> tree1, shared_ptr<UpTreeNode<T>> tree2)
    {
        if(tree1->groupCount >= tree2->groupCount)
        {
            tree2->father = make_shared<UpTreeNode>(tree1);
            tree1->groupCount += tree2->groupCount;
            tree2->groupCount = -1;
            return tree1;
        }
        else
        {
            tree1->father = make_shared<UpTreeNode>(tree2);
            tree2->groupCount += tree1->groupCount;
            tree1->groupCount = -1;
            return tree2;
        }
    }

    // TODO: high from groud for up three node
    /// @brief 
    /// @param tree1 root of the first record group
    /// @param tree2 root of the second record group
    /// @return 
    template <class T>
    UpTreeNode<T>* UnionFind<T>::union_PutOnTop(shared_ptr<UpTreeNode<Record>> tree1, shared_ptr<UpTreeNode<Record>> tree2)
    {
        
        if(tree1->groupCount >= tree2->groupCount)
        {
            tree2->father = make_shared<UpTreeNode<T>>(tree1);
            tree1->groupCount += tree2->groupCount;
            tree2->groupCount = -1;
            tree2->semiHight = tree2->semiHight + tree1->highFromGround() - tree1->semiHight;
            return tree1;
        }
        else
        {
            tree1->father = make_shared<UpTreeNode<T>>(tree2);
            tree2->groupCount += tree1->groupCount;
            tree1->groupCount = -1;
            tree2->semiHight = tree2->semiHight + tree1->highFromGround();
            tree1->semiHight = tree1->semiHight - tree2->semiHight;
            return tree2;
        }

    }



 template <class T>
    int UnionFind<T>::highFromGround()//still need to ceack if adding thr the record copies is true!!!
    {
        auto nodeToRun = this->father;
        int hight = this->semiHight;
        while (nodeToRun != NULL)
        {
            hight += nodeToRun->semiHight + nodeToRun->value->copies;
            auto currentFather = nodeToRun->father;
            nodeToRun->father = groupFather;
            nodeToRun = currentFather;
        } 
        return hight;
    }








#endif //WET2_UNIONFIND_H