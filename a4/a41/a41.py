#!/usr/bin/env python3

from typing import IO

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

class ProEpiloge:
    '''Prologue and Epilogue class'''
    def Prologue(f: IO[str], winTitle: str):
        '''Prologue method'''
        writeHTMLline(f, 0, "<html>")
        writeHTMLline(f, 0, "<head>")
        writeHTMLline(f, 1, f"<title>{winTitle}</title>")
        writeHTMLline(f, 0, "</head>")
        writeHTMLline(f, 0, "<body>")
    
    def Epilogue(f: IO[str]):
        '''Epilogue method'''
        writeHTMLline(f, 0, "</body>")
        writeHTMLline(f, 0, "</html>")

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


def genCircleArt(f: IO[str], t: int):
    '''genART method'''
    drawCircleLine(f, t, Circle((50, 50, 50), (255, 0, 0, 1.0)))
    drawCircleLine(f, t, Circle((200, 50, 50), (255, 0, 0, 1.0)))
    drawCircleLine(f, t, Circle((350, 50, 50), (255, 0, 0, 1.0)))
    drawCircleLine(f, t, Circle((500, 50, 50), (255, 0, 0, 1.0)))
    drawCircleLine(f, t, Circle((650, 50, 50), (255, 0, 0, 1.0)))
    drawCircleLine(f, t, Circle((50, 170, 50), (0, 0, 255, 1.0)))
    drawCircleLine(f, t, Circle((200, 170, 50), (0, 0, 255, 1.0)))
    drawCircleLine(f, t, Circle((350, 170, 50), (0, 0, 255, 1.0)))
    drawCircleLine(f, t, Circle((500, 170, 50), (0, 0, 255, 1.0)))
    drawCircleLine(f, t, Circle((650, 170, 50), (0, 0, 255, 1.0)))

def genRectangleArt(f: IO[str], t: int):
    '''genART method'''
    drawRectangleLine(f, t, Rectangle((0, 240, 100, 100), (255, 0, 0, 1.0)))
    drawRectangleLine(f, t, Rectangle((150, 240, 100, 100), (255, 0, 0, 1.0)))
    drawRectangleLine(f, t, Rectangle((300, 240, 100, 100), (255, 0, 0, 1.0)))
    drawRectangleLine(f, t, Rectangle((450, 240, 100, 100), (255, 0, 0, 1.0)))
    drawRectangleLine(f, t, Rectangle((600, 240, 100, 100), (255, 0, 0, 1.0)))
    drawRectangleLine(f, t, Rectangle((0, 370, 100, 100), (0, 0, 255, 1.0)))
    drawRectangleLine(f, t, Rectangle((150, 370, 100, 100), (0, 0, 255, 1.0)))
    drawRectangleLine(f, t, Rectangle((300, 370, 100, 100), (0, 0, 255, 1.0)))
    drawRectangleLine(f, t, Rectangle((450, 370, 100, 100), (0, 0, 255, 1.0)))
    drawRectangleLine(f, t, Rectangle((600, 370, 100, 100), (0, 0, 255, 1.0)))

def openSVGcanvas(f: IO[str], t: int, canvas: tuple):
    '''openSVGcanvas method'''
    ts: str = "   " * t
    writeHTMLcomment(f, t, "Define SVG drawing box")
    f.write(f'{ts}<svg width="{canvas[0]}" height="{canvas[1]}">\n')


def closeSVGcanvas(f: IO[str], t: int):
    '''closeSVGcanvas method'''
    ts: str = "   " * t
    f.write(f'{ts}</svg>\n')


def writeHTMLline(f: IO[str], t: int, line: str):
    '''writeLineHTML method'''
    ts = "   " * t
    f.write(f"{ts}{line}\n")


def writeHTMLfile():
    '''writeHTMLfile method'''
    fnam: str = "a41.html"
    winTitle = "Han Tran's Art Part 1"
    f: IO[str] = open(fnam, "w")
    ProEpiloge.Prologue(f, winTitle)
    openSVGcanvas(f, 1, (500, 300))
    genCircleArt(f, 2)
    genRectangleArt(f, 2)
    closeSVGcanvas(f, 1)
    ProEpiloge.Epilogue(f)
    f.close()


def main():
    '''main method'''
    writeHTMLfile()


main()
