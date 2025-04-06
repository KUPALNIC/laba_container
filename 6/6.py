import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

def read_results(filename):
    """Читает данные из файла результатов."""
    containers_data = {}
    current_container = None
    current_data = []

    with open(filename, 'r') as f:
        for line in f:
            line = line.strip()
            if not line:  # Пропускаем пустые строки
                continue
            elif ',' not in line:  # Название контейнера
                if current_container and current_data:
                    containers_data[current_container] = pd.DataFrame(current_data)
                current_container = line
                current_data = []
            elif line != 'size,time_ns':  # Пропускаем заголовок
                size, time = map(float, line.split(','))
                current_data.append({'size': size, 'time_ns': time})

    # Добавляем последний контейнер
    if current_container and current_data:
        containers_data[current_container] = pd.DataFrame(current_data)

    return containers_data

def create_linear_plot(containers_data):
    """Создает график в линейном масштабе."""
    plt.figure(figsize=(10, 6))

    for container, data in containers_data.items():
        plt.plot(data['size'], data['time_ns'], marker='o', label=container, markersize=3)

    plt.xlabel('Размер контейнера')
    plt.ylabel('Среднее время обхода на элемент (нс)')
    plt.title('Производительность обхода контейнеров')
    plt.legend()
    plt.grid(True)
    plt.savefig('traversal_performance.png', dpi=300, bbox_inches='tight')
    plt.close()

def print_statistics(containers_data):
    """Выводит статистику по производительности."""
    print("\nСтатистика производительности:")
    print("-" * 80)

    for container, data in containers_data.items():
        print(f"\n{container}:")
        print(f"  Минимальное время: {data['time_ns'].min():.2f} нс")
        print(f"  Максимальное время: {data['time_ns'].max():.2f} нс")
        print(f"  Среднее время: {data['time_ns'].mean():.2f} нс")
        print(f"  Медианное время: {data['time_ns'].median():.2f} нс")

def main():
    # Чтение данных
    data = read_results('/home/kupalnic/CLionProjects/laba_container/cmake-build-debug/6.txt')

    # Создание визуализации
    create_linear_plot(data)

    # Вывод статистики в консоль
    print_statistics(data)

    print("\nГотово! Создан файл:")
    print("- traversal_performance.png (график производительности)")

if __name__ == "__main__":
    main()