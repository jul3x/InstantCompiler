/*** BNFC-Generated Visitor Design Pattern JVMInstructionsVisitor. ***/
/* This implements the common visitor design pattern.
   Note that this method uses Visitor-traversal of lists, so
   List->accept() does NOT traverse the list. This allows different
   algorithms to use context information differently. */

#include "JVMPreprocessingVisitor.h"

void JVMPreprocessingVisitor::visitProgram(Program *t) {} //abstract class
void JVMPreprocessingVisitor::visitStmt(Stmt *t) {}       //abstract class
void JVMPreprocessingVisitor::visitExp(Exp *t) {}         //abstract class

void JVMPreprocessingVisitor::visitProg(Prog *prog)
{
    prog->liststmt_->accept(this);
}

std::pair<int, bool> JVMPreprocessingVisitor::visitSAss(SAss *sass)
{
    sass->exp_->accept(this);
    sass->difficulty_ = sass->exp_->difficulty_ + 1;
    return std::make_pair(sass->difficulty_, false);
}

std::pair<int, bool> JVMPreprocessingVisitor::visitSExp(SExp *sexp)
{
    sexp->exp_->accept(this);
    sexp->difficulty_ = sexp->exp_->difficulty_;
    return std::make_pair(sexp->difficulty_, false);
}

std::pair<int, bool> JVMPreprocessingVisitor::visitExpAdd(ExpAdd *expadd)
{
    expadd->exp_1->accept(this);
    expadd->exp_2->accept(this);

    expadd->difficulty_ = expadd->exp_1->difficulty_ + expadd->exp_2->difficulty_;
    return std::make_pair(expadd->difficulty_, false);
}

std::pair<int, bool> JVMPreprocessingVisitor::visitExpSub(ExpSub *expsub)
{
    expsub->exp_1->accept(this);
    expsub->exp_2->accept(this);

    expsub->difficulty_ = expsub->exp_1->difficulty_ + expsub->exp_2->difficulty_;
    return std::make_pair(expsub->difficulty_, false);
}

std::pair<int, bool> JVMPreprocessingVisitor::visitExpMul(ExpMul *expmul)
{
    expmul->exp_1->accept(this);
    expmul->exp_2->accept(this);

    expmul->difficulty_ = expmul->exp_1->difficulty_ + expmul->exp_2->difficulty_;
    return std::make_pair(expmul->difficulty_, false);
}

std::pair<int, bool> JVMPreprocessingVisitor::visitExpDiv(ExpDiv *expdiv)
{
    expdiv->exp_1->accept(this);
    expdiv->exp_2->accept(this);

    expdiv->difficulty_ = expdiv->exp_1->difficulty_ + expdiv->exp_2->difficulty_;
    return std::make_pair(expdiv->difficulty_, false);
}

std::pair<int, bool> JVMPreprocessingVisitor::visitExpLit(ExpLit *explit)
{
    explit->difficulty_ = 1;
    return std::make_pair(explit->difficulty_, false);
}

std::pair<int, bool> JVMPreprocessingVisitor::visitExpVar(ExpVar *expvar)
{
    expvar->difficulty_ = 1;
    return std::make_pair(expvar->difficulty_, false);
}

void JVMPreprocessingVisitor::visitListStmt(ListStmt *liststmt)
{
    for (ListStmt::iterator i = liststmt->begin(); i != liststmt->end(); ++i)
    {
        (*i)->accept(this);
    }
}

std::pair<int, bool> JVMPreprocessingVisitor::visitInteger(Integer x)
{
    return std::make_pair(0, false);
}

std::pair<int, bool> JVMPreprocessingVisitor::visitChar(Char x)
{
    return std::make_pair(0, false);
}

std::pair<int, bool> JVMPreprocessingVisitor::visitDouble(Double x)
{
    return std::make_pair(0, false);
}

std::pair<int, bool> JVMPreprocessingVisitor::visitString(String x)
{
    return std::make_pair(0, false);
}

std::pair<int, bool> JVMPreprocessingVisitor::visitIdent(Ident x)
{
    return std::make_pair(0, false);
}
