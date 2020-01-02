# Execute este makefile para criar lista de símbolos e abreviaturas

target_A= ./ppgmmc/ppgmmc.ist
target_B= thesis.abx
target_C= thesis.syx
target_D= thesis.lab
target_E= thesis.los

FLAG = -s
COMP = makeindex
COMP2= pdflatex

all:   simb abrev c_latex

abrev : 
	if [ -f $(target_B) ] ;	then \
		$(COMP) $(FLAG) $(target_A)  -o $(target_D)  $(target_B) ;\
	fi;

simb  :
	if [ -f $(target_C) ]; then \
		$(COMP) $(FLAG) $(target_A)  -o $(target_E)  $(target_C) ;\
	fi;

c_latex :
	$(COMP2) thesis.tex
