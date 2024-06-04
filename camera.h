#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

struct SCamera{
    float x,y,z;
    float Xrot, Zrot;
} camera;

void CameraApply();
void CameraRotation(float xAngel, float zAngel);
void CameraFollowToCurcor(float xCenter, float yCenter, float speed);
void CameraMoveDiraction(int forwardMove, int rightMove, float speed);
void CameraHight(int UpDown, float speed);

#endif // CAMERA_H_INCLUDED
