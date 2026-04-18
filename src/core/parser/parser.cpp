#include "parser.hpp"
#include "ast.hpp"
#include "token.hpp"
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

namespace parser {

bool Parser::is_eof() const { return position_ >= tokens_.size(); };
Token Parser::peek() const { return tokens_.at(position_); };
Token Parser::consume() { return tokens_.at(position_++); };

void Parser::expect(TokenType expected_type) const {
  if (peek().get_type() != expected_type)
    throw new std::runtime_error(
        "The expected type does not matach the current token.");
};

Token Parser::expect_and_consume(TokenType type) {
  expect(type);
  return consume();
}

ast::IntegerType Parser::get_type(Token untyped_token) {
  if (untyped_token.get_type() != TokenType::Identifier)
    throw std::runtime_error("The provided token cannot be typed.");

  std::string type_label = untyped_token.get_lexeme();
  if (type_label == "u8")
    return ast::IntegerType::U8;
  else if (type_label == "u16")
    return ast::IntegerType::U16;
  else if (type_label == "u32")
    return ast::IntegerType::U32;
  else if (type_label == "u64")
    return ast::IntegerType::U64;
  else if (type_label == "i8")
    return ast::IntegerType::I8;
  else if (type_label == "i16")
    return ast::IntegerType::I16;
  else if (type_label == "i32")
    return ast::IntegerType::I32;
  else if (type_label == "i64")
    return ast::IntegerType::I64;

  throw std::runtime_error("The provided token cannot be typed.");
}

std::unique_ptr<ast::Program> Parser::generate_program() {
  std::vector<std::unique_ptr<ast::FunctionDeclaration>> functions = {};
  while (!is_eof())
    functions.push_back(parse_function());
  return std::make_unique<ast::Program>(std::move(functions));
};

std::unique_ptr<ast::FunctionDeclaration> Parser::parse_function() {
  // FIX: very less scalability.
  auto return_type_token = expect_and_consume(TokenType::Identifier);
  auto return_type = get_type(return_type_token);
  auto name = expect_and_consume(TokenType::Identifier);

  expect_and_consume(TokenType::LBracket);
  expect_and_consume(TokenType::RBracket);

  expect_and_consume(TokenType::LBrace);
  auto block = parse_block();
  expect_and_consume(TokenType::RBrace);

  return std::make_unique<ast::FunctionDeclaration>(
      return_type, name, std::vector<ast::Parameter>{}, std::move(block));
};

std::unique_ptr<ast::BlockStatement> Parser::parse_block() {
  std::vector<std::unique_ptr<ast::Statement>> statements = {};
  while (!is_eof() && peek().get_type() != TokenType::RBrace)
    statements.push_back(parse_statement());
  return std::make_unique<ast::BlockStatement>(std::move(statements));
};

std::unique_ptr<ast::Statement> Parser::parse_statement() {
  auto token = peek();
  switch (token.get_type()) {
  case TokenType::Return: {
    consume();
    auto expression = parse_expression();
    expect_and_consume(TokenType::SemiColon);
    return std::make_unique<ast::ReturnStatement>(std::move(expression));
  }

  default:
    throw std::runtime_error("Unknown statement");
  }
};

std::unique_ptr<ast::Expression> Parser::parse_expression() {
  auto token = peek();
  switch (token.get_type()) {
  case TokenType::IntegerLiteral: {
    consume();
    auto type = ast::IntegerType::U32;
    auto value = std::stoi(token.get_lexeme());
    return std::make_unique<ast::IntegerLiteral>(value, type);
  }

  default:
    throw std::runtime_error("Unknown expression");
  }
}

void Parser::print_indent(int spaces) const {
  for (int i = 0; i < spaces; i++) {
    std::cout << " ";
  }
};

void Parser::print_program(const ast::Program *program) const {
  std::cout << "Program\n";
  for (const auto &function_declaration : program->functions) {
    print_function_declaration(function_declaration.get(), 1);
  }
};

void Parser::print_function_declaration(
    const ast::FunctionDeclaration *function_declaration, int indent) const {
  int indent_offset = 1;
  print_indent(indent);
  std::cout << "Function: " << function_declaration->name.get_lexeme() << "\n";
  print_indent(indent + indent_offset);
  // FIX:: Remove the hard-coded integer
  std::cout << "ReturnType: " << "Integer"
            << "\n";
  print_indent(indent + indent_offset);
  std::cout << "Params Size: " << function_declaration->params.size() << "\n";
  print_statement(function_declaration->block.get(), indent + indent_offset);
};

void Parser::print_statement(const ast::Statement *statement,
                             int indent) const {
  int indent_offset = 1;
  if (auto return_statement =
          dynamic_cast<const ast::ReturnStatement *>(statement)) {
    print_indent(indent);
    std::cout << "ReturnStatement\n";
    print_expression(return_statement->expression.get(),
                     indent + indent_offset);
  } else if (auto block =
                 dynamic_cast<const ast::BlockStatement *>(statement)) {
    print_indent(indent);
    std::cout << "Block\n";
    for (const auto &statement : block->statements) {
      print_statement(statement.get(), indent + indent_offset);
    }
  }
};

void Parser::print_expression(const ast::Expression *expression,
                              int indent) const {
  if (auto integer_literal =
          dynamic_cast<const ast::IntegerLiteral *>(expression)) {
    print_indent(indent);
    std::cout << "IntegerLiteral(" << integer_literal->value << ")\n";
  }
};

} // namespace parser
