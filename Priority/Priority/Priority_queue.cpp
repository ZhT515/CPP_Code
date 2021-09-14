#include "Priority_queue.h"

int main()
{
  Zht::priority_queue<int, vector<int>, Zht::greater<int>> pq;
	pq.push(3);
	pq.push(5);
	pq.push(6);
	pq.push(1);
	pq.push(4);
	pq.push(3);
	pq.push(6);
	pq.push(10);
	pq.push(3);

	int k = 5;
	while (!pq.empty() && k--)
	{
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << endl;
}
