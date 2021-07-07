import re
import math
import config


def checkData(coord: str) -> bool:
    return bool(re.fullmatch(r"[-, +]?\d+(?:\.\d+)?\s*,\s*[-, +]?\d+(?:\.\d+)?", coord))


def formCoordFromText(text: str) -> list or None:
    coordsText = text.split('\n')
    coords = []
    # print(coordsText)
    for coordText in coordsText:
        if coordText == '':
            coordsText.remove(coordText)
            continue
        coordText.strip(" ")
        if not checkData(coordText):
            return None
        twoNumbersText = coordText.split(',')
        coord = (float(twoNumbersText[0].strip(" ")), float(twoNumbersText[1].strip(" ")))
        coords.append(coord)
    return coords


'''
Функция проверки НЕ принадлежности трех точек одной прямой
Input:
    threePoints - три точки
Output:
    True, если все три точки не принадлежат одной прямой, False, если три точки 
    лежат на одной прямой или None, если переданы неверные данные
'''
def checkNotStraight(threePoints: list) -> bool or None:
    if len(threePoints) != 3:
        return None
    firstPoint, secondPoint, thirdPoint = threePoints
    if (secondPoint[1] - firstPoint[1]) * (thirdPoint[0] - firstPoint[0]) != \
            (thirdPoint[1] - firstPoint[1]) * (secondPoint[0] - firstPoint[0]):
        return True
    else:
        return False


'''
Функция вычисления коэффициентов ур-я прямой
Input:
    twoPoints - две точки
Output:
    [a,b,c] or None - коэффициенты или None, если переданы неверные данные
'''
def findStraightCoef(twoPoints: list) -> list or None:
    if len(twoPoints) != 2:
        return None
    firstPoint, secondPoint = twoPoints
    a = firstPoint[1] - secondPoint[1]
    b = secondPoint[0] - firstPoint[0]
    c = -b * firstPoint[1] + -a * firstPoint[0]
    return [a, b, c]


'''
Функция вычисления коэф ур-я прямой, перпендикулярной заданной
Input:
    twoPoints - точка вершины и коэф противолежащей прямой
Output:
    [a, b, c] - коэффициенты
'''
def findPerpendicularStraightCoef(straightAndPoint: list) -> list or None:
    if len(straightAndPoint) != 2:
        return None
    straight, center = straightAndPoint
    a = -straight[1]
    b = straight[0]
    c = -a * center[0] - b * center[1]
    return [a, b, c]


'''
Функция определения координат точки пересечения двух прямых
Input:
    twoStraightCoef - коэффициенты двух прямых
Output:
    point or None - координаты точки или None, если переданы неверные данные
'''
def findIntersection(twoStraightCoef: list) -> tuple or None:
    if len(twoStraightCoef) != 2 or len(twoStraightCoef[0]) != 3 \
            or len(twoStraightCoef[0]) != 3:
        return None
    firstStraightCoef, secondStraightCoef = twoStraightCoef
    p = firstStraightCoef[0] * secondStraightCoef[1] - \
        secondStraightCoef[0] * firstStraightCoef[1]
    tmp1 = (-firstStraightCoef[2] * secondStraightCoef[1] +
            firstStraightCoef[1] * secondStraightCoef[2])
    tmp2 = (firstStraightCoef[0] * -secondStraightCoef[2] +
            firstStraightCoef[2] * secondStraightCoef[0])
    x = tmp1 / p
    y = tmp2 / p
    return x, y


'''
Функция определения угла между двумя прямыми
Input:
    twoStraightCoef - коэффициенты двух прямых
    eps - эпсилон из config
Output:
    angle or None - угол между абсциссой или None, если переданы неверные данные
'''
def calculateAngle(twoStraightCoef: list) -> float or None:
    if len(twoStraightCoef) != 2 or len(twoStraightCoef[0]) != 3 and \
            len(twoStraightCoef[1]) != 3:
        return None
    firstStraightCoef, secondStraightCoef = twoStraightCoef
    p = firstStraightCoef[0] * secondStraightCoef[1] - \
        secondStraightCoef[0] * firstStraightCoef[1]
    s = firstStraightCoef[0] * secondStraightCoef[0] + \
        firstStraightCoef[1] * secondStraightCoef[1]
    c = firstStraightCoef[0] * secondStraightCoef[1] - \
        secondStraightCoef[0] * firstStraightCoef[1]
    if s == 0 or (math.fabs(p) <= config.eps and c > 100 * s):
        return math.pi / 2
    else:
        t = math.fabs(c/s)
        #return math.pi/2 - (math.atan(t))
        return math.atan(t)


'''
Функция вычисления координат ортцентра
Input:
    threePoints - три точки
Output:
    intersecPoint - ортцентр (x, y)
'''
def calcOrthocenter(threePoints: list) -> tuple or None:
    if len(threePoints) != 3:
        return None
    # a, b, c - points
    a, b, c = threePoints
    firstCoef = findStraightCoef([a, b])
    secondCoef = findStraightCoef([a, c])
    firstPerp = findPerpendicularStraightCoef([firstCoef, c])
    secondPerp = findPerpendicularStraightCoef([secondCoef, b])
    intersecPoint = findIntersection([firstPerp, secondPerp])
    return intersecPoint


def mainFunc(firstText: str, secondText: str) -> tuple or None:
    firstCoords = formCoordFromText(firstText)
    secondCoords = formCoordFromText(secondText)
    if firstCoords == None or secondCoords == None:
        return None, None, 1
    firstCoords = list(set(firstCoords))
    secondCoords = list(set(secondCoords))
    if len(firstCoords) < 3 or len(secondCoords) < 3:
        return None, None, 1

    minAngle = 1000
    count = 0
    minPoint1 = []
    minPoint2 = []

    for i in range(len(firstCoords) - 2):
        for j in range(i + 1, len(firstCoords) - 1):
            for k in range(j + 1, len(firstCoords)):
                if not checkNotStraight([firstCoords[i],
                                          firstCoords[j],
                                          firstCoords[k]]):
                    continue
                for i_2 in range(len(secondCoords) - 2):
                    for j_2 in range(i_2 + 1, len(secondCoords) - 1):
                        for k_2 in range(j_2 + 1, len(secondCoords)):
                            if not checkNotStraight([secondCoords[i_2],
                                                      secondCoords[j_2],
                                                      secondCoords[k_2]]):
                                continue
                            count += 1
                            firstPointIntersec = calcOrthocenter([firstCoords[i],
                                                                  firstCoords[j],
                                                                  firstCoords[k]])
                            secondPointIntersec = calcOrthocenter([secondCoords[i_2],
                                                                   secondCoords[j_2],
                                                                   secondCoords[k_2]])
                            mainStraight = findStraightCoef([firstPointIntersec, secondPointIntersec])
                            angle = calculateAngle([mainStraight, [0, 1, 0]])
                            if angle < minAngle:
                                minPoint1 = [i, j, k]
                                minPoint2 = [i_2, j_2, k_2]
                                minAngle = angle
    if count == 0:
        return None, None, 2
    '''
    print(count)
    if minPoint1 != [] and minPoint2 != []:
        print(minAngle)
        print(minPoint1)
        print(minPoint2)
    '''
    return [[firstCoords[minPoint1[0]], firstCoords[minPoint1[1]], firstCoords[minPoint1[2]]],
            [secondCoords[minPoint2[0]], secondCoords[minPoint2[1]], secondCoords[minPoint2[2]]]], minAngle, 0

'''
Функция нахождения минимальных и максимальных точек
Input:
    coordinates - два множества
Output:
    minX, maxX, minY, maxY - минимальные и максимальные точки
'''
def findMinAndMax(coordinates: list) -> tuple:
    maxX = coordinates[0][0]
    minX = coordinates[0][0]
    maxY = coordinates[0][1]
    minY = coordinates[0][1]
    for i in range(1, len(coordinates)):
        if coordinates[i][0] > maxX:
            maxX = coordinates[i][0]

        if coordinates[i][0] < minX:
            minX = coordinates[i][0]

        if coordinates[i][1] > maxY:
            maxY = coordinates[i][1]

        if coordinates[i][1] < minY:
            minY = coordinates[i][1]
    return minX, maxX, minY, maxY

'''
Функция нахождения минимальных и максимальных точек
Input:
    coordinates - два множества
Output:
    minX, maxX, minY, maxY - минимальные и максимальные точки
'''
def scaleCoord(coordinates: list, k: tuple, ext: tuple) -> list:
    newCoords = []
    for coord in coordinates:
        x = int(round(config.indent + (coord[0] - ext[0]) * k[0]))
        y = int(round(config.indent + (ext[1] - coord[1]) * k[1]))
        newCoords.append((x, y))
    return newCoords



def scaling(sixPoints: list) -> list or None:
    firstCoords, secondCoords, line = sixPoints
    firstExt = findMinAndMax(firstCoords)
    secondExt = findMinAndMax(secondCoords)
    thirdExt = findMinAndMax(line)

    minX = min(firstExt[0], secondExt[0])
    maxX = max(firstExt[1], secondExt[1])
    minY = min(firstExt[2], secondExt[2])
    maxY = max(firstExt[3], secondExt[3])
    minX = min(minX, thirdExt[0])
    maxX = max(maxX, thirdExt[1])
    minY = min(minY, thirdExt[2])
    maxY = max(maxY, thirdExt[3])

    kX = (config.canvasWidth - 2 * config.indent) / (maxX - minX)
    kY = (config.canvasHeight - 2 * config.indent) / (maxY - minY)

    firstCoords = scaleCoord(firstCoords, (kX, kY), (minX, maxY))
    secondCoords = scaleCoord(secondCoords, (kX, kY), (minX, maxY))
    line = scaleCoord(line, (kX, kY), (minX, maxY))

    return [firstCoords, secondCoords, line]


def extraSchame(threePoints: list) -> list:
    points = []
    for i in range(len(threePoints) - 1):
        straight = findStraightCoef([threePoints[i % 3], threePoints[(i + 1) % 3]])
        perpStraight = findPerpendicularStraightCoef([straight, threePoints[(i + 2) % 3]])
        points.append(findIntersection([straight, perpStraight]))
    return points



