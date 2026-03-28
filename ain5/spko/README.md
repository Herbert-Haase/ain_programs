# set up antlr4 env
echo alias antlr4='java -jar /path/to/antlr-4.13.1-complete.jar' >> ~/.zshrc
# set up python packages
pip install --require-virtualenv antlr4-python3-runtime

# download antlr4
curl -O https://www.antlr.org/download/antlr-4.13.1-complete.jar

# generate lexer, parser, visitor pattern, listener pattern
antlr4 -Dlanguage=Python3 -visitor Calc.g4
# start application
python3 main.py
