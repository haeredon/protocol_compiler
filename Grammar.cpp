
#include "Grammar.h"
#include "AST.h"
#include "Node.h"
#include "ParseNode.h"
#include "ParserAction.h"

#include<map>
#include<string>
#include<utility>
#include<vector>
#include<regex>
#include<iostream>
#include<stack>
#include<deque>

namespace ProtocolParser {





/*****************************************************************/













    const GrammarToken Grammar::START = GrammarToken("START", "START", false);
    const GrammarToken Grammar::END = GrammarToken("END", "END", false);
    const GrammarToken Grammar::EPSILON = GrammarToken("EPSILON", "EPSILON", true);


/*****************************************************************/


}

// alle non-terms med et barn kan fjernes
// alle ligegyldige tegn kan fjernes
// alle operatore med non-term som parent kan erstatte parent


// protocol: (6+7) required: (ether_type, 2)
/*
protocol: (Ethernet)
required: (src, 6) type: (Mac)
required: (dst, 6) type: (Mac)
optional: (vlan, 4)
required: (ether_type, 2)


S -> definition

definition -> protocol termination definition
definition -> epsilon

protocol -> 'protocol:' '(' expr ')' stmt

termination -> '-' termination
termination -> epsilon

stmt -> 'required:' '(' expr ',' expr ')' stmt
stmt -> 'optional:' '(' expr ',' expr ')' stmt
stmt -> epsilon

expr --> var expr_1
expr --> number expr_1
expr --> '(' expr ')' expr_1

expr_1 --> '+' expr
expr_1 --> '-' expr
expr_1 --> '*' expr
expr_1 --> '/' expr
expr_1 --> epsilon

*/

/*

S -> protocol                                       s.val = protocol.val

protocol -> 'protocol:' '(' expr ')' stmt           protocol.val = name -> expr.val,

stmt -> 'required:' '(' expr ',' expr ')' stmt      stmt.val = private(expr,expr) + stmt.val

 */

/*
S -> expr                   S.val = expr.val

expr --> var expr_1         expr_1.inh = var.val
                            expr.val = expr_1.val

expr_1 --> op expr          expr_1.val = expr_1.inh op.val expr.val

expr_1 --> epsilon          expr_1.val = expr_1.inh

var --> ID                  var.val = ID
var --> INT                 var.val = INT

op --> +                    op.val = '+'
op --> *                    op.val = '*'

*/


/*
protocol: (Ethernet)
required: (src, 6) type: (Mac)
required: (dst, 6) type: (Mac)
optional: (vlan, 4)
required: (ether_type, 2)


S -> definition

definition -> protocol termination definition
definition -> epsilon

protocol -> 'protocol:' '(' expr ')' stmt

termination -> '-' termination
termination -> epsilon

stmt -> 'field:' '(' ID ',' expr conditional ')' bitmap enum stmt
stmt -> epsilon

conditional -> ',' cond_fun '(' arg_list ')'
conditional -> epsilon

cond_fun -> match

arg_list -> arg arg_list_1
arg_list -> epsilon

arg_list_1 -> ',' arg arg_list_1
arg_list_1 -> epsilon

bitmap -> 'bitmap:' id_val_tuple
bitmap -> epsilon

enum -> 'enum:' id_val_tuple
enum -> epsilon

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
-----------------------------------------------------------------------
exp --> add_exp

add_exp  --> mul_exp add_exp'

add_exp' --> + atom add_exp'
add_exp' --> epsilon


mul_exp  --> atom mul_exp'

mul_exp' --> * atom mul_exp'
mul_exp' --> epsilon

atom --> int
atom --> ( exp )

E  -> T E'
E' -> + T E' | epsilon
T  -> F T'
T' -> * F T' | epsilon
F  -> (E) | int

 */


    /*
            for each production in current.name
                node* parent = current;

                for each val in production
                    node *new_node = new node()
                    new_node->parent = parent;
                    new_node->name = val;
                    parent->children.push_back(new_node);

                    if term
                        parent = new_node;
                    else if non_term which exists
                        new_node->children.push_back(non_term_to_node[val]);
                    else
                        build_tree(new_node);*/