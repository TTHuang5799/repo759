import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages

t_values = range(1, 21)

times = []

with open("task1c.txt") as f:
    for i in t_values:
        f.readline()
        f.readline() 
        f.readline()  
        times.append(float(f.readline()))
        f.readline() 
        
with PdfPages("task1.pdf") as pdf:
    plt.plot(t_values, times, "o-")
    plt.xlabel("Number of Threads (t)")
    plt.ylabel("Time (ms)")
    plt.title("Time Taken by mmul Function vs. Number of Threads")
    plt.xticks(t_values)
    pdf.savefig()

plt.show()
