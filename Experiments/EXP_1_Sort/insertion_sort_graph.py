import matplotlib.pyplot as plt
import numpy as np

# Data for Insertion Sort
elements = [10000, 50000, 100000]
ascending_times = [0, 0.001, 0]
descending_times = [0.427, 9.05, 74.945]
random_times = [0.162, 4.486, 37.116]

# Bar positions
x = np.arange(len(elements))
bar_width = 0.25

# Plot bars with clear colors
plt.figure(figsize=(8, 5))
plt.bar(x - bar_width, ascending_times, width=bar_width, label="Ascending", color="green")
plt.bar(x, descending_times, width=bar_width, label="Descending", color="orange")
plt.bar(x + bar_width, random_times, width=bar_width, label="Random", color="blue")

# Labels and title
plt.xticks(x, elements)
plt.xlabel("Number of Elements")
plt.ylabel("Execution Time (seconds)")
plt.title("Insertion Sort Execution Time Comparison")
plt.legend()
plt.grid(axis='y', linestyle='--', alpha=0.7)

# Display graph
plt.tight_layout()
plt.show()
