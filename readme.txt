LAIG 2013
Leonel Araújo ei11130
Sérgio Esteves ei11162

********
**Octi**
********
O OCTI é um jogo de tabuleiro de estratégia.
Cada jogador começa com 3 peças em campo nas suas casas "base".
O objetivo do jogo é conseguir ocupar uma casa "base" do adversária com as suas próprias peças.
Para movimentar uma peça é necessário a peça tenha um "prong" referente a essa direção associada à mesma, ou seja, uma peça pode andar até 8 direções diferentes desde que tenha todos os seus lados "marcados"(preenchidos com prongs). É dada ainda a opção a um jogador de adicionar uma nova peça ao jogo desde que alguma das suas casas "base" esteja vazia. O número de peças máximo é de 7 para cada jogador. Por fim, um movimento de uma peça é dependentemente das peças no tabuleiro, isto é uma peça não pode ser movida para uma casa onde já haja uma peça (quer do jogador, quer do adversário).
Assim sendo, em cada turno o jogador pode escolher uma de três acções:
1- Adicionar um "prong"
2- Mover uma peça
3- Adicionar uma peça

*************
**Aplicação**
*************
Para correr o jogo é necessário correr o executável "OCTI" (servidor da lógica) que se encontra na pasta homónima.
De seguida é necessário correr o executável gráfico que se encontra na pasta "LAIG".
Quando é iniciada a aplicação é apresentado um menu:
1- P v P, onde o jogo é feito com 2 jogadores em que a camara roda tendo em conta o turno
2- P v IA, que abre outro menu para escolher dificuldade. Após escolhida a dificuldade o jogo é iniciado no modo utilizador vs computador.
3- Menu com regras do jogo
4- Sair

****************
**Ecrã de jogo**
****************
O ecra de jogo contém o tabuleiro, um octógono à esquerda do utilizador e 4 pods auxiliares.
O octógono à esquerda do utilizador é utilizado para adicionar "prongs" (direcções) às peças em jogo. Após clicar numa das direcções do octógono é mostrado ao utilizador quais peças podem ter a direção seleccionada e, então adicionar.
Cada uma das 4 peças extra podem ser adicionados ao jogo se uma casa "base" do jogador estiver vazia. Caso assim seja, ao clicar numa dessas peças é mostrado no tabuleiro quais as casas para as quais se pode mover essa nova peça.

************
**Texturas**
************
Para alterar de ambiente (tema de texturas) é necessário premir a tecla 'T'

*********************
**Conclusão do Jogo**
*********************
Ao concluir o jogo é mostrado ao utilizador o ecrã de vitória. Aqui o utilizador pode escolher rever o filme do jogo ou voltar ao menu inicial.


****************
**NOTAS FINAIS**
****************
De referir:
	- Nenhum procedimento de lógica é feito do lado gráfico. Toda a lógica de um jogo é feita do outro lado do socket. O lado gráfico limita-se a mover peças e prongs (tanto num movimento normal, como aquando da anulação de uma jogada), a rodar o tabuleiro, efetuar highlights, alterar aparências, etc.
	- A comunicação é feita utilizando strings de curto tamanho. Não é passsado um tabuleiro integral em nenhuma comunicação.
	- Quando o utilizador escolhe o modo de P vs COM:
			- A câmara não efetua qualquer rotação, pois não achávamos que fazia sentido ver a perspectiva do Computador
			- Computador executa sempre a jogada dentro do tempo
			- Nenhum cálculo da jogada a fazer é feita do lado gráfico. Quando é necessária a geração de uma jogada o lado gráfico efetua o pedido e anima a resposta obtida.