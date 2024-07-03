#ifndef EXPR_PARSE_HPP
#define EXPR_PARSE_HPP

#include "expr.hpp"

#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>

struct SyntaxError : public std::runtime_error {
  SyntaxError() : runtime_error{"Syntax error while parsing an expression"} {}
  using runtime_error::runtime_error;
};

struct LexerError : public std::runtime_error {
  explicit LexerError(const std::string &msg) : runtime_error{msg} {}
};

enum class TokenKind {
  Null,
  Operator,
  IntegerConstant,
  FloatConstant,
  BooleanConstant,
  Variable
};

class Token {
  struct OperatorTag {};
  struct VariableTag {};

  std::variant<std::monostate, OperatorTag, int, double, bool, VariableTag>
      mInfo;
  std::string_view mSrcRange;

  template <typename Tag>
  Token(Tag tag, std::string_view srcRange) : mInfo{tag}, mSrcRange{srcRange} {}

public:
  Token(std::string_view srcRange, int value)
      : mInfo{value}, mSrcRange{srcRange} {}

  Token(std::string_view srcRange, double value)
      : mInfo{value}, mSrcRange{srcRange} {}

  Token(std::string_view srcRange, bool value)
      : mInfo{value}, mSrcRange{srcRange} {}

  static Token createOperator(std::string_view srcRange) {
    return {OperatorTag{}, srcRange};
  }

  static Token createVariable(std::string_view srcRange) {
    return {VariableTag{}, srcRange};
  }

  static Token createNull(const char *pos) {
    return {std::monostate{}, {pos, 0}};
  }

  TokenKind getKind() const { return static_cast<TokenKind>(mInfo.index()); }

  int getIntValue() const { return getValueImpl<int>(); }

  double getFloatValue() const { return getValueImpl<double>(); }

  bool getBooleanValue() const { return getValueImpl<bool>(); }

  std::string_view getSourceRange() const { return mSrcRange; }

private:
  template <typename Type> Type getValueImpl() const {
    static_assert(std::is_same_v<Type, int> || std::is_same_v<Type, double> ||
                  std::is_same_v<Type, bool>);
    auto ptr = std::get_if<Type>(&mInfo);
    assert(ptr);
    return *ptr;
  }
};

class Parser {
  const std::string_view mSrc;
  const std::unordered_map<std::string_view, ExprType> &mVarTypes;
  Token mLookahead;

public:
  explicit Parser(
      const std::string_view src,
      const std::unordered_map<std::string_view, ExprType> &varTypes)
      : mSrc{src}, mVarTypes{varTypes},
        mLookahead{Token::createNull(src.begin())} {}

  Expr doParse();

private:
  Expr parseExpression();

  Expr parseConditionalOp();

  Expr parseBinaryLogicalOp();

  Expr parseEqualityOp();

  Expr parseRelationalOp();

  Expr parsePlusMinusOp();

  Expr parseMultiplyDivideOp();

  Expr parseUnaryOp();

  Expr parseLeaf();

  bool tryMatchOperator(std::string_view op);

  void matchOperator(std::string_view op);

  void moveAhead();
};

/// @brief Parses an expression given by @c exprCode and builds the AST.
/// @param exprCode A string representing the expression.
/// @param varTypes Types of the variables. If a variable's name is not
/// contained in @c varTypes, its type is @c Float.
/// @return The root of the AST.
inline Expr
parse(std::string_view exprCode,
      const std::unordered_map<std::string_view, ExprType> &varTypes = {}) {
  return Parser{exprCode, varTypes}.doParse();
}

#endif // EXPR_PARSE_HPP