#include "parser.gen.h"
bool parser::try_empty() { return true;}
bool parser::try_signal_program() {
 if (try_program()) {
 return true;
 } 
 return false;
}

bool parser::try_program() {
 if ((*tk)->content == "PROGRAM") {
 return true;
 } 
 return false;
}

bool parser::try_block() {
 if (try_declarations()) {
 return true;
 } 
 return false;
}

bool parser::try_declarations() {
 if (try_label_declarations()) {
 return true;
 } 
 return false;
}

bool parser::try_label_declarations() {
 if ((*tk)->content == "LABEL") {
 return true;
 } 
 if (try_empty()) {
 return true;
 } 
 return false;
}

bool parser::try_labels_list() {
 if ((*tk)->content == ",") {
 return true;
 } 
 if (try_empty()) {
 return true;
 } 
 return false;
}

bool parser::try_statements_list() {
 if (try_statement()) {
 return true;
 } 
 if (try_empty()) {
 return true;
 } 
 return false;
}

bool parser::try_statement() {
 if (try_unsigned_integer()) {
 return true;
 } 
 if (try_cond_statement()) {
 return true;
 } 
 if (try_goto_statement()) {
 return true;
 } 
 return false;
}

bool parser::try_cond_statement() {
 if (try_condition_statement()) {
 return true;
 } 
 return false;
}

bool parser::try_goto_statement() {
 if ((*tk)->content == "GOTO") {
 return true;
 } 
 return false;
}

bool parser::try_condition_statement() {
 if (try_incomplete_condition_statement()) {
 return true;
 } 
 return false;
}

bool parser::try_incomplete_condition_statement() {
 if ((*tk)->content == "IF") {
 return true;
 } 
 return false;
}

bool parser::try_conditional_expression() {
 if (try_variable_identifier()) {
 return true;
 } 
 return false;
}

bool parser::try_alternative_part() {
 if (try_alt()) {
 return true;
 } 
 if (try_empty()) {
 return true;
 } 
 return false;
}

bool parser::try_alt() {
 if ((*tk)->content == "ELSE") {
 return true;
 } 
 return false;
}

bool parser::try_variable_identifier() {
 if (try_identifier()) {
 return true;
 } 
 return false;
}

bool parser::try_procedure_identifier() {
 if (try_identifier()) {
 return true;
 } 
 return false;
}

bool parser::try_identifier() {
 if (
    (*tk)->token_code > 1000
) {
 return true;
 } 
 return false;
}

bool parser::try_unsigned_integer() {
 if (
    (*tk)->token_code > 500 && (*tk)->token_code < 1000
) {
 return true;
 } 
 return false;
}

