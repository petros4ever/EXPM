import numpy as np

def lloyd_max(x, N, min_value, max_value, tol=1e-6, max_iter=100):
    x = np.array(x)
    delta = (max_value - min_value) / N
    centers = np.linspace(min_value + delta / 2, max_value - delta / 2, N)
    thresholds = np.linspace(min_value, max_value, N + 1)

    D_prev = np.inf

    for _ in range(max_iter):
        # Κβαντισμός
        xq = np.zeros_like(x)
        for i in range(N):
            idx = (x >= thresholds[i]) & (x < thresholds[i + 1])
            xq[idx] = centers[i]
        xq[x >= thresholds[-1]] = centers[-1]

        # Ενημέρωση thresholds
        thresholds[1:-1] = (centers[:-1] + centers[1:]) / 2

        # Ενημέρωση centers
        for i in range(N):
            region = x[(x >= thresholds[i]) & (x < thresholds[i + 1])]
            if region.size > 0:
                centers[i] = np.mean(region)

        # Υπολογισμός σφάλματος
        D = np.mean((x - xq) ** 2)
        if abs(D_prev - D) < tol:
            break
        D_prev = D

    return xq, centers, D
np.random.seed(0)
x = np.random.uniform(0, 1, 1000)
N = 4
min_val = 0.0
max_val = 1.0

xq, centers, distortion = lloyd_max(x, N, min_val, max_val)

print("🎯 Κέντρα:", centers)
print("📉 Μέσο τετραγωνικό σφάλμα (Distortion):", distortion)
