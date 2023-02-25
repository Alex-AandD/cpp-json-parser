#include "scanner.hh"
#include "token.hh"
#include <iostream>

Scanner::Scanner(std::string _input): input(_input), curr(0)
{

}

bool Scanner::atEnd() noexcept
{
    return curr >= input.size();
}

bool Scanner::matchCurr(char c) noexcept
{
    if (input[curr] == c) {
        advance();
        return true;
    }
    return false;
}

std::vector<Token> Scanner::getTokens() noexcept
{
    return tokens;
}

std::vector<std::string> Scanner::getLexemes() noexcept
{
    return lexemes;
}

void Scanner::advance() noexcept
{
    curr++;
}

void Scanner::scan()
{
    while (!atEnd())
    {
        switch (input[curr])
        {
        case ' ':
        case '\n':
        case '\t':
        case '\r': break;
        case '[': pushSimple(Tokentype::LSQ); break;
        case ']': pushSimple(Tokentype::RSQ); break;
        case '{': pushSimple(Tokentype::LBR); break;
        case '}': pushSimple(Tokentype::RBR); break;
        case ',': pushSimple(Tokentype::COMA); break;
        case ':': pushSimple(Tokentype::SEMI); break;
        case '"': {
            pushString(); 
            break;
        }
        case 't': pushTrue(); break;
        case 'f': pushFalse(); break;
        case 'n': pushNull(); break;
        case '-': pushNumber(false); break;
        default: {
                if (std::isdigit(input[curr])) {
                    pushNumber(true);
                    break;
                }
                throw("unknown character");
            }
        }
        advance();
    }
}

void Scanner::pushSimple(Tokentype t) {
    tokens.push_back(Token(t));
}

void Scanner::pushString()
{
    advance();
    std::string finalString;
    while((!atEnd()) && (!matchCurr('"'))) {
        finalString += input[curr]; 
        advance();
    }

    if (atEnd())
    {
        throw("unterminated string");
    }

    // create the token
    tokens.push_back(Token(Tokentype::STRING));
    lexemes.push_back(finalString);
}

void Scanner::pushTrue()
{ 
    advance();
    if(!atEnd() && !matchCurr('r')) {
        throw("expected true");
    }

    if (!atEnd() && !matchCurr('u')) {
        throw("expected true");
    }

    if (!atEnd() && !matchCurr('e')) {
        throw("expected true");
    }

    tokens.push_back(Token(Tokentype::TRUE));
}

void Scanner::pushFalse()
{    
    advance();
    if(!atEnd() && !matchCurr('a')) {
        throw("expected false");
    }

    if (!atEnd() && !matchCurr('l')) {
        throw("expected false");
    }

    if (!atEnd() && !matchCurr('s')) {
        throw("expected false");
    }

    if (!atEnd() && !matchCurr('e')) {
        throw("expected true");
    }

    tokens.push_back(Token(Tokentype::FALSE));
}

void Scanner::pushNull()
{
    advance();
    if(!atEnd() && !matchCurr('u')) {
        throw("expected null");
    }

    if(!atEnd() && !matchCurr('l')) {
        throw("expected null");
    }

    if(!atEnd() && !matchCurr('l')) {
        throw("expected null");
    }
}

void Scanner::pushNumber(bool isPos)
{
    Tokentype type = isPos ? Tokentype::POS_INT : Tokentype::NEG_INT;
    std::string digitString = "";
    digitString += input[curr];
    advance();

    while(std::isdigit(input[curr]))
    {
        digitString += input[curr];
        advance();
    }

    if (input[curr] == '.')
    {
        Tokentype type = isPos ? Tokentype::POS_FLOAT : Tokentype::NEG_FLOAT;
        digitString += input[curr];
        advance();
        while (std::isdigit(input[curr]))
        {
            digitString += input[curr];
            advance();
        }
    }

    tokens.push_back(Token(type));
    lexemes.push_back(digitString);

    // we are one past the end of the integer
    curr--;
}

void Scanner::printLexemes() noexcept
{
    for (const auto& lex: lexemes)
    {
        std::cout << lex << " :: ";
    }
}

void Scanner::printTokens() noexcept
{
    for (auto& tok: tokens)
    {
        std::cout << tok.toString() << " :: ";
    }
}