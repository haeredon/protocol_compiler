//
// Created by skod on 12/15/21.
//


#include "ProtocolClass.h"
#include "BuildClass.h"
#include "Util.h"

#include <iostream>
#include <valarray>
#include <cctype>


ProtocolClass::ProtocolClass() {

}


std::string ProtocolClass::class_to_string(Class &p_class) {
    ss << "#ifndef PROTOCOL" << "_" << p_class.get_name() << "_H" << std::endl;
    ss << "#define PROTOCOL" << "_" << p_class.get_name() << "_H" << std::endl;

    ss << "#include <vector>" << std::endl;
    ss << "#include <string>" << std::endl;
    ss << "#include <cstdint>" << std::endl;
    ss << "#include <cstring>" << std::endl << std::endl;

    ss << "#include \"Util.h\"" << std::endl;
    ss << "#include \"Protocols.h\"" << std::endl;
    ss << "#include \"Config.h\"" << std::endl;
    ss << "#include \"Protocol.h\"" << std::endl << std::endl;

    ss << "namespace Tunneler {";

    ss << "class " << p_class.get_name() << " : public Protocol " << "{";

    ss << "private:" << std::endl;

    /************************** Private fields **************************************/
    ss << "struct field {"
          "uint64_t offset;"
          "uint64_t length;"
          "};";


    ss << "uint8_t* data;";
    ss << "std::size_t size;";

    for(const Field& field : p_class.get_fields()) {
        ss << "field " << field.get_name() << ";";

        for(const auto& name_to_map : field.get_bitmap().get_name_to_map()) {
            std::string range_name = std::get<0>(name_to_map);
            std::tuple<std::size_t, std::size_t> range = std::get<1>(name_to_map);;
            uint64_t mask = std::pow(2, std::get<1>(range)) + (std::pow(2, std::get<1>(range)) - std::pow(2, std::get<0>(range)));
            ss << "static const uint64_t "<< field.get_name() << "_" << range_name << "= 0x" << std::hex << mask << ";" << std::endl;
        }
    }

    for(const FieldGroup& group : p_class.get_field_groups()) {
        for(const Field& field : group.get_fields()) {
            ss << "field " << field.get_name() << ";";

            for(const auto& name_to_map : field.get_bitmap().get_name_to_map()) {
                std::string range_name = std::get<0>(name_to_map);
                std::tuple<std::size_t, std::size_t> range = std::get<1>(name_to_map);;
                uint64_t mask = std::pow(2, std::get<1>(range)) + (std::pow(2, std::get<1>(range)) - std::pow(2, std::get<0>(range)));
                ss << "static const uint64_t "<< field.get_name() << "_" << range_name << "= 0x" << std::hex << mask << ";" << std::endl;
            }
        }
    }

    /************************** Builder **************************************/

    BuildClass build_class;
    ss << build_class.class_to_string(p_class);

    /************************** Builder end **************************************/

    /************************** Private fields end **************************************/

    ss << std::endl << "public:" << std::endl;


    /*************** Constructor *********************/
    // [ProtocolName]()
    ss << p_class.get_name() << "(uint8_t* data) {";
    ss << "init(data);";
    ss << "}"; // constructor end

    // [ProtocolName](Builder& builder)
    ss << p_class.get_name() << "(Builder& builder) {";
    ss << "init(builder.get_data());";
    ss << "}";

    /*************** Constructor End *********************/

    /*************** Getters *********************/

    // Fields
    for(const Field& field : p_class.get_fields()) {
        std::string name = field.get_name();

        const std::unordered_map<std::string, std::size_t>& enums = field.get_enumeration().get_enum_to_Val();
        if(enums.size() != 0) {
            ss << "enum class " << name << "_enum" << " { ";
            for(const auto& key_pair : field.get_enumeration().get_enum_to_Val()) {
                ss << std::get<0>(key_pair) << " = 0x" << std::hex << std::get<1>(key_pair);
                ss << ", ";
            }
            ss << "UNKNOWN ";
            ss << "};";
        }

        for(const auto& name_to_map : field.get_bitmap().get_name_to_map()) {
            std::string bit_mapping_name = name + "_" + std::get<0>(name_to_map);
            ss << "uint64_t get_" << bit_mapping_name << "() {";
            ss << "return Util::to_numeric<uint64_t>(&data[" << name << ".offset], " << name << ".length) & " <<  bit_mapping_name << ";";
            ss << "}";
        }

        ss << "std::vector<uint8_t> get_" << name << "() {";
        ss << "return std::vector<uint8_t>(data + " << name << ".offset, data + " << name << ".offset + " << name << ".length);";
        ss << "}";
    }

    // Field Groups
    for(const FieldGroup& group : p_class.get_field_groups()) {

        for(const Field& field : group.get_fields()) {
            std::string name = field.get_name();

            const std::unordered_map<std::string, std::size_t>& enums = field.get_enumeration().get_enum_to_Val();
            if(enums.size() != 0) {
                ss << "enum class " << name << "_enum" << " { ";
                for(const auto& key_pair : field.get_enumeration().get_enum_to_Val()) {
                    ss << std::get<0>(key_pair) << " = 0x" << std::hex << std::get<1>(key_pair);
                    ss << ", ";
                }
                ss << "UNKNOWN ";
                ss << "};";
            }

            for(const auto& name_to_map : field.get_bitmap().get_name_to_map()) {
                std::string bit_mapping_name = name + "_" + std::get<0>(name_to_map);
                ss << "uint64_t get_" << bit_mapping_name << "() {";
                ss << "return Util::to_numeric<uint64_t>(&data[" << name << ".offset], " << name << ".length) & " <<  bit_mapping_name << ";";
                ss << "}";
            }

            ss << "std::vector<uint8_t> get_" << name << "() {";
            ss << "return std::vector<uint8_t>(data + " << name << ".offset, data + " << name << ".offset + " << name << ".length);";
            ss << "}";
        }

    }

    // Protocols get_protocol_type();
    ss << "Protocols get_protocol_type() {";
    ss << "return Protocols::" << ProtocolParser::Util::to_upper(p_class.get_name()) << ";";
    ss << "}";

    // std::string to_string();
    ss << "std::string to_string() {";
    ss << "return Util::binary_to_hex_pretty_print(data, size);";
    ss << "}";

    // std::size_t get_size();
    ss << "std::size_t get_size() {";
    ss << "return size;";
    ss << "}";

    // std::vector<uint8_t> to_data();
    ss << "std::vector<uint8_t> to_data() {";
    ss << "return std::vector<uint8_t>(data, data + size);";
    ss << "}";

    // static Builder get_builder()
    ss << "static Builder get_builder() {";
    ss << "return Builder();";
    ss << "}";

    // get_inner_protocol()
    ss << "Protocols get_inner_protocol() {";
    for(auto& field : p_class.get_next_protocol().get_priorities()) {
        const std::string& field_name = field->get_name();
        const std::unordered_map<std::string, std::size_t>& enums = field->get_enumeration().get_enum_to_Val();
        if(enums.size() != 0) {
            for(const auto& key_pair : field->get_enumeration().get_enum_to_Val()) {
                const std::string& enum_name = std::get<0>(key_pair);
                ss << "if(Util::range_equals(static_cast<std::size_t>(" << field_name << "_enum::" << enum_name << "), &data[" << field_name << ".offset], 0," << field_name << ".length)) {";
                ss << "return Protocols::" << enum_name << ";";
                ss << "}";
            }
        }
    }
    ss << "return Protocols::" << p_class.get_next_protocol().get_default_next() << ";";
    ss << "}";


    /*************** Getters End *********************/

    // void init(uint8_t* data)
    ss << "void init(uint8_t* data) {";
    ss << "uint16_t num = 0;";

    // Fields
    for(const Field& field : p_class.get_fields()) {

        if(field.get_is_included() != nullptr) {
            ss << "if(" << field.get_is_included()->to_string() << ") {";
        }

        ss << field.get_name() << ".offset = num;";
        ss << "num +=" << field.get_length()->to_string() << ";";
        ss << field.get_name() << ".length = num - " << field.get_name() << ".offset" << ";";

        if(field.get_is_included() != nullptr) {
            ss << "}";
        }
    }

    // Field Groups
    for(const FieldGroup& group : p_class.get_field_groups()) {
        ss << "{";
        ss << "uint16_t num_read = 0;";

        ss << "while(" << group.get_is_continue()->to_string() << ") {";

        bool first = true;
        for(const Field& field : group.get_fields()) {

            if(field.get_is_included() != nullptr) {
                ss << (first ? "if" : "else if") << "(" << field.get_is_included()->to_string() << ") {";
            }

            ss << field.get_name() << ".offset = num;";
            ss << "num +=" << field.get_length()->to_string() << ";";
            ss << "num_read +=" << field.get_length()->to_string() << ";";
            ss << field.get_name() << ".length = num - " << field.get_name() << ".offset" << ";";

            if(field.get_is_included() != nullptr) {
                ss << "}";
            }
        }

        ss << "}";
        ss << "}";
    }

    ss << "size = num;";
    ss << "}";

    ss << "};"; // class end
    ss << "}"; // namespace end

    ss << std::endl << "#endif /* PROTOCOL" << "_" << p_class.get_name() << "_H */" << std::endl;

    return ss.str();


}


//protocol: (Tcp)
//field: (src_port, 2)
//field: (dst_port, 2 + src_port) enum: (ARP, 1544), (IPV4, 8)
//field: (eth_802_1q_outer, 4, range_equals(0, 3, 34984))
//field: (protocol_id, 2, equals(222, dst_port, src_port))
//field: (length, 2, has_not(eth_802_1q_outer))
//field_group: (num_read < src_port)
//field: (end, 0, prefix(0))
//field: (no_op, 0, prefix(1))
//field: (max_segment_size, 4, prefix(2))
//end:
//next_protocol: (dst_port, LLC)

//Protocols get_inner_protocol() {
//    if(Util::range_equals(static_cast<std::size_t>(dst_port_enum::ARP), data[dst_port.offset], 0, dst_port.length)) {
//        return Protocols::ARP;
//    } else if(Util::range_equals(static_cast<std::size_t>(dst_port_enum::IPV4), data[dst_port.offset], 0, dst_port.length)) {
//        return Protocols::IPV4;
//    } else {
//        return Protocols::LLC;
//    }
//}


//
//    std::string get_constructor() {
//        std::stringstream class_ss;
//        std::stringstream builder_first_ss;
//        std::stringstream builder_second_ss;
//
//        typename std::vector<Field>::iterator it;
//
//        std::size_t num_consumed = 0;
//        class_ss << BaseClass::TAB << "// TODO: REMEMBER TO DO BOUNDS CHECKING" << std::endl;
//        class_ss << BaseClass::TAB << "void init(const uint8_t data[]) {" << std::endl;
//        class_ss << BaseClass::TAB << BaseClass::TAB << "std::size_t num_consumed = 0;" << std::endl;
//        class_ss << BaseClass::TAB << BaseClass::TAB << "std::size_t num_read = 0;" << std::endl << std::endl;
//
//        builder_first_ss << BaseClass::TAB << get_name() << "(Builder& builder) {" << std::endl;
//        builder_first_ss << BaseClass::TAB << BaseClass::TAB << "std::size_t num_consumed = 0;" << std::endl << std::endl;
//        builder_first_ss << BaseClass::TAB << BaseClass::TAB << "uint8_t* data = new uint8_t[" << std::endl;
//
//        for(it = fields.begin() ; it != fields.end() ; ++it) {
//            Field& field = *it;
//
//            std::string length_str;
//            std::string num_add_str;
//
//            std::string builder_length = field.get_name() + ".length";
//            length_str = parse_expr(field.get_length_exp());
//
//            if(field.is_conditional()) {
//                // Conditional field
//                const std::vector<std::string>& args = field.get_conditional().get_args();
//
//                if(field.get_conditional().get_name() == "range_equals") {
//                    class_ss << BaseClass::TAB << BaseClass::TAB << "if(Util::range_equals(" << args[2] << ", data, " << args[0] << ", " << args[1] << ")) {" << args[2] << ";" << std::endl;
//                } else if(field.get_conditional().get_name() == "equals") {
//
//                    class_ss << BaseClass::TAB << BaseClass::TAB << "if(" << std::endl;
//
//                    std::string arg_length_expr;
//
//                    for(auto it = args.begin() ; it != args.end() ; ++it) {
//                        std::string arg = *it;
//
//                        if(arg == args.back()) {
//                            break;
//                        }
//
//                        arg_length_expr = parse_expr(get_field_by_name(arg).get_length_exp());
//                        class_ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "Util::range_equals(" << args.back() << ", " << arg << ".data(), 0," << arg_length_expr << ")";
//
//                        if(*(it + 1) != args.back()) {
//                            class_ss << "&&" << std::endl;
//                        }
//                    }
//
//                    if(args.size() == 1) {
//                        class_ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "Util::range_equals(" << args.back() << ", data, 0," << arg_length_expr << ")";
//                    }
//
//                    class_ss << ") {" << std::endl;
//                } else if(field.get_conditional().get_name() == "has_not") {
//                    class_ss << BaseClass::TAB << BaseClass::TAB << "if(" << std::endl;
//
//                    for(const std::string& arg : args) {
//                        class_ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << arg << ".size() == 0";
//
//                        if(arg != args.back()) {
//                            class_ss << "&&" << std::endl;
//                        }
//                    }
//
//                    class_ss << ") {" << std::endl;
//                } else if(field.get_conditional().get_name() == "lte") {
//                    class_ss << BaseClass::TAB << BaseClass::TAB << "if(Util::to_numeric<uint_arc>(data, " << length_str << ") <= " << args[0] << ") {" << std::endl;
//                } else if(field.get_conditional().get_name() == "gt") {
//                    class_ss << BaseClass::TAB << BaseClass::TAB << "if(Util::to_numeric<uint_arc>(data, " << length_str << ") > " << args[0] << ") {" << std::endl;
//                } else {
//                    throw "Conditional function not found";
//                }
//
//                class_ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB  << "num_read = " << length_str << ";" << std::endl;
//                class_ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB  << field.get_name() << " = " << "std::vector<uint8_t>" << "(" << "data + num_consumed, data + num_consumed + num_read);" << std::endl;
//                class_ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "num_consumed += num_read;" << std::endl;
//                class_ss << BaseClass::TAB << BaseClass::TAB << "}" << std::endl << std::endl;
//            } else {
//                // Dependency field
//                class_ss << BaseClass::TAB << BaseClass::TAB << "num_read = " << length_str << ";" << std::endl;
//                class_ss << BaseClass::TAB << BaseClass::TAB << field.get_name() << " = " << "std::vector<uint8_t>" << "(" << "data + num_consumed, data + num_consumed + num_read);" << std::endl;
//                class_ss << BaseClass::TAB << BaseClass::TAB << "num_consumed += num_read;" << std::endl << std::endl;
//            }
//
//            if(it == fields.begin()) {
//                builder_first_ss << "builder." << builder_length;
//            } else {
//                builder_first_ss << " + builder." << builder_length;
//            }
//
//            builder_second_ss << BaseClass::TAB << BaseClass::TAB << "if(builder." << field.get_name() << ".initialized) {" << std::endl;
//            builder_second_ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "memcpy(data + num_consumed, builder." << field.get_name() << ".data, builder." << builder_length << ");" << std::endl;
//            builder_second_ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "num_consumed += builder." << builder_length << ";" << std::endl;
//            builder_second_ss << BaseClass::TAB << BaseClass::TAB << "}" << std::endl << std::endl;
//        }
//
//        builder_first_ss << "];" << std::endl << std::endl;
//
//        builder_second_ss << BaseClass::TAB << BaseClass::TAB << "init(data);" << std::endl;
//        builder_second_ss << BaseClass::TAB << BaseClass::TAB << "delete data;" << std::endl;
//
//        builder_second_ss << BaseClass::TAB << "}";
//
//        class_ss << BaseClass::TAB << BaseClass::TAB << "size = num_consumed;" << std::endl;
//        class_ss << BaseClass::TAB << "}" << std::endl << std::endl;
//
//        class_ss << BaseClass::TAB << get_name() << "(const uint8_t data[]) {" << std::endl;
//        class_ss << BaseClass::TAB << BaseClass::TAB << "init(data);" << std::endl;
//        class_ss << BaseClass::TAB << "}" << std::endl << std::endl;
//
//        return class_ss.str() + builder_first_ss.str() + builder_second_ss.str();
//    }