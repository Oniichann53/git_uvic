#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Feb 01 08:35:33 2022
@author: rivera

This is a text processor that allows to translate XML-based events to YAML-based events.
CAREFUL: You ARE NOT allowed using (i.e., import) modules/libraries/packages to parse XML or YAML
(e.g., yaml or xml modules). You will need to rely on Python collections to achieve the reading of XML files and the
generation of YAML files.
"""
from calendar import day_abbr, month
import sys
import re
import datetime



def main():
    """The main entry point for the program.
    """
    # Calling a dummy function to illustrate the process in Python
    # print('Hi! from:', sys.argv[0])
    event_list = []
    argv = {"start":"", "end":"", "event_file":"", "cir_file":"", "br_file":""}

    parse_argv(argv)

    parse_event(event_list, argv["event_file"])
    broadcaster_list = parse_broadcaster(argv["br_file"])
    circuit_list = parse_circuit(argv["cir_file"])

    for i in range(len(event_list)):
        convert_broadcaster(event_list[i], broadcaster_list)
    

    for i in range(len(event_list)):
        convert_circuit(event_list[i], circuit_list)
    

    event_list = sort_list(event_list)
    date_s = parse_date(argv["start"])
    date_e = parse_date(argv["end"])
    event_list = final_list(event_list, date_s, date_e)
    output(event_list,circuit_list)

def parse_argv(argv):
    argv1 = re.split("=", sys.argv[1])
    argv2 = re.split("=", sys.argv[2])
    argv3 = re.split("=", sys.argv[3])
    argv4 = re.split("=", sys.argv[4])
    argv5 = re.split("=", sys.argv[5])

    argv["start"] = argv1[1]
    argv["end"] = argv2[1]
    argv["event_file"] = argv3[1]
    argv["cir_file"] = argv4[1]
    argv["br_file"] = argv5[1]

def parse_broadcaster(filename):
    br_list = []
    fil_lines = []
    with open(filename) as file:
        for line in file:
            line = re.findall(r'<(.*?)>(.*?)</\1>', line)
            if len(line) > 0:
                fil_lines.append(line[0])
    br_dic = {}
    for i in range(len(fil_lines)):
        tup = fil_lines[i]
        br_dic[tup[0]] = tup[1]
        if (i+1)%3 == 0 and i>0:
            br_list.append(br_dic)
            br_dic = {}
    file.close()
    return br_list

def parse_circuit(filename):
    cir_list = []
    fil_lines = []
    with open(filename) as file:
        for line in file:
            line = re.findall(r'<(.*?)>(.*?)</\1>', line)
            if len(line) > 0:
                fil_lines.append(line[0])
    cir_dic = {}
    for i in range(len(fil_lines)):
        tup = fil_lines[i]
        cir_dic[tup[0]] = tup[1]
        if (i+1)%5 == 0 and i>0:
            cir_list.append(cir_dic)
            cir_dic = {}
    file.close()
    return cir_list

def parse_event(event_list,filename):
    fil_lines = []
    with open(filename) as file:
        for line in file:
            line = re.findall(r'<(.*?)>(.*?)</\1>', line)
            if len(line) > 0:
                fil_lines.append(line[0])
    event_dic = {}
    for i in range(len(fil_lines)):
        tup = fil_lines[i]
        event_dic[tup[0]] = tup[1]
        if (i+1)%9 == 0 and i>0:
            event_list.append(event_dic)
            event_dic = {}
    file.close()

def parse_date(date):
    date = re.split("/", date)
    return datetime.datetime(int(date[0]), int(date[1]), int(date[2]), 0, 0)

def convert_broadcaster(event, broadcaster_list):
    broadcaster_tup = re.split(",",event["broadcaster"])
    for i in range(len(broadcaster_tup)):
        for j in range(len(broadcaster_list)):
            if broadcaster_tup[i] == broadcaster_list[j]["id"]:
                broadcaster_tup[i] = broadcaster_list[j]["name"]
    event["broadcaster"] = broadcaster_tup

def convert_circuit(event, circuit_list):
    for i in range(len(circuit_list)):
        if event["location"] == circuit_list[i]["id"]:
            event["location"] = circuit_list[i]["location"]
     

def sort_list(event_list):
    temp = [None] * len(event_list)
    size = 0
    size_event = len(event_list)
    while size != size_event:
        min_date = convert_datetime_hour(event_list[0])
        min_event = event_list[0]
        for i in range(len(event_list)):
            date = convert_datetime_hour(event_list[i])
            if date < min_date:
                min_date = date
                min_event = event_list[i]   
        temp[size] = min_event
        size += 1
        event_list.remove(min_event)
    return temp

def convert_datetime(event):
    start = re.split(":", event["start"])
    end = re.split(":", event["end"])
    day = int(event["day"])
    month = int(event["month"])
    year = int(event["year"])
    result = datetime.datetime(year, month, day)
    return result

def convert_datetime_hour(event):
    start = re.split(":", event["start"])
    end = re.split(":", event["end"])
    day = int(event["day"])
    month = int(event["month"])
    year = int(event["year"])
    hour_s = int(start[0])
    minute_s = int(start[1])
    result = datetime.datetime(year, month, day, hour_s, minute_s)
    return result

def convert_date_str(event):
    day = event["day"]
    month = event["month"]
    year = event["year"]
    return day+"-"+month+"-"+year

def convert_date_formal(event):
    if int(event["month"]) == 1:
        return "January"
    if int(event["month"]) == 2:
        return "February"
    if int(event["month"]) == 3:
        return "March"
    if int(event["month"]) == 4:
        return "April"
    if int(event["month"]) == 5:
        return "May"
    if int(event["month"]) == 6:
        return "June"
    if int(event["month"]) == 7:
        return "July"
    if int(event["month"]) == 8:
        return "August"
    if int(event["month"]) == 9:
        return "September"
    if int(event["month"]) == 10:
        return "October"
    if int(event["month"]) == 11:
        return "November"
    if int(event["month"]) == 12:
        return "December"

def final_list(event_list, date_s, date_e):
    temp = []
    for i in range(len(event_list)):
        print(i)
        date = convert_datetime_hour(event_list[i])
        if date >= date_s and date <= date_e:
                temp.append(event_list[i])
    return temp         

def convert_event(event, cir_list):
    temp = []
    id = event["id"]
    description = event["description"]
    for i in range(len(cir_list)):
        if cir_list[i]["location"] == event["location"]:
            name = cir_list[i]["name"]
            direction = cir_list[i]["direction"]
            circuit = f"{name} ({direction})" 
            timezone = cir_list[i]["timezone"]
    location = event["location"]
    start = re.split(":", event["start"])
    end = re.split(":", event["end"])
    day = int(event["day"])
    month = convert_date_formal(event)
    year = int(event["year"])
    hour_s = int(start[0])
    minute_s = int(start[1])
    hour_e = int(end[0])
    minute_e = int(end[1])
    dweek = convert_datetime_hour(event)
    dweek = dweek.strftime("%A")
    
    if hour_s == 0:
        hour_s = 12
        s_time = "AM"
    elif hour_s < 12 and hour_s > 0:
        s_time = "AM"
    else:
        s_time = "PM"
        if hour_s != 12:
            hour_s -=12
    if hour_e == 0:
        hour_e = 12
        e_time = "AM"
    elif hour_e < 12 and hour_s > 0:
        e_time = "AM"
    else:
        e_time = "PM"
        if hour_e != 12:
            hour_e -=12
    when = f"{hour_s:02}:{minute_s:02} {s_time} - {hour_e:02}:{minute_e:02} {e_time} {dweek}, {month} {day}, {year} ({timezone})"
    temp.append(id)
    temp.append(description)
    temp.append(circuit)
    temp.append(location)
    temp.append(when)
    return temp




def output(event_list, cir_list):
    file = open("output.yaml", "w")
    file.write("events:\n")
    date_str = convert_date_str(event_list[0])
    file.write(f"  - {date_str}:\n")
    id_list = convert_event(event_list[0], cir_list)
    file.write(f"    - id: {id_list[0]}\n")
    file.write(f"      description: {id_list[1]}\n")
    file.write(f"      circuit: {id_list[2]}\n")
    file.write(f"      location: {id_list[3]}\n")
    file.write(f"      when: {id_list[4]}\n")
    broadcaster = event_list[0]["broadcaster"]
    file.write(f"      broadcasters:\n")
    for i in range(len(broadcaster)):
        file.write(f"        - {broadcaster[i]}\n")
        if len(event_list) > 1:
             print("\n")
    for i in range(1,(len(event_list))):
        if convert_datetime(event_list[i]) == convert_datetime(event_list[i-1]):
            id_list = convert_event(event_list[i], cir_list)
            file.write(f"    - id: {id_list[0]}\n")
            file.write(f"      description: {id_list[1]}\n")
            file.write(f"      circuit: {id_list[2]}\n")
            file.write(f"      location: {id_list[3]}\n")
            file.write(f"      when: {id_list[4]}\n")
            broadcaster = event_list[0]["broadcaster"]
            file.write(f"      broadcasters:\n")
            for i in range(len(broadcaster)):
                file.write(f"        - {broadcaster[i]}")
                if i != len(event_list):
                    print("\n")
        else:
            date_str = convert_date_str(event_list[0])
            file.write(f"  - {date_str}:\n")
            id_list = convert_event(event_list[i], cir_list)
            file.write(f"    - id: {id_list[0]}\n")
            file.write(f"      description: {id_list[1]}\n")
            file.write(f"      circuit: {id_list[2]}\n")
            file.write(f"      location: {id_list[3]}\n")
            file.write(f"      when: {id_list[4]}\n")
            broadcaster = event_list[0]["broadcaster"]
            file.write(f"      broadcasters:\n")
            for i in range(len(broadcaster)):
                file.write(f"        - {broadcaster[i]}")
                if i != len(event_list):
                    print("\n")
    
    






if __name__ == '__main__':
    main()
    