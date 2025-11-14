#ifndef FEIFOOD_H
#define FEIFOOD_H

void cadastrarUsuario(char usuario[255]);

void loginAdm(char usuario[255]);

int menuAdm(char usuario[255]);

void fazerLogin(char usuario[255]);

void buscarComida(char usuario[255]);

void listarInformacoes(char usuario[255]);

void avaliarPedido(char usuario[255]);

int menuInicial(char usuario[255]);

void menuPedido(char usuario[255]);

void fazerPedido(char usuario[255]);

void modificarPedido(char usuario[255]);

void cancelarPedido(char usuario[255]);

void visualizarUsuario();

void menuEditarAlimentos();

void menuEstatistica();

void cadastrarAlimento();

void excluirAlimento();

void top5BemAvaliados();

void top5MalAvaliados();

void cadastrarEstabelecimento();

#endif