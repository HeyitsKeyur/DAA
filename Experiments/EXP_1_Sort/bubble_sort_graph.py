import matplotlib.pyplot as plt
import numpy as np

# Your data
elements = [10000, 50000, 100000]
ascending_times = [0.000, 0.000, 0.000]
descending_times = [0.490, 11.414, 46.786]
random_times = [0.473, 11.977, 48.87]

# Set up bar positions
x = np.arange(len(elements))
bar_width = 0.25

# Create bar chart with custom colors
plt.figure(figsize=(8, 5))
plt.bar(x - bar_width, ascending_times, width=bar_width, label="Ascending", color="green")
plt.bar(x, descending_times, width=bar_width, label="Descending", color="orange")
plt.bar(x + bar_width, random_times, width=bar_width, label="Random", color="blue")

# Labels and title
plt.xticks(x, elements)
plt.xlabel("Number of Elements")
plt.ylabel("Execution Time (seconds)")
plt.title("Bubble Sort Execution Time Comparison")
plt.legend()
plt.grid(axis='y', linestyle='--', alpha=0.7)

# Show the graph
plt.tight_layout()
plt.show()
