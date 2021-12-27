//
// Created by skod on 12/12/21.
//

#include "FunctionExpr.h"
#include<sstream>

void FunctionExpr::add_arg(Expression* expression) {
    args.push_back(expression);
}

std::string FunctionExpr::to_string() {
    std::stringstream ss;

    if(name == "range_equals") {
        ss << "Util::range_equals(" << args[2]->to_string() << ", data, " << args[0]->to_string() << ", " << args[1]->to_string() << ");";
//        static bool range_equals(uint64_t num, const uint8_t* data, std::size_t start, std::size_t length);
//        range_equals(0, 3, 33024)
        return ss.str();
    } else if(name == "equals") {
//        class_ss << BaseClass::TAB << BaseClass::TAB << "if(" << std::endl;
//
//        for(auto it = args.begin() ; it != args.end() ; ++it) {
//            std::string arg = *it;
//
//            if(arg == args.back()) {
//                break;
//            }
//
//            class_ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "Util::range_equals(" << args.back() << ", " << arg << ", 0," << length_str << ")";
//
//            if(*(it + 1) != args.back()) {
//                class_ss << "&&" << std::endl;
//            }
//        }
//
//        if(args.size() == 1) {
//            class_ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "Util::range_equals(" << args.back() << ", data, 0," << length_str << ")";
//        }
//
//        class_ss << ") {" << std::endl;
        return ss.str();
    } else if(name == "has_not") {
//        class_ss << BaseClass::TAB << BaseClass::TAB << "if(" << std::endl;
//
//        for(std::string& arg : args) {
//            class_ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << arg << ".size() == 0";
//
//            if(arg != args.back()) {
//                class_ss << "&&" << std::endl;
//            }
//        }
//
//        class_ss << ") {" << std::endl;
        return ss.str();
    } else if(name == "prefix") {
        return ss.str();
    }

    throw "No matching function";
}

void FunctionExpr::set_name(const std::string &name) {
    this->name = name;
}
