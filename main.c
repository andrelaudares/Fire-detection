#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "functions.h"

#define SIZE 30
#define NUM_SENSORS (SIZE * SIZE)

char forest[SIZE][SIZE];

void initialize_forest() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            forest[i][j] = '-';
        }
    }
}

int main() {
    initialize_forest();

    pthread_t sensor_threads[NUM_SENSORS];
    pthread_t fire_thread, control_thread;

    // Criação da thread geradora de incêndios
    pthread_create(&fire_thread, NULL, fire_generator, NULL);

    // Criação das threads dos nós sensores
    for (int i = 0; i < NUM_SENSORS; i++) {
        pthread_create(&sensor_threads[i], NULL, sensor_node, (void*)(intptr_t)i);
    }

    // Criação da thread da central de controle
    pthread_create(&control_thread, NULL, control_center, NULL);

    // Espera pelas threads (neste exemplo, o programa roda indefinidamente)
    pthread_join(fire_thread, NULL);
    pthread_join(control_thread, NULL);
    for (int i = 0; i < NUM_SENSORS; i++) {
        pthread_join(sensor_threads[i], NULL);
    }

    return 0;
}