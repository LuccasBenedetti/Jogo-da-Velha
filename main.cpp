#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <WinUser.h>

int board[3][3];	        //define o tamanho da matriz do tabuleiro
int turn;                   //turno atual
int result;		            //resultado do jogo
bool over = false;	        //o jogo já acabou?
int comp;		            //variável do computador
int mainmenu = 0;		    //menu principal
char p1[10], p2[10];        //tamanho do nome dos jogadores 1 e 2
int i = 0, j = 0, k = 0;    //variáveis globais de utilidade

//inicia e limpa o tabuleiro pro início do jogo
void Intialize(){
	turn=1;
	for(int i=0;i<3;i++)//aqui ele tá checando os "slots" em um loop e limpando todos{
		for(int j=0;j<3;j++){
			board[i][j]=0;
	}
	i=0;j=0;k=0;//volta as posições dos "ponteiros do tabuleiro" pro início
}
//função pra desenhar o texto (peguei isso na net)
void DrawString(void *font,const char s[],float x,float y){
	unsigned int i;
	glRasterPos2f(x,y);
	for(i=0;i<strlen(s);i++){
		glutBitmapCharacter(font,s[i]);
	}
}
//função do teclado (comandos do jogo e digitar nomes)
void OnKeyPress(unsigned char key,int x,int y){
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
                over=false;
                comp = 0;
                Intialize();
                glutPostRedisplay();

            break;
            case 'c': //jogo contra o computador
                mainmenu = 2;
                over=false;
                glutPostRedisplay();
                comp = 1;
                Intialize();
            break;
            case 's': //sim para jogar novamente
            if(over==true){
                mainmenu = 0;
                over=false;
                Intialize();
            }
            break;
            case 'n': //nao para jogar novamente
            if(over==true){
                exit(0);
            }
            break;
            case 'f':
                return 0;
            break;
        }
    }
}
//função do mouse (vlw Will)
void OnMouseClick(int button, int state, int mousex, int mousey){
	if(over==false && button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
		if(turn==1){
			if(board[(mousey-50)/200][mousex/200]==0){
				board[(mousey-50)/200][mousex/200]=1;
				if(comp == 1)
				turn = -1;
				else
				turn=2;
			}
		}
		else if(turn==2){
			if(board[(mousey-50)/200][mousex/200]==0){
				board[(mousey-50)/200][mousex/200]=2;
				turn=1;
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
	glVertex2f(650,450);//até aqui tá definindo as posições das linhas
    glEnd();
}
//função pra fazer um circulo (vlw internet)
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
//função pra desenhar o X e o O
void DrawXO(){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(board[i][j]==1){
				glBegin(GL_LINES);
				glVertex2f(100 + j * 200 - 25, 100 + i * 200 - 25);
				glVertex2f(200 + j * 200 + 25, 200 + i * 200 + 25);
				glVertex2f(100 + j * 200 - 25, 200 + i * 200 + 25);
				glVertex2f(200 + j * 200 + 25, 100 + i * 200 - 25);
				glEnd();
			}
			else if(board[i][j]==2){
				DrawCircle(150 + j*200 , 150 + i*200 , 60 , 50);
			}
		}
	}
}
int blocking_win(){
    int i, t;
    for( i = 0; i < 3; i++){
        t = 0;
        t = board[i][0] + board[i][1] + board[i][2];
        if (t == 2){
            if (board[i][0] == 0) board[i][0] = 2;
                else if (board[i][1] == 0) board[i][1] = 2;
                else if (board[i][2] == 0) board[i][2] = 2;
                return 1;
        }
    }
    if((board[0][1] + board[1][1] + board[2][1]) == 2){
        if (board[0][1] == 0) board[0][1] = 2;
        else if (board[1][1] == 0) board[1][1] = 2;
        else if (board[2][1] == 0) board[2][1] = 2;
        return(1);
    }
    else if ((board[0][0] + board[1][0] + board[2][0]) == 2){
        if (board[0][0] == 0) board[0][0] = 2;
        else if (board[1][0] == 0) board[1][0] = 2;
        else if (board[2][0] == 0) board[2][0] = 2;
        return(1);
    }
    else if ((board[0][2] + board[1][2] + board[2][2]) == 2){
        if (board[0][2] == 0) board[0][2] = 2;
        else if (board[1][2] == 0) board[1][2] = 2;
        else if (board[2][2] == 0) board[2][2] = 2;
        return(1);
    }
    else if ((board[0][0] + board[1][1] + board[2][2]) == 2){
        if (board[0][0] == 0) board[0][0] = 2;
        else if (board[1][1] == 0) board[1][1] = 2;
        else if (board[2][2] == 0) board[2][2] = 2;
        return(1);
    }
    else if ((board[0][2] + board[1][1] + board[2][0]) == 2){
        if (board[0][2] == 0) board[0][2] = 2;
        else if (board[1][1] == 0) board[1][1] = 2;
        else if (board[2][0] == 0) board[2][0] = 2;
        return(1);
    }
    if (board[1][1] == 0){
         board[1][1] = 2; return 1;
    }

    return(0);
}
int check_corner(void){
    if (board[0][0]==0){
         board[0][0]=2;
         return(1);
    }
    else if(board[0][2]==0){
         board[0][2]=2;
         return(1);
    }
    else if(board[2][0]==0){
         board[2][0]=2;
         return(1);
    }
    else if(board[2][2]==0){
         board[2][2]=2;
         return(1);
    }
    return(0);
}
int check_row(void){
    if(board[0][1] == 0){
         board[0][1]=2;
         return(1);
    }
    else if(board[1][0] == 0){
         board[1][0]=2;
         return(1);
    }
    else if(board[1][2] == 0){
         board[1][2]=2;
         return(1);
    }
    else if(board[2][1] == 0){
         board[2][1]=2;
         return(1);
    }

    return(0);
}
//função que checa se alguem ganhou
bool CheckWinner(){
	int i, j;
	//checagem horizontal
	for(i=0;i<3;i++){
		for(j=1;j<3;j++){
			if(board[i][0]!=0 && board[i][0]==board[i][j]){
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
			if(board[0][i]!=0 && board[0][i]==board[j][i]){
				if(j==2)
					return true;
			}
			else
            break;
		}
	}
	//checagem diagonal
	if((board[0][0]!=0 && board[0][0]==board[1][1] && board[0][0]==board[2][2]) || (board[2][0]!=0 && board[2][0]==board[1][1] && board[2][0]==board[0][2]))
		return true;
	return false;
}
//função que checa se rolou empate
bool CheckIfDraw(){
	int i, j;
	bool draw;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(board[i][j]==0)
				return false;
		}
	}
	return true;
}
//função super incrivelmente avançada pra máquina jogar contra o usuário
//ele parece ser inteligente nas jogadas, mas acredite, ele é bem burro
int computer(){
    if(!CheckWinner()){
        if(turn == -1){
                if (blocking_win() == 1) turn = 1;
                else if ( check_corner() == 1) turn = 1;
                else if ( check_row() == 1) turn = 1;
                return 1;
            }
    }
    return 0;
}//ele basicamente checa os "slots" que não foram marcados e escolhe um
void Criador(){
    glColor3f(0,1,1);
    DrawString(GLUT_BITMAP_HELVETICA_10, "Desenvolvido por: Luccas Silva Benedetti", 0, 650);
}
//função pra botar td na tela
void Display(){
	if(mainmenu == 0){
		glClear(GL_COLOR_BUFFER_BIT);//limpa a tela
		glClearColor(0, 0, 0, 0);//define a cor do fundo
		Criador();
		glColor3f(1, 1, 0);//define a cor das letras do título
		DrawString(GLUT_BITMAP_HELVETICA_18, "Jogo da Velha", 280, 180);
		glColor3f(1, 1, 1);//define a cor das letras da opção 1
		DrawString(GLUT_BITMAP_HELVETICA_18, "Dois Jogadores - 2", 260, 230);
		glColor3f(1, 1, 1);//define a cor das letras da opção 2
		DrawString(GLUT_BITMAP_HELVETICA_18, "Contra o PC - C", 270, 280);
		glColor3f(1, 1, 1);//define a cor das letras da opçào 3
		DrawString(GLUT_BITMAP_HELVETICA_18, "Encerrar programa - F", 250, 330);
		glutSwapBuffers();
		}
    if(mainmenu == 1){
		glClear(GL_COLOR_BUFFER_BIT);//limpa a tela
		glClearColor(0, 0, 0, 0);//define a cor do fundo
		Criador();
		glColor3f(1, 1, 1);//define a cor das letras do texto 1
		DrawString(GLUT_BITMAP_HELVETICA_18, "Insira o nome 1: ", 110, 230);
		glColor3f(1, 1, 1);//define a cor das do nome 1
		DrawString(GLUT_BITMAP_HELVETICA_18, p1, 310, 230);
		glColor3f(1, 1, 1);//define a cor das letras do texto 2
		DrawString(GLUT_BITMAP_HELVETICA_18, "Insira o nome 2: ", 110, 280);
		glColor3f(1, 1, 1);//define a cor das do nome 2
		DrawString(GLUT_BITMAP_HELVETICA_18, p2, 310, 280);
		glutSwapBuffers();
		}
    if(mainmenu == 2){
		glClear(GL_COLOR_BUFFER_BIT);//limpa a tela
		glClearColor(0, 0, 0, 0);//cor do fundo
		Criador();
		glColor3f(1, 1, 1);//define a cor do texto 1
		DrawString(GLUT_BITMAP_HELVETICA_18, "Insira o seu nome: ", 110, 230);
		glColor3f(1, 1, 1);//define a cor do nome digitado
		DrawString(GLUT_BITMAP_HELVETICA_18, p1, 310, 230);
		glutSwapBuffers();
		}
	if(mainmenu == 3){
        glClear(GL_COLOR_BUFFER_BIT);//limpa a tela
        glClearColor(0, 0, 0, 0);//cor do fundo
        glColor3f(1, 1, 1);//cor das letras
        glColor3f(0,1,1);
		Criador();
        if(!over){
            if(turn == 1){
                if(comp == 1) usleep(700000);
                DrawString(GLUT_BITMAP_HELVETICA_18, "Vez de: ", 225, 30);
                DrawString(GLUT_BITMAP_HELVETICA_18, p1, 300, 30);//desenha o nome do jogador 1
            }
            else if(turn == 2){
                DrawString(GLUT_BITMAP_HELVETICA_18, "Vez de: ", 225, 30);
                DrawString(GLUT_BITMAP_HELVETICA_18, p2, 300, 30);//desenha o nome do jogador 2
            }
            else if(turn == -1){
                DrawString(GLUT_BITMAP_HELVETICA_18, "Vez de: ", 225, 30);
                DrawString(GLUT_BITMAP_HELVETICA_18, "Computador", 300, 30);//desenha o nome do computador (pré definido)
            }
            DrawLines();
            DrawXO();
        }
        if(computer()) turn = 1;

        if(CheckWinner() == true){
            if(turn == 1 && comp == 1){
                usleep(800000);
                over = true;
                result = 3;
            }
            else if(turn == 2 || turn == -1){
                usleep(800000);
                over = true;
                result = 1;
            }
            else if(turn == 1){
                usleep(800000);
                over = true;
                result = 2;
            }
        }
        else if(CheckIfDraw() == true){
            usleep(800000);
            over = true;
            result = 0;
        }
        if(over == true){
            glColor3f(1, 1, 1);
            DrawString(GLUT_BITMAP_TIMES_ROMAN_24, "Fim de Jogo!", 250, 160);
            if(result == 0)
                DrawString(GLUT_BITMAP_HELVETICA_18, "Empate", 280, 235);
            else{
                DrawString(GLUT_BITMAP_HELVETICA_18, "Vencedor: ", 230, 235);
                if(result == 1)
                    DrawString(GLUT_BITMAP_HELVETICA_18, p1, 320, 235);
                if(result == 2)
                    DrawString(GLUT_BITMAP_HELVETICA_18, p2, 320, 235);
                if(result == 3)
                    DrawString(GLUT_BITMAP_HELVETICA_18, "Computador", 320, 235);
            }
            DrawString(GLUT_BITMAP_HELVETICA_18, "Quer continuar ?(s/n)", 210, 310);
        }
        glutSwapBuffers();
    }
}
//função do reshape
void Reshape(int x, int y){
	glViewport(0, 0, x, y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, x, y, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
}
//função main
int main(int argc, char **argv){
    ShowWindow(GetConsoleWindow(), SW_HIDE);
	Intialize();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowPosition(550,200);
	glutInitWindowSize(700,650);
	glutCreateWindow("Jogo da Velha do Will");
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutKeyboardFunc(OnKeyPress);
	glutMouseFunc(OnMouseClick);
	glutIdleFunc(Display);
	glutMainLoop();
    return 0;
}
