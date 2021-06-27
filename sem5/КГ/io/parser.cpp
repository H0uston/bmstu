#include "parser.h"

Parser::Parser()
{

}

static bool isNumber(const std::string& str)
{
    std::istringstream ist(str);
    int number = 0;
    return (ist >> number) && (ist>>std::ws).eof();
}

static std::vector<int>& find_numbers(std::vector<int>& nums, std::string& str) {
    std::vector<std::string> vec;
    vec.push_back(str);
    const std::string& delims = "/";
    for(std::vector<std::string>::iterator iter = vec.begin(); iter != vec.end(); ++iter)
    {
        for(std::string::iterator t_iter = iter->begin(); t_iter != iter->end(); ++t_iter)
            if(delims.find(*t_iter) != std::string::npos)
                *t_iter = ' ';
            std::istringstream ist(*iter);
            while(ist >> str)
            {
                if(isNumber(str))
                {
                    QString a = str.data();
                    nums.push_back(a.toInt());
                }
            }
    }
    return nums;
}

void Parser::_open_file(std::string& filename)
{
    if (_file.is_open())
    {
        _close();
    }
    _file.open(filename);

    if (!_file)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Ошибка","Файлы моделей не найдены! Свяжитесь с разработчиком.");
        messageBox.setFixedSize(500,200);
        exit(1);
    }
}

Model& Parser::load_model(std::string& filename)
{
    _open_file(filename);
    _read_file();

    return _model;
}

Model& Parser::load_model(QString& qfilename)
{
    _model = Model();
    std::string filename = qfilename.toStdString();
    _open_file(filename);
    _read_file();

    return _model;
}
/*
 * Some conventions:
 * parser only support 3DSMAX obj files with polygons broken into triangles.
 * Groups are also not supported.
 * Strings must be shorter than 256 symbols.
 * If you file has bad format, you'll receive a notification.
 * Polygon "is ready" when polygon has name and parser meet string with vertexes.
*/
void Parser::_read_file()
{
    std::string type;
    std::string name;
    char buffer[256];
    double x,y,z;
    Polygon tmp_polygon;
    std::vector<Point3D> points;
    std::vector<Point3D> normals;
    while (!_file.eof())
    {
        _file >> type;
        if (type == " " || type == "\n")  // For empty strings
        {
            _file.getline(buffer, 256, '\n');
        }
        else if (type == "#") // For comment strings
        {
            _file.getline(buffer, 256, '\n');
        }
        else if (type == "v") // For vertexes
        {
            if (tmp_polygon.is_ready())
            {
                tmp_polygon.set_color(default_color);
                _model.append_polygon(tmp_polygon);
                tmp_polygon = Polygon();
                points.clear();
                normals.clear();
            }
            _file >> x >> y >> z;
            Point3D point(x, y, z);
            points.push_back(point);
        }
        else if (type == "o") // For name of object
        {
            _file >> name;
            tmp_polygon.set_name(name);
        }
        else if (type == "vn") // For normal vector
        {
            _file >> x >> y >> z;
            Point3D point(x, y, z);
            normals.push_back(point);
        }
        else if (type == "f") // For vertex normal indeces
        {
            _file.getline(buffer, 256, '\n');
            std::string str = buffer;
            std::vector<int> nums;
            find_numbers(nums, str);
            Triangle triangle(points[points.size() + nums[0]], points[points.size() + nums[2]], points[points.size() + nums[4]]);
            Point3D n0 = normals[normals.size() + nums[1]], n1 = normals[normals.size() + nums[3]], n2 = normals[normals.size() + nums[5]];
            double avg_x = (n0.get_x() + n1.get_x() + n2.get_x()) / 3;
            double avg_y = (n0.get_y() + n1.get_y() + n2.get_y()) / 3;
            double avg_z = (n0.get_z() + n1.get_z() + n2.get_z()) / 3;
            Point3D avg_p(avg_x, avg_y, avg_z);
            triangle.set_normal_vector(avg_p);
            tmp_polygon.append_triangle(triangle);
        }
        else if (type == "g") // For groups (not supported)
        {
            _file >> name;
        }
        else
        {
            _file.getline(buffer, 256, '\n');
        }
    }
    tmp_polygon.set_color(default_color);
    _model.append_polygon(tmp_polygon);
}

void Parser::_close()
{
    if (_file.is_open())
    {
        _file.close();
    }
}

Parser::~Parser()
{
    _close();
}
