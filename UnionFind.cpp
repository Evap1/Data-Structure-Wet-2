//
// Created by Eva Poluliakhov on 18/06/2023.
//

#include "UnionFind.h"


shared_ptr<UpTreeNode> UnionFind::makeSet(shared_ptr<Record> data)
{
    if(arr.find(data->get_id()) != NULL)
        return NULL;

    shared_ptr<UpTreeNode> toAdd = make_shared<UpTreeNode>(data);

    if(arr.insert(toAdd) == StatusType::SUCCESS)
    {
        // toAdd->column = insertionIndex;
        // insertionIndex++;
        // size++;
        toAdd->column = size;
        size++;
        return toAdd;
    }
    return NULL;
}



shared_ptr<Record> UnionFind::find(int dataId)
{
    shared_ptr<UpTreeNode> node = findNode(dataId);
    if (node != NULL){
        return node->value;
    }
    return NULL;
}

shared_ptr<Record> UnionFind::findSpecified(int dataId)
{
    shared_ptr<UpTreeNode> node = arr.find(dataId);
    if (node != NULL){
        return node->value;
    }
    return NULL;
}

shared_ptr<UpTreeNode> UnionFind::findSpecifiedNode(int dataId)
{
    shared_ptr<UpTreeNode> node = arr.find(dataId);
    if (node != NULL){
        return node;
    }
    return NULL;
}



shared_ptr<UpTreeNode> UnionFind::findNode(int dataId)
{
    shared_ptr<UpTreeNode> node = arr.find(dataId);
    if(node == NULL)
        return NULL;

    int sumR = 0;
    int toSubtract = 0;
    // runs to find the group's root
    shared_ptr<UpTreeNode> nodeToRun = node;
    while (nodeToRun->father != NULL)
    {
        // used for calculating the hight from ground:
        sumR += nodeToRun->semiHight;
        // _____________

        nodeToRun = nodeToRun->father;
    }
    shared_ptr<UpTreeNode> groupFather = nodeToRun;


    int tempR = 0;
    // runs up to the root and change the fathers to point on the group's root
    nodeToRun = node;
    while (nodeToRun->father != NULL)
    {
        // used for calculating the hight from ground:
        tempR = nodeToRun->semiHight;
        nodeToRun->semiHight = sumR-toSubtract;
        toSubtract += nodeToRun->semiHight;
        // _____________


        shared_ptr<UpTreeNode> currentFather = nodeToRun->father;
        nodeToRun->father = groupFather;
        nodeToRun = currentFather;
    }

    return groupFather;
}


shared_ptr<UpTreeNode> UnionFind::unionGroups(shared_ptr<UpTreeNode> tree1, shared_ptr<UpTreeNode> tree2)
{
    if(tree1->groupCount >= tree2->groupCount)
    {
        //up tree node recive record as a parameter
        tree2->father = tree1;
        tree1->groupCount += tree2->groupCount;
        tree2->groupCount = -1;
        return tree1;
    }
    else
    {
        tree1->father = tree2;
        tree2->groupCount += tree1->groupCount;
        tree1->groupCount = -1;
        return tree2;
    }
}

///
/// \param r_id1
/// \param r_id2
/// \return nullptr in case some of the records wasnt found
shared_ptr<Record> UnionFind::union_PutOnTop(int r_id1, int r_id2)
{
    shared_ptr<UpTreeNode> record1 = findNode(r_id1);
    shared_ptr<UpTreeNode> record2 = findNode(r_id2);
    if(record1 == NULL || record2 == NULL)
        return nullptr;

    return union_PutOnTopNode(record1, record2)->value;

}


/// @brief
/// @param treeB root of the first record group
/// @param treeA root of the second record group
/// @return
shared_ptr<UpTreeNode> UnionFind::union_PutOnTopNode(shared_ptr<UpTreeNode> treeB, shared_ptr<UpTreeNode> treeA)
{
    if (treeB->groupCount <= treeA->groupCount)
    {
        treeB->semiHight = treeB->semiHight + (treeA->highFromGround() + treeA->value->get_copies()) - treeA->semiHight;
        treeA->groupCount += treeB->groupCount;
        treeB->groupCount = -1;
        treeB->father = treeA;
        treeB->column = treeA->column;
        return treeB;
    }
    else
    {
        treeB->semiHight = treeB->semiHight + (treeA->highFromGround() + treeA->value->get_copies());
        treeA->semiHight = treeA->semiHight - treeB->semiHight;
        treeA->father = treeB;
        treeB->groupCount += treeA->groupCount;
        treeA->groupCount = -1;
        treeB->column = treeA->column;
        return treeA;
    }
}
//shared_ptr<UpTreeNode> UnionFind::union_PutOnTopNode(shared_ptr<UpTreeNode> treeB, shared_ptr<UpTreeNode> treeA)
//{
//
//    if(treeB->groupCount <= treeA->groupCount)
//    {
//        treeB->father = treeA;
//        treeA->groupCount += treeB->groupCount;
//        treeB->groupCount = -1;
//        // semi hight is r funtion
//        treeB->semiHight = treeB->semiHight + treeA->highFromGround() + treeA->value->get_copies() - treeA->semiHight ;
//        treeB->column = treeA->column;
//        return treeB;
//    }
//    else
//    {
//        treeA->father = treeB;
//        treeB->groupCount += treeA->groupCount;
//        treeA->groupCount = -1;
//        treeB->semiHight = treeB->semiHight + treeA->highFromGround() + treeA->value->get_copies();
//        treeA->semiHight = treeA->semiHight - treeB->semiHight ;
//        treeB->column = treeA->column;
//        return treeA;
//    }
//}


/// @brief in use for the function getPlace.
/// @param r_id record id
/// @param column record's column
/// @param hight record's hight from ground
/// @return returns true if the function succeeded
bool UnionFind::getPlace(int r_id, int *column, int *hight)
{
    shared_ptr<UpTreeNode> recordNode = findSpecifiedNode(r_id);
    if(recordNode == NULL)
        return false;

    *column = findNode(r_id)->column;
    *hight = recordNode->highFromGround();
    return true;
}


int UnionFind::getSize() const
{
    return size;
}


//______________UpTreeNode Functions_______________

int UpTreeNode::highFromGround()//still need to ceack if adding the record copies is true!!!
{
    shared_ptr<UpTreeNode> nodeToRun = this->father;
    int hight = this->semiHight;
    while (nodeToRun != NULL)
    {
        hight += nodeToRun->semiHight + nodeToRun->value->get_copies();
        nodeToRun = nodeToRun->father;
    }
    return hight;
}

//_________________________________