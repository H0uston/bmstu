import sources.config as config
import gui.message as message
import math


def draw_circle(window, data_circle: list, current_algorithm: str):
    """
    Chooses method of drawing circle
    :param window: - class of window
    :param data_circle: - list with data of circle [x, y, radius]
    :param current_algorithm:
    :return: None if you'd forgotten to add new method
    """
    xc, yc, radius = data_circle
    if current_algorithm == config.BRESENHAM:
        brezenham_circle(window, xc, yc, radius)
    elif current_algorithm == config.CANONICAL:
        canon_circle(window, xc, yc, radius)
    elif current_algorithm == config.PARAMETRIC:
        param_circle(window, xc, yc, radius)
    elif current_algorithm == config.MIDDLE_POINT:
        middle_point_circle(window, xc, yc, radius)
    elif current_algorithm == config.LIBRARY:
        window.scene.addEllipse(xc - radius, yc - radius, radius * 2,
                                radius * 2, window.pen_colour)
    else:
        message.show_error(config.PROG_ERR1)
        return None


def brezenham_circle(win, cx: float, cy: float, r: float):
    """
    Draws circle using brezenham method
    :param win: - class of window
    :param cx: - x center
    :param cy: - y center
    :param r: - radius of circle
    :return: pixels on image.
    """
    x = 0   # start values
    y = r
    d = 2 - 2 * r
    while y >= 0:
        if (0 < cx + x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy + y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx + x, cy + y, win.pen_colour.rgb())

        if (0 < cx + x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy - y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx + x, cy - y, win.pen_colour.rgb())

        if (0 < cx - x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy + y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx - x, cy + y, win.pen_colour.rgb())

        if (0 < cx - x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy - y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx - x, cy - y, win.pen_colour.rgb())

        if d < 0:  # inside circle
            buf = 2 * d + 2 * y - 1
            x += 1

            if buf <= 0:
                d = d + 2 * x + 1
            else:
                y -= 1
                d = d + 2 * x - 2 * y + 2
        elif d > 0:  # outside circle
            buf = 2 * d - 2 * x - 1
            y -= 1

            if buf > 0:
                d = d - 2 * y + 1
            else:
                x += 1
                d = d + 2 * x - 2 * y + 2
        elif d == 0.0:  # on circle
            x += 1
            y -= 1
            d = d + 2 * x - 2 * y + 2
        else:  # Impossible?
            continue
    win.paint()


def canon_circle(win, cx: float, cy: float, r: float):
    """
    Draws circle using canonical equation method
    :param win: - class of window
    :param cx: - x center
    :param cy: - y center
    :param r: - radius of circle
    :return: pixels on image.
    """
    for x in range(int(r) + 1):
        y = round(math.sqrt(r ** 2 - x ** 2))

        if (0 < cx + x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy + y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx + x, cy + y, win.pen_colour.rgb())

        if (0 < cx + x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy - y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx + x, cy - y, win.pen_colour.rgb())

        if (0 < cx - x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy + y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx - x, cy + y, win.pen_colour.rgb())

        if (0 < cx - x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy - y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx - x, cy - y, win.pen_colour.rgb())

    for y in range(int(r) + 1):
        x = round(math.sqrt(r ** 2 - y ** 2))

        if (0 < cx + x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy + y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx + x, cy + y, win.pen_colour.rgb())

        if (0 < cx + x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy - y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx + x, cy - y, win.pen_colour.rgb())

        if (0 < cx - x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy + y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx - x, cy + y, win.pen_colour.rgb())

        if (0 < cx - x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy - y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx - x, cy - y, win.pen_colour.rgb())
    win.paint()


def param_circle(win, cx, cy, r):
    """
    Draws circle using parametric equation method
    :param win: - class of window
    :param cx: - x center
    :param cy: - y center
    :param r: - radius of circle
    :return: pixels on image.
    """
    t = 0
    while t < math.pi / 2:
        x = round(r * math.cos(t))
        y = round(r * math.sin(t))

        if (0 < cx + x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy + y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx + x, cy + y, win.pen_colour.rgb())

        if (0 < cx + x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy - y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx + x, cy - y, win.pen_colour.rgb())

        if (0 < cx - x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy + y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx - x, cy + y, win.pen_colour.rgb())

        if (0 < cx - x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy - y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx - x, cy - y, win.pen_colour.rgb())
        t += 1 / r
    win.paint()


def middle_point_circle(win, cx, cy, r):
    """
    Draws circle using middle point method
    :param win: - class of window
    :param cx: - x center
    :param cy: - y center
    :param r: - radius of circle
    :return: pixels on image.
    """
    x = 0  # start values
    y = r
    p = 5 / 4 - r  # (x + 1)^2 + (y - 1/2)^2 - r^2
    while True:
        if (0 < cx - x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy + y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx - x, cy + y, win.pen_colour.rgb())

        if (0 < cx + x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy - y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx + x, cy - y, win.pen_colour.rgb())

        if (0 < cx - x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy - y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx - x, cy - y, win.pen_colour.rgb())

        if (0 < cx + x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy + y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx + x, cy + y, win.pen_colour.rgb())

        if (0 < cx - y < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy + x < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx - y, cy + x, win.pen_colour.rgb())

        if (0 < cx + y < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy - x < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx + y, cy - x, win.pen_colour.rgb())

        if (0 < cx - y < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy - x < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx - y, cy - x, win.pen_colour.rgb())
        if (0 < cx + y < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy + x < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx + y, cy + x, win.pen_colour.rgb())

        x += 1

        if p < 0:  # middle point inside circle
            p += 2 * x + 1
        else:   # middle point outside circle
            p += 2 * x - 2 * y + 5
            y -= 1

        if x > y:
            break
    win.paint()


def draw_ellipse(window, data_ellipse: list, current_algorithm: str):
    """
    Chooses method of drawing ellipse
    :param window:
    :param data_ellipse: - list with data of ellipse [x, y, a, b]
    :param current_algorithm:
    :return: None if you'd forgotten to add new method
    """
    xc, yc, a, b = data_ellipse
    if current_algorithm == config.BRESENHAM:
        brezenham_ellipse(window, xc, yc, a, b)
    elif current_algorithm == config.CANONICAL:
        canon_ellipse(window, xc, yc, a, b)
    elif current_algorithm == config.PARAMETRIC:
        param_ellipse(window, xc, yc, a, b)
    elif current_algorithm == config.MIDDLE_POINT:
        middle_point_ellipse(window, xc, yc, a, b)
    elif current_algorithm == config.LIBRARY:
        window.scene.addEllipse(xc - b, yc - a, a * 2, b * 2, window.pen_colour)
    else:
        message.show_error(config.PROG_ERR1)
        return None


def brezenham_ellipse(win, cx: float, cy: float, a: float, b: float):
    """
    Draws ellipse using brezenham method
    :param win: - class of window
    :param cx: - x center
    :param cy: - y center
    :param a: - width of ellipse
    :param b: - height of ellipse
    :return: pixels on image.
    """
    x = 0  # start values
    y = b
    a = a ** 2
    d = round(b * b / 2 - a * b * 2 + a / 2)
    b = b ** 2
    while y >= 0:
        if (0 < cx + x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy + y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx + x, cy + y, win.pen_colour.rgb())

        if (0 < cx + x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy - y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx + x, cy - y, win.pen_colour.rgb())

        if (0 < cx - x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy + y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx - x, cy + y, win.pen_colour.rgb())

        if (0 < cx - x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy - y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx - x, cy - y, win.pen_colour.rgb())

        if d < 0:  # pixel inside ellipse
            buf = 2 * d + 2 * a * y - a
            x += 1
            if buf <= 0:
                d = d + 2 * b * x + b
            else:
                y -= 1
                d = d + 2 * b * x - 2 * a * y + a + b
        elif d > 0:  # pixel outside ellipse
            buf = 2 * d - 2 * b * x - b
            y -= 1

            if buf > 0:  # вертикальный шаг
                d = d - 2 * y * a + a
            else:
                x += 1
                d = d + 2 * x * b - 2 * y * a + a + b
        elif d == 0.0:  # pixel on ellipse
            x += 1
            y -= 1
            d = d + 2 * x * b - 2 * y * a + a + b
        else:  # Impossible
            continue
    win.paint()


def canon_ellipse(win, cx: float, cy: float, a: float, b: float):
    """
    Draws ellipse using canonical equation method
    :param win: - class of window
    :param cx: - x center
    :param cy: - y center
    :param a: - width of ellipse
    :param b: - height of ellipse
    :return: pixels on image.
    """
    for x in range(0, int(a) + 1, 1):
        y = round(b * math.sqrt(1.0 - x ** 2 / a / a))

        if (0 < cx + x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy + y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx + x, cy + y, win.pen_colour.rgb())

        if (0 < cx + x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy - y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx + x, cy - y, win.pen_colour.rgb())

        if (0 < cx - x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy + y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx - x, cy + y, win.pen_colour.rgb())

        if (0 < cx - x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy - y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx - x, cy - y, win.pen_colour.rgb())

    for y in range(0, int(b) + 1, 1):
        x = round(a * math.sqrt(1.0 - y ** 2 / b / b))
        if (0 < cx + x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy + y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx + x, cy + y, win.pen_colour.rgb())

        if (0 < cx + x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy - y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx + x, cy - y, win.pen_colour.rgb())

        if (0 < cx - x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy + y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx - x, cy + y, win.pen_colour.rgb())

        if (0 < cx - x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy - y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx - x, cy - y, win.pen_colour.rgb())
    win.paint()


def param_ellipse(win, cx: float, cy: float, a: float, b: float):
    """
    Draws ellipse using parametric equation method
    :param win:
    :param cx: - x center
    :param cy: - y center
    :param a: - width of ellipse
    :param b: - height of ellipse
    :return: pixels of image.
    """
    m = max(a, b)
    # length = round(math.pi * m / 2)
    t = 0
    while t < math.pi / 2:
        # mb better to round values
        x = round(a * math.cos(t))
        y = round(b * math.sin(t))

        if (0 < cx + x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy + y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx + x, cy + y, win.pen_colour.rgb())

        if (0 < cx + x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy - y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx + x, cy - y, win.pen_colour.rgb())

        if (0 < cx - x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy + y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx - x, cy + y, win.pen_colour.rgb())

        if (0 < cx - x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy - y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx - x, cy - y, win.pen_colour.rgb())
        t += 1 / m
    win.paint()


def middle_point_ellipse(win, cx: float, cy: float, a: float, b: float):
    """
    Draws ellipse using middle point method
    :param win:
    :param cx: - x center
    :param cy: - y center
    :param a: - width of ellipse
    :param b: - height of ellipse
    :return: pixels on image
    """
    x = 0   # start values
    y = b
    p = b * b - a * a * b + 0.25 * a * a   # tg < 1
    while 2 * (b ** 2) * x < 2 * a * a * y:  # while tg < 1
        if (0 < cx - x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy + y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx - x, cy + y, win.pen_colour.rgb())

        if (0 < cx + x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy - y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx + x, cy - y, win.pen_colour.rgb())

        if (0 < cx - x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy - y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx - x, cy - y, win.pen_colour.rgb())

        if (0 < cx + x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy + y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx + x, cy + y, win.pen_colour.rgb())

        x += 1

        if p < 0:
            p += 2 * b * b * x + b * b
        else:
            y -= 1
            p += 2 * b * b * x - 2 * a * a * y + b * b

    p = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1) * (y - 1) - a * a * b * b

    while y >= 0:

        if (0 < cx - x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy + y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx - x, cy + y, win.pen_colour.rgb())

        if (0 < cx + x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy - y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx + x, cy - y, win.pen_colour.rgb())

        if (0 < cx - x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy - y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx - x, cy - y, win.pen_colour.rgb())

        if (0 < cx + x < config.CANVAS_WIDTH - config.INDENT_OF_PIXMAP
                and 0 < cy + y < config.CANVAS_HEIGHT - config.INDENT_OF_PIXMAP):
            win.image.setPixel(cx + x, cy + y, win.pen_colour.rgb())

        y -= 1

        if p > 0:
            p -= 2 * a * a * y + a * a
        else:
            x += 1
            p += 2 * b * b * x - 2 * a * a * y + a * a
    win.paint()
