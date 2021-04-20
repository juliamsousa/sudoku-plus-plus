# Sudoku 🎴

O Sudoku é um jogo de quebra-cabeças criado por Howard Garns. O jogo consiste de uma matriz 9x9
separada em 9 sub-matrizes de tamanho 3x3, chamadas regiões. O objetivo é posicionar números de
1 a 9 de forma que cada coluna, linha e região tenham apenas um número de cada um dos 1
a 9. Para mais detalhes sobre o problema, consultar https://pt.wikipedia.org/wiki/Sudoku.
No jogo Sudoku, alguns números são posicionados inicialmente na matriz, e é dever do jogador completar
os espaços em branco. A Figura 1 apresenta um exemplo do estado inicial de um jogo de Sudoku
e o mesmo resolvido.

![image](https://user-images.githubusercontent.com/39354498/115167807-2e26e300-a08f-11eb-8731-da39dc3958a6.png)


## O Trabalho Prático 🔨
Você deve implementar um programa que lê uma matriz inicial de Sudoku e permita ao usuário
resolvê-lo. Seu programa deve ser executado seguindo este fluxo:


1. O programa deve solicitar o nome do arquivo texto contendo o estado inicial. O programa deve
imprimir a matriz logo em seguida.


2. O usuário deve digitar um comando (ver abaixo) ou um número de três digitos, indicando a
linha, coluna e o número a inserir. Exemplo: 117 insere o número “7” na célula (1,1), que
corresponde à primeira linha e primeira coluna. O programa deve imprimir a matriz logo após
a alteração. Nota: o usuário não pode alterar células que já tem valores.


A qualquer momento o usuário pode digitar um dos seguintes comandos:
salvar : para sobrescrever o arquivo contendo o estado inicial com o estado atual do jogo.
sair : para encerrar o programa (sem salvar as alterações).
Importante: seu programa deve proibir que o usuário faça alocações inválidas. O usuário deve ser
alertado com uma mensagem de erro caso digite um valor inválido ou faça uma alocação que infrinja
as regras do jogo.

Exemplo de uso do programa (os dados digitados pelo usuário estão destacados em azul):


![image](https://user-images.githubusercontent.com/39354498/115167927-a55c7700-a08f-11eb-8d54-acfcc9bea299.png)
![image](https://user-images.githubusercontent.com/39354498/115167946-b311fc80-a08f-11eb-86b3-293a4ea4e869.png)


## Arquivo de entrada 📑

O arquivo de entrada que será lido pelo usuário contém 81 números inteiros dispostos em 9 linhas,
cada um indicando o valor de uma célula da matriz do Sudoku. As células que não estão preenchidas
tem valor ‘0’. No exemplo da página anterior, o arquivo final terá a configuração a seguir:

![image](https://user-images.githubusercontent.com/39354498/115167985-d472e880-a08f-11eb-9697-d293c034fc25.png)

## Executando o Programa 👾 

Se estivar no Ubuntu, Debian:

![apt_get_code](https://user-images.githubusercontent.com/39354498/115168411-2a945b80-a091-11eb-97b0-3ee68c772dae.png)


Se estiver no Fedora, CentOS:


![yum_install_code](https://user-images.githubusercontent.com/39354498/115168418-33852d00-a091-11eb-963b-ef34675154af.png)

Se estiver no Windows é necessário ter suporte para C e C++ instalado em sua máquina. Seguindo esse tutorial é possível completar esse passo: https://terminaldeinformacao.com/2015/10/08/como-instalar-e-configurar-o-gcc-no-windows-mingw/


### Compilando

A linha de comando que compila é:

![run_ubuntu](https://user-images.githubusercontent.com/39354498/115168429-3f70ef00-a091-11eb-923e-e43d0ee26192.png)


### Executando

A linha de comando que executa em Ubuntu, Linux, Debian, e outros:

![run_exe](https://user-images.githubusercontent.com/39354498/115168438-47309380-a091-11eb-863f-b51dc5b6d5e7.png)


A linha de comando que executa em Windows:

![run_windows](https://user-images.githubusercontent.com/39354498/115170580-5a466200-a097-11eb-8a0a-b98b39618574.png)



