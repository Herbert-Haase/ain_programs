import sys
from antlr4 import *
from VHDLLexer import VHDLLexer
from VHDLParser import VHDLParser

def parse(file_path):
    # Input Stream erzeugen
    input_stream = FileStream(file_path, encoding='utf-8')
    
    # Lexer & Parser initialisieren
    lexer = VHDLLexer(input_stream)
    stream = CommonTokenStream(lexer)
    parser = VHDLParser(stream)
    
    # Start-Regel aufrufen (muss in deiner VHDLParser.g4 definiert sein)
    # Laut deinem Log scheint 'startRule' zu existieren [cite: 13]
    tree = parser.startRule()
    
    # Ausgabe des Baums im Lisp-Format
    print(tree.toStringTree(recog=parser))

if __name__ == '__main__':
    if len(sys.argv) > 1:
        parse(sys.argv[1])
    else:
        print("Usage: python parse_vhdl.py <file.vhd>")
