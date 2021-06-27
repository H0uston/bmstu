#include "render_manager.h"

Render_manager::Render_manager(QWidget *parent)
{
    _paintwidget = new PaintWidget(parent);
    CameraAttributes attributes
    {
        Point3D(0,0,500),                                                   // position
        -90,                                                                // yaw
        0,                                                                  // pitch
        Point3D(0,1,0),                                                     // top
        {90, 0.1, 1000, WIDGET_WIDTH / static_cast<double>(WIDGET_HEIGHT)}  // frustrum
    };
    camera = new Camera(attributes);
    _mm = new Model_manager();
    makeScene();
}

void Render_manager::makeScene()
{
    Ground ground = Ground(length, width, height);
    _mm->rotate_x(ground, -90);
    _models.push_back(ground);

    Railroad railroad = Railroad(-length, length, 0, 0);
    _mm->rotate_x(railroad, -90);
    _models.push_back(railroad);

    camera->move(Point3D(length - 5, 35, -460));
    camera->rotate(Point3D(-70, -10, 0));

}

void Render_manager::render_models()
{
    _paintwidget->start_of_drawing();
    size_t count = _models.size();
    for (size_t i = 0; i < count; i++)
    {
        render_model(_models[i]);
    }
    _paintwidget->update();
}

void Render_manager::render_trains(std::vector<Train> models)
{
    size_t count = _train.size();
    for (size_t i = 0; i < count; i++)
    {
        render_model(models[i]);
    }
    _paintwidget->update();
}

void Render_manager::render_model(Model& model)
{
    size_t pol_count = model.get_count_of_polygons();
    changes chn = {_mm->get_model_view(model), camera->get_look(), camera->get_projection(), model.get_rotation()};

    for (size_t i = 0; i < pol_count; i++)
    {
        Polygon polygon = model.get_polygons()[i];
        _paintwidget->_render_polygon(polygon, polygon.get_color(), chn);
    }
    _paintwidget->update();
}

void Render_manager::render_train(Train& model)
{
    size_t pol_count = model.get_count_of_polygons();
    changes chn = {_mm->get_model_view(model), camera->get_look(), camera->get_projection(), model.get_rotation()};
    changes for_wheels = chn;
    for (size_t i = 0; i < pol_count; i++)
    {
        Polygon polygon = model.get_polygons()[i];
        if (polygon.get_name() == "wheel_l" || polygon.get_name() == "wheel_r")
        {
            for_wheels.model_view = model.get_wheel_view(polygon.get_center());
            _paintwidget->_render_polygon(polygon, polygon.get_color(), for_wheels);
        }
        else
        {
            _paintwidget->_render_polygon(polygon, polygon.get_color(), chn);
        }
    }
    _paintwidget->update();
}

void Render_manager::set_locomotive(Model& model)
{
    Train loc(model);
    _loc = loc;
    _train.push_back(loc);
}

void Render_manager::set_carriage(Model& model)
{
    Train car(model);
    _carriage = car;
}

void Render_manager::set_tree(Model& model)
{
    Tree tree(model);
    _tree = tree;
}

Tree Render_manager::get_tree_model()
{
    return _tree;
}

std::vector<Train>& Render_manager::get_train()
{
    return _train;
}

void Render_manager::spawn_train(const int count)
{
    if (count == _train.size() - 1)
    {
        return;
    }
    else if (count > _train.size() - 1)
    {
        double loclength = 22.59716;
        double halfloclength = loclength / 2.0;
        double fulllength = 20.54962;
        double halflength = fulllength / 2.0;
        double start_pos;
        if (_train.size() == 1) // only loc is defined
            start_pos = - halfloclength - halflength + 2;
        else
            start_pos = - halflength;
        for (int i = 0; i < count; i++)
        {
            Train new_carr(_carriage);
            _mm->move(new_carr, Point3D(start_pos, 0, 0));
            _train.push_back(new_carr);
            start_pos -= fulllength;
        }
    }
    else
    {
        for (size_t i = 0; i < count; i++)
            _train.pop_back();
    }
}

void Render_manager::append_model(Model& model)
{
    _models.push_back(model);
}

std::vector<Model>& Render_manager::get_models()
{
    return _models;
}
