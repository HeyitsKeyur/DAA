import matplotlib.pyplot as plt
import numpy as np

# Data for Selection Sort
elements = [10000, 50000, 100000]
ascending_times = [0.212, 5.215, 20.93]
descending_times = [0.23, 5.113, 20.499]
random_times = [0.216, 5.188, 20.832]

# Bar positions
x = np.arange(len(elements))
bar_width = 0.25

# Plot bars with distinct colors
plt.figure(figsize=(8, 5))
plt.bar(x - bar_width, ascending_times, width=bar_width, label="Ascending", color="blue")
plt.bar(x, descending_times, width=bar_width, label="Descending", color="orange")
plt.bar(x + bar_width, random_times, width=bar_width, label="Random", color="green")

# Labels and title
plt.xticks(x, elements)
plt.xlabel("Number of Elements")
plt.ylabel("Execution Time (seconds)")
plt.title("Selection Sort Execution Time Comparison")
plt.legend()
plt.grid(axis='y', linestyle='--', alpha=0.7)

# Display graph
plt.tight_layout()
plt.show()
