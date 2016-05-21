#include <iostream>

//void keyboardHandler (unsigned char tecla, int x, int y) {
//    if(tecla==27) // ESC
//        exit(0);

//    if (tecla == 'p') {
//        glEnable(GL_DEPTH_TEST);
//        glutPostRedisplay();
//    }

//    if (tecla == 'P') {
//        glDisable(GL_DEPTH_TEST);
//        glutPostRedisplay();
//    }
//}

//void specialKeysHandler(int key, int x, int y) {
//    switch(key) {
//        case GLUT_KEY_HOME: {
//            if(obs_fov>=10)
//                obs_fov -= 5;
//        } break;
//        case GLUT_KEY_END: {
//            if(obs_fov<=150)
//                obs_fov +=5;
//        } break;
//    }
//    checkVisualizationParams();
//    glutPostRedisplay();
//}

#include <SolarSystem/solarsystem.hh>

int main(int argc, char *argv[]) {

    SolarSystem solar;
    solar.start(argc, argv);

    return 0;
}
