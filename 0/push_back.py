import matplotlib.pyplot as plt
import numpy as np
from matplotlib.pyplot import xlabel, ylabel

x=np.linspace(0,1000000, 1000000)
size=[]
capacity=[]
with open('/home/kupalnic/CLionProjects/laba_container/cmake-build-debug/push_back.txt','r') as pb:
    for line in pb:
        value = line.split()
        size.append(int(value[0]))
        capacity.append(int(value[1]))
size = np.array(size)
capacity = np.array(capacity)
plt.plot(x, size, label='size')
plt.plot(x, capacity, label='capacity')
xlabel('i, iteration')
plt.minorticks_on()
plt.grid(True, which='major', color='k')
plt.grid(True, which='minor', color='lightgray', )
ylabel('size | capacity')
plt.title('графике capacity и size от номера итерации')
plt.legend()
plt.show()