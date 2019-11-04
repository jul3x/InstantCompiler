/*** BNFC-Generated Visitor Design Pattern for JVM. ***/
/*** BNFC was used to generate skeleton for tree traversal. ***/

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

std::pair<int, bool> JVMInstructionsVisitor::visitSAss(SAss *sass)
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

    JVMVariables::getInstance().modifyStack(-1);

    CompilerOutput::getInstance().append(out);
    return std::make_pair(0, false);
}

std::pair<int, bool> JVMInstructionsVisitor::visitSExp(SExp *sexp)
{
    CompilerOutput::getInstance().append("  getstatic java/lang/System/out Ljava/io/PrintStream;\n");
    JVMVariables::getInstance().modifyStack(1);
    sexp->exp_->accept(this);
    CompilerOutput::getInstance().append("  invokevirtual java/io/PrintStream/println(I)V\n");
    JVMVariables::getInstance().modifyStack(-2);

    return std::make_pair(0, false);
}

std::pair<int, bool> JVMInstructionsVisitor::visitExpAdd(ExpAdd *expadd)
{
    if (expadd->exp_1->difficulty_ >= expadd->exp_2->difficulty_)
    {
        expadd->exp_1->accept(this);
        expadd->exp_2->accept(this);
    }
    else
    {
        expadd->exp_2->accept(this);
        expadd->exp_1->accept(this);
    }

    CompilerOutput::getInstance().append("  iadd\n");
    JVMVariables::getInstance().modifyStack(-1);

    return std::make_pair(0, false);
}

std::pair<int, bool> JVMInstructionsVisitor::visitExpSub(ExpSub *expsub)
{
    if (expsub->exp_1->difficulty_ >= expsub->exp_2->difficulty_)
    {
        expsub->exp_1->accept(this);
        expsub->exp_2->accept(this);
    }
    else
    {
        expsub->exp_2->accept(this);
        expsub->exp_1->accept(this);
        CompilerOutput::getInstance().append("  swap\n");
    }

    CompilerOutput::getInstance().append("  isub\n");
    JVMVariables::getInstance().modifyStack(-1);

    return std::make_pair(0, false);
}

std::pair<int, bool> JVMInstructionsVisitor::visitExpMul(ExpMul *expmul)
{
    if (expmul->exp_1->difficulty_ >= expmul->exp_2->difficulty_)
    {
        expmul->exp_1->accept(this);
        expmul->exp_2->accept(this);
    }
    else
    {
        expmul->exp_2->accept(this);
        expmul->exp_1->accept(this);
    }

    CompilerOutput::getInstance().append("  imul\n");
    JVMVariables::getInstance().modifyStack(-1);

    return std::make_pair(0, false);
}

std::pair<int, bool> JVMInstructionsVisitor::visitExpDiv(ExpDiv *expdiv)
{
    if (expdiv->exp_1->difficulty_ >= expdiv->exp_2->difficulty_)
    {
        expdiv->exp_1->accept(this);
        expdiv->exp_2->accept(this);
    }
    else
    {
        expdiv->exp_2->accept(this);
        expdiv->exp_1->accept(this);
        CompilerOutput::getInstance().append("  swap\n");
    }

    CompilerOutput::getInstance().append("  idiv\n");
    JVMVariables::getInstance().modifyStack(-1);

    return std::make_pair(0, false);
}

std::pair<int, bool> JVMInstructionsVisitor::visitExpLit(ExpLit *explit)
{
    visitInteger(explit->integer_);

    return std::make_pair(0, false);
}

std::pair<int, bool> JVMInstructionsVisitor::visitExpVar(ExpVar *expvar)
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

    CompilerOutput::getInstance().append(out);
    JVMVariables::getInstance().modifyStack(1);

    return std::make_pair(0, false);
}

void JVMInstructionsVisitor::visitListStmt(ListStmt *liststmt)
{
    for (ListStmt::iterator i = liststmt->begin(); i != liststmt->end(); ++i)
    {
        (*i)->accept(this);
    }
}

std::pair<int, bool> JVMInstructionsVisitor::visitInteger(Integer x)
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
    else if (x <= 32767 && x >= -32767)
    {
        out = "  sipush " + std::to_string(x) + "\n";
    }
    else
    {
        out = "  ldc " + std::to_string(x) + "\n";
    }

    CompilerOutput::getInstance().append(out);
    JVMVariables::getInstance().modifyStack(1);

    return std::make_pair(0, false);
}

std::pair<int, bool> JVMInstructionsVisitor::visitChar(Char x)
{
    return std::make_pair(0, false);
}

std::pair<int, bool> JVMInstructionsVisitor::visitDouble(Double x)
{
    return std::make_pair(0, false);
}

std::pair<int, bool> JVMInstructionsVisitor::visitString(String x)
{
    return std::make_pair(0, false);
}

std::pair<int, bool> JVMInstructionsVisitor::visitIdent(Ident x)
{
    return std::make_pair(0, false);
}
