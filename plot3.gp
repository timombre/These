f(x)=exp(-x/a)
a=10
fit f(x) "<cat ./N257/moycorrelendtoend.txt|awk '{if($1<100000){print$0}}'" u ($1*100):2 via a
set terminal postscript eps color "Times-Roman" 24
set output 'correlendtoend.eps'
set yrange [-0.2:1.2]
set xrange [10:2000000000.0]
#set size square
set logscale x
set xlabel "Time interval size"
set ylabel "Correlation function of the end to end distance"
set multiplot
plot "<cat ./N9/moycorrelendtoend.txt|awk '{if($1<1000){print$0}}'" u ($1*100):2 title "N=4","<cat ./N17/moycorrelendtoend.txt|awk '{if($1<1000){print$0}}'" u ($1*100):2 title "N=8" ,"<cat ./N35/moycorrelendtoend.txt|awk '{if($1<10000){print$0}}'" u ($1*100):2 title "N=17","<cat ./N65/moycorrelendtoend.txt|awk '{if($1<1700){print$0}}'" u ($1*100):2 title "N=32","<cat ./N129/moycorrelendtoend.txt|awk '{if($1<2900){print$0}}'" u ($1*100):2 title "N=64","<cat ./N257/moycorrelendtoend.txt|awk '{if($1<10000000){print$0}}'" u ($1*100):2 title "N=128","<cat ./N513/moycorrelendtoend.txt|awk '{if($1<10000000){print$0}}'" u ($1*100):2 title "N=256", f(x) title "fit" linewidth 2, 1/exp(1) title "threshold" linewidth 2
#, "" using (200):(0.001):(sprintf(" Power: %.3f, Prefactor: %.3f",a,exp(b))) notitle with labels 
unset multiplot


set output
#Appel extérieur à epstopdf pour transformer le fichier eps en pdf.
!epstopdf --outfile=correlendtoend.pdf correlendtoend.eps 
quit
