# _*_ coding:utf-8 _*_

# 1- P(N,n) / pow(N, n)
# N : days, 365/366
# n : peoples
# P(N, n) = (N-1+1)*(N-2+1)*(N-3+1)*...*(N-n+1)
# pow(N, n) = N * N * N * ... * N
# P(N, n) / pow(N, n), nobody birthday conflict

import matplotlib.pyplot as plt

if __name__ == "__main__":
    days = 366
    # peoples = range(1, days/2)
    peoples = range(1, 50)
    percent = [x for x in peoples]

    tmp = 1.0
    before = 1
    for i in peoples:
        tmp = tmp * (days - i + 1) / days
        percent[i-1] = 1 - tmp
        if percent[i-1] < 0.5:
            before = i
    after = before + 1

    plt.plot(peoples, percent, 'r-', linewidth=2, label='birth conflict percentage')
    plt.plot([before, after], [percent[before - 1], percent[after - 1]], 'b*', linewidth=2)
    plt.plot([peoples[0], peoples[-1]], [0.5, 0.5], 'g-', linewidth=2)
    plt.show()


