#/usr/bin/python
# -*- coding: utf-8 -*-

# this exercise example shows a cosine and sine curve from -PI to PI

import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(-np.pi, np.pi, 256, endpoint=True)
c, s = np.cos(x), np.sin(x)

plt.plot(x, c)
plt.plot(x, s)

plt.show()
