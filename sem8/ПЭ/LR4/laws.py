import math
from numpy.random import uniform, rayleigh


def uniform_by_intensity(intensity, dispersion):
    m = 1 / intensity
    d = 1 / dispersion
    b = (math.sqrt(12 * d) + 2 * m) / 2
    a = 2 * m - b

    return math.fabs(uniform(a, b))


def rayleigh_by_intensity(intensity):
    sigma = math.sqrt(1 / intensity)

    return rayleigh(sigma)
