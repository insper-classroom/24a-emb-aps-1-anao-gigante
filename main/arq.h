#ifndef JOGO_GENIUS_H
#define JOGO_GENIUS_H
#include <stdint.h> // Adicione essa linha para corrigir o erro com uint32_t
#include <stdbool.h>

extern int button_red;
extern int button_yellow;
extern int button_green;
extern int button_blue;

extern volatile bool vermelho;
extern volatile bool verde;
extern volatile bool amarelo;
extern volatile bool azul;

// extern bool vermelho;
// extern bool verde;
// extern bool amarelo;
// extern bool azul;

extern int BUZZER;

extern int led_red;
extern int led_yellow;
extern int led_green;
extern int led_blue;

extern int time;
extern int freq_r;
extern int freq_g;
extern int freq_y;
extern int freq_b;

void btn_callback(uint gpio, uint32_t events);
char* genius(int tam);
void reproduzir_sequencia(char* sequencia, int freq_r, int freq_g, int freq_y, int freq_b, int BUZZER, int led_red, int led_yellow, int led_green, int led_blue);
char* adiciona(char lista[], int tam);
void errou(int tam);
void iniciando();

#endif /* JOGO_GENIUS_H */
