#include "TreeStandardizer.h"
#include <iostream>
#include <queue>

TreeStandardizer::TreeStandardizer(treeNode *topNode)
{

    standardize(topNode);
}

TreeStandardizer::~TreeStandardizer()
{
}

void TreeStandardizer::standardizeLET(treeNode *topNode)
{
    // std::cout << "Standardizing LET" << std::endl;
    treeNode *p;

    if (treeNode::BINDING != topNode->childNode->type)
    {
        printf("Subtree not standardised: case LET");
    }

    topNode->type = treeNode::GAMMA;
    topNode->nodeString = "gamma";
    topNode->childNode->type = treeNode::LAMBDA;
    topNode->childNode->nodeString = "lambda";
    p = topNode->childNode->siblingNode;
    topNode->childNode->siblingNode = topNode->childNode->childNode->siblingNode;
    topNode->childNode->childNode->siblingNode = p;
}

void TreeStandardizer::standardizeWHERE(treeNode *topNode)
{
    // std::cout << "Standardizing WHERE" << std::endl;
    treeNode *p, *x, *e;
    if (treeNode::BINDING != topNode->childNode->siblingNode->type)
    {
        printf("Subtree not standardised: case WHERE");
    };
    topNode->type = treeNode::GAMMA;
    topNode->nodeString = "gamma";
    p = topNode->childNode;
    x = topNode->childNode->siblingNode->childNode;
    e = topNode->childNode->siblingNode->childNode->siblingNode;
    p->siblingNode = NULL;
    x->siblingNode = NULL;
    topNode->childNode = new treeNode();
    topNode->childNode->type = treeNode::LAMBDA;
    topNode->childNode->nodeString = "lambda";
    topNode->childNode->siblingNode = e;
    topNode->childNode->childNode = x;
    x->siblingNode = p;
}

void TreeStandardizer::standardizeWITHIN(treeNode *topNode)
{
    treeNode *x1, *x2, *e1;
    if (treeNode::BINDING != topNode->childNode->type || treeNode::BINDING != topNode->childNode->siblingNode->type)
    {
        printf("Subtree not standardised: case WITHIN");
    };
    topNode->type = treeNode::BINDING;
    x1 = topNode->childNode->childNode;
    x2 = topNode->childNode->siblingNode->childNode;
    e1 = x1->siblingNode;
    x1->siblingNode = x2->siblingNode;
    x2->siblingNode = new treeNode();
    x2->siblingNode->type = treeNode::GAMMA;
    x2->siblingNode->nodeString = "gamma";
    x2->siblingNode->childNode = new treeNode();
    x2->siblingNode->childNode->type = treeNode::LAMBDA;
    x2->siblingNode->childNode->nodeString = "lambda";
    x2->siblingNode->childNode->siblingNode = e1;
    x2->siblingNode->childNode->childNode = x1;
    topNode->childNode = x2;
}

void TreeStandardizer::standardizeREC(treeNode *topNode)
{
    // std::cout << "Standardizing REC" << std::endl;
    treeNode *x, *x2, *e, *temp;
    if (treeNode::BINDING != topNode->childNode->type)
    {
        printf("Subtree not standardised: case REC");
    };
    topNode->type = treeNode::BINDING;
    x = topNode->childNode->childNode;
    e = topNode->childNode->childNode->siblingNode;
    x->siblingNode = NULL;
    topNode->childNode = x; // removing the reference to the old = node
    temp = new treeNode();
    temp->type = treeNode::GAMMA;
    temp->nodeString = "gamma";
    x->siblingNode = temp;
    temp->childNode = new treeNode();
    temp->childNode->type = treeNode::YSTAR;
    temp->childNode->nodeString = "<Y*>";
    temp->childNode->siblingNode = new treeNode();
    temp->childNode->siblingNode->type = treeNode::LAMBDA;
    temp->childNode->siblingNode->nodeString = "lambda";
    temp->childNode->siblingNode->childNode = new treeNode();
    temp->childNode->siblingNode->childNode->type = x->type;
    temp->childNode->siblingNode->childNode->nodeString = x->nodeString;
    temp->childNode->siblingNode->childNode->siblingNode = e;
}

void TreeStandardizer::standardizeFCNFORM(treeNode *topNode)
{
    // std::cout << "Standardizing FCNFORM" << std::endl;
    treeNode *temp, *newNode, *e, *v;
    topNode->type = treeNode::BINDING;
    topNode->nodeString = "=";
    temp = topNode->childNode;
    while (temp->siblingNode->siblingNode != NULL)
    {
        newNode = new treeNode();
        newNode->type = treeNode::LAMBDA;
        newNode->nodeString = "lambda";
        newNode->childNode = temp->siblingNode;
        temp->siblingNode = newNode;
        temp = newNode->childNode;
    }
}

void TreeStandardizer::standardizeLAMBDA(treeNode *topNode)
{
    treeNode *temp, *newNode;

    temp = topNode->childNode;
    while (temp->siblingNode->siblingNode != NULL)
    {
        newNode = new treeNode();
        newNode->type = treeNode::LAMBDA;
        newNode->nodeString = "lambda";
        newNode->childNode = temp->siblingNode;
        temp->siblingNode = newNode;
        temp = temp->siblingNode;
    }
}

void TreeStandardizer::standardizeAND(treeNode *topNode)
{
    treeNode *temp;
    treeNode *tauNode, *commaNode, **currentTau, **currentComma;

    topNode->type = treeNode::BINDING;
    topNode->nodeString = "=";
    temp = topNode->childNode;
    tauNode = new treeNode();
    commaNode = new treeNode();
    tauNode->type = treeNode::TAU;
    tauNode->nodeString = "tau";
    tauNode->childNode = NULL;
    tauNode->siblingNode = NULL;
    commaNode->type = treeNode::COMMA;
    commaNode->nodeString = ",";
    commaNode->childNode = NULL;
    commaNode->siblingNode = NULL;
    topNode->childNode = commaNode;
    topNode->childNode->siblingNode = tauNode;
    currentTau = &(tauNode->childNode);
    currentComma = &(commaNode->childNode);
    while (temp != NULL)
    {
        *currentTau = temp->childNode->siblingNode;
        temp->childNode->siblingNode = NULL;
        *currentComma = temp->childNode;
        temp = temp->siblingNode;
        currentComma = &((*currentComma)->siblingNode); // Can your code BE any more UGLY?
        currentTau = &((*currentTau)->siblingNode);
    }
}

void TreeStandardizer::standardize(treeNode *node)
{
    // Base case: If node is null, return
    // std::cout << "Current top node  :  " << node->nodeString << std::endl;
    treeNode *p, *e, *e1, *e2, *x, *x1, *x2, *n, *temp, *new_temp;
    string origString = node->nodeString;

    if (node->childNode != NULL)
        standardize(node->childNode);
    if (node->siblingNode != NULL)
        standardize(node->siblingNode);

    switch (node->type)
    {
    case treeNode::LET:
        standardizeLET(node);
        break;
    case treeNode::WHERE:
        standardizeWHERE(node);
        break;
    case treeNode::WITHIN:
    {
        standardizeWITHIN(node);
        break;
    }
    case treeNode::REC:
    {
        standardizeREC(node);
        break;
    }
    case treeNode::FCN_FORM:
    {
        standardizeFCNFORM(node);
        break;
    }
    case treeNode::LAMBDA:
        standardizeLAMBDA(node);
        break;
    case treeNode::AND:
        standardizeAND(node);
        break;

    default:
        if (0)
            printf("Nothing to do. TopNode is %s\n", origString.c_str());
    }
    if (0)
        printf("Done with node %s\n", origString.c_str());
}