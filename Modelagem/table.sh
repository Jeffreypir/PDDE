#!/bin/bash

for count in 0.1 0.2 0.5 0.7 1.0
do
	cp tabela.sh prob*$count*/
	cd prob*$count*/
	for cont in 1.0 1.4 1.5 1.6 1.8 2.0
	do
	   cp tabela.sh simulacao*$cont*/
		cd simulacao*$cont*/
		./tabela.sh > tabela$count$cont.txt
	   	cat tabela$count$cont.txt | tr '.' ',' > tabela$count$cont.dat
		cd ..
	done
	cd ..
done
