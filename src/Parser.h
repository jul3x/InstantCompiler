#ifndef PARSER_HEADER_FILE
#define PARSER_HEADER_FILE

#include<vector>
#include<string>


class Program;
class Stmt;
class ListStmt;
class Exp;

typedef union
{
  int int_;
  char char_;
  double double_;
  char* string_;
  Program* program_;
  Stmt* stmt_;
  ListStmt* liststmt_;
  Exp* exp_;
} YYSTYPE;

Program* pProgram(FILE *inp);
Program* pProgram(const char *str);
Stmt* pStmt(FILE *inp);
Stmt* pStmt(const char *str);
ListStmt* pListStmt(FILE *inp);
ListStmt* pListStmt(const char *str);
Exp* pExp(FILE *inp);
Exp* pExp(const char *str);



#define _ERROR_ 258
#define _SYMB_0 259
#define _SYMB_1 260
#define _SYMB_2 261
#define _SYMB_3 262
#define _SYMB_4 263
#define _SYMB_5 264
#define _SYMB_6 265
#define _SYMB_7 266
#define _INTEGER_ 267
#define _IDENT_ 268

extern YYSTYPE yylval;

#endif
