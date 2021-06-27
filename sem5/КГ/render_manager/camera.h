#ifndef CAMERA_H
#define CAMERA_H

#include "../model/point.h"
#include "../math/matrix.h"

struct CameraRotation
{
    double yaw;
    double pitch;
};

struct ViewFrustrum
{
    double fow;
    double near;
    double far;
    double aspect_ratio;
};

struct CameraAttributes
{
    Point3D position;
    double yaw;
    double pitch;
    Point3D top;
    ViewFrustrum frustrum;
};

struct camera_direction_movement
{
    bool forward;
    bool backward;
    bool left;
    bool right;
    bool up;
    bool down;
};

class Camera
{
public:
    Camera();
    Camera(const CameraAttributes &attributes);
    void set_position(Point3D position);
    void set_direction(Point3D direction);
    void set_up(Point3D up);
    void set_right(Point3D right);
    void set_top(Point3D top);
    void set_yaw(double yaw);
    void set_pitch(double pitch);
    void set_ViewFrustrum(ViewFrustrum frustrum);
    Point3D get_position();
    Point3D get_direction();
    Point3D get_up();
    Point3D get_right();
    Point3D get_top();
    double get_yaw();
    double get_pitch();
    ViewFrustrum get_ViewFrustrum();
    void updateCoords();

    void rotate(const Point3D& rotation);
    void move(const Point3D& parametr);
    void move_to(camera_direction_movement& cmm);
    void set_to(const Point3D& parametr);
    Matrix get_look() const;
    Matrix get_rotation() const;
    Matrix get_projection() const;

    void set_attributes(CameraAttributes attr);
    CameraAttributes get_attributes();

private:
    Point3D _position;
    Point3D _direction;
    Point3D _up;
    Point3D _right;
    Point3D _top;
    double _yaw;
    double _pitch;
    ViewFrustrum _frustrum;
    const double speed = 5;
};

#endif // CAMERA_H
