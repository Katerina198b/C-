#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>
#include <time.h>
#define ten_power 1000000000

long my_floor(long a, long b) {
	int r = 0;
	if (a < 0) return 0;
	if (a % b) r = 1;
	return ((a/b) + r);
}

int main(int argc, char *argv[]) {	
	
	int  numtasks, rank, rc;
	// Инициализация MPI
	rc = MPI_Init(&argc, &argv);
	if (rc != MPI_SUCCESS) {
		printf ("Error starting MPI program. Terminating.\n");
		MPI_Abort(MPI_COMM_WORLD, rc);
	}

	// Получаем число процессов
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	// Получаем ранк процесса
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	//В in.txt лежат 4 чила: длина первого числа, длина второго числа и сами числа
	FILE *fp;
	if((fp=fopen("in3.txt", "rb+"))==NULL) {
		printf ("Cannot open file.\n");
		return 0;
	}
	
	double start,end;
	
	int length_n_1 = 0;
	int length_n_2 = 0;
	fscanf(fp, "%d %d", &length_n_1, &length_n_2);
	long* number_1 = (long *) calloc(length_n_1, sizeof(long));
	long* number_2 = (long *) calloc(length_n_1,  sizeof(long));
	long b = 0;
	int i = 0;
	int j = 0;
	int count = 1;
	int rest = (length_n_1 % 9);
	int length_1 = my_floor(length_n_1 , 9);
	int length_2 = my_floor(length_n_2, 9);
	// Делаем так, чтобы наибольшее по длине число было первым
	if (length_n_2 > length_n_1) {
		int length = length_n_1;
		length_n_1 = length_n_2;
		length_n_2 = length;
		length = length_1;
		length_1 = length_2;
		length_2 = length;
		rest = (length_n_1 % 9);
		length_2 = my_floor(length_n_2 - rest, 9);
		//printf("rest: %d\n", rest);
		for(i = rest; i > 0; i--) count=count*10;
		for (i = 0; i < length_1 - length_2 - my_floor(rest,9); i++) {
				number_2[j] = 0;
				j++;
		}
		for (i = 0; i < length_n_2 - rest; i=i+9) {
			if ((length_n_2 - rest - i) >= 9) {
				fscanf(fp, "%9ld", &b);
				number_2[j] = b;
				j++;
			} else {
				switch (length_n_2 - rest - i){
					case(1):
						fscanf(fp, "%1ld", &b);
						break;
					case(2):
						fscanf(fp, "%2ld", &b);	
						break;
					case(3):
						fscanf(fp, "%3ld", &b);
						break;
					case(4):
						fscanf(fp, "%4ld", &b);
						break;
					case(5):
						fscanf(fp, "%5ld", &b);
						break;
					case(6):
						fscanf(fp, "%6ld", &b);
						break;
					case(7):
						fscanf(fp, "%7ld", &b);
						break;
					case(8):
						fscanf(fp, "%8ld", &b);
						break;
					
				}
				//printf("b: %ld\n", b);
				number_2[j] = b;
				j++;
			}
		}
		fscanf(fp, "%9ld ", &b);
		number_2[j] = b;
		j = 0;
		for(i = 0; i < length_n_1; i=i+9) {
			fscanf(fp, "%9ld ", &b);
			number_1[j] = b;
			j++;
		}
	} else {
		length_2 = my_floor(length_n_2 - rest, 9);
		//printf("rest: %d\n", rest);
		for(i = rest; i > 0; i--) count=count*10;
		j = 0;
		for(i = 0; i < length_n_1; i=i+9) {
			fscanf(fp, "%9ld ", &b);
			number_1[j] = b;
			j++;
		}
		j = 0;
		for (i = 0; i < length_1 - length_2 - my_floor(rest,9); i++) {
				number_2[j] = 0;
				j++;
		}
		for (i = 0; i < length_n_2 - rest; i=i+9) {
			if ((length_n_2 - rest - i) >= 9) {
				fscanf(fp, "%9ld", &b);
				number_2[j] = b;
				j++;
			} else {
				switch (length_n_2 - rest - i){
					case(1):
						fscanf(fp, "%1ld", &b);
						break;
					case(2):
						fscanf(fp, "%2ld", &b);	
						break;
					case(3):
						fscanf(fp, "%3ld", &b);
						break;
					case(4):
						fscanf(fp, "%4ld", &b);
						break;
					case(5):
						fscanf(fp, "%5ld", &b);
						break;
					case(6):
						fscanf(fp, "%6ld", &b);
						break;
					case(7):
						fscanf(fp, "%7ld", &b);
						break;
					case(8):
						fscanf(fp, "%8ld", &b);
						break;
					
				}
				//printf("b: %ld\n", b);
				number_2[j] = b;
				j++;
			}
		}
		fscanf(fp, "%9ld ", &b);
		number_2[j] = b;
	}

	if (rank == 0) start = MPI_Wtime();
	//Cпекулятивный алгоритм суммирования
	int size= length_1 / numtasks;
	long* answer_0 = number_1;
	long* answer_1 = (long*) calloc(length_1, sizeof(long));
	memcpy(answer_1, number_1, sizeof(long)*length_1);
	int r[2] = {0,0};
	int rr = 0;
	int begin = 1;
	
	if (rank == numtasks - 1) {
		for(int k = length_1; k > (rank - 1) * size; k--) {
			if (begin) {
				begin = 0;
				rr = (answer_0[k-1] + number_2[k-1] + r[0]) / count;
				answer_0[k-1] = (answer_0[k-1] + number_2[k-1] + r[0]) % count;
				r[0] = rr;
				r[1] = rr;
				
			} else {
				rr = (answer_0[k-1] + number_2[k-1] + r[0]) / ten_power;
				answer_0[k-1] = (answer_0[k-1] + number_2[k-1] + r[0]) % ten_power;
				r[0] = rr;
				r[1] = rr;
			}
		}
	} else {
		for(int k = (rank + 1) * size; k > rank * size; k--) {
			if (begin) {
				r[1] = 1;
				begin = 0;
			}
			rr = (number_1[k-1] + number_2[k-1] + r[1]) / ten_power;
			answer_1[k-1] = (number_1[k-1] + number_2[k-1] + r[1]) % ten_power;
			r[1] = rr;
			rr = (number_1[k-1] + number_2[k-1] + r[0]) / ten_power;
			answer_0[k-1] = (number_1[k-1] + number_2[k-1] + r[0]) % ten_power;
			r[0] = rr;
		}
	}
	if (rank == 0) {
		end = MPI_Wtime();
		printf("Спекулятивный алгоритм суммирования: %f\n", end - start);
		start = MPI_Wtime();
	}
	//Отправка сообщений между процессами методом сдваивания.
	long a[2] = {r[0] << rank, r[1] << rank};
	//printf("Num tack is %d, a = %ld\n", rank, a[0]);
	long answer[2] = {0, 0};
	j = 1;
	for (int i = 2; i <= numtasks; i=i*2) {
		if ((rank + j) % i == 0) {
			MPI_Send(a, 2 , MPI_LONG, rank - j, 0, MPI_COMM_WORLD);
		} 
		if(rank % i == 0){
			MPI_Recv(answer,2, MPI_LONG, rank + j, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			if ((answer[0] >> (rank + 1) == 0) && (answer[1] >> (rank + 1) == 0)) {
				a[0] = a[0] + answer[0];
				a[1] = a[0] + answer[1];
			} else if ((answer[0] >> (rank +1) == 0) && (answer[1] >> (rank + 1) == 1)) {
				a[0] = a[0] + answer[0];
				a[1] = a[1] + answer[1];
			} else if ((answer[0] >> (rank +1) == 1) && (answer[1] >> (rank + 1) == 0)) {
				a[0] = a[0] + answer[1];
				a[1] = a[1] + answer[0];
			} else {
				a[0] = a[1] + answer[1];
				a[1] = a[1] + answer[0];
			}
		}
		j=j*2;
	}
	
	
	if (rank == 0) {
		end = MPI_Wtime();
		//printf("Правильная последоваиельность переносов с десятичном виде: %ld\n", a[0]);
		printf("Время выполнения отправки: %f секунд.\n", end - start);
		//Вывод результата суммирования
		/*
		long* ans = (long*) calloc(length_1, sizeof(long));
		long* trash = (long*) calloc(length_1 - rank * size, sizeof(long));
		if (a[0]) memcpy(ans, answer_1, sizeof(long)*size); 
		else memcpy(ans, answer_0, sizeof(long)*size);
		for (int i = 1; i < numtasks; i++) {
			if (a[0] << i) {
				MPI_Recv(ans + i * size, length_1 - i * size, MPI_LONG, i, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				MPI_Recv(ans + i * size, length_1 - i * size, MPI_LONG, i, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);	
			} else {
				MPI_Recv(ans + i * size, length_1 - i * size, MPI_LONG, i, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				MPI_Recv(trash, length_1 - rank * size, MPI_LONG, i, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);	
			}
		}
		printf("answer: ");
		int j = ten_power/10;
		if (a[1]%2) printf("1");
		for (int k = 0; k < length_1; k++) {
			if (k == (length_1 - 1)) j = count/10;
			
			if (ans[k] != 0) {
				
				while(!(ans[k] / j)) {
					printf("0");
					j = j/10;
				}
			} else {
				if (k == (length_1 -1))
					for (int i = 0; i < rest-1; i++) {
						printf("0");
					}
				else printf("0000000");
			}
			printf("%ld", ans[k]);
		}
	*/		
	}
	/* else {		
		if (rank != numtasks - 1) {
			MPI_Send(answer_0 + rank * size, size, MPI_LONG, 0, 99, MPI_COMM_WORLD);
			MPI_Send(answer_0 + rank * size, size, MPI_LONG, 0, 99, MPI_COMM_WORLD);
		} else {
			MPI_Send(answer_0 + rank * size, length_1 - rank * size, MPI_LONG, 0, 99, MPI_COMM_WORLD);
			MPI_Send(answer_0 + rank * size, length_1 - rank * size, MPI_LONG, 0, 99, MPI_COMM_WORLD);
		}
	}
	*/
	free(number_1);
	free(number_2);
	
	// Завершение работы с MPI
	MPI_Finalize();
	return 0;
}
