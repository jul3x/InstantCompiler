#ifndef LLVM_INSTRUCTIONS_VISITOR_HEADER
#define LLVM_INSTRUCTIONS_VISITOR_HEADER

#include "Absyn.h"

class LLVMInstructionsVisitor : public Visitor
{
public:
    void visitProgram(Program *p);
    void visitStmt(Stmt *p);
    void visitExp(Exp *p);
    void visitProg(Prog *p);
    std::pair<int, bool> visitSAss(SAss *p);
    std::pair<int, bool> visitSExp(SExp *p);
    std::pair<int, bool> visitExpAdd(ExpAdd *p);
    std::pair<int, bool> visitExpSub(ExpSub *p);
    std::pair<int, bool> visitExpMul(ExpMul *p);
    std::pair<int, bool> visitExpDiv(ExpDiv *p);
    std::pair<int, bool> visitExpLit(ExpLit *p);
    std::pair<int, bool> visitExpVar(ExpVar *p);
    void visitListStmt(ListStmt *p);

    std::pair<int, bool> visitInteger(Integer x);
    std::pair<int, bool> visitChar(Char x);
    std::pair<int, bool> visitDouble(Double x);
    std::pair<int, bool> visitString(String x);
    std::pair<int, bool> visitIdent(Ident x);
};

#endif
