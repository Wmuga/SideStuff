#include "calc.h"
#include <algorithm>
#include <iostream>
#include <cctype>

calculator::calculator(const std::string& sin):iteration(0) {
    for (const std::string& str : split_by(sin,';')) {
        _sin.clear();
        _sin.str(to_lower(str));
        if (iteration==0 && !str.empty()) set_variables();
        if (iteration) calculate();
        iteration++;
    }
}



double calculator::get_value() {
    if (isalpha(_sin.get())) {
        _sin.unget();
        std::string _name = get_name();
        return variables[_name];
    }
    _sin.unget();
    std::string buffer_value;
    while(std::find(act_symbols,act_symbols+6,_sin.get())==act_symbols+6 and !_sin.eof())
    {
        _sin.unget();
        char symb = _sin.get();
        if (!isalpha(symb) and symb!=-1) buffer_value+=symb;
        else
        {
            _sin.unget();
            break;
        }
    }
    _sin.unget();
    cur_act=VAR;
    return atof(buffer_value.c_str());
}


std::string calculator::get_name()
{
    std::string name;
    while(std::find(act_symbols,act_symbols+6,_sin.get())==act_symbols+6 and !_sin.eof())
    {
        _sin.unget(); if (_sin.get()==-1) {_sin.unget();break;}
        _sin.unget();
        name+=(char)_sin.get();
    }
    _sin.unget();
    return name;
}


std::vector<std::string> calculator::split_by(const std::string& in,char delim) {
    std::vector<std::string> str_ar;
    std::string acts;
    for (char c : in)
    {
        if (c==delim) {str_ar.push_back(acts);acts="";}
        else acts+=c;
    }
    if (!acts.empty()) str_ar.push_back(acts);
    return str_ar;
}

void calculator::calculate() {
    tree.destroy_current(tree.goto_head());
    tree.change_head(tree.create_Node(var(), nullptr));
    build_tree();
    double result=tree_get(tree.goto_head());
    std::string res = "result"; res+=((char)iteration+'0');
    std::cout << res<< " = " << result<<std::endl;
    variables[res] = result;
}

void calculator::set_variables() {
    while(!_sin.eof())
    {
        if (_sin.get()!=' ') {
            _sin.unget();
            std::string name = get_name();
            if (name.empty()) break;
            _sin.get();
            variables[name] = get_value();
        }
    }
}

std::string calculator::to_lower(const std::string& str_in) {
    std::string res;
    for (char c : str_in) {
        res += (isalpha(c)) ? tolower(c) : c;
    };
    return res;
}

void calculator::build_tree() {
    auto cur = tree.goto_head();
    double v = get_value();
    tree.insert_c(cur,{VAR,v});
    while(!_sin.eof()) {
        char symb = _sin.get();
        if (symb == -1) break;
        double cur_val = 0;
        if (isalpha(symb) or isdigit(symb)) {
            _sin.unget();
            cur_val = get_value();
            auto buffer = cur;
            while (buffer->next_r != nullptr) buffer = buffer->next_r;
            tree.insert_r(buffer, {VAR, cur_val});
        } else {
            cur_act = static_cast<actions>(symb);
            switch (cur_act) {
                case SUB:
                case SUM: {
                    binary_tree<var>::leaf _leaf = tree.create_Node({cur_act, 0}, nullptr);
                    cur->prev = _leaf;
                    _leaf->next_l = cur;
                    cur = _leaf;
                }
                    break;
                case DIV:
                case MUL: {
                    binary_tree<var>::leaf _leaf = tree.create_Node({cur_act, 0}, nullptr);
                    if (cur->value.act == VAR) {
                        _leaf->next_l=cur;
                        cur->prev=_leaf;
                        cur=_leaf;
                    } else {

                        _leaf->prev = cur;
                        _leaf->next_l = cur->next_r;
                        cur->next_r = _leaf;
                    }
                    break;
                }
            }
        }
    }
    tree.change_head(cur);
}

double calculator::tree_get(binary_tree<var>::leaf cur) {
    switch (cur->value.act) {

        case VAR:
            return(cur->value.val);
        case SUM:
            return (tree_get(cur->next_l)+tree_get(cur->next_r));
        case SUB:
            return (tree_get(cur->next_l)-tree_get(cur->next_r));
        case DIV:
            return (tree_get(cur->next_l)/tree_get(cur->next_r));
        case MUL:
            return (tree_get(cur->next_l)*tree_get(cur->next_r));
    }
    return 0;
}

calculator::~calculator() = default;
