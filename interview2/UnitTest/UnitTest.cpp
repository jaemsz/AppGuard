#include <iostream>
#include <thread>
#include <chrono>
#include "..\interview2\ThreadFuncs.h"

bool test_N(int N)
{
	CQueue queue(N);
	COutput output;

	HANDLE hProducerEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	HANDLE hConsumerEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	std::thread t1(producer, std::ref(queue), std::ref(hConsumerEvent), std::ref(hProducerEvent));
	std::thread t2(producer, std::ref(queue), std::ref(hConsumerEvent), std::ref(hProducerEvent));
	std::thread t3(consumer, std::ref(queue), std::ref(output), std::ref(hConsumerEvent), std::ref(hProducerEvent));
	std::thread t4(consumer, std::ref(queue), std::ref(output), std::ref(hConsumerEvent), std::ref(hProducerEvent));

	t1.join();
	t2.join();
	t3.join();
	t4.join();

	CloseHandle(hProducerEvent);
	CloseHandle(hConsumerEvent);

	int nAccum = output.sumFreq();
	return nAccum == N;
}

bool test_queue_push(int N)
{
	CQueue queue(N);
	QueueRet ret = QueueRet::ok;

	for (int i = 0; i < N; i++)
	{
		ret = queue.push(i);
		if (ret != QueueRet::ok)
		{
			return false;
		}
	}

	return true;
}

bool test_queue_push_over_10(int N)
{
	CQueue queue(N);
	QueueRet ret = QueueRet::ok;

	for (int i = 0; i < N; i++)
	{
		ret = queue.push(i);
		if (i >= 10 && ret != QueueRet::full)
		{
			return false;
		}
	}

	return true;
}

bool test_queue_push_pop(int N)
{
	CQueue queue(N);
	QueueRet ret = QueueRet::ok;

	for (int i = 0; i < N; i++)
	{
		ret = queue.push(i);
		if (ret == QueueRet::ok)
		{
			int nVal = 0;
			ret = queue.pop(nVal);
			if (ret != QueueRet::ok && nVal != i)
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool test_queue_pop(int N)
{
	CQueue queue(N);
	QueueRet ret = QueueRet::ok;

	for (int i = 0; i < N; i++)
	{
		int nVal = 0;
		ret = queue.pop(nVal);
		if (ret == QueueRet::ok)
		{
			return false;
		}
	}

	return true;
}


bool test_output(int nIndex)
{
	COutput output;

	output.update(nIndex);

	int nSum = output.sumFreq();
	if (nSum != 1)
	{
		return false;
	}

	return true;
}

int main()
{
	/*
	*	Unit test for CQueue class N = 0 to 9
	*/
	int nNumTests = 0;
	int nNumFailed = 0;
	for (int N = 0; N < 10; N++)
	{
		if (!test_queue_push(N))
		{
			nNumFailed++;
			std::cout << "test_queue_push(" << N << ") failed" << std::endl;
		}
		nNumTests++;
	}

	std::cout << "Tests for test_queue_push" << std::endl;
	std::cout << "Total number of tests: " << nNumTests << std::endl;
	std::cout << "# of passed test cases: " << nNumTests - nNumFailed << std::endl;
	std::cout << "# of failed test cases: " << nNumFailed << std::endl << std::endl;

	/*
	*	Unit test for CQueue class N = 10 to 20
	*/
	nNumTests = 0;
	nNumFailed = 0;
	for (int N = 0; N < 20; N++)
	{
		if (!test_queue_push_over_10(N))
		{
			nNumFailed++;
			std::cout << "test_queue_push_over_10(" << N << ") failed" << std::endl;
		}
		nNumTests++;
	}

	std::cout << "Tests for test_queue_push_over_10" << std::endl;
	std::cout << "Total number of tests: " << nNumTests << std::endl;
	std::cout << "# of passed test cases: " << nNumTests - nNumFailed << std::endl;
	std::cout << "# of failed test cases: " << nNumFailed << std::endl << std::endl;

	/*
	*	Unit test for CQueue class push/pop, N = 0 to 9
	*/
	nNumTests = 0;
	nNumFailed = 0;
	for (int N = 0; N < 10; N++)
	{
		if (!test_queue_push_pop(N))
		{
			nNumFailed++;
			std::cout << "test_queue_push_pop(" << N << ") failed" << std::endl;
		}
		nNumTests++;
	}

	std::cout << "Tests for test_queue_push_pop" << std::endl;
	std::cout << "Total number of tests: " << nNumTests << std::endl;
	std::cout << "# of passed test cases: " << nNumTests - nNumFailed << std::endl;
	std::cout << "# of failed test cases: " << nNumFailed << std::endl << std::endl;

	/*
	*	Unit test for CQueue class pop, N = 0 to 9
	*/
	nNumTests = 0;
	nNumFailed = 0;
	for (int N = 0; N < 10; N++)
	{
		if (!test_queue_pop(N))
		{
			nNumFailed++;
			std::cout << "test_queue_pop(" << N << ") failed" << std::endl;
		}
		nNumTests++;
	}

	std::cout << "Tests for test_queue_pop" << std::endl;
	std::cout << "Total number of tests: " << nNumTests << std::endl;
	std::cout << "# of passed test cases: " << nNumTests - nNumFailed << std::endl;
	std::cout << "# of failed test cases: " << nNumFailed << std::endl << std::endl;

	/*
	*	Unit test for COutput class
	*/
	nNumTests = 0;
	nNumFailed = 0;
	for (int i = 0; i < 10; i++)
	{
		if (!test_output(i))
		{
			nNumFailed++;
			std::cout << "test_output(" << i << ") failed" << std::endl;
		}
		nNumTests++;
	}

	std::cout << "Tests for test_output (pos)" << std::endl;
	std::cout << "Total number of tests: " << nNumTests << std::endl;
	std::cout << "# of passed test cases: " << nNumTests - nNumFailed << std::endl;
	std::cout << "# of failed test cases: " << nNumFailed << std::endl << std::endl;

	/*
	*	Unit test for COutput class
	*/
	nNumTests = 0;
	nNumFailed = 0;
	for (int i = 10; i < 20; i++)
	{
		if (test_output(i))
		{
			nNumFailed++;
			std::cout << "test_output(" << i << ") failed" << std::endl;
		}
		nNumTests++;
	}

	std::cout << "Tests for test_output (neg)" << std::endl;
	std::cout << "Total number of tests: " << nNumTests << std::endl;
	std::cout << "# of passed test cases: " << nNumTests - nNumFailed << std::endl;
	std::cout << "# of failed test cases: " << nNumFailed << std::endl << std::endl;


	/*
	*	Integration tests for N = 0 to 100
	*/
	nNumTests = 0;
	nNumFailed = 0;
	for (int N = 0; N < 100; N++)
	{
		if (!test_N(N))
		{
			nNumFailed++;
			std::cout << "test_N(" << N << ") failed" << std::endl;
		}
		nNumTests++;
	}

	std::cout << "Tests for test_N" << std::endl;
	std::cout << "Total number of tests: " << nNumTests << std::endl;
	std::cout << "# of passed test cases: " << nNumTests - nNumFailed << std::endl;
	std::cout << "# of failed test cases: " << nNumFailed << std::endl << std::endl;

	/*
	*	Performance test for N = 100,1000,10000,100000,1000000,2000000
	*/
	std::cout << "Performance tests:" << std::endl;

	int N[] = { 100,1000,10000,100000,1000000,2000000 };

	for (int i = 0; i < sizeof(N) / sizeof(int); i++)
	{
		auto t1 = std::chrono::high_resolution_clock::now();

		test_N(N[i]);

		auto t2 = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double, std::milli> ms_double = t2 - t1;
		std::cout << "N = " << N[i] << " : " << ms_double.count() << " ms" << std::endl;;
	}


	return 0;
}
