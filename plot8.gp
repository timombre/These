f(x)= x*a+b
a=-1
b=1
fit f(x) "./penteN.txt" u (log(($1-1)/2)):(log(3/$2)) via a,b
g(x)=exp(b)*x**a
h(x)= (exp(b)*x)/3
set terminal postscript eps color "Times-Roman" 24
set output 'penteforce.eps'
set yrange [300:6000000]
set xrange [6.0:500.0]
#set size square
set logscale
set xlabel "Polymer size"
set ylabel "Friction coefficient"
set multiplot
plot "./penteN.txt" u (($1-1)/2):(3/$2) title "Computed results" with points linetype 1 pointtype 1, h(x) title "Theoretical +1 slope" with lines linetype -1 , g(x) title "Power law fit" with lines linetype 2 linewidth 2, "" using (115):(500000):(sprintf(" Power: %.3f, Prefactor: %.3f",a,exp(b))) notitle with labels 
unset multiplot


set output
#Appel extérieur à epstopdf pour transformer le fichier eps en pdf.
!epstopdf --outfile=penteforce.pdf penteforce.eps 
quit
