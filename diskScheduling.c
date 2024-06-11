#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define QUEUE_SIZE 8
#define SCAN_QUEUE_SIZE QUEUE_SIZE+1

void SSTF(int*, int*, int, int, int);
void SCAN(int*, int*, int, int, int);
void LOOK(int*, int*, int, int, int);
void calculateVarience(int*, int);

int main() {
	int queue[QUEUE_SIZE] = { 98, 183, 37, 122, 14, 124, 65, 67 };
	int localizedQueue[QUEUE_SIZE] = { 30, 32, 35, 33, 40, 37, 38, 36 };
	int randomQueue[QUEUE_SIZE] = { 0, };

	int seekDist[QUEUE_SIZE], scanSeekDist[SCAN_QUEUE_SIZE], seekIdx = 0;
	int head = 53, result = 0;

	printf("교과서의 요청 시나리오\n");
	SSTF(queue, seekDist, seekIdx, head, result);
	SCAN(queue, scanSeekDist, seekIdx, head, result);
	LOOK(queue, seekDist, seekIdx, head, result);

	printf("인접 위주 요청 시나리오\n");
	SSTF(localizedQueue, seekDist, seekIdx, head, result);
	SCAN(localizedQueue, scanSeekDist, seekIdx, head, result);
	LOOK(localizedQueue, seekDist, seekIdx, head, result);

	printf("무작위 요청 시나리오\n");
	srand(time(NULL));
	for (int i = 0; i < QUEUE_SIZE; i++) randomQueue[i] = (rand() % 199) + 1;
	SSTF(randomQueue, seekDist, seekIdx, head, result);
	SCAN(randomQueue, scanSeekDist, seekIdx, head, result);
	LOOK(randomQueue, seekDist, seekIdx, head, result);

	return 0;
}

/*
@function
 void SSTF(int* queue, int* seekDist, int seekIdx, int head, int result)
 SSTF scheduling algorithm을 구현한 함수

@parameter
 queue : 요청 큐를 배열로 구현
 seekDist : seek distance를 저장하는 배열
 seekIdx : seekDist 배열의 인덱스
 head : 현재 헤드를 저장하는 변수
 result : 결과를 출력하기 위한 변수
@variable
 reqIdx : 서비스될 요청의 인덱스를 저장하는 변수
*/
void SSTF(int* queue, int* seekDist, int seekIdx, int head, int result) {
	printf("SSTF scheduling algorithm\n");

	int reqIdx = 0;

	while (seekIdx < 8) {
		int sst = 0;
		int tmp = 0;

		for (int i = reqIdx; i < 8; i++) {
			if (sst == 0 || abs(head - queue[i]) < sst) {
				tmp = queue[reqIdx];
				queue[reqIdx] = queue[i];
				queue[i] = tmp;

				sst = abs(head - queue[reqIdx]);
			}
		}

		seekDist[seekIdx] = sst;
		head = queue[reqIdx];

		reqIdx++;
		seekIdx++;
	}

	for (int i = 0; i < seekIdx; i++) {
		result += seekDist[i];
	}
	printf("total head movement of %d cylinders.\n", result);
	calculateVarience(seekDist, seekIdx);
}

/*
@function
 void SCAN(int* queue, int* seekDist, int seekIdx, int head, int result)
 SCAN scheduling algorithm을 구현한 함수

@parameter
 queue : 요청 큐를 배열로 구현
 seekDist : seek distance를 저장하는 배열
 seekIdx : seekDist 배열의 인덱스
 head : 현재 헤드를 저장하는 변수
 result : 결과를 출력하기 위한 변수

@variable
 reqIdx : 서비스될 요청의 인덱스를 저장하는 변수
 reOrder : 요청 큐를 스캔의 이동 경로 순서로 재정렬하기 위한 배열
 less : 시작 헤드보다 작은 수 배열
 greater : 시작 헤드보다 큰 수 배열
 reach : 이동 경로의 끝에 도달했는가의 여부를 확인하기 위한 변수. 요청 큐의 크기와 같다면 끝에 도달하지 않은 것이다.
*/
void SCAN(int* queue, int* seekDist, int seekIdx, int head, int result) {
	printf("SCAN scheduling algorithm\n");

	int reqIdx = 0; // reqIdx : 서비스될 요청을 저장하는 변수
	int reOrder[QUEUE_SIZE] = { 0, };
	int reach = 0;
	int less = 0, greater = QUEUE_SIZE;

	for (int i = 0; i < QUEUE_SIZE; i++) {
		if (queue[i] < head) { reOrder[less] = queue[i]; less++; reach--; }
		else { reOrder[greater - 1] = queue[i]; greater--; reach++; }
	}

	int tmp = 0;
	for (int i = 0; i < less; i++) {
		for (int j = 0; j < less - 1; j++) {
			if (reOrder[i] > reOrder[j]) {
				tmp = reOrder[i];
				reOrder[i] = reOrder[j];
				reOrder[j] = tmp;
			}
		}
	}
	for (int i = greater; i < QUEUE_SIZE; i++) {
		for (int j = greater; j < QUEUE_SIZE - 1; j++) {
			if (reOrder[i] < reOrder[j]) {
				tmp = reOrder[i];
				reOrder[i] = reOrder[j];
				reOrder[j] = tmp;
			}
		}
	}

	int scan = 0;
	int i = 0;
	if (abs(reach) >= QUEUE_SIZE) {
		while (seekIdx < QUEUE_SIZE) {
			if (scan == less) {
				seekDist[seekIdx] = abs(head - 0);
				seekIdx++;
				seekDist[seekIdx] = abs(0 - reOrder[greater]);
			}
			else seekDist[seekIdx] = abs(head - reOrder[i]);

			head = reOrder[i];
			seekIdx++;
			scan++;
			i++;
		}
	}
	else {
		while (seekIdx < SCAN_QUEUE_SIZE) {
			if (scan == less) {
				seekDist[seekIdx] = abs(head - 0);
				seekIdx++;
				seekDist[seekIdx] = abs(0 - reOrder[greater]);
			}
			else seekDist[seekIdx] = abs(head - reOrder[i]);

			head = reOrder[i];
			seekIdx++;
			scan++;
			i++;
		}
	}

	for (int i = 0; i < seekIdx; i++) {
		result += seekDist[i];
	}
	printf("total head movement of %d cylinders.\n", result);
	calculateVarience(seekDist, seekIdx);
}

/*
@function
 void LOOK(int* queue, int* seekDist, int seekIdx, int head, int result)
 LOOK scheduling algorithm을 구현한 함수

@parameter
 queue : 요청 큐를 배열로 구현
 seekDist : seek distance를 저장하는 배열
 seekIdx : seekDist 배열의 인덱스
 head : 현재 헤드를 저장하는 변수
 result : 결과를 출력하기 위한 변수

@variable
 reqIdx : 서비스될 요청의 인덱스를 저장하는 변수
 reOrder : 요청 큐를 스캔의 이동 경로 순서로 재정렬하기 위한 배열
 less : 시작 헤드보다 작은 수 배열
 greater : 시작 헤드보다 큰 수 배열
*/
void LOOK(int* queue, int* seekDist, int seekIdx, int head, int result) {
	printf("LOOK scheduling algorithm\n");

	int reqIdx = 0; // reqIdx : 서비스될 요청을 저장하는 변수
	int reOrder[QUEUE_SIZE] = { 0, };

	int less = 0, greater = QUEUE_SIZE;
	for (int i = 0; i < QUEUE_SIZE; i++) {
		if (queue[i] < head) { reOrder[less] = queue[i]; less++; }
		else { reOrder[greater - 1] = queue[i]; greater--; }
	}
	int tmp = 0;
	for (int i = 0; i < less; i++) {
		for (int j = 0; j < less - 1; j++) {
			if (reOrder[i] > reOrder[j]) {
				tmp = reOrder[i];
				reOrder[i] = reOrder[j];
				reOrder[j] = tmp;
			}
		}
	}
	for (int i = greater; i < QUEUE_SIZE; i++) {
		for (int j = greater; j < QUEUE_SIZE - 1; j++) {
			if (reOrder[i] < reOrder[j]) {
				tmp = reOrder[i];
				reOrder[i] = reOrder[j];
				reOrder[j] = tmp;
			}
		}
	}

	int i = 0;
	while (seekIdx < QUEUE_SIZE) {
		seekDist[seekIdx] = abs(head - reOrder[i]);
		head = reOrder[i];
		seekIdx++;
		i++;
	}

	for (int i = 0; i < seekIdx; i++) {
		result += seekDist[i];
	}
	printf("total head movement of %d cylinders.\n", result);
	calculateVarience(seekDist, seekIdx);
}

/*
@funtion
 void calculateVarience(int* seekDist, int seekIdx)
 calculateVarience : 응답 시간의 편차를 구하기 위한 함수

@parameter
 seekDist : 응답 시간을 구하기 위한 디스크 이동 거리
 seekIdx : 평균을 구하기 위한 큐 크기

@
*/
void calculateVarience(int* seekDist, int seekIdx) {
	double* responseTimes = (double*)malloc(sizeof(double) * seekIdx);
	if (responseTimes == NULL) {
		fprintf(stderr, "error occured");
		exit(1);
	}
	double mean = 0, variance = 0;

	for (int i = 0; i < seekIdx; i++) {
		responseTimes[i] = (i == 0) ? seekDist[i] : responseTimes[i - 1] + seekDist[i];
		mean += responseTimes[i];
	}
	mean /= seekIdx;

	for (int i = 0; i < seekIdx; i++) {
		variance += pow(responseTimes[i] - mean, 2);
	}
	variance /= seekIdx;

	printf("Variance of Response Times : %.1f\n", sqrt(variance));
	free(responseTimes);
}
