#/usr/bin/python
# -*- coding: utf-8 -*-

# this exercise example shows figure

import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(-np.pi, np.pi, 256, endpoint=True)
c, s = np.cos(x), np.sin(x)

plt.figure(1)
plt.plot(x, c)
# Show figure 1, and continue to run next code without waiting figure 1 to be closed
plt.show(block=False)
plt.figure(2)
plt.plot(x, s)

# Show and waiting all of figure to be closed
plt.show()
