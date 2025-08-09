#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // For sleep()
#include <pthread.h> // For threading functions
#include <time.h>    // For srand()

#define NUM_PHILOSOPHERS 5

// Global variables
pthread_t philosophers[NUM_PHILOSOPHERS];
pthread_mutex_t chopsticks[NUM_PHILOSOPHERS];
pthread_mutex_t screen_lock; // To prevent garbled printf output

/**
 * @brief The main routine for each philosopher thread.
 */
void *philosopher(void *arg)
{
    int id = *(int *)arg;

    // Determine the indices of the left and right chopsticks
    int left_chopstick = id;
    int right_chopstick = (id + 1) % NUM_PHILOSOPHERS;

    while (1)
    {
        // --- THINKING ---
        pthread_mutex_lock(&screen_lock);
        printf("Philosopher %d is thinking.\n", id);
        pthread_mutex_unlock(&screen_lock);
        sleep(1 + rand() % 3); // Think for a random duration

        // --- HUNGRY & PICKING UP CHOPSTICKS ---
        pthread_mutex_lock(&screen_lock);
        printf("Philosopher %d is hungry.\n", id);
        pthread_mutex_unlock(&screen_lock);

        // Asymmetric solution to prevent deadlock
        if (id == NUM_PHILOSOPHERS - 1)
        {
            // The last philosopher picks up the right chopstick first
            pthread_mutex_lock(&chopsticks[right_chopstick]);
            pthread_mutex_lock(&chopsticks[left_chopstick]);
        }
        else
        {
            // All other philosophers pick up the left chopstick first
            pthread_mutex_lock(&chopsticks[left_chopstick]);
            pthread_mutex_lock(&chopsticks[right_chopstick]);
        }

        // --- EATING ---
        pthread_mutex_lock(&screen_lock);
        printf("Philosopher %d is eating.\n", id);
        pthread_mutex_unlock(&screen_lock);
        sleep(1 + rand() % 2); // Eat for a random duration

        // --- FINISHED EATING & PUTTING DOWN CHOPSTICKS ---
        // The order of unlocking doesn't matter
        pthread_mutex_unlock(&chopsticks[left_chopstick]);
        pthread_mutex_unlock(&chopsticks[right_chopstick]);

        pthread_mutex_lock(&screen_lock);
        printf("Philosopher %d finished eating and is back to thinking.\n", id);
        pthread_mutex_unlock(&screen_lock);
    }

    return NULL;
}

int main()
{
    int i;
    int phil_ids[NUM_PHILOSOPHERS];

    srand(time(NULL));

    // Initialize all mutexes
    pthread_mutex_init(&screen_lock, NULL);
    for (i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_mutex_init(&chopsticks[i], NULL);
        phil_ids[i] = i;
    }

    printf("Starting the Dining Philosophers simulation...\n");

    // Create a thread for each philosopher
    for (i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        if (pthread_create(&philosophers[i], NULL, philosopher, &phil_ids[i]) != 0)
        {
            perror("Failed to create thread");
            return 1;
        }
    }

    // Wait for philosopher threads to finish (they won't in this infinite loop)
    for (i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy mutexes (won't be reached, but good practice)
    pthread_mutex_destroy(&screen_lock);
    for (i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_mutex_destroy(&chopsticks[i]);
    }

    return 0;
}