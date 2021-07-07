import sources.config as config
import math
import re


# Check entered data
def check_float(x: str) -> bool:
    return True if re.fullmatch(r'^-?\d+\.\d+|-?\d+$', x.strip(" ")) else False


# Form points for default image
def form_default_points() -> list:
    first_point = config.STARTPOINT
    second_point = [config.LENGTH + config.STARTPOINT[0], -config.DIAGLINE + config.STARTPOINT[1]]
    third_point = [config.LENGTH + config.STARTPOINT[0], config.DIAGLINE + config.STARTPOINT[1]]
    ellipse_points = form_ellipse()
    polygon = [first_point, second_point]
    for i in range(len(ellipse_points)):
        polygon.append(ellipse_points[i])
    # Making line
    polygon.append([config.LENGTH + config.STARTPOINT[0], config.DIAGLINE + config.STARTPOINT[1]])
    polygon.append([config.LENGTH + config.STARTPOINT[0], -config.DIAGLINE + config.STARTPOINT[1]])
    polygon.append(third_point)
    return polygon


# Form points of ellipse
def form_ellipse(dx=config.LENGTH + config.STARTPOINT[0],
                 dy=config.STARTPOINT[1],
                 ell_width=config.ELLIPSEWIDTH,
                 ell_height=config.DIAGLINE,
                 angle=config.ANGLE) -> list:
    start_angle = 0 - angle
    end_angle = math.pi - angle
    a = ell_width
    b = ell_height
    coords = []
    while start_angle <= end_angle + 0.01:
        x = a * math.cos(start_angle) + dx
        y = b * math.sin(start_angle) + dy
        coords.append([x, y])
        start_angle += 0.05
        start_angle = round(start_angle, 2)
    coords[len(coords) - 1][0] = round(coords[len(coords) - 1][0])
    coords[len(coords) - 1][1] = round(coords[len(coords) - 1][1])
    return coords
