////
//// Created by root on 26/07/2021.
////
//
//#ifndef PROTOCOL_COMPILER_BUILDBASECLASS_H
//#define PROTOCOL_COMPILER_BUILDBASECLASS_H
//
//#include "BaseClass.h"
//
//class BuildBaseClass : public BaseClass {
//
//protected:
//
//    std::string to_build_name;
//
//    std::string get_inheritance() {
//        return "";
//    }
//
//    std::string get_privates() {
//        std::stringstream ss;
//
//        ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "struct field {" << std::endl;
//        ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "uint8_t *data;" << std::endl;
//        ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "std::size_t length;" << std::endl;
//        ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "bool optional;" << std::endl;
//        ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "bool initialized;" << std::endl;
//        ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "" << std::endl;
//        ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "field(std::size_t length, bool optional, bool initialized) : length(length), optional(optional)," << std::endl;
//        ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "initialized(initialized) {}" << std::endl;
//        ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "};" << std::endl;
//        ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "" << std::endl << std::endl;
//
//        typename std::vector<Field>::iterator it;
//
//        for(it = fields.begin() ; it != fields.end() ; ++it) {
//            Field& field = *it;
//            ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "field "<< field.get_name() << ";" << std::endl;
//        }
//
//        return ss.str();
//    }
//
//    std::string get_constructor() {
//        std::stringstream ss;
//
//        typename std::vector<Field>::iterator it;
//        std::smatch match;
//        std::regex num_regex ("^([0-9+-/\\*]*$).*");
//
//        ss << get_name() << "() :" << std::endl;
//
//        for(it = fields.begin() ; it != fields.end() ; ++it) {
//            Field& field = *it;
//
//            std::string length_expr = parse_expr(field.get_length_exp());
//            bool depends_on_var = !std::regex_search (length_expr, match, num_regex);
//            ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << field.get_name() << "(" << (depends_on_var ? "0" : parse_expr(
//                    field.get_length_exp())) << "," << (field.is_conditional() ? "true" : "false") << ", false)" << std::endl;
//
//            if(it != --fields.end()) {
//                ss << ",";
//            }
//        }
//
//        ss << BaseClass::TAB << BaseClass::TAB << "{}" << std::endl;
//
//        return ss.str();
//    }
//
//    std::string get_getters() {
//        std::stringstream ss;
//
//        ss << BaseClass::TAB << BaseClass::TAB << to_build_name << "* " << "build() { " << std::endl;
//        ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "return new " << to_build_name << "(*this);" << std::endl;
//        ss << BaseClass::TAB << BaseClass::TAB << "}" << std::endl << std::endl;
//
//        return ss.str();
//    }
//
//    std::string get_destructor() {
//        std::stringstream ss;
//
//        typename std::vector<Field>::iterator it;
//
//        ss << "~" << get_name() << "() {" << std::endl;
//
//        for(it = fields.begin() ; it != fields.end() ; ++it) {
//            Field& field = *it;
//            ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "if(" << field.get_name() << ".initialized) {" << std::endl;
//            ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "delete " << field.get_name() << ".data;" << std::endl;
//            ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "}" << std::endl << std::endl;
//        }
//
//        ss << BaseClass::TAB << BaseClass::TAB << "}" << std::endl;
//
//        return ss.str();
//    }
//
//    std::string get_setters() {
//        std::stringstream uint8_ss;
//        std::stringstream vector_ss;
//
//        typename std::vector<Field>::iterator it;
//
//        std::smatch match;
//        std::regex num_regex ("^([0-9+-/\\*]*$).*");
//
//        for(it = fields.begin() ; it != fields.end() ; ++it) {
//            Field& field = *it;
//            std::string length_var = field.get_name() + ".length";
//
//            std::string length_expr = parse_expr(field.get_length_exp());
//            bool depends_on_var = !std::regex_search (length_expr, match, num_regex);
//
//            vector_ss << BaseClass::TAB << BaseClass::TAB << "Builder& " << "set_" << field.get_name() << "(std::vector<uint8_t> data) { " << std::endl;
//
//            if(depends_on_var) {
//                uint8_ss << BaseClass::TAB << BaseClass::TAB << "Builder& " << "set_" << field.get_name() << "(uint8_t* data, std::size_t length) { " << std::endl;
//                uint8_ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << length_var << " = length;" << std::endl;
//                vector_ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "return set_" << field.get_name() << "(data.data(), data.size());" << std::endl;
//            } else {
//                uint8_ss << BaseClass::TAB << BaseClass::TAB << "Builder& " << "set_" << field.get_name() << "(uint8_t* data) { " << std::endl;
//                vector_ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "return set_" << field.get_name() << "(data.data());" << std::endl;
//            }
//
//            uint8_ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << field.get_name() << ".data = new uint8_t[" << length_var << "];" << std::endl;
//            uint8_ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "memcpy(" << field.get_name() << ".data, data, " << length_var << ");" << std::endl;
//            uint8_ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << field.get_name() << ".initialized = true;" << std::endl;
//            uint8_ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "return *this;" << std::endl;
//
//
//            vector_ss << BaseClass::TAB << BaseClass::TAB << "}" << std::endl << std::endl;
//            uint8_ss << BaseClass::TAB << BaseClass::TAB << "}" << std::endl << std::endl;
//        }
//
//        return uint8_ss.str() + vector_ss.str();
//    }
//
//public:
//
//    void set_to_build_name(std::string name) {
//        to_build_name = name;
//    }
//
//    BuildBaseClass(std::string to_build_name, std::string name) : to_build_name(to_build_name), BaseClass(name) {}
//
//};
//
//#endif //PROTOCOL_COMPILER_BUILDBASECLASS_H
