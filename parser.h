
#include <string>
#include <stack>
#include "lexer.h"
#include "treeNode.h"
#include "TreeStandardizer.h"
#include "CSEMachine.h"

class parser
{
private:
    lexer *lex;
    token *nextToken;
    std::stack<treeNode *> treeStack;

    // Helper methods for parsing different non-terminals
    void E();
    void Ew();
    void T();
    void Ta();
    void Tc();
    void B();
    void Bt();
    void Bs();
    void Bp();
    void A();
    void At();
    void Af();
    void Ap();
    void R();
    void Rn();
    void D();
    void Da();
    void Dr();
    void Db();
    void Vb();
    void Vl();

    // Other helper methods
    // void parse();
    bool isKeyword(const std::string &value);
    void read(const std::string &tokenStr);
    void buildTree(const std::string &nodeStr, int numChildNodes, int type);
    std::string to_s(treeNode *node);

public:
    void parse();
    parser(lexer *lex);
    virtual ~parser();
    std::stack<treeNode *> getTreeStack() const;
    std::stack<treeNode *> getASTTreeStack() const;
    void preOrderTraverse(treeNode *node, int i);
    void printAST();
    void printST();
    void evaluateProgram();

    // void treePrettyPrint(treeNode *node, int level);
    // void print_string_in_treestack(std::stack<treeNode *> treeStack);
    // void print_tree(treeNode *node);
};
