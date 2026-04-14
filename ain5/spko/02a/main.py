import sys
from antlr4 import *
from VHDLLexer import VHDLLexer
from VHDLParser import VHDLParser

def main(argv):
    if len(argv) < 2:
        print("Usage: python main.py <input-file>")
        sys.exit(1)

    input_stream = FileStream(argv[1], encoding='utf-8')
    
    # Lexing
    lexer = VHDLLexer(input_stream)
    stream = CommonTokenStream(lexer)
    
    # Parsing
    parser = VHDLParser(stream)
    
    # WICHTIG: Ersetze 'startRule' durch die oberste Regel in deiner VHDLParser.g4
    # (z.B. 'design_file', 'root' oder wie auch immer du sie genannt hast)
    tree = parser.startRule()
    
    # Gibt den Ableitungsbaum im Terminal aus
    print(tree.toStringTree(recog=parser))

if __name__ == '__main__':
    main(sys.argv)
