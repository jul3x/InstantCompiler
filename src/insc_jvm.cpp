#include <cstdio>
#include <stdexcept>
#include "Parser.h"
#include "Printer.h"
#include "Absyn.h"
#include "JVMInstructionsVisitor.h"
#include "CompilerOutput.h"

int main(int argc, char **argv)
{
    FILE *input;
    if (argc > 1)
    {
        input = fopen(argv[1], "r");
        if (!input)
        {
            fprintf(stderr, "Error opening input file.\n");
            exit(1);
        }
    }
    else
    {
        fprintf(stderr, "No input file provided.\n");
        exit(1);
    }

    ListStmt *parse_tree = pListStmt(input);
    if (parse_tree)
    {
        try
        {
            std::string out_file(std::string(argv[1]) + ".j");
            CompilerOutput::getInstance().initialize(out_file.c_str());
            CompilerOutput::getInstance().printLine(
                ".class public Main\n"
                ".super java/lang/Object\n"
                ".method public <init>()V\n"
                "  .limit stack 1\n"
                "  .limit locals 1\n"
                "  aload_0\n"
                "  invokespecial java/lang/Object/<init>()V\n"
                "  return\n"
                ".end method\n"
                ".method public static main([Ljava/lang/String;)V\n"
                "  .limit stack 1000\n"
                "  .limit locals 1\n");

            JVMInstructionsVisitor instructions_visitor;
            instructions_visitor.visitListStmt(parse_tree);

            CompilerOutput::getInstance().printLine(
                "  return\n"
                ".end method");

            CompilerOutput::getInstance().deinitialize();

            printf("Compiling successful!\n");

            return 0;
        }
        catch (std::invalid_argument &e)
        {
            fprintf(stderr, e.what());
            CompilerOutput::getInstance().destroy();

            return 1;
        }

    }

    return 1;
}
