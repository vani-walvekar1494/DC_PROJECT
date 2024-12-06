import matplotlib.pyplot as plt

# Example data with the provided times
processors = [1, 2, 4, 8, 16]

# Measured times for n=32 and n=256 (from the provided values)
times_32 = [0.000190476, 0.000103743, 0.000110593, 0.000822302, 0.00163699]
times_256 = [0.120822, 0.0630646, 0.0450688, 0.0269226, 0.0330439]

# Calculate speedup for both N=32 and N=256 (Speedup = Time for 1 processor / Time for P processors)
speedup_32 = [times_32[0] / t for t in times_32]
speedup_256 = [times_256[0] / t for t in times_256]

# Plot Speedup vs Processors
plt.figure(figsize=(12, 6))

# Subplot for Speedup vs Number of Processors
plt.subplot(1, 2, 1)
plt.plot(processors, speedup_32, marker='o', label='n=32')
plt.plot(processors, speedup_256, marker='o', label='n=256')
plt.title("Speedup vs Number of Processors")
plt.xlabel("Number of Processors")
plt.ylabel("Speedup")
plt.legend()

# Subplot for CPU Time vs Number of Processors
plt.subplot(1, 2, 2)
plt.plot(processors, times_32, marker='o', label='n=32')
plt.plot(processors, times_256, marker='o', label='n=256')
plt.title("CPU Time vs Number of Processors")
plt.xlabel("Number of Processors")
plt.ylabel("Time (seconds)")
plt.legend()

plt.tight_layout()
plt.show()
