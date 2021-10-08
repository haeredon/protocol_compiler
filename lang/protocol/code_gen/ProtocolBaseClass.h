//
// Created by root on 26/07/2021.
//

#ifndef PROTOCOL_COMPILER_PROTOCOLBASECLASS_H
#define PROTOCOL_COMPILER_PROTOCOLBASECLASS_H

#include "BaseClass.h"
#include <stdint.h>

class ProtocolBaseClass : public BaseClass {

protected:

    std::string get_inheritance() {
        return ": public Protocol";
    }

    std::string get_privates() {
        std::stringstream ss;

        typename std::vector<Field>::iterator it;

        for(it = fields.begin() ; it != fields.end() ; ++it) {
            ss << BaseClass::TAB << "std::vector<uint8_t> "<< it->get_name() << ";" << std::endl << std::endl;

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
        class_ss << BaseClass::TAB << BaseClass::TAB << "std::size_t num_consumed = 0;" << std::endl;
        class_ss << BaseClass::TAB << BaseClass::TAB << "std::size_t num_read = 0;" << std::endl << std::endl;

        builder_first_ss << BaseClass::TAB << get_name() << "(Builder& builder) {" << std::endl;
        builder_first_ss << BaseClass::TAB << BaseClass::TAB << "std::size_t num_consumed = 0;" << std::endl << std::endl;
        builder_first_ss << BaseClass::TAB << BaseClass::TAB << "uint8_t* data = new uint8_t[" << std::endl;

        bool has_prev_conditional = false;

        for(it = fields.begin() ; it != fields.end() ; ++it) {
            Field& field = *it;

            bool depends_on_var = !std::regex_search (field.get_second(), match, num_regex);

            std::string length_str;
            std::string num_add_str;

            std::string builder_length = field.get_name() + ".length";

            if(depends_on_var) {
                length_str = "Util::flip_endian(Util::to_numeric<uint8_t>(" + field.get_second() + ".data()))"; // TODO: not only uint8_t!!!!
            } else {
                length_str = std::to_string(stoi(field.get_second()));
            }

            if(field.is_conditional()) {
                // Conditional field
                std::vector<std::string>& args = field.get_conditional_args();

                if(field.get_conditional_name() == "range_equals") {
                    class_ss << BaseClass::TAB << BaseClass::TAB << "if(Util::range_equals(" << args[2] << ", data, " << args[0] << ", " << args[1] << ")) {" << args[2] << ";" << std::endl;
                } else if(field.get_conditional_name() == "equals") {

                    class_ss << BaseClass::TAB << BaseClass::TAB << "if(" << std::endl;

                    for(auto it = args.begin() ; it != args.end() ; ++it) {
                        std::string arg = *it;

                        if(arg == args.back()) {
                            break;
                        }

                        class_ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "Util::range_equals(" << args.back() << ", " << arg << ", 0," << length_str << ")";

                        if(*(it + 1) != args.back()) {
                            class_ss << "&&" << std::endl;
                        }
                    }

                    if(args.size() == 1) {
                        class_ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "Util::range_equals(" << args.back() << ", data, 0," << length_str << ")";
                    }

                    class_ss << ") {" << std::endl;
                } else if(field.get_conditional_name() == "has_not") {
                    class_ss << BaseClass::TAB << BaseClass::TAB << "if(" << std::endl;

                    for(std::string& arg : args) {
                        class_ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << arg << ".size() == 0";

                        if(arg != args.back()) {
                            class_ss << "&&" << std::endl;
                        }
                    }

                    class_ss << ") {" << std::endl;
                } else if(field.get_conditional_name() == "lte") {
                    class_ss << BaseClass::TAB << BaseClass::TAB << "if(Util::to_numeric<uint_arc>(data) <= " << args[0] << ") {" << std::endl;
                } else if(field.get_conditional_name() == "gt") {
                    class_ss << BaseClass::TAB << BaseClass::TAB << "if(Util::to_numeric<uint_arc>(data) > " << args[0] << ") {" << std::endl;
                } else {
                    throw "Conditional function not found";
                }

                class_ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB  << "num_read = " << length_str << ";" << std::endl;
                class_ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB  << field.get_name() << " = " << "std::vector<uint8_t>" << "(" << "data + num_consumed, data + num_consumed + num_read);" << std::endl;
                class_ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "num_consumed += num_read;" << std::endl;
                class_ss << BaseClass::TAB << BaseClass::TAB << "}" << std::endl << std::endl;

                has_prev_conditional = true;
            } else {
                // Dependency field
                class_ss << BaseClass::TAB << BaseClass::TAB << "num_read = " << length_str << ";" << std::endl;
                class_ss << BaseClass::TAB << BaseClass::TAB << field.get_name() << " = " << "std::vector<uint8_t>" << "(" << "data + num_consumed, data + num_consumed + num_read);" << std::endl;
                class_ss << BaseClass::TAB << BaseClass::TAB << "num_consumed += num_read;" << std::endl << std::endl;
            }

            if(it == fields.begin()) {
                builder_first_ss << "builder." << builder_length;
            } else {
                builder_first_ss << " + builder." << builder_length;
            }

            builder_second_ss << BaseClass::TAB << BaseClass::TAB << "memcpy(data + num_consumed, builder." << field.get_name() << ".data, builder." << builder_length << ");" << std::endl;
            builder_second_ss << BaseClass::TAB << BaseClass::TAB << "num_consumed += builder." << builder_length << ";" << std::endl << std::endl;
        }

        builder_first_ss << "];" << std::endl << std::endl;

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
        std::stringstream to_data_ss;

        to_data_ss << BaseClass::TAB <<  "std::vector<uint8_t> to_data() {" << std::endl;
        to_data_ss << BaseClass::TAB << BaseClass::TAB << "std::vector<uint8_t> data;" << std::endl;
        to_data_ss << BaseClass::TAB << BaseClass::TAB << "data.reserve(size);" << std::endl << std::endl;

        typename std::vector<Field>::iterator val_it;

        std::string lowest_inner_priority_name = "";
        std::size_t lowest_inner_priority = SIZE_MAX;
        for(val_it = fields.begin() ; val_it != fields.end() ; ++val_it) {
            std::size_t inner_priority = val_it->get_inner().priority;
            if(val_it->get_inner().is_inner && inner_priority < lowest_inner_priority) {
                lowest_inner_priority_name = val_it->get_name();
                lowest_inner_priority = inner_priority;
            }
        }

        // Value fields
        for(val_it = fields.begin() ; val_it != fields.end() ; ++val_it) {
            std::unordered_map<std::string, std::tuple<std::size_t, std::size_t>>& bitmap = val_it->get_bitmap();
            std::unordered_map<std::string, std::size_t>& enumeration = val_it->get_enumeration();

            to_data_ss << BaseClass::TAB << BaseClass::TAB << "data.insert(data.end(), " << val_it->get_name() << ".begin(), " << val_it->get_name() << ".end());" << std::endl;

            if(!bitmap.empty()) {
                for(auto it = bitmap.begin() ; it != bitmap.end() ; ++it) {
                    ss << BaseClass::TAB << "uint_arc " << "get_" << val_it->get_name() << "_" << it->first << "() { " << std::endl;
                    ss << BaseClass::TAB << BaseClass::TAB << "return Util::to_numeric<uint_arc>(" << val_it->get_name() << ".data) & " << val_it->get_name() << "_" << it->first << ";" << std::endl;
                    ss << BaseClass::TAB << "}" << std::endl << std::endl;
                }
            }

            if(!enumeration.empty()) {
                bool is_inner = val_it->get_inner().is_inner && val_it->get_name() == lowest_inner_priority_name;
                std::string return_type = is_inner ? "Protocols" : val_it->get_name() + "_enum";
                std::string method_name = is_inner ? "get_inner_protocol" : "get_" + val_it->get_name() + "_enum";

                ss << BaseClass::TAB << return_type << " " << method_name << "() { " << std::endl;
                ss << BaseClass::TAB << BaseClass::TAB << "std::size_t numeric_" << val_it->get_name() << " = 0;" << std::endl;
                ss << BaseClass::TAB << BaseClass::TAB << "memcpy(&numeric_" << val_it->get_name() << ", " << val_it->get_name() << ".data(), " << val_it->get_name() << ".size());" << std::endl;


                for(auto it = enumeration.begin() ; it != enumeration.end() ; ++it) {
                    ss << BaseClass::TAB << BaseClass::TAB << "if(static_cast<std::size_t>(" << val_it->get_name() << "_enum" << "::" << it->first << ") == numeric_" << val_it->get_name() << ") {" << std::endl;
                    ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "return " << return_type << "::" << it->first << ";" << std::endl;
                    ss << BaseClass::TAB << BaseClass::TAB << "}" << std::endl;
                }
                ss << BaseClass::TAB << BaseClass::TAB << "return Protocols::UNKNOWN;" << std::endl;
                ss << BaseClass::TAB << "}" << std::endl << std::endl;

                ss << BaseClass::TAB << "const std::vector<uint8_t>& " << "get_" << val_it->get_name() << "() { " << std::endl;
                ss << BaseClass::TAB << BaseClass::TAB << "return " << val_it->get_name() << ";" << std::endl;
                ss << BaseClass::TAB << "}" << std::endl << std::endl;
            } else {
                ss << BaseClass::TAB << "const std::vector<uint8_t>& " << "get_" << val_it->get_name() << "() { " << std::endl;
                ss << BaseClass::TAB << BaseClass::TAB << "return " << val_it->get_name() << ";" << std::endl;
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

        ss << BaseClass::TAB << "static Builder " << "get_builder() { " << std::endl;
        ss << BaseClass::TAB << BaseClass::TAB << "return Builder();" << std::endl;
        ss << BaseClass::TAB << "}" << std::endl << std::endl;

        ss << BaseClass::TAB << "std::string " << "to_string() { " << std::endl;
        ss << BaseClass::TAB << BaseClass::TAB << "return Util::binary_to_hex_pretty_print(to_data().data(), size);" << std::endl;
        ss << BaseClass::TAB << "}" << std::endl << std::endl;

        to_data_ss << BaseClass::TAB << BaseClass::TAB << "return data;" << std::endl;
        to_data_ss << BaseClass::TAB << "}" << std::endl << std::endl;

        return ss.str() + to_data_ss.str();
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
