import matplotlib.pyplot as plt

procs = [1, 2, 3, 4]
time_ex2 = [0.006894, 0.004081, 0.002613, 0.002415]
time_ex3 = [0.194533, 0.099005, 0.068802, 0.068682]
speedup_ex2 = [1.0, 1.69, 2.64, 2.85]
speedup_ex3 = [1.0, 1.96, 2.83, 2.83]

# Plot Time vs Processors for Ex 2
plt.figure(figsize=(6, 4))
plt.plot(procs, time_ex2, marker='o', color='blue')
plt.title('Exercise 2: Time vs Processors')
plt.xlabel('Number of Processors')
plt.ylabel('Time (seconds)')
plt.xticks(procs)
plt.grid(True)
plt.savefig('Time_vs_Processors_Ex2.png')
plt.close()

# Plot Time vs Processors for Ex 3
plt.figure(figsize=(6, 4))
plt.plot(procs, time_ex3, marker='o', color='green')
plt.title('Exercise 3: Time vs Processors')
plt.xlabel('Number of Processors')
plt.ylabel('Time (seconds)')
plt.xticks(procs)
plt.grid(True)
plt.savefig('Time_vs_Processors_Ex3.png')
plt.close()

# Plot Speedup
plt.figure(figsize=(6, 4))
plt.plot(procs, speedup_ex2, marker='o', label='Ex 2 (Sum)', color='blue')
plt.plot(procs, speedup_ex3, marker='o', label='Ex 3 (Pi)', color='green')
plt.title('Speedup vs Processors')
plt.xlabel('Number of Processors')
plt.ylabel('Speedup (Multiplier)')
plt.xticks(procs)
plt.legend()
plt.grid(True)
plt.savefig('Speedup_vs_Processors.png')
plt.close()
