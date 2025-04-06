import matplotlib.pyplot as plt

# Load data from file
sizes = []
set_times = []
map_times = []
multiset_times = []
multimap_times = []

with open('insert_times.txt', 'r') as file:
    for line in file:
        size, set_time, map_time, multiset_time, multimap_time = map(float, line.split())
        sizes.append(size)
        set_times.append(set_time)
        map_times.append(map_time)
        multiset_times.append(multiset_time)
        multimap_times.append(multimap_time)

# Plot data
plt.figure(figsize=(10, 6))
plt.plot(sizes, set_times, label='set', marker='o')
plt.plot(sizes, map_times, label='map', marker='x')
plt.plot(sizes, multiset_times, label='multiset', marker='s')
plt.plot(sizes, multimap_times, label='multimap', marker='d')
plt.ylim(0.15, 0.3)

# Add titles and labels
plt.title('Average Insert Time for set, map, multiset, and multimap')
plt.xlabel('Container Size')
plt.ylabel('Insert Time (microseconds)')
plt.legend()
plt.grid(True)

# Show plot
plt.savefig('insert_time_comparison.png')
plt.show()