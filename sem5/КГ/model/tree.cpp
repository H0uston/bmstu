#include "tree.h"

Tree::Tree(Model& model)
{
    std::vector<Polygon> polygons = model.get_polygons();
    size_t count = polygons.size(), pos;
    std::string str;
    for (size_t i = 0; i < count; i++)
    {
        str = polygons[i].get_name();
        if ((pos = str.find("Trunk")) != std::string::npos)
        {
            polygons[i].set_color(color_trunk);
        }
        else if ((pos = str.find("leaf")) != std::string::npos)
        {
            polygons[i].set_color(color_leaf);
        }
        else
        {
        }
        this->append_polygon(polygons[i]);
    }
    this->set_translation(model.get_translation());
    this->set_rotation(model.get_rotation());
}
