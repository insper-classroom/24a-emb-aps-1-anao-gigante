/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "main.h"




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

    char* sequencia = genius(tam); // Gera a sequência


    while(!vermelho && !azul && !verde && !amarelo){}
    iniciando();
    vermelho = false;
    azul = false;
    verde = false;
    amarelo = false;

    uint64_t start_us = to_us_since_boot(get_absolute_time());
    srand(start_us);

    while (continua) {
        tam = strlen(sequencia);
        // dormida = dormida/(tam/2);   
        sequencia = adiciona(sequencia, tam);
        reproduzir_sequencia(sequencia, freq_r, freq_g, freq_y, freq_b, BUZZER, led_red, led_yellow, led_green, led_blue); 
        int contagem = 0;
        while (contagem < tam+1) {
            if (vermelho) {
                if (sequencia[contagem] == 'r') {
                    gpio_put(led_red,1);
                    buzzer(freq_r, BUZZER);
                    vermelho = false;
                    printf("Vermelho\n");
                    sleep_ms(dormida);
                    gpio_put(led_red,0);
                    sleep_ms(dormida1);
                    contagem++;
                } else {
                    printf("ERRO\n");
                    continua = false;
                    errou(tam);
                    abort();
                    printf("abortou\n");

                }
            } else if (verde) {
                if (sequencia[contagem] == 'g') {
                    gpio_put(led_green,1);
                    buzzer(freq_g, BUZZER);
                    sleep_ms(dormida);
                    verde = false;
                    printf("Verde\n");
                    gpio_put(led_green,0);
                    sleep_ms(dormida1);
                    contagem++;
                } else {
                    printf("ERRO\n");
                    continua = false;
                    errou(tam);
                    abort();
                    printf("abortou\n");

                }
            } else if (amarelo) {
                if (sequencia[contagem] == 'y') {
                    gpio_put(led_yellow,1);
                    buzzer(freq_y, BUZZER);
                    sleep_ms(dormida);
                    amarelo = false;
                    printf("Amarelo\n");
                    gpio_put(led_yellow,0);
                    sleep_ms(dormida1);
                    contagem++;
                } else {
                    printf("ERRO\n");
                    continua = false;
                    errou(tam);
                    abort();
                    printf("abortou\n");

                }
            } else if (azul) {
                if (sequencia[contagem] == 'b') {
                    gpio_put(led_blue,1);
                    buzzer(freq_b, BUZZER);
                    sleep_ms(dormida);
                    azul = false;
                    printf("Azul\n");
                    gpio_put(led_blue,0);
                    sleep_ms(dormida1);
                    contagem++;
                } else {
                    printf("ERRO\n");
                    continua = false;
                    errou(tam);
                    abort();
                    printf("abortou\n");
                }
            }
        }
        
    }
}