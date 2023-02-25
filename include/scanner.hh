#pragma once
#include <string>
#include <vector>
#include "token.hh"

namespace Json {

class Scanner {
private:
    size_t curr;
    std::string input;
    std::vector<Token> tokens;
    std::vector<std::string> lexemes;
private:
    void advance() noexcept;
    [[nodiscard]] bool atEnd() noexcept;
    [[nodiscard]] bool matchCurr(char) noexcept;
private:
    void pushString();
    void pushNumber(bool isPos);
    void pushFalse();
    void pushNull();
    void pushTrue();
    void pushList();
    void pushObj();
    void pushSimple(Tokentype);
public:
    Scanner(std::string);
public:
    void scan();
    [[nodiscard]] std::vector<Token> getTokens() noexcept;
    [[nodiscard]] std::vector<std::string> getLexemes() noexcept;
    void printLexemes() noexcept;
    void printTokens() noexcept;
};
}