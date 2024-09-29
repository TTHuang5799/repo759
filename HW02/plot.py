import matplotlib.pyplot as plt

from matplotlib.backends.backend_pdf import PdfPages

powers = range(10, 31)

times = []

with open("task1.output") as f:
    for i in powers:
        f.readline()
        times.append(float(f.readline()))
        f.readline() 
        f.readline()  
        f.readline() 
        
with PdfPages("task1.pdf") as pdf:
    plt.plot(powers, times, "o")
    plt.xlabel("Size of the array (power)")
    plt.ylabel("Time (milliseconds)")
    plt.title("Scaling Analysis Plot")
    plt.powers(powers)
    pdf.savefig()