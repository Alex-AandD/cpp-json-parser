#include "token.hh"

namespace Json {

Token::Token(Tokentype _t): t(_t) { }
std::string Token::toString() noexcept
{
    using enum Tokentype;
    switch(t)
    {
        case TRUE: return "TRUE";
        case FALSE: return "FALSE";
        case JSON_NULL: return "NULL";
        case STRING: return "STRING";
        case POS_INT: return "POS INT";
        case NEG_INT: return "NEG INT";
        case POS_FLOAT: return "POS FLOAT";
        case NEG_FLOAT: return "NEG FLOAT";
        case LBR: return "LBR";
        case RBR: return "RBR";
        case LSQ: return "LSQ";
        case RSQ: return "RSQ";
        case COMA: return "COMA";
        case SEMI: return "SEMI";
        default: return "UNKNOWN";
    }
}

}