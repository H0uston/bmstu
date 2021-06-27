#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include "../model/model_manager.h"
#include "paintwidget.h"
#include "clipper.h"
#include "camera.h"
#include "../model/train.h"
#include "../model/tree.h"
#include "../model/ground.h"
#include "../model/scene.h"

class Render_manager
{
public:
    Render_manager(QWidget *parent = nullptr);
    void render_model(Model& model);
    void render_train(Train& train);
    void render_models();
    void render_trains(std::vector<Train> train);
    Camera* camera;

    void set_locomotive(Model& model);
    void set_carriage(Model& model);
    void set_tree(Model& model);
    Tree get_tree_model();

    std::vector<Train>& get_train();
    void spawn_train(const int count);

    void append_model(Model& model);
    std::vector<Model>& get_models();

    double length = 50, width = 75, height = 0;
private:
    void makeScene();
    PaintWidget* _paintwidget;
    void _draw_triangle(Triangle& triangle);
    std::vector<Triangle> _triangulation(Triangle& triangle);

    std::vector<Train> _train;

    Train _loc;
    Train _carriage;
    Model _tree;

    Model_manager* _mm;

    std::vector<Model> _models;
};

#endif // RENDER_MANAGER_H
