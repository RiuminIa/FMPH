float radius=0;
float startAngelf0=0;
float angelf0=0;
float angelf1=0;
float speed0v0=0;
float speedv0=0;
float speed0v1=0;
float speedv1=0;
float nitro0=0;
float nitro1=0;
float posunX=0;
float posunY=0;
float startAngelNitro0=0;
float startAngelNitro1=0;
float angelNitro0=0;
float angelnitro1=0;
float icaskrok=0;
float actualTime=0;


void changecoordinates(){
    actualTime+=icaskrok/1000;
    
    startAngelNitro0=speed0v0/radius;
    angelNitro0=startAngelNitro0+nitro0*actualTime;
    angelf0=startAngelNitro0*actualTime+(1/2)*nitro0*pow(actualTime,2);
    speedv0=angelNitro0*radius;
    
    startAngelNitro1=speed0v1/radius;
    angelnitro1=startAngelNitro1+nitro1*actualTime;
    angelf1=startAngelf0+startAngelNitro1*actualTime+(1/2)*nitro1*pow(actualTime,2);

    speedv1=angelnitro1*radius;

}
void refresh(const int ihod){
    changecoordinates();    
    glutPostRedisplay();  // Tymto podavame ziadost o prekreslenie sceny.
    glutTimerFunc(tick, refresh,ihod+1);
}

void resizeWindow(int width, int heigth){
    //resize Window
    printf(" obsluhaResize(): sirka = %d px,  vyska = %d px\n",width,heigth);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (width == 0) width++;
    const float pomstr = ((float)heigth)/width;
    gluOrtho2D(-0.5*Lmax, 0.5*Lmax, -0.5*Lmax*pomstr, 0.5*Lmax*pomstr);
}

void drawSquare(float r, float phi){
    glLoadIdentity();
    //glRotatef(phi,0,0,-1);
    glRotatef(0,0,0,0);
    glTranslatef(r,0,0);

    glBegin(GL_POLYGON);

    glVertex2f(-1 , -1 );
    glVertex2f(1 , -1 );
    glVertex2f(1 , 1 );
    glVertex2f(-1 , 1);
    glEnd();
}

void drawVector(float phi){
    glLoadIdentity();
    glRotatef(phi,0,0,-1); //implametn phi
    glTranslatef(r,0,0);
}

void drawCircle(float r, int num_segments){
    glLoadIdentity();
    glColor3f(1, 1, 1);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < num_segments; i++)   {
        float theta = 2.0 * 3.1415926 * i / num_segments;//get the current angle
        float x = r * cos(theta);//calculate the x component
        float y = r * sin(theta);//calculate the y component
        glVertex2f(x, y);//output vertex
    }
    glEnd();
}

void drawCenter(){
    drawCircle(0.1,100);
}

void draw(){
    //main drawing function
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    drawCircle(r,100);
    drawCenter();
    drawSquare(r,10);

    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    sscanf(argv[1],"%f", &radius );
    sscanf(argv[2],"%f", &startAngelf0 );
    sscanf(argv[3],"%f", &speed0v0 );
    sscanf(argv[4],"%f", &speed0v1 );
    sscanf(argv[5],"%f", &nitro0 );
    sscanf(argv[6],"%f", &nitro1 );

    printf("t     x(y)   y(t)   z(t)   vz(t)\n");
    printf("0.00  0.00  0.00   %.2f  %.2f\n",posunZ0,speedZ0);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(640, 640);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("OpenGL: Square");
	glutDisplayFunc(draw);
	glClearColor(0.2, 0.2, 0.2, 0.3);
	glutReshapeFunc(resizeWindow);
	glutTimerFunc(icaskrok, refresh, 0);
	glutMainLoop();
	return 0;
}