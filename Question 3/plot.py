import matplotlib.pyplot as plt

# Data for P (Number of Processes)
P = [1, 2, 4, 6, 8, 10]

# Weak Scaling Times
weak_scaling = [0.304, 0.295, 0.316, 0.319, 0.371, 0.534]

# Strong Scaling Times
strong_scaling = [0.912, 0.463, 0.229, 0.152, 0.195, 0.155]

# Create the plot
plt.figure(figsize=(10, 6))

# Plotting Weak Scaling
plt.plot(P, weak_scaling, label='Weak Scaling', marker='o', color='b', linestyle='-', linewidth=2, markersize=8)

# Plotting Strong Scaling
plt.plot(P, strong_scaling, label='Strong Scaling', marker='s', color='r', linestyle='--', linewidth=2, markersize=8)

# Adding labels and title
plt.xlabel('Number of Processes (P)', fontsize=14)
plt.ylabel('Computation Time (seconds)', fontsize=14)
plt.title('Weak Scaling vs Strong Scaling', fontsize=16)

# Adding grid
plt.grid(True)

# Adding legend
plt.legend()

# Show the plot
plt.tight_layout()
plt.show()
