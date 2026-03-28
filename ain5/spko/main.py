import sys
from antlr4 import *
from CalcLexer import CalcLexer
from CalcParser import CalcParser
from CalcVisitor import CalcVisitor

# 1. Create a custom Visitor to evaluate the math
class MyCalcVisitor(CalcVisitor):
    def visitProg(self, ctx:CalcParser.ProgContext):
        return self.visit(ctx.expr())

    def visitExpr(self, ctx:CalcParser.ExprContext):
        # If the expression is just an integer (e.g., 'INT')
        if ctx.INT():
            return int(ctx.INT().getText())
            
        # If the expression has parentheses (e.g., '(' expr ')')
        if ctx.getChildCount() == 3 and ctx.getChild(0).getText() == '(':
            return self.visit(ctx.expr(0))
            
        # If it's a binary operation (e.g., expr '+' expr)
        left = self.visit(ctx.expr(0))
        right = self.visit(ctx.expr(1))
        op = ctx.op.text
        
        if op == '+': return left + right
        if op == '-': return left - right
        if op == '*': return left * right
        if op == '/': return left / right

def main():
    # 2. Setup the input stream
    input_text = "10 + 5 * 2"
    input_stream = InputStream(input_text)
    
    # 3. Lexer: Convert text to tokens
    lexer = CalcLexer(input_stream)
    stream = CommonTokenStream(lexer)
    
    # 4. Parser: Convert tokens to a syntax tree
    parser = CalcParser(stream)
    tree = parser.prog() # 'prog' is the starting rule of our grammar
    
    # 5. Evaluate the tree using our Visitor
    visitor = MyCalcVisitor()
    result = visitor.visit(tree)
    
    print(f"Result of '{input_text}' is: {result}")

if __name__ == '__main__':
    main()
