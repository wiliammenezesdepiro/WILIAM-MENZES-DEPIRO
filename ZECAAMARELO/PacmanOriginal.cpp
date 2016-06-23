#include <allegro.h>
volatile int exit_program = FALSE;
void fecha_program(){
exit_program=TRUE;
}END_OF_FUNCTION(fecha_program)

bool AtualizaTempoPersonagem(int tmilisegundos){
static double tempoPERS;
static clock_t t0pac=clock(), tfpac;
tfpac=clock();
tempoPERS=( (double)(tfpac - t0pac)) / (CLOCKS_PER_SEC/1000);
if(tempoPERS>tmilisegundos){
    tempoPERS=0;
    t0pac=clock();
    return true;
}return false;
}

bool AtualizaTempoBixoPapao(int tmilisegundos){
static double tempoPERS;
static clock_t t0pac=clock(), tfpac;
tfpac=clock();
tempoPERS=( (double)(tfpac - t0pac)) / (CLOCKS_PER_SEC/1000);
if(tempoPERS>tmilisegundos){
    tempoPERS=0;
    t0pac=clock();
    return true;
}return false;
}

typedef struct{
	int x;
	int y;
	int life;
    int vida;
    int coin;
    int morreu;
	BITMAP *sprite;
}PERSONAGEM;

PERSONAGEM personagem,inimigo,inimigo2;

int matriz[13][15]={
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{2,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
	{2,1,2,2,2,2,1,2,1,2,1,2,2,1,2},
	{2,1,2,1,1,1,1,2,1,2,3,2,1,1,2},
	{2,2,2,2,2,2,1,2,1,2,1,2,1,2,2},
	{2,1,1,1,1,1,1,2,1,2,1,1,1,2,2},
	{2,1,2,2,2,2,2,2,1,2,2,2,1,1,2},
	{2,1,2,1,1,1,1,1,1,2,1,1,1,1,2},
	{2,1,2,1,2,1,1,1,1,2,1,1,2,1,2},
	{2,1,1,1,2,1,2,2,2,2,1,1,2,1,2},
	{2,1,2,2,2,1,1,2,3,2,2,2,2,1,2},
	{2,1,1,1,2,1,3,2,1,1,1,1,1,1,2},
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
};
bool movimentaPersonagem = false;
bool movimentaBixoPapao = false;
void init();
void deinit();
void movimentoinimigo();
int menu();
void movimentoinimigo(){
if(personagem.x !=1 || personagem.y !=1){
//movimenta pra baixo
if(personagem.y<inimigo.y &&movimentaBixoPapao && matriz[inimigo.y-1][inimigo.x]!=2){
        inimigo.y--;
}else //movimenta pra cima
if( personagem.y>inimigo.y &&movimentaBixoPapao && matriz[inimigo.y+1][inimigo.x]!=2){
        inimigo.y++;
}else //movimenta pra  esquerda
if(personagem.x<inimigo.x  &&movimentaBixoPapao && matriz[inimigo.y][inimigo.x-1]!=2){
    inimigo.x--;
}else//movimenta pra direita
if(personagem.x>inimigo.x &&movimentaBixoPapao && matriz[inimigo.y][inimigo.x+1]!=2){
    inimigo.x++;
}else //movimenta pra direita
if(personagem.x>inimigo.x  &&movimentaBixoPapao && matriz[inimigo.y][inimigo.x+1]!=2){
    inimigo.x++;
}else //movimenta pra esquerda
if(personagem.x<inimigo.x &&movimentaBixoPapao && matriz[inimigo.y][inimigo.x-1]!=2){
    inimigo.x--;
}else //movimenta pra baixo
if(personagem.x!=inimigo.x  &&movimentaBixoPapao && matriz[inimigo.y-1][inimigo.x]!=2){
    inimigo.y--;
}
}
}
int op;
int main(){
personagem.vida=3;
init();
menu();

op = menu(); //variavelc que recebe uma funcao chamado menu e retorna um inteiro, 1 - jogar  2 - sair

switch(op)
{
	case 2:{ //2 - sai do jogo
		return 0;
		exit(1);
		break;
	}
}
personagem.coin=0;
BITMAP *fundo=create_bitmap(800,800);
personagem.x=1;
personagem.y=1;
inimigo.x=10;
inimigo.y=9;
personagem.sprite=load_bitmap("imagens/pacman.bmp", NULL);
BITMAP *parede=load_bitmap("imagens/parede.bmp",NULL);
BITMAP *gameover=load_bitmap("imagens/gameover.bmp",NULL);
BITMAP *coin=load_bitmap("imagens/coin.bmp",NULL);
BITMAP *win=load_bitmap("imagens/win.bmp",NULL);
inimigo.sprite=load_bitmap("imagens/inimigo.bmp", NULL);
while (!exit_program) {
if(personagem.vida>0){
clear_to_color(fundo,makecol(28,183,32));
}

if(matriz[personagem.x][personagem.y]==3){
    matriz[personagem.x][personagem.y]=0;
}
    movimentaPersonagem = AtualizaTempoPersonagem(400);
    movimentaBixoPapao = AtualizaTempoBixoPapao(400);
    if(key[KEY_ESC]){
            fecha_program();
    }
if(key[KEY_RIGHT] && movimentaPersonagem && matriz[personagem.y][personagem.x+1]!=2){
    personagem.x++;
    if(personagem.x==inimigo.x && personagem.y==inimigo.y){
        personagem.x--;
    }
}
if(key[KEY_LEFT] && movimentaPersonagem && matriz[personagem.y][personagem.x-1]!=2){
    personagem.x--;
    if(personagem.x==inimigo.x && personagem.y==inimigo.y){
        personagem.x++;
    }
}
if(key[KEY_UP] && movimentaPersonagem && matriz[personagem.y-1][personagem.x]!=2){
    personagem.y--;
    if(personagem.x==inimigo.x && personagem.y==inimigo.y){
        personagem.y++;
    }

}
if(key[KEY_DOWN] && movimentaPersonagem && matriz[personagem.y+1][personagem.x]!=2){
    personagem.y++;
    if(personagem.x==inimigo.x && personagem.y==inimigo.y){
        personagem.y--;
    }
}
if(personagem.x==inimigo.x && personagem.y==inimigo.y && personagem.vida!=0){
    personagem.vida=personagem.vida -1;
    personagem.x=1;
    personagem.y=1;
}
if(matriz[personagem.y][personagem.x]==3){
    matriz[personagem.y][personagem.x]=0;
    personagem.coin++;
}
movimentoinimigo();
if(personagem.vida>-1){
for(int i=0;i<13;i++)
for(int j=0;j<15;j++)
{
if(personagem.x == j && personagem.y == i)
{
    masked_blit(personagem.sprite, fundo,0, 0, j*50, i*45, 50, 45);
}
if(inimigo.x == j && inimigo.y == i)
{
    masked_blit(inimigo.sprite, fundo,0, 0, j*50, i*45, 50, 45);
}
if(matriz[i][j]==2){
    masked_blit(parede, fundo,0, 0, j*50, i*45, 50, 45);
}
if(matriz[i][j]==3){
    masked_blit(coin,fundo,0,0,j*50,i*45,50,45);
}

}
if(personagem.vida!=0 && personagem.coin!=3){
textprintf_ex(screen,font,650,80,makecol(0,0,255), -1, "Vida Jogador : %d",personagem.vida);
textprintf_ex(screen,font,650,60,makecol(0,0,255), -1, "inimigo.x : %d",inimigo.x);
textprintf_ex(screen,font,650,70,makecol(255,0,255), -1, "inimigo.y : %d",inimigo.y);
}
if(personagem.coin==3){
masked_blit(win, fundo, 0, 0, 0, 0, 800, 600);
while(!keypressed());
}
if(personagem.vida ==0){
        masked_blit(gameover, fundo, 0, 0, 0, 0, 800, 600);
while(!keypressed());
}
blit(fundo,screen,0,0,0,0,800,600);
}

}

}END_OF_MAIN()


int menu(){
	int i = 40;
	int escolha;


	//load nas imagens do menu
    BITMAP *menu=load_bitmap("imagens/menu.bmp", NULL);
	BITMAP *select=load_bitmap("imagens/select.bmp", NULL);
	BITMAP *fundo =create_bitmap(800,600);

	do{

		if(key[KEY_UP])
		{//move em cima da posicao jogar
			i = 40;
			escolha = 1;
		}
		if(key[KEY_DOWN])
		{//move em cima da posicao sair
			i = 100;
			escolha = 2;
		}
		//imprime o menu
		masked_blit(menu, fundo, 0, 0, 0, 0, 800, 600);
		masked_blit(select, fundo, 0, 0,20, i, 250, 100);
		blit(fundo,screen,0,0,0,0,800,600); //imprime tudo na screen
	}
while(!key[KEY_ENTER]);
	stop_midi();//para a midia do menu
return escolha;
}

void init() {
	int depth, res;
	allegro_init();
	set_window_title("Zeca amarelo");
	depth = desktop_color_depth();
    set_close_button_callback(fecha_program);
    install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,NULL);
    install_joystick(JOY_TYPE_AUTODETECT);
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
    }

	install_timer();
	install_keyboard();
	install_mouse();
	/* add other initializations here */
}

void deinit() {
	clear_keybuf();
	/* add other deinitializations here */
}
