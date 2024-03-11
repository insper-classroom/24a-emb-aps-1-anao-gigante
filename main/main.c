#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "arq.h"


int button_red = 17;
int button_yellow = 14;
int button_green = 13;
int button_blue = 20;

volatile int vermelho = 0;
volatile int verde = 0;
volatile int amarelo = 0;
volatile int azul = 0;

int BUZZER = 7;

int led_red = 22;
int led_yellow = 21;
int led_green = 11;
int led_blue = 10;

int time = 1;
int freq_r = 1000;
int freq_g = 3000;
int freq_y = 6000;
int freq_b = 9000;


int main() {
    stdio_init_all();
    int dormida = 100;
    int dormida1 = 100*2;
    bool continua = true;

    char* sequencia = genius(0); // Gera a sequência

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

    while(!vermelho && !azul && !verde && !amarelo){}
    indiana_jones();
    sleep_ms(500);
    iniciando();
    sleep_ms(500);
    vermelho = 0;
    azul = 0;
    verde = 0;
    amarelo = 0;

    
    int us = 1000000;
    int limite = 15*us;

    
    while (continua) {
        int tam = strlen(sequencia);
        uint64_t seed = to_us_since_boot(get_absolute_time());
        srand(seed);
        sequencia = adiciona(sequencia, tam);
        reproduzir_sequencia(sequencia, freq_r, freq_g, freq_y, freq_b, BUZZER, led_red, led_yellow, led_green, led_blue); 
        uint64_t start_us = to_us_since_boot(get_absolute_time());
        int contagem = 0;
        while (contagem < tam+1) {
            uint64_t tempo = to_us_since_boot(get_absolute_time());
            if (tempo - start_us > limite) {
                continua = false;
                errou(tam);
                abort();
            }
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
                    start_us = to_us_since_boot(get_absolute_time());
                } else {
                    printf("ERRO\n");
                    continua = false;
                    errou(tam);
                    abort();

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
                    start_us = to_us_since_boot(get_absolute_time());
                } else {
                    printf("ERRO\n");
                    continua = false;
                    errou(tam);
                    abort();

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
                    start_us = to_us_since_boot(get_absolute_time());
                } else {
                    printf("ERRO\n");
                    continua = false;
                    errou(tam);
                    abort();

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
                    start_us = to_us_since_boot(get_absolute_time());
                } else {
                    printf("ERRO\n");
                    continua = false;
                    errou(tam);
                    abort();
                }
            }
        }
        
    }
}
