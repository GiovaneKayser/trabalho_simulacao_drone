
#include "FreeRTOS.h"
#include "task.h"
#include "basic_io.h"

void vArfagem(void* pvParameters);
void vRolagem(void* pvParameters);
void vGuinada(void* pvParameters);


float motor0 = 0;
float motor1 = 0;
float motor2 = 0;
float motor3 = 0;
// Task da Arfagem
/*
A Tarefa criada para manobra de arfagem deve se mover para frente e para trás,
alterar a velocidade dos motores correspondente a manobra de arfagem,
neste sentido incrementar ou decrementar a variável em 25 vezes conforme a direção;
*/
void vArfagem(boolean* pvParameters()) {
    int velocidadeDeModificacao = 1;
    boolean direction = (*pvParameters);

    if (direction) {
        vPrintString("indo para frente");
    }
    else {
        vPrintString("indo para tras");
    }
    for (int i = 0; i < 25; i++) {
        if (direction) {
            if (motor0 > 0 && motor1 > 1) {
                motor0 -= velocidadeDeModificacao;
                motor1 -= velocidadeDeModificacao;
            }
            motor2 += velocidadeDeModificacao;
            motor3 += velocidadeDeModificacao;
        }
        else {
            motor0 += velocidadeDeModificacao;
            motor1 += velocidadeDeModificacao;
            if (motor2 > 0 && motor3 > 0) {
                motor2 -= velocidadeDeModificacao;
                motor3 -= velocidadeDeModificacao;
            }
        }

        vTaskDelay(40);
    }
    vPrintString("\n");
    vPrintStringAndNumber("Velocidade Motor 1 =", motor0);
    vPrintStringAndNumber("Velocidade Motor 2 =", motor1);
    vPrintStringAndNumber("Velocidade Motor 3 =", motor2);
    vPrintStringAndNumber("Velocidade Motor 4 =", motor3);
    vTaskDelete(NULL);
}

// Task da Rolagem
/*
A Tarefa criada para manobra de rolagem deve se mover para esquerda e para direita,
alterar a velocidade dos motores correspondente a manobra de rolagem,
neste sentido incrementar ou decrementar a variável em 50 vezes conforme a direção;
*/
void vRolagem(boolean* pvParameters()) {
    //virar à direita: aumentar a velocidade dos motores 0 e 3, diminuir a velocidade dos motores 1 e 2;
    //virar à esquerda: diminuir a velocidade dos motores 0 e 3, aumentar a velocidade dos motores 1 e 2.
    //O controle de rolagem deve ser realizado 50 vezes por segundo (período de 20 ms);
    vPrintString("Iniciado manobra Rolagem...");
    vPrintString("\n");

    boolean vRolagem = (*pvParameters);
    if (vRolagem) {
        vPrintString("virando à direita");
        vPrintString("\n");

    }
    else {
        vPrintString("virando à esquerda");
        vPrintString("\n");

    }
    for (int i = 0; i < 50; i++) {
        if (vRolagem) {
            motor0 += 1;
            motor3 += 1;
            if (motor1 > 0 && motor2 > 0) {
                motor1 -= 1;
                motor2 -= 1;
            }
        }
        else {
            if (motor0 > 0 && motor3 > 0) {
                motor0 -= 1;
                motor3 -= 1;
            }
            motor1 += 1;
            motor2 += 1;
        }
        vTaskDelay(20);
    }
    vPrintString("\n");
    vPrintString("Fim manobra Rolagem...");
    vPrintString("\n");
    vPrintStringAndNumber("Motor0", motor0);
    vPrintStringAndNumber("Motor1", motor1);
    vPrintStringAndNumber("Motor2", motor2);
    vPrintStringAndNumber("Motor3", motor3);
    vTaskDelete(NULL);
}

// Task da Guinada
/*
A Tarefa criada para manobra de guinada deve verificar se o sentido é horário ou anti-horário,
alterar a velocidade dos motores correspondente a manobra da guinada,
neste sentido incrementar ou decrementar a variável em 100 vezes conforme o sentido;
*/
void vGuinada(boolean* pvParameters()) {
    vPrintString("Iniciado manobra Guinada...");
    vPrintString("\n");

    boolean horario = (*pvParameters);
    if (horario) {
        vPrintString("Horario");
        vPrintString("\n");

    }
    else {
        vPrintString("Nao - Horario");
        vPrintString("\n");

    }
    for (int i = 0; i < 100; i++) {
        if (horario) {
            motor0 += 1;
            motor2 += 1;
            if (motor1 > 0 && motor3 > 0) {
                motor1 -= 1;
                motor3 -= 1;
            }
        }
        else {
            if (motor0 > 0 && motor2 > 0) {
                motor0 -= 1;
                motor2 -= 1;
            }
            motor1 += 1;
            motor3 += 1;
        }
        vTaskDelay(10);
    }
    vPrintString("\n");
    vPrintString("Fim da manobra!");
    vPrintString("\n");
    vPrintStringAndNumber("Motor0", motor0);
    vPrintStringAndNumber("Motor1", motor1);
    vPrintStringAndNumber("Motor2", motor2);
    vPrintStringAndNumber("Motor3", motor3);
    vTaskDelete(NULL);
}


int main_(void) {

    xTaskCreate(vArfagem, "Arfagem", 1000,TRUE, 1, NULL);
    xTaskCreate(vRolagem, "Rolagem", 1000,FALSE, 1, NULL);
    xTaskCreate(vGuinada, "Guinada", 1000,FALSE, 1, NULL);

    vTaskStartScheduler();

    for (;; );
    return 0;
}