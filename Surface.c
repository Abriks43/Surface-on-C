#include <math.h>
#include <gl/gl.h>

#include "Surface.h"

float vert[] = {1,1,0,  1,-1,0, -1,-1,0, -1,1,0};

void WhiteLight(int cnt, int a, int b, int CntPetl){
    float tmp = M_PI/ cnt;
    glBegin(GL_TRIANGLE_STRIP);

        for(int k2 = 0; k2 < cnt; k2 ++){
            for(int k1 = 0; k1 < cnt; k1 ++){
            float x = a * sin(k2 * tmp / 2) * cos(k1 * tmp * CntPetl) ;
            float y = a * sin(k2 * tmp / 2) * sin(k1 * tmp * CntPetl);
            float z = a * (cos(k2 * tmp / 2) + log(tan(k2 * tmp / 4 ))) + (b * k1 * tmp * CntPetl);
            //glColor3f(0, 0.8, 0.1);
            glColor3f(1, 0.2, 0.3);
            glVertex3f(-4 + x, 4 + y, 4 + z);
            k2 ++;
            x = a * sin(k2 * tmp / 2) * cos(k1 * tmp * CntPetl);
            y = a * sin(k2 * tmp / 2) * sin(k1 * tmp * CntPetl);
            z = a * (cos(k2 * tmp / 2) + log(tan(k2 * tmp / 4))) + (b * k1 * tmp * CntPetl);
            glColor3f(0.5 + rand()%50/50, 0.2 + rand()%20/20, 0.1 + rand()%10/10);
            glVertex3f(-4 + x, 4 + y, 4 + z);
            k2 --;
            }
        }
    glEnd();
}
void ShowP(){
    glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, &vert);
        for(int k1 = -10; k1 < 10; k1++)
            for(int k2 = -10; k2 < 10; k2++){
                glPushMatrix();
                    if((k1 + k2) % 2 == 0)
                        glColor3f(0.3, 0.3, 0.5);
                    else
                        glColor3f(0.6, 0.1, 0.3);
                    glTranslatef(k1*2, k2*2, 0);
                    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
                glPopMatrix();
            }
    glDisableClientState(GL_VERTEX_ARRAY);
}
void ShowP22(){
    glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, &vert);
        for(int k1 = -10; k1 < 10; k1++)
            for(int k2 = -10; k2 < 10; k2++){
                glPushMatrix();
                    if((k1 + k2) % 2 == 0)
                        glColor3f(0, 0.1, 0.5);
                    else
                        glColor3f(0.1, 0.6, 0.7);
                    glTranslatef(k1*2, k2*2, 20);
                    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
                glPopMatrix();
            }
    glDisableClientState(GL_VERTEX_ARRAY);
}
void Egg3D(float sR, int cnt){
    float tmp = M_PI * 2/ cnt;
    glBegin(GL_TRIANGLE_STRIP);
        for(int k1 = -1; k1 < cnt; k1 ++){
            for(int k2 = -1; k2 < cnt; k2 ++){
            float x = sin(k1 * tmp) * cos(tmp * k2 / 2);
            float y = sin(k1 * tmp) * sin(tmp * k2 / 2);
            float z = cos(k1 * tmp);
            glVertex3f(x, y, z);
            x = sin((k1+1) * tmp) * cos(tmp * k2 / 2);
            y = sin((k1+1) * tmp) * sin(tmp * k2 / 2);
            z = cos((k1+1) * tmp);
            glVertex3f(x,y,z);

            }
        }
    glEnd();
}
