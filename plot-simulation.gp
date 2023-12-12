set terminal png
set output "plot.png"

# Set data file and separator
datafile = "./data/graphe.data"
separator = ' '  # Change this if your data file uses a different separator
 
set yrange [0:0.4] 

# Plot the data
plot datafile using 1:2 with lines title "Init Condition", \
     datafile using 1:3 with lines title "Upwind Solution", \
     datafile using 1:4 with lines title "Lax solution", \
     datafile using 1:5 with lines title "Exacte solution" 

# Add labels and title
set xlabel "t"
set ylabel "u"
set title "Solutions"


# Display the plot
replot

