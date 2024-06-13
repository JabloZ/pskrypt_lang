#ifndef PARSER_H
#define PARSER_H
#include "common.h"

struct Node* parser(struct Token *tokens);
struct Node* binaryOperation();

#endif