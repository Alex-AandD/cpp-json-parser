#include "parser.hh"
#include "value.hh"
#include <iostream>

Parser::Parser(std::vector<Token>& t, std::vector<std::string>& l)
    : tokens(t), lexemes(l), currTok(0), currLex(0)
{

}

bool Parser::matchCurr(Tokentype t) noexcept {
    if (currTok >= tokens.size()) return false;
    if (tokens[currTok].t == t)
    {
        currTok++;
        return true;
    }
    return false;
}

ObjectValue* Parser::parse()
{
    return parseObj();
}

ObjectValue* Parser::parseObj()
{
    std::unordered_map<std::string, Value*> map;
    if (matchCurr(Tokentype::LBR))
    {
        do {
            std::string key = parseKey(); 
            if (!matchCurr(Tokentype::SEMI))
            {
                throw("missing semicolon");
            }
            Value* val = parseValue();

            // insert key and value into the object
            map[key] = val;
        } while(matchCurr(Tokentype::COMA));
    }

    if (matchCurr(Tokentype::RBR))
    {
        return new ObjectValue(map);
    }
    throw("missing closing bracket");
}

std::string Parser::parseKey()
{
    if (matchCurr(Tokentype::STRING))
    {
        // get the lexeme
        std::string l = lexemes[currLex];
        currLex++;
        return l;
    }
    throw("invalid key");
}

Value* Parser::parseValue()
{
    using enum Tokentype;
    std::cout << tokens[currTok].toString() << '\n';
    switch (tokens[currTok].t)
    {
    case STRING: {
        currTok++; 
        return parseString();
    }
    case POS_INT: {
        currTok++; 
        return parseInt(true);
    }
    case NEG_INT: {
        currTok++; 
        return parseInt(false);
    }
    case POS_FLOAT: {
        currTok++; 
        return parseFloat(true);
    }
    case NEG_FLOAT: {
        currTok++; 
        return parseFloat(false);
    }
    case LSQ: {
        currTok++; 
        return parseList(); 
    }
    case LBR: {
        return parseObj();
    }
    case JSON_NULL: {
        currTok++; 
        return parseNull();
    }
    case TRUE: {
        currTok++; 
        return parseTrue();
    }
    case FALSE: {
        currTok++; 
        return parseFalse();
    }
    default: break;
    }
    return nullptr;
}

StringValue* Parser::parseString()
{
    StringValue* v = new StringValue(lexemes[currLex]);
    currLex++;
    return v;
}

IntValue* Parser::parseInt(bool isPos)
{
    IntValue* v = isPos
        ? new IntValue(std::stoi(lexemes[currLex]))
        : new IntValue(std::stoi(lexemes[currLex]));
    currLex++;
    return v;
}

FloatValue* Parser::parseFloat(bool isPos)
{
    FloatValue* v = isPos
        ? new FloatValue(std::stof(lexemes[currLex])) 
        : new FloatValue(-std::stof(lexemes[currLex]));
    currLex++;
    return v;
}

BoolValue* Parser::parseTrue()
{
    BoolValue* v = new BoolValue(true);
    return v;
}

BoolValue* Parser::parseFalse()
{
    BoolValue* v = new BoolValue(false);
    return v;
}

NullValue* Parser::parseNull()
{
    NullValue* v = new NullValue();
    return v;
}

ListValue* Parser::parseList()
{
    std::vector<Value*> values;
    do {
        Value* v = parseValue();
        values.push_back(v);
    } while(matchCurr(Tokentype::COMA));
    if (matchCurr(Tokentype::RSQ))
    {
        return new ListValue(values);
    }
    throw("missing closing bracket");
}