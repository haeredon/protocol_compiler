////
//// Created by root on 26/07/2021.
////
//
//#ifndef PROTOCOL_COMPILER_BUILDCLASS_H
//#define PROTOCOL_COMPILER_BUILDCLASS_H
//
//
//#include "BuildBaseClass.h"
//
//#include<sstream>
//
//class BuildClass : public BuildBaseClass {
//
//public:
//
//
//    BuildClass(std::string name) : BuildBaseClass("Dummy", name) {
//
//    }
//
//
//
//    std::string to_string() {
//        std::stringstream ss;
//
//        if(fields.empty()) {
//            return ss.str();
//        }
//
//        ss << BaseClass::TAB << "class " << get_name() << " { " << std::endl << std::endl;
//
//        ss << BaseClass::TAB << BaseClass::TAB << "friend " << to_build_name << ";" << std::endl << std::endl;
//
//        ss << BaseClass::TAB << BaseClass::TAB << "private: " << std::endl << std::endl;
//
//        ss << this->get_privates() << std::endl << std::endl;
//
//        ss << BaseClass::TAB << BaseClass::TAB << "public:" << std::endl << std::endl;
//
//        ss << BaseClass::TAB << BaseClass::TAB  <<  this->get_constructor() << std::endl << std::endl;
//
//        ss << BaseClass::TAB << BaseClass::TAB  << this->get_destructor() << std::endl << std::endl;
//
//        ss << this->get_getters() << std::endl << std::endl;
//
//        ss << this->get_setters() << std::endl << std::endl;
//
//        ss << BaseClass::TAB << BaseClass::TAB  << "};" << std::endl << std::endl;
//
//        return ss.str();
//    }
//
//};
//
//
//
//#endif //PROTOCOL_COMPILER_BUILDCLASS_H
