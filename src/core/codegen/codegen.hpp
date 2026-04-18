#pragma once
#include "../parser/ast.hpp"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>

namespace codegen {
class Codegen {
public:
  Codegen()
      : module_(llvm::Module{"main_module", context_}), builder_(context_) {};
  void generate_program(const parser::ast::Program *program);

private:
  llvm::LLVMContext context_;
  llvm::Module module_;
  llvm::IRBuilder<> builder_;

  void generate_function_declaration(
      const parser::ast::FunctionDeclaration *function_declaration);

  void generate_statement(const parser::ast::Statement *statement);
  llvm::Value *
  generate_expression_value(const parser::ast::Expression *expression);
};
}; // namespace codegen
