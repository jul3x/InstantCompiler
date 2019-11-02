#ifndef COMPILER_OUTPUT_HEADER
#define COMPILER_OUTPUT_HEADER

#include <fstream>

class CompilerOutput
{
public:
    CompilerOutput(const CompilerOutput&) = delete;
    CompilerOutput& operator=(const CompilerOutput&) = delete;

    static CompilerOutput& getInstance() {
        static CompilerOutput instance;
        return instance;
    }

    void initialize(const std::string &filename) {
        filename_ = filename;
        out_file_.open(filename);
    }

    void deinitialize() {
        out_file_.close();
        output_.clear();
        filename_ = "";
    }

    void append(const std::string &new_line) {
        output_ = output_ + new_line;
    }

    void save() {
        out_file_ << output_;
    }

    void print(const std::string &what) {
        out_file_ << what;
    }

    void destroy() {
        deinitialize();
        remove(filename_.c_str());
    }

private:
    CompilerOutput() = default;

    std::ofstream out_file_;
    std::string filename_;
    std::string output_;
};

#endif
