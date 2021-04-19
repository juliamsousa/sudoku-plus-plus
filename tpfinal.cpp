#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <fstream>

#define tamanho 9
#define total 81

using namespace std;

//struct para armazenar as coordenadas das posicoes ja inicializadas durante o jogo
typedef struct posicoes 
{
	int linha;
	int coluna;
} Tposicoes;

//struct para armazenar as coordenadas e o numero que o usuario deseja inserir na matriz
typedef struct inserir
{
	int linha;
	int coluna;
	int numero;
} Tinserir;

//funcao responsavel por alocar na memoria a matriz que contem os dados do jogo
int** alocaMatriz (int l, int c);

//funcao responsavel por desalocar na memoria a matriz que contem os dados do jogo
void desalocaMatriz (int l, int c, int **matriz);

//funcao responsavel por solicitar ao usuario o arquivo que contem os valores iniciais do jogo e inseri-los na matriz
void inicializaMatriz (int **matriz);

//funcao responsavel por imprimir na tela a matriz do jogo apos ser inicializada e a cada alteracao feita pelo usuario
void imprimeMatriz (int **matriz);

//funcao responsavel por armazenar as posicoes que ja possuem valores iniciais, que nao podem ser alterados pelo usuario
void varredura (int **matriz, Tposicoes *vetor, int *v); 

//funcao responsavel por receber um comando do usuario e, caso seja um comando valido, armazena-lo
void entrada (
	char *comandos, 
	Tposicoes *inicial, 
	Tinserir *inserir, 
	int **matriz, 
	int *c, 
	int *cont, 
	int *cont2, 
	int *cont3, 
	int *cont4
);

//funcao responsavel por impedir o usuario de alterar um valor ja inicializado 
void verificaInicial (
	Tposicoes *inicial, 
	Tinserir *coordenadas, 
	int *varredura, 
	int *cont
);

//funcao responsavel por impedir o usuario de inserir um valor ja existente na linha desejada
void verificaLinha (Tinserir *coordenadas, int **matriz, int *cont); 

//funcao responsavel por impedir o usuario de inserir um valor ja existente na coluna desejada
void verificaColuna (Tinserir *coordenadas, int **matriz, int *cont);

//funcao responsavel por impedir o usuario de inserir um valor ja existente na regiao desejada
void verificaRegiao (Tinserir *coordenadas, int **matriz, int *cont);

//funcao responsavel por inserir o valor desejado na matriz, apos serem feitas todas as verificacoes necessarias
void inserirMatriz (
	Tinserir *coordenadas, 
	int **matriz, 
	int *cont, 
	int *cont2, 
	int *cont3, 
	int *cont4); 

//funcao responsavel por salvar o progresso do jogador em um arquivo de saida
void salvaMatriz (int **matriz);

//funcao responsavel por verificar se o jogador inseriu a resolucao correta e , caso sim, finalizar o jogo
void venceJogo (
	int **matriz, 
	int *cont, 
	int *cont2, 
	int *cont3, 
	int *cont4, 
	int *verificas
);

//inicio da funcao main
int main ()
{
	//ponteiro para a matriz que armazena os dados do jogo
	int **sudoku;

	//ponteiro para o vetor que armazena os valores ja inicializados pelo jogo
	Tposicoes *a = NULL;
	a = new Tposicoes [total];

	//ponteiro para a struct que armazena a linha, coluna e numero digitados pelo ususario
	Tinserir comando;
	Tinserir *coord = &comando;

	//ponteiro para o vetor que recebe os comandos digitados pelo usuario
	char vetor [10];
	char *v = vetor;

	//inteiros que armazenam o total de linhas e colunas da matriz do jogo
	int l=tamanho, c=tamanho;

	//ponteiro para o contador que verifica se o suario deseja alterar um numero ja inicializado
	int tvarredura = 0;
	int *tv = &tvarredura; 

	//ponteiro para os contadores que  verificam se o usuario deseja inserir um numero ja existente em determinada linha, coluna, ou regiao
	int vlinha=0, vcoluna=0, vregiao=0, vinicial=0;
	int *vl = &vlinha;
	int *vc = &vcoluna;
	int *vr = &vregiao;
	int *vi = &vinicial;

    //ponteiro para inteiro que recebe valor 1 caso o usuario resolva o jogo corretamente
    int sucesso=0;
    int *s = &sucesso;

	//chamada da funcao alocaMatriz
	sudoku = alocaMatriz (l, c);

	//chamada da funcao inicializaMatriz
	inicializaMatriz (sudoku);

	//chamada da funcao imprimeMatriz
	imprimeMatriz (sudoku);

	//chamada da funcao varredura
	varredura (sudoku, a, tv);

	//chamada da funcao entrada
	entrada (v, a, coord, sudoku, tv, vi, vl, vc, vr);

	//estrutura de repeticao que se interrompe caso o usuario digite o comando sair ou resolva o jogo corretamente
	while (strcmp (vetor, "sair") && sucesso==0)
	{
		//chamada da fucnao imprimeMatriz
		imprimeMatriz (sudoku);
		//chamda da funca venceJogo
		venceJogo (sudoku, vi, vl, vc, vr, s);
		//caso o jogador nao obtenha sucesso a funcao entrada e chamada novamente
		if (sucesso==0)
			entrada (v, a, coord, sudoku, tv, vi, vl, vc, vr);	
	}

	//ao fim da estrutura de repeticao e chamada a funcao desalocaMatriz
	desalocaMatriz (l, c, sudoku);

	//comando para desalocar o ponteiro para o vetor que armazena os valores ja inicializados pelo jogo
	delete[] a;

	//retorno da funcao int main
	return 0;
}
//fim da funcao main

//implementacao da funcao alocaMatriz
int** alocaMatriz (int l, int c)
{
	//alocacao das linhas da matriz
    int **matriz = new int*[l];

    //alocacao das colunas da matriz
    for (int i=0; i<l; i++)
        matriz[i] = new int [c];

    //retorno do ponteiro de ponteiro
    return matriz;
}

//implemetacao da funcao desalocaMatriz
void desalocaMatriz (int l, int c, int **matriz)
{
	//desalocao das colunas da matriz
	for (int i=0; i<l; i++)
       delete [] matriz[i];

    //desalocacao das linhas da matriz
    delete [] matriz;
}

//implemetacao da funcao inicializaMatriz
void inicializaMatriz (int **matriz)
{
	//vetor de char para armazenar o nome do arquivo de entrada
	char nome [30];

	//arquivo de entrada a ser aberto para inicializar a matrizdo jogo
	ifstream fileentrada;

	//solicitacao do nome do arquivo de entrada
	cout<<"Indique o arquivo texto contendo o jogo: "<<endl;
	cin>>nome;

	//abertura do arquivo de entrada
	fileentrada.open (nome,ios::in);

	//transferencia dos dados do arquivo para a matriz do jogo
	 if (fileentrada.is_open())
   	{
		 for (int i =0; i<9; i++)
    		for (int j=0; j<9; j++)
    			fileentrada>>matriz[i][j];
	}

	//caso o arquivo nao possa ser aberto a funcao e chamada novamente
		else 
		{
			cout<<"Nao foi possivel abrir o arquivo de entrada."<<endl<<endl;
			inicializaMatriz (matriz);
		}

	//fechamento do arquivo de entrada
	fileentrada.close();	
}

//implementacao da funcao imprimematriz
void imprimeMatriz (int **matriz)
{
	//espaco de uma linha para melhorar a visualizacao da matriz 
	cout<<endl;

	for (int i=0; i<tamanho; i++)
	{
		for (int j=0; j<tamanho; j++)
		{	
				//testa se o valor a ser impresso e zero para ser substituido por um traco
				if (matriz [i][j] == 0)
					cout<<setw(2)<<"-";
					//imprime o numero da matriz
					else 
						cout<<setw(2)<<matriz [i] [j];

				//faz uma comparacao para pular uma linha entre regioes
				if (j==tamanho-1)
					cout<<"\n";
				//faz um comparacao para pular espacos entre regioes
				if (j==2 || j==5)
					cout<<"  ";
		}

		//faz uma comparacao para pular uma linha entre regioes	
		if (i==2 || i ==5)
			cout<<endl;
	}
	//espaco de uma linha para melhorar a visualizacao da matriz
	cout<<endl;
}

//implementacao da funcao varredura
void varredura (int **matriz, Tposicoes *vetor, int *v)
{
 	//inteiro para andar dentro do vetor
 	int k=0;

 	//estrutura de repeticao para verificar os valores ja inicializados na matriz
 	for (int i=0; i<tamanho; i++)
		for (int j=0; j<tamanho; j++)
			//caso o termo da matriz for diferente de zero suas coordenadas sao armazenadas no vetor de estruturas
			if (matriz [i][j] != 0)
			{
				vetor[k].linha = i;
				vetor[k].coluna = j;
				k++;
			}

	//o valor de k e passado para o ponteiro, indicando quantos valores sao diferentes de zero
	*v=k;
}   

//implementacao da funcao salvaMatriz
void salvaMatriz (int **matriz)
{	
	//declaracao do arquivo de saida
	ofstream salvar;

	//abertura do arquivo de saida
	salvar.open ("progressosalvo.txt", ios::out);

	//estrutura de repeticao para transferir os valores da matriz para o arquivo de saida	
	for (int i=0; i<tamanho; i++)
	{
		for (int j=0; j<tamanho; j++)
			salvar<<matriz[i][j]<<" ";
		salvar<<endl;	
	}

	//mensagem informando o sucesso do salvamento e o nome do arquivo de destino
	cout<<"Jogo foi salvo em progressosalvo.txt."<<endl;
}

//implementacao da funcao inserir
void inserirMatriz (Tinserir *coordenadas, int **matriz, int *cont, int *cont2, int *cont3, int *cont4)
{	
	//recebe como parametro contadores que apresentam valor 0 caso o usuario digite um numero valido, 
	//que nao seja repetido em nenhuma linha, coluna e regiao e que nao seja na posicao de um valor ja inicializado
	if (*cont==0 && *cont2==0 && *cont3==0 && *cont4==0)
		matriz[coordenadas->linha][coordenadas->coluna] = coordenadas->numero;
	//caso todos os contadores apresentem valor 0 o numero fornecido pelo usuario sera inserido na matriz
}

 //implementacao da funcao entrada
void entrada (char *comandos, Tposicoes *inicial, Tinserir *inserir, int **matriz, int *c, int *cont, int *cont2, int *cont3, int *cont4)
{
	//inteiro que recebera um valor digitado pelo usuario	
	int i;

	//solicitacao das coordenadas e do numero desejado ao usuario
	cout<<"Digite um comando ou uma celula a alterar "<<endl;
	cin>>comandos;

	//caso o usuario digite sair o jogo e encerrado
	if (!strcmp (comandos, "sair"))
		cout<<endl; 
		else 
		//caso o usuario digite salvar o jogo sera salvo
		if (!strcmp (comandos, "salvar"))
			salvaMatriz (matriz);
			else
			//caso o usuario nao deseje salvar ou sair
			{	
			    //os numeros recebidos sao convertidos de char para int
				i = atoi (comandos);
				//verifica se o numero digitado pelo usuario esta dentro do intervalo 9x9 da matriz
				if (i>=111 && i<=999)
				{
					//o resto da divisao sera atribuido ao campo "numero" da struct
					inserir->numero = (i%10);
					//o resto da divisao sera atribuido ao campo "coluna" da struct
					inserir->coluna = ((i/10)%10) - 1;
					//o resto da divisao sera atribuido ao campo "linha" da struct
					inserir->linha = (i/100) - 1;

					//obs.: e subtraida uma unidade pois os indices da matriz, na realidade, variam de 0 a 8 e nao de 1 a 9
					//chamada da funcao verificaInicial, que verifica se o usuario deseja alterar um valor ja inicializada
					verificaInicial (inicial, inserir, c, cont);
					//chamada da funcao verificaLinha que verifica se o usuario deseja inserir um valor ja existente na linha desejada
					verificaLinha (inserir, matriz, cont2);
					//chamada da funcao verificaColuna que verifica se o usuario deseja inserir um valor ja existente na coluna desejada
					verificaColuna (inserir, matriz, cont3);
					//chamada da funcao verificaRegiao que verifica se o usuario deseja inserir um valor ja existente na regiao desejada
					verificaRegiao (inserir, matriz, cont4);
					//chamda da funcao inserirMatriz que insere o valor desejado na matriz, 
					//caso nao esteja repetido na linha, coluna e regiao desejados e que nao seja uma celula com valor ja inicializado pelo jogo
					inserirMatriz (inserir, matriz, cont, cont2, cont3, cont4);
				}
				//caso o valor desejado nao estiver dentro do intervalo 9x9 exibe uma mensagem de erro
				else
					cout<<"Alocacao invalida, digite um valor dentro do intervalo 9x9."<<endl;
			}
} 

//implementacao da funcao verificaInicial
void verificaInicial (Tposicoes *inicial, Tinserir *coordenadas, int *varredura, int *cont)
{
	//contador que verifica se a celula desejada ja possui um valor inicializado
	int c=0;
	
	//estrutura de repeticao que faz uma comparacao entre o valor inserido pelo usuario e os valores armazenados no vetor de struct  
	for (int i=0; i<*varredura; i++)
	{
		if (coordenadas->linha == inicial[i].linha && coordenadas->coluna == inicial[i].coluna)
				c++;
	}
	//caso a celula solicitada pelo usuario apresentar um valor inicializado c apresenta valor diferente de zero
	
	//uma mensagem de erro e exibida
	if (c!=0)
		cout<<"Erro! A celula "<<coordenadas->linha+1<<","<<coordenadas->coluna+1<<" ja possui valor."<<endl;
	//o valor de c e passado para o ponteiro	
	*cont=c;	
}

//implementacao da funcao verificaLinha
void verificaLinha (Tinserir *coordenadas, int **matriz, int*cont)
{
	//contador que verifica se o valor digitado pelo usuario ja existe na linha desejada
	int c=0;

	//estrutura de repeticao que compara o valor digitado pelo usuario e os valores contidos na linha especificada
	for (int i=coordenadas->linha; i<=coordenadas->linha; i++)
		for (int j=0; j<tamanho; j++)
		{
			if (coordenadas->numero == matriz[i][j])
				c++;
		}
	//caso o valor digitado pelo usuario ja existir na linha especificada, c apresenta valor diferente de zero
	
	//uma mensagem de erro e exibida	
	if (c!=0)
		cout<<"Erro! A linha "<<coordenadas->linha+1<<" ja possui o valor "<<coordenadas->numero<<"."<<endl;
	
	//o valor de c passa para o ponteiro	
	*cont = c;
}

//implementacao da funcao verificaColuna
void verificaColuna (Tinserir *coordenadas, int **matriz, int *cont)
{
	//contador que verifica se o valor digitado pelo usuario ja existe na coluna desejada
	int c=0;

	//estrutura de repeticao que compara o valor digitado pelo usuario e os valores contidos na coluna especificada
	for (int i=0; i<tamanho; i++)
		for (int j=coordenadas->coluna; j<=coordenadas->coluna; j++)
		{
			if (coordenadas->numero == matriz[i][j])
				c++;
		}
	//caso o valor digitado pelo usuario ja existir na coluna especificada, c apresenta valor diferente de zero
	
	//uma mensagem de erro e exibida	
	if (c!=0)
		cout<<"Erro! A coluna "<<coordenadas->linha+1<<" ja possui o valor "<<coordenadas->numero<<"."<<endl;
	
	//o valor de c passa para o ponteiro	
	*cont = c;
}

//implementacao da funcao verificaRegiao
void verificaRegiao (Tinserir *coordenadas, int **matriz, int *cont)
{
	//contador que verifica se o valor desejado pelo usuario ja existe na regiao desejada
	int c=0;
	
	//verifica se a celula desejada pertence as regioes 1, 2 ou 3
	if (coordenadas->linha>=0 && coordenadas->linha<=2)
	{
		//verifica se a celula desejada pertence a regiao 1
		if (coordenadas->coluna>=0 && coordenadas->coluna<=2)
		{
			//estrutura de repeticao que verifica se o valor digitado ja existe na regiao especificada
			for (int i=0; i<=2; i++)
				for (int j=0; j<=2; j++)
					if (coordenadas->numero == matriz [i][j])
						c=1;
		}
		else
		//verifica se a celula desejada pertence a regiao 2
		if (coordenadas->coluna>=3 && coordenadas->coluna<=5)
		{
			//estrutura de repeticao que verifica se o valor digitado ja existe na regiao especificada
			for (int i=0; i<=2; i++)
				for (int j=3; j<=5; j++)
					if (coordenadas->numero == matriz [i][j])
						c=2;
		}
		else
		//verifica se a celula desejada pertence a regiao 3
		if (coordenadas->coluna>=6 && coordenadas->coluna<=8)
		{
			//estrutura de repeticao que verifica se o valor digitado ja existe na regiao especificada
			for (int i=0; i<=2; i++)
				for (int j=6; j<=8; j++)
					if (coordenadas->numero == matriz [i][j])
						c=3;
		}
	}
	else
	//verifica se a celula desejada pertence as regioes 4, 5 ou 6 
	if (coordenadas->linha>=3 && coordenadas->linha<=5)
	{
		//verifica se a celula desejada pertence a regiao 4
		if (coordenadas->coluna>=0 && coordenadas->coluna<=2)
		{
			//estrutura de repeticao que veriica se o valor digitado ja existe na regiao especificada
			for (int i=3; i<=5; i++)
				for (int j=0; j<=2; j++)
					if (coordenadas->numero == matriz [i][j])
						c=4;
		}	
		else
		//verifica se a celula desejada pertence a regiao 5
		if (coordenadas->coluna>=3 && coordenadas->coluna<=5)
		{
			//estrutura de repeticao que verifica se o valor digitado ja existe na regiao especificada 
			for (int i=3; i<=5; i++)
				for (int j=3; j<=5; j++)
					if (coordenadas->numero == matriz [i][j])
						c=5;
		}
		else
		//verifica se a celula desejada pertence a regiao 6
		if (coordenadas->coluna>=6 && coordenadas->coluna<=8)
		{
			//estrutura de repeticao que verifica se o valor digitado ja existe na regiao especificada
			for (int i=3; i<=5; i++)
				for (int j=6; j<=8; j++)
					if (coordenadas->numero == matriz [i][j])
						c=6;
		}
	}
	else
	//verifica se a celula desejada pertence as regioes 7, 8 ou 9 
	if (coordenadas->linha>=6 && coordenadas->linha<=8)
	{
		//verifica se a celula desejada pertence a regiao 7
		if (coordenadas->coluna>=0 && coordenadas->coluna<=2)
		{
			//estrutura de repeticao que verifica se o valor digitado ja existe na regiao especificada
			for (int i=6; i<=8; i++)
				for (int j=0; j<=2; j++)
					if (coordenadas->numero == matriz [i][j])
						c=7;
		}
		else
		//verifica se a celula desejada pertence a regiao 8
		if (coordenadas->coluna>=3 && coordenadas->coluna<=5)
		{
			//estrutura de repetica que verifica se o valor digitado ja existe na regiao especificada
			for (int i=6; i<=8; i++)
				for (int j=3; j<=5; j++)
					if (coordenadas->numero == matriz [i][j])
						c=8;	
		}
		else
		//verifica se a celula desejad pertence a regiao 9
		if (coordenadas->coluna>=6 && coordenadas->coluna<=8)
		{
			//estrutura de repeticao que verifica se o valor digitado ja existe na regiao specificada
			for (int i=6; i<=8; i++)
				for (int j=6; j<=8; j++)
					if (coordenadas->numero == matriz [i][j])
						c=9;
		}
	}	
	//caso c apresente valor diferente de 0, uma mensagem de erro e exibida
	if (c!=0)
		cout<<"Erro! A regiao "<<c<<" ja possui o valor "<<coordenadas->numero<<"."<<endl;
	
	//o valor de c e atribuido ao ponteiro
	*cont=c;
}

//implementacao da funcao venceJogo
void venceJogo (int **matriz, int *cont, int *cont2, int *cont3, int *cont4, int *verifica)
{
	//contador que verifica se o usuario resolveu o jogo corretamnente
	int vence=0;

	//estrutura de repeticao que verifica se existe algum valor 0 na matriz
	for (int i=0; i<tamanho; i++)
		for (int j=0; j<tamanho; j++)
		{
			if (matriz[i][j] == 0)
				vence++;
		}	

	//caso a matriz esteja totalmente preenchida e as funcoes que verificam os valores das linhas, colunas e regioes retornem valor 0
	
	//o ponteiro de inteiro recebe um e uma mensagem de finalizacao e exibida 
	if (vence==0 && *cont==0 && *cont2==0 && *cont3==0 && *cont4==0)
	{
		cout<<"Resolucao correta! Fim de jogo."<<endl;
		*verifica = 1;
	}
}
