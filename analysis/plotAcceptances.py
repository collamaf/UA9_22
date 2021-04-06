import argparse
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

parser = argparse.ArgumentParser(description="mUA9 parser")
parser.add_argument('--input', action="store", dest="fileName", default="Acceptances.txt", help='input file name')
args = parser.parse_args()

#settings
plt.style.use('fast')
colNames=['angle','eff1S','eff2S','label']
bendAngle=61.0
dataLabel='ACP80'
mcLabel='Sim'
yMin=0.0
yMax=1.0
dataset = pd.read_csv(args.fileName,sep=" ",comment='#',names=colNames)
print(dataset.label)

dsData = dataset[dataset['label'].str.contains(dataLabel)]
print(dsData)

dsMC = dataset[dataset['label'].str.contains(mcLabel)]
print(dsMC)

fig = plt.figure(figsize=(6,4))

plt.plot(dsMC['angle'],dsMC['eff1S'],'--r',label='$A_{1\sigma}$ Simulation')
plt.plot(dsMC['angle'],dsMC['eff2S'],'--b',label='$A_{2\sigma}$ Simulation')
plt.plot(dsData['angle'],dsData['eff1S'],'or',label='$A_{1\sigma}$ Data (%s)'%dataLabel)
plt.plot(dsData['angle'],dsData['eff2S'],'ob',label='$A_{2\sigma}$ Data (%s)'%dataLabel)
plt.title(r'Acceptance $\theta_b$ +/- 1(2)$\sigma$  ($\theta_b$= {:.1f} $\mu$rad)'.format(bendAngle))
plt.xlabel('Beam angle',fontsize='15')
plt.ylabel('Window acceptance',fontsize='15')
plt.ylim(yMin,yMax)
plt.grid(True)
plt.vlines(-1*bendAngle,yMin,yMax)
#plt.legend(loc="best", bbox_to_anchor=(1,1), fontsize=17, framealpha=0.1)
plt.legend(loc="upper right", fontsize=12, framealpha=0.1)
for x,y in zip(dsData['angle'],dsData['eff1S']):
    label = "{:.2f}".format(y)
    plt.annotate(label,(x,y),textcoords="offset points",xytext=(0,10),ha='center',color='r')
for x,y in zip(dsData['angle'],dsData['eff2S']):
    label = "{:.2f}".format(y)
    plt.annotate(label,(x,y),textcoords="offset points",xytext=(0,10),ha='center',color='b')

plt.annotate("Alignement",(-1*bendAngle,0.7),textcoords="offset points",xytext=(10,0),ha='center',rotation=90)

plt.show()
fig.savefig("Acceptances.png",bbox_inches='tight')
