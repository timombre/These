f(x)= x*a+b
a=-1
b=-10
fit f(x) "./moyenned" u (log(($1-1)/2)):(log($2/6)):(log(($3+$2)/(6*$2))) via a,b
g(x)=exp(b)*x**a
h(x)= (exp(b)/x)/3
set terminal postscript eps color "Times-Roman" 24
set output 'diffusioncoefficient.eps'
#set yrange [0.00001:0.01]
set xrange [6.0:500.0]
#set size square
set logscale
set xlabel "Polymer size"
set ylabel "Diffusion coefficient"
set multiplot
plot "./moyenned" u (($1-1)/2):($2/6):($3/6) notitle with yerrorbars, "" u (($1-1)/2):($2/6):($3/6) title "Computed results" with points linetype 1 pointtype 1, h(x) title "Theoretical -1 slope" with lines linetype -1 , g(x) title "Power law fit" with lines linetype 2 linewidth 2, "" using (90):(0.00018):(sprintf(" Power: %.2f, Prefactor: %.4f",a,exp(b))) notitle with labels 
unset multiplot


set output
#Appel extérieur à epstopdf pour transformer le fichier eps en pdf.
!epstopdf --outfile=diffusioncoefficient.pdf diffusioncoefficient.eps 
quit

#297.089436154883
#0.0052214072808247
