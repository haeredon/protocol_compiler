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

            // protocol --> 'protocol:' '(' ID ')' stmt       : S.val = epsilon
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::PRO_TOKEN,
            std::vector<GrammarToken> { Tokens::PROTOCOL_TOKEN, Tokens::LEFT_PAR_TOKEN, Tokens::ID_TOKEN, Tokens::RIGHT_PAR_TOKEN, Tokens::STMT_TOKEN },
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
                                if((*it)->get_value() == "FIELD") {
                                    fields->add_child(*it);
                                } else {
                                    properties->add_child(*it);
                                }

                            }

                            stack[1].add_value(top);
                        }
            }),

            // stmt --> 'field:' '(' ID ',' expr conditional ')' bitmap enum stmt  : S.val = epsilon
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::STMT_TOKEN,
            std::vector<GrammarToken> { Tokens::FIELD_TOKEN, Tokens::Tokens::LEFT_PAR_TOKEN, Tokens::Tokens::ID_TOKEN, Tokens::Tokens::COMMA_TOKEN, Tokens::Tokens::EXPR_TOKEN, Tokens::COND_TOKEN, Tokens::Tokens::RIGHT_PAR_TOKEN, Tokens::Tokens::BITMAP_TOKEN, Tokens::Tokens::ENUM_TOKEN, Tokens::STMT_TOKEN },
            [](auto stack) {
                ParserAction<Node*>& act = stack.front();

                stack[18].add_inherits(act.get_inherits());
            },
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {},
                        [](auto stack) {},
                        [](auto stack) {
                            ParserAction<Node*>& syn = stack.front();

                            stack[12].add_value(syn.get_values().front());
                        },
                        [](auto stack) {},
                        [](auto stack) {
                            ParserAction<Node*>& syn = stack.front();

                            stack[8].add_value(syn.get_values().front());
                        },
                        [](auto stack) {
                            ParserAction<Node*>& syn = stack.front();

                            stack[6].add_values(syn.get_values());
                        },
                        [](auto stack) {},
                        [](auto stack) {
                            ParserAction<Node*>& syn = stack.front();
                            std::vector<Node*> values = syn.get_values();

                            if(!values.empty()) {
                                stack[2].add_value(syn.get_values().front());
                            }
                        },
                        [](auto stack) {
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

                            stack[1].add_inherits(inherits);
                            stack[1].add_inherit(attr);
                        },
                        [](auto stack) {
                            ParserAction<Node*>& syn = stack.front();

                            stack[1].add_values(syn.get_values());
                        }
            }),

            // stmt -> 'next_protocol:' '(' arg_list ')' stmt
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::STMT_TOKEN,
             std::vector<GrammarToken> { Tokens::NEXT_PROTOCOL_TOKEN, Tokens::LEFT_PAR_TOKEN, Tokens::ARG_LIST_TOKEN, Tokens::RIGHT_PAR_TOKEN, Tokens::STMT_TOKEN },
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

                    stack[3].add_inherits(inherits);
                    stack[3].add_inherit(top);
                },
                [](auto stack) {},
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();

                    stack[1].add_values(syn.get_values());
                }
            }),

            // stmt --> epsilon                                 : S.val = epsilon
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::STMT_TOKEN,
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

            // conditional -> ',' cond_fun '(' arg_list ')'  : S.val = epsilon
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::COND_TOKEN,
            std::vector<GrammarToken> { Tokens::COMMA_TOKEN, Tokens::COND_FUN_TOKEN, Tokens::LEFT_PAR_TOKEN, Tokens::ARG_LIST_TOKEN, Tokens::Tokens::RIGHT_PAR_TOKEN },
            [](auto stack) {},
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {},
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();

                    stack[4].add_value(syn.get_values().front());
                },
                [](auto stack) {},
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();
                    std::vector<Node*> values = syn.get_values();

                    Node* top = new Node(nullptr, "CONDITIONAL");
                    Node* name = new Node(nullptr, "NAME");
                    Node* args = values[1];

                    name->add_child(values[0]);

                    top->add_child(name);
                    top->add_child(args);

                    stack[3].add_value(top);
                },
                [](auto stack) {}
            }),

            // conditional --> epsilon
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::COND_TOKEN,
            std::vector<GrammarToken> { Tokens::EPS_TOKEN },
            [](auto stack) {},
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {}
            }),

            // cond_fun --> 'match'
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::COND_FUN_TOKEN,
            std::vector<GrammarToken> { Tokens::COND_TOKEN_T },
            [](auto stack) {},
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();

                    stack[1].add_value(syn.get_values().front());
                }
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

            // expr --> INT
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::EXPR_TOKEN,
            std::vector<GrammarToken> { Tokens::INT_TOKEN },
            [](auto stack) {},
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();

                    stack[1].add_value(syn.get_values().front());
                }
            }),

            // expr --> ID
            Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>(Tokens::EXPR_TOKEN,
            std::vector<GrammarToken> { Tokens::ID_TOKEN },
            [](auto stack) {},
            std::vector<void (*)(std::deque<ParserAction<Node*>>&)> {
                [](auto stack) {
                    ParserAction<Node*>& syn = stack.front();

                    stack[1].add_value(syn.get_values().front());
                }
            })
    };

}

#endif //PARSER_GRAMMARDEFS_H

/*

S -> definition

definition -> protocol termination definition
definition -> epsilon

protocol -> 'protocol:' '(' expr ')' stmt

termination -> '-' termination
termination -> epsilon

stmt -> 'field:' '(' ID ',' expr conditional ')' bitmap enum stmt
stmt -> 'next_protocol:' '(' arg_list ')' stmt
stmt -> epsilon

conditional -> ',' cond_fun '(' arg_list ')'
conditional -> epsilon

cond_fun -> range_equals
cond_fun -> equals
cond_fun -> has
cond_fun -> has_not

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

op --> +
op --> *

var --> ID
var --> INT
var --> HEX

*/