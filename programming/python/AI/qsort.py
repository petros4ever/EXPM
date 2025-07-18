import pennylane as qml
import torch
import torch.nn as nn
import numpy as np
from sklearn.datasets import make_moons
from sklearn.model_selection import train_test_split

# Dataset
X, y = make_moons(n_samples=100, noise=0.1)
X = torch.tensor(X, dtype=torch.float64)
y = torch.tensor(y, dtype=torch.float64)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2)

# Κβαντικό κύκλωμα
n_qubits = 2
n_layers = 6
dev = qml.device("default.qubit", wires=n_qubits)

@qml.qnode(dev, interface="torch")
def quantum_circuit(inputs, weights):
    qml.AngleEmbedding(inputs, wires=range(n_qubits))
    qml.BasicEntanglerLayers(weights, wires=range(n_qubits))
    return qml.expval(qml.PauliZ(0))

# Κβαντικό ταξινομητή
class QuantumClassifier(nn.Module):
    def __init__(self):
        super().__init__()
        # Αρχικοποίηση με μικρές τιμές
        init_weights = 0.01 * torch.randn((n_layers, n_qubits), dtype=torch.float64)
        self.weights = nn.Parameter(init_weights)

    def forward(self, x):
        x = x.to(torch.float64)
        return quantum_circuit(x, self.weights)

# Εκπαίδευση
model = QuantumClassifier().to(torch.float64)
optimizer = torch.optim.Adam(model.parameters(), lr=0.01)
loss_fn = nn.MSELoss()

epochs = 200
for epoch in range(epochs):
    total_loss = 0
    for xi, yi in zip(X_train, y_train):
        xi = xi.to(torch.float64)
        yi = yi.to(torch.float64)
        optimizer.zero_grad()
        output = model(xi)
        loss = loss_fn(output, yi)
        loss.backward()
        optimizer.step()
        total_loss += loss.item()
    if epoch % 10 == 0:
        print(f"Epoch {epoch+1}: Loss = {total_loss:.4f}")

# Αξιολόγηση
correct = 0
for xi, yi in zip(X_test, y_test):
    xi = xi.to(torch.float64)
    pred = model(xi).detach().numpy()
    correct += int((pred > 0.5) == yi.item())

accuracy = correct / len(y_test)
print(f"✅ Τελική ακρίβεια ταξινομητή: {accuracy:.2f}")


import matplotlib.pyplot as plt

# Υπολογισμός προβλέψεων για όλα τα test σημεία
X_vis = X_test.numpy()
y_true = y_test.numpy()
y_pred = []

for xi in X_test:
    xi = xi.to(torch.float64)
    pred = model(xi).detach().numpy()
    y_pred.append(int(pred > 0.5))

# Οπτικοποίηση
plt.figure(figsize=(8, 6))
for i in range(len(X_vis)):
    color = "green" if y_pred[i] == y_true[i] else "red"
    marker = "o" if y_pred[i] == 1 else "x"
    plt.scatter(X_vis[i][0], X_vis[i][1], c=color, marker=marker, s=100)

plt.title(" Κβαντικός ταξινομητής: σωστές (πράσινες) vs λάθος (κόκκινες)")
plt.xlabel("Χ1")
plt.ylabel("Χ2")
plt.grid(True)
plt.show()

