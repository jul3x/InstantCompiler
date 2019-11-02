#include <cstdio>
#include <stdexcept>
#include <experimental/filesystem>
#include "Parser.h"
#include "Absyn.h"
#include "LLVMInstructionsVisitor.h"
#include "LLVMVariables.h"
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
            printf("Parse successful!\n");

            std::string directory, class_name, out_file;
            std::tie(directory, class_name, out_file) = generateOutNames(argv[1], "ll");

            CompilerOutput::getInstance().initialize(out_file);

            if (!parseFilename(class_name))
            {
                throw std::invalid_argument("Invalid filename!\n");
            }

            CompilerOutput::getInstance().print(
                "declare void @printInt(i32)\n"
                "define i32 @main() {\n");

            LLVMInstructionsVisitor instructions_visitor;
            instructions_visitor.visitListStmt(parse_tree);

            CompilerOutput::getInstance().save();

            CompilerOutput::getInstance().print(
                "  ret i32 0\n"
                "}\n");

            CompilerOutput::getInstance().deinitialize();

            printf("Compiling successful!\n");
            printf("Generated: %s/%s.ll\n",
                directory.c_str(), class_name.c_str());

            std::string exec_param = argv[0];
            auto last_slash_iter = exec_param.find_last_of('/');
            std::string relative_directory_exec =
                last_slash_iter == std::string::npos ? exec_param : exec_param.substr(0, last_slash_iter);
            std::string asm_command =
                "llvm-as " + directory + "/" + class_name + ".ll";
            std::string linker_command =
                "llvm-link -o " + directory + "/" + class_name + ".bc "
                + directory + "/" + class_name + ".bc " + relative_directory_exec + "/lib/runtime.bc ";

            std::system(asm_command.c_str());
            std::system(linker_command.c_str());

            printf("Generated: %s/%s.bc\n",
                directory.c_str(), class_name.c_str());

            return 0;
        }
        catch (std::invalid_argument &e)
        {
            fprintf(stderr, e.what());
            CompilerOutput::getInstance().save();
            CompilerOutput::getInstance().deinitialize();
            // CompilerOutput::getInstance().destroy();

            return 1;
        }

    }

    return 1;
}
