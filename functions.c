#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "functions.h"

#define SIZE 30

extern char forest[SIZE][SIZE];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* fire_generator(void* arg) {
    while (1) {
        sleep(3);
        pthread_mutex_lock(&mutex);
        int x = rand() % SIZE;
        int y = rand() % SIZE;
        if (forest[x][y] == '-') {
            forest[x][y] = '@';
            printf("Incêndio iniciado em (%d, %d)\n", x, y);
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* sensor_node(void* arg) {
    int id = (intptr_t)arg;
    int x = id / SIZE;
    int y = id % SIZE;

    while (1) {
        pthread_mutex_lock(&mutex);
        if (forest[x][y] == '@') {
            printf("Sensor (%d, %d) detectou fogo!\n", x, y);
            forest[x][y] = 'D'; // Marcar como detectado
            // Sinalizar a central apenas se estiver na borda
            if (x == 0 || x == SIZE-1 || y == 0 || y == SIZE-1) {
                pthread_cond_signal(&cond);
            }
        }
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}

void* control_center(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond, &mutex);
        printf("Central de controle recebeu alerta de incêndio!\n");
        // Lógica para combater o fogo
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (forest[i][j] == 'D') { // Verificar incêndios detectados
                    forest[i][j] = '/';
                    printf("Fogo combatido em (%d, %d)\n", i, j);
                }
            }
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void print_forest() {
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", forest[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    pthread_mutex_unlock(&mutex);
}