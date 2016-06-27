##Line Graph showing the coverage of barcodes across the genome
##Approximates bargraph with large data-set, loads fast
import matplotlib as mpl
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cbook as cbook

def read_datafile(file_name):
    data = np.loadtxt(file_name, delimiter=',', skiprows=1)
    return data

data = read_datafile('/Users/awr/Desktop/10xVariantCaller/10xVarCall/barCodeFreq.csv')

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


###Creates histogram of the count of the frequencies of barcodes
import collections
counter=collections.Counter(y)


print counter.keys()
print counter.values()

barCodeFreq = counter.keys()
print barCodeFreq

minBin = int(np.amin(barCodeFreq))
maxBin = int(np.amax(barCodeFreq))

bins = np.linspace(minBin, maxBin, num=5)

plt.hist(y, bins)
plt.xticks(range(minBin, maxBin))

plt.title("Barcode Frequency Distribution")
plt.xlabel('Barcode Frequency')
plt.ylabel('Count of Frequencies')

plt.show()




###Creates an actual bargraph - literally the slowest thing ever
###Line graph with this many categories approximatesa barGraph, and is probably a better choice
import matplotlib as mpl
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cbook as cbook
###%matplotlib inline

def read_datafile(file_name):
    data = np.loadtxt(file_name, delimiter=',', skiprows=1)
    return data

data = read_datafile('/Users/awr/Desktop/10xVarCall/10xVarCall/barCodeFreq.csv')

x= data[:,0]
y= data[:,1]

plt.bar(x,y)

fig = plt.gcf()

#fig = plt.figure()

#ax1 = fig.add_subplot(111)

#ax1.set_title("Barcode Coverage")
#ax1.set_xlabel('Barcode ID')
#ax1.set_ylabel('Frequency')

#ax1.plot(x,y, c='r')

#leg = ax1.legend()

plt.show()
