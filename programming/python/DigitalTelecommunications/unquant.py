import numpy as np
import matplotlib.pyplot as plt

def uniform_quantizer(x, N, min_value, max_value):
    L = 2 ** N
    delta = (max_value - min_value) / L
    centers = np.linspace(min_value + delta / 2, max_value - delta / 2, L)

    x = np.array(x)
    x_clipped = np.clip(x, min_value, max_value)

    indices = ((x_clipped - min_value) / delta).astype(int) + 1
    indices[x_clipped == max_value] = L

    decoded_values = centers[indices - 1]
    quantization_error = x - decoded_values
    mse = np.mean(quantization_error ** 2)
    signal_power = np.mean(x ** 2)
    snr = 10 * np.log10(signal_power / mse) if mse != 0 else np.inf

    return indices, centers, decoded_values, quantization_error, mse, snr

# 🔹 Παράδειγμα με λίγες τιμές
x = [0.1, 0.5, 0.9, 1.0]
N = 2
min_val = 0.0
max_val = 1.0

xq, centers, decoded, error, mse, snr = uniform_quantizer(x, N, min_val, max_val)

print("📊 Αρχικές τιμές:", x)
print("🔢 Δείκτες κβαντισμού:", xq)
print("🎯 Τιμές αποκωδικοποίησης:", decoded)
print("📉 Σφάλμα κβαντισμού:", error)
print(f"📐 MSE: {mse:.6f}")
print(f"📈 SNR: {snr:.2f} dB")

# 🔹 Ανάλυση SNR για διάφορα N
np.random.seed(0)
x_random = np.random.uniform(0, 1, 1000)

N_values = range(1, 11)
snr_values = []

print("\n📊 SNR για διαφορετικά bits:")
for N in N_values:
    _, _, _, _, _, snr = uniform_quantizer(x_random, N, 0.0, 1.0)
    snr_values.append(snr)
    print(f"N = {N} bits → SNR = {snr:.2f} dB")

# 🔹 Γράφημα
plt.figure(figsize=(8, 5))
plt.plot(N_values, snr_values, marker='o', linestyle='-', color='teal')
plt.title(" SNR vs Αριθμός Bits στον Κβαντιστή")
plt.xlabel("Αριθμός Bits (N)")
plt.ylabel("SNR (dB)")
plt.grid(True)
plt.xticks(N_values)
plt.tight_layout()
plt.show()
