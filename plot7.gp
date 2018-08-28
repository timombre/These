f(x)= x*a+b
a=2
b=1
fit f(x) "./moyenneendtoendN.txt" u (log(($1-1)/2)):(log($2)) via a,b
g(x)=exp(b)*x**a
#h(x)= (exp(b)/x)/3
set terminal postscript eps color "Times-Roman" 24
set output 'endtoenddistance.eps'
#set yrange [0.00001:0.01]
set xrange [6.0:600.0]
#set size square
set key left top
set logscale
set xlabel "Polymer size, N"
set ylabel "End to end distance"
set multiplot
plot "./moyenneendtoendN.txt" u (($1-1)/2):($2):($3*sqrt((5*$4)/300000)) notitle with yerrorbars linewidth 3, "" u (($1-1)/2):($2):($3*sqrt((5*$4)/1732.050807569)) title "Computed results" with points linetype 1 pointtype 1 linewidth 3, g(x) title "Power law fit" with lines linetype 2 linewidth 3, "" using (30):(300):(sprintf(" Power: %.3f, Prefactor: %.3f",a,exp(b))) notitle with labels 
unset key
unset multiplot


set output
#Appel extérieur à epstopdf pour transformer le fichier eps en pdf.
!epstopdf --outfile=endtoenddistance.pdf endtoenddistance.eps 
quit


