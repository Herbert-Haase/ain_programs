# Generated from VHDLParser.g4 by ANTLR 4.13.1
# encoding: utf-8
from antlr4 import *
from io import StringIO
import sys
if sys.version_info[1] > 5:
	from typing import TextIO
else:
	from typing.io import TextIO

def serializedATN():
    return [
        4,1,27,179,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
        6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,
        2,14,7,14,2,15,7,15,2,16,7,16,1,0,5,0,36,8,0,10,0,12,0,39,9,0,1,
        0,4,0,42,8,0,11,0,12,0,43,1,0,1,0,1,1,1,1,3,1,50,8,1,1,2,1,2,1,2,
        1,2,1,3,1,3,1,3,4,3,59,8,3,11,3,12,3,60,1,3,1,3,1,3,1,4,1,4,3,4,
        68,8,4,1,5,1,5,1,5,1,5,3,5,74,8,5,1,5,1,5,3,5,78,8,5,1,5,1,5,1,6,
        1,6,1,6,1,6,1,6,1,6,1,7,4,7,89,8,7,11,7,12,7,90,1,8,1,8,1,8,5,8,
        96,8,8,10,8,12,8,99,9,8,1,8,1,8,1,8,1,8,3,8,105,8,8,1,9,1,9,1,9,
        1,9,1,9,1,9,5,9,113,8,9,10,9,12,9,116,9,9,1,9,1,9,5,9,120,8,9,10,
        9,12,9,123,9,9,1,9,1,9,3,9,127,8,9,1,9,1,9,1,10,1,10,1,10,1,10,5,
        10,135,8,10,10,10,12,10,138,9,10,1,10,1,10,1,10,1,10,1,11,1,11,1,
        11,1,11,1,11,1,12,1,12,1,13,1,13,1,13,5,13,154,8,13,10,13,12,13,
        157,9,13,1,14,1,14,1,14,5,14,162,8,14,10,14,12,14,165,9,14,1,15,
        1,15,1,15,3,15,170,8,15,1,16,1,16,1,16,1,16,1,16,3,16,177,8,16,1,
        16,0,0,17,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,0,2,2,0,
        14,14,26,26,1,0,11,12,179,0,37,1,0,0,0,2,49,1,0,0,0,4,51,1,0,0,0,
        6,55,1,0,0,0,8,67,1,0,0,0,10,69,1,0,0,0,12,81,1,0,0,0,14,88,1,0,
        0,0,16,92,1,0,0,0,18,106,1,0,0,0,20,130,1,0,0,0,22,143,1,0,0,0,24,
        148,1,0,0,0,26,150,1,0,0,0,28,158,1,0,0,0,30,169,1,0,0,0,32,176,
        1,0,0,0,34,36,3,2,1,0,35,34,1,0,0,0,36,39,1,0,0,0,37,35,1,0,0,0,
        37,38,1,0,0,0,38,41,1,0,0,0,39,37,1,0,0,0,40,42,3,8,4,0,41,40,1,
        0,0,0,42,43,1,0,0,0,43,41,1,0,0,0,43,44,1,0,0,0,44,45,1,0,0,0,45,
        46,5,0,0,1,46,1,1,0,0,0,47,50,3,4,2,0,48,50,3,6,3,0,49,47,1,0,0,
        0,49,48,1,0,0,0,50,3,1,0,0,0,51,52,5,2,0,0,52,53,5,26,0,0,53,54,
        5,23,0,0,54,5,1,0,0,0,55,58,5,3,0,0,56,57,5,26,0,0,57,59,5,25,0,
        0,58,56,1,0,0,0,59,60,1,0,0,0,60,58,1,0,0,0,60,61,1,0,0,0,61,62,
        1,0,0,0,62,63,7,0,0,0,63,64,5,23,0,0,64,7,1,0,0,0,65,68,3,10,5,0,
        66,68,3,18,9,0,67,65,1,0,0,0,67,66,1,0,0,0,68,9,1,0,0,0,69,70,5,
        4,0,0,70,71,5,26,0,0,71,73,5,5,0,0,72,74,3,12,6,0,73,72,1,0,0,0,
        73,74,1,0,0,0,74,75,1,0,0,0,75,77,5,7,0,0,76,78,5,26,0,0,77,76,1,
        0,0,0,77,78,1,0,0,0,78,79,1,0,0,0,79,80,5,23,0,0,80,11,1,0,0,0,81,
        82,5,6,0,0,82,83,5,20,0,0,83,84,3,14,7,0,84,85,5,21,0,0,85,86,5,
        23,0,0,86,13,1,0,0,0,87,89,3,16,8,0,88,87,1,0,0,0,89,90,1,0,0,0,
        90,88,1,0,0,0,90,91,1,0,0,0,91,15,1,0,0,0,92,97,5,26,0,0,93,94,5,
        24,0,0,94,96,5,26,0,0,95,93,1,0,0,0,96,99,1,0,0,0,97,95,1,0,0,0,
        97,98,1,0,0,0,98,100,1,0,0,0,99,97,1,0,0,0,100,101,5,22,0,0,101,
        102,7,1,0,0,102,104,5,15,0,0,103,105,5,23,0,0,104,103,1,0,0,0,104,
        105,1,0,0,0,105,17,1,0,0,0,106,107,5,8,0,0,107,108,5,26,0,0,108,
        109,5,13,0,0,109,110,5,26,0,0,110,114,5,5,0,0,111,113,3,20,10,0,
        112,111,1,0,0,0,113,116,1,0,0,0,114,112,1,0,0,0,114,115,1,0,0,0,
        115,117,1,0,0,0,116,114,1,0,0,0,117,121,5,10,0,0,118,120,3,22,11,
        0,119,118,1,0,0,0,120,123,1,0,0,0,121,119,1,0,0,0,121,122,1,0,0,
        0,122,124,1,0,0,0,123,121,1,0,0,0,124,126,5,7,0,0,125,127,5,26,0,
        0,126,125,1,0,0,0,126,127,1,0,0,0,127,128,1,0,0,0,128,129,5,23,0,
        0,129,19,1,0,0,0,130,131,5,9,0,0,131,136,5,26,0,0,132,133,5,24,0,
        0,133,135,5,26,0,0,134,132,1,0,0,0,135,138,1,0,0,0,136,134,1,0,0,
        0,136,137,1,0,0,0,137,139,1,0,0,0,138,136,1,0,0,0,139,140,5,22,0,
        0,140,141,5,15,0,0,141,142,5,23,0,0,142,21,1,0,0,0,143,144,5,26,
        0,0,144,145,5,19,0,0,145,146,3,24,12,0,146,147,5,23,0,0,147,23,1,
        0,0,0,148,149,3,26,13,0,149,25,1,0,0,0,150,155,3,28,14,0,151,152,
        5,17,0,0,152,154,3,28,14,0,153,151,1,0,0,0,154,157,1,0,0,0,155,153,
        1,0,0,0,155,156,1,0,0,0,156,27,1,0,0,0,157,155,1,0,0,0,158,163,3,
        30,15,0,159,160,5,16,0,0,160,162,3,30,15,0,161,159,1,0,0,0,162,165,
        1,0,0,0,163,161,1,0,0,0,163,164,1,0,0,0,164,29,1,0,0,0,165,163,1,
        0,0,0,166,167,5,18,0,0,167,170,3,30,15,0,168,170,3,32,16,0,169,166,
        1,0,0,0,169,168,1,0,0,0,170,31,1,0,0,0,171,177,5,26,0,0,172,173,
        5,20,0,0,173,174,3,24,12,0,174,175,5,21,0,0,175,177,1,0,0,0,176,
        171,1,0,0,0,176,172,1,0,0,0,177,33,1,0,0,0,18,37,43,49,60,67,73,
        77,90,97,104,114,121,126,136,155,163,169,176
    ]

class VHDLParser ( Parser ):

    grammarFileName = "VHDLParser.g4"

    atn = ATNDeserializer().deserialize(serializedATN())

    decisionsToDFA = [ DFA(ds, i) for i, ds in enumerate(atn.decisionToState) ]

    sharedContextCache = PredictionContextCache()

    literalNames = [ "<INVALID>", "<INVALID>", "'library'", "'use'", "'entity'", 
                     "'is'", "'port'", "'end'", "'architecture'", "'signal'", 
                     "'begin'", "'in'", "'out'", "'of'", "'all'", "'std_logic'", 
                     "'and'", "'or'", "'not'", "'<='", "'('", "')'", "':'", 
                     "';'", "','", "'.'" ]

    symbolicNames = [ "<INVALID>", "COMMENT", "LIBRARY", "USE", "ENTITY", 
                      "IS", "PORT", "END", "ARCHITECTURE", "SIGNAL", "BEGIN", 
                      "IN", "OUT", "OF", "ALL", "STD_LOGIC", "AND", "OR", 
                      "NOT", "ASSIGN", "LPAREN", "RPAREN", "COLON", "SEMI", 
                      "COMMA", "DOT", "ID", "WS" ]

    RULE_startRule = 0
    RULE_libs = 1
    RULE_lib_declaration = 2
    RULE_use_declaration = 3
    RULE_units = 4
    RULE_entity_unit = 5
    RULE_port_obj = 6
    RULE_port_list = 7
    RULE_in_out_signal = 8
    RULE_arch_unit = 9
    RULE_signal_obj = 10
    RULE_statement = 11
    RULE_expression = 12
    RULE_orExpr = 13
    RULE_andExpr = 14
    RULE_notExpr = 15
    RULE_primary = 16

    ruleNames =  [ "startRule", "libs", "lib_declaration", "use_declaration", 
                   "units", "entity_unit", "port_obj", "port_list", "in_out_signal", 
                   "arch_unit", "signal_obj", "statement", "expression", 
                   "orExpr", "andExpr", "notExpr", "primary" ]

    EOF = Token.EOF
    COMMENT=1
    LIBRARY=2
    USE=3
    ENTITY=4
    IS=5
    PORT=6
    END=7
    ARCHITECTURE=8
    SIGNAL=9
    BEGIN=10
    IN=11
    OUT=12
    OF=13
    ALL=14
    STD_LOGIC=15
    AND=16
    OR=17
    NOT=18
    ASSIGN=19
    LPAREN=20
    RPAREN=21
    COLON=22
    SEMI=23
    COMMA=24
    DOT=25
    ID=26
    WS=27

    def __init__(self, input:TokenStream, output:TextIO = sys.stdout):
        super().__init__(input, output)
        self.checkVersion("4.13.1")
        self._interp = ParserATNSimulator(self, self.atn, self.decisionsToDFA, self.sharedContextCache)
        self._predicates = None




    class StartRuleContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def EOF(self):
            return self.getToken(VHDLParser.EOF, 0)

        def libs(self, i:int=None):
            if i is None:
                return self.getTypedRuleContexts(VHDLParser.LibsContext)
            else:
                return self.getTypedRuleContext(VHDLParser.LibsContext,i)


        def units(self, i:int=None):
            if i is None:
                return self.getTypedRuleContexts(VHDLParser.UnitsContext)
            else:
                return self.getTypedRuleContext(VHDLParser.UnitsContext,i)


        def getRuleIndex(self):
            return VHDLParser.RULE_startRule

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterStartRule" ):
                listener.enterStartRule(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitStartRule" ):
                listener.exitStartRule(self)




    def startRule(self):

        localctx = VHDLParser.StartRuleContext(self, self._ctx, self.state)
        self.enterRule(localctx, 0, self.RULE_startRule)
        self._la = 0 # Token type
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 37
            self._errHandler.sync(self)
            _la = self._input.LA(1)
            while _la==2 or _la==3:
                self.state = 34
                self.libs()
                self.state = 39
                self._errHandler.sync(self)
                _la = self._input.LA(1)

            self.state = 41 
            self._errHandler.sync(self)
            _la = self._input.LA(1)
            while True:
                self.state = 40
                self.units()
                self.state = 43 
                self._errHandler.sync(self)
                _la = self._input.LA(1)
                if not (_la==4 or _la==8):
                    break

            self.state = 45
            self.match(VHDLParser.EOF)
        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class LibsContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def lib_declaration(self):
            return self.getTypedRuleContext(VHDLParser.Lib_declarationContext,0)


        def use_declaration(self):
            return self.getTypedRuleContext(VHDLParser.Use_declarationContext,0)


        def getRuleIndex(self):
            return VHDLParser.RULE_libs

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterLibs" ):
                listener.enterLibs(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitLibs" ):
                listener.exitLibs(self)




    def libs(self):

        localctx = VHDLParser.LibsContext(self, self._ctx, self.state)
        self.enterRule(localctx, 2, self.RULE_libs)
        try:
            self.state = 49
            self._errHandler.sync(self)
            token = self._input.LA(1)
            if token in [2]:
                self.enterOuterAlt(localctx, 1)
                self.state = 47
                self.lib_declaration()
                pass
            elif token in [3]:
                self.enterOuterAlt(localctx, 2)
                self.state = 48
                self.use_declaration()
                pass
            else:
                raise NoViableAltException(self)

        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class Lib_declarationContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def LIBRARY(self):
            return self.getToken(VHDLParser.LIBRARY, 0)

        def ID(self):
            return self.getToken(VHDLParser.ID, 0)

        def SEMI(self):
            return self.getToken(VHDLParser.SEMI, 0)

        def getRuleIndex(self):
            return VHDLParser.RULE_lib_declaration

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterLib_declaration" ):
                listener.enterLib_declaration(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitLib_declaration" ):
                listener.exitLib_declaration(self)




    def lib_declaration(self):

        localctx = VHDLParser.Lib_declarationContext(self, self._ctx, self.state)
        self.enterRule(localctx, 4, self.RULE_lib_declaration)
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 51
            self.match(VHDLParser.LIBRARY)
            self.state = 52
            self.match(VHDLParser.ID)
            self.state = 53
            self.match(VHDLParser.SEMI)
        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class Use_declarationContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def USE(self):
            return self.getToken(VHDLParser.USE, 0)

        def SEMI(self):
            return self.getToken(VHDLParser.SEMI, 0)

        def ID(self, i:int=None):
            if i is None:
                return self.getTokens(VHDLParser.ID)
            else:
                return self.getToken(VHDLParser.ID, i)

        def ALL(self):
            return self.getToken(VHDLParser.ALL, 0)

        def DOT(self, i:int=None):
            if i is None:
                return self.getTokens(VHDLParser.DOT)
            else:
                return self.getToken(VHDLParser.DOT, i)

        def getRuleIndex(self):
            return VHDLParser.RULE_use_declaration

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterUse_declaration" ):
                listener.enterUse_declaration(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitUse_declaration" ):
                listener.exitUse_declaration(self)




    def use_declaration(self):

        localctx = VHDLParser.Use_declarationContext(self, self._ctx, self.state)
        self.enterRule(localctx, 6, self.RULE_use_declaration)
        self._la = 0 # Token type
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 55
            self.match(VHDLParser.USE)
            self.state = 58 
            self._errHandler.sync(self)
            _alt = 1
            while _alt!=2 and _alt!=ATN.INVALID_ALT_NUMBER:
                if _alt == 1:
                    self.state = 56
                    self.match(VHDLParser.ID)
                    self.state = 57
                    self.match(VHDLParser.DOT)

                else:
                    raise NoViableAltException(self)
                self.state = 60 
                self._errHandler.sync(self)
                _alt = self._interp.adaptivePredict(self._input,3,self._ctx)

            self.state = 62
            _la = self._input.LA(1)
            if not(_la==14 or _la==26):
                self._errHandler.recoverInline(self)
            else:
                self._errHandler.reportMatch(self)
                self.consume()
            self.state = 63
            self.match(VHDLParser.SEMI)
        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class UnitsContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def entity_unit(self):
            return self.getTypedRuleContext(VHDLParser.Entity_unitContext,0)


        def arch_unit(self):
            return self.getTypedRuleContext(VHDLParser.Arch_unitContext,0)


        def getRuleIndex(self):
            return VHDLParser.RULE_units

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterUnits" ):
                listener.enterUnits(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitUnits" ):
                listener.exitUnits(self)




    def units(self):

        localctx = VHDLParser.UnitsContext(self, self._ctx, self.state)
        self.enterRule(localctx, 8, self.RULE_units)
        try:
            self.state = 67
            self._errHandler.sync(self)
            token = self._input.LA(1)
            if token in [4]:
                self.enterOuterAlt(localctx, 1)
                self.state = 65
                self.entity_unit()
                pass
            elif token in [8]:
                self.enterOuterAlt(localctx, 2)
                self.state = 66
                self.arch_unit()
                pass
            else:
                raise NoViableAltException(self)

        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class Entity_unitContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def ENTITY(self):
            return self.getToken(VHDLParser.ENTITY, 0)

        def ID(self, i:int=None):
            if i is None:
                return self.getTokens(VHDLParser.ID)
            else:
                return self.getToken(VHDLParser.ID, i)

        def IS(self):
            return self.getToken(VHDLParser.IS, 0)

        def END(self):
            return self.getToken(VHDLParser.END, 0)

        def SEMI(self):
            return self.getToken(VHDLParser.SEMI, 0)

        def port_obj(self):
            return self.getTypedRuleContext(VHDLParser.Port_objContext,0)


        def getRuleIndex(self):
            return VHDLParser.RULE_entity_unit

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterEntity_unit" ):
                listener.enterEntity_unit(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitEntity_unit" ):
                listener.exitEntity_unit(self)




    def entity_unit(self):

        localctx = VHDLParser.Entity_unitContext(self, self._ctx, self.state)
        self.enterRule(localctx, 10, self.RULE_entity_unit)
        self._la = 0 # Token type
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 69
            self.match(VHDLParser.ENTITY)
            self.state = 70
            self.match(VHDLParser.ID)
            self.state = 71
            self.match(VHDLParser.IS)
            self.state = 73
            self._errHandler.sync(self)
            _la = self._input.LA(1)
            if _la==6:
                self.state = 72
                self.port_obj()


            self.state = 75
            self.match(VHDLParser.END)
            self.state = 77
            self._errHandler.sync(self)
            _la = self._input.LA(1)
            if _la==26:
                self.state = 76
                self.match(VHDLParser.ID)


            self.state = 79
            self.match(VHDLParser.SEMI)
        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class Port_objContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def PORT(self):
            return self.getToken(VHDLParser.PORT, 0)

        def LPAREN(self):
            return self.getToken(VHDLParser.LPAREN, 0)

        def port_list(self):
            return self.getTypedRuleContext(VHDLParser.Port_listContext,0)


        def RPAREN(self):
            return self.getToken(VHDLParser.RPAREN, 0)

        def SEMI(self):
            return self.getToken(VHDLParser.SEMI, 0)

        def getRuleIndex(self):
            return VHDLParser.RULE_port_obj

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterPort_obj" ):
                listener.enterPort_obj(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitPort_obj" ):
                listener.exitPort_obj(self)




    def port_obj(self):

        localctx = VHDLParser.Port_objContext(self, self._ctx, self.state)
        self.enterRule(localctx, 12, self.RULE_port_obj)
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 81
            self.match(VHDLParser.PORT)
            self.state = 82
            self.match(VHDLParser.LPAREN)
            self.state = 83
            self.port_list()
            self.state = 84
            self.match(VHDLParser.RPAREN)
            self.state = 85
            self.match(VHDLParser.SEMI)
        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class Port_listContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def in_out_signal(self, i:int=None):
            if i is None:
                return self.getTypedRuleContexts(VHDLParser.In_out_signalContext)
            else:
                return self.getTypedRuleContext(VHDLParser.In_out_signalContext,i)


        def getRuleIndex(self):
            return VHDLParser.RULE_port_list

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterPort_list" ):
                listener.enterPort_list(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitPort_list" ):
                listener.exitPort_list(self)




    def port_list(self):

        localctx = VHDLParser.Port_listContext(self, self._ctx, self.state)
        self.enterRule(localctx, 14, self.RULE_port_list)
        self._la = 0 # Token type
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 88 
            self._errHandler.sync(self)
            _la = self._input.LA(1)
            while True:
                self.state = 87
                self.in_out_signal()
                self.state = 90 
                self._errHandler.sync(self)
                _la = self._input.LA(1)
                if not (_la==26):
                    break

        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class In_out_signalContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def ID(self, i:int=None):
            if i is None:
                return self.getTokens(VHDLParser.ID)
            else:
                return self.getToken(VHDLParser.ID, i)

        def COLON(self):
            return self.getToken(VHDLParser.COLON, 0)

        def STD_LOGIC(self):
            return self.getToken(VHDLParser.STD_LOGIC, 0)

        def IN(self):
            return self.getToken(VHDLParser.IN, 0)

        def OUT(self):
            return self.getToken(VHDLParser.OUT, 0)

        def COMMA(self, i:int=None):
            if i is None:
                return self.getTokens(VHDLParser.COMMA)
            else:
                return self.getToken(VHDLParser.COMMA, i)

        def SEMI(self):
            return self.getToken(VHDLParser.SEMI, 0)

        def getRuleIndex(self):
            return VHDLParser.RULE_in_out_signal

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterIn_out_signal" ):
                listener.enterIn_out_signal(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitIn_out_signal" ):
                listener.exitIn_out_signal(self)




    def in_out_signal(self):

        localctx = VHDLParser.In_out_signalContext(self, self._ctx, self.state)
        self.enterRule(localctx, 16, self.RULE_in_out_signal)
        self._la = 0 # Token type
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 92
            self.match(VHDLParser.ID)
            self.state = 97
            self._errHandler.sync(self)
            _la = self._input.LA(1)
            while _la==24:
                self.state = 93
                self.match(VHDLParser.COMMA)
                self.state = 94
                self.match(VHDLParser.ID)
                self.state = 99
                self._errHandler.sync(self)
                _la = self._input.LA(1)

            self.state = 100
            self.match(VHDLParser.COLON)
            self.state = 101
            _la = self._input.LA(1)
            if not(_la==11 or _la==12):
                self._errHandler.recoverInline(self)
            else:
                self._errHandler.reportMatch(self)
                self.consume()
            self.state = 102
            self.match(VHDLParser.STD_LOGIC)
            self.state = 104
            self._errHandler.sync(self)
            _la = self._input.LA(1)
            if _la==23:
                self.state = 103
                self.match(VHDLParser.SEMI)


        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class Arch_unitContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def ARCHITECTURE(self):
            return self.getToken(VHDLParser.ARCHITECTURE, 0)

        def ID(self, i:int=None):
            if i is None:
                return self.getTokens(VHDLParser.ID)
            else:
                return self.getToken(VHDLParser.ID, i)

        def OF(self):
            return self.getToken(VHDLParser.OF, 0)

        def IS(self):
            return self.getToken(VHDLParser.IS, 0)

        def BEGIN(self):
            return self.getToken(VHDLParser.BEGIN, 0)

        def END(self):
            return self.getToken(VHDLParser.END, 0)

        def SEMI(self):
            return self.getToken(VHDLParser.SEMI, 0)

        def signal_obj(self, i:int=None):
            if i is None:
                return self.getTypedRuleContexts(VHDLParser.Signal_objContext)
            else:
                return self.getTypedRuleContext(VHDLParser.Signal_objContext,i)


        def statement(self, i:int=None):
            if i is None:
                return self.getTypedRuleContexts(VHDLParser.StatementContext)
            else:
                return self.getTypedRuleContext(VHDLParser.StatementContext,i)


        def getRuleIndex(self):
            return VHDLParser.RULE_arch_unit

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterArch_unit" ):
                listener.enterArch_unit(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitArch_unit" ):
                listener.exitArch_unit(self)




    def arch_unit(self):

        localctx = VHDLParser.Arch_unitContext(self, self._ctx, self.state)
        self.enterRule(localctx, 18, self.RULE_arch_unit)
        self._la = 0 # Token type
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 106
            self.match(VHDLParser.ARCHITECTURE)
            self.state = 107
            self.match(VHDLParser.ID)
            self.state = 108
            self.match(VHDLParser.OF)
            self.state = 109
            self.match(VHDLParser.ID)
            self.state = 110
            self.match(VHDLParser.IS)
            self.state = 114
            self._errHandler.sync(self)
            _la = self._input.LA(1)
            while _la==9:
                self.state = 111
                self.signal_obj()
                self.state = 116
                self._errHandler.sync(self)
                _la = self._input.LA(1)

            self.state = 117
            self.match(VHDLParser.BEGIN)
            self.state = 121
            self._errHandler.sync(self)
            _la = self._input.LA(1)
            while _la==26:
                self.state = 118
                self.statement()
                self.state = 123
                self._errHandler.sync(self)
                _la = self._input.LA(1)

            self.state = 124
            self.match(VHDLParser.END)
            self.state = 126
            self._errHandler.sync(self)
            _la = self._input.LA(1)
            if _la==26:
                self.state = 125
                self.match(VHDLParser.ID)


            self.state = 128
            self.match(VHDLParser.SEMI)
        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class Signal_objContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def SIGNAL(self):
            return self.getToken(VHDLParser.SIGNAL, 0)

        def ID(self, i:int=None):
            if i is None:
                return self.getTokens(VHDLParser.ID)
            else:
                return self.getToken(VHDLParser.ID, i)

        def COLON(self):
            return self.getToken(VHDLParser.COLON, 0)

        def STD_LOGIC(self):
            return self.getToken(VHDLParser.STD_LOGIC, 0)

        def SEMI(self):
            return self.getToken(VHDLParser.SEMI, 0)

        def COMMA(self, i:int=None):
            if i is None:
                return self.getTokens(VHDLParser.COMMA)
            else:
                return self.getToken(VHDLParser.COMMA, i)

        def getRuleIndex(self):
            return VHDLParser.RULE_signal_obj

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterSignal_obj" ):
                listener.enterSignal_obj(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitSignal_obj" ):
                listener.exitSignal_obj(self)




    def signal_obj(self):

        localctx = VHDLParser.Signal_objContext(self, self._ctx, self.state)
        self.enterRule(localctx, 20, self.RULE_signal_obj)
        self._la = 0 # Token type
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 130
            self.match(VHDLParser.SIGNAL)
            self.state = 131
            self.match(VHDLParser.ID)
            self.state = 136
            self._errHandler.sync(self)
            _la = self._input.LA(1)
            while _la==24:
                self.state = 132
                self.match(VHDLParser.COMMA)
                self.state = 133
                self.match(VHDLParser.ID)
                self.state = 138
                self._errHandler.sync(self)
                _la = self._input.LA(1)

            self.state = 139
            self.match(VHDLParser.COLON)
            self.state = 140
            self.match(VHDLParser.STD_LOGIC)
            self.state = 141
            self.match(VHDLParser.SEMI)
        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class StatementContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def ID(self):
            return self.getToken(VHDLParser.ID, 0)

        def ASSIGN(self):
            return self.getToken(VHDLParser.ASSIGN, 0)

        def expression(self):
            return self.getTypedRuleContext(VHDLParser.ExpressionContext,0)


        def SEMI(self):
            return self.getToken(VHDLParser.SEMI, 0)

        def getRuleIndex(self):
            return VHDLParser.RULE_statement

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterStatement" ):
                listener.enterStatement(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitStatement" ):
                listener.exitStatement(self)




    def statement(self):

        localctx = VHDLParser.StatementContext(self, self._ctx, self.state)
        self.enterRule(localctx, 22, self.RULE_statement)
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 143
            self.match(VHDLParser.ID)
            self.state = 144
            self.match(VHDLParser.ASSIGN)
            self.state = 145
            self.expression()
            self.state = 146
            self.match(VHDLParser.SEMI)
        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class ExpressionContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def orExpr(self):
            return self.getTypedRuleContext(VHDLParser.OrExprContext,0)


        def getRuleIndex(self):
            return VHDLParser.RULE_expression

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterExpression" ):
                listener.enterExpression(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitExpression" ):
                listener.exitExpression(self)




    def expression(self):

        localctx = VHDLParser.ExpressionContext(self, self._ctx, self.state)
        self.enterRule(localctx, 24, self.RULE_expression)
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 148
            self.orExpr()
        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class OrExprContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def andExpr(self, i:int=None):
            if i is None:
                return self.getTypedRuleContexts(VHDLParser.AndExprContext)
            else:
                return self.getTypedRuleContext(VHDLParser.AndExprContext,i)


        def OR(self, i:int=None):
            if i is None:
                return self.getTokens(VHDLParser.OR)
            else:
                return self.getToken(VHDLParser.OR, i)

        def getRuleIndex(self):
            return VHDLParser.RULE_orExpr

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterOrExpr" ):
                listener.enterOrExpr(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitOrExpr" ):
                listener.exitOrExpr(self)




    def orExpr(self):

        localctx = VHDLParser.OrExprContext(self, self._ctx, self.state)
        self.enterRule(localctx, 26, self.RULE_orExpr)
        self._la = 0 # Token type
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 150
            self.andExpr()
            self.state = 155
            self._errHandler.sync(self)
            _la = self._input.LA(1)
            while _la==17:
                self.state = 151
                self.match(VHDLParser.OR)
                self.state = 152
                self.andExpr()
                self.state = 157
                self._errHandler.sync(self)
                _la = self._input.LA(1)

        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class AndExprContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def notExpr(self, i:int=None):
            if i is None:
                return self.getTypedRuleContexts(VHDLParser.NotExprContext)
            else:
                return self.getTypedRuleContext(VHDLParser.NotExprContext,i)


        def AND(self, i:int=None):
            if i is None:
                return self.getTokens(VHDLParser.AND)
            else:
                return self.getToken(VHDLParser.AND, i)

        def getRuleIndex(self):
            return VHDLParser.RULE_andExpr

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterAndExpr" ):
                listener.enterAndExpr(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitAndExpr" ):
                listener.exitAndExpr(self)




    def andExpr(self):

        localctx = VHDLParser.AndExprContext(self, self._ctx, self.state)
        self.enterRule(localctx, 28, self.RULE_andExpr)
        self._la = 0 # Token type
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 158
            self.notExpr()
            self.state = 163
            self._errHandler.sync(self)
            _la = self._input.LA(1)
            while _la==16:
                self.state = 159
                self.match(VHDLParser.AND)
                self.state = 160
                self.notExpr()
                self.state = 165
                self._errHandler.sync(self)
                _la = self._input.LA(1)

        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class NotExprContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def NOT(self):
            return self.getToken(VHDLParser.NOT, 0)

        def notExpr(self):
            return self.getTypedRuleContext(VHDLParser.NotExprContext,0)


        def primary(self):
            return self.getTypedRuleContext(VHDLParser.PrimaryContext,0)


        def getRuleIndex(self):
            return VHDLParser.RULE_notExpr

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterNotExpr" ):
                listener.enterNotExpr(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitNotExpr" ):
                listener.exitNotExpr(self)




    def notExpr(self):

        localctx = VHDLParser.NotExprContext(self, self._ctx, self.state)
        self.enterRule(localctx, 30, self.RULE_notExpr)
        try:
            self.state = 169
            self._errHandler.sync(self)
            token = self._input.LA(1)
            if token in [18]:
                self.enterOuterAlt(localctx, 1)
                self.state = 166
                self.match(VHDLParser.NOT)
                self.state = 167
                self.notExpr()
                pass
            elif token in [20, 26]:
                self.enterOuterAlt(localctx, 2)
                self.state = 168
                self.primary()
                pass
            else:
                raise NoViableAltException(self)

        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class PrimaryContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def ID(self):
            return self.getToken(VHDLParser.ID, 0)

        def LPAREN(self):
            return self.getToken(VHDLParser.LPAREN, 0)

        def expression(self):
            return self.getTypedRuleContext(VHDLParser.ExpressionContext,0)


        def RPAREN(self):
            return self.getToken(VHDLParser.RPAREN, 0)

        def getRuleIndex(self):
            return VHDLParser.RULE_primary

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterPrimary" ):
                listener.enterPrimary(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitPrimary" ):
                listener.exitPrimary(self)




    def primary(self):

        localctx = VHDLParser.PrimaryContext(self, self._ctx, self.state)
        self.enterRule(localctx, 32, self.RULE_primary)
        try:
            self.state = 176
            self._errHandler.sync(self)
            token = self._input.LA(1)
            if token in [26]:
                self.enterOuterAlt(localctx, 1)
                self.state = 171
                self.match(VHDLParser.ID)
                pass
            elif token in [20]:
                self.enterOuterAlt(localctx, 2)
                self.state = 172
                self.match(VHDLParser.LPAREN)
                self.state = 173
                self.expression()
                self.state = 174
                self.match(VHDLParser.RPAREN)
                pass
            else:
                raise NoViableAltException(self)

        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx





