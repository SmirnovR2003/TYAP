// ConstParser.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <map>

using namespace std;

enum class Token
{
    Const = 0,
    Var,
    Ident,
    Type,
    Assignment,
    Semicolon,
    Noc
};
map<Token, string> tokenToString;
class Lexer
{
public:
    Token GetToken() { return Token::Const; };
};
Lexer lexer;
Token token;
bool error = false;

void Var(){}

void Expr(){}

void SectionConst()
{

    if (token == Token::Type)
    {
        if (token == Token::Ident)
        {

            if (token == Token::Assignment)
            {
                Expr();
            }
            else
                throw exception(("expected Assignment given " + tokenToString[token]).c_str());
        }
        else
            throw exception(("expected Ident given " + tokenToString[token]).c_str());
    }
    else
        throw exception(("expected Type given " + tokenToString[token]).c_str());


}

void ListSectionsConst()
{
    token = lexer.GetToken();
    if (token == Token::Noc) 
        return;
    else if(token == Token::Type)
    {
        SectionConst();
        if (token == Token::Noc)
            return;
        else if (token == Token::Semicolon)
            ListSectionsConst();
        else
            throw exception(("expected Semicolon or Noc given " + tokenToString[token]).c_str());

    }
    else
        throw exception(("expected Type or Noc given " + tokenToString[token]).c_str());

}

void Consts()
{
    if (token != Token::Const)
    {
        throw exception(("expected Const given " + tokenToString[token]).c_str());
    }
    ListSectionsConst();
    if (token != Token::Noc)
    {
        throw exception(("expected Noc given " + tokenToString[token]).c_str());

    }
}

int main()
{
    token = lexer.GetToken();

    if (token == Token::Const)
    {
        Consts();
        token = lexer.GetToken();
        if (token == Token::Var)
        {
            Var();
        }
        else
        {
            throw exception(("expected Var given " + tokenToString[token]).c_str());
        }
    }
    else if (token == Token::Var)
    {
        Var();
    }
    else
    {
        throw exception(("expected Var given " + tokenToString[token]).c_str());
    }
}

