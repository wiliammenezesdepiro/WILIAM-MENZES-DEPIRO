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
    int morreu;
	BITMAP *sprite;
}PERSONAGEM;

PERSONAGEM personagem,inimigo;

int matriz[13][15]={
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{2,1,1,1,1,1,1,2,1,1,1,1,1,1,2},
	{2,1,2,2,2,2,1,2,1,2,2,2,2,1,2},
	{2,1,2,1,1,1,1,2,1,2,1,2,1,1,2},
	{2,2,2,2,2,2,1,2,1,2,1,2,1,2,2},
	{2,1,1,1,1,1,1,2,1,2,1,1,1,2,2},
	{2,1,2,2,2,2,2,2,1,2,2,2,1,1,2},
	{2,1,2,1,1,1,1,1,1,2,1,1,1,1,2},
	{2,1,2,1,2,2,1,2,1,2,1,1,2,1,2},
	{2,1,1,1,2,1,1,2,2,2,1,1,2,1,2},
	{2,1,2,2,2,1,2,2,1,2,2,2,2,1,2},
	{2,1,1,1,2,1,2,1,1,1,1,1,1,1,2},
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
};


void init();
void deinit();
bool movimentaPersonagem = false;
bool movimentaBixoPapao = false;
int main(){
init();
BITMAP *fundo=create_bitmap(800,800);
personagem.x=1;
personagem.y=1;
inimigo.x=13;
inimigo.y=11;
personagem.sprite=load_bitmap("imagens/pacman.bmp", NULL);
BITMAP *parede=load_bitmap("imagens/parede.bmp",NULL);
inimigo.sprite=load_bitmap("imagens/inimigo.bmp", NULL);
while (!exit_program) {
    clear_to_color(fundo,makecol(28,183,32));
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
}else
if(key[KEY_LEFT] && movimentaPersonagem && matriz[personagem.y][personagem.x-1]!=2){
    personagem.x--;
    if(personagem.x==inimigo.x && personagem.y==inimigo.y){
        personagem.x++;
    }
}else
if(key[KEY_UP] && movimentaPersonagem && matriz[personagem.y-1][personagem.x]!=2){
    personagem.y--;
    if(personagem.x==inimigo.x && personagem.y==inimigo.y){
        personagem.y++;
    }
}else
if(key[KEY_DOWN] && movimentaPersonagem && matriz[personagem.y+1][personagem.x]!=2){
    personagem.y++;
    if(personagem.x==inimigo.x && personagem.y==inimigo.y){
        personagem.y--;
    }
}
if(personagem.x !=1 || personagem.y !=1){

}
if(personagem.x==inimigo.x && personagem.y==inimigo.y){
    personagem.vida=personagem.vida -1;
    personagem.x=1;
    personagem.y=1;
}

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

}
textprintf_ex(fundo,font,650,60,makecol(0,0,255), -1, "inimigo.x : %d",inimigo.x);
textprintf_ex(fundo,font,650,70,makecol(255,0,255), -1, "inimigo.y : %d",inimigo.y);
blit(fundo,screen,0,0,0,0,800,600);
}

}END_OF_MAIN()
void init() {
	int depth, res;
	allegro_init();
	set_window_title("BOMBER MAN");
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
