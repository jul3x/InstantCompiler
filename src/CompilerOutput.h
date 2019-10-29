#ifndef COMPILER_OUTPUT_HEADER
#define COMPILER_OUTPUT_HEADER

#include <stdio.h>

class CompilerOutput
{
public:
    CompilerOutput(const CompilerOutput&) = delete;
    CompilerOutput& operator=(const CompilerOutput&) = delete;

    static CompilerOutput& getInstance() {
        static CompilerOutput instance;
        return instance;
    }

    void initialize(const char *filename) {
        filename_ = filename;
        out_file_ = fopen(filename, "w");
    }

    void deinitialize() {
        fclose(out_file_);
    }

    void printLine(const char *line) {
        fprintf(out_file_, line);
    }

    void destroy() {
        deinitialize();
        remove(filename_);
    }

private:
    CompilerOutput() = default;

    FILE *out_file_;
    const char *filename_;
};

#endif
