# Generated from VHDLParser.g4 by ANTLR 4.13.1
from antlr4 import *
if "." in __name__:
    from .VHDLParser import VHDLParser
else:
    from VHDLParser import VHDLParser

# This class defines a complete listener for a parse tree produced by VHDLParser.
class VHDLParserListener(ParseTreeListener):

    # Enter a parse tree produced by VHDLParser#startRule.
    def enterStartRule(self, ctx:VHDLParser.StartRuleContext):
        pass

    # Exit a parse tree produced by VHDLParser#startRule.
    def exitStartRule(self, ctx:VHDLParser.StartRuleContext):
        pass


    # Enter a parse tree produced by VHDLParser#libs.
    def enterLibs(self, ctx:VHDLParser.LibsContext):
        pass

    # Exit a parse tree produced by VHDLParser#libs.
    def exitLibs(self, ctx:VHDLParser.LibsContext):
        pass


    # Enter a parse tree produced by VHDLParser#lib_declaration.
    def enterLib_declaration(self, ctx:VHDLParser.Lib_declarationContext):
        pass

    # Exit a parse tree produced by VHDLParser#lib_declaration.
    def exitLib_declaration(self, ctx:VHDLParser.Lib_declarationContext):
        pass


    # Enter a parse tree produced by VHDLParser#use_declaration.
    def enterUse_declaration(self, ctx:VHDLParser.Use_declarationContext):
        pass

    # Exit a parse tree produced by VHDLParser#use_declaration.
    def exitUse_declaration(self, ctx:VHDLParser.Use_declarationContext):
        pass


    # Enter a parse tree produced by VHDLParser#units.
    def enterUnits(self, ctx:VHDLParser.UnitsContext):
        pass

    # Exit a parse tree produced by VHDLParser#units.
    def exitUnits(self, ctx:VHDLParser.UnitsContext):
        pass


    # Enter a parse tree produced by VHDLParser#entity_unit.
    def enterEntity_unit(self, ctx:VHDLParser.Entity_unitContext):
        pass

    # Exit a parse tree produced by VHDLParser#entity_unit.
    def exitEntity_unit(self, ctx:VHDLParser.Entity_unitContext):
        pass


    # Enter a parse tree produced by VHDLParser#port_obj.
    def enterPort_obj(self, ctx:VHDLParser.Port_objContext):
        pass

    # Exit a parse tree produced by VHDLParser#port_obj.
    def exitPort_obj(self, ctx:VHDLParser.Port_objContext):
        pass


    # Enter a parse tree produced by VHDLParser#port_list.
    def enterPort_list(self, ctx:VHDLParser.Port_listContext):
        pass

    # Exit a parse tree produced by VHDLParser#port_list.
    def exitPort_list(self, ctx:VHDLParser.Port_listContext):
        pass


    # Enter a parse tree produced by VHDLParser#in_out_signal.
    def enterIn_out_signal(self, ctx:VHDLParser.In_out_signalContext):
        pass

    # Exit a parse tree produced by VHDLParser#in_out_signal.
    def exitIn_out_signal(self, ctx:VHDLParser.In_out_signalContext):
        pass


    # Enter a parse tree produced by VHDLParser#arch_unit.
    def enterArch_unit(self, ctx:VHDLParser.Arch_unitContext):
        pass

    # Exit a parse tree produced by VHDLParser#arch_unit.
    def exitArch_unit(self, ctx:VHDLParser.Arch_unitContext):
        pass


    # Enter a parse tree produced by VHDLParser#signal_obj.
    def enterSignal_obj(self, ctx:VHDLParser.Signal_objContext):
        pass

    # Exit a parse tree produced by VHDLParser#signal_obj.
    def exitSignal_obj(self, ctx:VHDLParser.Signal_objContext):
        pass


    # Enter a parse tree produced by VHDLParser#statement.
    def enterStatement(self, ctx:VHDLParser.StatementContext):
        pass

    # Exit a parse tree produced by VHDLParser#statement.
    def exitStatement(self, ctx:VHDLParser.StatementContext):
        pass


    # Enter a parse tree produced by VHDLParser#expression.
    def enterExpression(self, ctx:VHDLParser.ExpressionContext):
        pass

    # Exit a parse tree produced by VHDLParser#expression.
    def exitExpression(self, ctx:VHDLParser.ExpressionContext):
        pass


    # Enter a parse tree produced by VHDLParser#orExpr.
    def enterOrExpr(self, ctx:VHDLParser.OrExprContext):
        pass

    # Exit a parse tree produced by VHDLParser#orExpr.
    def exitOrExpr(self, ctx:VHDLParser.OrExprContext):
        pass


    # Enter a parse tree produced by VHDLParser#andExpr.
    def enterAndExpr(self, ctx:VHDLParser.AndExprContext):
        pass

    # Exit a parse tree produced by VHDLParser#andExpr.
    def exitAndExpr(self, ctx:VHDLParser.AndExprContext):
        pass


    # Enter a parse tree produced by VHDLParser#notExpr.
    def enterNotExpr(self, ctx:VHDLParser.NotExprContext):
        pass

    # Exit a parse tree produced by VHDLParser#notExpr.
    def exitNotExpr(self, ctx:VHDLParser.NotExprContext):
        pass


    # Enter a parse tree produced by VHDLParser#primary.
    def enterPrimary(self, ctx:VHDLParser.PrimaryContext):
        pass

    # Exit a parse tree produced by VHDLParser#primary.
    def exitPrimary(self, ctx:VHDLParser.PrimaryContext):
        pass



del VHDLParser