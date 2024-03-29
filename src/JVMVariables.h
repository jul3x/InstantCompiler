#ifndef JVM_VARIABLES_HEADER
#define JVM_VARIABLES_HEADER

#include <unordered_map>
#include <string>

class JVMVariables
{
public:
    JVMVariables(const JVMVariables&) = delete;
    JVMVariables& operator=(const JVMVariables&) = delete;

    static JVMVariables& getInstance() {
        static JVMVariables instance;
        return instance;
    }

    // Function returns pair of <bool, unsigned int>
    // Bool determines if variable has been already declared
    // Int returns index of variable (appropriate if variables has been declared)
    std::pair<bool, unsigned int> getIndex(const std::string &name) const {
        auto it = vars_.find(name);

        if (it == vars_.end())
        {
            return std::make_pair(false, 0);
        }

        return std::make_pair(true, it->second);
    }

    // Function returns unsigned int value
    // Int determines index that is connected with variable name
    unsigned int assignment(const std::string &name) {
        auto currently = getIndex(name);
        if (currently.first)
        {
            return currently.second;
        }

        vars_.emplace(name, ++max_index_);

        return max_index_;
    }

    void modifyStack(short int diff) {
        current_stack_ += diff;

        max_stack_ = std::max(current_stack_, max_stack_);
    }

    const unsigned int getMaxIndex() const {
        return max_index_;
    }

    const unsigned int getMaxStack() const {
        return max_stack_;
    }

private:
    JVMVariables() {
        max_index_ = 0;
        max_stack_ = 0;
        current_stack_ = 0;
    }

    std::unordered_map<std::string, unsigned int> vars_;
    unsigned int max_index_;
    unsigned int max_stack_;
    unsigned int current_stack_;
};

#endif
