import matplotlib.pyplot as plt

# 주어진 큐들
request_queues = {
    "Textbook Request Scenario": {
        "SSTF": [65, 67, 37, 14, 98, 122, 124, 183],
        "SCAN": [37, 14, 0, 65, 67, 98, 122, 124, 183],
        "LOOK": [37, 14, 65, 67, 98, 122, 124, 183]
    },
    "Localized Request Scenario": {
        "SSTF": [40, 38, 37, 36, 35, 33, 32, 30],
        "SCAN": [40, 38, 37, 36, 35, 33, 32, 30],
        "LOOK": [40, 38, 37, 36, 35, 33, 32, 30]
    },
    "Random Request Scenario": {
        "SSTF": [57, 8, 116, 119, 146, 148, 154, 192],
        "SCAN": [8, 0, 57, 116, 119, 146, 148, 154, 192],
        "LOOK": [8, 57, 116, 119, 146, 148, 154, 192]
    }
}

# 각 시나리오에 대해 디스크 헤드의 위치 변화를 그래프로 시각화하는 함수
def plot_disk_head_movement(request_queues):
    for scenario, queue_data in request_queues.items():
        for algorithm, queue in queue_data.items():
            disk_head_position = 53  # 초기 위치
            positions = [disk_head_position]
            for cylinder in queue:
                positions.append(cylinder)
                disk_head_position = cylinder
            plt.figure(figsize=(8, 5))
            plt.plot(range(len(positions)), positions, marker='o', label=algorithm, linestyle='-')
            plt.title(f"{scenario} - {algorithm}", pad=20)
            plt.xlabel('Request Index')
            plt.ylabel('Disk Cylinder')
            plt.yticks([53] + queue, fontsize=5)
            plt.grid(True)
            plt.legend()
            plt.show()

# 그래프 생성
plot_disk_head_movement(request_queues)
