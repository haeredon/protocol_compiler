//
// Created by root on 26/07/2021.
//

#ifndef PROTOCOL_COMPILER_PROTOCOLBASECLASS_H
#define PROTOCOL_COMPILER_PROTOCOLBASECLASS_H

#include "BaseClass.h"

class ProtocolBaseClass : public BaseClass {

protected:

    std::string get_inheritance() {
        return ": public Protocol";
    }

    std::string get_privates() {
        std::stringstream ss;

        typename std::vector<Field>::iterator it;

        for(it = fields.begin() ; it != fields.end() ; ++it) {
            ss << BaseClass::TAB << "Bitmap "<< it->get_name() << ";" << std::endl << std::endl;

            std::unordered_map<std::string, std::tuple<std::size_t, std::size_t>>& bitmap = it->get_bitmap();
            std::unordered_map<std::string, std::size_t>& enumeration = it->get_enumeration();

            std::unordered_map<std::string, std::tuple<std::size_t, std::size_t>>::iterator bitmap_it;
            for(bitmap_it = bitmap.begin() ; bitmap_it != bitmap.end() ; ++bitmap_it) {
                std::string range_name = (*bitmap_it).first;
                std::tuple<std::size_t, std::size_t> range = (*bitmap_it).second;
                uint64_t mask = std::pow(2, std::get<1>(range)) + (std::pow(2, std::get<1>(range)) - std::pow(2, std::get<0>(range)));
                ss << BaseClass::TAB << "static const uint_arc "<< it->get_name() << "_" << range_name << "= 0x" << std::hex << mask << ";" << std::endl;
            }

            if(!enumeration.empty()) {
                ss << BaseClass::TAB << "enum class " << it->get_name() << "_enum" << " { ";

                for(auto e_it = enumeration.begin() ; e_it != enumeration.end() ; ++e_it) {
                    if(e_it != enumeration.begin()) {
                        ss << ", ";
                    }

                    ss << e_it->first << " = 0x" << std::hex << e_it->second;
                }

                ss << "};";
            }

            ss << std::endl << std::endl;
        }

        ss << BaseClass::TAB << "std::size_t size;" << std::endl;

        return ss.str();
    }

    std::string get_constructor() {
        std::stringstream class_ss;
        std::stringstream builder_first_ss;
        std::stringstream builder_second_ss;

        typename std::vector<Field>::iterator it;

        std::smatch match;
        std::regex num_regex ("^([0-9]*$).*");

        std::size_t num_consumed = 0;
        class_ss << BaseClass::TAB << "// TODO: REMEMBER TO DO BOUNDS CHECKING" << std::endl;
        class_ss << BaseClass::TAB << "void init(const uint8_t data[]) {" << std::endl;
        class_ss << BaseClass::TAB << BaseClass::TAB << "std::size_t num_consumed = 0;" << std::endl << std::endl;

        builder_first_ss << BaseClass::TAB << get_name() << "(Builder& builder) {" << std::endl;
        builder_first_ss << BaseClass::TAB << BaseClass::TAB << "uint8_t* data = new uint8_t[" << std::endl;


        for(it = fields.begin() ; it != fields.end() ; ++it) {
            Field& field = *it;

            bool depends_on_var = !std::regex_search (field.get_second(), match, num_regex);

            std::string length_str;
            std::string num_add_str;

            std::string builder_length = field.get_name() + "_length";

            if(depends_on_var) {
                length_str = "BitUtility::bytes_to_bits(" + field.get_second() + ".get_data())";
                num_add_str = field.get_second() + ".get_data()";
            } else {
                length_str = std::to_string(stoi(field.get_second()) * 8);
                num_add_str = field.get_second();
            }

            if(field.is_conditional()) {
                // Conditional field
                std::string contain_data_str = field.get_name() + "_contain_data";
                std::string contain_mask_str = field.get_name() + "_contain_mask";

                class_ss << BaseClass::TAB << BaseClass::TAB << "uint_arc " << contain_data_str << " = 0;" << std::endl;
                class_ss << BaseClass::TAB << BaseClass::TAB << "uint_arc " << contain_mask_str << " = " << std::hex << field.get_second() << ";" << std::endl;
                class_ss << BaseClass::TAB << BaseClass::TAB << "memcpy(&" << contain_data_str << ", data, sizeof(uint_arc));" << std::endl;

                class_ss << BaseClass::TAB << BaseClass::TAB << "if(BitUtility::binary_sub_match(" << contain_data_str << "," << contain_mask_str << ")) {" << std::endl;
                class_ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << field.get_name() << " = " << "Bitmap" << "(" << "data + num_consumed" << ", " << length_str << ");" << std::endl;
                class_ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "num_consumed += " << num_add_str << ";" << std::endl;
                class_ss << BaseClass::TAB << BaseClass::TAB << "}" << std::endl << std::endl;
            } else {
                // Dependency field
                class_ss << BaseClass::TAB << BaseClass::TAB << field.get_name() << " = " << "Bitmap" << "(" << "data + num_consumed" << ", " << length_str << ");" << std::endl;
                class_ss << BaseClass::TAB << BaseClass::TAB << "num_consumed += " << num_add_str << ";" << std::endl << std::endl;
            }

            if(it == fields.begin()) {
                builder_first_ss << "builder." << builder_length;
            } else {
                builder_first_ss << " + builder." << builder_length;
            }

            builder_second_ss << BaseClass::TAB << BaseClass::TAB << "memcpy(data , builder." << field.get_name() << ", builder." << builder_length << ");" << std::endl;
        }

        builder_first_ss << "];";

        builder_second_ss << BaseClass::TAB << BaseClass::TAB << "init(data);" << std::endl;
        builder_second_ss << BaseClass::TAB << BaseClass::TAB << "delete data;" << std::endl;

        builder_second_ss << BaseClass::TAB << "}";

        class_ss << BaseClass::TAB << BaseClass::TAB << "size = num_consumed;" << std::endl;
        class_ss << BaseClass::TAB << "}" << std::endl << std::endl;

        class_ss << BaseClass::TAB << get_name() << "(const uint8_t data[]) {" << std::endl;
        class_ss << BaseClass::TAB << BaseClass::TAB << "init(data);" << std::endl;
        class_ss << BaseClass::TAB << "}" << std::endl << std::endl;

        return class_ss.str() + builder_first_ss.str() + builder_second_ss.str();
    }

    std::string get_getters() {
        std::stringstream ss;

        typename std::vector<Field>::iterator val_it;

        // Value fields
        for(val_it = fields.begin() ; val_it != fields.end() ; ++val_it) {
            std::unordered_map<std::string, std::tuple<std::size_t, std::size_t>>& bitmap = val_it->get_bitmap();
            std::unordered_map<std::string, std::size_t>& enumeration = val_it->get_enumeration();

            if(!bitmap.empty()) {
                for(auto it = bitmap.begin() ; it != bitmap.end() ; ++it) {
                    ss << BaseClass::TAB << "uint_arc " << "get_" << val_it->get_name() << "_" << it->first << "() { " << std::endl;
                    ss << BaseClass::TAB << BaseClass::TAB << "return " << val_it->get_name() << ".get_mask(" << val_it->get_name() << "_" << it->first << ");" << std::endl;
                    ss << BaseClass::TAB << "}" << std::endl << std::endl;
                }
            }

            if(!enumeration.empty()) {
                std::string return_type = val_it->is_inner() ? "Protocols" : val_it->get_name() + "_enum";
                std::string method_name = val_it->is_inner() ? "get_inner_protocol" : "get_" + val_it->get_name() + "_enum";

                ss << BaseClass::TAB << return_type << " " << method_name << "() { " << std::endl;

                for(auto it = enumeration.begin() ; it != enumeration.end() ; ++it) {
                    ss << BaseClass::TAB << BaseClass::TAB << "if(static_cast<uint_arc>(" << val_it->get_name() << "_enum" << "::" << it->first << ") == " << val_it->get_name() << ".get_data()) {" << std::endl;
                    ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "return " << return_type << "::" << it->first << ";" << std::endl;
                    ss << BaseClass::TAB << BaseClass::TAB << "}" << std::endl;
                }
                ss << BaseClass::TAB << BaseClass::TAB << "return Protocols::UNKNOWN;" << std::endl;
                ss << BaseClass::TAB << "}" << std::endl << std::endl;

                ss << BaseClass::TAB << "uint_arc " << "get_" << val_it->get_name() << "() { " << std::endl;
                ss << BaseClass::TAB << BaseClass::TAB << "return " << val_it->get_name() << ".get_data();" << std::endl;
                ss << BaseClass::TAB << "}" << std::endl << std::endl;
            } else {
                ss << BaseClass::TAB << "uint_arc " << "get_" << val_it->get_name() << "() { " << std::endl;
                ss << BaseClass::TAB << BaseClass::TAB << "return " << val_it->get_name() << ".get_data();" << std::endl;
                ss << BaseClass::TAB << "}" << std::endl << std::endl;
            }
        }

        ss << BaseClass::TAB << "std::size_t " << "get_size() { " << std::endl;
        ss << BaseClass::TAB << BaseClass::TAB << "return size;" << std::endl;
        ss << BaseClass::TAB << "}" << std::endl << std::endl;

        std::string name_upper = name;
        std::transform(name.begin(), name.end(), name_upper.begin(), ::toupper);

        ss << BaseClass::TAB << "Protocols " << "get_protocol_type() { " << std::endl;
        ss << BaseClass::TAB << BaseClass::TAB << "return Protocols::" << name_upper << ";" << std::endl;
        ss << BaseClass::TAB << "}" << std::endl << std::endl;

        ss << BaseClass::TAB << "Builder " << "get_builder() { " << std::endl;
        ss << BaseClass::TAB << BaseClass::TAB << "return Builder();" << std::endl;
        ss << BaseClass::TAB << "}" << std::endl << std::endl;



        return ss.str();
    }

    std::string get_setters() {
        return "";
    }

    std::string get_destructor() {
        return "";
    }

    ProtocolBaseClass(std::string name) : BaseClass(name) {}

};

#endif //PROTOCOL_COMPILER_PROTOCOLBASECLASS_H
