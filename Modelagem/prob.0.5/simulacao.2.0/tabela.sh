#!/bin/bash
cont=1;

exec 4<'VTH2S1.dat'
exec 5<'G1.dat'
exec 6<'G2.dat'

echo " \\begin{tabular}{|c|c|c|c|} "
echo "\\hline"
echo " Hidrel\'etrica H1 & Hidrel\'etrica H2 & Termel\'etrica T1 & Termel\'etrica T2" " \\\ "
echo "\\hline"
while  read -r linha 
do
	echo "$linha & $(head -n 1 <&4) & $(head -n 1 <&5) & $(head -n 1 <&6)"  " \\\ " 
	echo "\\hline"
	if [ $cont -eq 500 ]
	then 
		break
	fi
	let cont=$cont+1
done < VTH1S1.dat
echo "\\end{tabular}"


