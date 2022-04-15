#!/usr/bin/env python3


import random
from random import randint
from typing import IO

class GenRandom:
    '''GenRandom class'''
    def __init__(self, cnt: int, xmin: int, xmax: int, ymin: int, ymax: int):
        self.sha = randint(ArtConfig(cnt, xmin, xmax, ymin, ymax).shamin, ArtConfig(cnt, xmin, xmax, ymin, ymax).shamax)
        self.x   = randint(ArtConfig(cnt, xmin, xmax, ymin, ymax).xmin, ArtConfig(cnt, xmin, xmax, ymin, ymax).xmax)
        self.y   = randint(ArtConfig(cnt, xmin, xmax, ymin, ymax).ymin, ArtConfig(cnt, xmin, xmax, ymin, ymax).ymax)
        self.rad = randint(ArtConfig(cnt, xmin, xmax, ymin, ymax).radmin, ArtConfig(cnt, xmin, xmax, ymin, ymax).radmax)
        self.rx  = randint(ArtConfig(cnt, xmin, xmax, ymin, ymax).rxmin, ArtConfig(cnt, xmin, xmax, ymin, ymax).rxmax)
        self.ry  = randint(ArtConfig(cnt, xmin, xmax, ymin, ymax).rymin, ArtConfig(cnt, xmin, xmax, ymin, ymax).rymax)
        self.w   = randint(ArtConfig(cnt, xmin, xmax, ymin, ymax).wmin, ArtConfig(cnt, xmin, xmax, ymin, ymax).wmax)
        self.h   = randint(ArtConfig(cnt, xmin, xmax, ymin, ymax).hmin, ArtConfig(cnt, xmin, xmax, ymin, ymax).hmax)
        self.r   = randint(ArtConfig(cnt, xmin, xmax, ymin, ymax).rmin, ArtConfig(cnt, xmin, xmax, ymin, ymax).rmax)
        self.g   = randint(ArtConfig(cnt, xmin, xmax, ymin, ymax).gmin, ArtConfig(cnt, xmin, xmax, ymin, ymax).gmax)
        self.b   = randint(ArtConfig(cnt, xmin, xmax, ymin, ymax).bmin, ArtConfig(cnt, xmin, xmax, ymin, ymax).bmax)
        self.op  = round(random.uniform(ArtConfig(cnt, xmin, xmax, ymin, ymax).opmin, ArtConfig(cnt, xmin, xmax, ymin, ymax).opmax), 1)
    def random_tuple(self):
        '''Generate random data tuple'''
        rtuple = (self.sha, self.x, self.y, self.rad, self.rx, self.ry, self.w, self.h, self.r, self.g, self.b, self.op)
        return rtuple

class ArtConfig:
    '''ArtConfig class'''
    def __init__(self, cnt: int,xmin: int, xmax: int, ymin: int, ymax: int):
        self.filename: str = "a43.html"
        self.wintitle: str = "Han Tran's Art Part 3"
        self.cnt: int = cnt
        self.shamin: int = 0
        self.shamax: int = 3
        self.xmin: int = xmin
        self.xmax: int = xmax
        self.ymin: int = ymin
        self.ymax: int = ymax
        self.radmin: int = 0
        self.radmax: int = 100
        self.rxmin: int = 10
        self.rxmax: int = 30
        self.rymin: int = 10
        self.rymax: int = 30
        self.wmin: int = 10
        self.wmax: int = 100
        self.hmin: int = 10
        self.hmax: int = 100
        self.rmin: int = 0
        self.rmax: int = 255
        self.gmin: int = 0
        self.gmax: int = 255
        self.bmin: int = 0
        self.bmax: int = 255
        self.opmin: float = 0.0
        self.opmax: float = 1.0

class Circle:
    '''Circle class'''
    def __init__(self, cir: tuple, col: tuple):
        self.cx: int = cir[0]
        self.cy: int = cir[1]
        self.rad: int = cir[2]
        self.red: int = col[0]
        self.green: int = col[1]
        self.blue: int = col[2]
        self.op: float = col[3]


class Rectangle:
    '''Rectangle class'''
    def __init__(self, rec: tuple, col:tuple):
        self.rx: int = rec[0]
        self.ry: int = rec[1]
        self.rw: int = rec[2]
        self.rl: int = rec[3]
        self.red: int = col[0]
        self.green: int = col[1]
        self.blue: int = col[2]
        self.op: float = col[3]

class Ellipse:
    '''Rectangle class'''
    def __init__(self, ell: tuple, col:tuple):
        self.ex: int = ell[0]
        self.ey: int = ell[1]
        self.rx: int = ell[2]
        self.ry: int = ell[3]
        self.red: int = col[0]
        self.green: int = col[1]
        self.blue: int = col[2]
        self.op: float = col[3]

class ProEpiloge:
    def Prologue(f: IO[str], winTitle: str):
        writeHTMLline(f, 0, "<html>")
        writeHTMLline(f, 0, "<head>")
        writeHTMLline(f, 1, f"<title>{winTitle}</title>")
        writeHTMLline(f, 0, "</head>")
        writeHTMLline(f, 0, "<body>")
    
    def Epilogue(f: IO[str]):
        writeHTMLline(f, 0, "</body>")
        writeHTMLline(f, 0, "</html>")

def get_random_data(cnt, xmax, ymax) -> tuple:
    '''Generate a random data tuple list'''
    data_list = []
    for i in range(0,cnt):
        data_tuple: tuple = GenRandom(cnt, 0, xmax, 0, ymax).random_tuple()
        data_list.append(data_tuple)
    return data_list

def writeHTMLcomment(f: IO[str], t: int, com: str):
    '''writeHTMLcomment method'''
    ts: str = "   " * t
    f.write(f'{ts}<!--{com}-->\n')


def drawCircleLine(f: IO[str], t: int, c: Circle):
    '''drawCircle method'''
    ts: str = "   " * t
    line: str = f'<circle cx="{c.cx}" cy="{c.cy}" r="{c.rad}" fill="rgb({c.red}, {c.green}, {c.blue})" fill-opacity="{c.op}"></circle>'
    f.write(f"{ts}{line}\n")

def drawRectangleLine(f: IO[str], t: int, r: Rectangle):
    '''drawCircle method'''
    ts: str = "   " * t
    line: str = f'<rect x="{r.rx}" y="{r.ry}" width="{r.rw}" height="{r.rl}" fill="rgb({r.red}, {r.green}, {r.blue})" fill-opacity="{r.op}"></rect>'
    f.write(f"{ts}{line}\n")

def drawEllipseLine(f: IO[str], t: int, e: Ellipse):
    '''drawCircle method'''
    ts: str = "   " * t
    line: str = f'<ellipse cx="{e.ex}" cy="{e.ey}" rx="{e.rx}" ry="{e.ry}" fill="rgb({e.red}, {e.green}, {e.blue})" fill-opacity="{e.op}"></ellipse>'
    f.write(f"{ts}{line}\n")

def genShapeArt(f: IO[str], t: int, data: list):
    '''genART method'''
    for i in range(len(data)):
        if data[i][0] == 0:
                drawCircleLine(f, t, Circle((data[i][1], data[i][2], data[i][3]), (data[i][8], data[i][9], data[i][10], data[i][11])))
        elif data[i][0] == 1:
            drawRectangleLine(f, t, Rectangle((data[i][1], data[i][2], data[i][6], data[i][7]), (data[i][8], data[i][9], data[i][10], data[i][11])))
        elif data[i][0] == 3:
            drawEllipseLine(f, t, Ellipse((data[i][1], data[i][2], data[i][4], data[i][5]), (data[i][8], data[i][9], data[i][10], data[i][11])))

def genRectangleArt(f: IO[str], t: int, data: list):
    '''genART method'''
    for i in range(data):
        drawRectangleLine(f, t, Rectangle((data[i][1], data[i][2], data[i][6], data[i][7]), (data[i][8], data[i][9], data[i][10], data[i][11])))
    

def openSVGcanvas(f: IO[str], t: int, canvas: tuple):
    '''openSVGcanvas method'''
    ts: str = "   " * t
    writeHTMLcomment(f, t, "Define SVG drawing box")
    f.write(f'{ts}<svg width="{canvas[0]}" height="{canvas[1]}">\n')


def closeSVGcanvas(f: IO[str], t: int):
    '''closeSVGcanvas method'''
    ts: str = "   " * t
    f.write(f'{ts}</svg>\n')
    #f.write(f'</body>\n')
    #f.write(f'</html>\n')


def writeHTMLline(f: IO[str], t: int, line: str):
    '''writeLineHTML method'''
    ts = "   " * t
    f.write(f"{ts}{line}\n")


def writeHTMLfile():
    '''writeHTMLfile method'''
    xmax = 600
    ymax = 400
    cnt = 10000
    fnam: str = ArtConfig(cnt, 0, xmax, 0, ymax).filename
    winTitle = ArtConfig(cnt, 0, xmax, 0, ymax).wintitle
    f: IO[str] = open(fnam, "w")
    ProEpiloge.Prologue(f, winTitle)
    openSVGcanvas(f, 1, (xmax, ymax))
    data = get_random_data(cnt, xmax, ymax)
    genShapeArt(f, 2, data)
    closeSVGcanvas(f, 1)
    ProEpiloge.Epilogue(f)
    f.close()

def main():
    '''main method'''
    writeHTMLfile()


main()
