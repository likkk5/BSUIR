def tridiag_solve(a, b, c, d):
    alpha = [-c[0] / b[0]]
    beta = [d[0] / b[0]]
    gamma = [b[0]]
    n = len(d)
    result = [0 for i in range(n)]

    for i in range(1, n - 1):
        gamma.append(b[i] + a[i] * alpha[i - 1])
        alpha.append(-c[i] / gamma[i])
        beta.append((d[i] - a[i] * beta[i - 1]) / gamma[i])

    gamma.append(b[n - 1] + a[n - 1] * alpha[n - 2])
    beta.append((d[n - 1] - a[n - 1] * beta[n - 2]) / gamma[n - 1])
    result[n - 1] = beta[n - 1]

    for i in reversed(range(n - 1)):
        result[i] = alpha[i] * result[i + 1] + beta[i]

    return result