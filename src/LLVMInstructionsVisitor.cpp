/*** BNFC-Generated Visitor Design Pattern for LLVM traversal. ***/
/*** BNFC was used to generate skeleton for tree traversal. ***/

#include "LLVMInstructionsVisitor.h"
#include "LLVMVariables.h"
#include "CompilerOutput.h"

void LLVMInstructionsVisitor::visitProgram(Program *t) {} //abstract class
void LLVMInstructionsVisitor::visitStmt(Stmt *t) {}       //abstract class
void LLVMInstructionsVisitor::visitExp(Exp *t) {}         //abstract class

void LLVMInstructionsVisitor::visitProg(Prog *prog)
{
    prog->liststmt_->accept(this);
}

std::pair<int, bool> LLVMInstructionsVisitor::visitSAss(SAss *sass)
{
    bool ok = false;
    std::string pointer = "";
    std::tie(ok, pointer) = LLVMVariables::getInstance().getPointer(sass->ident_);

    if (!ok)
    {
        pointer = LLVMVariables::getInstance().assignment(sass->ident_);
        CompilerOutput::getInstance().append("  %" + pointer + " = alloca i32\n");
    }

    std::pair<int, bool> r = sass->exp_->accept(this);

    if (!r.second)
    {
        unsigned int reg = LLVMVariables::getInstance().getRegister();
        CompilerOutput::getInstance().append("  %" + std::to_string(reg) + " = add i32 " + std::to_string(r.first) + ", 0\n");
        r.first = reg;
    }

    CompilerOutput::getInstance().append("  store i32 %" + std::to_string(r.first) + ", i32* %" + pointer + "\n");
    return std::make_pair(0, false);
}

std::pair<int, bool> LLVMInstructionsVisitor::visitSExp(SExp *sexp)
{
    std::pair<int, bool> r;
    r = sexp->exp_->accept(this);

    if (!r.second)
    {
        unsigned int reg = LLVMVariables::getInstance().getRegister();
        CompilerOutput::getInstance().append("  %" + std::to_string(reg) + " = add i32 " + std::to_string(r.first) + ", 0\n");
        r.first = reg;
    }

    CompilerOutput::getInstance().append("  call void @printInt(i32 %" + std::to_string(r.first) + ")\n");

    return std::make_pair(0, false);
}

std::pair<int, bool> LLVMInstructionsVisitor::visitExpAdd(ExpAdd *expadd)
{
    std::pair<int, bool> r1, r2;
    r1 = expadd->exp_1->accept(this);
    r2 = expadd->exp_2->accept(this);
    unsigned int reg = LLVMVariables::getInstance().getRegister();

    CompilerOutput::getInstance().append("  %" + std::to_string(reg) + " = add i32 " + (r1.second ? "%" : "") +
                                         std::to_string(r1.first) + ", " + (r2.second ? "%" : "") +
                                         std::to_string(r2.first) + "\n");

    return std::make_pair(reg, true);
}

std::pair<int, bool> LLVMInstructionsVisitor::visitExpSub(ExpSub *expsub)
{
    std::pair<int, bool> r1, r2;
    r1 = expsub->exp_1->accept(this);
    r2 = expsub->exp_2->accept(this);
    unsigned int reg = LLVMVariables::getInstance().getRegister();

    CompilerOutput::getInstance().append("  %" + std::to_string(reg) + " = sub i32 " + (r1.second ? "%" : "") +
                                         std::to_string(r1.first) + ", " + (r2.second ? "%" : "") +
                                         std::to_string(r2.first) + "\n");

    return std::make_pair(reg, true);
}

std::pair<int, bool> LLVMInstructionsVisitor::visitExpMul(ExpMul *expmul)
{
    std::pair<int, bool> r1, r2;
    r1 = expmul->exp_1->accept(this);
    r2 = expmul->exp_2->accept(this);
    unsigned int reg = LLVMVariables::getInstance().getRegister();

    CompilerOutput::getInstance().append("  %" + std::to_string(reg) + " = mul i32 " + (r1.second ? "%" : "") +
                                         std::to_string(r1.first) + ", " + (r2.second ? "%" : "") +
                                         std::to_string(r2.first) + "\n");

    return std::make_pair(reg, true);
}

std::pair<int, bool> LLVMInstructionsVisitor::visitExpDiv(ExpDiv *expdiv)
{
    std::pair<int, bool> r1, r2;
    r1 = expdiv->exp_1->accept(this);
    r2 = expdiv->exp_2->accept(this);
    unsigned int reg = LLVMVariables::getInstance().getRegister();

    CompilerOutput::getInstance().append("  %" + std::to_string(reg) + " = udiv i32 " + (r1.second ? "%" : "") +
                                         std::to_string(r1.first) + ", " + (r2.second ? "%" : "") +
                                         std::to_string(r2.first) + "\n");

    return std::make_pair(reg, true);
}

std::pair<int, bool> LLVMInstructionsVisitor::visitExpLit(ExpLit *explit)
{
    return visitInteger(explit->integer_);
}

std::pair<int, bool> LLVMInstructionsVisitor::visitExpVar(ExpVar *expvar)
{
    bool ok = false;
    std::string pointer = "";
    std::tie(ok, pointer) = LLVMVariables::getInstance().getPointer(expvar->ident_);

    if (!ok)
    {
        throw std::invalid_argument(
            std::string("Variable \"") + expvar->ident_ + std::string("\" used but not declared!\n"));
    }

    unsigned int reg = LLVMVariables::getInstance().getRegister();

    std::string out;

    out = "  %" + std::to_string(reg) + " = load i32, i32* %" + pointer + "\n";

    CompilerOutput::getInstance().append(out);

    return std::make_pair(reg, true);
}

void LLVMInstructionsVisitor::visitListStmt(ListStmt *liststmt)
{
    for (ListStmt::iterator i = liststmt->begin(); i != liststmt->end(); ++i)
    {
        (*i)->accept(this);
    }
}

std::pair<int, bool> LLVMInstructionsVisitor::visitInteger(Integer x)
{
    return std::make_pair(x, false);
}

std::pair<int, bool> LLVMInstructionsVisitor::visitChar(Char x)
{
    return std::make_pair(0, false);
}

std::pair<int, bool> LLVMInstructionsVisitor::visitDouble(Double x)
{
    return std::make_pair(0, false);
}

std::pair<int, bool> LLVMInstructionsVisitor::visitString(String x)
{
    return std::make_pair(0, false);
}

std::pair<int, bool> LLVMInstructionsVisitor::visitIdent(Ident x)
{
    return std::make_pair(0, false);
}
