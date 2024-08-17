# Trabalho Prático 1 – Simulador Protocolo MESI em uma aplicação
## OBJETIVO
Implementar um programa que simule uma memória cache gerenciada utilizando o protocolo MESI (Modify, Exclusive, Shared, Invalid) implementado em uma aplicação real.
## DESCRIÇÃO
O trabalho consiste em realizar uma simulação de pelo menos três processadores, cada um com um nível de memória cache dedicada e uma memória RAM compartilhada entre os processadores.
O programa deve conter dois espaços de endereçamento, um para simular a memória principal e outro para simular a memória cache alocada a cada um dos processadores.
O programa deve solicitar acessos aos dados contidos na memória. O espaço da memória principal deve ter pelo menos 50 posições, e o espaço da memória cache deve ter pelo menos 5 posições. O tamanho do bloco da memória RAM deve ser levado em conta, pois um bloco da memória RAM é alocado a uma linha da memória cache.
As solicitações podem ocorrer em cada um dos processadores, ou seja, o processador 1 pode solicitar um dado da posição X da memória RAM e o processador 2 também pode solicitar dados de qualquer posição da memória.
A representação da memória e das caches devem ser similares as representações abaixo:
<img src="![image](https://github.com/user-attachments/assets/43c83ebb-1dcf-4f26-a7ca-784b9369fb2c)"/>
