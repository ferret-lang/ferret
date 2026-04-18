#pragma once
#include "ast.hpp"
#include "token.hpp"
#include <cstddef>
#include <memory>
#include <vector>

namespace parser {

class Parser {
public:
  Parser(const std::vector<Token> tokens) : position_(0), tokens_(tokens) {};
  std::unique_ptr<ast::Program> generate_program();
  void print_program(const ast::Program *program) const;

private:
  std::size_t position_;
  std::vector<Token> tokens_;

  bool is_eof() const;
  Token peek() const;
  Token consume();
  void expect(TokenType expected_type) const;
  Token expect_and_consume(TokenType expected_type);
  ast::IntegerType get_type(Token untyped_type);

  std::unique_ptr<ast::FunctionDeclaration> parse_function();
  std::unique_ptr<ast::BlockStatement> parse_block();
  std::unique_ptr<ast::Statement> parse_statement();
  std::unique_ptr<ast::Expression> parse_expression();

  void print_indent(int indent) const;
  void print_expression(const ast::Expression *expression, int indent) const;
  void print_statement(const ast::Statement *statement, int indent) const;
  void print_function_declaration(
      const ast::FunctionDeclaration *function_declaration, int indent) const;
};

} // namespace parser
