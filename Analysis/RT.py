import matplotlib.pyplot as plt
import numpy as np

# 응답 시간 데이터
response_times = {
    "Textbook Request Scenario": {
        "SSTF": [12.0, 14.0, 44.0, 67.0, 151.0, 175.0, 177.0, 236.0],
        "SCAN": [16.0, 39.0, 53.0, 118.0, 120.0, 151.0, 175.0, 177.0, 236.0],
        "LOOK": [16.0, 39.0, 90.0, 92.0, 123.0, 147.0, 149.0, 208.0]
    },
    "Localized Request Scenario": {
        "SSTF": [13.0, 15.0, 16.0, 17.0, 18.0, 20.0, 21.0, 23.0],
        "SCAN": [13.0, 15.0, 16.0, 17.0, 18.0, 20.0, 21.0, 23.0],
        "LOOK": [13.0, 15.0, 16.0, 17.0, 18.0, 20.0, 21.0, 23.0]
    },
    "Random Request Scenario": {
        "SSTF": [4.0, 53.0, 161.0, 164.0, 191.0, 193.0, 199.0, 237.0],
        "SCAN": [45.0, 53.0, 110.0, 169.0, 172.0, 199.0, 201.0, 207.0, 245.0],
        "LOOK": [45.0, 94.0, 153.0, 156.0, 183.0, 185.0, 191.0, 229.0]
    }
}

# 각 시나리오별 표준편차 계산
std_devs = {}
for scenario, data in response_times.items():
    std_devs[scenario] = {}
    for algorithm, times in data.items():
        std_devs[scenario][algorithm] = np.std(times)

# 그래프 그리기
for scenario, std_dev in std_devs.items():
    plt.figure(figsize=(8, 5))
    for algorithm, std_dev_value in std_dev.items():
        plt.plot(np.arange(len(response_times[scenario][algorithm])), response_times[scenario][algorithm], marker='o', linestyle='-', label=algorithm)
    plt.title(f"Response Time Variance - {scenario}")
    plt.xlabel('Request Index')
    plt.ylabel('Response Time (ms)')
    plt.legend()
    plt.grid(True)
    plt.show()
