import time
from matplotlib import pyplot as plt

def timed(f, *args, n_iter=100):
    acc = float("inf")
    for i in range(n_iter):
        t0 = time.perf_counter()
        f(*args)
        t1 = time.perf_counter()
        acc = min(acc, t1-t0)
    return acc

def compare(fs, args, n_iter=100):
    for f in fs:
        plt.plot(args, [timed(f, arg, n_iter=n_iter) for arg in args], label=f.__name__)
    plt.legend()
    plt.grid(True)