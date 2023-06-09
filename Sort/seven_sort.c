#include <stdio.h>
#include<time.h>
#include <stdlib.h>
#define SWAP(x,y) {x ^= y;y^=x;x^=y;}
//#define MIN(min,target) {min = min>target?target:min;}
#define MAX_SIZE 10
int sorted[MAX_SIZE];
int SIZE = MAX_SIZE;

// 힙 정렬에 사용
typedef struct {
	int key;
} element;

typedef struct {
	element heap[MAX_SIZE];
	int heap_size;
} HeapType;


void bubble_sort(int* ptr, int size);
void select_sort(int* ptr, int size);
void insertion_sort(int* ptr, int size);
void shell_sort(int* ptr, int size);
void shell_insertion_sort(int* ptr, int first, int last, int gap);
void merge_sort_execute(int* ptr, int size);
void merge_sort(int* ptr, int left,int right);
void merge(int* ptr, int left, int mid, int right);
element delete_max_heap(HeapType* h);
init(HeapType* h);
void heap_sort(element e[], int n);
void insert_max_heap(HeapType* h, element item);

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
	//shell_sort(arr_ptr, SIZE);

	//합병정렬
	//merge_sort_execute(arr_ptr, SIZE);

	//힙 정렬
	element e[MAX_SIZE] = { 9,7,6,5,8,3,1,2,1,3 };
	heap_sort(e, SIZE);


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

/*
*	Merge Sort
*	분할 정복 알고리즘을 사용한다.
*	
*	[과정 설명]
*	1. 리스트의 길이가 0 or 1이면 정렬된 것으로 본다.
*	2. 그렇지 않은 경우에는, 정렬되지 않은 리스트를 절반으로 잘라 두 부분 리스트로 나눈다.
*	3. 각 부분 리스트를 재귀적으로 합병 정렬을 통해 정렬한다.
*	4. 이를 반복한다.
*	5. 단 2개의 리스트가 남았을 때, 두 개의 리스트에 index를 두고, 두 index가 가르키는 값의 크기 차이를 통해 정렬할 수 있다.
* 
*	시간 복잡도:
*	[최적]: nlogn
*	[평균]: nlogn
*	[최악]: nlogn
* 
*	※장점
*		안정적인 정렬에 속한다.
*		최악의 경우에도 nlogn의 시간복잡도를 보여준다.
*	※단점
*		배열 정렬의 경우에는 임시 배열이 필요하다.
*		이는 꽤 큰 메모리 낭비를 불러올 수 있다.
* 
*	데이터 60000개 기준: 5371ms.
*/
void merge_sort_execute(int* ptr,int size) {
	re_create_data(ptr, size);

	merge_sort(ptr, 0, size - 1);

	after_print_data(ptr, size);
}

void merge_sort(int* ptr, int left, int right) {
	int mid;

	if (left < right) {
		mid = (left + right) / 2;
		merge_sort(ptr, left, mid);
		merge_sort(ptr, mid + 1, right);
		merge(ptr, left, mid, right);
	}
}

void merge(int* ptr, int left, int mid, int right) {
	int left_idx, right_idx, list_idx, l;
	left_idx = left;
	right_idx = mid + 1;
	list_idx = left;

	//left_idx는 mid까지, right_idx는 right까지 진행
	while (left_idx <= mid && right_idx <= right) {
		if (*(ptr + left_idx) <= *(ptr + right_idx)) {
			sorted[list_idx++] = *(ptr + left_idx++);
		}
		else {
			sorted[list_idx++] = *(ptr + right_idx++);
		}
	}

	//값이 남았을 경우 그냥 마지막 배열에 삽입
	//left, right 중 하나의 인덱스가 마지막에 도착했다는 의미는,
	//다른 하나의 인덱스부터 마지막까지의 값은 전부,
	//나머지 하나의 인덱스보다 크다는 의미임.
	//그러므로 그냥 전부 순서대로 더해줘도 흐트러지지 않음.
	if (left_idx > mid) {
		for (left_idx = right_idx; left_idx <= right; left_idx++) {
			sorted[list_idx++] = *(ptr + left_idx);
		}
	}
	else {
		for (l = left_idx; left_idx <= mid; left_idx++) {
			sorted[list_idx++] = *(ptr + l);
		}
	}

	//배열 sorted[](임시 배열)의 리스트를 arr로 재복사
	for (l = left; l <= right; l++) {
		*(ptr + l) = sorted[l];
	}

}

/*
Heap Sort

자료구조의 Heap에서 따온 정렬법이다.
완전 이진 트리의 일종이며, 우선순위 큐를 위해 만들어진 자료구조이다.
최대 힙 트리나 최소 힙 트리를 이용하면 정렬된 값을 얻을 수 있다.
[과정 설명]
1. 정렬해야 할 N개의 요소들로 최대 힙(완전 이진 트리)를 만든다.
2. 그 다음으로 한 번에 요소를 힙에서 꺼내서 배열의 뒤부터 저장하면 된다.
3. 삭제되는 요소들은 값이 감소되는 순서대로 정렬되게 되어 있다.
*/
void heap_sort(element e[], int n) {
	int i;
	HeapType h;

	//힙을 초기화해주는 함수
	init(&h);

	//MAX HEAP에 하나씩 삽입
	for (i = 0; i < n; i++) {
		insert_max_heap(&h, e[i]);
	}

	//내림차순으로 정렬되어있는 힙 자료구조에서 제일 큰 값부터 차례대로 제거.
	for (i = (n - 1); i >= 0; i--) {
		e[i] = delete_max_heap(&h);
		printf("%d ", e[i].key);
	}
}

//힙 초기화
init(HeapType* h) {
	h->heap_size = 0;
}


/*현재 요소의 개수가 heap_size인 힙 h에 item을 삽입.*/
//최대 힙(max heap) 삽입 함수
//마지막 값을 들고 있다가, 뒤에서부터 앞으로 한 칸씩 땡겨서 일치하는 곳에 삽입하는 전략 (생각보다 많이 쓰는 듯?)
void insert_max_heap(HeapType* h, element item) {
	int i;
	i = ++(h->heap_size); // 힙 크기를 하나 증가

	/* 트리를 거슬러 올라가면서 부모 노드와 비교하는 과정 */
	//i가 루트 노드(index:1)이 아니고, 삽입할 item의 값이 부모 노드(index: i/2)보다 크면
	//(i가 1이면 바로 힙에 삽입)
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		//i번째 노드와 부모 노드를 교환한다.
		h->heap[i] = h->heap[i / 2];
		//한 레벨 위로 올라간다.
		i /= 2;
	}

	h->heap[i] = item; //새 노드 삽입
}

element delete_max_heap(HeapType* h) {
	int parent, child;
	element item, temp;

	item = h->heap[1]; //루트 값을 저장하기 위한 item에 할당
	temp = h->heap[(h->heap_size)--]; // temp값은 마지막 노드에 할당하고 힙 크기를 줄임
	parent = 1;
	child = 2;

	while (child <= h->heap_size) {
		//현재 노드의 자식 노드 중 더 큰 자식 노드를 찾는다 (루트 노드의 왼쪽 노드인 index:2 부터 탐색 시작)
		//만약 왼쪽 노드가 오른쪽 노드보다 작다면, 오른쪽 노드를 탐색하는 과정에 들어간다.
		if ((child < h->heap_size) && (h->heap[child].key < h->heap[child + 1].key)) {
			child++;
		}

		//만약 temp 노드가 child 노드보다 커지면, while문을 중지한다. 제대로 위치했다는 뜻이므로 while문을 탈출한다.
		if (temp.key >= h->heap[child].key) 
			break;

		//child 노드가 temp 노드보다 크다면, 부모 노드와 child 노드를 교환
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
		
	}

	//마지막 노드를 재구성한 위치에 삽입한다.
	h->heap[parent] = temp;

	//최댓값(루트노드)를 반환한다.
	return item;
}
