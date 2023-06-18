

#ifndef WET2_UNIONFIND_H
#define WET2_UNIONFIND_H

#include "utilesWet2.h"
#include <memory>
#include "Record.h"
#include "Hash.h"

using namespace std;


class UpTreeNode
{
public:
    int groupCount;
    shared_ptr<Record> value;
    shared_ptr<UpTreeNode> father;

    // added to the basic union find:
    int semiHight;
    int column;

    explicit UpTreeNode(shared_ptr<Record> Value): groupCount(1), value(Value), father(NULL), semiHight(0), column(0){}
    ~UpTreeNode() = default;

    int get_id() const {
        return value->get_id();
    }

    int highFromGround();

};


class UnionFind
{
private:
    shared_ptr<UpTreeNode> root;
    Hash<UpTreeNode> arr;
    int insertionIndex = 0;
    int size = 0;

public:
    friend class UpTreeNode;

    UnionFind() = default;
    ~UnionFind() = default;

    shared_ptr<UpTreeNode> makeSet(shared_ptr<Record> data);
    shared_ptr<UpTreeNode> findNode(int dataId);
    shared_ptr<UpTreeNode> unionGroups(shared_ptr<UpTreeNode> tree1, shared_ptr<UpTreeNode> tree2);

    int getSize() const;

    shared_ptr<Record> find(int dataId);
    shared_ptr<Record> union_PutOnTop(int r_id1, int r_id2);
    shared_ptr<UpTreeNode> union_PutOnTopNode(shared_ptr<UpTreeNode> tree1, shared_ptr<UpTreeNode> tree2);

    bool getPlace(int r_id, int *column, int *hight);

    // UpTreeNode* find(int data);

};



#endif //WET2_UNIONFIND_H