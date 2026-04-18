#include "codegen.hpp"
#include <llvm-18/llvm/IR/Constants.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Value.h>
#include <llvm/Support/raw_ostream.h>
#include <stdexcept>

namespace codegen {

void Codegen::generate_program(const parser::ast::Program *program) {
  for (const auto &function_declaration : program->functions) {
    generate_function_declaration(function_declaration.get());
  }
  module_.print(llvm::outs(), nullptr);
}

void Codegen::generate_function_declaration(
    const parser::ast::FunctionDeclaration *function_declaration) {
  llvm::FunctionType *llvm_return_type =
      llvm::FunctionType::get(builder_.getInt8Ty(), false);
  std::string function_name = function_declaration->name.get_lexeme();
  llvm::Function *llvm_function =
      llvm::Function::Create(llvm_return_type, llvm::Function::ExternalLinkage,
                             function_name, module_);

  llvm::BasicBlock *llvm_block =
      llvm::BasicBlock::Create(context_, "entry", llvm_function);
  builder_.SetInsertPoint(llvm_block);

  generate_statement(function_declaration->block.get());
}

void Codegen::generate_statement(const parser::ast::Statement *statement) {
  if (auto return_statement =
          dynamic_cast<const parser::ast::ReturnStatement *>(statement)) {
    builder_.CreateRet(
        generate_expression_value(return_statement->expression.get()));
  } else if (auto block =
                 dynamic_cast<const parser::ast::BlockStatement *>(statement)) {
    for (const auto &statement : block->statements) {
      generate_statement(statement.get());
    }
  }
};

llvm::Value *
Codegen::generate_expression_value(const parser::ast::Expression *expression) {
  if (auto integer_literal =
          dynamic_cast<const parser::ast::IntegerLiteral *>(expression)) {
    return llvm::ConstantInt::get(builder_.getInt8Ty(), integer_literal->value);
  }
  throw std::runtime_error("Not a valid expression!");
}

}; // namespace codegen
