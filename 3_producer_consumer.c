#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>    // For sleep()
#include <pthread.h>   // For threading functions
#include <semaphore.h> // For semaphore functions
#include <time.h>      // For srand()

// Define the size of the shared buffer
#define BUFFER_SIZE 5

// Shared resources
int buffer[BUFFER_SIZE];
int in_index = 0;  // Index where producer will place the next item
int out_index = 0; // Index from where consumer will pick up the next item

// Semaphores
sem_t mutex; // For mutual exclusion to access the buffer
sem_t empty; // Counts empty buffer slots
sem_t full;  // Counts full buffer slots

/**
 * @brief The producer thread function.
 * * This function continuously produces items and places them in the buffer.
 */
void *producer(void *arg)
{
    int item;
    while (1)
    {
        // Produce a random item
        item = rand() % 100;

        // 1. Wait for an empty slot
        sem_wait(&empty);

        // 2. Acquire the lock to access the buffer (critical section)
        sem_wait(&mutex);

        // --- Critical Section Start ---
        buffer[in_index] = item;
        printf("Producer %ld: Produced item %d at index %d\n", (long)pthread_self(), item, in_index);
        in_index = (in_index + 1) % BUFFER_SIZE; // Circular buffer logic
        // --- Critical Section End ---

        // 3. Release the lock
        sem_post(&mutex);

        // 4. Signal that a slot is now full
        sem_post(&full);

        // Simulate time taken to produce
        sleep(1);
    }
    return NULL;
}

/**
 * @brief The consumer thread function.
 * * This function continuously consumes items from the buffer.
 */
void *consumer(void *arg)
{
    int item;
    while (1)
    {
        // 1. Wait for a full slot
        sem_wait(&full);

        // 2. Acquire the lock to access the buffer (critical section)
        sem_wait(&mutex);

        // --- Critical Section Start ---
        item = buffer[out_index];
        printf("Consumer %ld: Consumed item %d from index %d\n", (long)pthread_self(), item, out_index);
        out_index = (out_index + 1) % BUFFER_SIZE; // Circular buffer logic
        // --- Critical Section End ---

        // 3. Release the lock
        sem_post(&mutex);

        // 4. Signal that a slot is now empty
        sem_post(&empty);

        // Simulate time taken to consume
        sleep(2);
    }
    return NULL;
}

int main()
{
    pthread_t prod_tid, cons_tid;

    // Seed the random number generator
    srand(time(NULL));

    // Initialize the semaphores
    // sem_init(semaphore, pshared, initial_value)
    // pshared = 0 means the semaphore is shared between threads of the same process
    sem_init(&mutex, 0, 1);           // Initial value 1 (unlocked)
    sem_init(&empty, 0, BUFFER_SIZE); // Initial value BUFFER_SIZE (all slots are empty)
    sem_init(&full, 0, 0);            // Initial value 0 (no items to consume)

    printf("Starting producer and consumer threads...\n");

    // Create the producer and consumer threads
    if (pthread_create(&prod_tid, NULL, producer, NULL) != 0)
    {
        perror("Failed to create producer thread");
        return 1;
    }
    if (pthread_create(&cons_tid, NULL, consumer, NULL) != 0)
    {
        perror("Failed to create consumer thread");
        return 1;
    }

    // Wait for the threads to finish (they won't in this infinite loop example,
    // but this is good practice for threads that do terminate)
    pthread_join(prod_tid, NULL);
    pthread_join(cons_tid, NULL);

    // Destroy the semaphores
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}