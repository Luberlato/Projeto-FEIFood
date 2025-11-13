#ifndef FEIFOOD_H
#define FEIFOOD_H

void cadastrarUsuario(char usuario[255]);


int fazerLogin(char usuario[255]);

void buscarComida(char usuario[255]);
void menuInicial(char usuario[255]);


void menuPedido(char usuario[255]);


void fazerPedido(char usuario[255]);

void modificarPedido(char usuario[255]);

void cancelarPedido(char usuario[255]);

#endif