#include <iostream>
#include <GL/glut.h>
#include <math.h>

GLfloat obs_fov, fAspect;
GLfloat obs_rotX, obs_rotY, obs_rotZ, rotX_ini, rotY_ini, rotZ_ini;
GLfloat obs_posX, obs_posY, obs_posZ, obsX_ini, obsY_ini, obsZ_ini;
int x_ini,y_ini,bot;

GLfloat obs_rotA;


float alpha = 0;
float beta = 0;
float delta = 1;

#define MESH 100

void drawSphere(int x, int y, int z, int radius) {
    glPushMatrix();
    glTranslated(x, y, z);

    glColor3f(1.0f, 1.0f, 1.0f);
    glutSolidSphere(radius, MESH, MESH);

    glPopMatrix();
}

void drawSphere2(int x, int y, int z, int radius) {
    glPushMatrix();
    glTranslated(x, y, z);

    glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
    glutSolidSphere(radius, MESH, MESH);

    glPopMatrix();
}

#define R 300
#define STEP 0.01

float angle = 0;
float angle2 = 0.2;

// Funcao callback de redesenho da janela de visualizacao
void draw(void) {
    // Limpa a janela de visualizacao com a cor de fundo definida previamente
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    std::cout << "draw!\n";

    drawSphere2(0, 0, 0, 70);

    drawSphere(R*cos(angle), R*sin(angle), 0, 30);
    angle += STEP;

    drawSphere(2*R*cos(angle2), 2*R*sin(angle2), 0, 30);
    angle2 += STEP;

    // Light 0
    GLfloat pos0[] = {0.0, 0.0, 0.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, pos0);

//    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 2.0);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.003);
//    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0001);



    glEnable(GL_LIGHT0);



    // Executa os comandos OpenGL
    glutSwapBuffers();
    glutPostRedisplay();
}

// Funcao usada para especificar a posicao do observador virtual
void positionateObservator(void) {
    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);

    // Inicializa sistema de coordenadas do modelo
    glLoadIdentity();

    // Posiciona e orienta o observador
    glTranslatef(-obs_posX,-obs_posY,-obs_posZ);
    glRotatef(obs_rotX,1,0,0);
    glRotatef(obs_rotY,0,1,0);
    glRotatef(obs_rotZ,0,0,1);
}

// Funcao usada para especificar o volume de visualizacao
void checkVisualizationParams(void) {
    // Especifica sistema de coordenadas de projecao
    glMatrixMode(GL_PROJECTION);

    // Inicializa sistema de coordenadas de projecao
    glLoadIdentity();

    // Especifica a projecao perspectiva (angulo, aspecto, zMin, zMax)
    gluPerspective(45, fAspect, 0.1, 2000);

    positionateObservator();
}

// Funcao callback chamada para gerenciar eventos de teclas normais (ESC)
void keyboardHandler (unsigned char tecla, int x, int y) {
    if(tecla==27) // ESC
        exit(0);

    if (tecla == 'p') {
        glEnable(GL_DEPTH_TEST);
        glutPostRedisplay();
    }

    if (tecla == 'P') {
        glDisable(GL_DEPTH_TEST);
        glutPostRedisplay();
    }
}

// Funcao callback para tratar eventos de teclas especiais
void specialKeysHandler(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_HOME: {
            if(obs_fov>=10)
                obs_fov -= 5;
        } break;
        case GLUT_KEY_END: {
            if(obs_fov<=150)
                obs_fov +=5;
        } break;
    }
    checkVisualizationParams();
    glutPostRedisplay();
}

// Funcao callback para eventos de botoes do mouse
void mouseHandler(int button, int state, int x, int y) {
    if(state==GLUT_DOWN) {
        // Salva os par‚metros atuais
        x_ini = x;
        y_ini = y;
        obsX_ini = obs_posX;
        obsY_ini = obs_posY;
        obsZ_ini = obs_posZ;
        rotX_ini = obs_rotX;
        rotY_ini = obs_rotY;
        rotZ_ini = obs_rotZ;
        bot = button;

    } else {
        bot = -1;
    }
}

// Funcao callback para eventos de movimento do mouse
#define SENS_ROT	5.0
#define SENS_OBS	10.0
#define SENS_TRANSL	10.0
void motionHandler(int x, int y) {

    if(bot==GLUT_LEFT_BUTTON) { // Botão esquerdo
        // Calcula diferencas
        int deltax = x_ini - x;
        int deltay = y_ini - y;
        // E modifica ‚ngulos
        obs_rotZ = rotZ_ini - deltax/SENS_ROT;

    } else if(bot==GLUT_RIGHT_BUTTON) { // Botao direito
        // Calcula diferenca
        int deltaz = y_ini - y;
        // E modifica distancia do observador
        obs_posZ = obsZ_ini + deltaz/SENS_OBS;

    } else if(bot==GLUT_MIDDLE_BUTTON) { // Botao do meio
        // Calcula diferencas
        int deltax = x_ini - x;
        int deltay = y_ini - y;
        // E modifica posicoes
        obs_posX = obsX_ini + deltax/SENS_TRANSL;
        obs_posY = obsY_ini - deltay/SENS_TRANSL;
    }

    positionateObservator();
    glutPostRedisplay();
}

void reshapeHandler(GLsizei width, GLsizei height) {
    // Para previnir uma divisao por zero
    if(height == 0)
        height = 1;

    // Especifica as dimensoes da viewport
    glViewport(0, 0, width, height);

    // Calcula a correcao de aspecto
    fAspect = (GLfloat)width/(GLfloat)height;
    checkVisualizationParams();
}

void initializeDraw(void) {

    // Background color
    glClearColor(0.1, 0.1, 0.1, 0.0);
    glEnable(GL_DEPTH_TEST);

    // Models
    glShadeModel(GL_SMOOTH);

    // Lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

    GLfloat mat_shininess[] = {50.0};
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);


    // Inicializa a variavel que especifica o angulo da projecao perspectiva
    obs_fov = 45;

    // Inicializa as variaveis usadas para alterar a posicao do observador virtual
    obs_rotA = 0;

    obs_rotX = -45;
    obs_rotY = 0;
    obs_rotZ = 45;
    obs_posX = 0;
    obs_posY = 0;
    obs_posZ = 1000;
}

int main(int argc, char *argv[]) {

    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA);

    // Create window
    int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);
    int windowWidth = screenWidth/1.3;
    int windowHeight = screenHeight/1.3;
    int windowPosX = (screenWidth - windowWidth)/2;
    int windowPosY = (screenHeight - windowHeight)/2;

    glutInitWindowPosition(windowPosX, windowPosY);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Solar System");

    // Handler functions
    glutDisplayFunc(draw);
    glutReshapeFunc(reshapeHandler);
//    glutKeyboardFunc(keyboardHandler);
//    glutSpecialFunc(specialKeysHandler);
    glutMouseFunc(mouseHandler);
    glutMotionFunc(motionHandler);

    // Intialize
    initializeDraw();

    // Inicia o processamento e aguarda interacoes do usuario
    glutMainLoop();

    return 0;
}
