#!/usr/bin/env python3


import random
from random import randint

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
        self.filename: str = ""
        self.wintitle: str = ""
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

def print_title():
    '''Print Title of Table'''
    title_list: list = ["CNT", "SHA", "X", "Y", "RAD", "RX", "RY", "W", "H", "R", "G", "B", "OP"]
    for i in range(len(title_list)):
        print("{:>3}".format(f"{title_list[i]}"), end=" ")
    print()

def print_data(cnt, xmax, ymax):
    '''Print Data of Table'''
    for i in range(0, cnt):
        data_list: tuple = GenRandom(10, 0, xmax, 0, ymax).random_tuple()
        print(f"{i:3}", end= " ")
        for i in range(len(data_list)):
            print(f"{data_list[i]:3}", end= " ")
        print()

def main():
    '''main method'''
    print_title()
    print_data(10, 500, 300)
main()