#include <cstdio>
#include <cstdlib>
#include <string>

#define TABLESIZE 50000
#define EXPTIMES 10000

void shuffle(int *array, size_t n)
{
    if (n > 1) {
        size_t i;
		for (i = 0; i < n - 1; i++) {
	  		size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
	  		int t = array[j];
	  		array[j] = array[i];
	  		array[i] = t;
		}
    }
}

int PearsonHash(int message_int , int table[TABLESIZE])
{
	int hash;
	std::string message = std::to_string(message_int);

	hash = message.length() % TABLESIZE;
	for(int i = 0 ; i < message.length() ; i++)
	{
		hash = table[(hash+atoi(&message[i]))%TABLESIZE];
	}
	return hash;
}

int main()
{
	srand(time(NULL));
	int times = EXPTIMES; //run time experiment
	
	//for Pearson
	int code_table[TABLESIZE];
	for(int i = 0 ; i < TABLESIZE ; i++)
		code_table[i] = i;

	shuffle(code_table,TABLESIZE);

	int collision_times_table[TABLESIZE]={0};
	double collision_prob_table[TABLESIZE]={0};

	while(times > 0)
	{	
		int hash_table[TABLESIZE]={0};
		//generate data
		for(int i = 0 ; i < TABLESIZE ; i++)
		{
			int data = rand();
			//hash code
			int hash_code = PearsonHash(data,code_table);
			if(hash_table[hash_code] > 0)
			{
				hash_table[hash_code]++;
				collision_times_table[i]++;
			}
			else
				hash_table[hash_code]++;
		}
		times--;
	}

	for(int i = 0 ; i < TABLESIZE; i++)
	{
		collision_prob_table[i] = (double) collision_times_table[i] / (double)EXPTIMES;
		printf("%f\n",collision_prob_table[i]);
	}

	return 0;
}
