/*** BNFC-Generated Visitor Design Pattern JVMInstructionsVisitor. ***/
/* This implements the common visitor design pattern.
   Note that this method uses Visitor-traversal of lists, so
   List->accept() does NOT traverse the list. This allows different
   algorithms to use context information differently. */

#include "JVMInstructionsVisitor.h"



void JVMInstructionsVisitor::visitProgram(Program* t) {} //abstract class
void JVMInstructionsVisitor::visitStmt(Stmt* t) {} //abstract class
void JVMInstructionsVisitor::visitExp(Exp* t) {} //abstract class

void JVMInstructionsVisitor::visitProg(Prog *prog)
{
  /* Code For Prog Goes Here */

  prog->liststmt_->accept(this);

}

void JVMInstructionsVisitor::visitSAss(SAss *sass)
{
  /* Code For SAss Goes Here */

  visitIdent(sass->ident_);
  sass->exp_->accept(this);
  printf("store\n");

}

void JVMInstructionsVisitor::visitSExp(SExp *sexp)
{
  /* Code For SExp Goes Here */

  sexp->exp_->accept(this);
  printf("printInt\n");

}

void JVMInstructionsVisitor::visitExpAdd(ExpAdd *expadd)
{
  /* Code For ExpAdd Goes Here */

  expadd->exp_1->accept(this);
  expadd->exp_2->accept(this);
  printf("iadd\n");

}

void JVMInstructionsVisitor::visitExpSub(ExpSub *expsub)
{
  /* Code For ExpSub Goes Here */

  expsub->exp_1->accept(this);
  expsub->exp_2->accept(this);
  printf("isub\n");

}

void JVMInstructionsVisitor::visitExpMul(ExpMul *expmul)
{
  /* Code For ExpMul Goes Here */

  expmul->exp_1->accept(this);
  expmul->exp_2->accept(this);
  printf("imul\n");

}

void JVMInstructionsVisitor::visitExpDiv(ExpDiv *expdiv)
{
  /* Code For ExpDiv Goes Here */

  expdiv->exp_1->accept(this);
  expdiv->exp_2->accept(this);
  printf("idiv\n");

}

void JVMInstructionsVisitor::visitExpLit(ExpLit *explit)
{
  /* Code For ExpLit Goes Here */

  visitInteger(explit->integer_);

}

void JVMInstructionsVisitor::visitExpVar(ExpVar *expvar)
{
  /* Code For ExpVar Goes Here */

  visitIdent(expvar->ident_);

}


void JVMInstructionsVisitor::visitListStmt(ListStmt* liststmt)
{
  for (ListStmt::iterator i = liststmt->begin() ; i != liststmt->end() ; ++i)
  {
    (*i)->accept(this);
  }
}


void JVMInstructionsVisitor::visitInteger(Integer x)
{
  if (x >= -1 && x <= 5)
  {
    printf("iconst_%d\n", x);
  }
  else
  {
    printf("bipush %d\n", x);
  }
}

void JVMInstructionsVisitor::visitChar(Char x)
{
  /* Code for Char Goes Here */
}

void JVMInstructionsVisitor::visitDouble(Double x)
{
  /* Code for Double Goes Here */
}

void JVMInstructionsVisitor::visitString(String x)
{
  /* Code for String Goes Here */
}

void JVMInstructionsVisitor::visitIdent(Ident x)
{
  /* Code for Ident Goes Here */
}



