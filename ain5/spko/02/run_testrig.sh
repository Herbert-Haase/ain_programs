#!/bin/bash
# run_testrig.sh

# 1. Generiere den Java-Code (ohne -Dlanguage ist Java der Standard)
antlr4 VHDLLexer.g4 VHDLParser.g4

# 2. Kompiliere die generierten Java-Dateien
javac VHDL*.java

# 3. Starte das TestRig (grun) mit GUI
# WICHTIG: Ersetze 'startRule' auch hier mit dem Namen deiner obersten Parser-Regel!
# Die antlr4-Pakete von Arch bringen das Alias 'grun' praktischerweise oft schon mit.
# Falls nicht, ist es: java org.antlr.v4.gui.TestRig VHDL startRule -gui beispiel_vhdl.vhd

grun VHDL startRule -gui beispiel_vhdl.vhd
