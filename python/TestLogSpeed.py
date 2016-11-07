#!/usr/bin/python
# -*- coding:utf-8 -*-

import math
import matplotlib.pyplot as plt
import numpy as np

if __name__ == "__main__":
    x = np.arange(0.05, 3, 0.05)
    y1 = [math.log(a, 1.5) for a in x]
    plt.plot(x, y1, linewidth=2, color="#007500", label='log1.5(x)')
    # draw a line from (1, y1[0]) to (1, y1[len(y1) - 1])
    plt.plot([1, 1], [y1[0], y1[-1]], 'r--', linewidth=2)
    y2 = [math.log(a, 2) for a in x]
    plt.plot(x, y2, linewidth=2, color="#9F35EF", label="log2(x)")
    y3 = [math.log(a, 3) for a in x]
    plt.plot(x, y3, linewidth=2, color="#F75000", label="log3(x)")
    plt.legend(loc="lower right")
    plt.grid(True)
    plt.show()
