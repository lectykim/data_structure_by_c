#include <stdio.h>
#include<time.h>
#include <stdlib.h>
#define SWAP(x,y) {x ^= y;y^=x;x^=y;}
//#define MIN(min,target) {min = min>target?target:min;}
int SIZE = 60000;

void bubble_sort(int* ptr, int size);
void select_sort(int* ptr, int size);
void insertion_sort(int* ptr, int size);
void shell_sort(int* ptr, int size);
void shell_insertion_sort(int* ptr, int first, int last, int gap);

int main() {
	int TIME = 0;

	/* Timer on */
	clock_t start = clock();

	//랜덤 난수 생성
	srand(time(NULL));

	int* arr = (int*)malloc(sizeof(int) * SIZE);
	int* arr_ptr = arr;

	//버블정렬
	//bubble_sort(arr_ptr,SIZE);

	//선택정렬
	//select_sort(arr_ptr, SIZE);

	//삽입정렬
	//insertion_sort(arr_ptr, SIZE);

	//셸정렬
	shell_sort(arr_ptr, SIZE);

	/* Timer off */
	TIME += ((int)clock() - start) / (CLOCKS_PER_SEC / 1000);
	printf("\nTIME : %d ms\n", TIME);

	free(arr);
	return 0;
}

/*
버블 정렬
시간 복잡도 :
[최적] O(n^2)
[평균] O(n^2)
[최악] O(n^2)

첫 번째 인자를 n-1번째 인자랑 비교하고,
다시 첫 번재 인자를 n-2번째 인자와 비교해가는 방식.

※장점
	구현이 매우 간단하다.
※단점
	순서에 맞지 않은 요소를 인접한 요소와 교환한다.
	하나의 요소가 가장 왼쪽에서 가장 오른쪽으로 이동하기 위해서는 배열에서 모든 다른 요소들과 교환되어야 한다.
	특히 특정 요소가 최종 정렬 위치에 이미 있는 경우라도 교환되는 일이 일어난다.
	일반적으로 자료의 교환 작업(SWAP)이 자료의 이동 작업(MOVE)보다 더 복잡하기 때문에 버블 정렬은 단순성에도 불구하고 거의 쓰이지 않는다.

데이터 60000개 기준 소요시간:14071ms
*/

void bubble_sort(int* ptr, int size) {
	re_create_data(ptr, size);

	//제일 큰 값을 맨 오른쪽으로 보내기 때문에, size-1부터 0까지 점진적으로 목표값을 감소시킨다..
	for (int i = size - 1; i >= 1; i--) {
		//비교는 0부터 시작한다.
		for (int j = 0; j < i; j++) {

			//더 큰 값을 오른쪽 인덱스와 스왑한다.
			if (*(ptr + j) > *(ptr + i)) {
				SWAP(*(ptr + j), *(ptr + i));
			}

		}
	}

	after_print_data(ptr, size);
}
/*
선택 정렬
시간 복잡도:
[최적]:O(N^2)
[평균]:O(N^2)
[최악]:O(N^2)

전체를 탐색하여 그 중 제일 작은 수를 나타내는 인덱스를 찾아,
그 인덱스를 처음 값이랑 바꾼다.
그 과정을 SIZE-1번 진행한다.

※장점
	(버블 정렬에 비해) SWAP 연산 수가 적어서 시간 소요는 좀 더 적다.
※단점
	같은 값이 존재할 경우 불필요한 SWAP 연산이 발생한다.
	안정성을 만족하지 않는다. (즉, 값이 같은 레코드가 있는 경우, 상대적인 위치가 변경될 수 있다.)

	데이터 60000개 기준 소요시간:9782ms

*/
void select_sort(int* ptr, int size) {
	re_create_data(ptr, size);

	//마지막 숫자는 자동으로 정렬되므로 size -1 만큼만 반복한다.
	for (int i = 0; i < size - 1; i++) {

		//초기값은 비교대상 인덱스이다.
		int min = i;

		//비교대상 인덱스 + 1부터, 마지막 인덱스까지 탐색한다.
		for (int j = i + 1; j < size; j++) {
			//만약 arr[초기값]보다 arr[j]가 작다면, 최솟값 인덱스는 j가 된다.
			if (*(ptr + min) > *(ptr + j)) {
				min = j;
			}
		}

		//초기값이 자기 자신이 아니라면, 두 값을 바꾼다. 
		if (i != min)
			SWAP(*(ptr + i), *(ptr + min));
	}

	after_print_data(ptr, size);
}

/*
* 삽입 정렬
* 손 안의 카드를 정렬하는 방법과 유사하다.
* 자료 배열의 모든 요소를 앞에서부터 차례대로 이미 정렬된 배열 부분과 비교하여, 자신의 위치를
* 찾아 삽입함으로써 정렬을 완성하는 알고리즘이다.
* 매 순서마다 원소를 삽입할 수 있는 위치를 찾아 해당 위치에 넣는다.
*
* 두 번째 자료에서 시작.
* 정렬 된 자료에서 해당 위치에 삽입할 자료를 찾고, 그 뒤의 자료들을 전부 한 칸씩 밀어낸다.
*
* 시간복잡도
* [최적]:O(N) - 배열이 이미 정렬되어 있는 경우. 외부 루프 n-1회만 이루어진다.
* [평균]:O(N^2)
* [최악]:O(N^2) - 입력 자료가 역순인 경우, (n-1)+(n-2)+...2+1회가 이루어진다. = O(N^2)
*
* ※장점
*	안정한 정렬 방법이다. (같은 값에서의 배열 위치 변경이 이루어지지 않음.)
*	레코드의 수가 적을 경우 알고리즘 자체가 간단하기 때문에, 다른 복잡한 정렬보다 유리하다.
*	이미 정렬되어 있는 레코드의 경우에 버블정렬과 삽입정렬에 비해 유리하다.
* ※단점
*	레코드의 이동이 많은 편이다.
*	레코드의 수가 많다면 이는 적합하지 않은 정렬 방식이다.
* 데이터 60000개 기준 8144ms
*/

void insertion_sort(int* ptr, int size) {

	re_create_data(ptr, size);

	int key, j;
	//index 0은 이미 정렬됨
	for (int pos = 1; pos < size; pos++) {
		key = *(ptr + pos);

		//정렬된 배열은 i-1까지이기 때문에, i-1번째부터 역순으로 조사한다.
		//j값은 음수이면 안 되고, arr[j]는 key보다 클 때만 진행해야 한다.(같으면 멈춘다.)
		//만약 key가 제일 크다면, 처음부터 for문의 조건을 만족하지 못해서 시작을 못 한다.
		for (j = pos - 1; j >= 0 && *(ptr + j) > key; j--) {
			*(ptr + j + 1) = *(ptr + j);
		}

		//j+1인 이유는, j가 >=0인 이유와도 같은데, 0번까지 비교를 해 줘야 하기 때문이다.
		//만약 j > 0으로 진행한다면, 첫 번째 인덱스는 정렬된 상태가 되지 않는다.
		*(ptr + j + 1) = key;
	}

	after_print_data(ptr, size);
}

/*
셸 정렬
삽입정렬을 보완한 알고리즘.
삽입정렬에서의 스왑할 숫자가 멀리 떨어져 있을 경우, 더 많은 이동을 해야 하기 때문에 시간적 손실이 발생.
그러므로, gap을 기준으로 계산 범위를 나눠서 삽입 정렬로 정렬하는 방식.
gap은 N/2, N/2가 짝수일 경우에는, 홀수로 진행한다.

셸 정렬은 행렬을 기준으로 gap개의 리스트로 쪼개서,열을 기준으로 정렬하는 정렬 방법이다.
고로 마지막은 1열 n행이 되어서, 삽입정렬을 진행하는 방식이다.

※장점
	삽입 정렬보다는 교환되는 요소들이 최종 위치랑 가깝게 배치된다.
	삽입 정렬보다 더 빠르다.

(단점은 딱히 없다.)

시간 복잡도:
[최적]: O(N)
[평균]: O(N^1.5)
[최악]: O(N^2)

데이터 60000개 기준: 5524ms
*/

void shell_sort(int* ptr, int size) {
	re_create_data(ptr, size);

	int gap = size;
	int i;

	//반복은 gap이 0보다 작아지면 끝난다. (마지막 
	for (gap = size / 2; gap > 0; gap /= 2) {
		if ((gap % 2) == 0)
			gap++;

		//부분 리스트의 개수는 gap과 같다.
		//결국 gap은 size를 gap으로 나눈 값이기 때문에, 전체 조각의 수는 gap의 크기로 쪼개지게 된다.
		for (i = 0; i < gap; i++) {
			shell_insertion_sort(ptr, i, size - 1, gap);
		}
	}



	after_print_data(ptr, size);
}

//같은 행에 위치한 수끼리만 선택정렬을 진행하는 함수
void shell_insertion_sort(int* ptr, int first, int last, int gap) {
	int key, j, i;

	for (i = first + gap; i <= last; i += gap) {
		key = *(ptr + i); // 현재 삽입될 숫자인 i번째 정수를 key 변수로 복사

		//첫 번째는 i,i+gap이 있는 행렬을 기준으로 비교,
		//두 번째는 i,i+gap,i+gap*2가 있는 배열을 기준으로 하기 때문에, size/gap + 1 ~ size/gap 번 정도의 계산이 필요함
		//key 값보다 정렬된 배열에 있는 값이 더 크면 j번째를 j+gap으로 이동 (선택정렬)
		//normal한 선택정렬의 gap이 1이라고 생각하면 이해가 편함.
		for (j = i - gap; j >= first && *(ptr + j) > key; j -= gap)
			*(ptr + j + gap) = *(ptr + j);

		*(ptr + j + gap) = key;
	}

}