
#include <gl/gl.h>
#include <math.h>
#include <windows.h>

#include "camera.h"

struct SCamera camera = {0,0,1.7, 0,0};

void CameraApply(){
    glRotatef(-camera.Xrot, 1,0,0);
    glRotatef(camera.Zrot, 0,0,1);
    glTranslatef(-camera.x, -camera.y, -camera.z);
}

void CameraRotation(float xAngel, float zAngel){
    camera.Zrot += zAngel;
    if(camera.Zrot < 0)
        camera.Zrot += 360;
    if(camera.Zrot > 360)
        camera.Zrot -= 360;

    camera.Xrot -= xAngel;
    if(camera.Xrot > 180)
        camera.Xrot = 180;
    if(camera.Xrot < 0)
        camera.Xrot = 0;

}

void CameraFollowToCurcor(float xCenter, float yCenter, float speed){
    POINT cursor;
    POINT base = {xCenter,yCenter};
    GetCursorPos(&cursor);
    CameraRotation(-(base.y - cursor.y) * speed, -(base.x - cursor.x) * speed);
    SetCursorPos(base.x, base.y);
}

void CameraHight(int UpDown, float speed){
    camera.z += (float)UpDown * speed;
}
void CameraMoveDiraction(int forwardMove, int rightMove, float speed){
    float angel = camera.Zrot / 180 * M_PI;
    /*
    forwardMove движимся вперед или назад куда смотрим
    rightMove движимся вправо или влево от направления куда смотрим
    */
    if(forwardMove > 0)
        angel += rightMove > 0 ? M_PI_4 : (rightMove < 0 ? -M_PI_4 : 0);
    if(forwardMove < 0){
        angel += M_PI + (rightMove > 0 ? -M_PI_4 : (rightMove < 0 ? M_PI_4 : 0));
    }
    if(forwardMove == 0){
        angel += rightMove > 0 ? M_PI_2 : -M_PI_2;
        if (rightMove == 0)
            speed = 0;
    }
    if(speed != 0){
        camera.x += sin(angel) * speed;
        camera.y += cos(angel) * speed;
    }

}
