#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

int tabuleiro[3][3];	        //define o tamanho da matriz do tabuleiro
int turno;                   //turnoo atual
int resultado;		            //resultadoado do jogo
bool gameover = false;	        //o jogo ja acabou?
int comp;		            //variavel do computador
int mainmenu = 0;		    //menu principal
char p1[10], p2[10];        //tamanho do nome dos jogadores 1 e 2
int i = 0, j = 0, k = 0;    //variaveis globais de utilidade

//inicia e limpa o tabuleiro pro inicio do jogo
void Intialize(){
	turno=1;
	for(int i=0;i<3;i++)//aqui ele ta checando os "slots" em um loop e limpando todos{
		for(int j=0;j<3;j++){
			tabuleiro[i][j]=0;
	}
	i=0;j=0;k=0;//volta as posicoes dos "ponteiros do tabuleiro" pro in�cio
}
//funcao pra desenhar o texto (peguei isso na net)
void DesenhaTexto(void *font,const char s[],float x,float y){
	unsigned int i;
	glRasterPos2f(x,y);
	for(i=0;i<strlen(s);i++){
		glutBitmapCharacter(font,s[i]);
	}
}
//funcao do teclado (comandos do jogo e digitar nomes)
void TeclaPressionada(unsigned char key,int x,int y){
	if(mainmenu == 1){
		if(k == 0 && key != 13) p1[i++] = key;
		else if(key == 13 && k == 0) k = 1;
		else if(k == 1 && key != 13) p2[j++] = key;
		else if(key == 13 && k == 1) mainmenu = 3;
	}
	else if(mainmenu == 2){
		if(key != 13) p1[k++] = key;
		else mainmenu = 3;
	}
	else{
        switch(key){
            case '2': //jogo de 2 jogadores
                mainmenu = 1;
                gameover=false;
                comp = 0;
                Intialize();
                glutPostRedisplay();

            break;
            case 'c': //jogo contra o computador
                mainmenu = 2;
                gameover=false;
                glutPostRedisplay();
                comp = 1;
                Intialize();
            break;
            case 's': //sim para jogar novamente
            if(gameover==true){
                mainmenu = 0;
                gameover=false;
                Intialize();
            }
            break;
            case 'n': //n�o para jogar novamente
            if(gameover==true){
                exit(0);
            }
            break;
            case 'f':
                exit(0);
            break;
        }
    }
}
//funcao do mouse (vlw Will)
void OnMouseClick(int button, int state, int mousex, int mousey){
	if(gameover==false && button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
		if(turno==1){
			if(tabuleiro[(mousey-50)/200][mousex/200]==0){
				tabuleiro[(mousey-50)/200][mousex/200]=1;
				if(comp == 1)
				turno = -1;
				else
				turno=2;
			}
		}
		else if(turno==2){
			if(tabuleiro[(mousey-50)/200][mousex/200]==0){
				tabuleiro[(mousey-50)/200][mousex/200]=2;
				turno=1;
			}
		}
	}
}
//desenha as linhas do tabuleiro
void DrawLines(){
	glBegin(GL_LINES);//inicia as linhas
	glColor3f(1,1,1);//define cor
    glVertex2f(250,50);//daqui
	glVertex2f(250,640);
	glVertex2f(450,640);
	glVertex2f(450,50);
    glVertex2f(50,250);
	glVertex2f(650,250);
	glVertex2f(50,450);
	glVertex2f(650,450);//ate aqui ta definindo as posicoes das linhas
    glEnd();
}
//funcao pra fazer um circulo (vlw internet)
void DrawCircle(float cx, float cy, float r, int num_segments){
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < num_segments; i++){
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle
        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component
        glVertex2f(x + cx, y + cy);//output vertex
    }
    glEnd();
}
//funcao pra desenhar o X e o O
void DrawXO(){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(tabuleiro[i][j]==1){
				glBegin(GL_LINES);
				glVertex2f(100 + j * 200 - 25, 100 + i * 200 - 25);
				glVertex2f(200 + j * 200 + 25, 200 + i * 200 + 25);
				glVertex2f(100 + j * 200 - 25, 200 + i * 200 + 25);
				glVertex2f(200 + j * 200 + 25, 100 + i * 200 - 25);
				glEnd();
			}
			else if(tabuleiro[i][j]==2){
				DrawCircle(150 + j*200 , 150 + i*200 , 60 , 50);
			}
		}
	}
}
int blocking_win(){//funcao pro computador funcionar
    int i, t;
    for( i = 0; i < 3; i++){
        t = 0;
        t = tabuleiro[i][0] + tabuleiro[i][1] + tabuleiro[i][2];
        if (t == 2){
            if (tabuleiro[i][0] == 0) tabuleiro[i][0] = 2;
                else if (tabuleiro[i][1] == 0) tabuleiro[i][1] = 2;
                else if (tabuleiro[i][2] == 0) tabuleiro[i][2] = 2;
                return 1;
        }
    }
    if((tabuleiro[0][1] + tabuleiro[1][1] + tabuleiro[2][1]) == 2){
        if (tabuleiro[0][1] == 0) tabuleiro[0][1] = 2;
        else if (tabuleiro[1][1] == 0) tabuleiro[1][1] = 2;
        else if (tabuleiro[2][1] == 0) tabuleiro[2][1] = 2;
        return(1);
    }
    else if ((tabuleiro[0][0] + tabuleiro[1][0] + tabuleiro[2][0]) == 2){
        if (tabuleiro[0][0] == 0) tabuleiro[0][0] = 2;
        else if (tabuleiro[1][0] == 0) tabuleiro[1][0] = 2;
        else if (tabuleiro[2][0] == 0) tabuleiro[2][0] = 2;
        return(1);
    }
    else if ((tabuleiro[0][2] + tabuleiro[1][2] + tabuleiro[2][2]) == 2){
        if (tabuleiro[0][2] == 0) tabuleiro[0][2] = 2;
        else if (tabuleiro[1][2] == 0) tabuleiro[1][2] = 2;
        else if (tabuleiro[2][2] == 0) tabuleiro[2][2] = 2;
        return(1);
    }
    else if ((tabuleiro[0][0] + tabuleiro[1][1] + tabuleiro[2][2]) == 2){
        if (tabuleiro[0][0] == 0) tabuleiro[0][0] = 2;
        else if (tabuleiro[1][1] == 0) tabuleiro[1][1] = 2;
        else if (tabuleiro[2][2] == 0) tabuleiro[2][2] = 2;
        return(1);
    }
    else if ((tabuleiro[0][2] + tabuleiro[1][1] + tabuleiro[2][0]) == 2){
        if (tabuleiro[0][2] == 0) tabuleiro[0][2] = 2;
        else if (tabuleiro[1][1] == 0) tabuleiro[1][1] = 2;
        else if (tabuleiro[2][0] == 0) tabuleiro[2][0] = 2;
        return(1);
    }
    if (tabuleiro[1][1] == 0){
         tabuleiro[1][1] = 2; return 1;
    }

    return(0);
}
int check_corner(void){//funcao pro computador funcionar
    if (tabuleiro[0][0]==0){
         tabuleiro[0][0]=2;
         return(1);
    }
    else if(tabuleiro[0][2]==0){
         tabuleiro[0][2]=2;
         return(1);
    }
    else if(tabuleiro[2][0]==0){
         tabuleiro[2][0]=2;
         return(1);
    }
    else if(tabuleiro[2][2]==0){
         tabuleiro[2][2]=2;
         return(1);
    }
    return(0);
}
int check_row(void){//funcao pro computador funcionar
    if(tabuleiro[0][1] == 0){
         tabuleiro[0][1]=2;
         return(1);
    }
    else if(tabuleiro[1][0] == 0){
         tabuleiro[1][0]=2;
         return(1);
    }
    else if(tabuleiro[1][2] == 0){
         tabuleiro[1][2]=2;
         return(1);
    }
    else if(tabuleiro[2][1] == 0){
         tabuleiro[2][1]=2;
         return(1);
    }

    return(0);
}
//funcao que checa se alguem ganhou
bool ChecaVencedor(){
	int i, j;
	//checagem horizontal
	for(i=0;i<3;i++){
		for(j=1;j<3;j++){
			if(tabuleiro[i][0]!=0 && tabuleiro[i][0]==tabuleiro[i][j]){
				if(j==2){
                    return true;
				}
			}else
            break;
		}
	}
	//checagem vertical
	for(i=0;i<3;i++){
		for(j=1;j<3;j++){
			if(tabuleiro[0][i]!=0 && tabuleiro[0][i]==tabuleiro[j][i]){
				if(j==2)
					return true;
			}
			else
            break;
		}
	}
	//checagem diagonal
	if((tabuleiro[0][0]!=0 && tabuleiro[0][0]==tabuleiro[1][1] && tabuleiro[0][0]==tabuleiro[2][2]) || (tabuleiro[2][0]!=0 && tabuleiro[2][0]==tabuleiro[1][1] && tabuleiro[2][0]==tabuleiro[0][2]))
		return true;
	return false;
}
//funcao que checa se rolou empate
bool ChecaEmpate(){
	int i, j;
	bool draw;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(tabuleiro[i][j]==0)
				return false;
		}
	}
	return true;
}
//funcao super incrivelmente avancada pra maquina jogar contra o usuario
//ele parece ser inteligente nas jogadas, mas acredite, ele e bem burro
int computador(){
    if(!ChecaVencedor()){
        if(turno == -1){
                if (blocking_win() == 1) turno = 1;
                else if ( check_corner() == 1) turno = 1;
                else if ( check_row() == 1) turno = 1;
                return 1;
            }
    }
    return 0;
}//ele basicamente checa os "slots" que nao foram marcados e escolhe um
void Criador(){
    glColor3f(0,1,1);
    DesenhaTexto(GLUT_BITMAP_HELVETICA_10, "Desenvolvido por: Luccas Silva Benedetti", 0, 650);
}
//funcao pra botar td na tela
void Display(){
	if(mainmenu == 0){
		glClear(GL_COLOR_BUFFER_BIT);//limpa a tela
		glClearColor(0, 0, 0, 0);//define a cor do fundo
		Criador();
		glColor3f(1, 1, 0);//define a cor das letras do t�tulo
		DesenhaTexto(GLUT_BITMAP_HELVETICA_18, "Jogo da Velha", 280, 180);
		glColor3f(1, 1, 1);//define a cor das letras da op��o 1
		DesenhaTexto(GLUT_BITMAP_HELVETICA_18, "Dois Jogadores - 2", 260, 230);
		glColor3f(1, 1, 1);//define a cor das letras da op��o 2
		DesenhaTexto(GLUT_BITMAP_HELVETICA_18, "Contra o PC - C", 270, 280);
		glColor3f(1, 1, 1);//define a cor das letras da op��o 3
		DesenhaTexto(GLUT_BITMAP_HELVETICA_18, "Encerrar programa - F", 250, 330);
		glutSwapBuffers();
		}
    if(mainmenu == 1){
		glClear(GL_COLOR_BUFFER_BIT);//limpa a tela
		glClearColor(0, 0, 0, 0);//define a cor do fundo
		Criador();
		glColor3f(1, 1, 1);//define a cor das letras do texto 1
		DesenhaTexto(GLUT_BITMAP_HELVETICA_18, "Insira o nome 1: ", 110, 230);
		glColor3f(1, 1, 1);//define a cor das do nome 1
		DesenhaTexto(GLUT_BITMAP_HELVETICA_18, p1, 310, 230);
		glColor3f(1, 1, 1);//define a cor das letras do texto 2
		DesenhaTexto(GLUT_BITMAP_HELVETICA_18, "Insira o nome 2: ", 110, 280);
		glColor3f(1, 1, 1);//define a cor das do nome 2
		DesenhaTexto(GLUT_BITMAP_HELVETICA_18, p2, 310, 280);
		glutSwapBuffers();
		}
    if(mainmenu == 2){
		glClear(GL_COLOR_BUFFER_BIT);//limpa a tela
		glClearColor(0, 0, 0, 0);//cor do fundo
		Criador();
		glColor3f(1, 1, 1);//define a cor do texto 1
		DesenhaTexto(GLUT_BITMAP_HELVETICA_18, "Insira o seu nome: ", 110, 230);
		glColor3f(1, 1, 1);//define a cor do nome digitado
		DesenhaTexto(GLUT_BITMAP_HELVETICA_18, p1, 310, 230);
		glutSwapBuffers();
		}
	if(mainmenu == 3){
        glClear(GL_COLOR_BUFFER_BIT);//limpa a tela
        glClearColor(0, 0, 0, 0);//cor do fundo
        glColor3f(1, 1, 1);//cor das letras
        glColor3f(0,1,1);
		Criador();
        if(!gameover){
            if(turno == 1){
                if(comp == 1) usleep(700000);
                DesenhaTexto(GLUT_BITMAP_HELVETICA_18, "Vez de: ", 225, 30);
                DesenhaTexto(GLUT_BITMAP_HELVETICA_18, p1, 300, 30);//desenha o nome do jogador 1
            }
            else if(turno == 2){
                DesenhaTexto(GLUT_BITMAP_HELVETICA_18, "Vez de: ", 225, 30);
                DesenhaTexto(GLUT_BITMAP_HELVETICA_18, p2, 300, 30);//desenha o nome do jogador 2
            }
            else if(turno == -1){
                DesenhaTexto(GLUT_BITMAP_HELVETICA_18, "Vez de: ", 225, 30);
                DesenhaTexto(GLUT_BITMAP_HELVETICA_18, "Computador", 300, 30);//desenha o nome do computador (pre definido)
            }
            DrawLines();
            DrawXO();
        }
        if(computador()) turno = 1;

        if(ChecaVencedor() == true){
            if(turno == 1 && comp == 1){
                usleep(800000);
                gameover = true;
                resultado = 3;
            }
            else if(turno == 2 || turno == -1){
                usleep(800000);
                gameover = true;
                resultado = 1;
            }
            else if(turno == 1){
                usleep(800000);
                gameover = true;
                resultado = 2;
            }
        }
        else if(ChecaEmpate() == true){
            usleep(800000);
            gameover = true;
            resultado = 0;
        }
        if(gameover == true){
            glColor3f(1, 1, 1);
            DesenhaTexto(GLUT_BITMAP_TIMES_ROMAN_24, "Fim de Jogo!", 250, 160);
            if(resultado == 0)
                DesenhaTexto(GLUT_BITMAP_HELVETICA_18, "Empate", 280, 235);
            else{
                DesenhaTexto(GLUT_BITMAP_HELVETICA_18, "Vencedor: ", 230, 235);
                if(resultado == 1)
                    DesenhaTexto(GLUT_BITMAP_HELVETICA_18, p1, 320, 235);
                if(resultado == 2)
                    DesenhaTexto(GLUT_BITMAP_HELVETICA_18, p2, 320, 235);
                if(resultado == 3)
                    DesenhaTexto(GLUT_BITMAP_HELVETICA_18, "Computador", 320, 235);
            }
            DesenhaTexto(GLUT_BITMAP_HELVETICA_18, "Jogar Novamente ?(s/n)", 210, 310);
        }
        glutSwapBuffers();
    }
}
//funcao do reshape
void Reshape(int x, int y){
	glViewport(0, 0, x, y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, x, y, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
}
//funcao main
int main(int argc, char **argv){
	Intialize();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowPosition(550,200);
	glutInitWindowSize(700,650);
	glutCreateWindow("Jogo da Velha do Will");
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutKeyboardFunc(TeclaPressionada);
	glutMouseFunc(OnMouseClick);
	glutIdleFunc(Display);
	glutMainLoop();
    return 0;
}
