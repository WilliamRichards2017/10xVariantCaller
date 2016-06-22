##Line Graph showing the coverage of barcodes across the genome
##Approximates bargraph with large data-set, loads fast
import matplotlib as mpl
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cbook as cbook

def read_datafile(file_name):
    data = np.loadtxt(file_name, delimiter=',', skiprows=1)
    return data

data = read_datafile('/Users/awr/Desktop/10xVarCall/10xVarCall/barCodeFreq.csv')

x= data[:,0]
y= data[:,1]

fig = plt.figure()

ax1 = fig.add_subplot(111)

ax1.set_title("Barcode Coverage")
ax1.set_xlabel('Barcode ID')
ax1.set_ylabel('Frequency')

ax1.plot(x,y, c='r')

leg = ax1.legend()

plt.show()
