#include "parse.hpp"

#include <cctype>
#include <charconv>
#include <utility>

Expr Parser::doParse() {
  moveAhead();
  auto result = parseExpression();
  if (mLookahead.getSourceRange().end() != mSrc.end())
    throw SyntaxError{"Expect end of expression"};
  return result;
}

/*
 * Operator precedence:
 *
 * 6: ! + - Right
 * 5: * /
 * 4: + -
 * 3: < <= > >=
 * 2: == !=
 * 1: && ||
 * 0: ?: Right
 */

// expr -> Cond
Expr Parser::parseExpression() { return parseConditionalOp(); }

// Cond -> BLog ? Cond : Cond
//       | BLog
Expr Parser::parseConditionalOp() {
  auto e1 = parseBinaryLogicalOp();
  if (tryMatchOperator("?")) {
    auto e2 = parseConditionalOp();
    matchOperator(":");
    auto e3 = parseConditionalOp();
    return Expr::create<ConditionalOp>(e1, e2, e3);
  } else
    return e1;
}

// BLog -> Eq E1
// E1   -> && Eq E1
//       | || Eq E1
//       | epsilon
Expr Parser::parseBinaryLogicalOp() {
  auto result = parseEqualityOp();
  while (true) {
    if (tryMatchOperator("&&"))
      result = Expr::create<BinaryLogicalOp>(
          OperatorKind::LogicalAnd, std::move(result), parseEqualityOp());
    else if (tryMatchOperator("||"))
      result = Expr::create<BinaryLogicalOp>(
          OperatorKind::LogicalOr, std::move(result), parseEqualityOp());
    else
      return result;
  }
}

// Eq   -> Rel E2
// E2   -> == Rel E2
//       | != Rel E2
//       | epsilon
Expr Parser::parseEqualityOp() {
  auto result = parseRelationalOp();
  while (true) {
    if (tryMatchOperator("=="))
      result = Expr::create<EqualityOp>(OperatorKind::Equal, std::move(result),
                                        parseRelationalOp());
    else if (tryMatchOperator("!="))
      result = Expr::create<EqualityOp>(OperatorKind::NotEqual,
                                        std::move(result), parseRelationalOp());
    else
      return result;
  }
}

// Rel  -> PM E3
// E3   -> < PM E3
//       | <= PM E3
//       | > PM E3
//       | >= PM E3
//       | epsilon
Expr Parser::parseRelationalOp() {
  auto result = parsePlusMinusOp();
  while (true) {
    if (tryMatchOperator("<"))
      result = Expr::create<RelationalOp>(OperatorKind::Less, std::move(result),
                                          parsePlusMinusOp());
    else if (tryMatchOperator("<="))
      result = Expr::create<RelationalOp>(
          OperatorKind::LessEqual, std::move(result), parsePlusMinusOp());
    else if (tryMatchOperator(">"))
      result = Expr::create<RelationalOp>(
          OperatorKind::Greater, std::move(result), parsePlusMinusOp());
    else if (tryMatchOperator(">="))
      result = Expr::create<RelationalOp>(
          OperatorKind::GreaterEqual, std::move(result), parsePlusMinusOp());
    else
      return result;
  }
}

// PM   -> MD E4
// E4   -> + MD E4
//       | - MD E4
//       | epsilon
Expr Parser::parsePlusMinusOp() {
  auto result = parseMultiplyDivideOp();
  while (true) {
    if (tryMatchOperator("+"))
      result = Expr::create<BinaryArithOp>(
          OperatorKind::BinaryPlus, std::move(result), parseMultiplyDivideOp());
    else if (tryMatchOperator("-"))
      result = Expr::create<BinaryArithOp>(OperatorKind::BinaryMinus,
                                           std::move(result),
                                           parseMultiplyDivideOp());
    else
      return result;
  }
}

// MD   -> Unary E5
// E5   -> * Unary E5
//       | / Unary E5
//       | epsilon
Expr Parser::parseMultiplyDivideOp() {
  auto result = parseUnaryOp();
  while (true) {
    if (tryMatchOperator("*"))
      result = Expr::create<BinaryArithOp>(OperatorKind::BinaryMultiply,
                                           std::move(result), parseUnaryOp());
    else if (tryMatchOperator("/"))
      result = Expr::create<BinaryArithOp>(OperatorKind::BinaryDivide,
                                           std::move(result), parseUnaryOp());
    else
      return result;
  }
}

// Unary-> !Unary
//       | +Unary
//       | -Unary
//       | Leaf
Expr Parser::parseUnaryOp() {
  if (tryMatchOperator("!"))
    return Expr::create<LogicalNotOp>(parseUnaryOp());
  else if (tryMatchOperator("+"))
    return Expr::create<UnaryArithOp>(OperatorKind::UnaryPlus, parseUnaryOp());
  else if (tryMatchOperator("-"))
    return Expr::create<UnaryArithOp>(OperatorKind::UnaryMinus, parseUnaryOp());
  else
    return parseLeaf();
}

// Leaf -> integer
//       | floating_point
//       | true
//       | false
//       | variable
//       | (expr)
Expr Parser::parseLeaf() {
  if (tryMatchOperator("(")) {
    auto expr = parseExpression();
    matchOperator(")");
    return expr;
  } else if (mLookahead.getKind() == TokenKind::IntegerConstant) {
    auto value = mLookahead.getIntValue();
    moveAhead();
    return Expr::create<IntegerConstant>(value);
  } else if (mLookahead.getKind() == TokenKind::FloatConstant) {
    auto value = mLookahead.getFloatValue();
    moveAhead();
    return Expr::create<FloatConstant>(value);
  } else if (mLookahead.getKind() == TokenKind::BooleanConstant) {
    auto value = mLookahead.getBooleanValue();
    moveAhead();
    return Expr::create<BooleanConstant>(value);
  } else {
    auto varName = mLookahead.getSourceRange();
    moveAhead();
    auto varType = ExprType::Float;
    if (auto pos = mVarTypes.find(varName); pos != mVarTypes.end())
      varType = pos->second;
    return Expr::create<Variable>(varType, std::string(varName));
  }
}

bool Parser::tryMatchOperator(std::string_view op) {
  if (mLookahead.getSourceRange() == op) {
    assert(mLookahead.getKind() == TokenKind::Operator);
    moveAhead();
    return true;
  }
  return false;
}

void Parser::matchOperator(std::string_view op) {
  if (!tryMatchOperator(op))
    throw SyntaxError{};
}

static std::from_chars_result from_chars_fp(const char *first, const char *last,
                                            double &value) {
#ifdef _LIBCPP_VERSION
  assert(*last == '\0' &&
         "Only the case where last is the end of the string is supported.");
  char *end;
  errno = 0;
  double val = std::strtod(first, &end);
  if (end == first) // no pattern match
    return {last, std::errc::invalid_argument};
  else if (errno == ERANGE) {
    errno = 0;
    return {end, std::errc::result_out_of_range};
  } else {
    value = val;
    return {end, std::errc{}};
  }
#else
  return std::from_chars(first, last, value);
#endif // _LIBCPP_VERSION
}

void Parser::moveAhead() {
  auto begin = mLookahead.getSourceRange().end();
  while (begin < mSrc.end() && std::isspace(*begin))
    ++begin;
  if (begin == mSrc.end()) {
    mLookahead = Token::createNull(mSrc.end());
    return;
  }
  switch (*begin) {
  case '+':
  case '-':
  case '*':
  case '/':
  case '?':
  case ':':
  case '(':
  case ')': {
    mLookahead = Token::createOperator({begin, 1});
    return;
  }
  case '!':
  case '<':
  case '>': {
    if (begin + 1 < mSrc.end() && begin[1] == '=')
      mLookahead = Token::createOperator({begin, 2});
    else
      mLookahead = Token::createOperator({begin, 1});
    return;
  }
  case '=':
  case '&':
  case '|': {
    if (begin + 1 < mSrc.end() && begin[1] == *begin) {
      mLookahead = Token::createOperator({begin, 2});
      return;
    } else
      throw LexerError{"Unrecognized token"};
  }
  default: {
    double fval{};
    auto [fend, fec] = from_chars_fp(begin, mSrc.end(), fval);
    int ival{};
    auto [iend, iec] = std::from_chars(begin, mSrc.end(), ival);

    if (fec != std::errc::invalid_argument) {
      // The number is floating-point, possibly out of range.
      if (iec == std::errc::invalid_argument) {
        // The number does not begin with an integer.
        if (fec == std::errc{}) {
          mLookahead = Token(std::string_view(begin, fend - begin), fval);
          return;
        } else
          throw LexerError{"Floating point constant out of range"};
      } else {
        // The number begins with an integer.
        if (iend == fend) {
          // The number is entirely an integer.
          if (iec == std::errc{}) {
            mLookahead = Token(std::string_view(begin, iend - begin), ival);
            return;
          } else
            throw LexerError{"Integer constant out of range"};
        } else {
          // The number is floating-point.
          assert(iend < fend);
          if (fec == std::errc{}) {
            mLookahead = Token(std::string_view(begin, fend - begin), fval);
            return;
          } else
            throw LexerError{"Floating point constant out of range"};
        }
      }
    }
    auto nameEnd = begin;
    while (nameEnd < mSrc.end() && (std::isalnum(*nameEnd) || *nameEnd == '_'))
      ++nameEnd;
    if (nameEnd == begin)
      throw LexerError{"Unrecognized token"};
    std::string_view name(begin, nameEnd - begin);
    if (name == "true" || name == "false")
      mLookahead = Token(name, name == "true");
    else
      mLookahead = Token::createVariable(name);
  }
  }
}