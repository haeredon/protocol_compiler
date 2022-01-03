//
// Created by skod on 12/15/21.
//


#include "ProtocolClass.h"

#include <iostream>
#include <valarray>


ProtocolClass::ProtocolClass() {

}


std::string ProtocolClass::class_to_string(Class &p_class) {
    ss << "#ifndef PROTOCOL" << "_" << p_class.get_name() << "_H" << std::endl;
    ss << "#define PROTOCOL" << "_" << p_class.get_name() << "_H" << std::endl;

    ss << "#include <vector>" << std::endl;
    ss << "#include <string>" << std::endl;
    ss << "#include <cstring>" << std::endl << std::endl;

    ss << "#include \"Util.h\"" << std::endl;
    ss << "#include \"Protocols.h\"" << std::endl;
    ss << "#include \"Config.h\"" << std::endl;
    ss << "#include \"Protocol.h\"" << std::endl << std::endl;

    ss << "namespace Tunneler {";

    ss << "class " << p_class.get_name() << " : public Protocol " << "{";

    ss << "private:" << std::endl;

    /************************** Private fields **************************************/
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

    /************************** Private fields end **************************************/

    ss << std::endl << "public:" << std::endl;


    /*************** Constructor *********************/
    ss << std::endl << p_class.get_name() << "() {" << std::endl;
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
    ss << "}"; // constructor end
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
            ss << "return Util::to_numeric<uint64_t>(data[" << name << ".offset], " << name << ".length) & " <<  bit_mapping_name << ";";
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
                ss << "return Util::to_numeric<uint64_t>(data[" << name << ".offset], " << name << ".length) & " <<  bit_mapping_name << ";";
                ss << "}";
            }

            ss << "std::vector<uint8_t> get_" << name << "() {";
            ss << "return std::vector<uint8_t>(data + " << name << ".offset, data + " << name << ".offset + " << name << ".length);";
            ss << "}";
        }

    }

    // Protocols get_protocol_type();
    ss << "Protocols get_protocol_type() {";
    ss << "return Protocols::" << p_class.get_name() << ";";
    ss << "}";

    // std::string to_string();
    ss << "std::string to_string() {";
    ss << "Util::binary_to_hex_pretty_print(data, size);";
    ss << "}";

    // std::size_t get_size();
    ss << "std::size_t get_size() {";
    ss << "return size;";
    ss << "}";

    // std::vector<uint8_t> to_data();
    ss << "std::vector<uint8_t> to_data() {";
    ss << "return std::vector<uint8_t>(data, data + size);";
    ss << "}";

    // get_inner_protocol()
    ss << "Protocols get_inner_protocol {";
    for(auto& field : p_class.get_next_protocol().get_priorities()) {
        const std::string& field_name = field->get_name();
        const std::unordered_map<std::string, std::size_t>& enums = field->get_enumeration().get_enum_to_Val();
        if(enums.size() != 0) {
            for(const auto& key_pair : field->get_enumeration().get_enum_to_Val()) {
                const std::string& enum_name = std::get<0>(key_pair);
                ss << "if(Util::range_equals(static_cast<std::size_t>(" << field_name << "_enum::" << enum_name << "), data[" << field_name << ".offset], 0," << field_name << ".length)) {";
                ss << "return Protocols::" << enum_name << ";";
                ss << "}";
            }
        }
    }
    ss << "return Protocols::" << p_class.get_next_protocol().get_default_next() << ";";
    ss << "}";


    /*************** Getters End *********************/


    ss << "};"; // class end
    ss << "}"; // namespace end

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