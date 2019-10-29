#include <cstdio>
#include <stdexcept>
#include "Parser.h"
#include "Printer.h"
#include "Absyn.h"
#include "JVMInstructionsVisitor.h"
#include "CompilerOutput.h"
#include "Utils.h"

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
            std::string in_file(argv[1]);
            auto slash_iter = in_file.find_last_of('/');
            auto dot_iter = in_file.find_last_of('.');

            std::string directory = slash_iter == std::string::npos ? "." : in_file.substr(0, slash_iter);
            std::string class_name = in_file.substr(slash_iter + 1,
                (dot_iter == std::string::npos ? in_file.length() : dot_iter) - slash_iter - 1);
            std::string out_file = directory + "/" + class_name + ".j";

            CompilerOutput::getInstance().initialize(out_file.c_str());

            if (!parseFilename(class_name))
            {
                throw std::invalid_argument("Invalid filename!\n");
            }

            CompilerOutput::getInstance().print(
                ".class public ");
            CompilerOutput::getInstance().print(
                (class_name + "\n").c_str());
            CompilerOutput::getInstance().print(
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
                "  .limit locals 3\n");

            JVMInstructionsVisitor instructions_visitor;
            instructions_visitor.visitListStmt(parse_tree);

            CompilerOutput::getInstance().print(
                "  return\n"
                ".end method\n");

            CompilerOutput::getInstance().deinitialize();

            printf("Compiling successful!\n");
            printf("Generated %s.j and %s.class files in %s directory.\n",
                class_name.c_str(), class_name.c_str(), directory.c_str()   );

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
