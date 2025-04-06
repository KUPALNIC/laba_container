import matplotlib.pyplot as plt

sizes = []
std_list_times = []
forward_list_times = []
subforwardlist_times = []

with open('/home/kupalnic/CLionProjects/laba_container/cmake-build-debug/3.txt', 'r') as file:
    for line in file:
        size, std_list_time, forward_list_time, subforwardlist_time = map(float, line.split())
        sizes.append(size)
        std_list_times.append(std_list_time)
        forward_list_times.append(forward_list_time)
        subforwardlist_times.append(subforwardlist_time)

# Plot data
plt.figure(figsize=(10, 6))
plt.plot(sizes, std_list_times, label='std::list', marker='o')
plt.plot(sizes, forward_list_times, label='std::forward_list', marker='x')
plt.plot(sizes, subforwardlist_times, label='Subforwardlist', marker='s')

# Add titles and labels
plt.title('Среднее время добавления в начало для std::list, std::forward_list, и Subforwardlist')
plt.xlabel('Container Size')
plt.ylabel('Время добавления в начало, мкс')
plt.legend()
plt.grid(True)

# Show plot
plt.savefig('push_front_time_comparison.png')
plt.show()