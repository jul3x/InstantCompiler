/*** BNFC-Generated Visitor Design Pattern JVMInstructionsVisitor. ***/
/* This implements the common visitor design pattern.
   Note that this method uses Visitor-traversal of lists, so
   List->accept() does NOT traverse the list. This allows different
   algorithms to use context information differently. */

#include "JVMVariables.h"
#include "JVMInstructionsVisitor.h"

void JVMInstructionsVisitor::visitProgram(Program *t) {} //abstract class
void JVMInstructionsVisitor::visitStmt(Stmt *t) {}       //abstract class
void JVMInstructionsVisitor::visitExp(Exp *t) {}         //abstract class

void JVMInstructionsVisitor::visitProg(Prog *prog)
{
    prog->liststmt_->accept(this);
}

void JVMInstructionsVisitor::visitSAss(SAss *sass)
{
    sass->exp_->accept(this);

    unsigned int index = JVMVariables::getInstance().assignment(sass->ident_);

    if (index <= 3)
    {
        printf("  istore_%d\n", index);
    }
    else
    {
        printf("  istore %d\n", index);
    }
}

void JVMInstructionsVisitor::visitSExp(SExp *sexp)
{
    printf("  getstatic java/lang/System/out Ljava/io/PrintStream;\n");
    sexp->exp_->accept(this);
    printf("  invokevirtual java/io/PrintStream/println(I)V\n");
}

void JVMInstructionsVisitor::visitExpAdd(ExpAdd *expadd)
{
    expadd->exp_1->accept(this);
    expadd->exp_2->accept(this);
    printf("  iadd\n");
}

void JVMInstructionsVisitor::visitExpSub(ExpSub *expsub)
{
    expsub->exp_1->accept(this);
    expsub->exp_2->accept(this);
    printf("  isub\n");
}

void JVMInstructionsVisitor::visitExpMul(ExpMul *expmul)
{
    expmul->exp_1->accept(this);
    expmul->exp_2->accept(this);
    printf("  imul\n");
}

void JVMInstructionsVisitor::visitExpDiv(ExpDiv *expdiv)
{
    expdiv->exp_1->accept(this);
    expdiv->exp_2->accept(this);
    printf("  idiv\n");
}

void JVMInstructionsVisitor::visitExpLit(ExpLit *explit)
{
    visitInteger(explit->integer_);
}

void JVMInstructionsVisitor::visitExpVar(ExpVar *expvar)
{
    bool ok = false;
    unsigned int index = 0;
    std::tie(ok, index) = JVMVariables::getInstance().getIndex(expvar->ident_);

    if (!ok)
    {
        throw std::invalid_argument(
            std::string("Variable \"") + expvar->ident_ + std::string("\" used but not declared!"));
    }

    if (index <= 3)
    {
        printf("  iload_%d\n", index);
    }
    else
    {
        printf("  iload %d\n", index);
    }
}

void JVMInstructionsVisitor::visitListStmt(ListStmt *liststmt)
{
    for (ListStmt::iterator i = liststmt->begin(); i != liststmt->end(); ++i)
    {
        (*i)->accept(this);
    }
}

void JVMInstructionsVisitor::visitInteger(Integer x)
{
    if (x >= 0 && x <= 5)
    {
        printf("  iconst_%d\n", x);
    }
    else if (x == -1)
    {
        printf("  iconst_m1\n");
    }
    else if (x <= 127 && x >= -127)
    {
        printf("  bipush %d\n", x);
    }
    else
    {
        printf("  sipush %d\n", x);
    }
}

void JVMInstructionsVisitor::visitChar(Char x)
{
}

void JVMInstructionsVisitor::visitDouble(Double x)
{
}

void JVMInstructionsVisitor::visitString(String x)
{
}

void JVMInstructionsVisitor::visitIdent(Ident x)
{
}
