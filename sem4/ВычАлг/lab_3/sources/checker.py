import re


def strIsFloatOrInt(x: str) -> bool:
    return True if re.fullmatch(r'^-?\d+\.\d+|-?\d+$', x.strip(" ")) else False


def strIsInt(x: str) -> bool:
    return True if re.fullmatch(r'^-?\d+$', x.strip(" ")) else False


