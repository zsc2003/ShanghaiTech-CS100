#ifndef EXPR_DUMP_HPP
#define EXPR_DUMP_HPP

#include "expr.hpp"

#include <iostream>

namespace detail {

const char *OperatorName(OperatorKind op) {
  switch (op) {
  case OperatorKind::UnaryPlus: return "+";
  case OperatorKind::UnaryMinus: return "-";
  case OperatorKind::BinaryPlus: return "+";
  case OperatorKind::BinaryMinus: return "-";
  case OperatorKind::BinaryMultiply: return "*";
  case OperatorKind::BinaryDivide: return "/";
  case OperatorKind::LogicalNot: return "!";
  case OperatorKind::LogicalAnd: return "&&";
  case OperatorKind::LogicalOr: return "||";
  case OperatorKind::Less: return "<";
  case OperatorKind::LessEqual: return "<=";
  case OperatorKind::Greater: return ">";
  case OperatorKind::GreaterEqual: return ">=";
  case OperatorKind::Equal: return "==";
  case OperatorKind::NotEqual: return "!=";
  case OperatorKind::Conditional: return "?:";
  default: assert(false && "not reachable"); return nullptr;
  }
}

const char *TypeName(ExprType type) {
  switch (type) {
  case ExprType::Unevaluated: return "Unevaluated";
  case ExprType::Integer: return "Integer";
  case ExprType::Float: return "Float";
  case ExprType::Boolean: return "Boolean";
  case ExprType::ErrorType: return "ErrorType";
  default: assert(false && "not reachable"); return nullptr;
  }
}

} // namespace detail

class DumpVisitor : public ExprNodeVisitor {
  std::ostream &mOS;
  std::string mContentBefore;

  // FirstChild and RestChildren are pointer-to-member-functions.
  // e.g. If Operator = UnaryArithOp and firstChild = &UnaryArithOp::getOperand,
  // (node.*firstChild)() is equivalent to node.getOperand().
  template <typename Operator, typename FirstChild, typename... RestChildren>
  void dumpChildren(Operator &node, const char *nodeName, FirstChild firstChild,
                    RestChildren... restChildren) {
    if constexpr (sizeof...(RestChildren) > 0) {
      mOS << mContentBefore << "|-";
      mContentBefore += "| ";
    } else {
      mOS << mContentBefore << "`-";
      mContentBefore += "  ";
    }

    // Calls 'accept' on the corresponding child, to traverse the tree
    // recursively.
    (node.*firstChild)().accept(*this);
    mContentBefore.pop_back();
    mContentBefore.pop_back();
    if constexpr (sizeof...(RestChildren) > 0)
      dumpChildren(node, nodeName, restChildren...);
  }

  template <typename Operator> struct OperatorTitle {
    Operator &node;
    const char *nodeName;

    OperatorTitle(Operator &node, const char *name)
        : node{node}, nodeName{name} {}

    friend std::ostream &operator<<(std::ostream &os, const OperatorTitle &ot) {
      return os << ot.nodeName << " '"
                << detail::OperatorName(ot.node.getOpKind())
                << "' : " << detail::TypeName(ot.node.getType());
    }
  };

  void visitUnaryOperator(UnaryOperator &u, const char *nodeName) {
    mOS << OperatorTitle{u, nodeName} << '\n';
    dumpChildren(u, nodeName, &UnaryOperator::getOperand);
  }

  void visitBinaryOperator(BinaryOperator &b, const char *nodeName) {
    mOS << OperatorTitle{b, nodeName} << '\n';
    dumpChildren(b, nodeName, &BinaryOperator::getLHS, &BinaryOperator::getRHS);
  }

public:
  explicit DumpVisitor(std::ostream &os) : mOS{os} {}

  void visit(Variable &v) override {
    mOS << "Variable '" << v.getName()
        << "' : " << detail::TypeName(v.getType()) << '\n';
  }

  void visit(IntegerConstant &i) override {
    mOS << "IntegerConstant " << i.getValue() << '\n';
  }

  void visit(FloatConstant &f) override {
    mOS << "FloatConstant " << f.getValue() << '\n';
  }

  void visit(BooleanConstant &b) override {
    mOS << "BooleanConstant " << std::boolalpha << b.getValue()
        << std::noboolalpha << '\n';
  }

  void visit(UnaryArithOp &u) override {
    visitUnaryOperator(u, "UnaryArithOp");
  }

  void visit(LogicalNotOp &l) override {
    visitUnaryOperator(l, "LogicalNotOp");
  }

  void visit(BinaryArithOp &b) override {
    visitBinaryOperator(b, "BinaryArithOp");
  }

  void visit(EqualityOp &e) override { visitBinaryOperator(e, "EqualityOp"); }

  void visit(RelationalOp &r) override {
    visitBinaryOperator(r, "RelationalOp");
  }

  void visit(BinaryLogicalOp &b) override {
    visitBinaryOperator(b, "BinaryLogicalOp");
  }

  void visit(ConditionalOp &c) override {
    mOS << OperatorTitle{c, "ConditionalOp"} << '\n';
    dumpChildren(c, "ConditionalOp", &ConditionalOp::getCondition,
                 &ConditionalOp::getExprTrue, &ConditionalOp::getExprFalse);
  }
};

void dump(const Expr &expr, std::ostream &os = std::cout) {
  DumpVisitor visitor{os};
  expr.accept(visitor);
}

#endif // EXPR_DUMP_HPP