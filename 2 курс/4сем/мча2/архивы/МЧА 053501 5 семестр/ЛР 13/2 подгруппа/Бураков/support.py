import math
LINEWIDTH = 0.5
def sweep_method(a, b, c, d):
    AlphaS = [-c[0] / b[0]]
    BetaS = [d[0] / b[0]]
    GammaS = [b[0]]
    n = len(d)
    result = [0 for i in range(n)]

    for i in range(1, n - 1):
        GammaS.append(b[i] + a[i] * AlphaS[i - 1])
        AlphaS.append(-c[i] / GammaS[i])
        BetaS.append((d[i] - a[i] * BetaS[i - 1]) / GammaS[i])

    GammaS.append(b[n - 1] + a[n - 1] * AlphaS[n - 2])
    BetaS.append((d[n - 1] - a[n - 1] * BetaS[n - 2]) / GammaS[n - 1])

    result[n - 1] = BetaS[n - 1]
    for i in reversed(range(n - 1)):
        result[i] = AlphaS[i] * result[i + 1] + BetaS[i]

    return result


def check_eps(current, prev, eps, debuging=True):
    eps_t = max([math.fabs(current[i*2]-prev[i]) for i in range(len(prev))])
    if debuging:
        print('Check: ', eps_t)
    if eps_t > eps:
        return False
    return True


def deep_copy(system):
    return [item for item in system]


def get_h(a, b, n):
    return (b - a) / n