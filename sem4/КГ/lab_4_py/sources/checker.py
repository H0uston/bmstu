import re


def check_float(data: str) -> bool:
    """
    Checks if the data is float number
    :param data: - some string
    :return: True if data is float number otherwise False
    """
    return bool(re.fullmatch(r"^\s*[+-]?(?:\d+(?:\.\d+)?)\s*$", data))
