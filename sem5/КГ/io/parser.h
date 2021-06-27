#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <QString>
#include <QMessageBox>

#include "../config.h"
#include "../model/model.h"

class Parser
{
public:
    Parser();
    Model& load_model(std::string& filename);
    Model& load_model(QString& filename);
    ~Parser();

private:
    Model _model;
    std::ifstream _file;
    void _close();
    void _open_file(std::string& filename);
    void _read_file();
    QColor default_color = Qt::gray;
};

#endif // PARSER_H
