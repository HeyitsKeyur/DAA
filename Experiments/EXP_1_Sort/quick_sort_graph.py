import matplotlib.pyplot as plt
import numpy as np

# Data
sizes = [10000, 50000, 100000]
ascending = [0.001, 0.002, 0.006]
descending = [0.001, 0.004, 0.019]
random = [0.001, 0.008, 0.037]

x = np.arange(len(sizes))  # X-axis positions
width = 0.25  # width of bars

# Plot
plt.bar(x - width, ascending, width, label='Ascending', color='blue')
plt.bar(x, descending, width, label='Descending', color='orange')
plt.bar(x + width, random, width, label='Random', color='green')

# Labels & Title
plt.xlabel('Number of Elements')
plt.ylabel('Execution Time (seconds)')
plt.title('Quick Sort Performance')
plt.xticks(x, sizes)
plt.legend()

# Show graph
plt.show()
