#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include "token.hh"

class Value;
class StringValue;
class IntValue;
class BoolValue;
class FloatValue;
class NullValue;
class ListValue;
class ObjectValue;

class Parser
{
private:
    std::size_t  currTok;
    std::size_t currLex;
    std::vector<Token> tokens;
    std::vector<std::string> lexemes;
public:
    Parser(std::vector<Token>& tok, std::vector<std::string>&);
    ObjectValue* parse();
private:
    std::string parseKey();
    Value* parseValue();

    StringValue* parseString();
    IntValue* parseInt(bool isPos);
    FloatValue* parseFloat(bool isPos);
    BoolValue* parseTrue();
    BoolValue* parseFalse();
    NullValue* parseNull();
    ListValue* parseList();
    ObjectValue* parseObj();

    bool matchCurr(Tokentype) noexcept;
};