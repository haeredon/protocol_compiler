//
// Created by skod on 14/06/2021.
//

#ifndef PARSER_GRAMMARDEFS_H
#define PARSER_GRAMMARDEFS_H

#include "../../Grammar.h"
#include "../../GrammarToken.h"
#include "../../ParserAction.h"
#include "../../Node.h"
#include "Tokens.h"

#include<vector>
#include<climits>


namespace ProtocolParser {

    class GrammarDefs {

    public:

        static std::vector<Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>> PRODUCTIONS;


    };


    std::vector<Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>> GrammarDefs::PRODUCTIONS = {
            // S --> definition                                 : S.val = definition.val
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::START_TOKEN,
            std::vector<GrammarToken> { Tokens::DEF_TOKEN },
            [](auto stack) {},
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();

                    stack[1].add_value(syn.get_values().front());
                }
            }),

            // definition --> protocol termination definition   : S.val = protocol_def(protocol.val, definition.val)
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::DEF_TOKEN,
            std::vector<GrammarToken> { Tokens::PRO_TOKEN, Tokens::TER_TOKEN, Tokens::DEF_TOKEN },
            [](auto stack) {
                ParserAction<Node*>& act = stack.front();

                stack[5].add_inherits(act.get_inherits());
            },
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();

                    stack[3].add_inherits(syn.get_values());
                    stack[3].add_inherits(syn.get_inherits());
                },
                [](auto stack) {},
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();

                    stack[1].add_value(syn.get_values().front());
                }
            }),

            // definition --> epsilon                           : S.val = epsilon
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::DEF_TOKEN,
            std::vector<GrammarToken> { Tokens::Tokens::EPS_TOKEN },
            [](auto stack) {
                ParserAction<Node*>& act = stack.front();

                stack[1].add_inherits(act.get_inherits());
            },
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();
                    std::vector<Node*> inherits = syn.get_inherits();

                    Node* top = new Node(nullptr, "CLASS SEQUENCE");

                    std::vector<Node*>::iterator it;

                    for(it = inherits.begin() ; it != inherits.end() ; ++it) {
                        top->add_child(*it);
                    }

                    stack[1].add_value(top);
                }
            }),

            // termination --> '-' termination                  : S.val = epsilon
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::TER_TOKEN,
            std::vector<GrammarToken> { Tokens::DASH_TOKEN, Tokens::TER_TOKEN },
            [](auto stack) {},
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {},
                        [](auto stack) {}
            }),

            // termination --> epsilon                          : S.val = epsilon
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::TER_TOKEN,
            std::vector<GrammarToken> { Tokens::Tokens::EPS_TOKEN },
            [](auto stack) {},
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {}
            }),

            // protocol --> 'protocol:' '(' ID ')' stmt_1       : S.val = epsilon
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::PRO_TOKEN,
            std::vector<GrammarToken> { Tokens::PROTOCOL_TOKEN, Tokens::LEFT_PAR_TOKEN, Tokens::ID_TOKEN, Tokens::RIGHT_PAR_TOKEN, Tokens::STMT_1_TOKEN },
            [](auto stack) {},
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {},
                        [](auto stack) {},
                        [](auto stack) {
                            ParserAction<Node*>& syn = stack.front();

                            stack[4].add_value(syn.get_values().front());
                        },
                        [](auto stack) {},
                        [](auto stack) {
                            ParserAction<Node*>& syn = stack.front();
                            std::vector<Node*> values = syn.get_values();

                            Node* top = new Node(nullptr, "CLASS");
                            Node* name = new Node(nullptr, "NAME");
                            Node* fields = new Node(nullptr, "FIELDS");
                            Node* properties = new Node(nullptr, "PROPERTIES");

                            name->add_child(values[0]);
                            top->add_child(name);
                            top->add_child(fields);
                            top->add_child(properties);

                            std::vector<Node*>::iterator it;
                            for(it = ++values.begin() ; it != values.end() ; ++it) {
                                Node* node = (*it);
                                if(node->get_value() != "PROPERTY") {
                                    fields->add_child(*it);
                                } else {
                                    properties->add_child(*it);
                                }

                            }

                            stack[1].add_value(top);
                        }
            }),

            // stmt_2 -> stmt_3
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::STMT_2_TOKEN,
            std::vector<GrammarToken> { Tokens::STMT_3_TOKEN },
            [](auto stack) {},
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();

                    stack[1].add_value(syn.get_values().front());
                }
            }),

            // stmt_2 -> 'switch:' '(' expr ')' case_list 'end:'
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::STMT_2_TOKEN,
            std::vector<GrammarToken> {Tokens::SWITCH_TOKEN, Tokens::LEFT_PAR_TOKEN, Tokens::EXPR_TOKEN, Tokens::RIGHT_PAR_TOKEN, Tokens::CASE_LIST, Tokens::END_TOKEN },
            [](auto stack) {},
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {},
                [](auto stack) {},
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();

                    stack[4].add_value(syn.get_values().front());
                },
                [](auto stack) {},
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();
                    std::vector<Node*> values = syn.get_values();

                    Node* top = new Node(nullptr, "SWITCH");

                    top->add_child(values.front());
                    top->add_child(values.back());

                    stack[3].add_value(top);
                },
                [](auto stack) {}
            }),

            // stmt_3 -> 'field:' '(' string ',' expr optional ')' bitmap enum
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::STMT_3_TOKEN,
            std::vector<GrammarToken> {Tokens::FIELD_TOKEN, Tokens::Tokens::LEFT_PAR_TOKEN, Tokens::Tokens::ID_TOKEN, Tokens::Tokens::COMMA_TOKEN, Tokens::Tokens::EXPR_TOKEN, Tokens::OPTIONAL_TOKEN, Tokens::Tokens::RIGHT_PAR_TOKEN, Tokens::Tokens::BITMAP_TOKEN, Tokens::Tokens::ENUM_TOKEN },
            [](auto stack) {},
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {},
                [](auto stack) {},
                [](auto stack) {
                    // ID
                    ParserAction<Node*>& syn = stack.front();

                    stack[12].add_value(syn.get_values().front());
                },
                [](auto stack) {},
                [](auto stack) {
                    // expr
                    ParserAction<Node*>& syn = stack.front();

                    stack[8].add_value(syn.get_values().front());
                },
                [](auto stack) {
                    // conditional
                    ParserAction<Node*>& syn = stack.front();

                    if(syn.get_values().size() != 0) {
                        Node* attr = new Node(nullptr, "CONDITIONAL");
                        attr->add_child(syn.get_values().front());
                        stack[6].add_value(attr);
                    } else {
                        stack[6].add_values(syn.get_values());
                    }
                },
                [](auto stack) {},
                [](auto stack) {
                    // Bitmap
                    ParserAction<Node*>& syn = stack.front();
                    std::vector<Node*> values = syn.get_values();

                    if(!values.empty()) {
                        stack[2].add_value(syn.get_values().front());
                    }
                },
                [](auto stack) {
                    // enum
                    ParserAction<Node*>& syn = stack.front();
                    std::vector<Node*> inherits = syn.get_inherits();
                    std::vector<Node*> values = syn.get_values();

                    Node* attr = new Node(nullptr, "FIELD");

                    Node* name = new Node(nullptr, "NAME");
                    Node* length = new Node(nullptr, "LENGTH");

                    name->add_child(values[0]);
                    length->add_child(values[1]);
                    attr->add_child(name);
                    attr->add_child(length);

                    for(std::size_t i = 2 ; i < values.size() ; ++i) {
                        attr->add_child(values[i]);
                    }

                    stack[1].add_value(attr);
                }
            }),

            // stmt_1 -> 'next_protocol:' '(' arg_list ')'
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::STMT_1_TOKEN,
             std::vector<GrammarToken> { Tokens::NEXT_PROTOCOL_TOKEN, Tokens::LEFT_PAR_TOKEN, Tokens::ARG_LIST_TOKEN, Tokens::RIGHT_PAR_TOKEN },
             [](auto stack) {
                ParserAction<Node*>& act = stack.front();

                stack[6].add_inherits(act.get_inherits());
            },
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {},
                [](auto stack) {},
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();
                    std::vector<Node*> values = syn.get_values();
                    std::vector<Node*> inherits = syn.get_inherits();

                    Node* top = new Node(nullptr, "PROPERTY");
                    Node* name = new Node(nullptr, "NAME");
                    name->add_child(new Node(nullptr, "NEXT_PROTOCOL"));

                    top->add_child(name);
                    top->add_child(values[0]);

                    stack[3].add_values(inherits);
                    stack[3].add_value(top);
                },
                [](auto stack) {}
            }),

            // stmt_1 -> 'while:' '(' expr ')' while 'end:' stmt_1
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::STMT_1_TOKEN,
             std::vector<GrammarToken> { Tokens::WHILE_TOKEN_T, Tokens::LEFT_PAR_TOKEN, Tokens::EXPR_TOKEN, Tokens::RIGHT_PAR_TOKEN, Tokens::WHILE_TOKEN, Tokens::END_TOKEN, Tokens::STMT_1_TOKEN },
             [](auto stack) {
                ParserAction<Node*>& act = stack.front();

                stack[13].add_inherits(act.get_inherits());
             },
             std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {},
                [](auto stack) {},
                [](auto stack) {
                    // expr
                    ParserAction<Node*>& syn = stack.front();
                    std::vector<Node*> values = syn.get_values();

                    Node* top = new Node(nullptr, "WHILE");
                    top->add_child(values.front());

                    stack[4].add_value(top);
                },
                [](auto stack) {},
                [](auto stack) {
                    // field_group
                    ParserAction<Node*>& syn = stack.front();
                    std::vector<Node*> values = syn.get_values();

                    Node* top = new Node(nullptr, "STATEMENTS");

                    for(std::size_t i = 1 ; i < values.size() ; ++i) {
                        top->add_child(values[i]);
                    }

                    values.front()->add_child(top);

                    stack[3].add_inherit(values.front());
                },
                [](auto stack) {},
                [](auto stack) {
                    // stmt_1
                    ParserAction<Node*>& syn = stack.front();
                    stack[1].add_values(syn.get_values());
                }
            }),

            // stmt_1 -> stmt_2 stmt_1
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::STMT_1_TOKEN,
             std::vector<GrammarToken> { Tokens::STMT_2_TOKEN, Tokens::STMT_1_TOKEN },
             [](auto stack) {
                ParserAction<Node*>& act = stack.front();
                stack[3].add_inherits(act.get_inherits());
            },
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();
                    std::vector<Node*> values = syn.get_values();

                    stack[1].add_inherits(values);
                },
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();
                    stack[1].add_values(syn.get_values());
                }
            }),

            // stmt_1 --> epsilon
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::STMT_1_TOKEN,
            std::vector<GrammarToken> { Tokens::Tokens::EPS_TOKEN },
            [](auto stack) {
                ParserAction<Node*>& act = stack.front();

                stack[1].add_inherits(act.get_inherits());
            },
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();
                    std::vector<Node*> inherits = syn.get_inherits();
                    stack[1].add_values(inherits);
                }
            }),

            // while -> stmt_2 while
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::WHILE_TOKEN,
            std::vector<GrammarToken> { Tokens::STMT_2_TOKEN, Tokens::WHILE_TOKEN },
            [](auto stack) {
                ParserAction<Node*>& act = stack.front();

                stack[3].add_inherits(act.get_inherits());
            },
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();
                    std::vector<Node*> values = syn.get_values();

                    stack[1].add_inherits(values);
                },
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();
                    stack[1].add_values(syn.get_values());
                }
            }),

            // while -> epsilon
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::WHILE_TOKEN,
            std::vector<GrammarToken> { Tokens::EPS_TOKEN },
            [](auto stack) {
                ParserAction<Node*>& act = stack.front();

                stack[1].add_inherits(act.get_inherits());
            },
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();
                    std::vector<Node*> inherits = syn.get_inherits();
                    stack[1].add_values(inherits);
                }
            }),

            // case_list -> expr ':' stmt_3
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::CASE_LIST,
            std::vector<GrammarToken> { Tokens::EXPR_TOKEN, Tokens::COLON_TOKEN, Tokens::STMT_3_TOKEN, Tokens::CASE_LIST },
            [](auto stack) {
                ParserAction<Node*>& act = stack.front();

                stack[7].add_inherits(act.get_inherits());
            },
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();

                    stack[4].add_value(syn.get_values().front());
                },
                [](auto stack) {},
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();
                    std::vector<Node*> values = syn.get_values();

                    Node* top = new Node(nullptr, "CASE");

                    top->add_child(values.front());
                    top->add_child(values.back());

                    stack[1].add_inherit(top);
                },
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();
                    stack[1].add_values(syn.get_values());
                }
            }),

            // case_list -> epsilon
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::CASE_LIST,
            std::vector<GrammarToken> { Tokens::EPS_TOKEN },
            [](auto stack) {
                ParserAction<Node*>& act = stack.front();

                stack[1].add_inherits(act.get_inherits());
            },
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();
                    std::vector<Node*> inherits = syn.get_inherits();

                    Node* top = new Node(nullptr, "CASES");

                    std::vector<Node*>::iterator it;
                    for(it = inherits.begin() ; it != inherits.end() ; ++it) {
                        top->add_child(*it);
                    }

                    stack[1].add_value(top);
                }
            }),

            // optional -> ',' expr
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::OPTIONAL_TOKEN,
            std::vector<GrammarToken> { Tokens::COMMA_TOKEN, Tokens::EXPR_TOKEN },
            [](auto stack) {},
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {},
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();

                    stack[1].add_value(syn.get_values().front());
                }
            }),

            // optional --> epsilon
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::OPTIONAL_TOKEN,
            std::vector<GrammarToken> { Tokens::EPS_TOKEN },
            [](auto stack) {},
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {}
            }),

            // arg_list -> expr arg_list_1
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::ARG_LIST_TOKEN,
            std::vector<GrammarToken> { Tokens::EXPR_TOKEN, Tokens::ARG_LIST_1_TOKEN },
            [](auto stack) {},
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();

                    stack[1].add_inherits(syn.get_values());
                },
                        [](auto stack) {
                            ParserAction<Node*>& syn = stack.front();

                            stack[1].add_value(syn.get_values().front());
                        }
            }),


            // arg_list -> epsilon
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::ARG_LIST_TOKEN,
            std::vector<GrammarToken> { Tokens::EPS_TOKEN },
            [](auto stack) {},
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {
                    Node* top = new Node(nullptr, "ARGS");

                    stack[1].add_value(top);
                }
            }),

            // arg_list_1 -> ',' arg arg_list_1
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::ARG_LIST_1_TOKEN,
            std::vector<GrammarToken> { Tokens::COMMA_TOKEN, Tokens::EXPR_TOKEN, Tokens::ARG_LIST_1_TOKEN },
            [](auto stack) {
                ParserAction<Node*>& syn = stack.front();

                stack[4].add_inherits(syn.get_inherits());
            },
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {},
                        [](auto stack) {
                            ParserAction<Node*>& syn = stack.front();

                            stack[1].add_inherits(syn.get_inherits());
                            stack[1].add_inherit(syn.get_values().front());
                        },
                        [](auto stack) {
                            ParserAction<Node*>& syn = stack.front();

                            stack[1].add_value(syn.get_values().front());
                        }
            }),

            // arg_list_1 -> epsilon
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::ARG_LIST_1_TOKEN,
            std::vector<GrammarToken> { Tokens::EPS_TOKEN },
            [](auto stack) {
                ParserAction<Node*>& act = stack.front();

                stack[1].add_inherits(act.get_inherits());
            },
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();
                    std::vector<Node*> inherits = syn.get_inherits();

                    Node* top = new Node(nullptr, "ARGS");

                    std::vector<Node*>::iterator it;

                    for(it = inherits.begin() ; it != inherits.end() ; ++it) {
                        top->add_child(*it);
                    }

                    stack[1].add_value(top);
                }
            }),

            // bitmap --> 'bitmap:' id_val_tuple
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::BITMAP_TOKEN,
            std::vector<GrammarToken> { Tokens::BITMAP_TOKEN_T, Tokens::ID_VAL_TUPLE_TOKEN },
            [](auto stack) {},
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {},
                        [](auto stack) {
                            ParserAction<Node*>& syn = stack.front();
                            std::vector<Node*> values = syn.get_values();

                            Node* top = new Node(nullptr, "MAP");

                            std::vector<Node*>::iterator it;

                            for(it = values.begin() ; it != values.end() ; ++it) {
                                top->add_child(*it);
                            }

                            stack[1].add_value(top);
                        }
            }),

            // bitmap --> epsilon
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::BITMAP_TOKEN,
            std::vector<GrammarToken> { Tokens::EPS_TOKEN },
            [](auto stack) {},
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();
                }
            }),

            // inner --> inner:
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::INNER_TOKEN,
            std::vector<GrammarToken> { Tokens::INNER_TOKEN_T, Tokens::LEFT_PAR_TOKEN, Tokens::EXPR_TOKEN, Tokens::RIGHT_PAR_TOKEN },
            [](auto stack) {},
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                 [](auto stack) {},
                 [](auto stack) {},
                 [](auto stack) {
                     ParserAction<Node*>& syn = stack.front();

                     stack[1].add_inherits(syn.get_inherits());
                     stack[1].add_inherit(syn.get_values().front());

                     Node* top = new Node(nullptr, "INNER");
                     Node* priority = new Node(nullptr, "PRIORITY");
                     top->add_child(priority);
                     priority->add_child(syn.get_values().front());

                     stack[3].add_value(top);
                 },
                 [](auto stack) {}
            }),

            // inner --> epsilon
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::INNER_TOKEN,
            std::vector<GrammarToken> { Tokens::EPS_TOKEN },
            [](auto stack) {},
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                 [](auto stack) {
                     ParserAction<Node*>& syn = stack.front();
                 }
            }),



            // enum --> 'enum:' id_val_tuple
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::ENUM_TOKEN,
            std::vector<GrammarToken> { Tokens::Tokens::ENUM_TOKEN_T, Tokens::ID_VAL_TUPLE_TOKEN, Tokens::INNER_TOKEN },
            [](auto stack) {},
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {},
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();
                    std::vector<Node*> values = syn.get_values();

                    Node* top = new Node(nullptr, "ENUM");

                    std::vector<Node*>::iterator it;

                    for(it = values.begin() ; it != values.end() ; ++it) {
                        top->add_child(*it);
                    }

                    stack[3].add_value(top);
                },
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();
                    stack[1].add_values(syn.get_values());
                }
            }),

            // enum --> epsilon
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::ENUM_TOKEN,
            std::vector<GrammarToken> { Tokens::EPS_TOKEN },
            [](auto stack) {},
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();
                }
            }),

            // id_val_tuple -> '(' ID ',' expr ')' id_val_tuple_1
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::ID_VAL_TUPLE_TOKEN,
            std::vector<GrammarToken> { Tokens::LEFT_PAR_TOKEN, Tokens::ID_TOKEN, Tokens::COMMA_TOKEN, Tokens::EXPR_TOKEN, Tokens::RIGHT_PAR_TOKEN, Tokens::ID_VAL_TUPLE_1_TOKEN },
            [](auto stack) {
                ParserAction<Node*>& act = stack.front();

                stack[10].add_inherits(act.get_inherits());
            },
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {},
                        [](auto stack) {
                            ParserAction<Node*>& syn = stack.front();

                            stack[4].add_value(syn.get_values().front());
                        },
                        [](auto stack) {},
                        [](auto stack) {
                            ParserAction<Node*>& syn = stack.front();
                            std::vector<Node*> inherits = syn.get_inherits();
                            std::vector<Node*> values = syn.get_values();

                            Node* range = new Node(nullptr, "TUPLE");

                            Node* name = new Node(nullptr, "FIRST");
                            Node* length = new Node(nullptr, "SECOND");
                            name->add_child(values[0]);
                            length->add_child(values[1]);
                            range->add_child(name);
                            range->add_child(length);

                            stack[3].add_inherits(inherits);
                            stack[3].add_inherit(range);
                        },
                        [](auto stack) {},
                        [](auto stack) {
                            ParserAction<Node*>& syn = stack.front();

                            stack[1].add_values(syn.get_values());
                        }
            }),

            // id_val_tuple_1 -> ',' '(' ID ',' expr ')' id_val_tuple_1
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::ID_VAL_TUPLE_1_TOKEN,
            std::vector<GrammarToken> { Tokens::COMMA_TOKEN, Tokens::LEFT_PAR_TOKEN, Tokens::ID_TOKEN, Tokens::COMMA_TOKEN, Tokens::EXPR_TOKEN, Tokens::RIGHT_PAR_TOKEN, Tokens::ID_VAL_TUPLE_1_TOKEN },
            [](auto stack) {
                ParserAction<Node*>& act = stack.front();

                stack[10].add_inherits(act.get_inherits());
            },
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {},
                        [](auto stack) {},
                        [](auto stack) {
                            ParserAction<Node*>& syn = stack.front();

                            stack[4].add_value(syn.get_values().front());
                        },
                        [](auto stack) {},
                        [](auto stack) {
                            ParserAction<Node*>& syn = stack.front();
                            std::vector<Node*> inherits = syn.get_inherits();
                            std::vector<Node*> values = syn.get_values();

                            Node* range = new Node(nullptr, "TUPLE");

                            Node* name = new Node(nullptr, "FIRST");
                            Node* length = new Node(nullptr, "SECOND");
                            name->add_child(values[0]);
                            length->add_child(values[1]);
                            range->add_child(name);
                            range->add_child(length);

                            stack[3].add_inherits(inherits);
                            stack[3].add_inherit(range);
                        },
                        [](auto stack) {},
                        [](auto stack) {
                            ParserAction<Node*>& syn = stack.front();

                            stack[1].add_values(syn.get_values());
                        }
            }),

            // id_val_tuple_1 -> epsilon
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::ID_VAL_TUPLE_1_TOKEN,
            std::vector<GrammarToken> { Tokens::EPS_TOKEN },
            [](auto stack) {
                ParserAction<Node*>& act = stack.front();

                stack[1].add_inherits(act.get_inherits());
            },
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();

                    stack[1].add_values(syn.get_inherits());
                }
            }),

            // expr --> var expr_1
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::EXPR_TOKEN,
             std::vector<GrammarToken> { Tokens::VAR_TOKEN, Tokens::EXPR_1_TOKEN },
             [](auto stack) {
//                ParserAction<Node*>& syn = stack.front();
//
//                stack[4].add_inherits(syn.get_inherits());
             },
             std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();

                    stack[1].add_inherits((syn.get_values()));
                },
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();

                    stack[1].add_values(syn.get_values());
                }
            }),

            // expr --> fun '(' arg_list ')' expr_1
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::EXPR_TOKEN,
             std::vector<GrammarToken> { Tokens::FUN_TOKEN, Tokens::LEFT_PAR_TOKEN, Tokens::ARG_LIST_TOKEN, Tokens::RIGHT_PAR_TOKEN, Tokens::EXPR_1_TOKEN },
             [](auto stack) {},
                std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                    [](auto stack) {
                        ParserAction<Node*>& syn = stack.front();
                        stack[4].add_value(syn.get_values().front());
                    },
                    [](auto stack) {},
                    [](auto stack) {
                        ParserAction<Node*>& syn = stack.front();
                        std::vector<Node*> values = syn.get_values();

                        Node* top = new Node(nullptr, "FUN");
                        Node* name = new Node(nullptr, "NAME");
                        Node* args = values[1];

                        name->add_child(values[0]);

                        top->add_child(name);
                        top->add_child(args);

                        stack[3].add_inherit(top);
                    },
                    [](auto stack) {},
                    [](auto stack) {
                        ParserAction<Node*>& syn = stack.front();

                        stack[1].add_values(syn.get_values());
                    },
            }),

            // expr_1 --> op expr
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::EXPR_1_TOKEN,
             std::vector<GrammarToken> { Tokens::OP_TOKEN, Tokens::EXPR_TOKEN  },
             [](auto stack) {
                ParserAction<Node*>& syn = stack.front();

                stack[4].add_inherits(syn.get_inherits());
             },
             std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();

                    stack[2].add_value(syn.get_values().front());
                },
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();
                    std::vector<Node*> values = syn.get_values();

                    Node* var = syn.get_inherits().front();
                    Node* op = values[0];
                    Node* expr = values[1];

                    op->add_child(var);

                    std::string& expr_val = expr->get_value();

                    short op_precedence = Tokens::op_precedence.at(op->get_value());
                    short expr_precedence = Tokens::op_precedence.contains(expr_val) ?
                            Tokens::op_precedence.at(expr->get_value()) : SHRT_MAX; // expr is not an operator but a value, gives max precedence

                    if(expr_precedence > op_precedence) {
                        op->add_child(expr);
                        stack[1].add_value(op);
                    }
                    // if same precedence
                    else {
                        std::vector<Node*>& expr_children = expr->get_children();

                        Node* expr_child = expr_children.front();
                        op->add_child(expr_child);

                        expr_children.erase(expr_children.begin());
                        expr->add_child(op);

                        stack[1].add_value(expr);
                    }
                }
            }),

            // expr_1 --> epsilon
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::EXPR_1_TOKEN,
             std::vector<GrammarToken> { Tokens::EPS_TOKEN },
             [](auto stack) {
                ParserAction<Node*>& syn = stack.front();

                stack[1].add_inherits(syn.get_inherits());
             },
             std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();

                    stack[1].add_values(syn.get_inherits());
                }
            }),

            // op --> +
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::OP_TOKEN,
             std::vector<GrammarToken> { Tokens::PLUS_TOKEN },
             [](auto stack) {},
             std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();

                    stack[1].add_value(new Node(nullptr, Tokens::PLUS));
                }
            }),

            // op --> -
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::OP_TOKEN,
             std::vector<GrammarToken> { Tokens::MINUS_TOKEN },
             [](auto stack) {},
             std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();

                    stack[1].add_value(new Node(nullptr, Tokens::MINUS));
                }
            }),

            // op --> and
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::OP_TOKEN,
             std::vector<GrammarToken> { Tokens::AND_TOKEN },
             [](auto stack) {},
             std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();

                    stack[1].add_value(new Node(nullptr, Tokens::AND));
                }
            }),

            // op --> or
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::OP_TOKEN,
             std::vector<GrammarToken> { Tokens::OR_TOKEN },
             [](auto stack) {},
             std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();

                    stack[1].add_value(new Node(nullptr, Tokens::OR));
                }
            }),

            // op --> <
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::OP_TOKEN,
             std::vector<GrammarToken> { Tokens::LESS_THAN_TOKEN },
             [](auto stack) {},
             std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();

                    stack[1].add_value(new Node(nullptr, Tokens::LESS_THAN));
                }
            }),

            // op --> >
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::OP_TOKEN,
             std::vector<GrammarToken> { Tokens::GREATER_THAN_TOKEN },
             [](auto stack) {},
             std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();

                    stack[1].add_value(new Node(nullptr, Tokens::GREATER_THAN));
                }
            }),

            // var --> INT
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::VAR_TOKEN,
             std::vector<GrammarToken> { Tokens::INT_TOKEN },
             [](auto stack) {},
             std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();

                    stack[1].add_values(syn.get_values());
                }
            }),

            // var --> ID dot_expr
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::VAR_TOKEN,
             std::vector<GrammarToken> { Tokens::ID_TOKEN, Tokens::DOT_EXPR_TOKEN },
             [](auto stack) {},
             std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();
                    stack[1].add_inherits(syn.get_values());
                },
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();
                    stack[1].add_values(syn.get_values());
                }
            }),

            // fun --> some function name
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::FUN_TOKEN,
             std::vector<GrammarToken> { Tokens::COND_TOKEN_T },
             [](auto stack) {},
             std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();

                    stack[1].add_values(syn.get_values());
                }
            }),

            // string --> "String"
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::STRING_TOKEN,
             std::vector<GrammarToken> { Tokens::STRING_TOKEN_T },
             [](auto stack) {},
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();

                    std::string& string = syn.get_values().front()->get_value();

                    string.erase(0, 1);
                    string.erase(string.size() - 1, 1);

                    stack[1].add_values(syn.get_values());
                }
            }),

            // dot_expr --> . ID
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::DOT_EXPR_TOKEN,
            std::vector<GrammarToken> { Tokens::DOT_TOKEN, Tokens::ID_TOKEN, Tokens::DOT_EXPR_TOKEN },
                [](auto stack) {
                    ParserAction<Node*>& act = stack.front();

                    stack[4].add_inherits(act.get_inherits());
                },
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();
                    stack[2].add_values(syn.get_values());
                },
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();
                    std::vector<Node*> inherits = syn.get_inherits();
                    std::vector<Node*> values = syn.get_values();

                    Node* dot = new Node(nullptr, "DOT");
                    dot->add_child(values.back());

                    if(!inherits.empty()) {
                        inherits.front()->add_child(dot);
                        stack[1].add_inherit(inherits.front());
                    } else {
                        stack[1].add_inherit(dot);
                    }
                },
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();
                    stack[1].add_values(syn.get_values());
                }
            }),

            // dot_expr --> epsilon
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::DOT_EXPR_TOKEN,
             std::vector<GrammarToken> { Tokens::EPS_TOKEN },
             [](auto stack) {
                ParserAction<Node*>& act = stack.front();
                stack[1].add_inherits(act.get_inherits());
             },
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();
                    std::vector<Node*> inherits = syn.get_inherits();
                    stack[1].add_values(inherits);
                }
            })

    };

}

#endif //PARSER_GRAMMARDEFS_H

/*

S -> definition

definition -> protocol termination definition
definition -> epsilon

protocol -> 'protocol:' '(' expr ')' stmt_1

termination -> '-' termination
termination -> epsilon

stmt_1 -> 'next_protocol:' '(' arg_list ')'
stmt_1 -> 'field_group:' '(' conditional ')' field_group 'end:' stmt_1
stmt_1 -> stmt_2 stmt_1
stmt_1 -> epsilon

field_group -> stmt_2 field_group
field_group -> epsilon

stmt_2 -> 'field:' '(' string ',' expr conditional ')' bitmap enum

conditional -> ',' cond_fun '(' arg_list ')'
conditional -> epsilon

cond_fun -> range_equals
cond_fun -> equals
cond_fun -> has
cond_fun -> has_not
cond_fun -> prefix

arg_list -> arg arg_list_1
arg_list -> epsilon

arg_list_1 -> ',' arg arg_list_1
arg_list_1 -> epsilon

bitmap -> 'bitmap:' id_val_tuple
bitmap -> epsilon

enum -> 'enum:' id_val_tuple inner
enum -> epsilon

inner -> 'inner: '(' expr ')'
inner -> epsilon

id_val_tuple -> '(' ID ',' expr ')' id_val_tuple_1

id_val_tuple_1 -> ',' '(' ID ',' expr ')' id_val_tuple_1
id_val_tuple_1 -> epsilon

conditional -> prefix '(' expr ')'

expr --> var expr_1

expr_1 --> op expr
expr_1 --> epsilon

op --> +          9
op --> +          9
op --> *          10
op --> and        7
op --> or         7
op --> <          8
op --> >          8

var --> ID dot_expr
var --> INT
var --> HEX

string --> " String "

dot_expr --> . ID dot_expr
dot_expr --> epsilon

*/

/// NEEEW
/*

S -> definition

definition -> protocol termination definition
definition -> epsilon

protocol -> 'protocol:' '(' expr ')' stmt_1

termination -> '-' termination
termination -> epsilon

stmt_1 -> 'next_protocol:' '(' arg_list ')'
stmt_1 -> 'while:' '(' expr ')' while 'end:' stmt_1                     #
stmt_1 -> stmt_2 stmt_1
stmt_1 -> epsilon

while -> stmt_2 while                                                   #
while -> epsilon                                                        #

stmt_2 -> stmt_3
stmt_2 -> 'switch:' '(' expr ')' case_list 'end:'                       #

stmt_3 -> 'field:' '(' string ',' expr optional ')' bitmap enum

case_list -> expr ':' stmt_3 case_list
case_list -> epsilon

optional -> ',' expr
optional -> epsilon

arg_list -> arg arg_list_1
arg_list -> epsilon

arg_list_1 -> ',' arg arg_list_1
arg_list_1 -> epsilon

bitmap -> 'bitmap:' id_val_tuple
bitmap -> epsilon

enum -> 'enum:' id_val_tuple inner
enum -> epsilon

inner -> 'inner: '(' expr ')'
inner -> epsilon

id_val_tuple -> '(' ID ',' expr ')' id_val_tuple_1

id_val_tuple_1 -> ',' '(' ID ',' expr ')' id_val_tuple_1
id_val_tuple_1 -> epsilon

conditional -> prefix '(' expr ')'

expr --> var expr_1
expr --> fun '(' arg_list ')' expr_1

expr_1 --> op expr
expr_1 --> epsilon

op --> +
op --> +
op --> and
op --> or
op --> <
op --> >

fun -> 'range_equals'
fun -> 'equals'
fun -> 'has'
fun -> 'has_not'
fun -> 'prefix'

var --> ID dot_expr
var --> INT
var --> HEX

string --> "String"

dot_expr --> . ID dot_expr
dot_expr --> epsilon

*/