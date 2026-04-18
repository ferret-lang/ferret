#pragma once
#include "token.hpp"
#include <memory>
#include <vector>

namespace parser {
namespace ast {

struct Expression {
  virtual ~Expression() = default;
};

struct IntegerLiteral : Expression {
  int value;
  IntegerLiteral(int value) : value(value) {}
};

struct FloatLiteral : Expression {
  float value;
};

struct Statement {
  virtual ~Statement() = default;
};

struct ReturnStatement : Statement {
  std::unique_ptr<Expression> expression;

  ReturnStatement(std::unique_ptr<Expression> expression)
      : expression(std::move(expression)) {}
};

struct BlockStatement : Statement {
  std::vector<std::unique_ptr<Statement>> statements;

  BlockStatement(std::vector<std::unique_ptr<Statement>> statements)
      : statements(std::move(statements)) {}
};

struct Parameter {
  Token type;
  Token name;
};

struct FunctionDeclaration {
  Token return_type;
  Token name;
  std::vector<Parameter> params;
  std::unique_ptr<BlockStatement> block;

  FunctionDeclaration(Token return_type, Token name,
                      std::vector<Parameter> params,
                      std::unique_ptr<BlockStatement> block)
      : return_type(return_type), name(name), params(std::move(params)),
        block(std::move(block)) {}
};

struct Program {
  std::vector<std::unique_ptr<FunctionDeclaration>> functions;

  Program(std::vector<std::unique_ptr<FunctionDeclaration>> functions)
      : functions(std::move(functions)) {}
};

} // namespace ast
} // namespace parser
