#include "camera.h"

Camera::Camera()
{

}

Camera::Camera(const CameraAttributes& attributes)
{
    _position = attributes.position;
    _top = attributes.top;
    _yaw = attributes.yaw;
    _pitch = attributes.pitch;
    _frustrum = attributes.frustrum;
    updateCoords();
}

void Camera::set_position(Point3D position)
{
    _position = position;
}

void Camera::set_direction(Point3D direction)
{
    _direction = direction;
}

void Camera::set_up(Point3D up)
{
    _up = up;
}

void Camera::set_right(Point3D right)
{
    _right = right;
}

void Camera::set_top(Point3D top)
{
    _top = top;
}

void Camera::set_yaw(double yaw)
{
    _yaw = yaw;
}

void Camera::set_pitch(double pitch)
{
    _pitch = pitch;
}
void Camera::set_ViewFrustrum(ViewFrustrum frustrum)
{
    _frustrum = frustrum;
}

Point3D Camera::get_position()
{
    return _position;
}

Point3D Camera::get_direction()
{
    return _direction;
}

Point3D Camera::get_up()
{
    return _up;
}

Point3D Camera::get_right()
{
    return _right;
}

Point3D Camera::get_top()
{
    return _top;
}

double Camera::get_yaw()
{
    return _yaw;
}

double Camera::get_pitch()
{
    return _pitch;
}

ViewFrustrum Camera::get_ViewFrustrum()
{
    return _frustrum;
}

void Camera::updateCoords()
{
    double yaw = _yaw * (M_PI / 180.0);
    double pitch = _pitch * (M_PI / 180.0);

    _direction.set_x(cos(yaw) * cos(pitch));
    _direction.set_y(sin(pitch));
    _direction.set_z(sin(yaw) * cos(pitch));
    _direction.normalize();
    _right = _top % _direction;
    _right.normalize();
    _up = _direction % _right;
    _up.normalize();
}

void Camera::rotate(const Point3D& rotation)
{
    double yaw = this->get_yaw();
    double pitch = this->get_pitch();
    yaw += rotation.get_x();
    pitch += rotation.get_y();
    if (pitch > 90)
    {
        pitch = 90;
    }
    else if (pitch < -90)
    {
        pitch = -90;
    }
    if (yaw > 180)
    {
        yaw = -180;
    }
    else if (yaw < -180)
    {
        yaw = 180;
    }
    this->set_yaw(yaw);
    this->set_pitch(pitch);
    this->updateCoords();
}

void Camera::move(const Point3D& parametr)
{
    Point3D position = this->get_position();
    double x = position.get_x(), y = position.get_y(), z = position.get_z();
    x += parametr.get_x();
    y += parametr.get_y();
    z += parametr.get_z();
    position.set(x, y, z);
    this->set_position(position);
}

void Camera::move_to(camera_direction_movement& cmm)
{
    Point3D right = this->get_right();
    Point3D direct = this->get_direction();
    Point3D position = this->get_position();
    if (cmm.forward)
        position = position + direct* speed;
    if (cmm.backward)
        position = position - direct * speed;
    if (cmm.left)
        position = position + right * speed;
    if (cmm.right)
        position = position - right * speed;
    if (cmm.up)
        position = position + (direct % right) * speed;
    if (cmm.down)
        position = position - (direct % right) * speed;
    this->set_position(position);
}

void Camera::set_to(const Point3D& parametr)
{
    Point3D position(parametr);
    this->set_position(position);
}

Matrix Camera::get_look() const
{
    Matrix rotate(4, 4);
    Matrix translate(4,4);
    Point3D direction(_direction);
    Point3D up(_up);
    Point3D right(_right);
    Point3D position(_position);
    translate.makeIdentity();
    rotate[3][3] = 1;
    for (int i = 0; i < 3; i++)
    {
        rotate[i][0] = right[i];
        rotate[i][1] = up[i];
        rotate[i][2] = direction[i];
        translate[3][i] = -position[i];
    }
    return translate * rotate;
}

Matrix Camera::get_rotation() const
{
    Matrix rotate(4, 4);
    Point3D direction(_direction);
    Point3D up(_up);
    Point3D right(_right);
    rotate[3][3] = 1;
    for (int i = 0; i < 3; i++)
    {
        rotate[i][0] = right[i];
        rotate[i][1] = up[i];
        rotate[i][2] = direction[i];
    }
    return rotate;

}

Matrix Camera::get_projection() const
{
    ViewFrustrum frustrum = _frustrum;
    Matrix projection(4,4);
    projection[1][1] = 1 / tan((frustrum.fow / 2) * (M_PI / 180.0));
    projection[0][0] = projection[1][1] / frustrum.aspect_ratio;
    projection[2][2] = (frustrum.far + frustrum.near) / (frustrum.far - frustrum.near);
    projection[3][2] = -2 * frustrum.near * frustrum.far / (frustrum.far - frustrum.near);
    projection[2][3] = 1;
    return projection;
}

void Camera::set_attributes(CameraAttributes attr)
{
    _position = attr.position;
    _yaw = attr.yaw;
    _pitch = attr.pitch;
    _top = attr.top;
    _frustrum = attr.frustrum;
    this->updateCoords();
}

CameraAttributes Camera::get_attributes()
{
    CameraAttributes attr =
    {
        _position,
        _yaw,
        _pitch,
        _top,
        _frustrum
    };
    return attr;
}
