import matplotlib.pyplot as plt
import numpy as np

f = open("datos.txt","r")
f2 = open("datos2.txt","r")
valores = []
valores2 = []
valores3 = []
valores4 = []
lines = f.readlines()
lines2 = f2.readlines()
print(lines)
for line in lines:
    x,y= line.split()
    valores2.append(float(x))
    valores.append(float(y))
f.close()
for line2 in lines2:
    x,y= line2.split()
    valores4.append(float(x))
    valores3.append(float(y))
f2.close()
print(lines)
print(lines2)
# Data for plotting
f = valores
g = valores2
f2 = valores3
g2 = valores4

fig, ax = plt.subplots()
ax.plot(f, g, f2, g2)
#ax.plot(t, s)

ax.set(xlabel='generaciones (g)', ylabel='fitness (f)',
       title='Grafica de generaciones')
ax.grid()

fig.savefig("test.png")
plt.show()
