/*** BNFC-Generated Visitor Design Pattern JVMInstructionsVisitor. ***/
/* This implements the common visitor design pattern.
   Note that this method uses Visitor-traversal of lists, so
   List->accept() does NOT traverse the list. This allows different
   algorithms to use context information differently. */

#include "JVMVariables.h"
#include "JVMInstructionsVisitor.h"
#include "CompilerOutput.h"

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

    std::string out;

    if (index <= 3)
    {
        out = "  istore_" + std::to_string(index) + "\n";
    }
    else
    {
        out = "  istore " + std::to_string(index) + "\n";
    }

    CompilerOutput::getInstance().print(out.c_str());
}

void JVMInstructionsVisitor::visitSExp(SExp *sexp)
{
    CompilerOutput::getInstance().print("  getstatic java/lang/System/out Ljava/io/PrintStream;\n");
    sexp->exp_->accept(this);
    CompilerOutput::getInstance().print("  invokevirtual java/io/PrintStream/println(I)V\n");
}

void JVMInstructionsVisitor::visitExpAdd(ExpAdd *expadd)
{
    expadd->exp_1->accept(this);
    expadd->exp_2->accept(this);
    CompilerOutput::getInstance().print("  iadd\n");
}

void JVMInstructionsVisitor::visitExpSub(ExpSub *expsub)
{
    expsub->exp_1->accept(this);
    expsub->exp_2->accept(this);
    CompilerOutput::getInstance().print("  isub\n");
}

void JVMInstructionsVisitor::visitExpMul(ExpMul *expmul)
{
    expmul->exp_1->accept(this);
    expmul->exp_2->accept(this);
    CompilerOutput::getInstance().print("  imul\n");
}

void JVMInstructionsVisitor::visitExpDiv(ExpDiv *expdiv)
{
    expdiv->exp_1->accept(this);
    expdiv->exp_2->accept(this);
    CompilerOutput::getInstance().print("  idiv\n");
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
            std::string("Variable \"") + expvar->ident_ + std::string("\" used but not declared!\n"));
    }

    std::string out;

    if (index <= 3)
    {
        out = "  iload_" + std::to_string(index) + "\n";
    }
    else
    {
        out = "  iload " + std::to_string(index) + "\n";
    }

    CompilerOutput::getInstance().print(out.c_str());
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
    std::string out;
    if (x >= 0 && x <= 5)
    {
        out = "  iconst_" + std::to_string(x) + "\n";
    }
    else if (x == -1)
    {
        out = "  iconst_m1\n";
    }
    else if (x <= 127 && x >= -127)
    {
        out = "  bipush " + std::to_string(x) + "\n";
    }
    else
    {
        out = "  sipush " + std::to_string(x) + "\n";
    }

    CompilerOutput::getInstance().print(out.c_str());
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
