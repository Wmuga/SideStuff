//
// Created by Alex on 09.08.2020.
//

#ifndef CALCULUS
#define CALCULUS


#include <map>
#include <fstream>
#include <vector>
#include <sstream>
#include "binary_tree.h"

class calculator{
    std::map<std::string,double> variables;
    char* act_symbols = (char*)"_+-*/=";
    size_t iteration;
    std::stringstream _sin;

    enum actions {VAR=0,SUM='+',SUB='-',DIV='/',MUL='*'};
    struct var{
        actions act;
        double val;
    };
    binary_tree<var> tree;
    actions cur_act;
public:
    calculator(const std::string&);
    ~calculator();

private:
    void calculate();
    std::string get_name();
    void set_variables();
    double get_value();
    std::vector<std::string> split_by(const std::string&,char);
    std::string to_lower(const std::string& str_in);
    void build_tree();
    double tree_get(binary_tree<var>::leaf);
};

#endif //CALCULUS_CALC_H
