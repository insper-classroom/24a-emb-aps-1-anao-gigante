#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "arq.h"


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

void indiana_jones(){

    int freq_re = 293;
    int freq_mi = 330;
    int freq_sol = 392;
    int freq_la = 440;
    int freq_si = 494;

    buzzer(freq_re, BUZZER);
    buzzer(freq_re, BUZZER);
    buzzer(freq_re, BUZZER);
    buzzer(freq_re, BUZZER);
    buzzer(freq_mi, BUZZER);
    buzzer(freq_sol,BUZZER);
    buzzer(freq_la, BUZZER);
    buzzer(freq_sol,BUZZER);
    buzzer(freq_mi, BUZZER);
    buzzer(freq_re, BUZZER);
    buzzer(freq_re, BUZZER);
    buzzer(freq_re, BUZZER);
    buzzer(freq_re, BUZZER);
    buzzer(freq_mi, BUZZER);
    buzzer(freq_sol,BUZZER);
    buzzer(freq_la, BUZZER);
    buzzer(freq_si, BUZZER);
    buzzer(freq_la, BUZZER);
    buzzer(freq_sol,BUZZER);
    buzzer(freq_mi, BUZZER);
    buzzer(freq_re, BUZZER);
    
    }

char* genius(int tam) {
    char* opcoes = "rbgy"; // Mudança: Use uma string para as opções
    char* lista = malloc((tam + 1) * sizeof(char)); // Aloca espaço para a lista
    tam++; // Mudança: Incrementa tam aqui para alocar espaço para o caractere nulo
    for (int i = 0; i < tam; i++) {
        lista[i] = opcoes[rand() % 4]; // Mudança: Escolha uma cor aleatória
    }
    lista[tam] = '\0'; // Adiciona o caractere nulo ao final da lista
    printf("Sequencia: %s\n", lista);
    return lista;
}

void reproduzir_sequencia(char* sequencia, int freq_r, int freq_g, int freq_y, int freq_b, int BUZZER, int led_red, int led_yellow, int led_green, int led_blue) {
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

char* adiciona(char lista[], int tam){
    char* opcoes = "rbgy";
    char opcao = opcoes[rand() % 4];
    lista[tam] = opcao;
    lista[tam+1] = '\0';
    printf("Sequencia: %s\n", lista);
    return lista;
} 

void errou(int tam){
    gpio_put(led_red,1);
    gpio_put(led_yellow,1);
    gpio_put(led_green,1);
    gpio_put(led_blue,1);
    buzzer(11000, BUZZER);
    sleep_ms(1000);
    gpio_put(led_red,0);
    gpio_put(led_yellow,0);
    gpio_put(led_green,0);
    gpio_put(led_blue,0);
    sleep_ms(1000);

    for(int i = 1; i < tam; i++){
        gpio_put(led_red,1);
        gpio_put(led_yellow,1);
        gpio_put(led_green,1);
        gpio_put(led_blue,1);
        buzzer(freq_b, BUZZER);
        sleep_ms(200);
        printf("%d \n",i);
        gpio_put(led_red,0);
        gpio_put(led_yellow,0);
        gpio_put(led_green,0);
        gpio_put(led_blue,0);
        sleep_ms(200);
    }
}

void iniciando(){
    for(int i = 0; i < 3; i++){
        gpio_put(led_red,1);
        buzzer(freq_r, BUZZER);
        gpio_put(led_yellow,1);
        buzzer(freq_y, BUZZER);
        gpio_put(led_green,1);
        buzzer(freq_g, BUZZER);
        gpio_put(led_blue,1);
        buzzer(freq_b, BUZZER);
        sleep_ms(50);
        printf("%d \n",i);
        gpio_put(led_red,0);
        gpio_put(led_yellow,0);
        gpio_put(led_green,0);
        gpio_put(led_blue,0);
        sleep_ms(50);
    }
    sleep_ms(1000);
    
}