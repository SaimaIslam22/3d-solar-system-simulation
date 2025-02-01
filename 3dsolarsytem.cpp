#include <GL/glut.h>
#include <cmath>
// Rotation angles for each planet
float mercuryAngle = 0.0f, venusAngle = 0.0f, earthAngle = 0.0f, marsAngle = 0.0f;
float jupiterAngle = 0.0f, saturnAngle = 0.0f, uranusAngle = 0.0f, neptuneAngle = 0.0f;

void drawOrbit(float radius) {
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float angle = 2.0f * M_PI * i / 360;
        glVertex3f(radius * cosf(angle), 0.0f, radius * sinf(angle));
    }
    glEnd();
}

void drawPlanet(float orbitRadius, float planetRadius, float angle, float r, float g, float b) {
    float x = orbitRadius * cosf(angle);
    float z = orbitRadius * sinf(angle);

    glPushMatrix();
    glTranslatef(x, 0.0f, z);
    glColor3f(r, g, b);
    GLUquadric* quad = gluNewQuadric();
    gluSphere(quad, planetRadius, 32, 32);
    gluDeleteQuadric(quad);
    glPopMatrix();
}

void drawSaturnRing(float orbitRadius, float ringRadius, float ringThickness, float angle) {
    float x = orbitRadius * cosf(angle);
    float z = orbitRadius * sinf(angle);

    glPushMatrix();
    glTranslatef(x, 0.0f, z);
    glRotatef(45, 1.0f, 0.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 0.5f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float angle = 2.0f * M_PI * i / 360;
        glVertex3f(ringRadius * cosf(angle), ringThickness * sinf(angle), 0.0f);
    }
    glEnd();
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0f, 2.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    // Draw the Sun
    glColor3f(1.0f, 0.5f, 0.0f); // orange color
    GLUquadric* quad = gluNewQuadric();
    gluSphere(quad, 0.2f, 32, 32);
    gluDeleteQuadric(quad);

    // Draw orbits
    drawOrbit(0.5f); drawOrbit(0.7f); drawOrbit(1.0f);
    drawOrbit(1.3f); drawOrbit(1.7f); drawOrbit(2.1f);
    drawOrbit(2.5f); drawOrbit(3.0f);

    // Draw planets
    drawPlanet(0.5f, 0.05f, mercuryAngle, 0.5f, 0.5f, 0.5f);
    drawPlanet(0.7f, 0.07f, venusAngle, 1.0f, 0.5f, 0.0f);
    drawPlanet(1.0f, 0.08f, earthAngle, 0.0f, 0.0f, 1.0f);
    drawPlanet(1.3f, 0.06f, marsAngle, 1.0f, 0.0f, 0.0f);
    drawPlanet(1.7f, 0.12f, jupiterAngle, 0.65f, 0.16f, 0.16f);
    drawPlanet(2.1f, 0.1f, saturnAngle, 1.0f, 1.0f, 0.0f);
    drawPlanet(2.5f, 0.09f, uranusAngle, 0.0f, 1.0f, 0.0f);
    drawPlanet(3.0f, 0.08f, neptuneAngle, 0.0f, 0.0f, 1.0f);
    drawSaturnRing(2.1f, 0.15f, 0.02f, saturnAngle);

    glutSwapBuffers();
}

void update(int value) {
    mercuryAngle += 0.02f;
    venusAngle += 0.016f;
    earthAngle += 0.01f;
    marsAngle += 0.006f;
    jupiterAngle += 0.004f;
    saturnAngle += 0.003f;
    uranusAngle += 0.002f;
    neptuneAngle += 0.0016f;
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

//setup OpenGl environment to prepare the scene for rendering correctly
void init() {
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // set background color of black 
}

//intializing glut library and setting up the display settings
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("3D Solar System");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(16, update, 0);
    glutMainLoop();
    return 0;
}
