#ifndef LLVM_VARIABLES_HEADER
#define LLVM_VARIABLES_HEADER

#include <unordered_map>
#include <string>

class LLVMVariables
{
public:
    LLVMVariables(const LLVMVariables&) = delete;
    LLVMVariables& operator=(const LLVMVariables&) = delete;

    static LLVMVariables& getInstance() {
        static LLVMVariables instance;
        return instance;
    }

    // Function returns pair of <bool, unsigned int>
    // Bool determines if variable has been already declared
    // std::string returns register of variable pointer (appropriate if variables has been declared)
    std::pair<bool, std::string> getPointer(const std::string &name) const {
        auto it = pointers_.find(name);

        if (it == pointers_.end())
        {
            return std::make_pair(false, "");
        }

        return std::make_pair(true, it->second);
    }

    // Function returns unsigned int value
    // std::string& determines pointer that is connected with variable name
    std::string assignment(const std::string &name) {
        auto pointer = name + "_p";
        pointers_.emplace(name, pointer);

        return pointer;
    }

    // If new register is needed it generates new
    unsigned int getRegister() {
        return ++max_register_;
    }

private:
    LLVMVariables() {
        max_register_ = 0;
    }

    std::unordered_map<std::string, std::string> pointers_;
    unsigned int max_register_;
};

#endif
