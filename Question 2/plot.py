import matplotlib.pyplot as plt

# Data for the number of processes (P) and execution times
processors = [4, 8, 12, 16]
static_times = [245.2, 113.9, 90.6, 80.1]
dynamic_times = [155.7, 75.2, 69.4, 58.6]

# Create the plot
plt.figure(figsize=(8, 6))

# Plotting both static and dynamic times
plt.plot(processors, static_times, label='Static Allocation', marker='o', linestyle='-', color='b')
plt.plot(processors, dynamic_times, label='Dynamic Allocation', marker='o', linestyle='-', color='g')

# Adding labels and title
plt.xlabel('Number of Processes (P)', fontsize=12)
plt.ylabel('Execution Time (seconds)', fontsize=12)
plt.title('Comparison of Pi Calculation with Static vs Dynamic Memory Allocation', fontsize=14)

# Adding x-ticks for all processors
plt.xticks(processors)

# Adding grid and legend
plt.grid(True)
plt.legend()

# Display the plot
plt.tight_layout()
plt.show()
