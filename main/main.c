/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"


volatile int tam = 1;

int led_red = 22;
int led_yellow = 21;
int led_green = 11;
int led_blue = 10;

int button_red = 17;
int button_yellow = 14;
int button_green = 13;
int button_blue = 20;

int BUZZER = 7;

volatile bool vermelho = false;
volatile bool verde = false;
volatile bool amarelo = false;
volatile bool azul = false;

int time = 1;
int freq_r = 1000;
int freq_g = 3000;
int freq_y = 6000;
int freq_b = 9000;


void btn_callback(uint gpio, uint32_t events) {
  if (events == GPIO_IRQ_EDGE_FALL) { // fall edge
    if (gpio == button_red) {
      vermelho = true;
    }else if (gpio == button_green) {
      verde = true;
    }else if (gpio == button_yellow) {
        amarelo = true;
    }else if (gpio == button_blue) {
        azul = true;
    }
}}

void buzzer(int frequencia, int pin){
    int periodo = 1000000 / frequencia;
    int pausa = periodo / 2.0;

    for (int i = 0; i < (((200*1000)/periodo));i++){
        gpio_put(pin, 1);
        sleep_us(pausa);
        gpio_put(pin, 0);
        sleep_us(pausa);
    }
}

char* genius(int tam) {
    char* opcoes = "rbgy"; // Mudança: Use uma string para as opções
    char* lista = malloc((tam + 1) * sizeof(char)); // Aloca espaço para a lista
    tam++; // Mudança: Incrementa tam aqui para alocar espaço para o caractere nulo
    for (int i = 0; i < tam; i++) {
        lista[i] = opcoes[rand() % 4]; // Mudança: Escolha uma cor aleatória
    }
    lista[tam] = '\0'; // Adiciona o caractere nulo ao final da lista
    return lista;
}

void reproduzir_sequencia(char* sequencia, int freq_r, int freq_g, int freq_y, int freq_b, int BUZZER,
                          int led_red, int led_yellow, int led_green, int led_blue) {
    int i = 0;
    while (sequencia[i] != '\0') {
        switch (sequencia[i]) {
            case 'r':
                gpio_put(led_red, 1);
                buzzer(freq_r, BUZZER);
                gpio_put(led_red, 0);
                break;
            case 'b':
                gpio_put(led_blue, 1);
                buzzer(freq_b, BUZZER);
                gpio_put(led_blue, 0);
                break;
            case 'g':
                gpio_put(led_green, 1);
                buzzer(freq_g, BUZZER);
                gpio_put(led_green, 0);
                break;
            case 'y':
                gpio_put(led_yellow, 1);
                buzzer(freq_y, BUZZER);
                gpio_put(led_yellow, 0);
                break;
        }
        sleep_ms(1000); // Mudança: Aguarde um curto intervalo entre as cores
        i++;
    }
}


int main() {
    stdio_init_all();

    gpio_init(led_red);
    gpio_init(led_yellow);
    gpio_init(led_green);
    gpio_init(led_blue);

    gpio_init(button_red);
    gpio_init(button_yellow);
    gpio_init(button_green);
    gpio_init(button_blue);

    gpio_set_dir(led_red, GPIO_OUT);
    gpio_set_dir(led_yellow, GPIO_OUT);
    gpio_set_dir(led_green, GPIO_OUT);
    gpio_set_dir(led_blue, GPIO_OUT);

    gpio_set_dir(button_red, GPIO_IN);
    gpio_set_dir(button_yellow, GPIO_IN);
    gpio_set_dir(button_green, GPIO_IN);
    gpio_set_dir(button_blue, GPIO_IN);

    gpio_pull_up(button_red);
    gpio_pull_up(button_yellow);
    gpio_pull_up(button_green);
    gpio_pull_up(button_blue);

    gpio_init(BUZZER);
    gpio_set_dir(BUZZER, GPIO_OUT);

    gpio_set_irq_enabled_with_callback(button_red, GPIO_IRQ_EDGE_FALL, true, &btn_callback);

    gpio_set_irq_enabled(button_blue, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(button_yellow, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(button_green, GPIO_IRQ_EDGE_FALL, true);

    while (true) {
        char* sequencia = genius(tam); // Gerar a sequência
        
        reproduzir_sequencia(sequencia, freq_r, freq_g, freq_y, freq_b, BUZZER, led_red, led_yellow, led_green, led_blue);
        int contagem = 0;
        while (contagem < tam) {
            if (vermelho) {
                if (sequencia[0] == 'r') {
                    gpio_put(led_red,1);
                    buzzer(freq_r, BUZZER);
                    sleep_ms(100);
                    vermelho = false;
                    printf("Vermelho\n");
                    gpio_put(led_red,0);
                    contagem++;
                } else {
                    printf("ERRO\n");
                    break;
                }
            } else if (verde) {
                if (sequencia[0] == 'g') {
                    gpio_put(led_green,1);
                    buzzer(freq_g, BUZZER);
                    sleep_ms(100);
                    verde = false;
                    printf("Verde\n");
                    gpio_put(led_green,0);
                    contagem++;
                } else {
                    printf("ERRO\n");
                    break;
                }
            } else if (amarelo) {
                if (sequencia[0] == 'y') {
                    gpio_put(led_yellow,1);
                    buzzer(freq_y, BUZZER);
                    sleep_ms(100);
                    amarelo = false;
                    printf("Amarelo\n");
                    gpio_put(led_yellow,0);
                    contagem++;
                } else {
                    printf("ERRO\n");
                    break;
                }
            } else if (azul) {
                if (sequencia[0] == 'b') {
                    gpio_put(led_blue,1);
                    buzzer(freq_b, BUZZER);
                    sleep_ms(100);
                    azul = false;
                    printf("Azul\n");
                    gpio_put(led_blue,0);
                    contagem++;
                } else {
                    printf("ERRO\n");
                    break;
                }
            }
        }
        
    }
}


//     while (true) {

//         if (vermelho) {
//             gpio_put(led_red,1);
//             buzzer(freq_r, BUZZER);
//             sleep_ms(100);
//             vermelho = false;
//             printf("Vermelho\n");
//             gpio_put(led_red,0);

//         }
//         if (verde) {
//             gpio_put(led_green,1);
//             buzzer(freq_g, BUZZER);
//             sleep_ms(100);
//             verde = false;
//             printf("Verde\n");
//             gpio_put(led_green,0);
//         }
//         if (amarelo) {
//             gpio_put(led_yellow,1);
//             buzzer(freq_y, BUZZER);
//             sleep_ms(100);
//             amarelo = false;
//             printf("Amarelo\n");
//             gpio_put(led_yellow,0);
//         }
//         if (azul) {
//             gpio_put(led_blue,1);
//             buzzer(freq_b, BUZZER);
//             sleep_ms(100);
//             azul = false;
//             printf("Azul\n");
//             gpio_put(led_blue,0);
//         }
//     }
// }