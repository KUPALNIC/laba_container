import matplotlib.pyplot as plt
sizes = []
std_vector_times = []
subvector_times = []

with open('/home/kupalnic/CLionProjects/laba_container/cmake-build-debug/1.txt', 'r') as file:
    for line in file:
        size, std_vector_time, subvector_time = map(float, line.split())
        sizes.append(size)
        std_vector_times.append(std_vector_time)
        subvector_times.append(subvector_time)

# Plot data
plt.figure(figsize=(10, 6))
plt.plot(sizes, std_vector_times, label='std::vector', marker='o')
plt.plot(sizes, subvector_times, label='subvector', marker='x')

# Add titles and labels
plt.title('Среднее время вставки для std::vector и subvector')
plt.xlabel('Container Size')
plt.ylabel('Время вставки, мкс')
plt.legend()
plt.grid(True)

# Show plot
plt.savefig('insertion_time_comparison.png')
plt.show()