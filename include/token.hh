#pragma once
#include <string>

namespace Json {
enum class Tokentype {
    LBR,
    RBR,
    LSQ,
    RSQ,
    COMA,
    SEMI,
    STRING,
    POS_INT,
    NEG_INT,
    POS_FLOAT,
    NEG_FLOAT,
    TRUE,
    FALSE,
    JSON_NULL
};

class Token {
public:
    Tokentype t;
public:
    Token(Tokentype t);
    [[nodiscard]] std::string toString() noexcept;
};
}